// #include <exception>
#include <iostream>
#include <ostream>
#include "Resource.hpp"
#include "Table.hpp"
#include <sstream>
using namespace prog2;
int main(){
  Resource r4[0];
  Table table(r4, 0);
  // std::cout << l["AAA2"] << std::endl;
  // l+= r3;
  Resource r1("1", 100);
  table += r1;
  // std::cout << &l.table << std::endl;
  std::cout << table << std::endl << table.check_size();
  return 0;

}
