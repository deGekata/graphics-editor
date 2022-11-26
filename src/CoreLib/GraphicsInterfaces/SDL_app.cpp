#include "SDL_app.hpp"
#include "App.hpp"


App::App() {
    rsp_ = new App_();

    
}

App::~App() {
    delete rsp_;
}

int App::pollEvent(Event* event, uint32_t window_id) {
    //TODO:`
    UNUSED(window_id);
    if (event == NULL) {
        printError("event ptr must not be NULL");
        throw;
    }
    //need to add id for events 
    SDL_Event sdl_event;
    int ret_val = rsp_->pollEvent(&sdl_event);
    if (ret_val < 0) return ret_val;

    switch (sdl_event.type) {
    case SDL_MOUSEMOTION:
        event->type = EventType::MOUSEMOTION;
        event->mouse_motion.pos.x_     = sdl_event.motion.x;
        event->mouse_motion.rel_pos.x_ = sdl_event.motion.xrel;
        event->mouse_motion.pos.y_     = sdl_event.motion.y;
        event->mouse_motion.rel_pos.y_ = sdl_event.motion.yrel;
        break;
    
    case SDL_KEYDOWN:
        event->type = EventType::KEYDOWN;
        event->keyboard.state = ButtonState::BUTTON_DOWN;
        event->keyboard.key.mode = (Keymod) sdl_event.key.keysym.mod;
        event->keyboard.key.scancode =  (Scancode) sdl_event.key.keysym.scancode;
        event->keyboard.key.sym = (Keycode) sdl_event.key.keysym.sym;
        break;

    case SDL_KEYUP:
        event->type = EventType::KEYUP;
        event->keyboard.state = ButtonState::BUTTON_UP;
        event->keyboard.key.mode = (Keymod) sdl_event.key.keysym.mod;
        event->keyboard.key.scancode =  (Scancode) sdl_event.key.keysym.scancode;
        event->keyboard.key.sym = (Keycode) sdl_event.key.keysym.sym;
        break;
    
    case SDL_MOUSEBUTTONDOWN:
        event->type = EventType::MOUSEBUTTONDOWN;
        event->mouse_button.button = (MouseButton) sdl_event.button.button;
        event->mouse_button.clicks = sdl_event.button.clicks;
        event->mouse_button.state = ButtonState::BUTTON_DOWN;
        event->mouse_button.x = sdl_event.button.x;
        event->mouse_button.y = sdl_event.button.y;
        break;

    case SDL_MOUSEBUTTONUP:
        event->type = EventType::MOUSEBUTTONUP;
        event->mouse_button.button = (MouseButton) sdl_event.button.button;
        event->mouse_button.clicks = sdl_event.button.clicks;
        event->mouse_button.state = ButtonState::BUTTON_UP;
        event->mouse_button.x = sdl_event.button.x;
        event->mouse_button.y = sdl_event.button.y;
        break;

    case SDL_MOUSEWHEEL:
        // event->type = EventType::MOUSEMOTION;
        // //fuck you i wont process it
        break;

    case SDL_QUIT:
        event->type = EventType::QUIT;
        break;

    default:
        break;
    }

    return ret_val;
} 