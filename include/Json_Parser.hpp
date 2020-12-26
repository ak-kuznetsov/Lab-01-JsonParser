// Copyright 2020 ak-kuznetsov <a.kuznetsov2701@mail.ru>

#ifndef INCLUDE_JSON_PARSER_HPP_
#define INCLUDE_JSON_PARSER_HPP_

#include <Student.hpp>
#include <any>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

class Json_Parser {
 private:
  std::vector<Student> students;
  size_t name_w{4};
  size_t group_w{5};
  size_t avg_w{3};
  size_t debt_w{4};

 public:
  explicit Json_Parser(std::vector<Student>);

  auto Get_Width(const std::string&) const -> size_t;

  void Set_Width(const std::string&, size_t);

  auto Get_Vector() const -> std::vector<Student>;

  void Print_students(const Student& student, std::ostream& os) const;

  void Filler_sep(std::ostream& os) const;

  static void Filler(size_t difference, std::ostream& os);

  void Filler_top(std::ostream& os, const Json_Parser& parser) const;

  static Json_Parser From_File(const std::string&);

  friend std::ostream& operator<<(std::ostream&, const Json_Parser&);
};
#endif  // INCLUDE_JSON_PARSER_HPP_
