#include "Shape2D.h"

ShapeTwoD::ShapeTwoD(string n,bool cws){
    this->name = n;
    this->containsWarpSpace = cws;
}

string ShapeTwoD::getName(){
    return name;
}
bool ShapeTwoD::getContainsWarpSpace(){
    return containsWarpSpace;
}
void ShapeTwoD::setName(string n){
    this->name = n;
}
void ShapeTwoD::setContainsWarpSpace(bool cws){
    this->containsWarpSpace = cws;
}

string ShapeTwoD::toString(){
    ostringstream oss;
    oss << "Name: " << name << "\nSpecial Type: ";
    if(containsWarpSpace==true){
        oss << "WS\n";
    }else{
        oss << "NS\n";
    }
    return oss.str();
}
