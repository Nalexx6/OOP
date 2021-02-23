//
// Created by Win10Pro on 28.09.2020.
//

#include "Circle.h"

bool operator==(figures::Circle a, figures::Circle b) {

    return a.center() == b.center() && a.radius() == b.radius();

}