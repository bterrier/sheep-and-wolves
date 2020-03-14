// Sentinelle d'inclusion
#ifndef _unite1_h
#define _unite1_h

// Déclarations externes
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_GIF_Image.H>

#include "drawarea.h"

// Définition des constantes
constexpr int X_ZONE = 10;      // X de la zone
constexpr int Y_ZONE = 10;      // Y de la zone
constexpr int L_ZONE = 400;     // Largeur de la zone
constexpr int H_ZONE = 400;     // Hauteur de la zone


class MainWindow : public Fl_Double_Window
{
public:

    MainWindow();


    ZoneDessin         *gZoneDessin ;

    Fl_Button          *gBoutonStartPause ;
    Fl_Button          *gBoutonPasPas ;
    Fl_Button          *gBoutonReset ;
    Fl_Button          *gBoutonQuitter ;

    Fl_Value_Slider    *gCurseurNatalite;
    Fl_Value_Slider    *gCurseurMortalite;
    Fl_Value_Slider    *gCurseurTpsTransition;
    Fl_Value_Slider    *gCurseurMouton;
    Fl_Value_Slider    *gCurseurLoup;

    Fl_Value_Slider    *gCusrseurRapportLM;
    Fl_GIF_Image *img_mouton;
    Fl_GIF_Image *img_debut;
    Fl_GIF_Image *img_loup;
    Fl_Color vert;
};
extern MainWindow *window;

#endif // unite1_h

