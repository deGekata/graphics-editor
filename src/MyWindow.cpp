#include "MyWindow.hpp"



MyWindow::MyWindow(int width, int height, int x, int y, uint32_t flags) :
    Window(width, height, x, y, flags)
{
    scene = new GraphicsScene();
    
    rect1 = new GraphicsRectangleItem(PointF(0, 0));
    rect1->rotation_angle_ = 0.1 * M_PI, rect1->parent_delta_coords_ = {100, 100};

    rect2 = new GraphicsRectangleItem(PointF(500, 200));

    // a не кринж иметь такое:
    // GraphicsScene scene = new GraphicsScene();
    // Event::connect((void*)scene, scene->mouseClickEvent, some_random_event_func);
    //scene->mouseClickEvent это void mouseClickEvent(Event* event)
    dot_rect = new DottedRectangle (PointF(0, 0));
    dot_rect->parent_delta_coords_ = {200, 200};

    arrow = new GraphicsArrow(PointF(0, 0));

    scene->items.push_back(arrow);
    scene->items.push_back(rect1);
    scene->items.push_back(rect2);
    scene->items.push_back(dot_rect);

    dot_rect->addChild(arrow, PointF(0, 0));
    rect1->addChild(rect2, PointF(-200, 100));
    rect1->addChild(dot_rect, PointF(200, 200));



    tracer = new RayTracerWidget(Rect(0, 0, 400, 400), Point(0, 0));
    tracer2 = new RayTracerWidget(Rect(0, 0, 400, 400), Point(0, 0));
    central_widget_->addChild(tracer, {400, 400});
    central_widget_->addChild(tracer2, {0, 0});


    //------------------- Light-source --------------------------
    // sphere1 = new Sphere(Vector3D(1, 1, 1), 100);
    sphere1 = new Sphere(Vector3D(200, 0, 400), 50);
    // sphere1 = new Sphere(Vector3D(200, 50, 400), 50);
    // sphere1->is_light_source_ = true;
    sphere1->material.actual_color_ = ColorF(255/255.0, 255/255.0, 255/255.0); // #ffffff
    sphere1->material.makeGlass();
    sphere1->material.refract_n_ = 2;
    tracer->add_item(sphere1);
    tracer2->add_item(sphere1);

    Sphere* sphere3 = new Sphere(Vector3D(-50, 0, 300), 60);
    // Sphere* sphere3 = new Sphere(Vector3D(-100, 100, 300), 60);
    // sphere3->is_light_source_ = true;
    // sphere3->material.actual_color_ = ColorF(0, 159, 37);
    sphere3->material.actual_color_ = ColorF(100/255.0, 220/255.0, 220/255.0); // #64dcdc
    sphere3->material.makeRubber();
    // sphere3->material.makeMirror();
    tracer->add_item(sphere3);
    tracer2->add_item(sphere3);

    Triangle* triangle = new Triangle(Vector3D(-100, -100, 200), Vector3D(-100, 100, 200), Vector3D(100, 0, 500));
    triangle->material.actual_color_ = ColorF(0.5, 0.5, 0.5);
    triangle->material.makeGlass();
    triangle->material.refract_n_ = 2;
    // triangle->material.makeRubber();
    // triangle->is_light_source_ = true;
    tracer->add_item(triangle);
    tracer2->add_item(triangle);

    //------------------- Not light-source ---------------------------
    Sphere* sphere2 = new Sphere(Vector3D( 0, 0, 300), 70);
    sphere2->is_light_source_ = false;
    sphere2->material.makeMirror();
    sphere2->material.actual_color_ = ColorF(120, 100, 15); // #78640F
    tracer->add_item(sphere2);
    tracer2->add_item(sphere2);

    //-----------------------------------------------------
    
    
    //--------------------Walls--------------------

    Plane* floor =   new Plane(Vector3D(0,  500, 0), Vector3D(0, -1, 0));
    Plane* ceil =    new Plane(Vector3D(0, -500, 0), Vector3D(0, -1, 0));

    Plane* wall_lf = new Plane(Vector3D(-700, 0, 0), Vector3D(-1, 0, 0));
    Plane* wall_rh = new Plane(Vector3D( 700, 0, 0), Vector3D(-1, 0, 0));

    Plane* wall_fr = new Plane(Vector3D(0, 0,  2000), Vector3D(0, 0, 1));
    Plane* wall_bk = new Plane(Vector3D(0, 0, -1000), Vector3D(0, 0,  1));
    ceil->is_light_source_  = true;
    // floor->is_light_source_ = true;
    wall_bk->is_light_source_ = true;
    // wall_fr->is_light_source_ = true;   
    // wall_rh->is_light_source_ = true;
    // wall_lf->is_light_source_ = true;   

    tracer->add_item(floor), floor->material.actual_color_ = ColorF(101/255.0, 98/255.0, 141/255.0), floor->material.makeRubber(); //#65628d
    tracer2->add_item(floor), floor->material.actual_color_ = ColorF(101/255.0, 98/255.0, 141/255.0), floor->material.makeRubber(); //#65628d
    tracer->add_item(ceil),  ceil->material.actual_color_  = ColorF(234/255.0, 100/255.0, 99/255.0), ceil->material.makeRubber();
    tracer2->add_item(ceil),  ceil->material.actual_color_  = ColorF(234/255.0, 100/255.0, 99/255.0), ceil->material.makeRubber();
    

    tracer->add_item(wall_lf), wall_lf->material.actual_color_ = ColorF(1.0, 1.0, 1.0), wall_lf->material.makeRubber(), wall_lf->is_light_source_ = true; //#ffffff
    tracer2->add_item(wall_lf), wall_lf->material.actual_color_ = ColorF(1.0, 1.0, 1.0), wall_lf->material.makeRubber(), wall_lf->is_light_source_ = true; //#ffffff
    // tracer->add_item(wall_lf), wall_lf->material.actual_color_ = ColorF(248/255.0, 177/255.0, 194/255.0), wall_lf->material.makeRubber(); //#f8b1c2
    tracer->add_item(wall_rh), wall_rh->material.actual_color_ = ColorF(255 / 255.0, 255 / 255.0, 255 / 255.0), wall_rh->material.makeRubber(); //#ffffff
    tracer2->add_item(wall_rh), wall_rh->material.actual_color_ = ColorF(255 / 255.0, 255 / 255.0, 255 / 255.0), wall_rh->material.makeRubber(); //#ffffff
    // tracer->add_item(wall_rh), wall_rh->material.actual_color_ = ColorF(248 / 255.0, 177 / 255.0, 194 / 255.0), wall_rh->material.makeRubber(); //#f8b1c2
    // tracer->add_item(wall_fr), wall_fr->material.actual_color_ = ColorF(1.0, 1.0, 1.0), wall_fr->material.makeRubber(); //#ffffff
    // tracer->add_item(wall_fr), wall_fr->material.actual_color_ = ColorF(255, 255, 255), wall_fr->material.makeRubber(); //#
    tracer->add_item(wall_fr), wall_fr->material.actual_color_ = ColorF(75.0/255, 106.0/255, 137.0/255), wall_fr->material.makeRubber(); //#4b6a89
    tracer2->add_item(wall_fr), wall_fr->material.actual_color_ = ColorF(1.0, 1.0, 1.0), wall_fr->material.makeRubber(); //#4b6a89
    tracer->add_item(wall_bk), wall_bk->material.actual_color_ = ColorF(255 / 255.0, 255 / 255.0, 255 / 255.0), wall_bk->material.makeRubber(); //#ffffff
    tracer2->add_item(wall_bk), wall_bk->material.actual_color_ = ColorF(1.0, 1.0, 1.0), wall_bk->material.makeRubber(); //#ffffff
    // tracer->add_item(wall_bk), wall_bk->material.actual_color_ = ColorF(248 / 255.0, 177 / 255.0, 194 / 255.0), wall_bk->material.makeRubber(); //#f8b1c2
    // tracer->add_item(wall_bk), wall_bk->material.actual_color_ = ColorF(75, 106, 137), wall_bk->material.makeRubber(); //#4b6a89
    // wall_fr->is_light_source_ = true;
    // wall_bk->is_light_source_ = true;
    // wall_rh->is_light_source_ = true;
    // tracer->add_item(wall_bk), wall_bk->color_ = ColorF(255, 255, 255);
    // tracer->add_item(wall_lf), wall_lf->color_ = ColorF(255, 255, 255);
    // tracer->add_item(wall_rh), wall_rh->color_ = ColorF(255, 255, 255);
    // tracer->add_item(wall_fr), wall_fr->color_ = ColorF(255, 255, 255);
    
    // tracer->add_item(wall_bk), wall_bk->material.actual_color_ = ColorF(75, 106, 137); //#4b6a89

    // tracer->add_item(wall_bk), wall_bk->material.actual_color_ = ColorF(75, 106, 137);


    //-------------------Walls end-----------------


    // tracer->trace_ray(Ray(Vector3D(0, 0, 0), Vector3D(-0.40824829046386307, -0.40824829046386307, 0.81649658092772592)), 0);
    // scene->items.push_back(tracer);
    center_vec = (sphere1->base_point_ + sphere2->base_point_ + sphere3->base_point_) / 3 ;
}