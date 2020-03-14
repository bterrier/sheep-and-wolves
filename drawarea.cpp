#include "drawarea.h"


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
