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
    // current_active_widget_ = widget;
    //FIX:
}

void App::unlinkModalWidget() {
    //FIX:
    // this->current_active_widget_ = central_widget_;
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
    //FIX:
    // central_widget_ = window->central_widget_;
    // current_active_widget_ = window->central_widget_;
    window->manager_ = this;
    return true;
}

int App::exec() {
    // int frames  = 0;
    // clock_t start = clock();
    while(true) {
        // if (frames == 10000) {
        //     clock_t end = clock() - start;
        //     std::cout << "fps: " << 10000 / (float(end) / CLOCKS_PER_SEC) << "\n";
        //     start = clock();
        //     frames = 0;
        // }
        //FIX:
        cur_window->update();
        cur_window->processEvents();
        cur_window->present();
        // frames++;
        // std::cout << "current frames" << frames << "\n";
    }

    return 0;
}

int App::pollEvent(Event* event, uint32_t window_id) {
    if (event == NULL) return -1;

    if (!event_queue.empty()) {
        *event = event_queue.front();
        event_queue.pop();
        return 1;
    }

    int res = pollEvent_(event, window_id);
    if (res > 0 && event->type == EventType::MOUSEMOTION) {
        
    }
    return res;
}