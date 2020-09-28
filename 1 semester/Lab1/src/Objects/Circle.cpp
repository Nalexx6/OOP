//
// Created by Win10Pro on 28.09.2020.
//

#include "Circle.h"

bool operator==(Circle a, Circle b) {

    return a._a() == b._a() && a._b() == b._b() && a._c() == b._c();

}

