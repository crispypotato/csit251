#include "Point3D.h"

bool operator==(const Point3D& pt1, const Point3D& pt2){
	if((pt1.x == pt2.x) && (pt1.y == pt2.y) && (pt1.z == pt2.z)){
		return true;
    }else{
        return false;
    }
}

Point3D::Point3D():Point2D(){
    z = 0;
}
Point3D::Point3D(int x,int y,int z):Point2D(x,y){
    this->z = z;
    setDistFrOrigin();
}

int Point3D::getZ(){
    return z;
}
void Point3D::setZ(){
    this->z = z;
}
void Point3D::setDistFrOrigin(){
    this->distFrOrigin = sqrt(x*x + y*y + z*z);
}