#pragma once
#include <string>
#include <vector>
#define ER_REFLECT()
using std::string;
class SecondClass;

ER_REFLECT()
class BottomClass {
public:
  string name = "Buttom";
  // SecondClass* second;
};

ER_REFLECT()
class SecondClass {
public:
  BottomClass *bottom;
  string name = "Second";
  int32_t y = 88;
  // RTTR_ENABLE()
};

ER_REFLECT()
class TopClass {
public:
  void set_second(SecondClass *_second) { second = _second; }
  std::vector<SecondClass *> secplist;
  SecondClass *second;

private:
  string name = "top";
  int32_t x = 99;
};