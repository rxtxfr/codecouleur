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



#include <gdk/gdk.h>
#include <ctype.h>

#include "callbacks.h"


extern GtkWidget *combo1;
extern GtkWidget *combo2;
extern GtkWidget *combo3;
extern GtkWidget *combo4;
extern GtkWidget *combo5;
extern GtkWidget *output4;
extern GtkWidget *notebook;
extern GtkWidget *resistor;

GtkListStore *valueListStore;
GtkListStore *toleranceListStore;
GtkCellRenderer *column;

int valeur_unite = 0;
int valeur_dizaine = 0;
long valeur_multiple = 0;
int tolerance = 0;

char valeur[32];

cairo_surface_t *surface;

GtkWidget *fillValueCombo( GtkWidget *combo, int limit )
{

    valueListStore = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    gtk_list_store_insert_with_values(valueListStore, NULL, -1,
                                      0, "white",
                                      1, "black",
                                      2, "     -",
                                      -1);
    gtk_list_store_insert_with_values(valueListStore, NULL, -1,
                                      0, "black",
                                      1, "white",
                                      2, "Noir",
                                      -1);
    gtk_list_store_insert_with_values(valueListStore, NULL, -1,
                                      0, "brown",
                                      1, "white",
                                      2, "Marron",
                                      -1);
    gtk_list_store_insert_with_values(valueListStore, NULL, -1,
                                      0, "red",
                                      1, "black",
                                      2, "Rouge",
                                      -1);
    gtk_list_store_insert_with_values(valueListStore, NULL, -1,
                                      0, "orange",
                                      1, "black",
                                      2, "Orange",
                                      -1);
    gtk_list_store_insert_with_values(valueListStore, NULL, -1,
                                      0, "yellow",
                                      1, "black",
                                      2, "Jaune",
                                      -1);
    gtk_list_store_insert_with_values(valueListStore, NULL, -1,
                                      0, "green",
                                      1, "black",
                                      2, "Vert",
                                      -1);
    if( limit == SIGNIFICATIFS ){
    gtk_list_store_insert_with_values(valueListStore, NULL, -1,
                                      0, "blue",
                                      1, "white",
                                      2, "Bleu",
                                      -1);
    gtk_list_store_insert_with_values(valueListStore, NULL, -1,
                                      0, "purple",
                                      1, "white",
                                      2, "Violet",
                                      -1);
    gtk_list_store_insert_with_values(valueListStore, NULL, -1,
                                      0, "grey",
                                      1, "black",
                                      2, "Gris",
                                      -1);
    gtk_list_store_insert_with_values(valueListStore, NULL, -1,
                                      0, "white",
                                      1, "black",
                                      2, "Blanc",
                                      -1);
    }

    combo = gtk_combo_box_new_with_model(GTK_TREE_MODEL(valueListStore));

    
    g_object_unref(valueListStore);

    column = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), column, TRUE);


    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), column,
                                   "cell-background", 0,
                                   "foreground", 1,
                                   "text", 2,
                                   NULL);

    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);

    return combo;
}

GtkWidget *fillToleranceCombo( GtkWidget *combo )
{

    toleranceListStore = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    gtk_list_store_insert_with_values(toleranceListStore, NULL, -1,
                                      0, "white",
                                      1, "black",
                                      2, "     -",
                                      -1);

    gtk_list_store_insert_with_values(toleranceListStore, NULL, -1,
                                      0, "grey",
                                      1, "black",
                                      2, "Argent",
                                      -1);

    gtk_list_store_insert_with_values(toleranceListStore, NULL, -1,
                                      0, "yellow",
                                      1, "black",
                                      2, "Or",
                                      -1);


    gtk_list_store_insert_with_values(toleranceListStore, NULL, -1,
                                      0, "red",
                                      1, "black",
                                      2, "Rouge",
                                      -1);

    gtk_list_store_insert_with_values(toleranceListStore, NULL, -1,
                                      0, "brown",
                                      1, "white",
                                      2, "Marron",
                                      -1);
    
    gtk_list_store_insert_with_values(toleranceListStore, NULL, -1,
                                      0, "green",
                                      1, "black",
                                      2, "Vert",
                                      -1);

    gtk_list_store_insert_with_values(toleranceListStore, NULL, -1,
                                      0, "blue",
                                      1, "white",
                                      2, "Bleu",
                                      -1);

    gtk_list_store_insert_with_values(toleranceListStore, NULL, -1,
                                      0, "purple",
                                      1, "white",
                                      2, "Violet",
                                      -1);



    combo = gtk_combo_box_new_with_model(GTK_TREE_MODEL(toleranceListStore));

    
    g_object_unref(toleranceListStore);

    column = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), column, TRUE);


    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), column,
                                   "cell-background", 0,
                                   "foreground", 1,
                                   "text", 2,
                                   NULL);

    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);

    return combo;
}

