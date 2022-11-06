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