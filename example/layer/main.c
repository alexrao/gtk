#include <gtk/gtk.h>
#include "print.h"


#if 0
void show_button(GtkWidget *window)
{
    GtkWidget *fixed = NULL;
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

// 竖着一排按钮
void show_vbox(GtkWidget *window)
{
    GtkWidget *vbox = NULL;
    GtkWidget *button1, *button2, *button3, *button4, *button5;

    vbox = gtk_box_new(TRUE, 2);
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
#endif

void show_table(GtkWidget *window)
{
    GtkWidget *table;
    GtkWidget *button;

    char *value[16] =
    {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "+",
        "0", ".", "=", "-",
    };

    table = gtk_table_new(4, 4, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 2);
    gtk_table_set_col_spacings(GTK_TABLE(table), 2);

    int i=0, j=0;
    int pos = 0;

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            button = gtk_button_new_with_label(value[4*i+j]);
            gtk_table_attach_defaults(GTK_TABLE(table), button, j, j+1, i, i+1);
        }
    }

    gtk_container_add(GTK_CONTAINER(window), table);

}

void show_align(GtkWidget *window)
{
    GtkWidget *ok, *close;
    GtkWidget *vbox, *hbox, *halign, *valign;

    vbox = gtk_vbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    hbox = gtk_hbox_new(TRUE, 3);

    ok = gtk_button_new_with_label("OK");
    close = gtk_button_new_with_label("Close");
    gtk_widget_set_size_request(ok, 170, 30);
    gtk_container_add(GTK_CONTAINER(hbox), ok);
    gtk_container_add(GTK_CONTAINER(hbox), close);

    halign = gtk_alignment_new(1, 1, 0, 0);
    gtk_container_add(GTK_CONTAINER(halign), hbox);

    gtk_box_pack_start(GTK_BOX(vbox), halign, FALSE, FALSE, 0);

}

int main(int argc, char **argv)
{
    GtkWidget *window = NULL;
    GtkWidget *button1, *button2, *button3;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 创建一个窗口
    gtk_window_set_title(GTK_WINDOW(window), "Layer"); // 设置窗口的标题
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 360); // 设置窗口的大小
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // 设置窗口的位置
    g_signal_connect_swapped(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);

    //show_button(window);
    //show_vbox(window);
    //show_table(window);
    show_align(window);

    gtk_widget_show_all(window);

    gtk_main(); // 主事件循环

    return 0;
}

