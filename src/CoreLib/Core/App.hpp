#ifndef APP_HPP
#define APP_HPP

#include "Events/EventManager.hpp"
#include "Utilities/Logger.hpp"
#include <map>
#include <queue>

// #include "WindowEventManager.hpp"

class App_;
class App;
class Window;
class Widget;

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
    static AppDestroyer destroyer;
    // static EventManager manager;
    
    
    Window* cur_window = NULL; //TODO: currently it supports only one window

    std::map<uint32_t, Window*> windows_;
    std::map<uint32_t, Widget*> current_active_widgets;
    std::queue<Event> event_queue;


protected:
    App();//implement constructor
    App(const App&) = default;
    App& operator=(App&) = default;
    ~App(); //implement destructor

    friend class AppDestroyer;
public:

    void linkModalWidget(Widget* widget, uint32_t window_id = 0);

    void unlinkModalWidget();

    bool addWindow(Window* window);

    int exec();

    int pollEvent(Event* event, uint32_t window_id=0);

    int pollEvent_(Event* event, uint32_t window_id=0);


    static App& getInstance();
};

#endif