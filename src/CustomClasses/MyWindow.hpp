#ifndef MY_WINDOW_HPP
#define MY_WINDOW_HPP
#include "CoreLib/Core/Window.hpp"
#include "Utilities/vectord_2d.hpp"
#include "CoreLib/Core/GraphicsItem.hpp"
#include "CoreLib/Core/Painter.hpp"
#include "CoreLib/Core/Window.hpp"
#include "CoreLib/Core/GraphicsScene.hpp"
#include "RectangleItem.hpp"
#include "DottedRectangle.hpp"
#include "Arrow.hpp"
#include "RayTracerWidget.hpp"
#include "HoverModifier.hpp"

class MyWindow : public Window {
public:
    MyWindow(int width = 800, int height = 600, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, uint32_t flags = 0);    

    void update() {
        // // exit(0);
        // while (isRunning) {
        //     while (manager_->pollEvent(&event) > 0) {
        //         // printf("lo1");
        //         switch (event.type) {
        //         case EventType::QUIT:
        //             isRunning = false;
        //             break;
                
        //         case EventType::MOUSEBUTTONUP:{
        //             PointF mouse_p;
        //             int x, y;
        //             Transformation trnsfrm = arrow->absTransformFromParent();
        //             // SDL_GetMouseState(&x, &y);
        //             std::cout << "af tranfrom " << trnsfrm * PointF(event.mouse_button.pos.x_, event.mouse_button.pos.y_) << "  \n";
        //             std::cout << "bef tranfrom " << PointF(event.mouse_button.pos.x_, event.mouse_button.pos.y_) << "  \n";
        //             if (event.mouse_button.state == ButtonState::BUTTON_DOWN) {
        //                 std::cout << "down\n";
        //             } else {
        //                 std::cout << "released\n";
        //             }
        //             // arrow->rect_.p2_ = trnsfrm * PointF(x, y);
        //             // arrow->rect_.p1_ = -arrow->rect_.p2_;
        //             break;
        //         }

        //         case EventType::MOUSEMOTION:{
                    
        //                                 int x, y;
        //             Transformation trnsfrm = arrow->absTransformFromParent();
        //             // SDL_GetMouseState(&x, &y);
        //             std::cout << "bef tranfrom " <<event.mouse_motion.pos << "  \n";
        //             std::cout << "after delta " << event.mouse_motion.rel_pos << "  \n";
        //             // if (event.mouse_button.state == ButtonState::BUTTON_DOWN) {
        //             //     std::cout << "down\n";
        //             // } else {
        //             //     std::cout << "released\n";
        //             // }
        //             // arrow->rect_.p2_ = trnsfrm * PointF(x, y);
        //             // arrow->rect_.p1_ = -arrow->rect_.p2_;
        //             break;
        //         }

        //         case EventType::KEYUP:
        //             if (event.keyboard.key.sym == K_k) {
        //                 isRunning = false;
        //                 break;
        //             }

        //             if (event.keyboard.key.sym == K_CAPSLOCK) {
        //                 invert_coord = !invert_coord;
        //             }
        //             break;
        //         default:
        //             break;
        //         }
        //     }
        central_widget_->update(painter_);
        
        this->present();
    
    }

    void setPainter(Painter* painter) {
        if (painter != NULL)
            painter_ = painter;
    }

    void drawSphere(const PointF& center, const PointF& radius); 

    

    GraphicsScene* scene;
    GraphicsRectangleItem* rect1;
    GraphicsRectangleItem* rect2;
    DottedRectangle* dot_rect;
    GraphicsArrow* arrow;
    Painter* painter_;
    RayTracerWidget* tracer;
    RayTracerWidget* tracer2;
    Sphere* sphere1;
    Vector3D center_vec;
};

#endif