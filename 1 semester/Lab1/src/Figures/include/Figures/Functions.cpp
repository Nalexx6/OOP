//
// Created by Win10Pro on 24.09.2020.
//


#include "Functions.h"

//auxiliary namespace to make contained within functions "private" for user
namespace {

    double point_distance(figures::Point &a, figures::Point &b) {

        return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));

    }

    figures::Point point_line_distance(figures::Point &point, figures::Line &line) {

        double x0 = (line.b() * (line.b() * point.x() - line.a() * point.y()) - line.a() * line.c())
                    / (pow(line.a(), 2) + pow(line.b(), 2));
        double y0 = (line.a() * (-line.b() * point.x() + line.a() * point.y()) - line.b() * line.c())
                    / (pow(line.a(), 2) + pow(line.b(), 2));

        return figures::Point(x0, y0);

    }

    figures::Line build_line(figures::Point &a, figures::Point &b) {

        return *new figures::Line(b.y() - a.y(), a.x() - b.x(),  -a.x() * b.y() + a.y() * b.x());

    }

    figures::Point image(figures::Circle &circle, figures::Point& point) {

        auto* center = new figures::Point(circle.center().x(), circle.center().y());
        figures::Line directive = build_line(*center, point);
        double distance = pow(circle.radius(), 2) / point_distance(*center, point);
        double norm = sqrt(pow(distance, 2) / (pow(directive.a(), 2) + pow(directive.b(), 2)));

        double x1 = center->x() + directive.b() * norm;
        double y1 = center->y() - directive.a() * norm;
        double x2 = center->x() - directive.b() * norm;
        double y2 = center->y() + directive.a() * norm;

        auto* first = new figures::Point(x1, y1);
        auto* second = new figures::Point(x2, y2);

        double first_dis = point_distance(*center, *first);
        double second_dis = point_distance(point, *first);

        if (first_dis > second_dis) {
            return *first;
        } else
            return *second;


    }

}

std::vector<figures::Point> figures::intersection(Line &line1, Line &line2) {

    std::vector<Point> res;

    if(line1.a() / line1.b() == line2.a() / line2.b()){
        return res;
    }

    double x = - (line1.c() * line2.b() - line1.b() * line2.c()) / (line1.a() * line2.b() - line1.b() * line2.a());
    double y = - (line1.a() * line2.c() - line1.c() * line2.a()) / (line1.a() * line2.b() - line1.b() * line2.a());

    res.emplace_back(Point(x, y));

    return res;

}

std::vector<figures::Point> figures::intersection(Line &line, Circle &circle) {

    std::vector<Point> res;

    Point center = circle.center();
    Point min = point_line_distance(center, line);
    double distance = point_distance(min, center);

    if(distance > circle.radius())
        return res;
    if(distance == circle.radius()){
        res.emplace_back(min);
        return res;
    }

    double x, y;
    double norm = sqrt( (pow(circle.radius(), 2) - pow(line.c(), 2) / ( pow(line.a(), 2) +
            pow(line.b(), 2))) / (pow(line.a(), 2) + pow(line.b(), 2)));

    x = min.x() + line.b() * norm;
    y = min.y() - line.a() * norm;
    res.emplace_back(Point(x, y));

    x = min.x() - line.b() * norm;
    y = min.y() + line.a() * norm;
    res.emplace_back(Point(x, y));

    return  res;

}

std::vector<figures::Point> figures::intersection(Circle &circle1, Circle &circle2) {

    double a = 2 * (circle1.center().x() - circle2.center().x());
    double b = 2 * (circle1.center().y() - circle2.center().y());
    double c = pow(circle2.center().x(), 2) + pow(circle2.center().y(), 2) - pow(circle2.radius(), 2) -
               (pow(circle1.center().y(), 2) - pow(circle1.center().y(), 2) - pow(circle1.radius(), 2));

    Line* line = new Line(a, b, c);

    return intersection(*line, circle1);

}

figures::Line figures::sym_display(Line &line, Line &to_sym) {

    std::vector<figures::Point> points = intersection(line, to_sym);

    if(points.empty()){
        return *new Line(to_sym.a(), to_sym.b(), 2 * to_sym.c() - to_sym.c());
    }

    if(line.a() == 0 || line.b() == 0){
        return *new Line(-to_sym.a(), to_sym.b(), to_sym.c());
    }

    auto* second = new Point(0, -to_sym.c() / to_sym.b());
    if(*second == points[0]){
        second = new Point(-to_sym.c() / to_sym.a(), 0);
    }

    Point min = point_line_distance(*second, line);
    auto* display = new Point(2 * min.x() - second->x(), 2 * min.y() - second->y());

    return build_line(*display, points[0]);

}

figures::Circle figures::sym_display(Line &line, Circle &to_sym) {

    Circle* res;

    Point center = to_sym.center();
    Point min = point_line_distance(center, line);

    return *new Circle(Point(2 * min.x() - center.x(), 2 * min.y() - center.y()), to_sym.radius());

}

figures::Circle figures::inversion(Circle &circle, Line &to_invert) {

    auto* center = new Point(circle.center().x(), circle.center().y());
    Point min = point_line_distance(*center, to_invert);

    Point inverted = image(circle, min);

    return *new Circle(Point((center->x() + inverted.x()) / 2, (center->y() + inverted.y()) / 2),
                       point_distance(*center, inverted) / 2);

}

figures::Line figures::inversion_cross(Circle &circle, Circle &to_invert) {

    auto* first = new Point (to_invert.center().x(), to_invert.center().y() + to_invert.radius());
    auto* second = new Point (to_invert.center().x() + to_invert.radius(), to_invert.center().y());

    if(*first == circle.center())
        first = new Point (to_invert.center().x(), to_invert.center().y() - to_invert.radius());

    if(*second == circle.center())
        second = new Point (to_invert.center().x() - to_invert.radius(), to_invert.center().y());

    *first = image(circle, *first);
    *second = image(circle, *second);

    return build_line(*first, *second);

}

figures::Circle figures::inversion(Circle &circle, Circle &to_invert) {

    double norm = pow(circle.radius(), 2) /
            (pow(to_invert.center().x() - circle.center().x(), 2) +
            pow(to_invert.center().y() - circle.center().y(), 2) - pow(to_invert.radius(), 2));

    double x = circle.center().x() + norm * (to_invert.center().x() - circle.center().x());
    double y = circle.center().y() + norm * (to_invert.center().y() - circle.center().y());

    double radius = std::abs(norm) * to_invert.radius();

    return *new Circle(Point(x, y), radius);

}