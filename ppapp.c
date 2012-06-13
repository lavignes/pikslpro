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

ppApp* PP_APP = NULL;

void pp_app_init(int argc, char* argv[]) {

  // Create appdata instance
  PP_APP = malloc(sizeof(ppApp));

  // Initialize gtk and create the main window
  gtk_init(&argc, &argv);
  PP_APP->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(PP_APP->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  
  
  
  
  gtk_widget_show(PP_APP->window);

  // Start gtk main thread
  gtk_main();
}

void pp_app_loadconfig() {

}
