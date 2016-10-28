#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 创建顶层窗口

    // 创建按钮
    GtkWidget *button = gtk_button_new_with_label("Button GTK+");

    // 显示按钮
    gtk_widget_show(button);

    gtk_widget_show(window); // 显示窗口

    gtk_main(); // 主循环

    return 0;
}
