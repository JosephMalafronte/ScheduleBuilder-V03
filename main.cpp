//***************************************************************************
//Joseph Malafronte
//Program to organize classes
//11/2/2016
//***************************************************************************


//Declare Libraries
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct classNode{
    string nameOfClass;
    double numHours;
    string daysOfClass;
    string timeString;
    double startTime;
    char startTimeAmOrPm;
    double endTime;
    char endTimeAmOrPm;
};

/*
bool my_predicate(const classNode* item)
{
   // apply some logic and return true or false
   return item.nameOfClass == 42;
}*/

struct hours_key_largest_first
{
    inline bool operator() (const classNode* struct1, const classNode* struct2)
    {
        return (struct1->numHours > struct2->numHours);
    }
};

struct time_key_smallest_first
{
    inline bool operator() (const classNode* struct1, const classNode* struct2)
    {
        return (struct1->startTime < struct2->startTime);
    }
};

vector<classNode*> deleteFromDayList(vector<classNode*> dayList, string className){

    int sizeClassList = dayList.size();
    if(sizeClassList == 0) return dayList;
    int i = 0;
    int deleteCheck = 0;
    for(i; i<sizeClassList;i++){
        classNode *temp = dayList[i];
        string tempString =temp->nameOfClass;
        if(tempString == className){
                deleteCheck = 1;
                break;
        }
    }


    if(deleteCheck == 1) dayList.erase(dayList.begin()+i);
    return dayList;

}

class classSchedule{



    vector<classNode*> allClasses;
    vector<classNode*> mondayAmClasses;
    vector<classNode*> mondayPmClasses;
    vector<classNode*> tuesdayAmClasses;
    vector<classNode*> tuesdayPmClasses;
    vector<classNode*> wednesdayAmClasses;
    vector<classNode*> wednesdayPmClasses;
    vector<classNode*> thursdayAmClasses;
    vector<classNode*> thursdayPmClasses;
    vector<classNode*> fridayAmClasses;
    vector<classNode*> fridayPmClasses;
    //vector< vector<classNode*> > dayClasses(10,vector<classNode*>(10));

    public:
    vector<string> inputLines;
    int numClasses;
    string nameOfSchedule;
    void lineToClasses (string line);
    void printAllClasses ();
    void printWeekSchedule ();
    void removeClass ();
    void clearClasses ();



};


int checkClassError (classNode *a, vector<classNode*> vec){

    int errorTest = 0;
    int vecSize = vec.size();
    for (int i =0; i<vecSize; i++){
        classNode *b = vec[i];
        if (a->startTime >= b->startTime && a->startTime <=b->endTime ){
            errorTest = 1;
        }
        if (a->endTime >= b->startTime && a->endTime <=b->endTime){
            errorTest = 1;
        }
        if(a->startTime <=b->startTime && a->endTime >= b->startTime){
            errorTest = 1;
        }
    }

    return errorTest;
}


