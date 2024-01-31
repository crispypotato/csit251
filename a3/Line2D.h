#ifndef LINE_2D_H
#define LINE_2D_H
#include "Point2D.h"

class Line2D{
    private:
        Point2D pt1,pt2;
    protected:
        double length;
        void setLength();
    public:
        Line2D();
        Line2D(Point2D pt1,Point2D pt2);
        Point2D getPt1();
        Point2D getPt2();
        double getScalarValue();
        void setPt1(Point2D pt1);
        void setPt2(Point2D pt2);
        friend bool operator==(const Line2D& l1, const Line2D& l2);
        friend bool operator<(const Line2D& l1,const Line2D& l2){
            if(l1.length<l2.length){
                return true;
            }else{
                return false;
            }
        }
    	friend bool operator>(const Line2D& l1,const Line2D& l2){
            if(l1.length>l2.length){
                return true;
            }else{
                return false;
            }
        }
        friend ostream &operator<<(ostream &out, Line2D& l){
            out << "[" << setw(4) << right << l.getPt1().getX() << ", ";
            out << setw(4) << right << l.getPt1().getY() << "]   [";
            out << setw(4) << right << l.getPt2().getX() << ", ";
            out << setw(4) << right << l.getPt2().getY() << "]   ";
            out << fixed << setprecision(3) << left << l.getScalarValue();
            return out;
        }
        static bool Pt1Asc(Line2D l1, Line2D l2){
            return Point2D::XAsc(l1.getPt1(),l2.getPt1());
        }
        static bool Pt1Dsc(Line2D l1, Line2D l2){
            return Point2D::XDsc(l1.getPt1(),l2.getPt1());
        }
        static bool Pt2Asc(Line2D l1, Line2D l2){
            return Point2D::XAsc(l1.getPt2(),l2.getPt2());
        }
        static bool Pt2Dsc(Line2D l1, Line2D l2){
            return Point2D::XDsc(l1.getPt2(),l2.getPt2());
        }
};

#endif