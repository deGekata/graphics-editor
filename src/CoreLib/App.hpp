#ifndef APP_HPP
#define APP_HPP

#include "WindowEventManager.hpp"

class App_;
class App;

class AppDestroyer {
private:
    App* app_instance_ = NULL;
public:
    ~AppDestroyer();
    void initialize(App* ptr);
};

class App {
private:
    App_* rsp_ = NULL;
    static App* app_instance_;
    std::map<uint32_t, Window*> windows_;
    Window* cur_window = NULL; //TODO: currently it supports only one window
    static AppDestroyer destroyer;

protected:
    App();//implement constructor
    App(const App&) = default;
    App& operator=(App&) = default;
    ~App(); //implement destructor

    friend class AppDestroyer;
public:
    int addWindow(Window* window) {
        //TODO: further it will be windows_.insert({window->id, window});
        //
        
    }
    static App& getInstance();
};

#endif