// #ifndef WINDOW_EVENT_MANAGER_HPP
// #define WINDOW_EVENT_MANAGER_HPP
// #include "Event.hpp"
// #include "EventManager.hpp"
// #include "Window.hpp"
// #include "Logger.hpp"
// #include <map>

// class WindowEventManager_;

// class WindowEventManager {
// private:
//     // WindowEventManager_* rsp_ = NULL;
//     // std::map<uint32_t, Window*> windows;
//     // std::map<uint32_t, Widget*> current_active_widgets;
//     // WindowEventManager();
// public:
//     // Widget* current_text_input = NULL;
//     // Widget* central_widget_ = NULL;
//     // Widget* current_active_widget_ = NULL;

//     // void linkModalWidget(Widget* widget, uint32_t window_id = 0) {
//     //     UNUSED(window_id); // TODO: etot pipec ya kogda nibud sdelau
//     //     if (widget == NULL) {
//     //         printError("modal widget ptr must not be NULL");
//     //         throw;
//     //     }
//     //     current_active_widget_ = widget;
//     // }

//     // void unlinkModalWidget() {
//     //     this->current_active_widget_ = central_widget_;
//     // }

//     // bool addWindow(Window* window) {
//     //     //TODO: replace further for many windows
//     //     central_widget_ = window->central_widget_;
//     //     current_active_widget_ = window->central_widget_;
         
//     // }

//     //Event dispatcher for windows

//     // int pollEvent(Event* event, uint32_t window_id=0);

//     // friend class Window;
// };

// #endif