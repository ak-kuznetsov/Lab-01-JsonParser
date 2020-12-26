// Copyright 2020 ak-kuznetsov <a.kuznetsov2701@mail.ru>

#include <gtest/gtest.h>
#include <Json_Parser.hpp>

TEST(Json_Parser_Test, Table_Test) {
  const char j_string[] =
R"({"name": "Ivan Ivanov", "group": "IU10-39", "avg": "4", "debt": "C++"})";
  nlohmann::json j = nlohmann::json::parse(j_string);
  Student Nikita(j);

  const char j_string1[] =
R"({"name": "Ivan Ivanov", "group": 39, "avg": 4, "debt": null})";
  j = nlohmann::json::parse(j_string1);
  Student Ivan(j);

  const char j_string2[] =
      R"({"name": "Ivan Ivanov", "group": "Nine", "avg": 3.33, "debt": ["C++", "Linux", "Network"]})";
  j = nlohmann::json::parse(j_string2);
  Student Petr(j);

  Json_Parser parser(std::vector<Student>{Petr, Ivan, Nikita});

  std::stringstream parser_stream;
  parser_stream << parser;
  std::string ref_string =
      R"(|-----------|-------|----|-------|
|name       |group  |avg |debt   |
|-----------|-------|----|-------|
|Ivan Ivanov|Nine   |3.33|3 items|
|-----------|-------|----|-------|
|Ivan Ivanov|39     |4   |null   |
|-----------|-------|----|-------|
|Ivan Ivanov|IU10-39|4   |C++    |
|-----------|-------|----|-------|
)";

  EXPECT_TRUE(ref_string == parser_stream.str());
}

TEST(Json_Parser_Test, File_Open_Bad) {
  try {
    Json_Parser::From_File("Bad_File.json");
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() == std::string("unable to open file"));
  }
}

TEST(Json_Parser_Test, Items_is_array_Bad) {
  std::string json_string1 =
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
  std::ofstream true_file;
  true_file.open("true_file.json", std::ios::out);
  true_file << json_string1;
  true_file.close();
  try {
    Json_Parser::From_File("true_file.json");
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() ==
                    std::string("incorrect items field, items should be an array"));
  }
}

TEST(Json_Parser_Test, Meta_Test) {
  std::string json_string1 =
R"({
"items": [
{
"name": "Ivan Ivanov",
"group": 39,
"avg": 4,
"debt": null
}
],
"_meta": {
"count": 2
}
})";
  std::ofstream true_file;
  true_file.open("true_file.json", std::ios::out);
  true_file << json_string1;
  true_file.close();
  try {
    Json_Parser::From_File("true_file.json");
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() ==
                    std::string(R"(incorrect count field, count at meta
     should be equal items field size)"));
  }
}

