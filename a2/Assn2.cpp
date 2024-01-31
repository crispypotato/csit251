// g++ -std=c++11 Shape2D.cpp Circle.cpp Cross.cpp Square.cpp Rectangle.cpp Assn2.cpp -o Assn2.exe
// ./Assn2.exe
#include "Shape2D.h"
#include "Circle.h"
#include "Cross.h"
#include "Rectangle.h"
#include "Square.h"
#include <iomanip>
#include <cstring>
#include <algorithm>

using namespace std;

vector<ShapeTwoD*> shapeArr;
vector<ShapeTwoD*> computedShapeArr;
vector<double> areaArr;
void menu();
void inputSensorData();
void computeShapeAreas();
void printReport();
void sortMenu();
void sortSwitch();
void sortAreaAsc();
void sortAreaDsc();
void sortSpTypeArea();

int main(){
    int choice;
    while(choice!=5){
        menu();
        cin >> choice;
        cout << endl;
        switch(choice){
            case 1:
                cout << "[Input sensor data]" << endl;
                inputSensorData();
                break;
            case 2:
                computeShapeAreas();
                break;
            case 3:
                printReport();
                break;
            case 4:
                sortSwitch();
                break;
            case 5:
                cout << endl;
                break;
            default: // when int is not any of the choices
                cout << "Invalid choice, please try again." << endl;
                cout << endl;
                break;
        }
    }
}

void menu(){
    cout << "Student ID " << setw(11) << right <<": 7910502" << endl;
    cout << "Student Name " << setw(12) << right << ": Toh Jing Wen" << endl;
    cout << "------------------------------------------" << endl;
    cout << "Welcome to Assn2 program!" << endl;
    cout << endl;
    cout << "1)\tInput sensor data" << endl;
    cout << "2)\tCompute area (for all records)" << endl;
    cout << "3)\tPrint shapes report" << endl;
    cout << "4)\tSort shape data" << endl;
    cout << "5)\tExit" << endl;
    cout << endl;
    cout << "Please enter your choice: ";
}

void inputSensorData(){//option 1: input a shape
    string shape,specialType;
    bool warpSpace;
    if(shapeArr.size()<100){
        cout << "Please enter name of shape: ";
        cin >> shape;
        cout << "Please enter special type: ";
        cin >> specialType;
        if(specialType=="WS"){
            warpSpace = true;
        }
        else if(specialType=="NS"){
            warpSpace = false;
        }
        cout << endl;
        if(shape=="Circle"){//initialize circle object
            shapeArr.push_back(new Circle(shape,warpSpace));
            int x,y;
            double radius;
            cout << "Please enter x-ordinate of center: ";
            cin >> x;
            cout << "Please enter y-ordinate of center: ";
            cin >> y;
            cout << "Please enter radius: ";
            cin >> radius;
            cout << endl;
            shapeArr.back()->setData(x,y,radius);
        }else if(shape=="Square"){//initialize square object
            shapeArr.push_back(new Square(shape,warpSpace));
            vector<int> xArr,yArr;
            for(int i=1;i<=4;i++){
                int x,y;
                cout << "Please enter x-ordinate of pt." << to_string(i) << ": ";
                cin >> x;
                xArr.push_back(x);
                cout << "Please enter y-ordinate of pt." << to_string(i) << ": ";
                cin >> y;
                yArr.push_back(y);
                cout << endl;
            }
            shapeArr.back()->setData(xArr,yArr);
        }else if(shape=="Rectangle"){//initialize rectangle object
            shapeArr.push_back(new Rectangle(shape,warpSpace));
            vector<int> xArr,yArr;
            for(int i=1;i<=4;i++){
                int x,y;
                cout << "Please enter x-ordinate of pt." << to_string(i) << ": ";
                cin >> x;
                xArr.push_back(x);
                cout << "Please enter y-ordinate of pt." << to_string(i) << ": ";
                cin >> y;
                yArr.push_back(y);
                cout << endl;
            }
            shapeArr.back()->setData(xArr,yArr);
        }else if(shape=="Cross"){//initialize cross object
            shapeArr.push_back(new Cross(shape,warpSpace));
            vector<int> xArr,yArr;
            for(int i=1;i<=12;i++){
                int x,y;
                cout << "Please enter x-ordinate of pt." << to_string(i) << ": ";
                cin >> x;
                xArr.push_back(x);
                cout << "Please enter y-ordinate of pt." << to_string(i) << ": ";
                cin >> y;
                yArr.push_back(y);
                cout << endl;
            }
            shapeArr.back()->setData(xArr,yArr);
        }
        cout << "Record successfully stored. Going back to main menu..." << endl;
        cout << endl;
    }else{
        cout << "Too many shapes stored! (max shapes allowed is 100)" << endl;
    }
}

