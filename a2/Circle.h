#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape2D.h"

using namespace std;

class Circle: public ShapeTwoD{
    private:
        int xCenter, yCenter;
        double radius;
        int topLeftX,topLeftY,btmRightX,btmRightY;
        double PI = 3.14;
    public:
        Circle(string name,bool containsWarpSpace);
        int getXCenter();
        int getYCenter();
        double getRadius();
        void setData(int x,int y, double r) override;
        string toString() override;
        double computeArea() override;
        bool isPointInShape(int x, int y) override;
        bool isPointOnShape(int x, int y) override;
};

#endif