#include "Point2D.h"

bool operator==(const Point2D& pt1, const Point2D& pt2){
	if((pt1.x == pt2.x) && (pt1.y == pt2.y)){
		return true;
    }else{
        return false;
    }
}

Point2D::Point2D(int x,int y){
    this->x = x;
    this->y = y;
    setDistFrOrigin();
}

int Point2D::getX(){
    return x;
}
int Point2D::getY(){
    return y;
}
double Point2D::getScalarValue(){
    return distFrOrigin;
}
void Point2D::setX(int x){
    this->x = x;
}
void Point2D::setY(int y){
    this->y = y;
}
void Point2D::setDistFrOrigin(){
    this->distFrOrigin = sqrt(x*x + y*y);
}