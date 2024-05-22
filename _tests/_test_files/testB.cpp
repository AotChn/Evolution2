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

TEST(OBSERVER, simple){ 
  Publisher pub;
  Subscriber s1, s2, s3, s4 ,s5;

  pub.Attach(&s1); //1
  pub.Attach(&s2); //1 2
  pub.Attach(&s3); // 1 2 3

  pub.Detach(&s2); // 1 3
  pub.Attach(&s4); // 1 3 4
  pub.Attach(&s5); // 1 3 4 5

  EXPECT_EQ(pub.count_sub(), 4);
}

TEST(OBSERVER, remove_all){ 
  Publisher pub;
  Subscriber s1, s2, s3, s4 ,s5;

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

TEST(OBSERVER, remove_DNE){ 
  Publisher pub;
  Subscriber s1, s2, s3, s4 ,s5;

  pub.Attach(&s1); //1
  pub.Attach(&s2); //1 2

  pub.Detach(&s2); // 1 
  pub.Detach(&s2); // 1

  EXPECT_EQ(pub.count_sub(), 1);
}

TEST(OBSERVER, remove_when_0){ 
  Publisher pub;
  Subscriber s1, s2, s3, s4 ,s5;

  pub.Attach(&s1); //1
  pub.Attach(&s2); //1 2

  pub.Detach(&s1); // 2
  pub.Detach(&s2); // 
  pub.Detach(&s2); // 

  EXPECT_EQ(pub.count_sub(), 0);
}

TEST(OBSERVER, remove_way_past_0){ 
  Publisher pub;
  Subscriber s1, s2, s3, s4 ,s5;

  pub.Attach(&s1); //1
  pub.Attach(&s2); //1 2

  pub.Detach(&s1); // 2
  pub.Detach(&s2); // 
  for (int i=0; i<100; i++) {
    pub.Detach(&s2); // 
  }

  EXPECT_EQ(pub.count_sub(), 0);
}

TEST(OBSERVER, add_dup){ 
  Publisher pub;
  Subscriber s1, s2, s3, s4 ,s5;

  pub.Attach(&s1); //1
  pub.Attach(&s1); //1 1

  EXPECT_EQ(pub.count_sub(), 2);
}

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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

