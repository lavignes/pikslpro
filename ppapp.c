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
 * Contains all information for a single instance of piksl to run.
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
  // Attach a watcher to track the window updates
  // this should catch resize events
  // TODO: Find better way to track resize events
  g_signal_connect(PP_APP->window, "size_allocate", G_CALLBACK(on_resize), NULL);
  
  GtkWidget* piksl = pp_piksl_new();
  
  gtk_container_add(GTK_CONTAINER(PP_APP->window), piksl);
  
  gtk_widget_show_all(PP_APP->window);
  
  GdkWindow* gdkwin = gtk_widget_get_window(PP_APP->window);
  GdkCursor* cursor = gdk_cursor_new_for_display(gdk_display_get_default(), GDK_PENCIL);
  gdk_window_set_cursor(gdkwin, cursor);
  
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
  
  // cleanup :3
  g_string_free(configpath, TRUE);
  g_key_file_free(configfile);
}

void pp_app_saveconfig() {

  // TODO: Write this... I'm lazy.
}

