#pragma once
#include <rttr/registration_friend.h>
#include <string>
#include <vector>
#define RTTR_REFLECT(...)
using std::string;
class SecondClass;

RTTR_REFLECT(WithNonPublic)
class BottomClass
{
 public:
  string name = "Buttom";
  // SecondClass* second;
};

RTTR_REFLECT(WithNonPublic)
class SecondClass
{
 public:
  BottomClass* bottom;
  string name = "Second";
  int32_t y = 88;
  // RTTR_ENABLE()
};

RTTR_REFLECT(WithNonPublic)
class TopClass
{
 public:
  class Top
  {
    int _x = 123;
  };
  void set_second(SecondClass* _second) { second = _second; }
  std::vector<SecondClass*> secplist;
  SecondClass* second;
  RTTR_REGISTRATION_FRIEND
 private:
  string name = "top";
  int32_t x = 99;
  Top top;
};