#include "Line3D.h"

bool operator==(const Line3D& l1, const Line3D& l2){
	if(((l1.pt1 == l2.pt1) && (l1.pt2 == l2.pt2))||((l1.pt2 == l2.pt1) && (l1.pt1 == l2.pt2))){
		return true;
    }else if((l1.pt1 == l1.pt2) || (l2.pt1 == l2.pt2)){//line cannot be formed since both points are same
        return true;
    }else{
        return false;
    }
}

Line3D::Line3D(){

}
Line3D::Line3D(Point3D pt1,Point3D pt2){
    this->pt1 = pt1;
    this->pt2 = pt2;
    setLength();
}

Point3D Line3D::getPt1(){
    return pt1;
}
Point3D Line3D::getPt2(){
    return pt2;
}
void Line3D::setPt1(Point3D pt1){
    this->pt1 = pt1;
}
void Line3D::setPt2(Point3D pt2){
    this->pt2 = pt2;
}
void Line3D::setLength(){
    length = sqrt(pow(pt1.getX()-pt2.getX(),2) + pow(pt1.getY()-pt2.getY(),2) + pow(pt1.getZ()-pt2.getZ(),2));
}