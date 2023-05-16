#pragma once
#include "myrttr/type"
#include "myrttr/registration"
#include "../common.h"

#include "/home/sxx/workSpace/cpp_generator/output/../data/exampleClass.h"


RTTR_REGISTRATION{
    rttr::registration::class_<io::IdHolder>("IdHolder")
      .property("id", &io::IdHolder::id)
      .property("derive_type", &io::IdHolder::derive_type);
  rttr::registration::class_<TopClass>("TopClass")
      .constructor<>()
      
      .property("secplist", &TopClass::secplist)
      .property("second", &TopClass::second)
      .property("name", &TopClass::name)
      .property("x", &TopClass::x)
      .property("top", &TopClass::top)
      
      ;
        rttr::registration::class_<SecondClass>("SecondClass")
      .constructor<>()
      
      .property("bottom", &SecondClass::bottom)
      .property("name", &SecondClass::name)
      .property("y", &SecondClass::y)
      
      ;
        rttr::registration::class_<TopClass::Top>("TopClass::Top")
      .constructor<>()
      
      .property("_x", &TopClass::Top::_x)
      
      ;
        rttr::registration::class_<BottomClass>("BottomClass")
      .constructor<>()
      
      .property("name", &BottomClass::name)
      
      ;
      
}