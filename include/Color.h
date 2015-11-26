#pragma once

#include <algorithm>

class Color {
public:
    Color(double r = 0, double g = 0, double b = 0) 
    {
        setRed(r);
        setGreen(g);
        setBlue(b);
    }

    void setRed(double r);
    void setGreen(double g);
    void setBlue(double b);

    double getRed();
    double getGreen();
    double getBlue();

    static inline double SetValid(double d);
    static inline unsigned char GetValid(double d);



    double _r;
    double _g;
    double _b;
};

