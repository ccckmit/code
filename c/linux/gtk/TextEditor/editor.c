#include <gtk/gtk.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "fileselect.c"
#include "menu.c"


/*gcc editor.c -Wall -ansi -o Editor `pkg-config --cflags --libs gtk+-2.0` */

GtkWidget *view; /* text view widget where all the typing is done */

/* Gtk - display error message */
static void err_msg(const gchar *msg)
{
    GtkWidget *dialog; /* pop up window with only OK button */

    dialog = gtk_message_dialog_new(GTK_WINDOW(window), 0, GTK_MESSAGE_ERROR,
				    GTK_BUTTONS_OK, msg);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog); /* destroy the window after ok is pressed */
}


/* when the user clicks on quit button or quits the app fire the delete event 
                              signal but first check if the file is modified or not*/

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    return !save_if_modified();
}


/* main function */


int main(int argc, char *argv[])
{
    GtkWidget *box, *scroll, *widget;
   
    GtkAccelGroup *accel;
      
    gtk_init(&argc, &argv);  /* gtk initializer can take filename as an argument*/

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /* if the user quits the app */  
    g_signal_connect(G_OBJECT(window), "delete_event",G_CALLBACK(delete_event), window);
    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
  


    gtk_window_set_title(GTK_WINDOW(window), "Text Editor (Insert file name)");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 500); /* window size y & x values */
    
    box = gtk_vbox_new(FALSE, 0); /* create a container where the menus n text widget goes */
    /* false if u dont want extra padding in the box, 0 for spacing */

    /* add the box wid in the window */
    gtk_container_add(GTK_CONTAINER(window), box);
    
    /* create an accerelator for the item factory, keyboard shortcuts */
    accel = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(window), accel);
    

    /* Create a menu above the text view widget */
    main_menu = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<TextView>", accel);
    gtk_item_factory_create_items(main_menu,sizeof(menu_def) / sizeof(*menu_def),menu_def, NULL);
    

    /* Return the actual menu bar created by the item factory. */
    widget = gtk_item_factory_get_widget(main_menu, "<TextView>");

    /* put the menu in the menu container */
    gtk_box_pack_start(GTK_BOX(box), widget, FALSE, FALSE, 0);
    
    scroll = gtk_scrolled_window_new(NULL, NULL); /* put a scroll window widget */

    /* put the scroll window in the text container */
    gtk_box_pack_start(GTK_BOX(box), scroll, TRUE, TRUE, 0);
  
    /* create the text view widget */
    view = gtk_text_view_new();

    /* create a buffer for the text view where everything gets stored */
    buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    /* put the text widget in the scroll window */
    gtk_container_add(GTK_CONTAINER(scroll), view);

    
    gtk_widget_show_all(window); /* show all widgets in the window */

    /* error checking */
    g_set_printerr_handler(err_msg);

    /* load the file if a filename is specified */
    if(argc > 1)
	load_file(g_strdup(argv[1]));

    /* the main loop where the app waits for mouse n keyboard events */
    gtk_main();

    return 0;
}
