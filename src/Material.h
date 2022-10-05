#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "CoreLib/Utilities.hpp"

class Material {
public:
    Material(const ColorF& lambert_coeff, const ColorF& reflect_coeff, const ColorF& refract_coeff) : 
        lambert_coeff_(lambert_coeff),
        reflect_coeff_(reflect_coeff),
        refract_coeff_(refract_coeff) {}

    Material() {};
    ColorF lambert_coeff_ = {1.0, 1.0, 1.0};
    ColorF reflect_coeff_ = {2.0, 2.0, 2.0};
    ColorF refract_coeff_ = {1.0, 1.0, 1.0};
    ColorF  actual_color_ = {1.0, 1.0, 1.0};
    double refract_n_ = 1;
    bool is_transparent = false;

    void makeGlass() {
        actual_color_  = {1.0, 1.0, 1.0};
        reflect_coeff_ = {0.0, 0.0, 0.0};
        lambert_coeff_ = {0.0, 0.0, 0.0};
        refract_coeff_ = {1.0, 1.0, 1.0};
        is_transparent = true;
    }

    void makeRubber() {
        reflect_coeff_ = {0.1, 0.1, 0.1};
        refract_coeff_ = {0.0, 0.0, 0.0};
        lambert_coeff_ = {1.0, 1.0, 1.0};
        // lambert_coeff_ = {0.5, 0.5, 0.5};
    }
    
    void makeMirror() {
        actual_color_  = {1.0, 1.0, 1.0};
        reflect_coeff_ = {0.83, 0.83, 0.83};
        lambert_coeff_ = {0.1, 0.1, 0.1};
        
    }

    // ColorF diffuse_coeff_ = 
};

#endif