void getDizaine(){

    valeur_dizaine = gtk_combo_box_get_active( (GtkComboBox *)combo1 );

    if( valeur_dizaine > 0 ) valeur_dizaine -=1;
    else valeur_dizaine = 0;

    sprintf(valeur, "%d", valeur_dizaine);

}

void getUnite(){

    valeur_unite = gtk_combo_box_get_active( (GtkComboBox *)combo2 );

    if( valeur_unite > 0 ) valeur_unite -=1;
    else valeur_unite = 0;

    if(valeur_dizaine > 0)
        sprintf(valeur, "%d", valeur_dizaine*10 + valeur_unite);
    else
        sprintf(valeur, "%d", valeur_unite);
}

void getMultiple(){

    valeur_multiple = gtk_combo_box_get_active( (GtkComboBox *)combo3 );

    if( valeur_multiple > 0 ) valeur_multiple -=1;

    valeur_multiple = pow( 10, valeur_multiple);

}

void getTolerance( char *str ){

    tolerance = gtk_combo_box_get_active( (GtkComboBox *)combo5 );

    switch(tolerance){

        case 1: sprintf(str, "%s", "10%"); break;
        case 2: sprintf(str, "%s", "5%"); break;
        case 3: sprintf(str, "%s", "2%"); break;
        case 4: sprintf(str, "%s", "1%"); break;
        case 5: sprintf(str, "%s", "0.5%"); break;
        case 6: sprintf(str, "%s", "0.25%"); break;
        case 7: sprintf(str, "%s", "0.1%"); break;

        default : sprintf(str, "%s", ""); break;
    }
}

void insertSpace( char *value ){

    int i = 0;
    char str[8];


    for(i=strlen(value); i>0; i--){


        if(i == (strlen(value)-7) ){

            strncpy(str, value+strlen(value)-7, 7);
            str[7] = '\0';
            value[strlen(value)-7] = ' ';
            strncpy(value+strlen(value)-6, str, 7);
        }

        if(i == (strlen(value)-3) ){

            strncpy(str, value+strlen(value)-3, 3);
            str[3] = '\0';
            value[strlen(value)-3] = ' ';
            strncpy(value+strlen(value)-2, str, 3);
        }
    }
}

void valueSelected4Rings( void ){

    char tol[8] = {""};
    long tmp = 0;

    memset(valeur, 0, 16);

    getDizaine();
    getUnite();
    getMultiple();

    tmp = ( valeur_dizaine*10 + valeur_unite) * valeur_multiple;

    sprintf(valeur, "%ld", tmp );

    insertSpace(valeur);

    getTolerance(tol);

    if(strlen(tol) > 1){
        strcat(valeur, " ");
        strcat(valeur, tol );
    }

    gtk_entry_set_text ((GtkEntry *)output4, valeur);

    ColorSelect( &valeur_dizaine, &valeur_unite, &valeur_multiple, &tolerance, &ColorRing1, &ColorRing2, &ColorRing3, &ColorRing4 );

    drawResistor( &ColorRing1, &ColorRing2, &ColorRing3, &ColorRing4 );
}

void redraw(){

    if( gtk_notebook_get_current_page (GTK_NOTEBOOK(notebook)) == 1 ){

        gtk_widget_set_visible(GTK_WIDGET(combo4), TRUE);
    }
}

gboolean draw (GtkWidget *widget, cairo_t *cr, gpointer data)
{
    cairo_set_source_surface (cr, surface, 0, 0);
    cairo_paint (cr);
    drawResistor( &ColorRing1, &ColorRing2, &ColorRing3, &ColorRing4 );
  return FALSE;
}

gboolean
configure (GtkWidget         *widget,
                    GdkEventConfigure *event,
                    gpointer           data)
{
    if (surface) cairo_surface_destroy (surface);

    surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
                                       CAIRO_CONTENT_COLOR,
                                       gtk_widget_get_allocated_width (widget),
                                       gtk_widget_get_allocated_height (widget));

    
    clear_surface ();

    
    return TRUE;
}

void
clear_surface (void)
{
    cairo_t *cr;

    cr = cairo_create (surface);

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);

    cairo_fill (cr);
    cairo_destroy (cr);
}

