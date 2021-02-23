//
// Created by Win10Pro on 24.09.2020.
//

#ifndef LAB1_LINE_H
#define LAB1_LINE_H

namespace figures {

    class Line {

    private:

        //line corresponds to equation Ax + By + C = 0, variables are corresponding coefficients
        double _a{};
        double _b{};
        double _c{};

    public:

        //constructor, destructor

        Line() = default;

        Line(const double &a, const double &b, const double &c) {

            this->_a = a;
            this->_b = b;
            this->_c = c;

        }

        ~Line()= default;

        //getters

        [[nodiscard]] double a() const { return this->_a; }
        [[nodiscard]] double b() const{ return this->_b; }
        [[nodiscard]] double c() const { return this->_c; }

    };


}

bool operator==(figures::Line a, figures::Line b);

#endif //LAB1_LINE_H