void classSchedule::lineToClasses(string line){

    int sizeInpLines = inputLines.size();
    if(sizeInpLines == 0){numClasses = 0;}
    inputLines.push_back(line);

    classNode *a = new classNode;

    istringstream stream1(line);

    string nameOfClass;
    stream1>> nameOfClass;
    a->nameOfClass = nameOfClass;

    string hourString;
    stream1>> hourString;
    int sizeHourString = hourString.size();
    for(int i = 0; i < sizeHourString; i++){
        if(hourString[i] == 'h'){
            hourString.insert(i," ");
        }
    }
        //cout<<"TEST:" <<hourString << endl;
        istringstream stream2(hourString);
        string hourStringB;
        stream2 >> hourStringB;
        double numHours = atof(hourStringB.c_str());
        a->numHours = numHours;
        //cout<<"TEST:" << numHours << endl;

    string allClassesString;
    stream1>> allClassesString;
    a->daysOfClass = allClassesString;


    string timeString;
    stream1>> timeString;
    a->timeString = timeString;
    int sizeTimeString = timeString.size();
    int b = 0;
    for(int i =0; i<sizeTimeString; i++){
        if(timeString[i] == ':'){
            timeString.erase(timeString.begin()+i);
        }
        if(timeString[i] == 'a' && b == 0){
            b = 1;
            a->startTimeAmOrPm = 'a';
            timeString[i] = ' ';
        }
        if(timeString[i] == 'p' && b == 0){
            b = 1;
            a->startTimeAmOrPm = 'p';
            timeString[i] = ' ';
        }
        if(timeString[i] == 'a' && b == 1){
            a->endTimeAmOrPm = 'a';
            timeString[i] = ' ';
        }
        if(timeString[i] == 'p' && b == 1){
            a->endTimeAmOrPm = 'p';
            timeString[i] = ' ';
        }
        if(timeString[i] == '-'){
            timeString[i] = ' ';
        }
    }
        istringstream stream3(timeString);
        string startTimeString;
        stream3 >> startTimeString;
        //a->startTimeString = startTimeString;
        double startTime = atof(startTimeString.c_str());
        a->startTime = startTime;
        stream3 >> startTimeString;
        //cout << "Starttime:" << startTime << endl;
        if(startTime>=1200 && startTime <1300) a->startTimeAmOrPm = 'a';

        string endTimeString;
        stream3 >> endTimeString;
        //a->endTimeString = endTimeString;
        double endTime = atof(endTimeString.c_str());
        a->endTime = endTime;

    int errorTest = 0;

    int sizeAllClasses = allClassesString.size();
    for(int i =0; i<sizeAllClasses; i++){
        if(allClassesString[i] == 'M' && a->startTimeAmOrPm == 'a'){
            errorTest = checkClassError(a, mondayAmClasses);
            if(errorTest == 0){
                    mondayAmClasses.push_back(a);
                    numClasses++;
            }
            else{
               cout << endl << "ERROR OVERLAPPING TIMES COULD NOT ADD CLASS TO SCHEDULE" <<endl;
               break;
            }
        }
        if(allClassesString[i] == 'M' && a->startTimeAmOrPm == 'p'){
            errorTest = checkClassError(a, mondayPmClasses);
            if(errorTest == 0){ mondayPmClasses.push_back(a);
            numClasses++;
            }
            else{
               cout << endl << "ERROR OVERLAPPING TIMES COULD NOT ADD CLASS TO SCHEDULE" <<endl;
               break;
            }
        }
        if(allClassesString[i] == 'T' && allClassesString[i+1] != 'R' && a->startTimeAmOrPm == 'a'){
            errorTest = checkClassError(a, tuesdayAmClasses);
            if(errorTest == 0){ tuesdayAmClasses.push_back(a);
            numClasses++;
            }
            else{
               cout << endl << "ERROR OVERLAPPING TIMES COULD NOT ADD CLASS TO SCHEDULE" <<endl;
               break;
            }
        }
        if(allClassesString[i] == 'T' && allClassesString[i+1] != 'R' && a->startTimeAmOrPm == 'p'){
            errorTest = checkClassError(a, tuesdayPmClasses);
            if(errorTest == 0){ tuesdayPmClasses.push_back(a);
            numClasses++;
            }
            else{
               cout << endl << "ERROR OVERLAPPING TIMES COULD NOT ADD CLASS TO SCHEDULE" <<endl;
               break;
            }
        }
        if(allClassesString[i] == 'W' && a->startTimeAmOrPm == 'a'){
            errorTest = checkClassError(a, wednesdayAmClasses);
            if(errorTest == 0){ wednesdayAmClasses.push_back(a);
            numClasses++;
            }
            else{
               cout << endl << "ERROR OVERLAPPING TIMES COULD NOT ADD CLASS TO SCHEDULE" <<endl;
               break;
            }
        }
        if(allClassesString[i] == 'W' && a->startTimeAmOrPm == 'p'){
            errorTest = checkClassError(a, wednesdayPmClasses);
            if(errorTest == 0){ wednesdayPmClasses.push_back(a);
            numClasses++;
            }
            else{
               cout << endl << "ERROR OVERLAPPING TIMES COULD NOT ADD CLASS TO SCHEDULE" <<endl;
               break;
            }
        }
        if(allClassesString[i] == 'T' && allClassesString[i+1] == 'R' && a->startTimeAmOrPm == 'a'){
            errorTest = checkClassError(a, thursdayAmClasses);
            if(errorTest == 0){ thursdayAmClasses.push_back(a);
            numClasses++;
            }
            else{
               cout << endl << "ERROR OVERLAPPING TIMES COULD NOT ADD CLASS TO SCHEDULE" <<endl;
               break;
            }
        }
        if(allClassesString[i] == 'T' && allClassesString[i+1] == 'R' && a->startTimeAmOrPm == 'p'){
            errorTest = checkClassError(a, thursdayPmClasses);
            if(errorTest == 0){ thursdayPmClasses.push_back(a);
            numClasses++;
            }
            else{
               cout << endl << "ERROR OVERLAPPING TIMES COULD NOT ADD CLASS TO SCHEDULE" <<endl;
               break;
            }
        }
        if(allClassesString[i] == 'F' && a->startTimeAmOrPm == 'a'){
            errorTest = checkClassError(a, fridayAmClasses);
            if(errorTest == 0){ fridayAmClasses.push_back(a);
            numClasses++;
            }
            else{
               cout << endl << "ERROR OVERLAPPING TIMES COULD NOT ADD CLASS TO SCHEDULE" <<endl;
               break;
            }
        }
        if(allClassesString[i] == 'F' && a->startTimeAmOrPm == 'p'){
            errorTest = checkClassError(a, fridayPmClasses);
            if(errorTest == 0){fridayPmClasses.push_back(a);
            numClasses++;
            }
            else{
               cout << endl << "ERROR OVERLAPPING TIMES COULD NOT ADD CLASS TO SCHEDULE" <<endl;
               break;
            }
        }
    }




    if(errorTest == 0) allClasses.push_back(a);
    //if(errorTest == 1)


}

