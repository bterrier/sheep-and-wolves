// Sentinelle d'inclusion
#ifndef _Main_h
#define _Main_h

// Déclarations externes
#include <FL/Fl_Widget.H>

// Déclaration de la classe ZoneDessin
class ZoneDessin : public Fl_Widget
{
public:
    using Callback = void(Fl_Widget *w, void *data);

    ZoneDessin(int x, int y, int width, int height) ;
    void draw_callback(Callback *function, void *data) ;
    void mouse_callback(Callback *function, void *data) ;
    void keyboard_callback(Callback *function, void *data) ;

private :
    void draw() override;
    int handle(int event) override;

    Callback *_draw_callback_function = nullptr;
    void *_draw_callback_data = nullptr;

    Callback *_mouse_callback_function = nullptr;
    void *_mouse_callback_data = nullptr;

    Callback *_keyboard_callback_function = nullptr;
    void *_keyboard_callback_data = nullptr;
};


#endif // _Main_h
