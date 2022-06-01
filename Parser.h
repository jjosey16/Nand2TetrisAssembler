#include <string>
#include <fstream> 
#include <iostream>
#include <algorithm>
#include "Command.h"

class Parser{    
    // input stream
    ifstream& input;
    public:
    Parser(ifstream& in): input(in){} //constructor

    Command get_next_command(){
        string line;
        while(getline(input, line)){
            if(line[0]=='/'&&line[1]=='/' || line.empty()){ // check for comment or empty line
                continue;
            } 
            if(line.find("//") != -1){ // if comment after code, retude line to just code
                int pos = line.find("//");
                line = line.substr(0, pos);
            }
            // remove all spaces in line
            std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
            line.erase(end_pos, line.end());
            // remove any carriage return characters
            end_pos = std::remove(line.begin(), line.end(), '\r');
            line.erase(end_pos, line.end());

            if(line.find("@")!=-1){ // type a
                Command c(2, line);
                return c;
            } else if (line.find("=")!=-1||line.find(";")!=-1){ // type c
                Command c(1, line);
                return c;
            } else {
                Command c(0, line); // type L
                return c;
            }
        } 
        Command c(3, ""); // type eof
        return c;
    }
    

    void reset_stream(){
        input.clear();
        input.seekg(0, ios::beg);
    }
};