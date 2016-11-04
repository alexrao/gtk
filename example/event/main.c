#include <gtk/gtk.h>
#include "print.h"
#include <stdlib.h>
#include <stdio.h>


void frame_callback(GtkWindow *window, 
              GdkEvent *event, gpointer data)
{
   int x, y;
   char buf[10];
   x = event->configure.x;
   y = event->configure.y;
   sprintf(buf, "%d, %d", x, y);
   gtk_window_set_title(window, buf);
}


void enter_button(GtkWidget *widget, gpointer data)
{
    GdkColor color;
    srand(time(0));
    color.red = rand()/0x10000;
    color.green = rand()/0x100;
    color.blue = rand()/0x10000;
    gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &color);
}

int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *fixed;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
  gtk_window_set_title(GTK_WINDOW(window), "Simple");
  gtk_widget_add_events(GTK_WIDGET(window), GDK_CONFIGURE);

  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), fixed);

  button = gtk_button_new_with_label("Button");
  gtk_widget_set_size_request(button, 100, 50);
  gtk_fixed_put(GTK_FIXED(fixed), button, 100, 100);

  g_signal_connect(G_OBJECT(button), "enter",
          G_CALLBACK(enter_button), NULL);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",
                  G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  g_signal_connect(G_OBJECT(window), "configure-event",
                  G_CALLBACK(frame_callback), NULL);

  

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