void computeShapeAreas(){
    if(shapeArr.size()!=0){
        for(int i=0;i<shapeArr.size();i++){
            computedShapeArr.push_back(shapeArr[i]);
            areaArr.push_back(shapeArr[i]->computeArea());
        }
        cout << "Computation completed! (" << shapeArr.size() << " records were updated)" << endl;
        cout << endl;
        shapeArr.clear();
    }else if(shapeArr.size()==100){
        cout << "Too many shapes stored! (max shapes allowed is 100)" << endl;
    }else{
        cout << "No shapes found, please input a shape first." << endl;
        cout << endl;
    }
}

void printReport(){
    cout << "Total no. of records available = " << computedShapeArr.size() << endl;
    cout << endl;
    for(int i=0;i<computedShapeArr.size();i++){
        cout << "Shape [" << i << "]" << endl;
        cout << computedShapeArr[i]->toString();
    }
}

void sortMenu(){
    cout << "\ta)\tSort by area (ascending)" << endl;
    cout << "\tb)\tSort by area (descending)" << endl;
    cout << "\tc)\tSort by special type and area" << endl;
    cout << endl;
    cout << "Please select sort option ('q' to go to main menu): ";
}
void sortAreaAsc(){
    sort(areaArr.begin(),areaArr.end());
    for(auto a:areaArr){
        for(int i=0;i<computedShapeArr.size();i++){
            if((computedShapeArr[i]->computeArea())==a){
                cout << "Shape [" << i << "]" << endl;                
                cout << computedShapeArr[i]->toString();
            }
        }
    }
}
void sortAreaDsc(){
    sort(areaArr.begin(),areaArr.end(),greater<double>());
    for(auto a:areaArr){
        for(int i=0;i<computedShapeArr.size();i++){
            if((computedShapeArr[i]->computeArea())==a){
                cout << "Shape [" << i << "]" << endl;                
                cout << computedShapeArr[i]->toString();
            }
        }
    }
}
void sortSpTypeArea(){
    vector<ShapeTwoD*> WSShapes;
    vector<ShapeTwoD*> NSShapes;
    for(auto c:computedShapeArr){
        if((c->getContainsWarpSpace())==true){
            WSShapes.push_back(c);
        }else{
            NSShapes.push_back(c);
        }
    }
    sort(areaArr.begin(),areaArr.end(),greater<double>());
    for(auto a:areaArr){
        for(auto w:WSShapes){
            if((w->computeArea())==a){
                int i = distance(computedShapeArr.begin(),find(computedShapeArr.begin(),computedShapeArr.end(),w));
                cout << "Shape [" << i << "]" << endl;                
                cout << w->toString();
            }
        }
    }
    for(auto a:areaArr){
        for(auto n:NSShapes){
            if((n->computeArea())==a){
                int i = distance(computedShapeArr.begin(),find(computedShapeArr.begin(),computedShapeArr.end(),n));
                cout << "Shape [" << i << "]" << endl;                
                cout << n->toString();
            }
        }
    }
}
void sortSwitch(){
    char sortChoice;
    while(sortChoice!='q'){
        sortMenu();
        cin >> sortChoice;
        switch (sortChoice)
        {
        case 'a':
            sortAreaAsc();
            break;
        case 'b':
            sortAreaDsc();
            break;
        case 'c':
            sortSpTypeArea();
            break;
        case 'q':
            cout << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            cout << endl;
            break;
        }
    }
}