void classSchedule::printAllClasses(){

    double totalHours = 0;

    sort(allClasses.begin(), allClasses.end(), hours_key_largest_first());

    cout << endl << "Full Schedule:" << endl;

    int sizeOfVec = allClasses.size();
    for(int i = 0; i<sizeOfVec; i++){
        classNode *a = new classNode;
        a = allClasses[i];
        cout <<  " " << a->nameOfClass << " ";
        cout << setw(12 - a->nameOfClass.size())<<left<<" "<< a->numHours << "hr ";
            totalHours = totalHours + a->numHours;
        cout << a->daysOfClass << " ";
        cout << a->timeString;
        cout << endl;

    }

    cout<<"Total hours: " << totalHours << endl << endl;

}


void printClass(classNode *a){

    cout<<setw(5)<<left<<" "<<a->nameOfClass;
    int stringSize = a->nameOfClass.size();
    for(int i =0; i < (9- stringSize); i++ ) cout<<" ";
    cout<< a->timeString<<endl;

    /*cout<<" ";
    cout<<a->nameOfClass << " ";
    cout<<a->timeString << endl;*/

}

void classSchedule::printWeekSchedule(){

    sort(mondayAmClasses.begin(), mondayAmClasses.end(), time_key_smallest_first());
    sort(mondayPmClasses.begin(), mondayPmClasses.end(), time_key_smallest_first());
    sort(tuesdayAmClasses.begin(), tuesdayAmClasses.end(), time_key_smallest_first());
    sort(tuesdayPmClasses.begin(), tuesdayPmClasses.end(), time_key_smallest_first());
    sort(wednesdayAmClasses.begin(), wednesdayAmClasses.end(), time_key_smallest_first());
    sort(wednesdayPmClasses.begin(), wednesdayPmClasses.end(), time_key_smallest_first());
    sort(thursdayAmClasses.begin(), thursdayAmClasses.end(), time_key_smallest_first());
    sort(thursdayPmClasses.begin(), thursdayPmClasses.end(), time_key_smallest_first());
    sort(fridayAmClasses.begin(), fridayAmClasses.end(), time_key_smallest_first());
    sort(fridayPmClasses.begin(), fridayPmClasses.end(), time_key_smallest_first());

    cout<<"MONDAY:" << endl;
        int sizeMondayAm = mondayAmClasses.size();
        for(int i = 0; i<sizeMondayAm;i++){
            printClass(mondayAmClasses[i]);
        }
        int sizeMondayPm = mondayPmClasses.size();
        for(int i = 0; i<sizeMondayPm;i++){
            printClass(mondayPmClasses[i]);
        }
    cout<<"TUESDAY:" << endl;
        int sizetuesdayAm = tuesdayAmClasses.size();
        for(int i = 0; i<sizetuesdayAm;i++){
            printClass(tuesdayAmClasses[i]);
        }
        int sizetuesdayPm = tuesdayPmClasses.size();
        for(int i = 0; i<sizetuesdayPm;i++){
            printClass(tuesdayPmClasses[i]);
        }
    cout<<"WEDNESDAY:" << endl;
        int sizewednesdayAm = wednesdayAmClasses.size();
        for(int i = 0; i<sizewednesdayAm;i++){

            printClass(wednesdayAmClasses[i]);
        }
        int sizewednesdayPm = wednesdayPmClasses.size();
        for(int i = 0; i<sizewednesdayPm;i++){
           // cout << "test" <<endl;
            printClass(wednesdayPmClasses[i]);
        }
    cout<<"THURSDAY:" << endl;
        int sizethursdayAm = thursdayAmClasses.size();
        for(int i = 0; i<sizethursdayAm;i++){
            printClass(thursdayAmClasses[i]);
        }
        int sizethursdayPm = thursdayPmClasses.size();
        for(int i = 0; i<sizethursdayPm;i++){
            printClass(thursdayPmClasses[i]);
        }
    cout<<"FRIDAY:" << endl;
        int sizefridayAm = fridayAmClasses.size();
        for(int i = 0; i<sizefridayAm;i++){
            printClass(fridayAmClasses[i]);
        }
        int sizefridayPm = fridayPmClasses.size();
        for(int i = 0; i<sizefridayPm;i++){
            printClass(fridayPmClasses[i]);
        }

        cout << endl;


}

