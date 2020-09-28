//
// Created by Win10Pro on 24.09.2020.
//

#ifndef LAB1_LINE_H
#define LAB1_LINE_H

#include "Figure.h"

class Line : public Figure {

private:

    //variables
    //line corresponds to equation Ax + By + C = 0, variables are corresponding coefficients
    double a;
    double b;
    double c;

public:

    //constructor, destructor

    Line() = default;
    Line(const double& a, const double& b, const double& c){

        this->a = a;
        this->b = b;
        this->c = c;

    }

    ~Line() override = default;

    //getters

    double _a() override { return this->a; }
    double _b() override { return this->b; }
    double _c() override { return this->c; }



};


#endif //LAB1_LINE_H
