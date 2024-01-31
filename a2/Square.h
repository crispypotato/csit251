#ifndef SQUARE_H
#define SQUARE_H
#include "Shape2D.h"

using namespace std;

class Square:public ShapeTwoD{
    private:
        vector<int> xVectors,yVectors;
        int xUpper,xLower,yUpper,yLower;
    public:
        Square(string name,bool containsWarpSpace);
        int getXUpper();
        int getXLower();
        int getYUpper();
        int getYLower();
        void setData(vector<int> x,vector<int> y) override;
        virtual string toString() override;
        virtual double computeArea() override;
        virtual bool isPointInShape(int x, int y) override;
        virtual bool isPointOnShape(int x, int y) override;
};

#endif