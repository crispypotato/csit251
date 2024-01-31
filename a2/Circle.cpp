#include "Circle.h"
#include <iomanip>

Circle::Circle(string name,bool containsWarpSpace):ShapeTwoD(name,containsWarpSpace){
    
}

int Circle::getXCenter(){
    return xCenter;
}
int Circle::getYCenter(){
    return yCenter;
}
double Circle::getRadius(){
    return radius;
}
void Circle::setData(int x,int y, double r){
    this->xCenter = x;
    this->yCenter = y;
    this->radius = r;
    topLeftX = x-radius;
    topLeftY = y+radius;
    btmRightX = x+radius;
    btmRightY = y-radius;
}

double Circle::computeArea(){
    return PI*radius*radius;
}
bool Circle::isPointInShape(int x,int y){
    if((x>topLeftX && x<btmRightX)&&(y>btmRightY && y<topLeftY)){
        return true;
    }else{
        return false;
    }
}
bool Circle::isPointOnShape(int x,int y){
    if((x==getXCenter() && (y==topLeftY || y==btmRightY))||(y==getYCenter() && (x==topLeftX || x==btmRightX))){
        return true;
    }else{
        return false;
    }
}
string Circle::toString(){
    ostringstream oss;
    string ptInShape,ptOnShape;
    oss << ShapeTwoD::toString();
    oss << "Area: " << setprecision(2) << fixed << computeArea() << " units square\nVertices: none!\n\n";
    oss << "Points on perimeter: ";
    for(int i=topLeftX;i<=btmRightX;i++){
        for(int j=btmRightY;j<=topLeftY;j++){
            if(isPointOnShape(i,j)==true){
                if(ptOnShape.empty()){
                    ptOnShape+="(" + to_string(i) + ", " + to_string(j) + ")";
                }else{
                    ptOnShape+=", (" + to_string(i) + ", " + to_string(j) + ")";
                }
            }
        }
    }
    if(ptOnShape.empty()==false){
        oss << ptOnShape << "\n\n";
    }else{
        oss << "none!\n\n";
    }
    oss << "Points within shape: ";
    for(int i=topLeftX;i<=btmRightX;i++){
        for(int j=btmRightY;j<=topLeftY;j++){
            if(isPointInShape(i,j)==true){
                if(ptInShape.empty()){
                    ptInShape+="(" + to_string(i) + ", " + to_string(j) + ")";
                }else{
                    ptInShape+=", (" + to_string(i) + ", " + to_string(j) + ")";
                }
            }
        }
    }
    if(ptInShape.empty()==false){
        oss << ptInShape << "\n\n";
    }else{
        oss << "none!\n\n";
    }
    string s = oss.str();
    return s;
}