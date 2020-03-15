// Déclarations externes
#include "unite1.h"

#include <FL/fl_draw.H>
#include <FL/Fl_GIF_Image.H>

#include "unite3.h"
#include "unite4.h"


MainWindow::MainWindow() :
    Fl_Double_Window(560, 480),
    vert(fl_rgb_color(87, 153, 40))
{
    label("Projet Loups et Moutons") ;                                        // Nom du programme
    begin() ;

    // Création de la zone de dessin
    gZoneDessin = new ZoneDessin(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);
    gZoneDessin->draw_callback(ZoneDessinDessinerCB, this) ;

    img_mouton = new Fl_GIF_Image("mouton.gif");
    img_debut = new Fl_GIF_Image("debut.gif");
    img_loup = new Fl_GIF_Image("loup.gif");



    // Création du bouton Start/Pause
    gBoutonStartPause = new Fl_Button(440, 10, 100, 30, "Start/Pause") ;                // Positionnement et affichage du nom du bouton
    gBoutonStartPause->callback(BoutonStartPauseCB, nullptr) ;                             // Lien avec la programmation
    gBoutonStartPause->box(FL_PLASTIC_UP_BOX);                                          // Type du bouton

    // Création du bouton Pas à pas
    gBoutonPasPas = new Fl_Button(440, 50, 100, 30, "Pas a Pas") ;
    gBoutonPasPas->callback(BoutonPasPasCB, nullptr) ;
    gBoutonPasPas->box(FL_PLASTIC_UP_BOX);

    // Création du bouton Reset
    gBoutonReset = new Fl_Button(440, 90, 100, 30, "Reset") ;
    gBoutonReset->callback(BoutonResetCB, nullptr) ;
    gBoutonReset->box(FL_ROUND_UP_BOX);

    // Création du bouton Quitter
    gBoutonQuitter = new Fl_Button(440, 440, 100, 30, "Quitter") ;
    gBoutonQuitter->callback(BoutonQuitterCB, nullptr) ;
    gBoutonQuitter->box(FL_OSHADOW_BOX);





    // Création du curseur Natalité
    gCurseurNatalite = new Fl_Value_Slider(440, 160, 100, 25, "Natalite") ;             // Positionnement et affichage du nom du curseur natalité
    gCurseurNatalite->type(FL_HOR_NICE_SLIDER) ;                                        // Type de curseur
    gCurseurNatalite->align(FL_ALIGN_TOP) ;                                             // Alignement au milieu et en haut du nom du curseur (par rapport au curseur)
    gCurseurNatalite->callback(CurseurNataliteCB, nullptr) ;                               // Lien avec la programmation
    gCurseurNatalite->bounds(0, 1);                                                     // Borne du curseur
    gCurseurNatalite->precision(2);                                                     // Précision du curseur en nombre de décimale
    gCurseurNatalite->value(game->sheepBirthRate());                                           // Lien avec la programmation

    // Création du curseur Mortalité
    gCurseurMortalite = new Fl_Value_Slider(440, 215, 100, 25, "Mortalite") ;
    gCurseurMortalite->type(FL_HOR_NICE_SLIDER) ;
    gCurseurMortalite->align(FL_ALIGN_TOP) ;
    gCurseurMortalite->callback(CurseurMortaliteCB, nullptr) ;
    gCurseurMortalite->bounds(0, 1);
    gCurseurMortalite->precision(2);
    gCurseurMortalite->value(game->wolfDeathRate());

    //Création du curseur mouton
    gCurseurMouton = new Fl_Value_Slider(30, 440, 150, 25, "Nombre Moutons Initial") ;
    gCurseurMouton->type(FL_HOR_NICE_SLIDER) ;
    gCurseurMouton->align(FL_ALIGN_TOP) ;
    gCurseurMouton->callback(CurseurMoutonCB, NULL) ;
    gCurseurMouton->bounds(1, 20000);
    gCurseurMouton->value(game->initialSheepCount());
    gCurseurMouton->precision(0);                                                   // Précision de la décimale (0 = entier)

    //Création du curseur loup
    gCurseurLoup = new Fl_Value_Slider(240, 440, 150, 25, "Nombre Loups Initial") ;
    gCurseurLoup->type(FL_HOR_NICE_SLIDER) ;
    gCurseurLoup->align(FL_ALIGN_TOP) ;
    gCurseurLoup->callback(CurseurLoupCB, NULL) ;
    gCurseurLoup->bounds(1, 20000);
    gCurseurLoup->value(game->initialWolfCount());
    gCurseurLoup->precision(0);

    // Création du curseur Temps de transition
    gCurseurTpsTransition = new Fl_Value_Slider(440, 270, 100, 25, "Tps de transition") ;
    gCurseurTpsTransition->type(FL_HOR_NICE_SLIDER) ;
    gCurseurTpsTransition->align(FL_ALIGN_TOP) ;
    gCurseurTpsTransition->callback(CurseurTpsTransitionCB, NULL) ;
    gCurseurTpsTransition->bounds(0.01, 2);
    gCurseurTpsTransition->precision(2);
    gCurseurTpsTransition->value(gTpsTransition);



    // Création d'une fenêtre pour afficher le rapport loup sur mouton
    gCusrseurRapportLM = new Fl_Value_Slider(470, 325, 40, 100, "Loups/Moutons") ;
    gCusrseurRapportLM->type(FL_VERT_FILL_SLIDER);
    gCusrseurRapportLM->color(FL_WHITE);
    gCusrseurRapportLM->color2(FL_BLACK);
    gCusrseurRapportLM->bounds(0, 2);
    gCusrseurRapportLM->deactivate();                                             // Pour désactiver le bouton après le démarrage du jeu
    gCusrseurRapportLM->align(FL_ALIGN_TOP);


    // Affichage de la fenetre
    end();

    //On initialise certains élément de l'interface

    gCurseurLoup->activate();
    gCurseurMouton->activate();
    gBoutonPasPas->activate();
}

