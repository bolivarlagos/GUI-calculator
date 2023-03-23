#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_BUTTONS 10
#define MAX_OPERATORS 6

GtkWidget *screen;
char number_container[MAX_BUTTONS];
char final_result[MAX_BUTTONS];

int first_number, second_number;
int result = 0;
char *selected;

typedef struct
{
  char *value;
  int col, row, width, height;
} Positions;

Positions coordinates[MAX_BUTTONS] =
{
  {"0", 0, 5, 1, 1},
  {"1", 0, 4, 1, 1},
  {"2", 1, 4, 1, 1},
  {"3", 2, 4, 1, 1},
  {"4", 0, 3, 1, 1},
  {"5", 1, 3, 1, 1},
  {"6", 2, 3, 1, 1},
  {"7", 0, 2, 1, 1},
  {"8", 1, 2, 1, 1},
  {"9", 2, 2, 1, 1},
};

Positions ope_coordinates[MAX_OPERATORS] =
{
  {"=", 1, 5, 1, 1},
  {"C", 2, 5, 1, 1},
  {"+", 3, 2, 1, 1},
  {"-", 3, 3, 1, 1},
  {"*", 3, 4, 1, 1},
  {"/", 3, 5, 1, 1},
};

static void print_result(int result)
{
  sprintf(final_result, "%d", result);
  gtk_label_set_text(GTK_LABEL(screen), final_result);
}

static void calculate_result(char *selected)
{
  if (selected == "+")
  {
    result = first_number + second_number;
  }
  else if (selected == "-")
  {
    result = first_number - second_number;
  }
  else if (selected == "*")
  {
    result = first_number * second_number;
  }
  else
  {
    result = first_number / second_number;
  }
}

static void set_selected(char *operation_type)
{
  selected = operation_type;
  first_number = atoi(number_container);
  strcpy(number_container, "");
}

static void number_button_handler(GtkWidget *widget, char *data)
{
  strcat(number_container, data);
  gtk_label_set_text(GTK_LABEL(screen), number_container);
}

static void operator_button_handler(GtkWidget *widget, char *data)
{
  if (data == "C")
  {
    strcpy(number_container, "");
    gtk_label_set_text(GTK_LABEL(screen), "");
  }
  else if (data == "=")
  {
    second_number = atoi(number_container);
    calculate_result(selected);
    print_result(result);
  }
  else
  {
    set_selected(data);
  }
}

static void make_single_number_button(GtkWidget *grid, GtkWidget *btn, Positions pos)
{
  btn = gtk_button_new_with_label(pos.value);
  g_signal_connect(btn, "clicked", G_CALLBACK(number_button_handler), pos.value);
  gtk_grid_attach(GTK_GRID(grid), btn, pos.col, pos.row, pos.width, pos.height);
}

static void make_single_operator_button(GtkWidget *grid, GtkWidget *btn, Positions ope_pos)
{
  btn = gtk_button_new_with_label(ope_pos.value);
  g_signal_connect(btn, "clicked", G_CALLBACK(operator_button_handler), ope_pos.value);
  gtk_grid_attach(GTK_GRID(grid), btn, ope_pos.col, ope_pos.row, ope_pos.width, ope_pos.height);
}

static void make_all_number_buttons(GtkWidget *grid, GtkWidget *btn)
{
  for (int i = 0; i < MAX_BUTTONS; i++)
  {
    make_single_number_button(grid, btn, coordinates[i]);
  }
}

static void make_all_operator_buttons(GtkWidget *grid, GtkWidget *btn)
{
  for (int i = 0; i < MAX_OPERATORS; i++)
  {
    make_single_operator_button(grid, btn, ope_coordinates[i]);
  }
}

static void activate(GtkApplication *app)
{
  GtkWidget *window;
  GtkWidget *number_buttons;
  GtkWidget *operator_buttons;
  GtkWidget *grid;

  window = gtk_application_window_new(app);
  grid = gtk_grid_new();

  screen = gtk_label_new("");
  gtk_grid_attach(GTK_GRID(grid), screen, 0, 0, 12, 1);

  gtk_window_set_child(GTK_WINDOW(window), grid);
  gtk_window_set_title(GTK_WINDOW(window), "Calculator");

  make_all_number_buttons(grid, number_buttons);
  make_all_operator_buttons(grid, operator_buttons);

  gtk_widget_show(window);
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.calculator", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
