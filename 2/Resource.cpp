#include "Resource.hpp"
// #include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>

namespace prog2 {

  Resource::Resource(): name("Resource"), cons(0.0), effi(0.0), price(0){

  /*
    name = std::string("Resource");
    cons = *new double;
    cons = 0.0;
    effi = *new double;
    effi = 0.0;
    price = *new uint;
    price = 0;
    */
  }
  Resource::Resource(std::string name, double consumption, double efficiency, uint price): name(name), cons(consumption), effi(efficiency), price(price) {}
  Resource::Resource(std::string name, uint price): name(name), cons(0.0), effi(0.0), price(price){}
  Resource::Resource(const Resource &ob):name(ob.name), cons(ob.cons), effi(ob.effi), price(ob.price){}

  Resource Resource::operator + (const Resource &rhs) const{
    if(name != rhs.name){
      throw std::runtime_error("Not the same name");
    }
    Resource tmp;
    tmp.name = name;
    tmp.cons = rhs.cons + cons;
    tmp.effi = rhs.effi + effi;
    tmp.price = (price < rhs.price) ? price : rhs.price;
    return tmp;
  }
  bool Resource::operator == (const Resource &rhs) const{
    return rhs.name == name;
  }
  bool Resource::operator < (const Resource &rhs) const{
    return rhs.name < name;
  }
  Resource Resource::operator * (double n) const{
    Resource tmp(*this);
    tmp.cons = tmp.cons * n;
    tmp.effi = tmp.effi * n;
    return tmp;
  }
  double Resource::proffit()const{
    return (effi - cons) * 7 * price;
  }

  std::ostream& operator << (std::ostream &os, Resource &rhs){
    os << rhs.getName() << " consumption: " << rhs.getCons() << " efficiency: " << rhs.getEffi() << " price: " << rhs.getPrice();
    return os;
  } 
  std::istream& operator >> (std::istream &os, Resource &rhs){
    std::string name;
    double cons, effi;
    uint price;
    os >> name >> cons >> effi >> price;
    rhs.setName(name);
    rhs.setCons(cons);
    rhs.setEffi(effi);
    rhs.setPrice(price);
    return os;
  }
  
}
