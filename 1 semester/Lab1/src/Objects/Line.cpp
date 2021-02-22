//
// Created by Win10Pro on 28.09.2020.
//

#include "Line.h"

bool operator==(figures::Line a, figures::Line b) {

    return  a.a() == b.a() && a.b() == b.b() && a.c() == b.c();

}

