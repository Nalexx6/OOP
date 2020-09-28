//
// Created by Win10Pro on 24.09.2020.
//

#ifndef LAB1_LINE_H
#define LAB1_LINE_H

#include "Figure.h"

class Line : public Figure {

private:

    //variables

    double a;
    double b;
    double c;

public:



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

    //setters

//    void _a(const double& a) override { this->a = a;}
//    void _b(const double& b) override { this->b = b;}
//    void _c(const double& c) override { this->c = c;}

};


#endif //LAB1_LINE_H
