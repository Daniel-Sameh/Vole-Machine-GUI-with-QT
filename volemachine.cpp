//Created By:
//Mariam Essam 20220511 S20
//Daniel Sameh 20221050 S20
//Ali Mohsen   20221106 S19
#include "volemachine.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <cctype>
#include <math.h>
#include <vector>
#include<QTextStream>
#include<QInputDialog>
using namespace std;
void machine::inputIntoMemory(const string& word) {
    string tmp;
    // bool ok = true;
    ++programLength;
    if(word.size()==7){ //0x1 0x2-> 12
        string x= string(1, word[2]) + string(1, word[6]);
        for (auto &c: x)c = toupper(c);
        machineMemory.memoryData[pCounter]=x;
    }else if(word.size()==4){ //0xAB -> AB
        string x=word.substr(2);
        for (auto &c: x)c = toupper(c);
        machineMemory.memoryData[pCounter] = x;
    }else{
        machineMemory.memoryData[pCounter]="00";
    }

    //    // --x;
    //    //Increment the pCounter
    //if(x==0){

    int temp =stoul(pCounter, 0, 16); temp++;//converting from Hexadecimal to decimal
    ostringstream os;
    os << hex << temp; //converting from decimal to hexadecimal again
    if (os.str().size() == 1)
        pCounter = "0" + os.str();//"a" -> "0a"
    else
        pCounter = os.str();
    for (auto &c: pCounter)c = toupper(c); //"ab" -> "AB"
    //    // x=2;
    //    // }
}


memory::memory() {
    for (int i = 0; i < 256; ++i) {
        ostringstream os;
        os << hex << i; //converting from decimal to hexadecimal again
        string x = os.str();
        if (x.size() == 1)
            x = "0" + x; //"a" -> "0a"
        for (auto &c: x)c = toupper(c); //"ab" -> "AB"
        memoryData[x] = "00";
    }
}

void memory::reset() {
    for (auto& i:memoryData) {
        i.second="00";
    }
}


Register::Register() {
    data = "00";
}

machine::machine(){
    //cout<<"Enter the program counter: ";
    //string c;
    //cin>>c;
    //pCounter=c;
    //tempCounter=c;
}

void machine::instruction1(string execute) {
    int memory_index = 0;
    int power = 0;
    for (int i = 3; i >= 2; --i) {
        if (isalpha(execute[i])) {
            memory_index += pow(16, power) * ((execute[i] - 'A') + 10);
        } else {
            memory_index += pow(16, power) * (execute[i] - '0');
        }
        power++;
    }

    int reg_index = 0;
    if (isalpha(execute[1])) {
        reg_index = (execute[1] - 'A') + 10;
    } else {
        reg_index = execute[1] - '0';
    }
    ostringstream os;
    os << hex << memory_index; //converting from decimal to hexadecimal again
    string tmp = os.str();

    if (tmp.size() == 1)
        tmp = "0" + tmp; //"a" -> "0a"
    for (auto &c: tmp)c = toupper(c); //"ab" -> "AB"
    R[reg_index].data = machineMemory.memoryData[tmp];
}

void machine::instruction2(string execute) {
    int reg_index = 0;
    if (isalpha(execute[1])) {
        reg_index = (execute[1] - 'A') + 10;
    } else {
        reg_index = execute[1] - '0';
    }

    string sequence = execute.substr(2);
    R[reg_index].data = sequence;
}

void machine::instruction3(std::string execute) {
    int reg_index = 0;
    if (isalpha(execute[1])) {
        reg_index = (execute[1] - 'A') + 10;
    } else {
        reg_index = execute[1] - '0';
    }

    if (execute.substr(2) == "00") {
        cout<<"Register#"<<reg_index<<"= "<<R[reg_index].data<<'\n';
        outRegister=reg_index;
    }
    int memory_index = 0;
    int power = 0;
    for (int i = 3; i >= 2; --i) {
        if (isalpha(execute[i])) {
            memory_index += pow(16, power) * ((execute[i] - 'A') + 10);
        } else {
            memory_index += pow(16, power) * (execute[i] - '0');
        }
        power++;
    }
    ostringstream os;
    os << hex << memory_index; //converting from decimal to hexadecimal again
    string tmp = os.str();

    if (tmp.size() == 1)
        tmp = "0" + tmp; //"a" -> "0a"
    for (auto &c: tmp)c = toupper(c); //"ab" -> "AB"
    machineMemory.memoryData[tmp] = R[reg_index].data;
}

