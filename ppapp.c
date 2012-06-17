/**
 * @file ppapp.c
 * @author  Scott LaVigne <scott.lavigne@linux.com>
 * @version 0.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Contains all information for a single instance of pikslpro to run.
 *
 */

#include <jemalloc/jemalloc.h>

#include "ppapp.h"

#include "widgets/pppiksl.h"

ppApp* PP_APP = NULL;

// watcher for window resizes
// It works.. :/
static void on_resize(GtkWidget* widget, gpointer data) {
  
  gtk_window_get_size(GTK_WINDOW(widget), &PP_APP->win_width,
                                          &PP_APP->win_height);
}

void pp_app_init(int argc, char* argv[]) {

  // Create appdata instance
  PP_APP = malloc(sizeof(ppApp));
  
  // Load config file
  pp_app_loadconfig();

  // Initialize gtk and create the main window
  gtk_init(&argc, &argv);
  PP_APP->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(PP_APP->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  
  gtk_window_set_default_size(GTK_WINDOW(PP_APP->window), PP_APP->win_width,
                                                          PP_APP->win_height);

  gtk_window_set_title(GTK_WINDOW(PP_APP->window), "PikslPro");
    
  // Attach a watcher to track the window updates
  // this should catch resize events
  // TODO: Find better way to track resize events
  g_signal_connect(PP_APP->window, "size_allocate", G_CALLBACK(on_resize), NULL);
  
  // Create the main widgets
  GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  
  GtkWidget* piksl = pp_piksl_new(800, 600);

  gtk_widget_set_halign(piksl, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(piksl, GTK_ALIGN_CENTER);
  gtk_widget_set_margin_top(piksl, PP_APP->canvas_padding);
  gtk_widget_set_margin_bottom(piksl, PP_APP->canvas_padding);
  gtk_widget_set_margin_left(piksl, PP_APP->canvas_padding);
  gtk_widget_set_margin_right(piksl, PP_APP->canvas_padding);
  
  GtkWidget* scroller = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroller), piksl);
  
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroller),  GTK_POLICY_ALWAYS,  GTK_POLICY_ALWAYS);

  PP_APP->toolbar = gtk_toolbar_new();
  // Set toolbar to primary-toolbar style
  // This fixes the gradient!!
  gtk_style_context_add_class(gtk_widget_get_style_context(PP_APP->toolbar),
                              "primary-toolbar");

  gtk_toolbar_insert(GTK_TOOLBAR(PP_APP->toolbar), gtk_tool_button_new_from_stock(GTK_STOCK_NEW), -1);
  gtk_toolbar_insert(GTK_TOOLBAR(PP_APP->toolbar), gtk_tool_button_new_from_stock(GTK_STOCK_OPEN), -1);
  gtk_toolbar_insert(GTK_TOOLBAR(PP_APP->toolbar), gtk_tool_button_new_from_stock(GTK_STOCK_SAVE), -1);
  gtk_toolbar_insert(GTK_TOOLBAR(PP_APP->toolbar), gtk_separator_tool_item_new(), -1);

  // Add padding to toolbar
  GtkToolItem* spacer = gtk_separator_tool_item_new();
  gtk_separator_tool_item_set_draw(GTK_SEPARATOR_TOOL_ITEM(spacer), FALSE);
  gtk_tool_item_set_expand(spacer, TRUE);
  gtk_toolbar_insert(GTK_TOOLBAR(PP_APP->toolbar), spacer, -1);
  
  gtk_toolbar_insert(GTK_TOOLBAR(PP_APP->toolbar), gtk_tool_button_new_from_stock(GTK_STOCK_PROPERTIES), -1);

  gtk_box_pack_start(GTK_BOX(vbox), PP_APP->toolbar, FALSE, FALSE, 0);

  GtkWidget* pane = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_end(GTK_BOX(vbox), pane, TRUE, TRUE, 0);
  
  GtkListStore* color_list = gtk_list_store_new(2, GDK_TYPE_PIXBUF, G_TYPE_UINT);
  GtkWidget* view = gtk_icon_view_new_with_model(GTK_TREE_MODEL(color_list));
  gtk_icon_view_set_columns(GTK_ICON_VIEW(view), 5);
  gtk_icon_view_set_column_spacing(GTK_ICON_VIEW(view), 0);
  gtk_icon_view_set_item_padding(GTK_ICON_VIEW(view), 4);
  gtk_icon_view_set_reorderable(GTK_ICON_VIEW(view), TRUE);
  gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(view), 0);
  
  GtkTreeIter iter;
  
  GdkPixbuf* p = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 24, 24);
  gdk_pixbuf_fill(p, 0x009900FF);
  gtk_list_store_insert_with_values(GTK_LIST_STORE(color_list), &iter, -1,
                                    0, p,
                                    1, 0x00FF00FF,
                                    -1);
                                    
  p = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 24, 24);
  gdk_pixbuf_fill(p, 0xFF0000FF);
  gtk_list_store_insert_with_values(GTK_LIST_STORE(color_list), &iter, -1,
                                    0, p,
                                    1, 0x00FF00FF,
                                    -1);

  p = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 24, 24);
  gdk_pixbuf_fill(p, 0x0000FFFF);
  gtk_list_store_insert_with_values(GTK_LIST_STORE(color_list), &iter, -1,
                                    0, p,
                                    1, 0x00FF00FF,
                                    -1);
                                    
  gtk_list_store_insert_with_values(GTK_LIST_STORE(color_list), &iter, -1,
                                    0, p,
                                    1, 0x00FF00FF,
                                    -1);
                                    
                                      gtk_list_store_insert_with_values(GTK_LIST_STORE(color_list), &iter, -1,
                                    0, p,
                                    1, 0x00FF00FF,
                                    -1);
                                    
                                      gtk_list_store_insert_with_values(GTK_LIST_STORE(color_list), &iter, -1,
                                    0, p,
                                    1, 0x00FF00FF,
                                    -1);
                                    
                                      gtk_list_store_insert_with_values(GTK_LIST_STORE(color_list), &iter, -1,
                                    0, p,
                                    1, 0x00FF00FF,
                                    -1);

  gtk_paned_add1(GTK_PANED(pane), view);
  gtk_paned_add2(GTK_PANED(pane), scroller);
  
  gtk_container_add(GTK_CONTAINER(PP_APP->window), vbox);

  gtk_widget_show_all(PP_APP->window);

  GdkWindow* gdkwin = gtk_widget_get_window(GTK_WIDGET(piksl));
  GdkCursor* cursor = gdk_cursor_new_for_display(gdk_display_get_default(), GDK_PENCIL);
  gdk_window_set_cursor(gdkwin, cursor);

  PP_APP->color1 = 0xFF000000;
  
  // Start gtk main thread
  gtk_main();
}

