// Copyright 2020 ak-kuznetsov <a.kuznetsov2701@mail.ru>

#include <gtest/gtest.h>

#include <Json_Parser.hpp>

TEST(Json_Parser_Test, File_Open_Bad) {
  std::vector<Student> students;
  EXPECT_THROW(students = From_File("path/to/bad_file.json"),
               std::runtime_error);
}

TEST(Json_Parser_Test, Meta_Test) {
  std::fstream file{"bad_file.json", std::ios::out};
  if (!file.is_open()) {
    FAIL() << "Unable to open \"bad_file.json\"" << std::endl;
  }
  std::string bad_file = R"(
{
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 1
  }
}
)";
  file << bad_file;
  file.close();
  EXPECT_THROW(auto students = From_File("bad_file.json"),
               std::runtime_error);
}

TEST(Json_Parser_Test, Table_Test) {
  std::fstream file{"table_test.json", std::ios::out};
  if (!file.is_open()) {
    FAIL() << "Unable to open \"table_test.json\"" << std::endl;
  }
  std::string json_string = R"(
{
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
}
)";
  file << json_string;
  file.close();
  std::string table =
      R"(| name          | group     | avg         | debt       |
|---------------|-----------|-------------|------------|
|Ivanov Petr    | 1         | 4.25        | none       |
|---------------|-----------|-------------|------------|
|Sidorov Ivan   | 31        | 4           | C++        |
|---------------|-----------|-------------|------------|
|Pertov Nikita  | IU8-31    | 3.33        | 3 items    |
|---------------|-----------|-------------|------------|
)";
  std::stringstream ss;
  auto students = From_File("table_test.json");
  Print(students, ss);
  EXPECT_EQ(ss.str(), table);
}

TEST(Json_Parser_Test, Items_Is_Not_Array) {
  std::fstream file{"bad_file.json", std::ios::out};
  if (!file.is_open()) {
    FAIL() << "Unable to open \"bad_file.json\"" << std::endl;
  }
  std::string bad_file =
      R"({
"items": 0,
"name": "Ivan Ivanov",
"group": 39,
"avg": 4,
"debt": null,
"_meta": {
"count": 3
}
})";
  file << bad_file;
  file.close();
  EXPECT_THROW(auto students = From_File("bad_file.json"),
               std::runtime_error);
}

