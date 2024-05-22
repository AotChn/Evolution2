#include "gtest/gtest.h"
#include <set>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include "../../file.h"


//------------------------------------------------------------------------------------------
//Files we are testing:

//------------------------------------------------------------------------------------------



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running basic_test.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}
