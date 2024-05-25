#include <iostream>
#include "file.h"

//++++++++++

int main() {

   Window w;
   simulation sim;
   w.Attach(&sim);
   sim.remove_pub(w.get_id()); //does not display sim
   w.run();


   std::cout<<"working"<<std::endl;
   return 0;
}

