// Copyright 2020 ak-kuznetsov <a.kuznetsov2701@mail.ru>

#include <Json_Parser.hpp>

std::string Get_Name(const nlohmann::json& j) { return j.get<std::string>(); }

std::any Get_Group(const nlohmann::json& j) {
  if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<int>();
}

std::any Get_Avg(const nlohmann::json& j) {
  if (j.is_null()) {
    return nullptr;
  } else if (j.is_string()) {
    return j.get<std::string>();
  } else if (j.is_number_float()) {
    return j.get<float>();
  } else {
    return j.get<int>();
  }
}

std::any Get_Debt(const nlohmann::json& j) {
  if (j.is_null()) {
    return nullptr;
  } else if (j.is_string()) {
    return j.get<std::string>();
  } else {
    return j.get<std::vector<std::string>>();
  }
}

std::vector<Student> From_File(const std::string& json_path) {
  std::fstream file;
  file.open(json_path, std::ios::in);
  if (!file.is_open()) {
    throw std::runtime_error(json_path + " not open");
  }
  nlohmann::json j;
  file >> j;
  file.close();
  std::vector<Student> result;
  if (!j.at("items").is_array()) {
    throw std::runtime_error("Items most be array type");
  }
  if (j.at("items").size() != j.at("_meta").at("count")) {
    throw std::runtime_error("meta_: count and items size mismatch");
  }
  for (std::size_t i = 0; i < j.at("items").size(); i++) {
    Student student;
    student.name = Get_Name(j.at("items")[i].at("name"));
    student.group = Get_Group(j.at("items")[i].at("group"));
    student.avg = Get_Avg(j.at("items")[i].at("avg"));
    student.debt = Get_Debt(j.at("items")[i].at("debt"));
    result.push_back(student);
  }
  return result;
}

void Print(const Student& student, std::ostream& os) {
  os << "|" << std::left << std::setw(Width[0] +1) << student.name;
  if (student.group.type() == typeid(int)) {
    os << "| " << std::setw(Width[1]) << std::left
           << std::any_cast<int>(student.group);
  } else {
    os << "| " << std::setw(Width[1]) << std::left
           << std::any_cast<std::string>(student.group);
  }
  if (student.avg.type() == typeid(float)) {
    os << "| " << std::setw(Width[2]) << std::left
           << std::any_cast<float>(student.avg);
  } else if (student.avg.type() == typeid(int)) {
    os << "| " << std::setw(Width[2]) << std::left
           << std::any_cast<int>(student.avg);
  } else {
    os << "| " << std::setw(Width[2]) << std::left
           << std::any_cast<std::string>(student.avg);
  }
  if (student.debt.type() == typeid(std::nullptr_t)) {
    os << "| " << std::setw(Width[3]) << std::left << "none" << std::right
           << "|";
  } else if (student.debt.type() == typeid(std::string)) {
    os << "| " << std::setw(Width[3]) << std::left
           << std::any_cast<std::string>(student.debt) << std::right << "|";
  } else {
    os
        << "| " << std::setw(Width[3]) << std::left
        << (std::to_string(
                std::any_cast<std::vector<std::string>>(student.debt).size()) +
            " items")
        << "|";
  }
}

void Print(const std::vector<Student>& students, std::ostream& os) {
  std::string table;
  for (int j : Width) {
    table += "|-";
    for (int i = 0; i < j; ++i) {
      table += "-";
    }
  }
  table += "|";
  os << "| " << std::left << std::setw(Width[0]) << "name";
  os << "| " << std::left << std::setw(Width[1]) << "group";
  os << "| " << std::left << std::setw(Width[2]) << "avg";
  os << "| " << std::left << std::setw(Width[3]) << "debt";
  os << std::right << "|";
  os << std::endl << table << std::endl;
  for (auto& student : students) {
    Print(student, os);
    os << std::endl << table << std::endl;
  }
}
