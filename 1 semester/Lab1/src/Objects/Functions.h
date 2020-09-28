//
// Created by Win10Pro on 24.09.2020.
//

#ifndef LAB1_FUNCTIONS_H
#define LAB1_FUNCTIONS_H

#include "Circle.h"
#include "Line.h"

#include <cmath>
#include <iostream>

class Functions {

private:


public:

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

    static double point_distance(Point& a, Point& b);

    static Point point_line_distance(Point& point, Line& line);

    static std::vector<Point> intersection(Line& line1, Line& line2);

    static std::vector<Point> intersection(Line& line, Circle& circle);

    static std::vector<Point> intersection(Circle& circle1, Circle& circle2);

    static Line build_line(Point& a, Point& b);

    static Line sym_display(Line& line1, Line& line2);

    static Circle sym_display(Line& line, Circle& circle);

//    static Point image(Circle& circle, Point);
//
//    static Figure inversion(Circle& circle, Line& line);
//
//    static Figure inversion(Circle& circle1, Circle& circle2);

};


#endif //LAB1_FUNCTIONS_H
