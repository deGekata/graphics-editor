#include <iostream> 
#include "vectord_2d.hpp"
#include "GraphicsItem.hpp"
#include "Painter.hpp"
#include "Window.hpp"
#include "GraphicsScene.hpp"
#include "RectangleItem.hpp"
#include "DottedRectangle.hpp"
#include "Arrow.hpp"

int main(int argv, char** args) {

    Window::startGraphicalLib();

    Window window;
    Painter painter(window);
    
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

    GraphicsScene scene;
    GraphicsRectangleItem rect1(Point(0, 0));
    // rect1.rotation_angle_ = 0.1 * M_PI;
    rect1.parent_delta_coords_ = {100, 100};
    GraphicsRectangleItem rect2(Point(500, 200));
    DottedRectangle dot_rect(Point(0, 0));
    dot_rect.parent_delta_coords_ = {200, 200};
    GraphicsArrow arrow(Point(0, 0));
    scene.items.push_back(&arrow);
    rect1.addChild(&arrow, Point(0, 0));
    rect1.addChild(&rect2, Point(-200, 100));
    rect1.addChild(&dot_rect, Point(200, 200));
    scene.items.push_back(&rect1);
    scene.items.push_back(&rect2);
    scene.items.push_back(&dot_rect);
    std::cout << rect1.absTransformToParent() << '\n';
    std::cout << rect2.transformOnParent() << '\n';
    std::cout << rect2.absTransformToParent() << '\n';
    
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
                Transformation trnsfrm = arrow.absTransformFromParent();
                std::cout << trnsfrm << " transformer\n";
                SDL_GetMouseState(&x, &y);
                std::cout << "af tranfrom " << trnsfrm * Point(x, y) << "  \n";
                arrow.rect_.p2_ = trnsfrm * Point(x, y);
                printf(" x %d  y %d \n", x, y);
                arrow.rect_.p1_ = -arrow.rect_.p2_;
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
        painter.setColor(255, 0, 0);
        painter.fillWindow();

        painter.setColor(255, 255, 255);
        painter.drawLine(320, 200, 300, 240);
        painter.drawLine(300, 240, 340, 240);
        painter.drawLine(340, 240, 320, 200);

        scene.repaint(&painter);

        if (invert_coord) {
            ss.drawVec(painter.painter_, ss2, line); 
        } else {
            ss.drawVec(painter.painter_, ss1, line);
        }
        painter.present();
        rect1.rotation_angle_ += 0.0001 * M_PI;
        dot_rect.rotation_angle_ += 0.0001 * M_PI;
        // arrow.rotation_angle_ += 0.0001 * M_PI;
    }

    Window::stopGraphicalLib();
    SDL_Quit();
    
    
    // itm_child.parent_base_point = {0, 0};
    // itm_child.rotation_angle_ = -1 * M_PI;
    // std::cout << itm_child.mapOnParent({1, 2}) << " fs\n";
    return 0;
}

