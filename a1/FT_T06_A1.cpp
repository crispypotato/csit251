#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>
using namespace std;

int xUpper, yUpper; //upper ranges of x and y axis; lower range will always =0
vector<string> fileVector; // stores all files for city grid areas, cloud coverage and atmospheric pressure
vector<string> cityLocArr;
vector<string> cloudCoverArr;
vector<string> pressureArr;
vector<string> uniqueCityID;

struct grid{
	string cityID;
	string cityName;
	int cloud;
	int cloudSingle;
	char cloudLMH;
	int pressure;
	int pressureSingle;
	string pressureLMH;
};
struct grid ** array2D = nullptr;
struct citySummary{
	string cityID;
	string cityName;
	vector<int> xCoord;
	vector<int> yCoord;
	double avgCloud;
	double avgPressure;
};
struct citySummary * cityLocPointer = nullptr;

void menu();
void readAndDisplay(string filename);
vector<string> splitString(string str, string delim);
void init2DArray(int col, int row);
void initCityArray(int noOfCity);
void displayCityMap();
void userEnter();
void displayCCIdxMap();
void displayCCLMHMap();
void displayPressureMap();
void displayPressureLMHMap();
void forecastSummary();
void safelyDeallocateMemory(int col, int row);

int main(){
    int choice;
    string configfile;
    while(choice!=8){
        choice = 0;
        menu(); // initializes main menu
        cin >> choice; // user enters choice
        switch (choice)
        {
            case 1: // read and process config file
                cout << "[Read in and process a configuration file]" << endl;
                cout << "Please enter config filename: ";
                cin >> configfile;
                cout << endl;
                readAndDisplay(configfile);
                break;
            case 2: // display city map
                cout << "[Display city map]" << endl;
                displayCityMap();
                userEnter();
                break;
            case 3: // display cloud coverage map (cloudiness index)
                cout << "[Display cloud coverage map (cloudiness index)]" << endl;
                displayCCIdxMap();
                userEnter();
                break;
            case 4: // display cloud coverage map (LMH index)
                cout << "[Display cloud coverage map (LMH symbols)]" << endl;
                displayCCLMHMap();
                userEnter();
                break;
            case 5: // display atmospheric pressure map (pressure index)
                cout << "[Display atmospheric pressure map (pressure index)]" << endl;
                displayPressureMap();
                userEnter();
                break;
            case 6: // display atmospheric pressure map (LMH index)
                cout << "[Display atmospheric pressure map (LMH symbols))]" << endl;
                displayPressureLMHMap();
                userEnter();
                break;
            case 7: // show weather forecast summary report
                cout << "[Show weather forecast summary report]" << endl;
                forecastSummary();
                userEnter();
                break;
            case 8:
                cout << "Thank you for using the Weather Information Processing System. Exiting Application..." << endl;
                safelyDeallocateMemory(xUpper, yUpper);
                break;
            default: // when int is not any of the choices
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }
    return 0;
}

void menu(){ // main menu
    cout << "Student ID " << setw(11) << right <<": 7910502" << endl;
    cout << "Student Name " << setw(12) << right << ": Toh Jing Wen" << endl;
    cout << "-------------------------------" << endl;
    cout << "Welcome to Weather Information Processing System!" << endl;
    cout << endl;
    cout << "1)\tRead in and process a configuration file" << endl;
    cout << "2)\tDisplay city map" << endl;
    cout << "3)\tDisplay cloud coverage map (cloudiness index)" << endl;
    cout << "4)\tDisplay cloud coverage map (LMH symbols)" << endl;
    cout << "5)\tDisplay atmospheric pressure map (pressure index)" << endl;
    cout << "6)\tDisplay atmospheric pressure map (LMH symbols)" << endl;
    cout << "7)\tShow weather forecast summary report" << endl;
    cout << "8)\tQuit" << endl;
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

void init2DArray(int col, int row){ // initialize 2d array
	array2D = new struct grid * [row];
	for(int i = 0; i < row; i++){
		array2D[i] = new struct grid[col];
    }
}

void initCityArray(int noOfCity){ // initialize array for each city range
	cityLocPointer = new struct citySummary [noOfCity];
	for(int i = 0; i < uniqueCityID.size(); i++){
		struct citySummary citySum = cityLocPointer[i];
		citySum.cityID = uniqueCityID[i];
		for(int i = 0; i <= yUpper; i++){
			for(int j = 0; j <= xUpper; j++){
				struct grid temp = array2D[j][i];
				if(citySum.cityID == temp.cityID){
					citySum.cityName = temp.cityName;
					citySum.xCoord.push_back(j);
					citySum.yCoord.push_back(i);
				}
			}
		}
		sort(citySum.xCoord.begin(), citySum.xCoord.end());
		sort(citySum.yCoord.begin(), citySum.yCoord.end());
		cityLocPointer[i] = citySum;
	}
}

char LMH(int index){
    if(index<35){
        return 'L';
    }else if(index>=35 && index<65){
        return 'M';
    }else{
        return 'H';
    }
}

void openCityFile(string filename){ // opens and stores data from city file
	int x, y;
	ifstream inputFile;
	inputFile.open(filename);
	while(inputFile.good()){
        string line;
        getline(inputFile, line);
        if(line!=""){
            line.erase(0,1);
            vector<string> tokenStringVector = splitString(line, ", ");
            x = stoi(tokenStringVector[0]);
            tokenStringVector = splitString(tokenStringVector[1], "]-");
            y = stoi(tokenStringVector[0]);
            struct grid temp = array2D[x][y];
            tokenStringVector = splitString(tokenStringVector[1], "-");
            temp.cityID = tokenStringVector[0];
            temp.cityName = tokenStringVector[1];
            if(find(uniqueCityID.begin(), uniqueCityID.end(), temp.cityID) == uniqueCityID.end()){
                uniqueCityID.push_back(temp.cityID);
            }
            array2D[x][y] = temp;
            tokenStringVector.clear();
        }
	}
	initCityArray(uniqueCityID.size());
	inputFile.close();
}

void openCloudFile(string filename){ // opens and stores data from cloud file
	int x, y;
	ifstream inputFile;
	inputFile.open(filename);
	while(inputFile.good()){
		string line;
        getline(inputFile, line);
        if(line!=""){
            line.erase(0,1);
            vector<string> tokenStringVector = splitString(line, ", ");
            x = stoi(tokenStringVector[0]);
            tokenStringVector = splitString(tokenStringVector[1], "]-");
            y = stoi(tokenStringVector[0]);
            struct grid temp = array2D[x][y];
            temp.cloud = stoi(tokenStringVector[1]);
            temp.cloudSingle = (stoi(tokenStringVector[1])) / 10;
            temp.cloudLMH = LMH(stoi(tokenStringVector[1]));
            array2D[x][y] = temp;
            tokenStringVector.clear();
        }
    }
	inputFile.close();
}

void openPressureFile(string filename){ //opens and stores data from pressure file
	int x, y;
	ifstream inputFile;
	inputFile.open(filename);
	while(inputFile.good()){
        string line;
        getline(inputFile, line);
        if(line!=""){
            line.erase(0,1);
            vector<string> splitCoord = splitString(line, ", ");
            x = stoi(splitCoord[0]);
            splitCoord = splitString(splitCoord[1], "]-");
            y = stoi(splitCoord[0]);
            struct grid temp = array2D[x][y];
            temp.pressure = stoi(splitCoord[1]);
            temp.pressureSingle = (stoi(splitCoord[1])) / 10;
            temp.pressureLMH = LMH(stoi(splitCoord[1]));
            array2D[x][y] = temp;
            splitCoord.clear();
        }
    }
	inputFile.close();
}

void readAndDisplay(string filename){ // option 1: reading config file
    ifstream inputFile;
    inputFile.open(filename.c_str());
    while(inputFile.good()){
        string aLine;
        getline(inputFile, aLine);
        if(aLine.find("GridX_IdxRange") != string::npos){
            cout << "Reading in " << aLine;
            vector<string> xRange = splitString(aLine, "="); //extracts range
            vector<string> xRange2 = splitString(xRange[1], "-"); //separates upper and lower limit
            xUpper = stoi(xRange2[1]); //stores upper limit of x-axis
            cout << " ... done!" << endl;
        }
        else if(aLine.find("GridY_IdxRange") != string::npos){
            cout << "Reading in " << aLine;
            vector<string> yRange = splitString(aLine, "="); //extracts range
            vector<string> yRange2 = splitString(yRange[1], "-"); //separates upper and lower limit
            yUpper = stoi(yRange2[1]); //stores upper limit of y-axis
            cout << " ... done!" << endl;
        }
        else if(aLine.find(".txt") != string::npos){
            cout << "Storing data from input file: " << aLine << " ... done!" << endl;
            fileVector.push_back(aLine);
        }else{
            //do nothing
        }
    }
    inputFile.close();
    init2DArray(yUpper+1,xUpper+1);
	openCityFile(fileVector[0]);
	openCloudFile(fileVector[1]);
	openPressureFile(fileVector[2]);
    cout << "All records successfully stored. Going back to main menu..." << endl;
    cout << endl;
}

void displayCityMap(){ // option 2: display city map
    if(cityLocArr.empty()){
        ifstream inputFile;
        inputFile.open(fileVector[0]); // open citylocation
        while(inputFile.good()){
            string line;
            getline(inputFile, line);
            cityLocArr.push_back(line);
        }
    }
    for(int i=0;i<=(yUpper+3);i++){// map grid; i goes through y-axis, j goes through x-axis
        if(i>0 && i<(yUpper+2)){
            if(i<10){ // printing numerical y-axis
                cout << yUpper-i+1 << " ";
            }else{
                cout << yUpper-i+1;
            }
        }else{
            cout << "  ";
        }
        for(int j=0;j<=(xUpper+2);j++){
            if(i==(yUpper+2) || i==0 || ((j==0 || j==(xUpper+2)) && i!=(yUpper+3))){ // print grid borders
                cout << " # ";
            }else if(i==(yUpper+3)){ // printing numerical x-axis
                if(j>2 && j<(xUpper+3)){
                    cout << " " << j-2 << " ";
                }else if(j==2){
                    cout << j-2 << " ";
                }else{
                    cout << "  ";
                }
            }else{ // populate data from file into map grid
                struct grid temp = array2D[j-1][yUpper-i+1];
                if(temp.cityID != "")
                    cout << " " << temp.cityID << " ";
                else{
                    cout << "   ";
                }
            }
        }
        cout << endl;
    }
}

void userEnter(){ // ensure user presses enter to return to main menu
	int i = 0;
	while(i == 0){
		cout << "Press <enter> to go back to main menu...";
		cin.ignore();
		if (cin.get() == '\n'){
			i = 1;
        }
	}
	cout << endl;
}

void displayCCIdxMap(){ // option 3: display cloud coverage by index
    if(cloudCoverArr.empty()){
        ifstream inputFile;
        inputFile.open(fileVector[1]); // open cloudcover
        while(inputFile.good()){
            string line;
            getline(inputFile, line);
            cloudCoverArr.push_back(line);
        }
    }
    sort(cloudCoverArr.begin(),cloudCoverArr.end(), greater<string>()); // sort in reverse axis order
    for(int i=0;i<=(yUpper+3);i++){// map grid; i goes through y-axis, j goes through x-axis
        if(i>0 && i<(yUpper+2)){
            if(i<10){ // printing numerical y-axis
                cout << yUpper-i+1 << " ";
            }else{
                cout << yUpper-i+1;
            }
        }else{
            cout << "  ";
        }
        for(int j=0;j<=(xUpper+2);j++){
            if(i==(yUpper+2) || i==0 || ((j==0 || j==(xUpper+2)) && i!=(yUpper+3))){ // print grid borders
                cout << " # ";
            }else if(i==(yUpper+3)){ // printing numerical x-axis
                if(j>2 && j<(xUpper+3)){
                    cout << " " << j-2 << " ";
                }else if(j==2){
                    cout << j-2 << " ";
                }else{
                    cout << "  ";
                }
            }else{ // populate data from file into map grid
                struct grid temp = array2D[j-1][yUpper-i+1];
                cout << " " << temp.cloudSingle << " ";
            }
        }
        cout << endl;
    }
}

void displayCCLMHMap(){ //option 4: display cloud coverage by LMH
    if(cloudCoverArr.empty()){
        ifstream inputFile;
        inputFile.open(fileVector[1]); // open cloudcover
        while(inputFile.good()){
            string line;
            getline(inputFile, line);
            cloudCoverArr.push_back(line);
        }
    }
    sort(cloudCoverArr.begin(),cloudCoverArr.end(), greater<string>()); // sort in reverse axis order
    for(int i=0;i<=(yUpper+3);i++){// map grid; i goes through y-axis, j goes through x-axis
        if(i>0 && i<(yUpper+2)){
            if(i<10){ // printing numerical y-axis
                cout << yUpper-i+1 << " ";
            }else{
                cout << yUpper-i+1;
            }
        }else{
            cout << "  ";
        }
        for(int j=0;j<=(xUpper+2);j++){
            if(i==(yUpper+2) || i==0 || ((j==0 || j==(xUpper+2)) && i!=(yUpper+3))){ // print grid borders
                cout << " # ";
            }else if(i==(yUpper+3)){ // printing numerical x-axis
                if(j>2 && j<(xUpper+3)){
                    cout << " " << j-2 << " ";
                }else if(j==2){
                    cout << j-2 << " ";
                }else{
                    cout << "  ";
                }
            }else{ // populate data from file into map grid
                struct grid temp = array2D[j-1][yUpper-i+1];
                cout << " " << temp.cloudLMH << " ";
            }
        }
        cout << endl;
    }
}

void displayPressureMap(){ // option 5: display atm pressure by index
    if(pressureArr.empty()){
        ifstream inputFile;
        inputFile.open(fileVector[2]); // open pressure
        while(inputFile.good()){
            string line;
            getline(inputFile, line);
            pressureArr.push_back(line);
        }
    }
    sort(pressureArr.begin(),pressureArr.end(), greater<string>()); // sort in reverse axis order
    for(int i=0;i<=(yUpper+3);i++){// map grid; i goes through y-axis, j goes through x-axis
        if(i>0 && i<(yUpper+2)){
            if(i<10){ // printing numerical y-axis
                cout << yUpper-i+1 << " ";
            }else{
                cout << yUpper-i+1;
            }
        }else{
            cout << "  ";
        }
        for(int j=0;j<=(xUpper+2);j++){
            if(i==(yUpper+2) || i==0 || ((j==0 || j==(xUpper+2)) && i!=(yUpper+3))){ // print grid borders
                cout << " # ";
            }else if(i==(yUpper+3)){ // printing numerical x-axis
                if(j>2 && j<(xUpper+3)){
                    cout << " " << j-2 << " ";
                }else if(j==2){
                    cout << j-2 << " ";
                }else{
                    cout << "  ";
                }
            }else{ // populate data from file into map grid
                struct grid temp = array2D[j-1][yUpper-i+1];
                cout << " " << temp.pressureSingle << " ";
            }
        }
        cout << endl;
    }
}

void displayPressureLMHMap(){ // option 6: display atm pressure by LMH
    if(pressureArr.empty()){
        ifstream inputFile;
        inputFile.open(fileVector[2]); // open pressure
        while(inputFile.good()){
            string line;
            getline(inputFile, line);
            pressureArr.push_back(line);
        }
    }
    sort(pressureArr.begin(),pressureArr.end(), greater<string>()); // sort in reverse axis order
    for(int i=0;i<=(yUpper+3);i++){// map grid; i goes through y-axis, j goes through x-axis
        if(i>0 && i<(yUpper+2)){
            if(i<10){ // printing numerical y-axis
                cout << yUpper-i+1 << " ";
            }else{
                cout << yUpper-i+1;
            }
        }else{
            cout << "  ";
        }
        for(int j=0;j<=(xUpper+2);j++){
            if(i==(yUpper+2) || i==0 || ((j==0 || j==(xUpper+2)) && i!=(yUpper+3))){ // print grid borders
                cout << " # ";
            }else if(i==(yUpper+3)){ // printing numerical x-axis
                if(j>2 && j<(xUpper+3)){
                    cout << " " << j-2 << " ";
                }else if(j==2){
                    cout << j-2 << " ";
                }else{
                    cout << "  ";
                }
            }else{ // populate data from file into map grid
                struct grid temp = array2D[j-1][yUpper-i+1];
                cout << " " << temp.pressureLMH << " ";
            }
        }
        cout << endl;
    }
}

int probOfRain(char ACC, char AP){
	int probability;
	if(AP =='L' && ACC == 'H'){
		probability = 90;
	}
	else if(AP == 'L' && ACC == 'M'){
		probability = 80;
	}
	else if(AP == 'L' && ACC == 'L'){
		probability = 70;
	}
	else if(AP == 'M' && ACC == 'H'){
		probability = 60;
	}
	else if(AP == 'M' && ACC == 'M'){
		probability = 50;
	}
	else if(AP == 'M' && ACC == 'L'){
		probability = 40;
	}
	else if(AP == 'H' && ACC == 'H'){
		probability = 30;
	}
	else if(AP == 'H' && ACC == 'M'){
		probability = 20;
	}
	else if(AP == 'H' && ACC == 'L'){
		probability = 10;
	}
	else {
		probability = 0;
	}
	return probability;
}

void rainASCII(int probability){ // graphics for rain prob
	if(probability == 90){
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << "\\\\\\\\\\" << endl << endl;
	}
	else if(probability == 80){
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << " \\\\\\\\" << endl << endl;
	}
	else if(probability == 70){
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << "  \\\\\\" << endl << endl;
	}
	else if(probability == 60){
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << "   \\\\" << endl << endl;
	}
	else if(probability == 50){
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << "    \\" << endl << endl;
	}
	else if(probability == 40){
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl << endl;
	}
	else if(probability == 30){
		cout << "~~~" << endl;
		cout << "~~~~" << endl << endl;
	}
	else if(probability == 20){
		cout << "~~" << endl;
		cout << "~~~" << endl << endl;
	}
	else if(probability == 10){
		cout << "~" << endl;
		cout << "~~" << endl << endl;
	}
}

void forecastSummary(){ // option 7: weather forecast report
    cout << "Weather Forecast Summary Report" << endl;
    cout << "-------------------------------" << endl;
    vector<string> data;
    vector<int> cityID;
    vector<string> cityName;
    for(auto a:cityLocArr){
        if(a.length()!=0){
            data = splitString(a,"-");
            if(find(cityID.begin(), cityID.end(),stoi(data[1]))==cityID.end()){ // check if value is already present in vector
                cityID.push_back(stoi(data[1]));
            }
            if(find(cityName.begin(), cityName.end(),data[2])==cityName.end()){
                cityName.push_back(data[2]);
            }
        }
    }
    if(cityID.size()==cityName.size()){ // check that no. of stored cityID and cityName values match
        for(int i=0; i<cityID.size(); i++){ // loop through each city
            vector<string> coordArr;
            vector<string> perimeterCoordArr;
            float cloudCoverSum=0;
            float pressureSum=0;
            float cloudCoverAvg=0;
            float pressureAvg=0;
            char avgCCLMH = ' ';
            char avgPressureLMH = ' ';
            float probability=0;
            cout << "City Name : " << cityName[i] << endl;
            cout << "City ID : " << cityID[i] << endl;
            for(auto a:cityLocArr){ // extract coordinates of each city
                if(a.length()!=0){
                    data = splitString(a,"-");
                    if(data[2].find(cityName[i]) != string::npos){
                        coordArr.push_back(data[0]);
                    }
                }
            }
            perimeterCoordArr = coordArr;
            for(auto coord:coordArr){ // extract corresponding CC and pressure values in coords
                int xAxis, yAxis;
                coord.erase(0,1);
                coord.erase(coord.end()-1);
                vector<string> v = splitString(coord,", ");
                xAxis = stoi(v[0]);
                yAxis = stoi(v[1]);
                ostringstream adj; // compare and extract perimeter coords
                adj << "[" << xAxis-1 << ", " << yAxis-1 << "]";
                if(find(perimeterCoordArr.begin(), perimeterCoordArr.end(),adj.str())==perimeterCoordArr.end()){
                    perimeterCoordArr.push_back(adj.str());
                }
                adj.clear();
                adj.str(string());
                adj << "[" << xAxis-1 << ", " << yAxis << "]";
                if(find(perimeterCoordArr.begin(), perimeterCoordArr.end(),adj.str())==perimeterCoordArr.end()){
                    perimeterCoordArr.push_back(adj.str());
                }
                adj.clear();
                adj.str(string());
                adj << "[" << xAxis << ", " << yAxis-1 << "]";
                if(find(perimeterCoordArr.begin(), perimeterCoordArr.end(),adj.str())==perimeterCoordArr.end()){
                    perimeterCoordArr.push_back(adj.str());
                }
                adj.clear();
                adj.str(string());
                if(xAxis!=xUpper){
                    adj << "[" << xAxis+1 << ", " << yAxis-1 << "]";
                    if(find(perimeterCoordArr.begin(), perimeterCoordArr.end(),adj.str())==perimeterCoordArr.end()){
                        perimeterCoordArr.push_back(adj.str());
                    }
                    adj.clear();
                    adj.str(string());
                    adj << "[" << xAxis+1 << ", " << yAxis << "]";
                    if(find(perimeterCoordArr.begin(), perimeterCoordArr.end(),adj.str())==perimeterCoordArr.end()){
                        perimeterCoordArr.push_back(adj.str());
                    }
                    adj.clear();
                    adj.str(string());
                    if(yAxis!=xUpper){
                        adj << "[" << xAxis+1 << ", " << yAxis+1 << "]";
                        if(find(perimeterCoordArr.begin(), perimeterCoordArr.end(),adj.str())==perimeterCoordArr.end()){
                            perimeterCoordArr.push_back(adj.str());
                        }
                    }
                }
                adj.clear();
                adj.str(string());
                if(yAxis!=xUpper){
                    adj << "[" << xAxis << ", " << yAxis+1 << "]";
                    if(find(perimeterCoordArr.begin(), perimeterCoordArr.end(),adj.str())==perimeterCoordArr.end()){
                        perimeterCoordArr.push_back(adj.str());
                    }
                    adj.clear();
                    adj.str(string());
                    adj << "[" << xAxis-1 << ", " << yAxis+1 << "]";
                    if(find(perimeterCoordArr.begin(), perimeterCoordArr.end(),adj.str())==perimeterCoordArr.end()){
                        perimeterCoordArr.push_back(adj.str());
                    }
                    adj.clear();
                    adj.str(string());
                }
            }
            for(auto coord:perimeterCoordArr){ // compare each coord in perimeter with:
                for(auto CCData:cloudCoverArr){ // 1. cloud cover index
                    if(CCData.find(coord) != string::npos){
                        data = splitString(CCData,"-");
                        cloudCoverSum+=stoi(data[1]);
                    }
                }
                for(auto PData:pressureArr){ // 2. pressure index
                     if(PData.find(coord) != string::npos){
                        data = splitString(PData,"-");
                        pressureSum+=stoi(data[1]);
                    }
                }
            }
            cloudCoverAvg = cloudCoverSum / perimeterCoordArr.size();
            pressureAvg = pressureSum / perimeterCoordArr.size();
            avgCCLMH = LMH(cloudCoverAvg);
            avgPressureLMH = LMH(pressureAvg);
            probability = probOfRain(avgCCLMH,avgPressureLMH);
            cout << "Ave. Cloud Cover (ACC)" << " : " << fixed << setprecision(2) << cloudCoverAvg << " (" << avgCCLMH << ")" << endl;
            cout << "Ave. Pressure (AP)" << " : " << fixed << setprecision(2) << pressureAvg << " (" << avgPressureLMH << ")" << endl;
            cout << "Probability of Rain (%) : " << fixed << setprecision(2) << probability << endl;
		    rainASCII(probability);
            cout << endl;
        }
    }
}

void safelyDeallocateMemory(int col, int row){
	if(col <= 0){
		return;
    }
	for(int i = 0; i < row; i++){
		delete [] array2D [i];
    }
	delete[] array2D;
	delete[] cityLocPointer;
	uniqueCityID.clear();
}