//Created By:
//Mariam Essam 20220511 S20
//Daniel Sameh 20221050 S20
//Ali Mohsen   20221106 S19

#ifndef VOLEMACHINE_VOLEMACHINE_H
#define VOLEMACHINE_VOLEMACHINE_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>
#include <vector>
#include<QInputDialog>
using namespace std;

class Register{
public:
    string data;
    Register();
};
class memory{
    //void setMemory();
public:
    //string memo [256];
    memory();
    map<string,string>memoryData;
    void reset();

};

class machine{
public:
    string pCounter="00";
    string pc="00";
    string tempCounter;
    Register R[16];
    int programLength=0;
    memory machineMemory;
    int x=2;
    vector<string>inst;
    int outRegister=-1;
public:

    machine();
    void setProgramCounter(string counter);
    void inputIntoMemory(const string& fileName);

    void execute();
    bool isValidCode(const string& first,const string& second);

    void instruction1(string execute);
    void instruction2(string execute);
    void instruction3(string execute);
    void instruction4(string execute);
    void instruction5(string execute);
    void instructionB(string execute);

    void reset();
    void displayMemory();
    void displayRegisters();

};


#endif //VOLEMACHINE_VOLEMACHINE_H
