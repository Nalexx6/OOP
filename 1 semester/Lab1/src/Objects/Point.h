//
// Created by Win10Pro on 2/22/2021.
//

#ifndef LAB1_POINT_H
#define LAB1_POINT_H

namespace figures {

    class Point {

        double _x;
        double _y;

    public:

        Point() = default;

        Point(const double &x, const double &y) {

            this->_x = x;
            this->_y = y;

        }

        [[nodiscard]] double x() const{return _x;}
        [[nodiscard]] double y() const{return _y;}

    };


}
bool operator == (figures::Point a, figures::Point b);

bool operator == (figures::Point* a, figures::Point b);


#endif //LAB1_POINT_H
