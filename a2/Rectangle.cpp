#include "Rectangle.h"

Rectangle::Rectangle(string name,bool containsWarpSpace):ShapeTwoD(name,containsWarpSpace){

}

int Rectangle::getXUpper(){
    return xUpper;
}
int Rectangle::getXLower(){
    return xLower;
}
int Rectangle::getYUpper(){
    return yUpper;
}
int Rectangle::getYLower(){
    return yLower;
}
void Rectangle::setData(vector<int> x,vector<int> y){
    for(int i=0;i<4;i++){
        xVectors.push_back(x[i]);
        yVectors.push_back(y[i]);
    }
    xUpper = x[0];
    xLower = x[0];
    yUpper = y[0];
    yLower = y[0];
    for(int i=1;i<4;i++){
        if(xUpper<x[i]){
            xUpper = x[i];
        }else if(xLower>x[i]){
            xLower = x[i];
        }else if(yUpper<y[i]){
            yUpper = y[i];
        }else if(yLower>y[i]){
            yLower = y[i];
        }
    }
}

double Rectangle::computeArea(){
    int length = xUpper-xLower;
    int breadth = yUpper-yLower;
    return length*breadth;
}
bool Rectangle::isPointInShape(int x,int y){
    if((x<xUpper && x>xLower)&&(y<yUpper && y>yLower)){
        return true;
    }else{
        return false;
    }
}
bool Rectangle::isPointOnShape(int x,int y){
    if((x==xUpper || x==xLower)&&(y<yUpper && y>yLower)){
        return true;
    }else if((y==yUpper || y==yLower)&&(x<xUpper && x>xLower)){
        return true;
    }else{
        return false;
    }
}
string Rectangle::toString(){
    ostringstream oss;
    string ptInShape,ptOnShape;
    oss << ShapeTwoD::toString();
    oss << "Area: " << computeArea() << " units square\nVertices:\n";
    for(int i=0;i<4;i++){
        oss << "Point [" << i <<"]: (" << xVectors[i] << ", " << yVectors[i] << ")\n";
    }
    oss << "\nPoints on perimeter: ";
    for(int i=xLower;i<=xUpper;i++){
        for(int j=yLower;j<=yUpper;j++){
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
    for(int i=xLower;i<=xUpper;i++){
        for(int j=yLower;j<=yUpper;j++){
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