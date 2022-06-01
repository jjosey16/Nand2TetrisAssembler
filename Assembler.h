#include <iostream>
#include <fstream>
# include <string>
#include "parser.h"
class Assembler {
    int PC; // program counter

    public:
    void assemble(string in, string out){
        ifstream infile;
        ofstream outfile;
        infile.open(in);
        outfile.open(out);
        Parser p(infile);
        first_pass(p);
        second_pass(p, outfile);

        infile.close();
        outfile.close();
        


    }

    void first_pass(Parser& p){ // need access to symbol table
        PC = 0;
        sTable *s = s->getInstance(); // instance of symbol table
        Command com = p.get_next_command();
        while(!(com.isEOF())){
            if(com.isLabel()){
                // add to table if label
                string str = com.get_symbol();
                int i = str.find('(');
                int j = str.find(')');
                str = str.substr(i+1, j-1);
                s->setAddress(PC);
                s->addEntry(str);
            } else {
                PC ++;
            }
            com = p.get_next_command();
        }
   }

    void second_pass(Parser& p, ofstream& outfile){
        sTable *s = s->getInstance(); // instance of symbol table
        s->setAddress(16); 
        p.reset_stream();
        Command com = p.get_next_command();
        while(!(com.isEOF())){
            if(!(com.isLabel())){
                // translate command if not eof or L type
                string bin_string = com.translate();
                outfile << bin_string<<endl;
            }
            com = p.get_next_command();
        }
   }
};