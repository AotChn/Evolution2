/* ************************************************************************* *
 * AUTHOR:      Aot Chanthorn
 * PROJECT: 
 * ------------------------------------------------------------------------- *
 * File: testC.cpp
 *  test unit functionality of functions
 *  ensure all functions work as intended 
 * ************************************************************************* */

#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>

//TEST FILES -----------------------------------------------------------------|

//----------------------------------------------------------------------------|
const bool debug = true;

/* ========================================================================= *
 * TEST CATEGORY
 * ========================================================================= */



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n|-* * * * * * * * running testC.cpp * * * * * * * *-|\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

