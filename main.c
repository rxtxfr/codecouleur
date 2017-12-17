/*************************************************************************
  Copyright 2017 Antoine FLORENTIN

  This file is part of Code Couleur.

  Code Couleur is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Code Couleur is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Code Couleur.  If not, see <http://www.gnu.org/licenses/>.

*************************************************************************/



#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "callbacks.h"

GtkWidget *combo1 = NULL;
GtkWidget *combo2 = NULL;
GtkWidget *combo3 = NULL;
GtkWidget *combo4 = NULL;
GtkWidget *combo5 = NULL;

GtkWidget *win = NULL;
GtkWidget *hbox4 = NULL;
GtkWidget *hbox5 = NULL;
GtkWidget *vbox4 = NULL;
GtkWidget *vbox5 = NULL;
GtkWidget *output4 = NULL;
GtkWidget *output5 = NULL;

GtkWidget *comboValue;
GtkWidget *comboTolerance;
GtkWidget *notebook;
GtkWidget *tab4;
GtkWidget *tab5;
GtkWidget *resistor;
GtkWidget *E12Label;


int main (int argc, char *argv[])
{

    /* Initialize GTK+ */
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    gtk_init (&argc, &argv);
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    /* Create the main window */
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), "Code Couleur");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request( win, 400, 200);
    gtk_window_set_resizable(GTK_WINDOW (win), FALSE);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);


    vbox4 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 3);

    tab4 = gtk_label_new ("Calculateur");
    notebook = gtk_notebook_new ();
    gtk_notebook_insert_page (GTK_NOTEBOOK(notebook), GTK_WIDGET(vbox4), GTK_WIDGET(tab4), 0);

    
    gtk_container_add (GTK_CONTAINER (win), notebook);

    hbox4 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 3);
    gtk_container_add (GTK_CONTAINER (vbox4), hbox4);

    combo1 = fillValueCombo(combo1, SIGNIFICATIFS);
    gtk_box_pack_start (GTK_BOX (hbox4), combo1, TRUE, TRUE, 3);

    combo2 = fillValueCombo(combo2, SIGNIFICATIFS);
    gtk_box_pack_start (GTK_BOX (hbox4), combo2, TRUE, TRUE, 3);

    combo3 = fillValueCombo(combo3, MULTIPLICATEUR);
    gtk_box_pack_start (GTK_BOX (hbox4), combo3, TRUE, TRUE, 3);

    combo5 = fillToleranceCombo(combo5);
    gtk_box_pack_start (GTK_BOX (hbox4), combo5, TRUE, TRUE, 3);

    resistor = gtk_drawing_area_new ();
    gtk_box_pack_start (GTK_BOX (vbox4), resistor, TRUE, TRUE, 3);

    output4 = gtk_entry_new();
    gtk_entry_set_alignment ( (GtkEntry *)output4, 0.5);
    gtk_box_pack_start (GTK_BOX (vbox4), output4, TRUE, TRUE, 3);


    g_signal_connect (combo1, "changed", G_CALLBACK (valueSelected4Rings), NULL);
    g_signal_connect (combo2, "changed", G_CALLBACK (valueSelected4Rings), NULL);
    g_signal_connect (combo3, "changed", G_CALLBACK (valueSelected4Rings), NULL);
    g_signal_connect (combo5, "changed", G_CALLBACK (valueSelected4Rings), NULL);

    g_signal_connect (output4, "activate", G_CALLBACK (inputValue), NULL);
    g_signal_connect (notebook, "change-current-page", G_CALLBACK (redraw), NULL);
    g_signal_connect (G_OBJECT(resistor), "draw", G_CALLBACK (draw), NULL);
    g_signal_connect (G_OBJECT(resistor), "configure-event", G_CALLBACK (configure), NULL);



    vbox5 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 3);
    tab5 = gtk_label_new ("Valeurs courantes");
    gtk_notebook_insert_page (GTK_NOTEBOOK(notebook), GTK_WIDGET(vbox5), GTK_WIDGET(tab5), 1);

    E12Label = gtk_label_new ("Série E12 par multiples de 10 :\n\n100   120   150   180   220   270   330   390   470   560   680   820");
    gtk_box_pack_start (GTK_BOX (vbox5), E12Label, TRUE, TRUE, 3);

    /* Enter the main loop */
    gtk_widget_show_all (win);
    gtk_main ();
    return 0;
}
