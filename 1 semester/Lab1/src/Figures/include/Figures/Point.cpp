//
// Created by Win10Pro on 2/22/2021.
//

#include "Point.h"
bool operator == (figures::Point a, figures::Point b){

    return a.x() == b.x() && a.y() == b.y();

}

bool operator==(figures::Point *a, figures::Point b) {
    return a->x() == b.x() && a->y() == b.y();
}