void classSchedule::removeClass(){

    cout<< endl << "List of classes:" <<endl;
        int sizeOfVec = allClasses.size();
        for(int i = 0; i<sizeOfVec; i++){
            classNode *a = new classNode;
            a = allClasses[i];
            cout << a->nameOfClass << " ";
            cout << a->numHours << "hr ";
            cout << a->daysOfClass << " ";
            cout << a->timeString;
            cout << endl;
        }

        string input;

        cout<< endl << "Enter the name of the class you wish to remove or enter 0 to exit" << endl;
        cin >> input;

        for(int i =0; i<sizeOfVec;i++){
            classNode *a = new classNode;
            a = allClasses[i];
            if(input == a->nameOfClass){
                allClasses.erase(allClasses.begin()+i);
            }
        }

        int sizeInputLines = inputLines.size();
        for(int i=0;i<sizeInputLines;i++){
            string fullString = inputLines[i];
            istringstream stream1(fullString);
            string test;
            stream1>>test;
            if(test == input) inputLines.erase(inputLines.begin()+i);
        }


        mondayAmClasses = deleteFromDayList(mondayAmClasses, input);
        mondayPmClasses = deleteFromDayList(mondayPmClasses, input);
        tuesdayAmClasses=deleteFromDayList(tuesdayAmClasses, input);
        tuesdayPmClasses=deleteFromDayList(tuesdayPmClasses, input);
        wednesdayAmClasses=deleteFromDayList(wednesdayAmClasses, input);
        wednesdayPmClasses=deleteFromDayList(wednesdayPmClasses, input);
        thursdayAmClasses=deleteFromDayList(thursdayAmClasses, input);
        thursdayPmClasses=deleteFromDayList(thursdayPmClasses, input);
        fridayAmClasses=deleteFromDayList(fridayAmClasses, input);
        fridayPmClasses = deleteFromDayList(fridayPmClasses, input);


        int sizeOfVecB = inputLines.size();
        for(int i =0; i<sizeOfVecB;i++){
            string test = inputLines[i];
            if(input == test){
                inputLines.erase(inputLines.begin()+i);
            }
        }


       // mondayAmClasses.erase( remove_if(mondayAmClasses.begin(), mondayAmClasses.end(), my_predicate), mondayAmClasses.end() );

}


