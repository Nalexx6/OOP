//
// Created by Win10Pro on 24.09.2020.
//

#ifndef LAB1_CIRCLE_H
#define LAB1_CIRCLE_H

#include "Point.h"
namespace figures {

    class Circle {

        //variables
        Point _center{};
        double _radius{};

    public:

        //constructor, destructor

        Circle() = default;

        explicit Circle(const Point& center, const double &radius) {

            this->_center = center;
            this->_radius = radius;

        }

        ~Circle() = default;

        //getters

        [[nodiscard]] Point center() const { return this->_center; }
        [[nodiscard]] double radius() const { return this->_radius; }

    };

}

bool operator == (figures::Circle a, figures::Circle b);





#endif //LAB1_CIRCLE_H