void drawResistor( Color *color1, Color *color2, Color *color3, Color *color4 ){

    cairo_t *cr;

    clear_surface();

    cr = cairo_create (surface);


    int width = gtk_widget_get_allocated_width (resistor);
    int height = gtk_widget_get_allocated_height (resistor);

    cairo_arc (cr, (double)3*width/7 - height/4 +2, (double)height/2, height/3, 50.0  * (M_PI/180.0), -50.0  * (M_PI/180.0));
    cairo_stroke (cr);

    cairo_arc (cr, (double)4*width/7 + height/4 -2, (double)height/2, height/3, -130.0  * (M_PI/180.0), 130.0  * (M_PI/180.0));
    cairo_stroke (cr);

    cairo_rectangle (cr, (double)6*width/14, (double)height/4, (double)height/5, (double)height/2);
    cairo_set_source_rgb (cr, color1->red, color1->green, color1->blue );
    cairo_fill_preserve (cr);

    if( valeur_dizaine == 9 ){
        cairo_set_source_rgb (cr, 0.0, 0.0, 0.0 );
    }
    cairo_stroke (cr);

    cairo_rectangle (cr, (double)7*width/15, (double)height/4, (double)height/5, (double)height/2);
    cairo_set_source_rgb (cr, color2->red, color2->green, color2->blue );
    cairo_fill_preserve (cr);

    if( valeur_unite == 9 ){
        cairo_set_source_rgb (cr, 0.0, 0.0, 0.0 );
    }
    cairo_stroke (cr);

    cairo_rectangle (cr, (double)7*width/14+2, (double)height/4, (double)height/5, (double)height/2);
    cairo_set_source_rgb (cr, color3->red, color3->green, color3->blue );
    cairo_fill(cr);

    cairo_rectangle (cr, (double)8*width/14 - height/4, (double)height/4, (double)height/5, (double)height/2);
    cairo_set_source_rgb (cr, color4->red, color4->green, color4->blue );
    cairo_fill(cr);


    cairo_set_source_rgb (cr, 0, 0, 0);

    cairo_move_to(cr, (double)3*width/7, (double)height/4);
    cairo_line_to (cr, (double)4*width/7, (double)height/4);

    cairo_move_to(cr, (double)3*width/7, (double)3*height/4);
    cairo_line_to (cr, (double)4*width/7, (double)3*height/4);

    cairo_move_to(cr, (double)3*width/7 - height/4 +2 -height/3, (double)height/2);
    cairo_line_to (cr, (double)width/4, (double)height/2);

    cairo_move_to(cr, (double)4*width/7 + height/4 -2 + height/3, (double)height/2);
    cairo_line_to (cr, (double)3*width/4, (double)height/2);

    cairo_set_line_width (cr, 2.0);
    cairo_stroke (cr);
    cairo_destroy (cr);

    gtk_widget_queue_draw_area (resistor,
                                0,
                                0,
                                width,
                                height);

}

void ColorSelect(   int *diz, int *unite, long *multiple, int *tolerance,
                    Color *color1, Color *color2, Color *color3, Color *color4 ){

    switch( *diz ){

        case 0 : color1->red = 0;   color1->green = 0;      color1->blue = 0;   break;

        case 1 : color1->red = 0.64; color1->green = 0.16;     color1->blue = 0.16;  break;

        case 2 : color1->red = 1.0; color1->green = 0;      color1->blue = 0;   break;

        case 3 : color1->red = 1.0; color1->green = 0.64;    color1->blue = 0;   break;

        case 4 : color1->red = 1.0; color1->green = 1.0;    color1->blue = 0;   break;

        case 5 : color1->red = 0;   color1->green = 0.5;    color1->blue = 0;   break;

        case 6 : color1->red = 0;   color1->green = 0;      color1->blue = 1.0; break;

        case 7 : color1->red = 0.5; color1->green = 0;      color1->blue = 0.5; break;

        case 8 : color1->red = 0.5; color1->green = 0.5;    color1->blue = 0.5; break;

        case 9 : color1->red = 1.0; color1->green = 1.0;    color1->blue = 1.0; break;


        default : color1->red = 0;   color1->green = 0;      color1->blue = 0;   break;

    }
    switch( *unite ){

        case 0 : color2->red = 0;   color2->green = 0;      color2->blue = 0;   break;

        case 1 : color2->red = 0.64; color2->green = 0.16;     color2->blue = 0.16;  break;

        case 2 : color2->red = 1.0; color2->green = 0;      color2->blue = 0;   break;

        case 3 : color2->red = 1.0; color2->green = 0.64;    color2->blue = 0;   break;

        case 4 : color2->red = 1.0; color2->green = 1.0;    color2->blue = 0;   break;

        case 5 : color2->red = 0;   color2->green = 0.5;    color2->blue = 0;   break;

        case 6 : color2->red = 0;   color2->green = 0;      color2->blue = 1.0; break;

        case 7 : color2->red = 0.5; color2->green = 0;      color2->blue = 0.5; break;

        case 8 : color2->red = 0.5; color2->green = 0.5;    color2->blue = 0.5; break;

        case 9 : color2->red = 1.0; color2->green = 1.0;    color2->blue = 1.0; break;


        default : color2->red = 0;   color2->green = 0;      color2->blue = 0;   break;

    }
    switch( *multiple ){

        case 1 : color3->red = 0;   color3->green = 0;      color3->blue = 0;   break;

        case 10 : color3->red = 0.64; color3->green = 0.16;     color3->blue = 0.16;  break;

        case 100 : color3->red = 1.0; color3->green = 0;      color3->blue = 0;   break;

        case 1000 : color3->red = 1.0; color3->green = 0.64;    color3->blue = 0;   break;

        case 10000 : color3->red = 1.0; color3->green = 1.0;    color3->blue = 0;   break;

        case 100000 : color3->red = 0;   color3->green = 0.5;    color3->blue = 0;   break;

        case 1000000 : color3->red = 0;   color3->green = 0;      color3->blue = 1.0; break;


        default : color3->red = 0;   color3->green = 0;      color3->blue = 0;   break;

    }
    switch( *tolerance ){

        case 1 : color4->red = 0.5; color4->green = 0.5;    color4->blue = 0.5; break;

        case 2 : color4->red = 1.0; color4->green = 1.0;    color4->blue = 0;   break;

        case 3 : color4->red = 1.0; color4->green = 0;      color4->blue = 0;   break;

        case 4 : color4->red = 0.64; color4->green = 0.16;     color4->blue = 0.16;  break;

        case 5 : color4->red = 0.0; color4->green = 0.5;    color4->blue = 0;   break;

        case 6 : color4->red = 0;   color4->green = 0;      color4->blue = 1.0; break;

        case 7 : color4->red = 0.5; color4->green = 0;      color4->blue = 0.5; break;


        default : color4->red = 0;   color4->green = 0;      color4->blue = 0;   break;

    }
}

