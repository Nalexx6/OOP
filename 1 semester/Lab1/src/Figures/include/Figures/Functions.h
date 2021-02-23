//
// Created by Win10Pro on 24.09.2020.
//

#ifndef LAB1_FUNCTIONS_H
#define LAB1_FUNCTIONS_H

#include "Circle.h"
#include "Line.h"
//#include "../doctest.h"


#include <cmath>
#include <iostream>
#include <vector>


namespace figures {

    //find the intersection point between 2 lines(vector is empty if line are parallel)
    static std::vector<Point> intersection(Line &line1, Line &line2);

    //find the intersection points between line and circle
    static std::vector<Point> intersection(Line &line, Circle &circle);

    //find the intersection points between 2 circles
    static std::vector<Point> intersection(Circle &circle1, Circle &circle2);

    //create the line which symmetric to particular line
    static Line sym_display(Line &line1, Line &to_sym);

    //create the circle which symmetric to particular line
    static Circle sym_display(Line &line, Circle &to_sym);

    //create inverted image of the line(which does not cross center of the circle)
    static Circle inversion(Circle &circle, Line &to_invert);

    //create inverted image of the circle(which crosses center of the "inversion"-circle)
    static Line inversion_cross(Circle &circle, Circle &to_invert);

    //create inverted image of the circle(which does not cross center of the "inversion"-circle)
    static Circle inversion(Circle &circle, Circle &to_invert);

}


#endif //LAB1_FUNCTIONS_H
