// Copyright 2020 Danil Postvaykin <postvaykin01@mail.ru>
#include "JSON.hpp"
#include <fstream>

JSON::JSON(std::string &j)
{
  _j = json::parse(j);
}

JSON::JSON()
{
}

json JSON::get_js()
{
  return _j;
}

void JSON::read_file(std::string &path)
{
  std::fstream input_file;
  input_file.open(path);
  if (!input_file.is_open())
    throw std::runtime_error("File error");
  std::string string_file;
  input_file >> string_file;
  input_file.close();
  std::cout << string_file << std::endl;
  JSON js_file(string_file);
}

void JSON::create_vec(json &j)
{
  Students st;
  for (json::const_iterator it = j.at("items").cbegin();
       it != j.at("items").cend(); ++it) {
    if (it->at("name").is_string())
      st.name = it->at("name").get<std::string>();
    else
      throw;
    if (it->at("group").is_number_integer())
      st.group = it->at("group").get<int>();
    else if (it->at("group").is_string())
      st.group = it->at("group").get<std::string>();
    else if (it->at("group").is_number_float())
      st.group = it->at("group").get<float>();
    else
      throw;
    if (it->at("avg").is_number_float())
      st.avg = it->at("avg").get<float>();
    else if (it->at("avg").is_number_integer())
      st.avg = it->at("avg").get<int>();
    else if (it->at("avg").is_string())
      st.avg = it->at("avg").get<std::string>();
    else
      throw;

    if (it->at("debt").is_null()) {
      st.debt.push_back(nullptr);
    } else if (it->at("debt").is_string()) {
      st.debt.push_back(it->at("debt").get<std::string>());
    } else if (it->at("debt").is_array()) {
      for (json::const_iterator i = it->at("debt").cbegin();
           i != it->at("debt").cend(); i++)
        st.debt.push_back(i.value());
    } else {
      throw;
    }
    all_students.push_back(st);
    _size_vector += 1;
    st.debt.clear();
  }
  json it = j.at("_meta");
  int m = 0;
  if (it.at("count").is_number_integer())
    m = it.at("count").get<std::size_t>();
  int n = all_students.size();
  if (n != m)
    throw std::runtime_error("Invalid _meta count");
  this->get_length();
}

void JSON::get_length()
{
  int len_null = 7;
  int len_float = 4;
  for ( int i = 0; i < _size_vector; i++ ) {
    all_students[i].len_name = all_students[i].name.length();
    if (all_students[i].group.type() == typeid(std::string))
      all_students[i].len_group =
          (std::any_cast<std::string>(all_students[i].group).length());
    else if (all_students[i].group.type() == typeid(int))
    all_students[i].len_group =
        std::to_string(
              (std::any_cast<int>((all_students[i].group)))).length();
    else if (all_students[i].group.type() == typeid(float))
      all_students[i].len_group =
          std::to_string(
              (std::any_cast<float>((all_students[i].group)))).length();
    if (all_students[i].avg.type() == typeid(std::string))
      all_students[i].len_avg =
          (std::any_cast<std::string>(all_students[i].avg).length());
    else if (all_students[i].avg.type() == typeid(int))
      all_students[i].len_avg =
          std::to_string(
              (std::any_cast<int>((all_students[i].avg)))).length();
    else if (all_students[i].avg.type() == typeid(float))
      all_students[i].len_avg = len_float;

    int n = all_students[i].debt.size();
    if (n == 1) {
      if (all_students[i].debt[0].type() == typeid(nullptr))
        all_students[i].len_debt = len_null;
      else if (all_students[i].debt[0].type() == typeid(std::string))
        all_students[i].len_debt =
            (std::any_cast<std::string>(all_students[i].debt[0]).length());
    } else {
      all_students[i].len_debt = len_null;
    }
  }
  this->length_max();
}

