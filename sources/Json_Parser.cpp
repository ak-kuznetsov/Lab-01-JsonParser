// Copyright 2020 ak-kuznetsov <a.kuznetsov2701@mail.ru>

#include <Json_Parser.hpp>

Json_Parser Json_Parser::From_File(const std::string& json_Path) {
  std::ifstream file(json_Path);
  if (!file) {
    throw std::runtime_error{"unable to open file"};
  }
  nlohmann::json data;
  file >> data;
  if (data.empty()) {
    throw std::runtime_error{"file is empty"};
  }
  if (!data.at("items").is_array()) {
    throw std::runtime_error{"incorrect items field,"
                             " items should be an array"};
  }
  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>()) {
    throw std::runtime_error{
        R"(incorrect count field, count at meta
     should be equal items field size)"};
  }
  std::vector<Student> newStudents;
  for (const auto& item : data.at("items")) {
    Student newStudent(item);
    newStudents.push_back(newStudent);
  }
  return Json_Parser(newStudents);
}

Json_Parser::Json_Parser(std::vector<Student> new_student) {
  students = std::move(new_student);
  for (const auto& student : students) {
    if (student.To_String(Field_Name[0]).length() >
        Get_Width(Field_Name[0]))
      Set_Width(Field_Name[0], student.To_String(Field_Name[0]).length());
    if (student.To_String(Field_Name[1]).length() >
        Get_Width(Field_Name[1]))
      Set_Width(Field_Name[1], student.To_String(Field_Name[1]).length());
    if (student.To_String(Field_Name[2]).length() >
        Get_Width(Field_Name[2]))
      Set_Width(Field_Name[2], student.To_String(Field_Name[2]).length());
    if (student.To_String(Field_Name[3]).length() >
        Get_Width(Field_Name[3]))
      Set_Width(Field_Name[3], student.To_String(Field_Name[3]).length());
  }
}

auto Json_Parser::Get_Width(const std::string& index) const -> size_t {
  if (index == Field_Name[0]) {
    return name_w;
  } else if (index == Field_Name[1]) {
    return group_w;
  } else if (index == Field_Name[2]) {
    return avg_w;
  } else if (index == Field_Name[3]) {
    return debt_w;
  }
  return 0;
}

void Json_Parser::Set_Width(const std::string& index, size_t new_Value) {
  if (index == Field_Name[0]) {
    name_w = new_Value;
  } else if (index == Field_Name[1]) {
    group_w = new_Value;
  } else if (index == Field_Name[2]) {
    avg_w = new_Value;
  } else if (index == Field_Name[3]) {
    debt_w = new_Value;
  }
}

std::ostream& operator<<(std::ostream& os, const Json_Parser& parser) {
  parser.Filler_sep(os);
  parser.Filler_top(os, parser);
  for (const auto& student : parser.Get_Vector()) {
    parser.Print_students(student, os);
  }
  parser.Filler_sep(os);
  return os;
}

auto Json_Parser::Get_Vector() const -> std::vector<Student> { return students; }

void Json_Parser::Print_students(const Student& student, std::ostream& os) const {
  Filler_sep(os);
  os << "|" << student.To_String(Field_Name[0]);
  Filler(Get_Width(Field_Name[0]) -
         student.To_String(Field_Name[0]).length(), os);
  os << "|" << student.To_String(Field_Name[1]);
  Filler(Get_Width(Field_Name[1]) -
         student.To_String(Field_Name[1]).length(), os);
  os << "|" << student.To_String(Field_Name[2]);
  Filler(Get_Width(Field_Name[2]) -
         student.To_String(Field_Name[2]).length(), os);
  os << "|" << student.To_String(Field_Name[3]);
  Filler(Get_Width(Field_Name[3]) -
         student.To_String(Field_Name[3]).length(), os);
  os << "|" << std::endl;
}

void Json_Parser::Filler_sep(std::ostream& os) const {
  os << "|";
  for (size_t i = 0; i < Get_Width(Field_Name[0]); ++i) {
    os << "-";
  }
  os << "|";
  for (size_t i = 0; i < Get_Width(Field_Name[1]); ++i) {
    os << "-";
  }
  os << "|";
  for (size_t i = 0; i < Get_Width(Field_Name[2]); ++i) {
    os << "-";
  }
  os << "|";
  for (size_t i = 0; i < Get_Width(Field_Name[3]); ++i) {
    os << "-";
  }
  os << "|" << std::endl;
}

void Json_Parser::Filler_top(std::ostream& os, const Json_Parser& parser) const {
  os << "|" << Field_Name[0];
  Filler(parser.Get_Width(Field_Name[0]) - Field_Name[0].length(), os);
  os << "|" << Field_Name[1];
  Filler(parser.Get_Width(Field_Name[1]) - Field_Name[1].length(), os);
  os << "|" << Field_Name[2];
  Filler(parser.Get_Width(Field_Name[2]) - Field_Name[2].length(), os);
  os << "|" << Field_Name[3];
  Filler(parser.Get_Width(Field_Name[3]) - Field_Name[3].length(), os);
  os << "|\n";
}

void Json_Parser::Filler(size_t difference, std::ostream& os) {
  for (size_t i = 0; i < difference; ++i) {
    os << " ";
  }
}
