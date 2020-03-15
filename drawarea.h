#ifndef DRAWAREA_H
#define DRAWAREA_H


// Déclarations externes
#include <FL/Fl_Widget.H>

// Déclaration de la classe ZoneDessin
class ZoneDessin : public Fl_Widget
{
public:
    using Callback = void(Fl_Widget *w, void *data);

    ZoneDessin(int x, int y, int width, int height) ;
    void draw_callback(Callback *function, void *data);

private :
    void draw() override;

    Callback *_draw_callback_function = nullptr;
    void *_draw_callback_data = nullptr;
};

#endif // DRAWAREA_H
