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
    tracer = new RayTracerWidget(RectF(0, 0, 300, 300), PointF(0, 0));
    
    //------------------- Light-source --------------------------
    sphere1 = new Sphere(Vector3D(-100, 50, 400), 50);
    sphere1->is_light_source_ = true;
    sphere1->color_ = ColorF(255, 255, 0);
    tracer->add_item(sphere1);

    Sphere* sphere3 = new Sphere(Vector3D(-100, 100, 300), 60);
    // sphere3->is_light_source_ = true;
    sphere3->color_ = ColorF(0, 159, 37);
    sphere3->color_ = ColorF(100, 220, 220);
    tracer->add_item(sphere3);

    Triangle* triangle = new Triangle(Vector3D(-100, -100, 200), Vector3D(-100, 100, 200), Vector3D(0, 0, 300));
    triangle->color_ = ColorF(0.5, 0.5, 0.5);
    // triangle->is_light_source_ = true;
    // tracer->add_item(triangle);

    //------------------- Not light-source ---------------------------
    Sphere* sphere2 = new Sphere(Vector3D( 0, 0, 600), 100);
    sphere2->is_light_source_ = false;
    sphere2->color_ = ColorF(0, 0, 0);
    tracer->add_item(sphere2);

    //-----------------------------------------------------
    

    
    //-----------------------------------------------------
    // Plane* plane1 = new Plane(Vector3D(0, 0, 300), Vector3D(-1.0, 0, -1.0));
    // plane1->color_ = ColorF(0.0, 255.0, 255.);
    // plane1->is_light_source_ = true;
    // plane1->albedo_ = 4;
    // tracer->add_item(plane1);
    
    //-----------------------------------------------------
    // Plane* plane2 = new Plane(Vector3D(0, 0, -300), Vector3D(-1.0, 0, -1.0));
    // plane2->color_ = ColorF(0.0, 1.0, 0.0);
    // plane2->albedo_ = 5;
    // plane2->is_light_source_ = true;
    // tracer->add_item(plane2);
    
    //--------------------Walls--------------------

    Plane* floor =   new Plane(Vector3D(0,  300, 0), Vector3D(0, -1, 0));
    Plane* ceil =    new Plane(Vector3D(0, -200, 0), Vector3D(0, -1, 0));

    Plane* wall_lf = new Plane(Vector3D(-300, 0, 0), Vector3D(-1, 0, 0));
    Plane* wall_rh = new Plane(Vector3D( 300, 0, 0), Vector3D(-1, 0, 0));

    Plane* wall_fr = new Plane(Vector3D(0, 0,  1000), Vector3D(0, 0,  -1));
    Plane* wall_bk = new Plane(Vector3D(0, 0, -400), Vector3D(0, 0,  1));
    // ceil->is_light_source_  = true;
    // floor->is_light_source_ = true;
    wall_bk->is_light_source_ = true;
    // wall_fr->is_light_source_ = true;   
    // wall_rh->is_light_source_ = true;
    // wall_lf->is_light_source_ = true;   

    tracer->add_item(floor), floor->color_ = ColorF(101, 98, 141);
    tracer->add_item(ceil),  ceil->color_  = ColorF(234, 100, 99);
    

    tracer->add_item(wall_lf), wall_lf->color_ = ColorF(248, 177, 194);
    tracer->add_item(wall_rh), wall_rh->color_ = ColorF(248, 177, 194);
    tracer->add_item(wall_fr), wall_fr->color_ = ColorF(75, 106, 137);
    tracer->add_item(wall_bk), wall_bk->color_ = ColorF(75, 106, 137);
    // tracer->add_item(wall_bk), wall_bk->color_ = ColorF(255, 255, 255);
    // tracer->add_item(wall_lf), wall_lf->color_ = ColorF(255, 255, 255);
    // tracer->add_item(wall_rh), wall_rh->color_ = ColorF(255, 255, 255);
    // tracer->add_item(wall_fr), wall_fr->color_ = ColorF(255, 255, 255);
    

    //-------------------Walls end-----------------


    // tracer->trace_ray(Ray(Vector3D(0, 0, 0), Vector3D(-0.40824829046386307, -0.40824829046386307, 0.81649658092772592)), 0);
    // scene->items.push_back(tracer);
}