// #include <exception>
#include <iostream>
#include <ostream>
#include "Resource.hpp"
#include "Table.hpp"
#include <sstream>
using namespace prog2;
int main(){
  std::string str = "1 tovar 100 200 300\n";
  std::istringstream istream(str);
  Table t;
  istream >> t;

  std::cout << t << std::endl << t.size;
  return 0;

}
