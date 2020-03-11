// Déclarations externes
#include "unite1.h"

#include <FL/Fl_GIF_Image.H>

#include "unite2.h"
#include "unite3.h"

// Définition des objets de l'interface
Fl_Double_Window   *gFenetre ;
ZoneDessin         *gZoneDessin ;
Fl_Button          *gBoutonStartPause;
Fl_Button          *gBoutonPasPas;
Fl_Button          *gBoutonReset;
Fl_Button          *gBoutonQuitter ;

Fl_Value_Slider    *gCurseurNatalite;
Fl_Value_Slider    *gCurseurMortalite;
Fl_Value_Slider    *gCurseurTpsTransition;
Fl_Value_Slider    *gCurseurMouton;
Fl_Value_Slider    *gCurseurLoup;

Fl_Value_Slider    *gCusrseurRapportLM;

// Définition des images

Fl_GIF_Image *img_mouton = nullptr; //("mouton.gif");
Fl_GIF_Image *img_debut = nullptr;   //("debut.gif");
Fl_GIF_Image *img_loup = nullptr;   //("loup.gif");

Fl_Color vert = fl_rgb_color(87, 153, 40);

// CréerFenetre
void CreerFenetre()
{
    {

        // Création de la fenêtre principale
        gFenetre = new Fl_Double_Window(560, 480);                                          // Dimensionnement de la fenêtre principale
        gFenetre->label("Projet Loups et Moutons") ;                                        // Nom du programme
        gFenetre->begin() ;

        // Création de la zone de dessin
        gZoneDessin = new ZoneDessin(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);
        gZoneDessin->draw_callback(ZoneDessinDessinerCB, NULL) ;

        img_mouton = new Fl_GIF_Image("mouton.gif");
        img_debut = new Fl_GIF_Image("debut.gif");
        img_loup = new Fl_GIF_Image("loup.gif");

    }

    {

        // Création du bouton Start/Pause
        gBoutonStartPause = new Fl_Button(440, 10, 100, 30, "Start/Pause") ;                // Positionnement et affichage du nom du bouton
        gBoutonStartPause->callback(BoutonStartPauseCB, NULL) ;                             // Lien avec la programmation
        gBoutonStartPause->box(FL_PLASTIC_UP_BOX);                                          // Type du bouton

        // Création du bouton Pas à pas
        gBoutonPasPas = new Fl_Button(440, 50, 100, 30, "Pas a Pas") ;
        gBoutonPasPas->callback(BoutonPasPasCB, NULL) ;
        gBoutonPasPas->box(FL_PLASTIC_UP_BOX);

        // Création du bouton Reset
        gBoutonReset = new Fl_Button(440, 90, 100, 30, "Reset") ;
        gBoutonReset->callback(BoutonResetCB, NULL) ;
        gBoutonReset->box(FL_ROUND_UP_BOX);

        // Création du bouton Quitter
        gBoutonQuitter = new Fl_Button(440, 440, 100, 30, "Quitter") ;
        gBoutonQuitter->callback(BoutonQuitterCB, NULL) ;
        gBoutonQuitter->box(FL_OSHADOW_BOX);

    }

    {

        // Création du curseur Natalité
        gCurseurNatalite = new Fl_Value_Slider(440, 160, 100, 25, "Natalite") ;             // Positionnement et affichage du nom du curseur natalité
        gCurseurNatalite->type(FL_HOR_NICE_SLIDER) ;                                        // Type de curseur
        gCurseurNatalite->align(FL_ALIGN_TOP) ;                                             // Alignement au milieu et en haut du nom du curseur (par rapport au curseur)
        gCurseurNatalite->callback(CurseurNataliteCB, NULL) ;                               // Lien avec la programmation
        gCurseurNatalite->bounds(0, 1);                                                     // Borne du curseur
        gCurseurNatalite->precision(2);                                                     // Précision du curseur en nombre de décimale
        gCurseurNatalite->value(gNataliteMouton);                                           // Lien avec la programmation

        // Création du curseur Mortalité
        gCurseurMortalite = new Fl_Value_Slider(440, 215, 100, 25, "Mortalite") ;
        gCurseurMortalite->type(FL_HOR_NICE_SLIDER) ;
        gCurseurMortalite->align(FL_ALIGN_TOP) ;
        gCurseurMortalite->callback(CurseurMortaliteCB, NULL) ;
        gCurseurMortalite->bounds(0, 1);
        gCurseurMortalite->precision(2);
        gCurseurMortalite->value(gMortaliteLoup);

        //Création du curseur mouton
        gCurseurMouton = new Fl_Value_Slider(30, 440, 150, 25, "Nombre Moutons Initial") ;
        gCurseurMouton->type(FL_HOR_NICE_SLIDER) ;
        gCurseurMouton->align(FL_ALIGN_TOP) ;
        gCurseurMouton->callback(CurseurMoutonCB, NULL) ;
        gCurseurMouton->bounds(1, 20000);
        gCurseurMouton->value(gNB_MOUTONS_INITIAUX);
        gCurseurMouton->precision(0);                                                   // Précision de la décimale (0 = entier)

        //Création du curseur loup
        gCurseurLoup = new Fl_Value_Slider(240, 440, 150, 25, "Nombre Loups Initial") ;
        gCurseurLoup->type(FL_HOR_NICE_SLIDER) ;
        gCurseurLoup->align(FL_ALIGN_TOP) ;
        gCurseurLoup->callback(CurseurLoupCB, NULL) ;
        gCurseurLoup->bounds(1, 20000);
        gCurseurLoup->value(gNB_LOUPS_INITIAUX);
        gCurseurLoup->precision(0);

        // Création du curseur Temps de transition
        gCurseurTpsTransition = new Fl_Value_Slider(440, 270, 100, 25, "Tps de transition") ;
        gCurseurTpsTransition->type(FL_HOR_NICE_SLIDER) ;
        gCurseurTpsTransition->align(FL_ALIGN_TOP) ;
        gCurseurTpsTransition->callback(CurseurTpsTransitionCB, NULL) ;
        gCurseurTpsTransition->bounds(0.01, 2);
        gCurseurTpsTransition->precision(2);
        gCurseurTpsTransition->value(gTpsTransition);

    }

    // Création d'une fenêtre pour afficher le rapport loup sur mouton
    gCusrseurRapportLM = new Fl_Value_Slider(470, 325, 40, 100, "Loups/Moutons") ;
    gCusrseurRapportLM->type(FL_VERT_FILL_SLIDER);
    gCusrseurRapportLM->color(FL_WHITE);
    gCusrseurRapportLM->color2(FL_BLACK);
    gCusrseurRapportLM->bounds(0, 2);
    gCusrseurRapportLM->deactivate();                                             // Pour désactiver le bouton après le démarrage du jeu
    gCusrseurRapportLM->align(FL_ALIGN_TOP);


    // Affichage de la fenetre
    gFenetre->end();
    gFenetre->show();
}