void inputValue(){

    int i = 0;
    int zeros =0;
    int inputLength = 0;
    int space;
    int percent;
    char tol = 0;
    char input[32];
    char tmp[32];
    char *pourcent;
    char *espace;
    
    
    strcpy(input, gtk_entry_get_text( GTK_ENTRY(output4)) );
    inputLength = strlen(input);
    
    if( inputLength == 0 ){
        
        tmp[0] = 0;
        tmp[1] = 0;
        zeros = 0;
        tol = 0;
        
        strcpy( input, "0");
    }
    else {
        
        if( ( pourcent = strchr( input, '%') ) != 0 ){
            percent = pourcent - input+1;
            
            if( ( espace = strrchr( input, ' ') ) != 0 ){
                
                space = espace - input+1;
                
                inputLength -= (percent - space);

                if( strstr(input, "10%") != NULL ) tol = 1;
                if( strstr(input, "5%") != NULL ) tol = 2;
                if( strstr(input, "2%") != NULL ) tol = 3;
                if( strstr(input, "1%") != NULL ) tol = 4;
                if( strstr(input, "0.5%") != NULL ) tol = 5;
                if( strstr(input, "0.25%") != NULL ) tol = 6;
                if( strstr(input, "0.1%") != NULL ) tol = 7;

                if(tol > 0 && tol < 8)
                    gtk_combo_box_set_active( (GtkComboBox *)combo5, tol );
                
            }
        }

        for(i=0; i<inputLength; i++ ){
                    
            if( input[i] == 32 && i < inputLength ){

                    int n = 0;
                    for(n=i; n <inputLength-1; n++){

                        input[n] = input[n+1];

                    }
                    input[inputLength-1] = '\0';
            }
            
            if( input[i] >= 48 && input[i] <= 57 ){
                tmp[i] = input[i] - 48;

                if(i > 1 && tmp[i] == 0) zeros++;
            }
        }
    }
    
    switch(tol){

        case 1: strcat(input, " 10%"); break;
        case 2: strcat(input, " 5%"); break;
        case 3: strcat(input, " 2%"); break;
        case 4: strcat(input, " 1%"); break;
        case 5: strcat(input, " 0.5%"); break;
        case 6: strcat(input, " 0.25%"); break;
        case 7: strcat(input, " 0.1%"); break;

        default : strcat(input, ""); break;
    }

    gtk_combo_box_set_active( (GtkComboBox *)combo1, tmp[0]+1 );
    gtk_combo_box_set_active( (GtkComboBox *)combo2, tmp[1]+1 );
    gtk_combo_box_set_active( (GtkComboBox *)combo3, zeros+1 );

    gtk_entry_set_text( GTK_ENTRY(output4), input);
}
