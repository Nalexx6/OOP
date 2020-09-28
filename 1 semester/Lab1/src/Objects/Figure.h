//
// Created by Win10Pro on 24.09.2020.
//

#ifndef LAB1_FIGURE_H
#define LAB1_FIGURE_H

#include <vector>

class Figure {

private:


public:

    //constructor, destructor

    Figure() = default;
    virtual ~Figure() = default;

    //getters

    virtual double _a() = 0;
    virtual double _b() = 0;
    virtual double _c() = 0;

    //setters

//    virtual void _a(const double& a) = 0;
//    virtual void _b(const double& b) = 0;
//    virtual void _c(const double& c) = 0;

};


#endif //LAB1_FIGURE_H
