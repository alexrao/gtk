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

void show_text(GtkWidget *widget, gpointer label)
{
    static int count = 0;
    count++;
    print("Open Click:%d", count);
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
    GtkWidget *window = NULL;
    GtkWidget *box = NULL;
    GtkWidget *menubar = NULL;
    GtkWidget *filemenu = NULL;
    GtkWidget *file, *open;
    GtkWidget *quit = NULL;

    gtk_init(&argc, &argv); // GTK初始化

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 创建一个窗口
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 360); // 设置窗口的大小
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // 设置窗口的位置
    gtk_window_set_title(GTK_WINDOW(window), "icon"); // 设置窗口的标题
    gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("test.png")); // 设置标题栏的图标

    box = gtk_vbox_new(FALSE, 0);
    //box = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), box);

    menubar = gtk_menu_bar_new();
    filemenu = gtk_menu_new();

    file = gtk_menu_item_new_with_label("File");
    open = gtk_menu_item_new_with_label("Open");
    quit = gtk_menu_item_new_with_label("Quit");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);

    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 3);


    g_signal_connect(G_OBJECT(open), "activate",
            G_CALLBACK(show_text), NULL); // 退出的回调(注销所有申请)

    g_signal_connect(G_OBJECT(quit), "activate",
            G_CALLBACK(gtk_main_quit), NULL); // 退出的回调(注销所有申请)

    g_signal_connect(window, "destroy",
            G_CALLBACK(gtk_main_quit), NULL); // 退出的回调(注销所有申请)

    gtk_widget_show_all(window); // 显示所有控件

    gtk_main(); // 主事件循环

    return 0;
}
