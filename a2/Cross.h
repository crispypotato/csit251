#ifndef CROSS_H
#define CROSS_H
#include "Shape2D.h"

using namespace std;

class Cross:public ShapeTwoD{
    private:
        vector<int> xVectors,yVectors;
        int xUpper,xLower,yUpper,yLower;
        double topRect,btmRect,leftRect,rightRect,centerRect;
        int topRectLength,btmRectLength,leftRectLength,rightRectLength;
        vector<int> xUpperIndex;
        int xUpperMaxY,xUpperMinY; //the higher and lower y-coordinates amongst the highest x-coordinate
        vector<int> yUpperIndex;
        int yUpperMaxX,yUpperMinX;
        vector<int> xLowerIndex;
        int xLowerMaxY,xLowerMinY;
        vector<int> yLowerIndex;
        int yLowerMaxX,yLowerMinX;
    public:
        Cross(string name,bool containsWarpSpace);
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