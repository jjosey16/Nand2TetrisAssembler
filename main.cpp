#include <fstream>
# include <iostream>
# include <map>
# include <string>
#include "Assembler.h"



int main(int argc, char* argv[]){

   string in = argv[1];
   string out = in.substr(0, in.find('.'));
   out += ".hack";
   Assembler a;
   a.assemble(in, out);
 
   return 0;
}
