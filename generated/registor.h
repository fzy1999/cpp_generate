#pragma once
#include <rttr/registration>
#include <rttr/type>

#include "/home/sxx/workSpace/cpp_generator/output/../data/exampleClass.h"

RTTR_REGISTRATION {
  struct TopClass {
    std::vector<SecondClass *> secplist;
    SecondClass *second;
    string name;
    int32_t x;
  };
  struct SecondClass {
    BottomClass *bottom;
    string name;
    int32_t y;
  };
  struct BottomClass {
    string name;
  }
}