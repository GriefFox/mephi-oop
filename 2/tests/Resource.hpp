#ifndef OOPPROG2
#define OOPPROG2

// #include <cstddef>
#include <string>
#include <iostream>

namespace prog2 {

  class Resource{
    private:
      std::string name;
      double cons;
      double effi;
      uint price;

    public:
      Resource();
      explicit Resource(std::string name, double consumption, double efficiency, uint price);
      explicit Resource(std::string name, uint price);
      Resource (const Resource &ob); 
      


      // getter
      std::string getName() const {return name;};
      double getCons() const {return cons;};
      double getEffi() const {return effi;};
      uint getPrice() const {return price;};
      
      // setter
      Resource &setName(std::string name) {(*this).name=name; return *this;};
      Resource &setCons(double cons) {(*this).cons=cons; return *this;};
      Resource &setEffi(double effi) {(*this).effi=effi; return *this;};
      Resource &setPrice(uint price) {(*this).price=price; return *this;};

      Resource operator + (const Resource &rhs) const;
      bool operator==(const Resource &rhs) const;
      bool operator<(const Resource &rhs) const;
      Resource operator * (double n) const;


      double proffit()const;

      
  };
  
  std::istream& operator>>(std::istream &os, Resource&rhs);
  std::ostream& operator<<(std::ostream &os, Resource&rhs);
}

#endif
