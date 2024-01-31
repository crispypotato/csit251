//g++ -std=c++11 Point2D.cpp Point3D.cpp Line2D.cpp Line3D.cpp Assn3.cpp -o Assn3.exe

#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"
#include "MyTemplates.h"
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

string currFilter = "Point2D";
string currSortCrit = "x-ordinate";
string currSortOrder = "ASC";
vector<Point2D> pt2DArr;
vector<Point3D> pt3DArr;
vector<Line2D> line2DArr;
vector<Line3D> line3DArr;
void menu();
vector<string> splitString(string str, string delim);
void readData(string filename);
void filterMenu();
void filterCrit();
void sortMenu();
void orderMenu();
void userEnter();
void showData();
void storeData();

int main(){
    int choice;
    string filename;
    while(choice!=7){
        menu();
        cin >> choice;
        cout << endl;
        switch(choice){
            case 1:
                cout << "Please enter filename: ";
                cin >> filename;
                cout << endl;
                readData(filename);
                break;
            case 2:
                cout << "[Specifying filtering criteria (current: " << currFilter << ")]" << endl;
                filterCrit();
                break;
            case 3:
                cout << "[Specifying sorting criteria (current: " << currSortCrit << ")]" << endl;
                sortMenu();
                break;
            case 4:
                cout << "[Specifying sorting order (current: " << currSortOrder << ")]" << endl;
                orderMenu();
                break;
            case 5:
                cout << "[View data...]" << endl;
                cout << "filtering criteria: " << currFilter << endl;
                cout << "sorting criteria: " << currSortCrit << endl;
                cout << "sorting order: " << currSortOrder << endl;
                showData();
                break;
            case 6:
                storeData();
                break;
            case 7:
                cout << "Exiting application..." << endl;
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
    cout << "Welcome to Assn3 program!" << endl;
    cout << endl;
    cout << "1)\tRead in data" << endl;
    cout << "2)\tSpecify filtering criteria (current: " << currFilter << ")" << endl;
    cout << "3)\tSpecify sorting criteria (current: " << currSortCrit << ")" << endl;
    cout << "4)\tSpecify sorting order (current: " << currSortOrder << ")" << endl;
    cout << "5)\tView data" << endl;
    cout << "6)\tStore data" << endl;
    cout << "7)\tQuit" << endl;
    cout << endl;
    cout << "Please enter your choice: ";
}

vector<string> splitString(string str, string delim){
    vector<string> result;
    size_t position = 0;
    string token;
    while((position = str.find(delim)) != string::npos){
        token = str.substr(0, position);
        result.push_back(token);
        str.erase(0,position+delim.length());
    }
    result.push_back(str);
    return result;
}

void readData(string filename){
    int linecount = 0;
    ifstream inputFile;
    inputFile.open(filename.c_str());
    while(inputFile.good()){
        string aLine;
        getline(inputFile, aLine);
        vector<string> lineData = splitString(aLine,", ");
        if(lineData[0]=="Point2D"){
            int x = stoi(lineData[1].erase(0,1)); //removes '[', then convert to int
            int y = stoi(lineData[2].substr(0,lineData[2].size()-1)); //removes ']', then convert to int
            Point2D p(x,y);
            if(find(pt2DArr.begin(),pt2DArr.end(),p) != pt2DArr.end()){
                //do nothing
            }else{
                pt2DArr.push_back(p);
            }
        }else if(lineData[0]=="Point3D"){
            int x = stoi(lineData[1].erase(0,1)); //removes '[', then convert to int
            int y = stoi(lineData[2]);
            int z = stoi(lineData[3].substr(0,lineData[3].size()-1)); //removes ']', then convert to int
            Point3D p(x,y,z);
            if(find(pt3DArr.begin(),pt3DArr.end(),p) != pt3DArr.end()){
                //do nothing
            }else{
                pt3DArr.push_back(p);
            }
        }else if(lineData[0]=="Line2D"){
            int x1 = stoi(lineData[1].erase(0,1));
            int y1 = stoi(lineData[2].substr(0,lineData[2].size()-1));
            int x2 = stoi(lineData[3].erase(0,1));
            int y2 = stoi(lineData[4].substr(0,lineData[4].size()-1));
            Line2D l(Point2D(x1,y1),Point2D(x2,y2));
            if(find(line2DArr.begin(),line2DArr.end(),l) != line2DArr.end()){
                //do nothing
            }else{
                line2DArr.push_back(l);
            }
        }else if(lineData[0]=="Line3D"){
            int x1 = stoi(lineData[1].erase(0,1));
            int y1 = stoi(lineData[2]);
            int z1 = stoi(lineData[3].substr(0,lineData[3].size()-1));            
            int x2 = stoi(lineData[4].erase(0,1));
            int y2 = stoi(lineData[5]);
            int z2 = stoi(lineData[6].substr(0,lineData[6].size()-1));
            Line3D l(Point3D(x1,y1,z1),Point3D(x2,y2,z2));
            if(find(line3DArr.begin(),line3DArr.end(),l) != line3DArr.end()){
                //do nothing
            }else{
                line3DArr.push_back(l);
            }
        }
        if(aLine!=""){
            linecount++;
        }
    }
    inputFile.close();
    cout << linecount << " records read in successfully!" << endl; //includes repeated
    cout << endl;
}

void filterMenu(){
    cout << "\ta)\tPoint2D records" << endl;
    cout << "\tb)\tPoint3D records" << endl;
    cout << "\tc)\tLine2D records" << endl;
    cout << "\td)\tLine3D records" << endl;
    cout << endl;
    cout << "\tPlease enter your criteria (a-d): ";
}

void filterCrit(){
    char filterChoice;
    filterMenu();
    cin >> filterChoice;
    switch (filterChoice){
    case 'a':
        currFilter = "Point2D";
        currSortCrit = "x-ordinate";
        cout << "\tFilter criteria successfully set to '" << currFilter << "'!" << endl;
        break;
    case 'b':
        currFilter = "Point3D";
        currSortCrit = "x-ordinate";
        cout << "\tFilter criteria successfully set to '" << currFilter << "'!" << endl;
        break;
    case 'c':
        currFilter = "Line2D";
        currSortCrit = "Pt. 1";
        cout << "\tFilter criteria successfully set to '" << currFilter << "'!" << endl;
        break;
    case 'd':
        currFilter = "Line3D";
        currSortCrit = "Pt. 1";
        cout << "\tFilter criteria successfully set to '" << currFilter << "'!" << endl;
        break;
    default:
        cout << "\tInvalid choice, please try again." << endl;
        break;
    }
    cout << endl;
}

void sortMenu(){
    char sortChoice;
    if(currFilter=="Point2D"){
        cout << "\ta)\tX ordinate value" << endl;
        cout << "\tb)\tY ordinate value" << endl;
        cout << "\tc)\tDist. Fr Origin value" << endl;
        cout << endl;
        cout << "\tPlease enter your criteria (a-c): ";
        cin >> sortChoice;
        switch(sortChoice){
            case 'a':
                currSortCrit = "x-ordinate";
                cout << "\tSorting criteria successfully set to '" << currSortCrit << "'!" << endl;
                break;
            case 'b':
                currSortCrit = "y-ordinate";
                cout << "\tSorting criteria successfully set to '" << currSortCrit << "'!" << endl;
                break;
            case 'c':
                currSortCrit = "Dist.";
                cout << "\tSorting criteria successfully set to '" << currSortCrit << "'!" << endl;
                break;
            default:
                cout << "\tInvalid choice, please try again." << endl;
                break;
        }
    }else if(currFilter=="Point3D"){
        cout << "\ta)\tX ordinate value" << endl;
        cout << "\tb)\tY ordinate value" << endl;
        cout << "\tc)\tZ ordinate value" << endl;
        cout << "\td)\tDist. Fr Origin value" << endl;
        cout << endl;
        cout << "\tPlease enter your criteria (a-d): ";
        cin >> sortChoice;
        switch(sortChoice){
            case 'a':
                currSortCrit = "x-ordinate";
                cout << "\tSorting criteria successfully set to '" << currSortCrit << "'!" << endl;
                break;
            case 'b':
                currSortCrit = "y-ordinate";
                cout << "\tSorting criteria successfully set to '" << currSortCrit << "'!" << endl;
                break;
            case 'c':
                currSortCrit = "z-ordinate";
                cout << "\tSorting criteria successfully set to '" << currSortCrit << "'!" << endl;
                break;
            case 'd':
                currSortCrit = "Dist.";
                cout << "\tSorting criteria successfully set to '" << currSortCrit << "'!" << endl;
                break;
            default:
                cout << "\tInvalid choice, please try again." << endl;
                break;
        }
    }else{
        cout << "\ta)\tPt. 1's (x, y) values" << endl;
        cout << "\tb)\tPt. 2's (x, y) values" << endl;
        cout << "\tc)\tLength value" << endl;
        cout << endl;
        cout << "\tPlease enter your criteria (a-c): ";
        cin >> sortChoice;
        switch(sortChoice){
            case 'a':
                currSortCrit = "Pt. 1";
                cout << "\tSorting criteria successfully set to '" << currSortCrit << "'!" << endl;
                break;
            case 'b':
                currSortCrit = "Pt. 2";
                cout << "\tSorting criteria successfully set to '" << currSortCrit << "'!" << endl;
                break;
            case 'c':
                currSortCrit = "Length";
                cout << "\tSorting criteria successfully set to '" << currSortCrit << "'!" << endl;
                break;
            default:
                cout << "\tInvalid choice, please try again." << endl;
                break;
        }
    }
    cout << endl;
}

void orderMenu(){
    char orderChoice;
    cout << "\ta)\tASC (Ascending order)" << endl;
    cout << "\tb)\tDSC (Descending order)" << endl;
    cout << endl;
    cout << "\tPlease enter your criteria (a-b): ";
    cin >> orderChoice;
    switch(orderChoice){
        case 'a':
            currSortOrder = "ASC";
            cout << "\tSorting order successfully set to '" << currSortOrder << "'!" << endl;
            break;
        case 'b':
            currSortOrder = "DSC";
            cout << "\tSorting order successfully set to '" << currSortOrder << "'!" << endl;
            break;
        default:
            cout << "\tInvalid choice, please try again." << endl;
            break;
    }
    cout << endl;
}

void userEnter(){
	int i = 0;
	while(i == 0){
		cout << "Press <enter> to go back to main menu...";
		cin.ignore();
		if(cin.get() == '\n'){
			i = 1;
        }
	}
	cout << endl;
}

void showData(){
    if(currFilter=="Point2D"){
        if(currSortCrit=="x-ordinate"){
            if(currSortOrder=="ASC"){
                sort(pt2DArr.begin(),pt2DArr.end(),Point2D::XAsc);
            }else{
                sort(pt2DArr.begin(),pt2DArr.end(),Point2D::XDsc);
            }
        }else if(currSortCrit=="y-ordinate"){
            if(currSortOrder=="ASC"){
                sort(pt2DArr.begin(),pt2DArr.end(),Point2D::YAsc);
            }else{
                sort(pt2DArr.begin(),pt2DArr.end(),Point2D::YDsc);
            }
        }else if(currSortCrit=="Dist."){
            if(currSortOrder=="ASC"){
                sort(pt2DArr.begin(),pt2DArr.end());
            }else{
                sort(pt2DArr.begin(),pt2DArr.end(),greater<Point2D>());
            }
        }
        cout << setw(5) << right << "X" << setw(6) << right << "Y" << "    Dist. Fr Origin" << endl;
        cout << "- - - - - - - - - - - - - - - - - - -" << endl;
        for(auto a:pt2DArr){
            cout << a << endl;
        }
    }else if(currFilter=="Point3D"){
        if(currSortCrit=="x-ordinate"){
            if(currSortOrder=="ASC"){
                sort(pt3DArr.begin(),pt3DArr.end(),Point3D::XAsc);
            }else{
                sort(pt3DArr.begin(),pt3DArr.end(),Point3D::XDsc);
            }
        }else if(currSortCrit=="y-ordinate"){
            if(currSortOrder=="ASC"){
                sort(pt3DArr.begin(),pt3DArr.end(),Point3D::YAsc);
            }else{
                sort(pt3DArr.begin(),pt3DArr.end(),Point3D::YDsc);
            }
        }else if(currSortCrit=="z-ordinate"){
            if(currSortOrder=="ASC"){
                sort(pt3DArr.begin(),pt3DArr.end(),Point3D::ZAsc);
            }else{
                sort(pt3DArr.begin(),pt3DArr.end(),Point3D::ZDsc);
            }
        }else if(currSortCrit=="Dist."){
            if(currSortOrder=="ASC"){
                sort(pt3DArr.begin(),pt3DArr.end());
            }else{
                sort(pt3DArr.begin(),pt3DArr.end(),greater<Point3D>());
            }
        }
        cout << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z" << "    Dist. Fr Origin" << endl;
        cout << "- - - - - - - - - - - - - - - - - - -" << endl;
        for(auto a:pt3DArr){
            cout << a << endl;
        }
    }else if(currFilter=="Line2D"){
        if(currSortCrit=="Pt. 1"){
            if(currSortOrder=="ASC"){
                sort(line2DArr.begin(),line2DArr.end(),Line2D::Pt1Asc);
            }else{
                sort(line2DArr.begin(),line2DArr.end(),Line2D::Pt1Dsc);
            }
        }else if(currSortCrit=="Pt. 2"){
            if(currSortOrder=="ASC"){
                sort(line2DArr.begin(),line2DArr.end(),Line2D::Pt2Asc);
            }else{
                sort(line2DArr.begin(),line2DArr.end(),Line2D::Pt2Dsc);
            }
        }else if(currSortCrit=="Length"){
            if(currSortOrder=="ASC"){
                sort(line2DArr.begin(),line2DArr.end());
            }else{
                sort(line2DArr.begin(),line2DArr.end(),greater<Line2D>());
            }
        }
        cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y";
        cout << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << "    Length" << endl;
        cout << "- - - - - - - - - - - - - - - - - - -" << endl;
        for(auto a:line2DArr){
            cout << a << endl;
        }
    }else{
        if(currSortCrit=="Pt. 1"){
            if(currSortOrder=="ASC"){
                sort(line3DArr.begin(),line3DArr.end(),Line3D::Pt1Asc);
            }else{
                sort(line3DArr.begin(),line3DArr.end(),Line3D::Pt1Dsc);
            }
        }else if(currSortCrit=="Pt. 2"){
            if(currSortOrder=="ASC"){
                sort(line3DArr.begin(),line3DArr.end(),Line3D::Pt2Asc);
            }else{
                sort(line3DArr.begin(),line3DArr.end(),Line3D::Pt2Dsc);
            }
        }else if(currSortCrit=="Length"){
            if(currSortOrder=="ASC"){
                sort(line3DArr.begin(),line3DArr.end());
            }else{
                sort(line3DArr.begin(),line3DArr.end(),greater<Line3D>());
            }
        }
        cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6) << right << "P1-Z";
        cout << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << setw(6) << right << "P2-Z" << "    Length" << endl;
        cout << "- - - - - - - - - - - - - - - - - - -" << endl;
        for(auto a:line3DArr){
            cout << a << endl;
        }
    }
    userEnter();
    cout << endl;
}

void storeData(){
    string filename;
    int records = 0;
    cout << "Please enter filename: ";
    cin >> filename;
    ofstream writeFile(filename);
    if(currFilter=="Point2D"){
        if(currSortCrit=="x-ordinate"){
            if(currSortOrder=="ASC"){
                sort(pt2DArr.begin(),pt2DArr.end(),Point2D::XAsc);
            }else{
                sort(pt2DArr.begin(),pt2DArr.end(),Point2D::XDsc);
            }
        }else if(currSortCrit=="y-ordinate"){
            if(currSortOrder=="ASC"){
                sort(pt2DArr.begin(),pt2DArr.end(),Point2D::YAsc);
            }else{
                sort(pt2DArr.begin(),pt2DArr.end(),Point2D::YDsc);
            }
        }else if(currSortCrit=="Dist."){
            if(currSortOrder=="ASC"){
                sort(pt2DArr.begin(),pt2DArr.end());
            }else{
                sort(pt2DArr.begin(),pt2DArr.end(),greater<Point2D>());
            }
        }
        for(auto a:pt2DArr){
            writeFile << a << endl;
            records++;
        }
    }else if(currFilter=="Point3D"){
        if(currSortCrit=="x-ordinate"){
            if(currSortOrder=="ASC"){
                sort(pt3DArr.begin(),pt3DArr.end(),Point3D::XAsc);
            }else{
                sort(pt3DArr.begin(),pt3DArr.end(),Point3D::XDsc);
            }
        }else if(currSortCrit=="y-ordinate"){
            if(currSortOrder=="ASC"){
                sort(pt3DArr.begin(),pt3DArr.end(),Point3D::YAsc);
            }else{
                sort(pt3DArr.begin(),pt3DArr.end(),Point3D::YDsc);
            }
        }else if(currSortCrit=="z-ordinate"){
            if(currSortOrder=="ASC"){
                sort(pt3DArr.begin(),pt3DArr.end(),Point3D::ZAsc);
            }else{
                sort(pt3DArr.begin(),pt3DArr.end(),Point3D::ZDsc);
            }
        }else if(currSortCrit=="Dist."){
            if(currSortOrder=="ASC"){
                sort(pt3DArr.begin(),pt3DArr.end());
            }else{
                sort(pt3DArr.begin(),pt3DArr.end(),greater<Point3D>());
            }
        }
        for(auto a:pt3DArr){
            writeFile << a << endl;
            records++;
        }
    }else if(currFilter=="Line2D"){
        if(currSortCrit=="Pt. 1"){
            if(currSortOrder=="ASC"){
                sort(line2DArr.begin(),line2DArr.end(),Line2D::Pt1Asc);
            }else{
                sort(line2DArr.begin(),line2DArr.end(),Line2D::Pt1Dsc);
            }
        }else if(currSortCrit=="Pt. 2"){
            if(currSortOrder=="ASC"){
                sort(line2DArr.begin(),line2DArr.end(),Line2D::Pt2Asc);
            }else{
                sort(line2DArr.begin(),line2DArr.end(),Line2D::Pt2Dsc);
            }
        }else if(currSortCrit=="Length"){
            if(currSortOrder=="ASC"){
                sort(line2DArr.begin(),line2DArr.end());
            }else{
                sort(line2DArr.begin(),line2DArr.end(),greater<Line2D>());
            }
        }
        for(auto a:line2DArr){
            writeFile << a << endl;
            records++;
        }
    }else{
        if(currSortCrit=="Pt. 1"){
            if(currSortOrder=="ASC"){
                sort(line3DArr.begin(),line3DArr.end(),Line3D::Pt1Asc);
            }else{
                sort(line3DArr.begin(),line3DArr.end(),Line3D::Pt1Dsc);
            }
        }else if(currSortCrit=="Pt. 2"){
            if(currSortOrder=="ASC"){
                sort(line3DArr.begin(),line3DArr.end(),Line3D::Pt2Asc);
            }else{
                sort(line3DArr.begin(),line3DArr.end(),Line3D::Pt2Dsc);
            }
        }else if(currSortCrit=="Length"){
            if(currSortOrder=="ASC"){
                sort(line3DArr.begin(),line3DArr.end());
            }else{
                sort(line3DArr.begin(),line3DArr.end(),greater<Line3D>());
            }
        }
        for(auto a:line3DArr){
            writeFile << a << endl;
            records++;
        }
    }
    writeFile.close();
    cout << records << " records output successfully!" << endl;
    cout << endl;
    cout << "Going back to main menu..." << endl;
    cout << endl;
}