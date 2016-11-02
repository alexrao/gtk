#include <gtk/gtk.h>
#include "print.h"


void show_button(GtkWidget *window, GtkWidget **fix)
{
    GtkWidget *fixed = *fix;
    GtkWidget *button1, *button2, *button3;

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    button1 = gtk_button_new_with_label("Button");
    gtk_fixed_put(GTK_FIXED(fixed), button1, 100, 50);
    gtk_widget_set_size_request(button1, 100, 50);

    button2 = gtk_button_new_with_label("Button");
    gtk_fixed_put(GTK_FIXED(fixed), button2, 100, 150);
    gtk_widget_set_size_request(button2, 100, 50);

    button3 = gtk_button_new_with_label("Button");
    gtk_fixed_put(GTK_FIXED(fixed), button3, 100, 250);
    gtk_widget_set_size_request(button3, 100, 50);

}

void show_vbox(GtkWidget *window, GtkWidget **box)
{
    GtkWidget *vbox = *box;
    GtkWidget *button1, *button2, *button3, *button4, *button5;

    vbox = gtk_box_new(TRUE, 1);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    button1 = gtk_button_new_with_label("Settings");
    button2 = gtk_button_new_with_label("Accoounts");
    button3 = gtk_button_new_with_label("Loans");
    button4 = gtk_button_new_with_label("Cash");
    button5 = gtk_button_new_with_label("Debts");

    gtk_box_pack_start(GTK_BOX(vbox), button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button4, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button5, TRUE, TRUE, 0);
}

int main(int argc, char **argv)
{
    GtkWidget *window = NULL;
    GtkWidget *fixed = NULL;
    GtkWidget *button1, *button2, *button3;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 创建一个窗口
    gtk_window_set_title(GTK_WINDOW(window), "Layer"); // 设置窗口的标题
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 360); // 设置窗口的大小
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // 设置窗口的位置

    //show_button(window, &fixed);
    show_vbox(window, &fixed);

    gtk_widget_show_all(window);

    g_signal_connect_swapped(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);

    gtk_main(); // 主事件循环

    return 0;
}

