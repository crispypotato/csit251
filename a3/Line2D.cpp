#include "Line2D.h"

bool operator==(const Line2D& l1, const Line2D& l2){
	if(((l1.pt1 == l2.pt1) && (l1.pt2 == l2.pt2))||((l1.pt2 == l2.pt1) && (l1.pt1 == l2.pt2))){
		return true;
    }else if((l1.pt1 == l1.pt2) || (l2.pt1 == l2.pt2)){//line cannot be formed since both points are same
        return true;
    }else{
        return false;
    }
}

Line2D::Line2D(){

}
Line2D::Line2D(Point2D pt1,Point2D pt2){
    this->pt1 = pt1;
    this->pt2 = pt2;
    setLength();
}

Point2D Line2D::getPt1(){
    return pt1;
}
Point2D Line2D::getPt2(){
    return pt2;
}
double Line2D::getScalarValue(){
    return length;
}
void Line2D::setPt1(Point2D p1){
    this->pt1 = pt1;
}
void Line2D::setPt2(Point2D pt2){
    this->pt2 = pt2;
}
void Line2D::setLength(){
    length = sqrt(pow(pt1.getX()-pt2.getX(),2)+pow(pt1.getY()-pt2.getY(),2));
}