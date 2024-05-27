#include <iostream>
#include "file.h"

//++++++++++
void run_visual();
void run_sim();
void run_graph();


int main() {

   run_visual();
   //run_sim();
   //run_graph();
   
   std::cout<<"working"<<std::endl;
   return 0;
}




void run_visual() {
   // int input = 6,
   //    hidden = 3,
   //    hiddentwo = 4,
   //    output = 5;
   // std::vector<tempNode::Node> inputs;
   // std::vector<tempNode::Node> hidden1;
   // std::vector<tempNode::Node> hidden2;
   // std::vector<tempNode::Node> outputs;
   // for (int i=0; i<input; i++) {
   //    tempNode::Node n;
   //    n.c = 'I';
   //    n.id = 0;
   //    inputs.push_back(n);
   // }
   // inputs[0].Links = {0,1};
   // inputs[1].Links = {1};
   // inputs[2].Links = {0};
   // inputs[3].Links = {1};
   // inputs[4].Links = {0,1};
   // inputs[5].Links = {1};
   // // inputs[6].Links = {2};
   // // inputs[7].Links = {1};
   // // inputs[8].Links = {0,2};
   // // inputs[9].Links = {1};
   
   // for (int i=0; i<hidden; i++) {
   //    tempNode::Node n;
   //    n.c = 'H';
   //    n.id = 0;
   //    hidden1.push_back(n);
   // }

   // hidden1[0].Links = {0,1};
   // hidden1[1].Links = {0,2};
   // hidden1[2].Links = {3};
   // for (int i=0; i<hiddentwo; i++) {
   //    tempNode::Node n;
   //    n.c = 'H';
   //    n.id = 0;
   //    hidden2.push_back(n);
   // }

   // hidden2[0].Links = {0,1};
   // hidden2[1].Links = {0,2};
   // hidden2[2].Links = {3,4};

   // for (int i=0; i<output; i++) {
   //    tempNode::Node n;
   //    n.c = 'O';
   //    n.id = 0;
   //    outputs.push_back(n);
   // }

   // std::vector<std::vector<tempNode::Node>> info;
   // info.push_back(inputs);
   // info.push_back(hidden1);
   // info.push_back(hidden2);
   // info.push_back(outputs);
   // for (int i=0; i<info.size(); i++){
   //    std::cout<<"size :" << info[i].size() << "\n";
   // }

   // NodeVisual<std::vector<tempNode::Node>> N;
//   N.set_parameters(NNVisualTest::width, NNVisualTest::height, NNVisualTest::off_x, NNVisualTest::off_y);
//   N.setNodeList(info);
   Window w;
   Plot<dataframe<int>> p(1);
   std::cout<<"plot made\n";
  simulation sim(&p);
   std::cout<<"sim made\n";
   w.Attach(&sim);
   std::cout<<"sim attached\n";
 //  w.Attach(&N);
   w.Attach(&p);
   std::cout<<"plot attached\n";
   w.run();
}

void run_sim() {
   Window w;
   simulation sim;
   w.Attach(&sim);
   w.run();
}

void run_graph() {
   Window w;
   dataframe<int> df;
   df.add(1,10);
   df.add(2,20);
   df.add(3,30);
   df.add(4,40);
   df.add(5,50);
   df.add(6,60);

   df.add(8,10);
   df.add(9,20);
   df.add(10,30);
   df.add(11,40);
   df.add(12,50);
   df.add(13,60);

   df.add(14,10);
   df.add(15,20);
   df.add(16,30);
   df.add(17,40);
   df.add(18,50);
   df.add(19,60);
   df.add(20,60);

   Plot<dataframe<int>> p(1);
   //p.set_x_range(0,20);
   //p.set_y_range(0,60);
   p.set_x_increment(2);
   p.set_y_increment(10);
   p.add_data(df);
   w.Attach(&p);
   w.run();
}

   //sim.remove_pub(w.get_id()); //does not display sim