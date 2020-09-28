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

Line Functions::sym_display(Line &line, Line &to_sym) {



    std::vector points = intersection(line, to_sym);


    if(points.empty()){

        return *new Line(to_sym._a(), to_sym._b(), 2 * to_sym._c() - to_sym._c());

    }

    if(line._a() == 0 || line._b() == 0){

        return *new Line(-to_sym._a(), to_sym._b(), to_sym._c());

    }

    std::cout<< "x " <<points[0].x<< " y " << points[0].y<<std::endl;

    auto* second = new Point(0, -to_sym._c() / to_sym._b());

    if(second->x == points[0].x && second->y == points[0].y){

        second = new Point(-to_sym._c() / to_sym._a(), 0);

    }

//    std::cout<< "x " <<second->x<< " y " << second->y<<std::endl;


    Point min = point_line_distance(*second, line);

    auto* display = new Point(2 * min.x - second->x, 2 * min.y - second->y);

    std::cout<< "x " <<display->x<< " y " << display->y<<std::endl;

//    res = new Line(a, b, c);
    return build_line(*display, points[0]);

}

Circle Functions::sym_display(Line &line, Circle &to_sym) {

    Circle* res;

    Point center = Point(to_sym._a(), to_sym._b());
    Point min = point_line_distance(center, line);

    return *new Circle(2 * min.x - center.x, 2 * min.y - center.y, to_sym._c());

}

Functions::Point Functions::image(Circle &circle, Functions::Point& point) {

    auto* center = new Point(circle._a(), circle._b());
    Line directive = build_line(*center, point);
    std::cout<<"center: x " << center->x << " y " << center->y <<std::endl;
    std::cout<<"directive: x " << directive._a() << " y " << directive._b() <<std::endl;



    double distance = pow(circle._c(), 2) / point_distance(*center, point);
    double norm = sqrt(pow(distance, 2) / (pow(directive._a(), 2) + pow(directive._b(), 2)));

    double x1 = center->x + directive._b() * norm;
    double y1 = center->y - directive._a() * norm;
    double x2 = center->x - directive._b() * norm;
    double y2 = center->y + directive._a() * norm;

    auto* first = new Point(x1, y1);
    auto* second = new Point(x2, y2);

    std::cout<<"first: x " << first->x << " y " << first->y <<std::endl;
    std::cout<<"second: x " << second->x << " y " << second->y <<std::endl;

    double first_dis = point_distance(*center, *first);
    double second_dis = point_distance(point, *first);

    if (first_dis > second_dis) {

        return *first;

    } else
        return *second;


}

Circle Functions::inversion(Circle &circle, Line &to_invert) {

    auto* center = new Point(circle._a(), circle._b());
    Point min = point_line_distance(*center, to_invert);
    std::cout<<"inverted: x " << min.x << " y " << min.y <<std::endl;


    Point inverted = image(circle, min);
    std::cout<<"inverted: x " << inverted.x << " y " << inverted.y <<std::endl;

    return *new Circle((center->x + inverted.x) / 2, (center->y + inverted.y) / 2, point_distance(*center, inverted) / 2);

}

Line Functions::inversion(Circle &circle, Circle &to_invert) {

    auto* first = new Point (to_invert._a(), to_invert._b() + to_invert._c());
    auto* second = new Point (to_invert._a() + to_invert._c(), to_invert._b());

    if(first->x == circle._a() && first->y == circle._b())
        first = new Point (to_invert._a(), to_invert._b() - to_invert._c());

    if(second->x == circle._a() && second->y == circle._b())
        second = new Point (to_invert._a() - to_invert._c(), to_invert._b());

    *first = image(circle, *first);
    *second = image(circle, *second);

    return build_line(*first, *second);


}

Circle Functions::inversion_c(Circle &circle, Circle &to_invert) {

    double norm = pow(circle._c(), 2) / (pow(to_invert._a() - circle._a(), 2) + pow(to_invert._b() - circle._b(), 2) - pow(to_invert._c(), 2));

    double x = circle._a() + norm * (to_invert._a() - circle._a());
    double y = circle._b() + norm * (to_invert._b() - circle._b());

    double r = std::abs(norm) * to_invert._c();

    return *new Circle(x, y, r);

}




