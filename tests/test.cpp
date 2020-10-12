// Copyright 2020 Danil Postvaykin <postvaykin01@mail.ru>

#include <gtest/gtest.h>
#include "JSON.hpp"
#include <string>
#include <nlohmann/json.hpp>

using nlohmann::json;
using namespace std;

TEST(Parser, JSON) {
  EXPECT_TRUE(true);
  std::cout << "Test started!" << endl;
  std::string test_string =
      R"({
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
      "name": "Petrov Nikita",
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
})";
  JSON first(test_string);
  json jes = first.get_js();
  first.create_vec(jes);
  first.out();
}
TEST(String, InvalidString){
  std::cout << "Test2 started!" << endl;
  std::string test_string =\
R"({
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
      "name": "Petrov Nikita",
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
    "count": 2
  }
})";
  try {
    JSON st(test_string);
    json jes = st.get_js();
    st.create_vec(jes);
    st.out();
  } catch (const std::runtime_error& e) {
    std::string expected = e.what();
    std::cout << expected << std::endl;
    std::string ref_string = "Invalid _meta count";
    EXPECT_EQ(expected, ref_string);
  }
}
TEST(Parse, FromFile){
  std::cout << "Test3 started!" << endl;
  try {
    JSON st;
    string path = "table.json";
    st.read_file(path);
    st.out();
  } catch (const std::runtime_error& e){
    string expected = e.what();
    std::cout << expected << std::endl;
    string ref_string = "File error";
    EXPECT_EQ(expected, ref_string);
  }
}