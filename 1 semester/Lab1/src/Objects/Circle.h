//
// Created by Win10Pro on 24.09.2020.
//

#ifndef LAB1_CIRCLE_H
#define LAB1_CIRCLE_H

#include "Figure.h"

class Circle : public Figure {

    //variables
    double x0{};
    double y0{};
    double radius{};

public:

    //constructor, destructor

    Circle() = default;
    explicit Circle(const double& x, const double& y, const double& radius){

        this->x0 = x;
        this->y0 = y;
        this->radius = radius;

    }

    ~Circle() override = default;

    //getters

    double _a() override { return this->x0; }
    double _b() override { return this->y0; }
    double _c() override { return this->radius; }

    //setters




};


#endif //LAB1_CIRCLE_H
