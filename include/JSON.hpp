// Copyright 2020 Danil Postvaykin <postvaykin01@mail.ru>
#pragma once

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <vector>
#include <iomanip>
#include <fstream>
#include <any>

using nlohmann::json;

struct Students
{
  std::string name;
  std::any group;
  std::any avg;
  std::vector<std::any> debt;
  int len_name;
  int len_group;
  int len_avg;
  int len_debt;
};

class JSON {
 public:
  JSON(std::string &j);
  JSON();
  void create_vec(json &j);
  json get_js();
  ~JSON();
  void read_file(std::string &path);
  void out();
  void len_all();
  void get_length();
  void length_max();

  int len_name_max = 0;
  int len_group_max = 0;
  int len_avg_max = 7;
  int len_debt_max = 0;
 private:
  json _j;
  std::vector<Students> all_students;
  int _size_vector = 0;
  std::string str = "";
};