void MainWindow::drawWorld()
{
    auto window = this;

    if (!gGameOver && !gStart) {
        fl_color(vert);                                                      // On efface toute la zone ( en dessinant dessus un carré plein, vert )
        fl_rectf(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);
        int p = gTour % 2;
        int tailleAnimal = L_ZONE / Game::TAILLE_MATRICE;

        for (int i = 0; i < Game::TAILLE_MATRICE + 1; i++) {                      // On dessine les moutons en blanc et les loups en noir sur la zone de dessin
            for (int j = 0; j < Game::TAILLE_MATRICE + 1; j++) {
                if (game->gTableauJeu[i + 1][j + 1][p] == MOUTON) {
                    fl_color(FL_WHITE);
                    fl_rectf(tailleAnimal * i + X_ZONE, tailleAnimal * j + Y_ZONE, tailleAnimal * 1, tailleAnimal * 1);
                } else if (game->gTableauJeu[i + 1][j + 1][p] == LOUP) {
                    fl_color(FL_BLACK);
                    fl_rectf(tailleAnimal * i + X_ZONE, tailleAnimal * j + Y_ZONE, tailleAnimal * 1, tailleAnimal * 1);
                }
            }
        }
    } else if (gStart)                                                    // Image sur la zone de dessin lors du lancement du jeu
        window->img_debut->draw(X_ZONE, Y_ZONE);
    else if (game->winner() == LOUP)                                             // Image d'un loup lorsque les loups l'emportent
        window->img_loup->draw(X_ZONE, Y_ZONE);
    else if (game->winner() == MOUTON)                                           // Image d'un mouton lorsque les moutons l'emportent
        window->img_mouton->draw(X_ZONE, Y_ZONE);
}

void MainWindow::updateControls()
{
    gCurseurNatalite->value(game->sheepBirthRate());
    gCurseurMortalite->value(game->wolfDeathRate());
    gCurseurTpsTransition->value(gTpsTransition);
}

MainWindow *window = nullptr;

void MainWindow::ZoneDessinDessinerCB(Fl_Widget *, void *data)
{
    auto window = static_cast<MainWindow *>(data);

    window->drawWorld();
}
