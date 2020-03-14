// Déclarations externes
#include "main.h"

#include <FL/Fl.H>      //  fl::run

#include "unite1.h"     // CreerFenetre
#include "unite2.h"     // DessinerZone
#include "unite3.h"     // Initialiser, TraiterCycle, TraiterClicZone, TraiterClavierZone

// Déclaration des sous-programmes
void CycleCB(void *) ;
int main();

#ifdef _WIN32
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    return main();
}
#endif

// Programme Principal
//void main()
int main()
{
    // initialise le logiciel
    firstinitialiser();


    // Initialize the game
    Initialiser() ;

    // Create the window
    window = new MainWindow();
    window->show();


    // Armement de la fonction cyclique
    Fl::add_timeout(gTpsTransition, CycleCB, NULL) ;

    // Lancer la boucle de gestion des événements
    return Fl::run();
}

// Fonction cyclique
void CycleCB(void *)
{
    // Appel de la fonction TraiterCycle ( Unite2 )
    TraiterCycle() ;

    // Rearmement de la fonction cyclique
    Fl::add_timeout(gTpsTransition, CycleCB, nullptr) ;
}


