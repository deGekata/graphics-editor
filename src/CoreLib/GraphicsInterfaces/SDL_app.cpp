#include "SDL_app.hpp"
#include "App.hpp"



App::App() {
    rsp_ = new App_();
    
}

App::~App() {
    delete rsp_;
}

