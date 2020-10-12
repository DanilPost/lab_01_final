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

    if (it->at("debt").is_null())
      st.debt.push_back(nullptr);
    else if (it->at("debt").is_string())
      st.debt.push_back(it->at("debt").get<std::string>());
    else if (it->at("debt").is_array())
    {
      for (json::const_iterator i = it->at("debt").cbegin();
           i != it->at("debt").cend(); i++)
        st.debt.push_back(i.value());
    }
    else
        throw;
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
      all_students[i].len_avg = 4;

    int n = all_students[i].debt.size();
    if (n == 1) {
      if (all_students[i].debt[0].type() == typeid(nullptr))
        all_students[i].len_debt = 7;
      else if (all_students[i].debt[0].type() == typeid(std::string))
        all_students[i].len_debt =
            (std::any_cast<std::string>(all_students[i].debt[0]).length());
    } else all_students[i].len_debt = 7;
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
  str = str + "| name ";
  std::cout << "| name ";
  for ( int i = 5; i <= len_name_max; i++)
  {
    str = str + " ";
    std::cout << " ";
  }
  str = str + "| group";
  std::cout << "| group";
  for ( int i = 5; i <= len_group_max; i++)
  {
    str = str + " ";
    std::cout << " ";
  }
  str = str + "| avg";
  std::cout << "| avg";
  for ( int i = 3; i <= len_avg_max; i++ )
  {
    str = str + " ";
    std::cout << " ";
  }
  str = str + "| debt";
  std::cout << "| debt";
  for ( int i = 4; i <= len_avg_max; i++ )
  {
    str = str + " ";
    std::cout << " ";
  }
  str = str + "|\n";
  std::cout << "|" << std::endl;
}

void JSON::out()
{
  for ( int i = 0; i < _size_vector; i++ )
    {
    str = str + "|";
      std::cout << "|";
    for ( int j = 0; j <= len_name_max+1; j++ )
    {
      str = str + "-";
      std::cout<< "-";
    }
      str = str + "|";
      std::cout << "|";
    for ( int j = 0; j <= len_group_max+1; j++ )
    {
      str = str + "-";
      std::cout<< "-";
    }
      str = str + "|";
      std::cout << "|";
    for ( int j = 0; j <= len_avg_max+1; j++ )
    {
      str = str + "-";
      std::cout<< "-";
    }
    str = str + "|";
      std::cout << "|";
    for ( int j = 0; j <= len_debt_max+1; j++ )
    {
      str = str + "-";
      std::cout<< "-";
    }
    str = str + "|\n|";
      std::cout << "|" << std::endl;

      std::cout << "| ";
    str = str + " " + all_students[i].name;
      std::cout << all_students[i].name;
    for ( int j = all_students[i].len_name; j <= len_name_max; j++ )
    {
      str = str + " ";
      std::cout << " ";
    }
    str = str + "| ";
      std::cout << "| ";
    if (all_students[i].group.type() == typeid(int)) {
      str = str + std::to_string(std::any_cast<int>(all_students[i].group));
      std::cout << std::any_cast<int>(all_students[i].group);
    } else if (all_students[i].group.type() == typeid(std::string)) {
      str = str + std::any_cast<std::string>(all_students[i].group);
      std::cout << std::any_cast<std::string>(all_students[i].group);
    } else if (all_students[i].group.type() == typeid(float)) {
      str = str + std::to_string(std::any_cast<float>(all_students[i].group));
      std::cout << std::any_cast<float>(all_students[i].group);
    }
    for ( int j = all_students[i].len_group; j <= len_group_max; j++ )
    {
      str = str + " ";
      std::cout << " ";
    }
    str = str + "| ";
      std::cout << "| ";
    if (all_students[i].avg.type() == typeid(int)) {
      str = str + std::to_string(std::any_cast<int>(all_students[i].avg));
      std::cout << std::any_cast<int>(all_students[i].avg);
    } else if (all_students[i].avg.type() == typeid(float)) {
      std::ostringstream avg_pr;
// Set Fixed -Point Notation
      avg_pr << std::fixed;
// Set precision to 2 digits
      avg_pr << std::setprecision(2);
//Add double to stream
      avg_pr << std::any_cast<float>(all_students[i].avg);
// Get string from output string stream
      std::string avg = avg_pr.str();
      str = str + avg;
      std::cout << avg;
    } else if (all_students[i].avg.type() == typeid(std::string)) {
      str = str + std::any_cast<std::string>(all_students[i].avg);
      std::cout << std::any_cast<std::string>(all_students[i].avg);
    }
    for ( int j = all_students[i].len_avg; j <= len_avg_max; j++ )
    {
      str = str + " ";
      std::cout << " ";
    }
    str = str + "| ";
      std::cout << "| ";

    int n = all_students[i].debt.size();

    if ( n == 1 ) {
      if (all_students[i].debt[0].type() == typeid(nullptr)){
        std::cout << "nullptr";
        str = str + "nullptr";
      }
      if (all_students[i].debt[0].type() == typeid(std::string))
      {
        std::cout << std::any_cast<std::string>(all_students[i].debt[0]);
        str = str + std::any_cast<std::string>(all_students[i].debt[0]);
      }
    } else {
      str = str + "items ";
      str = str + std::to_string(n);
      std::cout << "items " << n; }
    for ( int j = all_students[i].len_debt; j <= len_debt_max; j++ )
    {
      str = str + " ";
      std::cout << " ";
    }
    str = str + "|\n";
      std::cout << "|" << std::endl;
  }
  std::cout << std::endl << std::endl;
  //cout << str;
}

JSON::~JSON(){}
