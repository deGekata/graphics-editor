#ifndef MY_WINDOW_HPP
#define MY_WINDOW_HPP

#include "Window.hpp"
#include "vectord_2d.hpp"
#include "GraphicsItem.hpp"
#include "Painter.hpp"
#include "Window.hpp"
#include "GraphicsScene.hpp"
#include "RectangleItem.hpp"
#include "DottedRectangle.hpp"
#include "Arrow.hpp"
#include "RayTracerWidget.hpp"

class MyWindow : public Window {
public:
    MyWindow(int width = 800, int height = 600, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, uint32_t flags = 0);    

    void exec() {
        bool isRunning = true;
        bool invert_coord = true;

        Event event;
        // SDL_Event event; 



        CoordSys ss(0, 0, 800, 600);
        CoordSys ss1(0, 0, 800, 600);
        CoordSys ss2(400, 0, 800, 300);
        SDL_Log("s x %d \n", ss.size_.getY());
        SDL_Log("s y %d \n", ss.size_.getY());
        SDL_Log("b x %d \n", ss.base_point_.getY());
        SDL_Log("b y %d \n", ss.base_point_.getY());

        // return 0;
        Vec2D line(400, 300);

        

        // exit(0);
        while (isRunning) {
            while (manager_->pollEvent(&event) > 0) {
                // printf("lo1");
                switch (event.type) {
                case EventType::QUIT:
                    isRunning = false;
                    break;
                
                case EventType::MOUSEBUTTONUP:{
                    PointF mouse_p;
                    int x, y;
                    Transformation trnsfrm = arrow->absTransformFromParent();
                    // SDL_GetMouseState(&x, &y);
                    std::cout << "af tranfrom " << trnsfrm * PointF(event.mouse_button.x, event.mouse_button.y) << "  \n";
                    std::cout << "bef tranfrom " << PointF(event.mouse_button.x, event.mouse_button.y) << "  \n";
                    if (event.mouse_button.state == ButtonState::BUTTON_DOWN) {
                        std::cout << "down\n";
                    } else {
                        std::cout << "released\n";
                    }
                    // arrow->rect_.p2_ = trnsfrm * PointF(x, y);
                    // arrow->rect_.p1_ = -arrow->rect_.p2_;
                    break;
                }

                case EventType::MOUSEMOTION:{
                    
                                        int x, y;
                    Transformation trnsfrm = arrow->absTransformFromParent();
                    // SDL_GetMouseState(&x, &y);
                    std::cout << "bef tranfrom " <<event.mouse_motion.pos << "  \n";
                    std::cout << "after delta " << event.mouse_motion.rel_pos << "  \n";
                    // if (event.mouse_button.state == ButtonState::BUTTON_DOWN) {
                    //     std::cout << "down\n";
                    // } else {
                    //     std::cout << "released\n";
                    // }
                    // arrow->rect_.p2_ = trnsfrm * PointF(x, y);
                    // arrow->rect_.p1_ = -arrow->rect_.p2_;
                    break;
                }

                case EventType::KEYUP:
                    if (event.keyboard.key.sym == K_k) {
                        isRunning = false;
                        break;
                    }

                    if (event.keyboard.key.sym == K_CAPSLOCK) {
                        invert_coord = !invert_coord;
                    }
                    break;
                default:
                    break;
                }
            }
            // printf("%d\n", __LINE__);
            // painter_->setColor(0, 0, 0);
            // painter_->fillWindow();

            // painter_->setColor(255, 255, 255);
            // painter_->drawLine(320, 200, 300, 240);
            // painter_->drawLine(300, 240, 340, 240);
            // painter_->drawLine(340, 240, 320, 200);

            // scene->repaint(painter_);
            // printf("%d\n", __LINE__);
            central_widget_->update(painter_);
            // tracer->update(painter_);
            // if (invert_coord) {
            //     ss.drawVec(painter_->painter_, ss2, line); 
            // } else {
            //     ss.drawVec(painter_->painter_, ss1, line);
            // }
            // printf("%d\n", __LINE__);

            // painter_->present();
            // printf("%d\n", __LINE__);

            // rect1->rotation_angle_ += 0.0001 * M_PI;
            // dot_rect->rotation_angle_ += 0.0001 * M_PI;
            // // tracer->camera_pos_.x_ += 5;
            // // sphere1->base_point_.x_ += 5;
            
            // // tracer->camera_pos_ = cen
            // // tracer->FOV_ += M_PI / 180 * 5;
            // // tracer->camera_pos_.x_ += 5;
            // // sphere1->base_point_.x_ += 5;
            
            // tracer->camera_pos_ = tracer->camera_pos_ - center_vec;
            // // tracer->camera_direction_ = {
            // //     tracer->camera_direction_.x_ * cos(0.05) - tracer->camera_direction_.z_ * sin(0.05),
            // //     0,
            // //     tracer->camera_direction_.x_ * sin(0.05) + tracer->camera_direction_.z_ * cos(0.05)
            // // };

            // tracer->camera_pos_ = {
            //     tracer->camera_pos_.x_ * cos(0.05) - tracer->camera_pos_.z_ * sin(0.05),
            //     tracer->camera_pos_.y_,
            //     tracer->camera_pos_.x_ * sin(0.05) + tracer->camera_pos_.z_ * cos(0.05)
            // };

            
            // tracer->camera_pos_ += center_vec;
            // // tracer->camera_direction_ = {
            // //     -tracer->camera_pos_.x_,
            // //     0,
            // //     -tracer->camera_pos_.z_ 
            // // };
            // tracer->camera_direction_ = center_vec - tracer->camera_pos_;
            // // tracer->FOV_ += M_PI / 180 * 5;
            
            // // tracer->recalc_view_plane_dist();
            // // arrow.rotation_angle_ += 0.0001 * M_PI;
            // tracer->recalc_view_plane_dist();
            // std::cout << tracer->camera_direction_.x_ << "  " << tracer->camera_direction_.y_ << "  " << tracer->camera_direction_.z_  << " direction\n";
            // std::cout << tracer->camera_pos_.x_ << "  " << tracer->camera_pos_.y_ << "  " << tracer->camera_pos_.z_  << " pos\n";
            // arrow.rotation_angle_ += 0.0001 * M_PI;

            // SDL_UpdateWindowSurface((SDL_Window*)this->rsp_);
            
            this->present();
        }
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