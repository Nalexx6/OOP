//
// Created by Win10Pro on 28.09.2020.
//

#include "Line.h"

bool operator==(Line a, Line b) {

    return  a._a() == b._a() && a._b() == b._b() && a._c() == b._c();

}