void machine::instruction4( std::string execute) {
    int reg_index = 0;
    //Get register1 index
    if (isalpha(execute[2])) {
        reg_index = (execute[2] - 'A') + 10;
    } else {
        reg_index = execute[2] - '0';
    }
    int reg2_index=0;
    //Get register2 index
    if(isalpha(execute[3]))
        reg2_index = (execute[3] - 'A') + 10;
    else
        reg2_index = execute[3] - '0';

    int memory_index = 0;
    int power = 0;
    for (int i = 3; i >= 2; i--) {
        if (isalpha(execute[i])) {
            memory_index += pow(16, power) * ((execute[i] - 'A') + 10);
        } else {
            memory_index += pow(16, power) * (execute[i] - '0');
        }
        power++;
    }


    if (R[reg_index].data.empty()) {
        cout << "content of register " << execute[1] << " = garbage value" << endl;
    }
    else
        R[reg2_index]=R[reg_index];
}

void machine::instruction5( std::string execute) {
    int regS,regT,regR;
    regS= stoul(execute.substr(2,1));
    regT= stoul(execute.substr(3));
    regR= stoul(execute.substr(1,1));
    string s=R[regS].data, t=R[regT].data;
    int n1,n2;
    n1= stoul(s,0,16);
    n2= stoul(t,0,16);
    int sum= n1+n2;
    ostringstream os;
    os<<hex<<uppercase<<sum;
    R[regR].data=os.str();
    if (R[regR].data.size()==1)
        R[regR].data="0"+R[regR].data;
}
void machine::instructionB(string execute) {
    //Get register index
    int reg_index=0;
    if (isalpha(execute[1])) {
        reg_index = (execute[1] - 'A') + 10;
    } else {
        reg_index = execute[1] - '0';
    }

    string s=execute.substr(2,2);
    //if R0 equals R we got Jump to adress XY ,else do nothing
    if(R[0].data==R[reg_index].data){
        pCounter= s;
        int temp = stoul(pCounter, 0, 16); //converting from Hexadecimal to decimal
        --temp;
        ostringstream os;
        os << hex << temp; //converting from decimal to hexadecimal again
        pCounter = os.str();
        if (pCounter.size() == 1)
            pCounter = "0" + pCounter; //"a" -> "0a"
        for (auto &c: pCounter)c = toupper(c); //"ab" -> "AB"
    }

}




void machine::execute() {
    pCounter=tempCounter;
    bool even= true;
    int x= stoul(pCounter,0,16);
    if (x%2){
        even= false;
    }
    string tmp;
    while (true) {
        string first,second;
        int check;
        istringstream is(pCounter);
        is>>hex>>check;
        if (check % 2==(!even)) {
            tmp = machineMemory.memoryData[pCounter];
        } else {
            first=tmp;
            second= machineMemory.memoryData[pCounter];
            if (isValidCode(first,second)){

                if (first[0]=='1')
                    instruction1(first+second),inst.push_back("instruction 1 ("+first+second+") ");
                else if (first[0]=='2')
                    instruction2(first+second),inst.push_back("instruction 2 ("+first+second+") ");
                else if (first[0]=='3')
                    instruction3(first+second),inst.push_back("instruction 3 ("+first+second+") ");
                else if (first[0]=='4')
                    instruction4(first+second),inst.push_back("instruction 4 ("+first+second+") ");
                else if (first[0]=='5')
                    instruction5(first+second),inst.push_back("instruction 5 ("+first+second+") ");
                else if(first[0]=='B')
                    instructionB(first+second),inst.push_back("instruction B ("+first+second+") ");
                else if (first[0]=='C'){
                    cout<<"Program finished\n",inst.push_back("instruction C ("+first+second+") ");
                    break;}

            }else
                inst.push_back("Error: InValid Instruction!");
            tmp="";
        }
        check= stoul(pCounter,0,16);
        ++check;
        ostringstream os;
        os << hex << check;
        pCounter = os.str();
        if (pCounter.size() == 1)
            pCounter = "0" + pCounter; //"a" -> "0a"
        for (auto &c: pCounter)c = toupper(c); //"ab" -> "AB"
    }
}

