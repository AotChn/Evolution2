#include <iostream>
#include "file.h"

//++++++++++

int main() {

   Window w;
   simulation sim;
   w.Attach(&sim);
   w.run();


   std::cout<<"working"<<std::endl;
   return 0;
}

