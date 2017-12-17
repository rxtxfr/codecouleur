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


#ifndef CALLBACKS_H_INCLUDED
#define CALLBACKS_H_INCLUDED


#define SIGNIFICATIFS   10
#define MULTIPLICATEUR  8

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

typedef struct {

    double red;
    double green;
    double blue;
}Color;

Color ColorRing1;
Color ColorRing2;
Color ColorRing3;
Color ColorRing4;

GtkWidget *fillValueCombo( GtkWidget *combo, int limit );

GtkWidget *fillToleranceCombo( GtkWidget *combo );

void getDizaine();

void getUnite();

void getMultiple();

void getTolerance( char *str );

void insertSpace( char *value );

void valueSelected4Rings( void );

void redraw();

gboolean draw (GtkWidget *widget, cairo_t *cr, gpointer data);

gboolean configure (GtkWidget *widget, GdkEventConfigure *event, gpointer data);

void clear_surface (void);

void drawResistor( Color *color1, Color *color2, Color *color3, Color *color4 );

void ColorSelect(   int *dizaine, int *unite, long *multiple, int *tolerance,
                    Color *color1, Color *color2, Color *color3, Color *color4 );

void inputValue();

#endif // CALLBACKS_H_INCLUDED
