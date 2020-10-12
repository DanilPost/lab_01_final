#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <any>

using namespace std;
using nlohmann::json;

struct Students
{
  string name;
  any group;
  any avg;
  vector<any> debt;
  int len_name;
  int len_group;
  int len_avg;
  int len_debt;
};

class JSON {
 public:
  JSON(string &j);
  JSON();
  void create_vec(json &j);
  json get_js();
  ~JSON();
  void read_file(string &path);
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
  vector<Students> all_students;
  int _size_vector = 0;
  string str = "";
};

