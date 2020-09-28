//
// Created by Win10Pro on 24.09.2020.
//

#include "Functions.h"

double Functions::point_distance(Functions::Point &a, Functions::Point &b) {

    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));

}

Functions::Point Functions::point_line_distance(Functions::Point &point, Line &line) {

    Point res{};

    res.x = (line._b() * ( line._b() * point.x - line._a() * point.y) - line._a() * line._c())
            / (pow(line._a(), 2) + pow(line._b(), 2));

    res.y = (line._a() * ( -line._b() * point.x + line._a() * point.y) - line._b() * line._c())
            / (pow(line._a(), 2) + pow(line._b(), 2));

    return res;

}

std::vector<Functions::Point> Functions::intersection(Line &line1, Line &line2) {

    std::vector<Point> res;

    if(line1._a() / line1._b() == line2._a() / line2._b()){

        return res;

    }

    double x = - (line1._c() * line2._b() - line1._b() * line2._c()) / (line1._a() * line2._b() - line1._b() * line2._a());
    double y = - (line1._a() * line2._c() - line1._c() * line2._a()) / (line1._a() * line2._b() - line1._b() * line2._a());

    res.emplace_back(Point(x, y));

    return res;

}

std::vector<Functions::Point> Functions::intersection(Line &line, Circle &circle) {

    std::vector<Point> res;

    Point center = Point(circle._a(), circle._b());

    std::cout<<"Center "<<center.x << " "<< center.y <<"\n";


    Point min = point_line_distance(center, line);

    std::cout<<"Nearest point "<<min.x << " "<< min.y <<"\n";

    double distance = point_distance(min, center);

    if(distance > circle._c())
        return res;

    if(distance == circle._c()){

        res.emplace_back(min);
        return res;

    }

    Point first{}, second{};
    std::cout<<"distance "<< distance << "\n";

    double norm = sqrt( (pow(circle._c(), 2) - pow(line._c(), 2) / ( pow(line._a(), 2) + pow(line._b(), 2))) /
                                (pow(line._a(), 2) + pow(line._b(), 2)));

    first.x = min.x + line._b() * norm;
    first.y = min.y - line._a() * norm;

    second.x = min.x - line._b() * norm;
    second.y = min.y + line._a() * norm;

    res.emplace_back(first);
    res.emplace_back(second);

    return  res;

}

std::vector<Functions::Point> Functions::intersection(Circle &circle1, Circle &circle2) {

    double a = 2 * (circle1._a() - circle2._a());
    double b = 2 * (circle1._b() - circle2._b());
    double c = pow(circle2._a(), 2) + pow(circle2._b(), 2) - pow(circle2._c(), 2) -
               (pow(circle1._a(), 2) - pow(circle1._b(), 2) - pow(circle1._c(), 2));

    Line* line = new Line(a, b, c);

    return intersection(*line, circle1);

}

Line Functions::build_line(Functions::Point &a, Functions::Point &b) {

    return *new Line(b.y - a.y, a.x - b.x,  -a.x * b.y + a.y * b.x);

}

Line Functions::sym_display(Line &line1, Line &line2) {



    std::vector points = intersection(line1, line2);


    if(points.empty()){

        return *new Line(line2._a(), line2._b(), 2 * line1._c() - line2._c());

    }

    if(line1._a() == 0 || line1._b() == 0){

        return *new Line(-line2._a(), line2._b(), line2._c());

    }

    std::cout<< "x " <<points[0].x<< " y " << points[0].y<<std::endl;

    auto* second = new Point(0, -line2._c() / line2._b());

    if(second->x == points[0].x && second->y == points[0].y){

        second = new Point(-line2._c() / line2._a(), 0);

    }

//    std::cout<< "x " <<second->x<< " y " << second->y<<std::endl;


    Point min = point_line_distance(*second, line1);

    Point* display = new Point(2 * min.x - second->x, 2 * min.y - second->y);

    std::cout<< "x " <<display->x<< " y " << display->y<<std::endl;

//    res = new Line(a, b, c);
    return build_line(*display, points[0]);

}

Circle Functions::sym_display(Line &line, Circle &circle) {

    Circle* res;

    Point center = Point(circle._a(), circle._b());
    Point min = point_line_distance(center, line);

    res = new Circle(2 * min.x - center.x, 2 * min.y - center.y, circle._c());
    return *res;

}