void classSchedule::clearClasses(){




}


int main()
{
    cout << "***Schedule Organizer***" << endl << endl;

    int userChoice = 500;
    classSchedule cs;
    classSchedule csB;
    while(userChoice != 0){
    cout<< "Enter a number to perform the operation:" << endl;
    cout<< " 0: Exit The program" << endl;
    cout<< " 1: Add a class to the schedule" << endl;
    cout<< " 2: Remove a class from the schedule" << endl;
    cout<< " 3: List full class schedule" << endl;
    cout<< " 4: List weekly class schedule" << endl;
    cout<< " 5: Open a saved schedule" << endl;
    cout<< " 6: Save schedule" << endl;
    cin >> userChoice;
    cin.ignore();


    if(userChoice == 0) break;
    if(userChoice == 1){
    cout << endl <<  "To add a class please input a class in the same format as the example below." << endl;
    cout << "       EXAMPLE:CS100 4hr M,W,F 11:00am-11:50am" << endl;
    string lineStart;
    getline(cin, lineStart);
    cs.lineToClasses(lineStart);
    }

    if(userChoice == 2) cs.removeClass();


    if(userChoice == 3)cs.printAllClasses();

    if(userChoice == 4)cs.printWeekSchedule();

    if(userChoice == 5)
        {
        cout<<endl;

        cs = csB;
        int userAnswer;
        ifstream myfile0 ("savedFiles.txt");
        string fileName;
        if(myfile0.is_open()){
            cout<<"Choose a file number:"<<endl;
            string line;
            int j = 0;

            while(myfile0){
                getline(myfile0,line);
                if(line == "")break;
                cout<<j<<": "<<line<<endl;
                j++;
            }
            cout<<endl;
            cin>>userAnswer;

        }
        ifstream myfile1 ("savedFiles.txt");
        if(myfile1.is_open()){
                string line;
                for(int i = -1; i<userAnswer;i++){
                    getline(myfile1,line);
                }
                fileName = line;
        }
        ifstream myfile((fileName+".txt").c_str());
        if(myfile.is_open()){
            string line;
            //getline(myfile, line);
            while(myfile){
                getline(myfile,line);
                if(line == "") break;
                cs.lineToClasses(line);
            }
        }

        cout<<"Successfully opened file " << fileName<<endl;

    }

    if(userChoice == 6){
        /*std::ofstream ofs;
        ofs.open("savedFile.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close;*/


        string userFileName;

        ifstream myfileA ("savedFiles.txt");
        if(myfileA.is_open()){
            cout<<"List of saved files in this location:"<<endl;
            string line;
            int j = 0;

            while(myfileA){
                getline(myfileA,line);
                if(line == "")break;
                cout<<line<<endl;
                j++;
            }

        }

        cout<<"What would you like to name your saved file?:";
        cin>>userFileName;

        ifstream myfile0 ("savedFiles.txt");
        string fileName;
        char userAns = 'P';
        if(myfile0.is_open()){

            string line;
            int j = 0;

            while(myfile0){
                getline(myfile0,line);
                if(userFileName == line){
                        cout<<"There is already a file with that name would you like to replace it? (Y/N)"<<endl;
                        cin>>userAns;
                    }
            }
            cout<<endl;

        }
        if(userAns == 'Y'){
                remove((userFileName+".txt").c_str());
        }

        if(userAns != 'N'){
        ofstream outputfile;
        outputfile.open((userFileName+".txt").c_str());
        int sizeOfVec = cs.inputLines.size();
        for(int i= 0;i<sizeOfVec;i++){
            string output;
            output = cs.inputLines[i];
            outputfile << output;
            outputfile << '\n';

        }
        if(userAns == 'P'){
        ofstream ofs;
        ofs.open ("savedFiles.txt", std::ofstream::out | std::ofstream::app);

        ofs << userFileName;
        ofs <<endl;

        ofs.close();
        }
        }





    }


    cout<< endl;

    }
    return 0;
}
