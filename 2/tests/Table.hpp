#ifndef TABLE
#define TABLE

#include <string>
#include <iostream>
#include "Resource.hpp"

namespace prog2 {
    class Table{
    private:

      uint _allocated;
      uint _correct_size(uint);
      void _sort();

    public:
      uint size;
      Resource **table;
      ~Table(); // Деструктор
      explicit Table() noexcept: _allocated(0), size(0),  table(nullptr){};
      explicit Table(const Table&other) noexcept; // копирующий конструктор
      Table(Table &&other) noexcept; // перемещающий конструктор
      Table &operator= (const Table &) noexcept; // копирующий оператор
      Table &operator= (Table &&other) noexcept; // перемещающий оператор
      Table(Resource *rhs, uint a);


      Resource& operator [] (const std::string &name);
      Table &operator += (const Resource &rhs);
      double proffit()const;
      Table &operator * (double n);
      bool del_res(std::string name); 
      bool rename(std::string oname, std::string nname);
      
      enum stat{
        empty,
        partially,
        full
      };
      stat check_size(); // return how many you can add without another allocating memory
  };

  std::ostream& operator>>(std::ostream &os, Table&rhs);
  std::ostream& operator<<(std::ostream &os, Table&rhs);
}

#endif
