#include "Cross.h"

Cross::Cross(string name,bool containsWarpSpace):ShapeTwoD(name,containsWarpSpace){

}

int Cross::getXUpper(){
    return xUpper;
}
int Cross::getXLower(){
    return xLower;
}
int Cross::getYUpper(){
    return yUpper;
}
int Cross::getYLower(){
    return yLower;
}
void Cross::setData(vector<int> x,vector<int> y){
    for(int i=0;i<12;i++){
        xVectors.push_back(x[i]);
        yVectors.push_back(y[i]);
    }
    xUpper = x[0];
    xLower = x[0];
    yUpper = y[0];
    yLower = y[0];
    for(int i=1;i<12;i++){
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

    for(int i=0;i<xVectors.size();i++){
        if(xVectors[i]==xUpper){
            xUpperIndex.push_back(i);
        }else if(xVectors[i]==xLower){
            xLowerIndex.push_back(i);
        }else if(yVectors[i]==yUpper){
            yUpperIndex.push_back(i);
        }else if(yVectors[i]==yLower){
            yLowerIndex.push_back(i);
        }
        //each vector should only contain 2 index values
        //since xVectors are of the same size as yVectors they can be compared in the same loop
    }
    if(yVectors[xUpperIndex[0]]>=yVectors[xUpperIndex[1]]){
        xUpperMaxY = yVectors[xUpperIndex[0]];
        xUpperMinY = yVectors[xUpperIndex[1]];
    }else{
        xUpperMaxY = yVectors[xUpperIndex[1]];
        xUpperMinY = yVectors[xUpperIndex[0]];
    }
    if(yVectors[xLowerIndex[0]]>=yVectors[xLowerIndex[1]]){
        xLowerMaxY = yVectors[xLowerIndex[0]];
        xLowerMinY = yVectors[xLowerIndex[1]];
    }else{
        xLowerMaxY = yVectors[xLowerIndex[1]];
        xLowerMinY = yVectors[xLowerIndex[0]];
    }
    if(xVectors[yUpperIndex[0]]>=xVectors[yUpperIndex[1]]){
        yUpperMaxX = xVectors[yUpperIndex[0]];
        yUpperMinX = xVectors[yUpperIndex[1]];
    }else{
        yUpperMaxX = xVectors[yUpperIndex[1]];
        yUpperMinX = xVectors[yUpperIndex[0]];
    }
    if(xVectors[yLowerIndex[0]]>=xVectors[yLowerIndex[1]]){
        yLowerMaxX = xVectors[yLowerIndex[0]];
        yLowerMinX = xVectors[yLowerIndex[1]];
    }else{
        yLowerMaxX = xVectors[yLowerIndex[1]];
        yLowerMinX = xVectors[yLowerIndex[0]];
    }
    if(xUpperMaxY>xLowerMaxY){
        topRectLength = yUpper-xUpperMaxY;
    }else{
        topRectLength = yUpper-xLowerMaxY;
    }
    if(yUpperMinX>yLowerMinX){
        leftRectLength = yLowerMinX-xLower;
    }else{
        leftRectLength = yUpperMinX-xLower;
    }
    if(xUpperMinY>xLowerMinY){
        btmRectLength = xUpperMinY-yLower;
    }else{
        btmRectLength = xLowerMinY-yLower;
    }
    if(yUpperMaxX>yLowerMaxX){
        rightRectLength = xUpper-yUpperMaxX;
    }else{
        rightRectLength = xUpper-yLowerMaxX;
    }
}

double Cross::computeArea(){
    //individually calculate area of the 5 separate inner rectangles
    topRect = (yUpperMaxX-yUpperMinX)*topRectLength;
    leftRect = (xLowerMaxY-xLowerMinY)*leftRectLength;
    btmRect = (yLowerMaxX-yLowerMinX)*btmRectLength;
    rightRect = (xUpperMaxY-xUpperMinY)*rightRectLength;
    centerRect = (xUpper-xLower-leftRectLength-rightRectLength)*(yUpper-yLower-topRectLength-btmRectLength);
    return topRect+btmRect+leftRect+rightRect+centerRect;
}
bool Cross::isPointInShape(int x,int y){
    if((y<yUpper && y>=yUpper-topRectLength)&&(x>yUpperMinX && x<yUpperMaxX)){//within top rectangle
        return true;
    }else if((x>xLower && x<=xLower+leftRectLength)&&(y>xLowerMinY && y<xLowerMaxY)){//within left rectangle
        return true;
    }else if((y>yLower && y<=yLower+btmRectLength)&&(x>yLowerMinX && x<yLowerMaxX)){//within bottom rectangle
        return true;
    }else if((x<xUpper && x>=xUpper-rightRectLength)&&(y>xUpperMinY && y<xUpperMaxY)){//within right rectangle
        return true;
    }else if((y>yLower+btmRectLength && y<yUpper-topRectLength)&&(x>xLower+leftRectLength && x<xUpper-rightRectLength)){
        //within center rectangle
        return true;
    }else{
        return false;
    }
}
bool Cross::isPointOnShape(int x,int y){
    // perimeter of top rectangle + bit of center (if any)
    if(y==yUpper && (x>yUpperMinX && x<yUpperMaxX)){
        return true;
    }else if(x==yUpperMinX && (y>xLowerMaxY && y<yUpper)){
        return true;
    }
    else if(x==yUpperMaxX && (y>xUpperMaxY && y<yUpper)){
        return true;
    }
    // perimeter of left rectangle + bit of center (if any)
    else if((x==xLower && (y>xLowerMinY && y<xLowerMaxY))){
        return true;
    }else if(y==xLowerMaxY && (x>xLower && x<yUpperMinX)){
        return true;
    }else if(y==xLowerMinY && (x>xLower && x<yLowerMinX)){
        return true;
    }
    // perimeter of bottom rectangle + bit of center (if any)
    else if(y==yLower && (x>yLowerMinX && y<yLowerMaxX)){
        return true;
    }else if(x==yLowerMinX && (y>yLower && y<xLowerMinY)){
        return true;
    }else if(x==yLowerMaxX && (y>yLower && y<xUpperMinY)){
        return true;
    }
    // perimeter of right rectangle + bit of center (if any)
    else if(x==xUpper && (y>xUpperMinY && y<xUpperMaxY)){
        return true;
    }else if(y==xUpperMaxY && (x>yUpperMaxX && x<xUpper)){
        return true;
    }else if(y==xUpperMinY && (x>yLowerMaxX && x<xUpper)){
        return true;
    }else{
        return false;
    }
}
string Cross::toString(){
    ostringstream oss;
    string ptInShape,ptOnShape;
    oss << ShapeTwoD::toString();
    oss << "Area: " << computeArea() << " units square\nVertices:\n";
    for(int i=0;i<12;i++){
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