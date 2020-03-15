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

// Méthode de dessin de la zone de dessin
void ZoneDessin::draw()
{
    if (_draw_callback_function)
        _draw_callback_function(this, _draw_callback_data);
}
