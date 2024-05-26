#include <iostream>
#include "file.h"

//++++++++++
void run_visual();
void run_sim();


int main() {

   run_visual();
   
   std::cout<<"working"<<std::endl;
   return 0;
}




void run_visual() {
   int input = 15,
      hidden = 3,
      hiddentwo = 4,
      output = 5;
   std::vector<tempNode::Node> inputs;
   std::vector<tempNode::Node> hidden1;
   std::vector<tempNode::Node> hidden2;
   std::vector<tempNode::Node> outputs;
   for (int i=0; i<input; i++) {
      tempNode::Node n;
      n.c = 'I';
      n.layer = 1;
      n.id = 0;
      inputs.push_back(n);
   }
   inputs[0].Links = {0,1};
   inputs[1].Links = {1};
   inputs[2].Links = {0};
   inputs[3].Links = {1};
   inputs[4].Links = {0,1};
   inputs[5].Links = {1};
   inputs[6].Links = {2};
   inputs[7].Links = {1};
   inputs[8].Links = {0,2};
   inputs[9].Links = {1};
   
   for (int i=0; i<hidden; i++) {
      tempNode::Node n;
      n.c = 'H';
      n.layer = 1;
      n.id = 0;
      hidden1.push_back(n);
   }

   hidden1[0].Links = {0,1};
   hidden1[1].Links = {0,2};
   hidden1[2].Links = {3};
   for (int i=0; i<hiddentwo; i++) {
      tempNode::Node n;
      n.c = 'H';
      n.layer = 1;
      n.id = 0;
      hidden2.push_back(n);
   }

   hidden2[0].Links = {0,1};
   hidden2[1].Links = {0,2};
   hidden2[2].Links = {3,4};

   for (int i=0; i<output; i++) {
      tempNode::Node n;
      n.c = 'O';
      n.layer = 1;
      n.id = 0;
      outputs.push_back(n);
   }

   std::vector<std::vector<tempNode::Node>> info;
   info.push_back(inputs);
   info.push_back(hidden1);
   info.push_back(hidden2);
   info.push_back(outputs);
   for (int i=0; i<info.size(); i++){
      std::cout<<"size :" << info[i].size() << "\n";
   }

   NodeVisual<std::vector<tempNode::Node>> N(3);
   N.setNodeList(info);
   Window w;
   w.Attach(&N);
   w.run();
}

void run_sim() {
   Window w;
   simulation sim;
   w.Attach(&sim);
   w.run();
}

   //sim.remove_pub(w.get_id()); //does not display sim