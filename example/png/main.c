#include <gtk/gtk.h>
#include "print.h"

int g_count = 0;
char g_buf[64] = {0};


/**
 * @Brief    create_pixbuf
 *
 * @Param    filename
 *
 * @Returns
 *
 * 图片数据读取函数
 */
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


/**
 * @Brief    increase
 *
 * @Param    widget
 * @Param    label
 *
 * 数据增加并显示文本
 */
void increase(GtkWidget *widget, gpointer label)
{
    g_count++;
    snprintf(g_buf, sizeof(g_buf), "%d", g_count);
    gtk_label_set_text(label, g_buf);
}


/**
 * @Brief    decrease
 *
 * @Param    widget
 * @Param    label
 *
 * 数据减少并显示文本
 */
void decrease(GtkWidget *widget, gpointer label)
{
    g_count--;
    snprintf(g_buf, sizeof(g_buf), "%d", g_count);
    gtk_label_set_text(label, g_buf);
}


/**
 * @Brief    main
 *
 * @Param    argc
 * @Param    argv
 *
 * @Returns
 *
 * 主函数
 */
int main(int argc, char **argv)
{
    GtkWidget *frame;
    GtkWidget *label;
    GtkWidget *add, *sub;
    GtkWidget *window = NULL;

    gtk_init(&argc, &argv); // GTK初始化


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 创建一个窗口
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 360); // 设置窗口的大小
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // 设置窗口的位置
    gtk_window_set_title(GTK_WINDOW(window), "icon"); // 设置窗口的标题
    gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("test.png")); // 设置标题栏的图标

    frame = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), frame);

    add = gtk_button_new_with_label("+");
    gtk_widget_set_size_request(add, 100, 50);
    gtk_fixed_put(GTK_FIXED(frame), add, 50, 50);

    sub = gtk_button_new_with_label("-");
    gtk_widget_set_size_request(sub, 100, 50);
    gtk_fixed_put(GTK_FIXED(frame), sub, 50, 200);

    label = gtk_label_new("0");
    gtk_fixed_put(GTK_FIXED(frame), label, 100, 150);

    gtk_widget_show_all(window); // 显示所有控件

    g_signal_connect(window, "destroy",
            G_CALLBACK(gtk_main_quit), NULL); // 退出的回调(注销所有申请)

    g_signal_connect(add, "clicked",
            G_CALLBACK(increase), label);

    g_signal_connect(sub, "clicked",
            G_CALLBACK(decrease), label);

    gtk_main(); // 主事件循环

    return 0;
}

