// Copyright 2020 ak-kuznetsov <a.kuznetsov2701@mail.ru>

#include <gtest/gtest.h>
#include <Student.hpp>

TEST(Student_Test, Empty_Index){
  const char j_string[] =\
      R"({"name": "Ivan Ivanov", "group": 9, "avg": 4, "debt": null})";
  Student emptyStudent((nlohmann::json::parse(j_string)));

  EXPECT_EQ(emptyStudent.Get_Type(""), Student::Null);
  EXPECT_EQ(std::any_cast<std::nullptr_t>(emptyStudent.Get_Field("")), \
      nullptr);
}
