// Sentinelle d'inclusion
#ifndef _Main_h
#define _Main_h

// Déclarations externes
#include <FL/Fl_Widget.H>

// Définition des constantes
#define DUREE_CYCLE 0.1   // 0.500 secondes

// Déclaration de la classe ZoneDessin
class ZoneDessin : public Fl_Widget
{
public:
    ZoneDessin(int X,int Y,int W,int H) ;
    void draw_callback( void (*Function) ( Fl_Widget* w, void* data), void* Data ) ;
    void mouse_callback( void (*Function) ( Fl_Widget* w, void* data), void* Data ) ;
    void keyboard_callback( void (*Function) ( Fl_Widget* w, void* data), void* Data ) ;

private :
    void draw() ;
    int handle(int event) ;

    void (*_draw_callback_function) ( Fl_Widget* w, void* data) ;
    void* _draw_callback_data ;

    void (*_mouse_callback_function) ( Fl_Widget* w, void* data) ;
    void* _mouse_callback_data ;

    void (*_keyboard_callback_function) ( Fl_Widget* w, void* data) ;
    void* _keyboard_callback_data ;
};


#endif // _Main_h
