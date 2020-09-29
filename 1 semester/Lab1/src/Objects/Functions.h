//
// Created by Win10Pro on 24.09.2020.
//

#ifndef LAB1_FUNCTIONS_H
#define LAB1_FUNCTIONS_H

#include "Circle.h"
#include "Line.h"
#include "../doctest.h"


#include <cmath>
#include <iostream>



class Functions {

public:

    //class for keep coordinates of resulting points together
    class Point{

    public:
        double x;
        double y;

        Point() = default;
        Point(const double& x, const double& y){

            this->x= x;
            this->y = y;

        }
    };

private:

    //calculate distance between 2 points
    static double point_distance(Point& a, Point& b);

    //find the point which belongs to particular line and has the minimum distance to particular point
    static Point point_line_distance(Point& point, Line& line);

    //return the line for which particular points belong to
    static Line build_line(Point& a, Point& b);

    //create inverted image of the point
    static Point image(Circle& circle, Point& point);


public:


    //find the intersection point between 2 lines(vector is empty if line are parallel)
    static std::vector<Point> intersection(Line& line1, Line& line2);

    //find the intersection points between line and circle
    static std::vector<Point> intersection(Line& line, Circle& circle);

    //find the intersection points between 2 circles
    static std::vector<Point> intersection(Circle& circle1, Circle& circle2);

    //create the line which symmetric to particular line
    static Line sym_display(Line& line1, Line&to_sym);

    //create the circle which symmetric to particular line
    static Circle sym_display(Line& line, Circle& to_sym);

    //create inverted image of the line(which does not cross center of the circle)
    static Circle inversion(Circle& circle, Line& to_invert);

    //create inverted image of the circle(which crosses center of the "inversion"-circle)
    static Line inversion(Circle& circle, Circle& to_invert);

    //create inverted image of the circle(which does not cross center of the "inversion"-circle)
    static Circle inversion_c(Circle& circle, Circle& to_invert);


};


#endif //LAB1_FUNCTIONS_H
