// Sentinelle d'inclusion
#ifndef _unite1_h
#define _unite1_h

// Déclarations externes
#include "main.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_GIF_Image.H>

// Définition des constantes
#define X_ZONE  10      // X de la zone
#define Y_ZONE  10      // Y de la zone
#define L_ZONE  400     // Largeur de la zone
#define H_ZONE  400     // Hauteur de la zone

// Déclaration des objets de l'interface

extern Fl_Double_Window*   gFenetre ;
extern ZoneDessin*         gZoneDessin ;

extern Fl_Button*          gBoutonStartPause ;
extern Fl_Button*          gBoutonPasPas ;
extern Fl_Button*          gBoutonReset ;
extern Fl_Button*          gBoutonQuitter ;

extern Fl_Value_Slider*    gCurseurNatalite;
extern Fl_Value_Slider*    gCurseurMortalite;
extern Fl_Value_Slider*    gCurseurTpsTransition;
extern Fl_Value_Slider*    gCurseurMouton;
extern Fl_Value_Slider*    gCurseurLoup;

extern Fl_Value_Slider*    gCusrseurRapportLM;
extern Fl_GIF_Image *img_mouton;
extern Fl_GIF_Image *img_debut;
extern Fl_GIF_Image *img_loup;
extern Fl_Color vert ;


// Déclaration des sous-programmes
void CreerFenetre() ;

#endif // unite1_h

