/**
 * @file ppapp.h
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

#ifndef PP_APP_H
#define PP_APP_H

#include <gtk/gtk.h>

typedef struct ppApp {

  GtkWidget* window;
  GtkWidget* toolbar;
  
  GList* projects;
  
  // Configurable members
  int win_width;
  int win_height;

} ppApp;

extern ppApp* PP_APP;

void pp_app_init(int argc, char* argv[]);

void pp_app_saveconfig();
void pp_app_loadconfig();

#endif /* PP_APP_H */
