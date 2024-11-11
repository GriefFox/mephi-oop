#include "Table.hpp"
#include "Resource.hpp"

#include <stdexcept>
#include <string>
#include <iostream>
#include <algorithm>


namespace prog2 {
uint Table::_correct_size(uint n){
    return (n - n % 2) * 2;
  }

  void Table::_sort(){
    std::sort(table, table + size, [](const Resource *a, const Resource *b) {
        return *b < *a;
    });
  }

  Table::Table(Resource *rhs, uint a){
    _allocated = _correct_size(a);
    size = a;
    table = new Resource*[_allocated];
    for(uint i = 0; i<a; i++){
      Resource pr = rhs[i];

      Resource *tmp = new Resource(pr.getName(), pr.getCons(), pr.getEffi(), pr.getPrice());
      table[i] = tmp;
    }
    _sort();
  }

  Resource& Table::operator[](const std::string& name) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (table[mid]->getName() == name) {
            return *table[mid];
        }
        else if (table[mid]->getName() < name) {
            left = mid + 1;
        }
        else {
            right = mid - 1; 
        }
    }

    throw std::runtime_error("Resource not found: " + name);
  }

  Table &Table::operator *(double n){
    // Table res(*this);
    Resource **tmp = new Resource*[this->_allocated];
    for (uint i=0; i < this->size; i++){
      tmp[i] = new Resource((*this->table[i]) * n);
      delete this->table[i];
    }
    delete[] this->table;
    this->table = tmp;
    return *this;
  }

  Table::Table(Table &&other) noexcept 
    : _allocated(other._allocated), size(other.size), table(other.table) {
    // Обнуляем перемещаемый объект
    other._allocated = 0;
    other.size = 0;
    other.table = nullptr;
}


  Table &Table::operator= (Table &&other) noexcept {
    // Проверяем самоприсваивание
    if (this == &other) {
        return *this;
    }

    // Освобождаем текущие ресурсы
    for (uint i=0;i<size;i++){
    delete table[i];
    }
    delete[] table;
    // Перемещаем данные из другого объекта
    size = other.size;
    _allocated = other._allocated;
    table = other.table;

    // Обнуляем перемещаемый объект
    other.size = 0;
    other._allocated = 0;
    other.table = nullptr;

    return *this;
  }



  Table& Table::operator+=(const Resource &rhs){
    if (this->_allocated == 0){
      this->_allocated = 2;
      delete[] this->table;
      this->table = new Resource*[this->_allocated];
    }

    if (this->size == this->_allocated){
      Resource **tmp = new Resource*[_correct_size(this->_allocated)];
      for (uint i=0; i<this->size; i++)
        tmp[i] = table[i];
      delete[] this->table;
      this->table = tmp;
      this->_allocated = _correct_size(this->_allocated);
    }
    this->table[this->size] = new Resource(rhs);
    this->size++;
    return *this;
    
  }
  
  Table::stat Table::check_size(){
    if (this->size == 0){
      return empty;
    } else if(this->size < this->_allocated) {
      return partially;
    } 
    return full;
  }

  void Table::del_res(std::string name){
    for (uint i=0; i < this->size; ++i){
      if ((this->table)[i]->getName() == name){
        delete (this->table)[i];

        for (uint j=i; j < this->size - 1; ++j){
          (this->table)[j] = (this->table)[j + 1];
        }

        this->size--;
        this->table[this->size] = nullptr;
        return;
      }
    }
    throw std::runtime_error("Resource not found: " + name);
  }

  bool Table::rename(std::string oname, std::string nname){
    try {
      Resource tmp = (*this)[oname];
      (*this)[oname].setName(nname);
    } 
    catch(...){
      throw std::runtime_error("Not such resource");
    }
    this->_sort();
    return 0;
    
  }
  Table :: ~Table(){
    for (uint i=0; i<size; i++){
      delete table[i];
    }
    delete[] table;
  }

  double Table::proffit() const{
    double res = 0;
    for (uint i=0; i<size; i++){
      res += table[i]->proffit();
    }
    return res;
  }

  std::ostream& operator << (std::ostream &os, Table &tab){
    for (uint i=0; i<tab.size;i++){

      os << *(tab.table[i]) << std::endl;

    }
    return os;
  } 
  std::istream& operator >> (std::istream &is, Table &tab){
    // firsly we ask how many Resources we need to add
    uint size = 0;
    is >> size;
    for (uint i=0; i<size; i++){
      Resource tmp;
      is >> tmp;
      tab += tmp;
    }
    return is;
  }
}
