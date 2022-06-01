#include <string>
#include <iostream>
#include <map>
#include "table.h"

class Command {
    enum types {L, C, A, eof};
    std::string Com_symbol;
    types type;
    static map<std::string, std::string> comp_lookup;
    static map<std::string, std::string> dest_lookup;
    static map<std::string, std::string> jump_lookup;

    public:
    std::string get_symbol(){
        return Com_symbol;
    }

    Command(int id, std::string sy){ // constructor
        Com_symbol = sy;

        switch (id){
            case 1:
            type = C;
            break;
            case 2:
            type = A;
            break;
            case 3:
            type = eof;
            break;
            default:
            type = L;
        }
    }

    std::string translate(){
        // L types should already be skipped
        if(type == A){
            return translate_A();
        } else {
            return translate_C();
        }
    }

    bool isLabel(){
        return (type == 0);
    }

    bool isEOF(){
        return (type == 3);
    }

    private:
    std::string translate_A(){
        sTable *s = s->getInstance();
        string str = Com_symbol.substr(1); // get part after @
        int val;
        if(isNum(str)){
            // convert to int
            val = std::stoi(str);

        } else {
            if(s->contains(str)){
                val = s->getAddress(str);
            } else {
                val = s->getAddress();
                s->addEntry(str);
            }
        }
        return to_bin(val);
    }

    bool isNum(const string& s){
        for(char const &c : s){
            if(std::isdigit(c)==0) return false;
        }
        return true;
    }

    std::string translate_C(){
        bool hasEquals = false;
        bool hasSemi = false; 
        if(Com_symbol.find('=')!=-1) hasEquals = true;
        if(Com_symbol.find(';')!=-1) hasSemi = true;
        int i;
        // dest
        string dest;
        if (hasEquals){
            i = Com_symbol.find('=');
            dest = Com_symbol.substr(0, i);

        } else {
            dest = "000";
        }

        //comp
        string comp;
        if(hasEquals && hasSemi){
            i = Com_symbol.find('=');
            int j = Com_symbol.find(';');
            comp = Com_symbol.substr(i+1, j-1); // may have to change later??

        } else if(hasEquals){
            i = Com_symbol.find('=');
            comp  = Com_symbol.substr(i+1);
        } else if(hasSemi){
            i = Com_symbol.find(';');
            comp = Com_symbol.substr(0, i);
        } else {
            comp = Com_symbol;
        }
         
        // jump
        string jump;
        if(hasSemi){
           i = Com_symbol.find(';');
           jump = Com_symbol.substr(i+1); 
        } else {
            jump = "000";
        }

        //make binary instruction
        string bin = "111";
        bin += comp_lookup[comp];
        bin += dest_lookup[dest];
        bin += jump_lookup[jump];

        return bin;
    }

    std::string to_bin(int n){
        int a[16] = {0};
        int i;
        for(i=0;n>0;i++){
            a[i] = n%2;
            n = n/2;
        }

        std::string bin = "";
        for(int j=15; j>=0; j--){
            std::string s = to_string(a[j]);
            bin = bin + s;
        }
        return bin;
    }

};

map<std::string, std::string> Command::comp_lookup = {
    {"0", "0101010"},
    {"1", "0111111"},
    {"-1", "0111010"},
    {"D", "0001100"},
    {"A", "0110000"},
    {"!D", "0001101"},
    {"!A", "0110001"},
    {"D+1", "0011111"},
    {"A+1", "0110111"},
    {"D-1", "0001110"},
    {"A-1", "0110010"},
    {"D+A", "0000010"},
    {"D-A", "0010011"},
    {"A-D", "0000111"},
    {"D&A", "0000000"},
    {"D|A", "0010101"},
    {"M", "1110000"},
    {"!M", "1110001"},
    {"-M", "1110011"},
    {"M+1", "1110111"},
    {"M-1", "1110010"},
    {"D+M", "1000010"},
    {"D-M", "1010011"},
    {"M-D", "1000111"},
    {"D&M", "1000000"},
    {"D|M", "1010101"},
};

map<std::string, std::string> Command::dest_lookup = {
    {"000", "000"},
    {"M", "001"},
    {"D", "010"},
    {"DM", "011"},
    {"MD", "011"},
    {"A", "100"},
    {"AM", "101"},
    {"MA", "101"},
    {"AD", "110"},
    {"DA", "110"},
    {"ADM", "111"},
};

map<std::string, std::string> Command::jump_lookup = {
    {"000", "000"},
    {"JGT", "001"},
    {"JEQ", "010"},
    {"JGE", "011"},
    {"JLT", "100"},
    {"JNE", "101"},
    {"JLE", "110"},
    {"JMP", "111"},
};