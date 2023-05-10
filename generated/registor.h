#pragma once
#include <rttr/type>
#include <rttr/registration>

#include "/home/sxx/workSpace/cpp_generator/output/../data/exampleClass.h" 


RTTR_REGISTRATION{
  rttr::registration::class_<TopClass>("TopClass")
      .constructor<>()
      
      .property("secplist", &TopClass::secplist)
      .property("second", &TopClass::second)
      .property("name", &TopClass::name)
      .property("x", &TopClass::x)
      
      ;
        rttr::registration::class_<SecondClass>("SecondClass")
      .constructor<>()
      
      .property("bottom", &SecondClass::bottom)
      .property("name", &SecondClass::name)
      .property("y", &SecondClass::y)
      
      ;
        rttr::registration::class_<BottomClass>("BottomClass")
      .constructor<>()
      
      .property("name", &BottomClass::name)
      
      ;
      
}