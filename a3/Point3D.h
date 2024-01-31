#ifndef POINT_3D_H
#define POINT_3D_H
#include "Point2D.h"

class Point3D: public Point2D{
    protected:
        int z;
        void setDistFrOrigin();
    public:
        Point3D();
        Point3D(int x,int y,int z);
        int getZ();
        void setZ();
        friend bool operator==(const Point3D& pt1, const Point3D& pt2);
        friend bool operator<(const Point3D& pt1,const Point3D& pt2){
            if(pt1.distFrOrigin<pt2.distFrOrigin){
                return true;
            }else{
                return false;
            }
        }
    	friend bool operator>(const Point3D& pt1,const Point3D& pt2){
            if(pt1.distFrOrigin>pt2.distFrOrigin){
                return true;
            }else{
                return false;
            }
        }
        friend ostream& operator<<(ostream &out, Point3D const &pt){
            out << "[" << setw(4) << right << pt.x << ", " << setw(4) << right << pt.y << ", ";
            out << setw(4) << right << pt.z << "]   " << fixed << setprecision(3) << left << pt.distFrOrigin;
            return out;
        }
        static bool XAsc(Point3D pt1, Point3D pt2){
            if(pt1.getX()<pt2.getX()){
                return true;
            }else if(pt1.getX() == pt2.getX()){
                if(pt1.getY()<pt2.getY()){
                    return true;
                }else if((pt1.getY() == pt2.getY())&&(pt1.getZ()<pt2.getZ())){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
        static bool XDsc(Point3D pt1, Point3D pt2){
            if(pt1.getX()>pt2.getX()){
                return true;
            }else if(pt1.getX() == pt2.getX()){
                if(pt1.getY()>pt2.getY()){
                    return true;
                }else if((pt1.getY() == pt2.getY())&&(pt1.getZ()>pt2.getZ())){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
        static bool YAsc(Point3D pt1, Point3D pt2){
            if(pt1.getY()<pt2.getY()){
                return true;
            }else if(pt1.getY() == pt2.getY()){
                if(pt1.getX()<pt2.getX()){
                    return true;
                }else if((pt1.getX() == pt2.getX())&&(pt1.getZ()<pt2.getZ())){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
        static bool YDsc(Point3D pt1, Point3D pt2){
            if(pt1.getY()>pt2.getY()){
                return true;
            }else if(pt1.getY() == pt2.getY()){
                if(pt1.getX()>pt2.getX()){
                    return true;
                }else if((pt1.getX() == pt2.getX())&&(pt1.getZ()>pt2.getZ())){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
        static bool ZAsc(Point3D pt1, Point3D pt2){
            if(pt1.getZ()<pt2.getZ()){
                return true;
            }else if(pt1.getZ() == pt2.getZ()){
                if(pt1.getX()<pt2.getX()){
                    return true;
                }else if((pt1.getX() == pt2.getX())&&(pt1.getY()<pt2.getY())){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
        static bool ZDsc(Point3D pt1, Point3D pt2){
            if(pt1.getZ()>pt2.getZ()){
                return true;
            }else if(pt1.getZ() == pt2.getZ()){
                if(pt1.getX()>pt2.getX()){
                    return true;
                }else if((pt1.getX() == pt2.getX())&&(pt1.getY()>pt2.getY())){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
};

#endif