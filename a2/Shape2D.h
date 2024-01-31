#ifndef SHAPE_2D_H
#define SHAPE_2D_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class ShapeTwoD{
    protected:
        string name;
        bool containsWarpSpace;
    public:
        ShapeTwoD(string name, bool containsWarpSpace);
        void setName(string name);
        string getName();
        void setContainsWarpSpace(bool containsWarpSpace);
        bool getContainsWarpSpace();
        virtual void setData(vector<int> x,vector<int> y){};
        virtual void setData(int x,int y, double r){};
        virtual string toString();
        virtual double computeArea(){
            return 1.0;
        };
        virtual bool isPointInShape(int x, int y){
            return false;
        };
        virtual bool isPointOnShape(int x, int y){
            return false;
        };
};

#endif