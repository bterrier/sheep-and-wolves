/*  Projet Loups et Moutons : unite3.cpp    Dernière modification : 30/05/2009 */

// Inclusion des fichiers d'entête
#include <stdlib.h>     // exit, rand
#include <ctime>       // time

#include <FL/Fl.H>
#include <FL/fl_ask.H>  // fl_message, fl_alert, fl_ask
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_GIF_Image.H> // fl_file_chooser

#include "unite1.h"     // objets graphiques pZoneDessin, pChampValeur, ...
#include "unite2.h"
#include "unite3.h"
#include "unite4.h"


//Déclaration des variables globales
int gTour, gStepByStep, gPlay, gReset, gGameOver,gTimeOver, gStart, gWinner, gNB_MOUTONS_INITIAUX, gNB_LOUPS_INITIAUX;
float gTpsTransition;
float gMortaliteLoup, gNataliteMouton;
int gTableauJeu[TAILLE_MATRICE+2][TAILLE_MATRICE+2][2];

//Initialisation au lacement du programme
void firstinitialiser(){
    gStart=1;                   //Le programme vient d're lancé
    gNB_MOUTONS_INITIAUX=2000;  //valeur par défaut
    gNB_LOUPS_INITIAUX=2000;
}


void Initialiser(){
    srand(time(NULL)); //on initialise rand()

    /* On définie les diffrentes variables */

    gTour=0;
    gGameOver=0;
    gTimeOver=0;
    gStepByStep=0;
    gPlay=0;
    gTpsTransition=1;
    gMortaliteLoup=0.1;
    gNataliteMouton=0.1;
    gWinner=VIDE;


    //On vide la tableau de jeu
    setTab(0);
    setTab(1);

    //On place les moutons aléatoirement dans le tableau de jeu
    int x,y;
    int n=0;
    do{
        x=rand()%TAILLE_MATRICE+1;
        y=rand()%TAILLE_MATRICE+1;
        if(isVacant(x,y,0)){
            gTableauJeu[x][y][0]=MOUTON;
            n++;
        }
    }while(n<gNB_MOUTONS_INITIAUX);

    //On place les loups aléatoirment dans le tableau de jeu
    n=0;
       do{
        x=rand()%TAILLE_MATRICE+1;
        y=rand()%TAILLE_MATRICE+1;
        if(isVacant(x,y,0)){
            gTableauJeu[x][y][0]=LOUP;
            n++;
        }
    }while(n<gNB_LOUPS_INITIAUX);

    //On initialise certains élément de l'interface
    gCurseurNatalite->value(gNataliteMouton);
    gCurseurMortalite->value(gMortaliteLoup);
    gCurseurTpsTransition->value(gTpsTransition);
    gCurseurMouton->value(gNB_MOUTONS_INITIAUX);
    gCurseurLoup->activate();
    gCurseurMouton->activate();
    gBoutonPasPas->activate();

}







// TraiterCycle
void TraiterCycle(){
    int x, y;

    //Si le jeu est lancé, on déplace les animaux
    if (gPlay){
            deplacement();
            gTour++;
        }
    //Si le jeu est en mode "Pas à pas", on déplace les animaux et on sort du pas à pas
    else if (gStepByStep)
        {
            deplacement();
            gStepByStep=0;
            gTour++;

        }

    //Si l'utilsateur a cliqueé qur "Reset", on initialise le jeu
    if (gReset){
        Initialiser();
        gReset=0;
    }
    // On redessine la zone
    gZoneDessin->redraw() ;
    //On actualise la valeur du rapport
    gCusrseurRapportLM->value(rapport());

    //Si il n'y a plus de loups, on attend 10 tours et on met fin au jeu
    if (rapport()==0){
        gTimeOver++;
        if(gTimeOver>10){
            gGameOver=1;
			gWinner=MOUTON;
        }
    }
    //Si il n'y a plus de mouton, on attend 10 tours et on arrette le jeu
    if (rapport()==-1){
        gTimeOver++;
        if(gTimeOver>10){
            gGameOver=1;
			gWinner=LOUP;
        }
    }
}



void BoutonQuitterCB(Fl_Widget* w, void* data)
{
    // Fin du programme
    exit(0) ;
}

void BoutonStartPauseCB(Fl_Widget* w, void* data)
{
    gPlay=1-gPlay;  // on inverse la valuer de gPlay   0 <-> 1
    gStart=0;       //Le jeu est lancé
    if(gPlay){
        gBoutonPasPas->deactivate() ;                                    // Lorsque le jeu se lance, on bloque les boutons et curseurs
        gCurseurMouton->deactivate();
        gCurseurLoup->deactivate();
    }
    else{
        gBoutonPasPas->activate() ;                                     // On les réactive lorsqu'on arrête le jeu
        gCurseurMouton->activate() ;
        gCurseurLoup->activate();
    }

}

void BoutonPasPasCB(Fl_Widget* w, void* data)
{
    gStepByStep=1;                                                      // Avance d'un tour à chaque clic
    gStart=0;

}

void BoutonResetCB(Fl_Widget* w, void* data)
{
    gReset=1;                                                           // Relance le jeu
    gStart=0;

}


void CurseurNataliteCB(Fl_Widget* w, void* data)
{
    gNataliteMouton = gCurseurNatalite->value() ;                       //On récupére la valeur

}

void CurseurMortaliteCB(Fl_Widget* w, void* data)
{
    gMortaliteLoup = gCurseurMortalite->value() ;                       //On récupére la valeur

}

void CurseurTpsTransitionCB(Fl_Widget* w, void* data)                   // Change le temps de transition entre chaque tour
{
    gTpsTransition = gCurseurTpsTransition->value() ;

}

void CurseurMoutonCB(Fl_Widget* w, void* data)                          // Permet de changer le nombre de moutons initial
{
    gNB_MOUTONS_INITIAUX = (int)gCurseurMouton->value() ;               //On récupére la valeur
    Initialiser() ;                                                     //On initialise avec la nouvelle valeur
}

void CurseurLoupCB(Fl_Widget* w, void* data)                            // Permet de changer le nombre de loups initial
{
    gNB_LOUPS_INITIAUX = (int)gCurseurLoup->value() ;                   //On récupére la valeur
    Initialiser();                                                      //On initialise avec la nouvelle valeur
}
