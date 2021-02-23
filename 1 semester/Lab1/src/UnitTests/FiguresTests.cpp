//
// Created by Win10Pro on 2/22/2021.
//

#include "../Figures/Functions.h"
#include "../Figures/Functions.cpp"

#include "../doctest.h"

namespace testFiguresFunctions{

    //intersection
    void testLinesIntersection(){

        auto* line1 = new figures::Line(1, 1, -1);
        auto* line2 = new figures::Line(-3, 1, 2);

        std::vector<figures::Point> res = figures::intersection(*line1, *line2);

        CHECK(res.size() == 1);
        CHECK(res[0].x() == 0.75);
        CHECK(res[0].y() == 0.25);

        line2 = new figures::Line( 2, 2, -2);

        res = figures::intersection(*line1, *line2);

        //checking intersection for parallel lines
        CHECK(res.size() == 0);

    }

    void testLineCircleIntersection(){

        auto* line1 = new figures::Line(1, 1, -1);
        auto* circle1 = new figures::Circle(figures::Point(0, 0), 1);
        auto* circle2 = new figures::Circle(figures::Point(1, 1), sqrt(2) / 2);

        std::vector<figures::Point> res = figures::intersection(*line1, *circle2);

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


    }

    void testCirclesIntersection(){

        auto* circle1 = new figures::Circle(figures::Point(0, 0), 1);
        auto* circle2 = new figures::Circle(figures::Point(1, 0), 1);
        std::vector<figures::Point> res = figures::intersection(*circle1, *circle2);

        //check circles intersect in 2 points
        CHECK(res.size() == 2);
        bool point = (res[0].x() == 0.5 && (res[0].y() == sqrt(3) / 2 || res[0].y() == - sqrt(3) / 2));
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

    void testIntersection() {

        testLinesIntersection();
        testLineCircleIntersection();
        testCirclesIntersection();

    }

    //symmetric display
    void testLineToLineDisplay(){

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

    }

    void testCircleToLineDisplay(){

        auto* line1 = new figures::Line(1, 1, -1);
        auto* circle1 = new figures::Circle(figures::Point(0, 0), 1);

        figures::Circle res1 = figures::sym_display(*line1, *circle1);

        CHECK(res1.center().x() == 1);
        CHECK(res1.center().y() == 1);

    }

    void testSymDisplay(){

        testLineToLineDisplay();
        testCircleToLineDisplay();

    }

    //inversion
    void testCircleToCircleInversion(){

        auto* circle1 = new figures::Circle(figures::Point(0, 0), 1);
        auto* to_invert = new figures::Circle(figures::Point(1, 1), 0.5);

        figures::Circle inverted = figures::inversion(*circle1, *to_invert);

        figures::Circle invertedDouble = figures::inversion(*circle1, inverted);

        CHECK(to_invert->center().x() == invertedDouble.center().x());
        CHECK(to_invert->center().y() == invertedDouble.center().y());

        //this assertion will be failed if radius of to_invert circle is irrational number
        CHECK(to_invert->radius() == invertedDouble.radius());

    }

    void testLineToCircleInversion(){

        auto* circle1 = new figures::Circle(figures::Point(0, 0), 1);
        auto* to_invert = new figures::Line(1, 1, 1);

        figures::Circle inverted = figures::inversion(*circle1, *to_invert);

        figures::Line invertedDouble = figures::inversion_cross(*circle1, inverted);

        CHECK(to_invert->a() / to_invert->b() == invertedDouble.a() / invertedDouble.b());
        CHECK(to_invert->c() / to_invert->b() == invertedDouble.c() / invertedDouble.b());



    }

    void testInversion(){

        testCircleToCircleInversion();
        testLineToCircleInversion();

    }

}

TEST_CASE("[figures] - checking all functions"){

    testFiguresFunctions::testIntersection();
    testFiguresFunctions::testSymDisplay();
    testFiguresFunctions::testInversion();


}
