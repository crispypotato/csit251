#ifndef LINE_3D_H
#define LINE_3D_H
#include "Line2D.h"
#include "Point3D.h"

class Line3D:public Line2D{
    private:
        Point3D pt1,pt2;
    protected:
        void setLength();
    public:
        Line3D();
        Line3D(Point3D pt1,Point3D pt2);
        Point3D getPt1();
        Point3D getPt2();
        void setPt1(Point3D pt1);
        void setPt2(Point3D pt2);
        friend bool operator==(const Line3D& l1, const Line3D& l2);
        friend bool operator<(const Line3D& l1,const Line3D& l2){
            if(l1.length<l2.length){
                return true;
            }else{
                return false;
            }
        }
    	friend bool operator>(const Line3D& l1,const Line3D& l2){
            if(l1.length>l2.length){
                return true;
            }else{
                return false;
            }
        }
        friend ostream &operator<<(ostream &out, Line3D& l){
            out << "[" << setw(4) << right << l.getPt1().getX() << ", ";
            out << setw(4) << right << l.getPt1().getY() << ", ";
            out << setw(4) << right << l.getPt1().getZ() << "]   [";
            out << setw(4) << right << l.getPt2().getX() << ", ";
            out << setw(4) << right << l.getPt2().getY() << ", ";
            out << setw(4) << right << l.getPt1().getZ() << "]   ";
            out << fixed << setprecision(3) << left << l.length;
            return out;
        }
        static bool Pt1Asc(Line3D l1, Line3D l2){
            return Point3D::XAsc(l1.getPt1(),l2.getPt1());
        }
        static bool Pt1Dsc(Line3D l1, Line3D l2){
            return Point3D::XDsc(l1.getPt1(),l2.getPt1());
        }
        static bool Pt2Asc(Line3D l1, Line3D l2){
            return Point3D::XAsc(l1.getPt2(),l2.getPt2());
        }
        static bool Pt2Dsc(Line3D l1, Line3D l2){
            return Point3D::XDsc(l1.getPt2(),l2.getPt2());
        }
};

#endif