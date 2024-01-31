#ifndef POINT_2D_H
#define POINT_2D_H
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

class Point2D{
    protected:
        int x,y;
        double distFrOrigin;
        void setDistFrOrigin();
    public:
        Point2D(){
            x = 0;
            y = 0;
        };
        Point2D(int x,int y);
        int getX();
        int getY();
        double getScalarValue();
        void setX(int x);
        void setY(int y);
        friend bool operator==(const Point2D& pt1, const Point2D& pt2);
        friend bool operator<(const Point2D& pt1,const Point2D& pt2){
            if(pt1.distFrOrigin<pt2.distFrOrigin){
                return true;
            }else{
                return false;
            }
        }
    	friend bool operator>(const Point2D& pt1,const Point2D& pt2){
            if(pt1.distFrOrigin>pt2.distFrOrigin){
                return true;
            }else{
                return false;
            }
        }
        friend ostream& operator<<(ostream &out, Point2D const &pt){
            out << "[" << setw(4) << right << pt.x << ", " << setw(4) << right << pt.y << "]   ";
            out << fixed << setprecision(3) << left << pt.distFrOrigin;
            return out;
        }
        static bool XAsc(Point2D pt1, Point2D pt2){
            if(pt1.getX()<pt2.getX()){
                return true;
            }else if(pt1.getX() == pt2.getX()){
                if(pt1.getY()<pt2.getY()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
        static bool XDsc(Point2D pt1, Point2D pt2){
            if(pt1.getX()>pt2.getX()){
                return true;
            }else if(pt1.getX() == pt2.getX()){
                if(pt1.getY()>pt2.getY()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
        static bool YAsc(Point2D pt1, Point2D pt2){
            if(pt1.getY()<pt2.getY()){
                return true;
            }else if(pt1.getY() == pt2.getY()){
                if(pt1.getX()<pt2.getX()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
        static bool YDsc(Point2D pt1, Point2D pt2){
            if(pt1.getY()>pt2.getY()){
                return true;
            }else if(pt1.getY() == pt2.getY()){
                if(pt1.getX()>pt2.getX()){
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