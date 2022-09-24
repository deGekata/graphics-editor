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

class MyWindow : public Window {
public:
    MyWindow(int width = 800, int height = 600, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, uint32_t flags = 0) :
        Window(width, height, x, y, flags)
    {
        scene = new GraphicsScene();

        rect1 = new GraphicsRectangleItem(Point(0, 0));
        rect1->rotation_angle_ = 0.1 * M_PI, rect1->parent_delta_coords_ = {100, 100};

        rect2 = new GraphicsRectangleItem(Point(500, 200));

        // a не кринж иметь такое:
        // GraphicsScene scene = new GraphicsScene();
        // Event::connect((void*)scene, scene->mouseClickEvent, some_random_event_func);
        //scene->mouseClickEvent это void mouseClickEvent(Event* event)
        dot_rect = new DottedRectangle (Point(0, 0));
        dot_rect->parent_delta_coords_ = {200, 200};

        arrow = new GraphicsArrow(Point(0, 0));

        scene->items.push_back(arrow);
        scene->items.push_back(rect1);
        scene->items.push_back(rect2);
        scene->items.push_back(dot_rect);

        dot_rect->addChild(arrow, Point(0, 0));
        rect1->addChild(rect2, Point(-200, 100));
        rect1->addChild(dot_rect, Point(200, 200));
        
    }

    void exec() {
        bool isRunning = true;
        bool invert_coord = true;

        SDL_Event event; 



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
            while (SDL_PollEvent(&event)) {
                // printf("lo1");
                switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:{
                    Point mouse_p;
                    int x, y;
                    Transformation trnsfrm = arrow->absTransformFromParent();
                    SDL_GetMouseState(&x, &y);
                    std::cout << "af tranfrom " << trnsfrm * Point(x, y) << "  \n";
                    arrow->rect_.p2_ = trnsfrm * Point(x, y);
                    arrow->rect_.p1_ = -arrow->rect_.p2_;
                    break;
                }

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        isRunning = false;
                        break;
                    }

                    if (event.key.keysym.sym == SDLK_CAPSLOCK) {
                        invert_coord = !invert_coord;
                    }
                    break;
                default:
                    break;
                }
            }
            painter_->setColor(255, 0, 0);
            painter_->fillWindow();

            painter_->setColor(255, 255, 255);
            painter_->drawLine(320, 200, 300, 240);
            painter_->drawLine(300, 240, 340, 240);
            painter_->drawLine(340, 240, 320, 200);

            scene->repaint(painter_);

            if (invert_coord) {
                ss.drawVec(painter_->painter_, ss2, line); 
            } else {
                ss.drawVec(painter_->painter_, ss1, line);
            }
            painter_->present();
            rect1->rotation_angle_ += 0.0001 * M_PI;
            dot_rect->rotation_angle_ += 0.0001 * M_PI;
            // arrow.rotation_angle_ += 0.0001 * M_PI;
        }
    }

    void setPainter(Painter* painter) {
        if (painter != NULL)
            painter_ = painter;
    }

    void drawSphere(const Point& center, const Point& radius); 

    GraphicsScene* scene;
    GraphicsRectangleItem* rect1;
    GraphicsRectangleItem* rect2;
    DottedRectangle* dot_rect;
    GraphicsArrow* arrow;
    Painter* painter_;
};

#endif