bool machine::isValidCode(const string& first, const string& second) {
    //map<string, string> instructions = machineMemory.memoryData;
    string code = first + second;
    int index = 0;

    //if not valid return empty vector
    if (code.size() != 4) {
        return false;
    }
    if (code[0] == '1') {
        int memory_index = 0;
        int power = 0;
        for (int i = 3; i >= 2; i--) {
            if (isalpha(code[i])) {
                memory_index += pow(16, power) * ((code[i] - 'A') + 10);
            } else {
                memory_index += pow(16, power) * (code[i] - '0');
            }
            power++;
        }

        //if given memory address is wrong return empty vector
        if (memory_index >= 256) {
            return false;
        } else {
            int reg_index = 0;
            if (isalpha(code[1])) {
                reg_index = (code[1] - 'A') + 10;
            } else {
                reg_index = code[1] - '0';
            }
            //if regester index is more than 16 return empty vector
            if (reg_index >= 16) {
                return false;
            }



        }
    } else if (code[0] == '2') {
        int reg_index = 0;
        if (isalpha(code[1])) {
            reg_index = (code[1] - 'A') + 10;
        } else {
            reg_index = code[1] - '0';
        }
        if (reg_index >= 16) {
            return false;
        }

    } else if (code[0] == '3') {
        int reg_index = 0;
        if (isalpha(code[1])) {
            reg_index = (code[1] - 'A') + 10;
        } else {
            reg_index = code[1] - '0';
        }
        if (reg_index >= 16) {
            return false;
        }
        int memory_index = 0;
        int power = 0;
        for (int i = 3; i >= 2; --i) {
            if (isalpha(code[i])) {
                memory_index += pow(16, power) * ((code[i] - 'A') + 10);
            } else {
                memory_index += pow(16, power) * (code[i] - '0');
            }
            power++;
        }
        if (memory_index >= 256) {
            return false;
        }

    } else if (code[0] == '4') {
        int reg_index1 = 0;
        if (isalpha(code[2])) {
            reg_index1 = (code[2] - 'A') + 10;
        } else {
            reg_index1 = code[2] - '0';
        }
        if (reg_index1 >= 16) {
            return false;
        }
        int reg_index2 = 0;
        if (isalpha(code[3])) {
            reg_index2 = (code[3] - 'A') + 10;
        } else {
            reg_index2 = code[3] - '0';
        }
        if (reg_index2 >= 16) {
            return false;
        }

    } else if (code[0] == '5' || code[0] == '6') {
        int reg_index1 = 0;
        if (isalpha(code[2])) {
            reg_index1 = (code[2] - 'A') + 10;
        } else {
            reg_index1 = code[2] - '0';
        }
        if (reg_index1 >= 16 || reg_index1 < 0) {
            return false;
        }
        int reg_index2 = 0;
        if (isalpha(code[3])) {
            reg_index2 = (code[3] - 'A') + 10;
        } else {
            reg_index2 = code[3] - '0';
        }
        if (reg_index2 >= 16 || reg_index2 < 0) {
            return false;
        }
        int reg_index3 = 0;
        if (isalpha(code[1])) {
            reg_index3 = (code[1] - 'A') + 10;
        } else {
            reg_index3 = code[1] - '0';
        }
        if (reg_index3 >= 16 || reg_index3 < 0) {
            return false;
        }

    } else if (code[0] == 'B') {
        int memory_index = 0;
        int power = 0;
        for (int i = 3; i >= 2; --i) {
            if (isalpha(code[i])) {
                memory_index += pow(16, power) * ((code[i] - 'A') + 10);
            } else {
                memory_index += pow(16, power) * (code[i] - '0');
            }
            power++;
        }
        if (memory_index >= 256) {
            return false;
        } else {
            int reg_index = 0;
            if (isalpha(code[1])) {
                reg_index = (code[1] - 'A') + 10;
            } else {
                reg_index = code[1] - '0';
            }
            if (reg_index >= 16) {
                return false;
            }

        }

    } else if (code[0] == 'C') {
        bool ck = false;
        for (int i = 1; i < 4; i++) {
            if (code[i] != '0') {
                ck = true;
                break;
            }
        }
        if (ck) {
            return false;
        }
    } else {
        return false;
    }

    return true;
}

void machine::reset() {
    machineMemory.reset();
    for (auto &i :R) {
        i.data="00";
    }
}

void machine::displayMemory() {
    cout<<"Memory: \n";
    cout<<"| Address | Content |\n";
    for (auto i:machineMemory.memoryData) {
        cout<<"|   "<<i.first<<"    |    "<<i.second<<"   |"<<'\n';
    }
}

void machine::displayRegisters() {
    cout<<"Registers: \n";
    for (int i = 0; i < 16; ++i) {
        cout<<"R#"<<hex<<i<<"= "<<R[i].data<<'\n';
    }
}

void machine::setProgramCounter(string counter){
    pCounter=counter;
    tempCounter=counter;
}
