#include <gtk/gtk.h>
#include "print.h"


GdkPixbuf *create_pixbuf(const gchar *filename)
{
    GdkPixbuf *pixbuf;
    GError *error = NULL;

    print("read picture[%s]", filename);
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if(!pixbuf)
    {
        print("%s", error->message);
    }

    return pixbuf;
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv); // GTK初始化

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 创建一个窗口

    gtk_window_set_title(GTK_WINDOW(window), "icon"); // 设置窗口的标题
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 360); // 设置窗口的大小
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // 设置窗口的位置

    gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("test.png")); // 设置标题栏的图标

    gtk_widget_show(window); // 显示所有控件

    g_signal_connect_swapped(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL); // 退出的回调(注销所有申请)

    gtk_main(); // 主事件循环

    return 0;
}

