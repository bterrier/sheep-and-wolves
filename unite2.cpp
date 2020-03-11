// Déclarations externes
#include <stdio.h>
#include <stdlib.h>                 // exit, rand
#include <time.h>                   // time
#include <FL/Fl.H>
#include <FL/fl_draw.H>             // fonctions de dessin
#include <stdio.h>                  // printf, ...
#include "unite1.h"
#include "unite2.h"
#include "unite3.h"
#include "unite4.h"
#include <FL/Fl_GIF_Image.H>


// DessinerZone
void ZoneDessinDessinerCB(Fl_Widget *, void *)
{
	if(!gGameOver && !gStart)
	{
		fl_color(vert);                                                     // On efface toute la zone ( en dessinant dessus un carré plein, vert )
		fl_rectf(X_ZONE, Y_ZONE,L_ZONE,H_ZONE);
		int p=gTour%2;
		int tailleAnimal=L_ZONE/TAILLE_MATRICE;

		for(int i=0;i<TAILLE_MATRICE+1;i++)                                 // On dessine les moutons en blanc et les loups en noir sur la zone de dessin
		{
			for(int j=0;j<TAILLE_MATRICE+1;j++)
			{
					if (gTableauJeu[i+1][j+1][p]==MOUTON)
					{
							fl_color(FL_WHITE);
							fl_rectf(tailleAnimal*i+X_ZONE, tailleAnimal*j+Y_ZONE, tailleAnimal*1,tailleAnimal*1);
					}
					else if  (gTableauJeu[i+1][j+1][p]==LOUP)
					{
							fl_color(FL_BLACK);
							fl_rectf(tailleAnimal*i+X_ZONE, tailleAnimal*j+Y_ZONE, tailleAnimal*1,tailleAnimal*1);
					}
			}
		}
	}
	else if(gStart)                                                       // Image sur la zone de dessin lors du lancement du jeu
		img_debut->draw(X_ZONE, Y_ZONE);
	else if(gWinner==LOUP)                                                // Image d'un loup lorsque les loups l'emportent
		img_loup->draw(X_ZONE, Y_ZONE);
	else if(gWinner==MOUTON)                                              // Image d'un mouton lorsque les moutons l'emportent
		img_mouton->draw(X_ZONE, Y_ZONE);
}
