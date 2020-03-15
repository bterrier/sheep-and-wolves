/*  Projet Loups et Moutons : unite3.cpp    Dernière modification : 30/05/2009 */
#include "unite3.h"

#include <cstdlib>     // exit, rand
#include <ctime>       // time

#include <FL/Fl.H>
#include <FL/fl_ask.H>  // fl_message, fl_alert, fl_ask
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_GIF_Image.H> // fl_file_chooser

#include "unite1.h"
#include "unite4.h"


//Déclaration des variables globales
int gTour;
bool gStepByStep, gPlay, gReset, gGameOver, gStart;
int gTimeOver;
float gTpsTransition;

//Initialisation au lacement du programme
void firstinitialiser()
{
    gStart = 1;                 //Le programme vient d're lancé
}


void Initialiser()
{
    std::srand(std::time(NULL)); //on initialise rand()

    /* On définie les diffrentes variables */

    gTour = 0;
    gGameOver = false;
    gTimeOver = 0;
    gStepByStep = false;
    gPlay = false;
    gTpsTransition = 1;
    delete game;
    game = new Game();
}

// TraiterCycle
void TraiterCycle()
{

    //Si le jeu est lancé, on déplace les animaux
    if (gPlay) {
        game->moveAll();
        gTour++;
    }
    //Si le jeu est en mode "Pas à pas", on déplace les animaux et on sort du pas à pas
    else if (gStepByStep) {
        game->moveAll();
        gStepByStep = false;
        gTour++;

    }

    //Si l'utilsateur a cliqueé qur "Reset", on initialise le jeu
    if (gReset) {
        Initialiser();
        gReset = false;
    }

    // On redessine la zone
    window->gZoneDessin->redraw() ;
    //On actualise la valeur du rapport
    const auto ratio = game->ratio();
    window->gCusrseurRapportLM->value(ratio);

    //Si il n'y a plus de loups, on attend 10 tours et on met fin au jeu
    if (ratio == 0) {
        gTimeOver++;

        if (gTimeOver > 10) {
            gGameOver = true;
            game->setWinner(MOUTON);
        }
    }

    //Si il n'y a plus de mouton, on attend 10 tours et on arrette le jeu
    if (ratio == -1) {
        gTimeOver++;

        if (gTimeOver > 10) {
            gGameOver = true;
            game->setWinner(LOUP);
        }
    }
}



void BoutonQuitterCB(Fl_Widget *, void *)
{
    // Fin du programme
    exit(0) ;
}

void BoutonStartPauseCB(Fl_Widget *, void *)
{
    gPlay = !gPlay; // on inverse la valuer de gPlay   0 <-> 1
    gStart = false;     //Le jeu est lancé

    if (gPlay) {
        window->gBoutonPasPas->deactivate() ;                                    // Lorsque le jeu se lance, on bloque les boutons et curseurs
        window->gCurseurMouton->deactivate();
        window->gCurseurLoup->deactivate();
    } else {
        window->gBoutonPasPas->activate() ;                                     // On les réactive lorsqu'on arrête le jeu
        window->gCurseurMouton->activate() ;
        window->gCurseurLoup->activate();
    }

}

void BoutonPasPasCB(Fl_Widget *, void *)
{
    gStepByStep = true;                                                    // Avance d'un tour à chaque clic
    gStart = false;

}

void BoutonResetCB(Fl_Widget *, void *)
{
    gReset = true;                                                         // Relance le jeu
    gStart = false;
}


void CurseurNataliteCB(Fl_Widget *, void *)
{
    game->setSheepBirthRate(window->gCurseurNatalite->value());
}

void CurseurMortaliteCB(Fl_Widget *, void *)
{
    game->setWolfDeathRate(window->gCurseurMortalite->value());
}

void CurseurTpsTransitionCB(Fl_Widget *, void *)                   // Change le temps de transition entre chaque tour
{
    gTpsTransition = window->gCurseurTpsTransition->value() ;

}

void CurseurMoutonCB(Fl_Widget *, void *)                          // Permet de changer le nombre de moutons initial
{
    game->setInitialSheepCount(int(window->gCurseurMouton->value()));               //On récupére la valeur
    Initialiser() ;                                                     //On initialise avec la nouvelle valeur
}

void CurseurLoupCB(Fl_Widget *, void *)                            // Permet de changer le nombre de loups initial
{
    game->setInitialWolfCount(int(window->gCurseurLoup->value()));                   //On récupére la valeur
    Initialiser();                                                      //On initialise avec la nouvelle valeur
}
