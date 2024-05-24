/* ************************************************************************* *
 * AUTHOR:      Aot Chanthorn
 * PROJECT: 
 * ------------------------------------------------------------------------- *
 * File: testB.cpp
 *  simulate program as if application 
 *  ensure all functions work as intended 
 * ************************************************************************* */

#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>
#include "../../file.h"

//TEST FILES -----------------------------------------------------------------|

//----------------------------------------------------------------------------|
const bool debug = true;

/* ========================================================================= *
 * OBSERVER 
 * ========================================================================= */
class OBSERVER : public testing::Test{
  protected:
  Publisher pub;
  Subscriber s1, s2, s3, s4 ,s5;
};

TEST_F(OBSERVER, simple){ 
  pub.Attach(&s1); //1
  pub.Attach(&s2); //1 2
  pub.Attach(&s3); // 1 2 3

  pub.Detach(&s2); // 1 3
  pub.Attach(&s4); // 1 3 4
  pub.Attach(&s5); // 1 3 4 5

  EXPECT_EQ(pub.count_sub(), 4);
}

TEST_F(OBSERVER, remove_all){ 
  pub.Attach(&s1); //1
  pub.Attach(&s2); //1 2
  pub.Attach(&s3); // 1 2 3
  pub.Attach(&s4); // 1 2 3 4
  pub.Attach(&s5); // 1 2 3 4 5
  pub.Detach(&s1); // 2 3 4 5
  pub.Detach(&s2); // 3 4 5
  pub.Detach(&s3); //4 5
  pub.Detach(&s4); //5
  pub.Detach(&s5); //

  EXPECT_EQ(pub.count_sub(), 0);
}

TEST_F(OBSERVER, remove_DNE){ 
  pub.Attach(&s1); //1
  pub.Attach(&s2); //1 2
  pub.Detach(&s2); // 1 
  pub.Detach(&s2); // 1

  EXPECT_EQ(pub.count_sub(), 1);
}

TEST_F(OBSERVER, remove_when_0){ 
  pub.Attach(&s1); //1
  pub.Attach(&s2); //1 2
  pub.Detach(&s1); // 2
  pub.Detach(&s2); // 
  pub.Detach(&s2); // 

  EXPECT_EQ(pub.count_sub(), 0);
}

TEST_F(OBSERVER, remove_way_past_0){ 
  pub.Attach(&s1); //1
  pub.Attach(&s2); //1 2
  pub.Detach(&s1); // 2
  pub.Detach(&s2); // 
  for (int i=0; i<100; i++) {
    pub.Detach(&s2); // 
  }

  EXPECT_EQ(pub.count_sub(), 0);
}

TEST_F(OBSERVER, add_dup){ 
  pub.Attach(&s1); //1
  pub.Attach(&s1); //1 1

  EXPECT_EQ(pub.count_sub(), 2);
}

TEST_F(OBSERVER, add_mil_sub_mil){ 
  for (int i=0; i<1000000; i++){
    pub.Attach(&s1);
  }
  for (int i=0; i<1000000; i++){
    pub.Detach(&s1);
  }
  
  EXPECT_EQ(pub.count_sub(), 0);
}

TEST_F(OBSERVER, sub_mil_add_mil){ 
  for (int i=0; i<1000000; i++){
    pub.Detach(&s1);
  }
  for (int i=0; i<1000000; i++){
    pub.Attach(&s1);
  }
  
  EXPECT_EQ(pub.count_sub(), 1000000);
}
/* ========================================================================= *
 * WINDOW
 * ========================================================================= */

TEST(WINDOW, simple){
  sf::RenderWindow w;
  Window_Publisher pub;
  Window_Subscriber o1, o2, o3, o4 ,o5;
  pub.Attach(&o1);
  pub.Attach(&o2);
  pub.Attach(&o3);
  pub.Detach(&o2);
  pub.Attach(&o4);
  pub.Attach(&o5);
  pub.Notify(w,0);
}

/* ========================================================================= *
 * SIMULATION
 * ========================================================================= */
class SIMULATION : public testing::Test{
  protected:
   Window w;
   simulation sim;
};

TEST_F(SIMULATION, simple) {
  w.Attach(&sim);
  w.run();
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