void JSON::length_max()
{
  for ( int i = 0; i < _size_vector; i++ ) {
    if (all_students[i].len_name >= len_name_max)
      len_name_max = all_students[i].len_name;
    if (all_students[i].len_group >= len_group_max)
      len_group_max = all_students[i].len_group;
    if (all_students[i].len_avg >= len_avg_max)
      len_avg_max = all_students[i].len_avg;
    if (all_students[i].len_debt >= len_debt_max)
      len_debt_max = all_students[i].len_debt;
  }
  this->len_all();
}

void JSON::len_all()
{
  int len_name = 5;
  int len_group = 5;
  int len_avg = 3;
  int len_debt = 4;
  str = str + "| name ";
  for ( int i = len_name; i <= len_name_max; i++)
  {
    str = str + " ";
  }
  str = str + "| group";
  for ( int i = len_group; i <= len_group_max; i++)
  {
    str = str + " ";
  }
  str = str + "| avg";
  for ( int i = len_avg; i <= len_avg_max; i++ )
  {
    str = str + " ";
  }
  str = str + "| debt";
  for ( int i = len_debt; i <= len_avg_max; i++ )
  {
    str = str + " ";
  }
  str = str + "|\n";
}

void JSON::out()
{
  for ( int i = 0; i < _size_vector; i++ )
    {
    str = str + "|";
    for ( int j = 0; j <= len_name_max+1; j++ )
    {
      str = str + "-";
    }
      str = str + "|";
    for ( int j = 0; j <= len_group_max+1; j++ )
    {
      str = str + "-";
    }
      str = str + "|";
    for ( int j = 0; j <= len_avg_max+1; j++ )
    {
      str = str + "-";
    }
    str = str + "|";
    for ( int j = 0; j <= len_debt_max+1; j++ )
    {
      str = str + "-";
    }
    str = str + "|\n|";

    str = str + " " + all_students[i].name;
    for ( int j = all_students[i].len_name; j <= len_name_max; j++ )
    {
      str = str + " ";
    }
    str = str + "| ";
    if (all_students[i].group.type() == typeid(int)) {
      str = str + std::to_string(std::any_cast<int>(all_students[i].group));
    } else if (all_students[i].group.type() == typeid(std::string)) {
      str = str + std::any_cast<std::string>(all_students[i].group);
    } else if (all_students[i].group.type() == typeid(float)) {
      str = str + std::to_string(std::any_cast<float>(all_students[i].group));
    }
    for ( int j = all_students[i].len_group; j <= len_group_max; j++ )
    {
      str = str + " ";
    }
    str = str + "| ";
    if (all_students[i].avg.type() == typeid(int)) {
      str = str + std::to_string(std::any_cast<int>(all_students[i].avg));
    } else if (all_students[i].avg.type() == typeid(float)) {
      std::ostringstream avg_pr;
      avg_pr << std::fixed;
      avg_pr << std::setprecision(2);
      avg_pr << std::any_cast<float>(all_students[i].avg);
      std::string avg = avg_pr.str();
      str = str + avg;
    } else if (all_students[i].avg.type() == typeid(std::string)) {
      str = str + std::any_cast<std::string>(all_students[i].avg);
    }
    for ( int j = all_students[i].len_avg; j <= len_avg_max; j++ )
    {
      str = str + " ";
    }
    str = str + "| ";

    int n = all_students[i].debt.size();
    int first = 0;
    if ( n == 1 ) {
      if (all_students[i].debt[first].type() == typeid(nullptr)){
        str = str + "nullptr";
      }
      if (all_students[i].debt[first].type() == typeid(std::string))
      {
        str = str + std::any_cast<std::string>(all_students[i].debt[first]);
      }
    } else {
      str = str + "items ";
      str = str + std::to_string(n); }
    for ( int j = all_students[i].len_debt; j <= len_debt_max; j++ )
    {
      str = str + " ";
    }
    str = str + "|\n";
  }
  std::cout << std::endl << std::endl;
  std::cout << str;
}

JSON::~JSON(){}