void pp_app_loadconfig() {

  // Get the user's config directory
  GString* configpath = g_string_new(g_get_user_config_dir());
  g_string_append(configpath, "/pikslpro");
  
  printf("Loading configuration: %s/config\n", configpath->str);
  
  // Check if the config folder exists
  if (g_file_test(configpath->str, G_FILE_TEST_IS_DIR) == FALSE) {
  
    printf("Configuration folder doesn't exist!\n"
           "Creating a new one...\n");
  
    // Create the config folder
    g_mkdir_with_parents(configpath->str, 0770);
  }
  
  // Check for the config file
  g_string_append(configpath, "/config");
  if (g_file_test(configpath->str, G_FILE_TEST_EXISTS) == FALSE) {
  
    printf("Configuration file doesn't exist!\n"
           "Creating a new one...\n");
           
    // Copy the default config from the data directory
    gchar* filedata;
    g_file_get_contents("data/default-config", &filedata, NULL, NULL);
    g_file_set_contents(configpath->str, filedata, -1, NULL);
    g_free(filedata);
  }
  
  // Parse the config
  GKeyFile* configfile = g_key_file_new();
  g_key_file_load_from_file(configfile, configpath->str, G_KEY_FILE_NONE, NULL);
  
  PP_APP->win_width =
    g_key_file_get_integer(configfile, "pikslpro", "win_width", NULL);

  PP_APP->win_height =
    g_key_file_get_integer(configfile, "pikslpro", "win_height", NULL);

  PP_APP->canvas_padding =
    g_key_file_get_integer(configfile, "pikslpro", "canvas_padding", NULL);
  
  // cleanup :3
  g_string_free(configpath, TRUE);
  g_key_file_free(configfile);
}

void pp_app_saveconfig() {

  // TODO: Write this... I'm lazy.
}

