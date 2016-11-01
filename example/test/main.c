#include <gtk/gtk.h>
void print_filename(GtkWidget *file)
{
    GtkWidget *dialog;
    gchar *filename;
    filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file));
    gtk_widget_destroy(file);
    dialog=gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,filename);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

GtkWidget *FileSelection;
void OpenFile(GtkWidget *widget,gpointer *data)
{
    printf("%s/n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(FileSelection)));
}

void button_event(GtkWidget *widget,gpointer *data)
{
    FileSelection=gtk_file_selection_new("选择文件");/*创建文件选择构件*/
    gtk_file_selection_set_filename(GTK_FILE_SELECTION(FileSelection), NULL);
    gtk_signal_connect(GTK_OBJECT(GTK_FILL_SELECTION(FileSelection)->ok_button),"clicked",GTK_SIGNAL_FUNC(OpenFile),NULL);/*捕捉打开按纽的"clicked"信号*/
    gtk_widget_show(FileSelection);
}

int main(int argc,char **argv)
{
    GtkWidget *win;
    GtkWidget *button;
    gtk_init(&argc,&argv);
    win=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win),"FileDialog");
    gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(win),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    button=gtk_button_new_with_label("Click Me");
    gtk_container_add(GTK_CONTAINER(win),button);
    //g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(select_file),NULL);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(button_event),NULL);
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}
