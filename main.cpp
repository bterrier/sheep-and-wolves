// Déclarations externes
#include <stdio.h>
#include <FL/Fl.H>      //  fl::run
#include "main.h"
#include "unite1.h"     // CreerFenetre
#include "unite2.h"     // DessinerZone
#include "unite3.h"     // Initialiser, TraiterCycle, TraiterClicZone, TraiterClavierZone

// Déclaration des sous-programmes
void CycleCB( void*) ;
int main();

#ifdef _WIN32
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                             LPSTR lpCmdLine, int nCmdShow) {
                                 return main();
}
#endif

// Programme Principal
//void main()
int main ()
{
    // initialise le logiciel
    firstinitialiser();

    // Créer la fenetre
    CreerFenetre() ;

    // Initialise le jeu
    Initialiser() ;

    // Armement de la fonction cyclique
    Fl::add_timeout(gTpsTransition, CycleCB, NULL ) ;

    // Lancer la boucle de gestion des événements
    return Fl::run();
}


ZoneDessin::ZoneDessin(int X,int Y,int W,int H)
: Fl_Widget(X,Y,W,H)
{
    _draw_callback_function = NULL ;
    _draw_callback_data = NULL ;

    _mouse_callback_function = NULL ;
    _mouse_callback_data = NULL ;

    _keyboard_callback_function = NULL ;
    _keyboard_callback_data = NULL ;
}


// Méthode draw_callback
void ZoneDessin::draw_callback( void (*Function) ( Fl_Widget* w, void* data), void* Data )
{
    _draw_callback_function = Function ;
    _draw_callback_data = Data ;
}

// Méthode mouse_callback
void ZoneDessin::mouse_callback( void (*Function) ( Fl_Widget* w, void* data), void* Data )
{
    _mouse_callback_function = Function ;
    _mouse_callback_data = Data ;
}

// Méthode keyboard_callback
void ZoneDessin::keyboard_callback( void (*Function) ( Fl_Widget* w, void* data), void* Data )
{
    _keyboard_callback_function = Function ;
    _keyboard_callback_data = Data ;
}

// Méthode de dessin de la zone de dessin
void ZoneDessin::draw()
{
    if ( _draw_callback_function != NULL )
        (* _draw_callback_function ) ( this, _draw_callback_data ) ;
}

// Méthode de gestion des événements dans la zone de dessin
int ZoneDessin::handle(int event)
{
    switch(event)
    {
        case FL_PUSH :
        case FL_RELEASE :
        case FL_DRAG :
             if ( _mouse_callback_function != NULL )
                (* _mouse_callback_function ) ( this, _mouse_callback_data ) ;
            return 1 ;
            break ;

        case FL_KEYBOARD:
             if ( _keyboard_callback_function != NULL )
                (* _keyboard_callback_function ) ( this, _keyboard_callback_data ) ;
            return 1 ;
            break ;

        case FL_FOCUS:
            return 1 ;
            break ;


        default:
            return Fl_Widget::handle(event);
    }
}

// Fonction cyclique
void CycleCB( void* )
{
    // Appel de la fonction TraiterCycle ( Unite2 )
    TraiterCycle() ;

    // Rearmement de la fonction cyclique
    Fl::add_timeout(gTpsTransition, CycleCB, NULL ) ;
}


