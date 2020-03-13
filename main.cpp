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

    // Créer la fenetre
    CreerFenetre() ;

    // Initialise le jeu
    Initialiser() ;

    // Armement de la fonction cyclique
    Fl::add_timeout(gTpsTransition, CycleCB, NULL) ;

    // Lancer la boucle de gestion des événements
    return Fl::run();
}


ZoneDessin::ZoneDessin(int x, int y, int width, int height) :
    Fl_Widget(x, y, width, height)
{}


// Méthode draw_callback
void ZoneDessin::draw_callback(Callback *function, void *data)
{
    _draw_callback_function = function;
    _draw_callback_data = data;
}

// Méthode mouse_callback
void ZoneDessin::mouse_callback(Callback *function, void *data)
{
    _mouse_callback_function = function;
    _mouse_callback_data = data;
}

// Méthode keyboard_callback
void ZoneDessin::keyboard_callback(Callback *function, void *data)
{
    _keyboard_callback_function = function;
    _keyboard_callback_data = data;
}

// Méthode de dessin de la zone de dessin
void ZoneDessin::draw()
{
    if (_draw_callback_function)
        _draw_callback_function(this, _draw_callback_data);
}

// Méthode de gestion des événements dans la zone de dessin
int ZoneDessin::handle(int event)
{
    switch (event) {
    case FL_PUSH :
    case FL_RELEASE :
    case FL_DRAG :
        if (_mouse_callback_function)
            _mouse_callback_function(this, _mouse_callback_data);

        return 1 ;

    case FL_KEYBOARD:
        if (_keyboard_callback_function)
            _keyboard_callback_function(this, _keyboard_callback_data);

        return 1 ;

    case FL_FOCUS:
        return 1 ;

    default:
        return Fl_Widget::handle(event);
    }
}

// Fonction cyclique
void CycleCB(void *)
{
    // Appel de la fonction TraiterCycle ( Unite2 )
    TraiterCycle() ;

    // Rearmement de la fonction cyclique
    Fl::add_timeout(gTpsTransition, CycleCB, nullptr) ;
}


