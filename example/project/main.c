#include <gtk/gtk.h>
#include <string.h>
#include "print.h"

#if 0
char buf[64] = {0};

#define KEY_BACKSPACE "c"

int cal_num(GtkButton *button, gpointer data)
{
    const char *str = gtk_button_get_label(button); // get string of button

    // backspace
    if(0 == strcmp(str, KEY_BACKSPACE))
    {
        buf[strlen(buf) - 1] = 0;
    }
    else
    {
        int a, b;
        char c;

        strcat(buf, str);

        if(0 == strcmp("=", str))
        {
            sscanf(buf, "%d%c%d", &a, &c, &b);

            print("a = %d, c=%c, b=%d", a, c, b);

            if('+' == c)
            {
                snprintf(buf, sizeof(buf), "%d", a+b);
            }
            else if('-' == c)
            {
                snprintf(buf, sizeof(buf), "%d", a-b);
            }
            else if('*' == c)
            {
                snprintf(buf, sizeof(buf), "%d", a*b);
            }
            else if('/' == c)
            {
                snprintf(buf, sizeof(buf), "%d", a/b);
            }

            print("buf[%s]", buf);
        }
    }

    gtk_entry_set_text(GTK_ENTRY(data), buf);
}
#else
int get_song_list(GtkWidget *widget, gpointer window)
{
    print("");
}

void print_filename(GtkWidget *file)
{
    GtkWidget *dialog;
    gchar *filename;
    filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file));
    gtk_widget_destroy(file);
    dialog = gtk_message_dialog_new (NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,filename);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void select_file(GtkWidget *widget,gpointer data)
{
    GtkWidget *file;
    int file_return;
    file=gtk_file_chooser_dialog_new("SelectFile",NULL,GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,GTK_STOCK_OK,GTK_RESPONSE_ACCEPT,NULL);
    if(gtk_dialog_run(GTK_DIALOG(file))==GTK_RESPONSE_ACCEPT)
    {
        print_filename(file);
    }
    else
    {
        gtk_widget_destroy(file);
    }
}
#endif

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 创建顶层窗口

    gtk_window_set_title(GTK_WINDOW(window), "获取当前歌单列表");
    gtk_widget_set_size_request(window, 300, 200);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    gtk_container_set_border_width(GTK_CONTAINER(window), 50);


    // 创建按钮
    GtkWidget *button = gtk_button_new_with_label("生成song.txt");
    gtk_widget_set_tooltip_text(button, "This is a Button"); // 鼠标放到按键上的时候显示的提示信息


    g_signal_connect(button, "clicked", G_CALLBACK(get_song_list), NULL);


    gtk_container_add(GTK_CONTAINER(window), button);


    // 显示按钮
    gtk_widget_show(button);

    gtk_widget_show(window); // 显示窗口

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);


    gtk_main(); // 主循环

    return 0;
}

