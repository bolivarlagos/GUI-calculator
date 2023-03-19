#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

GtkWidget *screen;
char number_container[100];
char final_result[100];

int first_number, second_number;
int result = 0;
char *selected;

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
  } else if (data == "=")
  {
    second_number = atoi(number_container);
    calculate_result(selected);
    print_result(result);
  } else 
  {
    set_selected(data);
  }
}

static void make_number_button(
    GtkWidget *grid,
    GtkWidget *btn,
    char *data,
    int column,
    int row,
    int width,
    int height)
{
  btn = gtk_button_new_with_label(data);
  g_signal_connect(btn, "clicked", G_CALLBACK(number_button_handler), data);
  gtk_grid_attach(GTK_GRID(grid), btn, column, row, width, height);
}

static void make_operator_button(
    GtkWidget *grid,
    GtkWidget *btn,
    char *data,
    int column,
    int row,
    int width,
    int height)
{
  btn = gtk_button_new_with_label(data);
  g_signal_connect(btn, "clicked", G_CALLBACK(operator_button_handler), data);
  gtk_grid_attach(GTK_GRID(grid), btn, column, row, width, height);
}

static void activate(GtkApplication *app)
{
  GtkWidget *window;
  GtkWidget *nummber_buttons;
  GtkWidget *operator_buttons;
  GtkWidget *grid;

  window = gtk_application_window_new(app);
  grid = gtk_grid_new();

  screen = gtk_label_new("");
  gtk_grid_attach(GTK_GRID(grid), screen, 0, 0, 12, 2);

  gtk_window_set_child(GTK_WINDOW(window), grid);
  gtk_window_set_title(GTK_WINDOW(window), "Calculator");

  make_number_button(grid, nummber_buttons, "0", 0, 5, 1, 1);
  make_number_button(grid, nummber_buttons, "1", 0, 4, 1, 1);
  make_number_button(grid, nummber_buttons, "2", 1, 4, 1, 1);
  make_number_button(grid, nummber_buttons, "3", 2, 4, 1, 1);
  make_number_button(grid, nummber_buttons, "4", 0, 3, 1, 1);
  make_number_button(grid, nummber_buttons, "5", 1, 3, 1, 1);
  make_number_button(grid, nummber_buttons, "6", 2, 3, 1, 1);
  make_number_button(grid, nummber_buttons, "7", 0, 2, 1, 1);
  make_number_button(grid, nummber_buttons, "8", 1, 2, 1, 1);
  make_number_button(grid, nummber_buttons, "9", 2, 2, 1, 1);

  make_operator_button(grid, operator_buttons, "=", 1, 5, 1, 1);
  make_operator_button(grid, operator_buttons, "C", 2, 5, 1, 1);
  make_operator_button(grid, operator_buttons, "+", 3, 2, 1, 1);
  make_operator_button(grid, operator_buttons, "-", 3, 3, 1, 1);
  make_operator_button(grid, operator_buttons, "*", 3, 4, 1, 1);
  make_operator_button(grid, operator_buttons, "/", 3, 5, 1, 1);

  gtk_widget_show(window);
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
