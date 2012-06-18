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
 
#include <string.h>

#include <jemalloc/jemalloc.h>

#include "ppapp.h"
#include "pputil.h"
#include "widgets/pppiksl.h"

ppApp* PP_APP = NULL;

// watcher for window resizes
// It works.. :/
static void on_resize(GtkWidget* widget, gpointer data) {
  
  gtk_window_get_size(GTK_WINDOW(widget), &PP_APP->win_width,
                                          &PP_APP->win_height);
}

static gboolean on_click(GtkWidget* widget, GdkEventButton* event) {

  GtkIconView* view = GTK_ICON_VIEW(widget);
  //GdkEventButton* button_event = GDK_EVENT_BUTTON(event);
  GtkTreePath* path = gtk_icon_view_get_path_at_pos(view,
                                                    event->x,
                                                    event->y);
                                                    
  if (path != NULL) {

    GtkTreeIter iter;
    gtk_tree_model_get_iter(gtk_icon_view_get_model(view), &iter, path);
    
    guint color;
    gtk_tree_model_get(gtk_icon_view_get_model(view), &iter, 1, &color, -1);
    
    pp_app_set_color(color);
  }
  
  return FALSE;
}

static void on_color(GtkRange* range, gpointer data) {

  if (!strcmp((gchar*)data, "red")) {

    pp_app_set_red((guint)gtk_range_get_value(range));
  
  } else if (!strcmp((gchar*)data, "green")) {

    pp_app_set_green((guint)gtk_range_get_value(range));
    
  } else if (!strcmp((gchar*)data, "blue")) {

    pp_app_set_blue((guint)gtk_range_get_value(range));
  
  } else if (!strcmp((gchar*)data, "alpha")) {

    pp_app_set_alpha((guint)gtk_range_get_value(range));
  }
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
                              GTK_STYLE_CLASS_PRIMARY_TOOLBAR);

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
  
  PP_APP->color_list = gtk_list_store_new(2, GDK_TYPE_PIXBUF, G_TYPE_UINT);
  GtkWidget* view = gtk_icon_view_new_with_model(GTK_TREE_MODEL(PP_APP->color_list));
  gtk_icon_view_set_columns(GTK_ICON_VIEW(view), 5);
  gtk_icon_view_set_column_spacing(GTK_ICON_VIEW(view), 0);
  gtk_icon_view_set_item_padding(GTK_ICON_VIEW(view), 2);
  gtk_icon_view_set_reorderable(GTK_ICON_VIEW(view), TRUE);
  gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(view), 0);
  gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(view), GTK_SELECTION_NONE);
  g_signal_connect(view, "button-press-event", G_CALLBACK(on_click), NULL);
                                       
  pp_app_add_color(0xFF000000);
  pp_app_add_color(0xFFFFFFFF);
  pp_app_add_color(0xFFFF0000);
  pp_app_add_color(0xFF00FF00);
  pp_app_add_color(0xFF0000FF);
  pp_app_add_color(0xFFFFFF00);
  pp_app_add_color(0xFFFF00FF);
  pp_app_add_color(0xFF00FFFF);
  
  GtkWidget* toolbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  
  gtk_box_pack_start(GTK_BOX(toolbox), view, FALSE, FALSE, 0);

  PP_APP->red_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
                                               0,
                                               255,
                                               1);
  gtk_scale_set_draw_value(GTK_SCALE(PP_APP->red_scale), FALSE);
  g_signal_connect(PP_APP->red_scale, "value-changed", G_CALLBACK(on_color), "red");
                                            
  PP_APP->green_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
                                                 0,
                                                 255,
                                                 1);
  gtk_scale_set_draw_value(GTK_SCALE(PP_APP->green_scale), FALSE);
  g_signal_connect(PP_APP->green_scale, "value-changed", G_CALLBACK(on_color), "green");
                                          
  PP_APP->blue_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
                                                0,
                                                255,
                                                1);
  gtk_scale_set_draw_value(GTK_SCALE(PP_APP->blue_scale), FALSE);
  g_signal_connect(PP_APP->blue_scale, "value-changed", G_CALLBACK(on_color), "blue");
  
  PP_APP->alpha_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
                                                 0,
                                                 255,
                                                 1);
  gtk_scale_set_draw_value(GTK_SCALE(PP_APP->alpha_scale), FALSE);
  g_signal_connect(PP_APP->alpha_scale, "value-changed", G_CALLBACK(on_color), "alpha");
                                             
  gtk_box_pack_start(GTK_BOX(toolbox), PP_APP->red_scale, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(toolbox), PP_APP->green_scale, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(toolbox), PP_APP->blue_scale, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(toolbox), PP_APP->alpha_scale, FALSE, FALSE, 0);

  gtk_paned_add1(GTK_PANED(pane), toolbox);
  gtk_paned_add2(GTK_PANED(pane), scroller);
  
  gtk_container_add(GTK_CONTAINER(PP_APP->window), vbox);

  gtk_widget_show_all(PP_APP->window);

  GdkWindow* gdkwin = gtk_widget_get_window(GTK_WIDGET(piksl));
  GdkCursor* cursor = gdk_cursor_new_for_display(gdk_display_get_default(), GDK_PENCIL);
  gdk_window_set_cursor(gdkwin, cursor);

  pp_app_set_color(0xFF000000);
  
  // Start gtk main thread
  gtk_main();
}

void pp_app_add_color(guint color) {

  GtkTreeIter iter;
  guint c;
  
  // Make sure there are no duplicates
  // Iterate through liststore to prevent color dplicates
  if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(PP_APP->color_list), &iter)) {
    do {
      gtk_tree_model_get(GTK_TREE_MODEL(PP_APP->color_list), &iter, 1, &c, -1);
      
      if (c == color)
        return;
    } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(PP_APP->color_list), &iter));
  }

  GdkPixbuf* p = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 24, 24);
  pp_color_pixbuf(p, color);
 
  gtk_list_store_insert_with_values(GTK_LIST_STORE(PP_APP->color_list), &iter, -1,
                                  0, p,
                                  1, color,
                                  -1);
}

void pp_app_set_color(guint color) {

  PP_APP->color1 = color;
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

