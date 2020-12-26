// Copyright 2020 ak-kuznetsov <a.kuznetsov2701@mail.ru>

#include <Student.hpp>

Student::Student(std::string new_name, std::any new_group, std::any new_avg, std::any new_debt) {
  name = std::move(new_name);
  group = std::move(new_group);
  avg = std::move(new_avg);
  debt = std::move(new_debt);

  if (group.type() == typeid(std::string)) {
    group_type = String;
  } else if (group.type() == typeid(int)) {
    group_type = Integer;
  } else if (group.type() == typeid(double)) {
    group_type = Double;
  } else if (group.type() == typeid(nullptr)) {
    group_type = Null;
  } else if (group.type() == typeid(std::vector<std::string>)) {
    group_type = Array;
  }

  if (avg.type() == typeid(std::string)) {
    avg_type = String;
  } else if (avg.type() == typeid(int)) {
    avg_type = Integer;
  } else if (avg.type() == typeid(double)) {
    avg_type = Double;
  } else if (avg.type() == typeid(nullptr)) {
    avg_type = Null;
  } else if (avg.type() == typeid(std::vector<std::string>)) {
    avg_type = Array;
  }
  if (debt.type() == typeid(std::string)) {
    debt_type = Student::String;
  } else if (debt.type() == typeid(nullptr)) {
    debt_type = Null;
  } else if (debt.type() == typeid(std::vector<std::string>)) {
    debt_type = Array;
  } else if (debt.type() == typeid(int)) {
    debt_type = Integer;
  } else if (debt.type() == typeid(double)) {
    debt_type = Double;
  }
}

Student::Student(nlohmann::json in) {
  name = in.at(Field_Name[0]).get<std::string>();

  if (in.at(Field_Name[1]).is_string()) {
    group_type = String;
    group = in[Field_Name[1]].get<std::string>();
  } else if (in.at(Field_Name[1]).is_number_integer()) {
    group_type = Integer;
    group = in[Field_Name[1]].get<int>();
  } else {
    throw std::runtime_error{"incorrect data in field GROUP"};
  }

  if (in.at(Field_Name[2]).is_string()) {
    avg_type = String;
    avg = in[Field_Name[2]].get<std::string>();
  } else if (in.at(Field_Name[2]).is_number_integer()) {
    avg_type = Integer;
    avg = in[Field_Name[2]].get<int>();
  } else if (in.at(Field_Name[2]).is_number_float()) {
    avg_type = Double;
    avg = in[Field_Name[2]].get<double>();
  } else {
    throw std::runtime_error{"incorrect data in field AVG"};
  }

  if (in.at(Field_Name[3]).is_string()) {
    debt_type = String;
    debt = in[Field_Name[3]].get<std::string>();
  } else if (in.at(Field_Name[3]).is_null()) {
    debt_type = Null;
    debt = nullptr;
  } else if (in.at(Field_Name[3]).is_array()) {
    debt_type = Array;
    debt = in[Field_Name[3]].get<std::vector<std::string>>();
  } else {
    throw std::runtime_error{"incorrect data in field DEBT"};
  }
}

bool Student::operator==(const Student& student) const {
  bool result = false;
  if (name != student.name) {
    result = false;
  }

  if (group_type != student.group_type) {
    result = false;
  } else {
    if (group_type == String) {
      result =
          std::any_cast<std::string>(group) ==
          std::any_cast<std::string>(student.group);
    } else if (group_type == Integer) {
      result = std::any_cast<int>(group) ==
               std::any_cast<int>(student.group);
    }
  }
  if (avg_type != student.avg_type) {
    result = false;
  } else {
    if (avg_type == String) {
      result = std::any_cast<std::string>(avg) ==
               std::any_cast<std::string>(student.avg);
    } else if (avg_type == Integer) {
      result = std::any_cast<int>(avg) ==
               std::any_cast<int>(student.avg);
    } else if (avg_type == Double) {
      result = std::any_cast<double>(avg) ==
               std::any_cast<double>(student.avg);
    }
  }
  if (debt_type != student.debt_type) {
    result = false;
  } else {
    if (debt_type == String) {
      result =
          std::any_cast<std::string>(debt) ==
          std::any_cast<std::string>(student.debt);
    } else if (debt_type == Null) {
      result = true;
    } else if (debt_type == Array) {
      result = std::any_cast<std::vector<std::string>>(debt) ==
               std::any_cast<std::vector<std::string>>(student.debt);
    }
  }
  return result;
}

std::string Student::To_String(const std::string& key) const {
  switch (Get_Type(key)) {
    default:
    case Null: {
      return "null";
    }
    case String: {
      return std::any_cast<std::string>(Get_Field(key));
    }
    case Double: {
      std::stringstream out;
      out << std::any_cast<double>(Get_Field(key));
      return out.str();
    }
    case Integer: {
      std::stringstream out;
      out << std::any_cast<int>(Get_Field(key));
      return out.str();
    }
    case Array: {
      std::stringstream out;
      out << std::any_cast<std::vector<std::string>>(Get_Field(key)).size();
      return out.str() + " items";
    }
  }
}

auto Student::Get_Type(const std::string& index) const -> Type {
  if (index == Field_Name[0]) {
    return name_type;
  } else if (index == Field_Name[1]) {
    return group_type;
  } else if (index == Field_Name[2]) {
    return avg_type;
  } else if (index == Field_Name[3]) {
    return debt_type;
  }
  return Null;
}

auto Student::Get_Field(const std::string& index) const -> std::any {
  if (index == Field_Name[0]) {
    return name;
  } else if (index == Field_Name[1]) {
    return group;
  } else if (index == Field_Name[2]) {
    return avg;
  } else if (index == Field_Name[3]) {
    return debt;
  }
  return nullptr;
}