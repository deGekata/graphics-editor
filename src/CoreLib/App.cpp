#include "App.hpp"

App* App::app_instance_ = 0;
AppDestroyer App::destroyer;

AppDestroyer::~AppDestroyer() {   
    delete app_instance_; 
}
void AppDestroyer::initialize(App* p) {
    app_instance_ = p; 
}
App& App::getInstance() {
    if(!app_instance_)     {
        app_instance_ = new App();
        destroyer.initialize( app_instance_);     
    }
    return *app_instance_;
}


void App::linkModalWidget(Widget* widget, uint32_t window_id) {
    UNUSED(window_id); // TODO: etot pipec ya kogda nibud sdelau
    if (widget == NULL) {
        printError("modal widget ptr must not be NULL");
        throw;
    }
    current_active_widget_ = widget;
}

void App::unlinkModalWidget() {
    this->current_active_widget_ = central_widget_;
}

bool App::addWindow(Window* window) {
    //TODO: replace further for many windows
    if (window == NULL) {
        printError("window ptr must not be NULL");
        throw;
    }
    //TODO: further it will be windows_.insert({window->id, window});
    //
    cur_window = window;
    central_widget_ = window->central_widget_;
    current_active_widget_ = window->central_widget_;
    window->manager_ = this;
    return true;
}

int App::exec() {
    cur_window->exec();
    return 0;
}