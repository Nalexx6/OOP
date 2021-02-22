//
// Created by Win10Pro on 24.09.2020.
//


#include "Functions.h"

namespace {

    double point_distance(figures::Point &a, figures::Point &b) {

        return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));

    }

    figures::Point point_line_distance(figures::Point &point, figures::Line &line) {

//    figures::Point res{};

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
//    std::cout<<"center: x " << center->x << " y " << center->y <<std::endl;
//    std::cout<<"directive: x " << directive._a() << " y " << directive._b() <<std::endl;



        double distance = pow(circle.radius(), 2) / point_distance(*center, point);
        double norm = sqrt(pow(distance, 2) / (pow(directive.a(), 2) + pow(directive.b(), 2)));

        double x1 = center->x() + directive.b() * norm;
        double y1 = center->y() - directive.a() * norm;
        double x2 = center->x() - directive.b() * norm;
        double y2 = center->y() + directive.a() * norm;

        auto* first = new figures::Point(x1, y1);
        auto* second = new figures::Point(x2, y2);

//    std::cout<<"first: x " << first->x << " y " << first->y <<std::endl;
//    std::cout<<"second: x " << second->x << " y " << second->y <<std::endl;

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

//    std::cout<<"Center "<<center.x << " "<< center.y <<"\n";


    Point min = point_line_distance(center, line);

//    std::cout<<"Nearest point "<<min.x << " "<< min.y <<"\n";

    double distance = point_distance(min, center);

    if(distance > circle.radius())
        return res;

    if(distance == circle.radius()){

        res.emplace_back(min);
        return res;

    }

    double x, y;
    //    std::cout<<"distance "<< distance << "\n";

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


    std::vector points = intersection(line, to_sym);

    if(points.empty()){

        return *new Line(to_sym.a(), to_sym.b(), 2 * to_sym.c() - to_sym.c());

    }

    if(line.a() == 0 || line.b() == 0){

        return *new Line(-to_sym.a(), to_sym.b(), to_sym.c());

    }

//    std::cout<< "x " <<points[0].x<< " y " << points[0].y<<std::endl;

    auto* second = new Point(0, -to_sym.c() / to_sym.b());

    if(*second == points[0]){

        second = new Point(-to_sym.c() / to_sym.a(), 0);

    }

//    std::cout<< "x " <<second->x<< " y " << second->y<<std::endl;


    Point min = point_line_distance(*second, line);

    auto* display = new Point(2 * min.x() - second->x(), 2 * min.y() - second->y());

//    std::cout<< "x " <<display->x<< " y " << display->y<<std::endl;

//    res = new Line(a, b, c);
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
//    std::cout<<"inverted: x " << min.x << " y " << min.y <<std::endl;


    Point inverted = image(circle, min);
//    std::cout<<"inverted: x " << inverted.x << " y " << inverted.y <<std::endl;

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



namespace test_figures_figures{

    void test_intersection() {

        figures::Line* line1 = new figures::Line(1, 1, -1);
        figures::Line* line2 = new figures::Line(-3, 1, 2);

        std::vector<figures::Point> res = figures::intersection(*line1, *line2);

        CHECK(res.size() == 1);
        CHECK(res[0].x() == 0.75);
        CHECK(res[0].y() == 0.25);

        line2 = new figures::Line( 2, 2, -2);

        res = figures::intersection(*line1, *line2);

        //checking intersection for parallel lines
        CHECK(res.size() == 0);

        auto* circle1 = new figures::Circle(figures::Point(0, 0), 1);
        auto* circle2 = new figures::Circle(figures::Point(1, 1), sqrt(2) / 2);

        res = figures::intersection(*line1, *circle2);

        //checking the line is tangent
        CHECK(res.size() == 1);
        CHECK(res[0].x() == 0.5);
        CHECK(res[0].y() == 0.5);

        res = figures::intersection(*line1, *circle1);

        //check the line crosses the circle in 2 points
        CHECK(res.size() == 2);
        bool point = (res[0].x() == 1 && res[0].y() == 0) || (res[0].x() == 0 && res[0].y() == 1);
        CHECK(point);
        point = (res[1].x() == 1 && res[1].y() == 0) || (res[1].x() == 0 && res[1].y() == 1);
        CHECK(point);

        circle2 = new figures::Circle(figures::Point(1, 0), 1);
        res = figures::intersection(*circle1, *circle2);

        //check circles intersect in 2 points
        CHECK(res.size() == 2);
        point = (res[0].x() == 0.5 && (res[0].y() == sqrt(3) / 2 || res[0].y() == - sqrt(3) / 2));
        CHECK(point);
        point = (res[1].x() == 0.5 && (res[1].y() == sqrt(3) / 2 || res[1].y() == - sqrt(3) / 2));
        CHECK(point);

        circle2 = new figures::Circle(figures::Point(2, 0), 1);
        res = figures::intersection(*circle1, *circle2);

        //check circles are tangent
        CHECK(res.size() == 1);
        point = (res[0].x() == 1 && res[0].y() == 0);
        CHECK(point);




    }
    void test_sym_display(){

        auto* line1 = new figures::Line(1, 1, -1);
        auto* line2 = new figures::Line(-3, 1, 2);

        figures::Line res = figures::sym_display(*line1, *line2);

        //check symmetric display(lines intersects)
        CHECK(res.a() / res.b() == double (-1) / 3);
        CHECK(res.c() == 0);

        line2 = new figures::Line(2, 2, -3);

        res = figures::sym_display(*line1, *line2);
        //check symmetric display(lines parallel)
        CHECK(res.a() / res.b() == line1->a() / line1->b());

        auto* circle1 = new figures::Circle(figures::Point(0, 0), 1);

        figures::Circle res1 = figures::sym_display(*line1, *circle1);

        CHECK(res1.center().x() == 1);
        CHECK(res1.center().y() == 1);



    }
    void test_inversion(){



    }

}

TEST_CASE("[figures] - checking all figures"){

    test_figures_figures::test_intersection();
    test_figures_figures::test_sym_display();
    test_figures_figures::test_inversion();

}




