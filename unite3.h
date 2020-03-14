// Sentinelle d'inclusion
#ifndef _unite3_h
#define _unite3_h

// Déclarations externes
#include <FL/Fl_Widget.H>


// Déclaration des données du projet
constexpr int TAILLE_MATRICE = 200;
enum Type {
    VIDE = 0,
    MOUTON = 1,
    LOUP = -1,
    BORD = 99
};

// Donnees du projet

extern int gTour, gStepByStep, gPlay, gGameOver, gTimeOver, gStart, gWinner, gNB_MOUTONS_INITIAUX, gNB_LOUPS_INITIAUX;
extern float gTpsTransition;
// Flag quand le bouton Solution est sollicite


extern int gTableauJeu[TAILLE_MATRICE + 2][TAILLE_MATRICE + 2][2];

// Déclaration des sous-programmes
void firstinitialiser();
void Initialiser() ;
void TraiterCycle() ;
void BoutonQuitterCB(Fl_Widget *w, void *data) ;
void BoutonStartPauseCB(Fl_Widget *w, void *data) ;
void BoutonPasPasCB(Fl_Widget *w, void *data) ;
void BoutonResetCB(Fl_Widget *w, void *data) ;
void CurseurNataliteCB(Fl_Widget *w, void *data);
void CurseurMortaliteCB(Fl_Widget *w, void *data);
void CurseurTpsTransitionCB(Fl_Widget *w, void *data);
void CurseurMoutonCB(Fl_Widget *w, void *data);
void CurseurLoupCB(Fl_Widget *w, void *data);
#endif // _unite3_h
