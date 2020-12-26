// Copyright 2020 ak-kuznetsov <a.kuznetsov2701@mail.ru>

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <any>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

const std::string Field_Name[4] = {"name", "group", "avg", "debt"};

struct Student {
 public:
  enum Type {
    Null,
    String,
    Integer,
    Array,
    Double};

  explicit Student(nlohmann::json);

  explicit Student(std::string, std::any, std::any, std::any);

  bool operator==(const Student&) const;

  std::string To_String(const std::string&) const;

  auto Get_Type(const std::string&) const -> Type;

  auto Get_Field(const std::string&) const -> std::any;

 private:
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;

  Type name_type = String;
  Type group_type;
  Type avg_type;
  Type debt_type;
};
#endif  // INCLUDE_STUDENT_HPP_
