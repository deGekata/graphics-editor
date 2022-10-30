#ifndef SURFACE_HPP
#define SURFACE_HPP

class Surface_;

class Surface {
private:
    Surface_* rsp_;
public:
    Surface() = delete;
    Surface(int width, int height);

    ~Surface();



};

#endif