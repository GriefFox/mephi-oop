#ifndef OOPPROG2
#define OOPPROG2

// #include <cstddef>
#include <string>
#include <iostream>

namespace prog2 {
  /**
 * @brief Класс Resource представляет собой ресурс с определенными характеристиками.
 *
 * Класс включает информацию о названии ресурса, его потреблении,
 * эффективности и цене. Предоставляет методы для работы с этими данными.
 */
  class Resource{
    private:
    std::string name; ///< Название ресурса.
    double cons; ///< Потребление ресурса.
    double effi; ///< Эффективность ресурса.
    uint price; ///< Цена ресурса.

    public:
    /**
      @brief Конструктор по умолчанию.
     
     Инициализирует ресурс с пустыми значениями.
     */
      Resource();
      /**
      @brief Конструктор с параметрами для инициализации ресурса.
     
      @param name Название ресурса.
      @param consumption Потребление ресурса.
      @param efficiency Эффективность ресурса.
      @param price Цена ресурса.
     */
      explicit Resource(std::string name, double consumption, double efficiency, uint price);
       /**
      @brief Конструктор для инициализации ресурса с названием и ценой.
     
      @param name Название ресурса.
      @param price Цена ресурса.
     */
      explicit Resource(std::string name, uint price);
	     /**
      @brief Конструктор копирования для класса Resource.
     
      Создает новый объект Resource как копию существующего объекта.
     
      @param ob Объект, который будет скопирован.
     */
      Resource (const Resource &ob); 
      


      // getter
	/**
      @brief Получает название ресурса.
     
      @return Название ресурса.
     */
      std::string getName() const {return name;};
       /**
      @brief Получает потребление ресурса.
     
      @return Потребление ресурса.
     */
      double getCons() const {return cons;};
      /**
      @brief Получает эффективность ресурса.
     
      @return Эффективность ресурса.
     */
      double getEffi() const {return effi;};
      /**
      @brief Получает цену ресурса.
     
      @return Цена ресурса.
     */ 
      uint getPrice() const {return price;};
      
      // setter
      /**
      @brief Устанавливает название ресурса.
     
      @param name Новое название ресурса.
      @return Ссылку на текущий объект Resource для цепочного вызова методов.
     */
    Resource &setName(std::string name) { (*this).name = name; return *this; };

    /**
      @brief Устанавливает потребление ресурса.
     
      @param cons Новое потребление ресурса.
      @return Ссылку на текущий объект Resource для цепочного вызова методов.
     */
    Resource &setCons(double cons) { (*this).cons = cons; return *this; };

    /**
      @brief Устанавливает эффективность ресурса.
     
      @param effi Новая эффективность ресурса.
      @return Ссылку на текущий объект Resource для цепочного вызова методов.
     */
    Resource &setEffi(double effi) { (*this).effi = effi; return *this; };

    /**
      @brief Устанавливает цену ресурса.
     
      @param price Новая цена ресурса.
      @return Ссылку на текущий объект Resource для цепочного вызова методов.
     */
    Resource &setPrice(uint price) { (*this).price = price; return *this; };

/**
       @brief Оператор сложения для ресурсов. 
      
       Позволяет складывать два объекта Resource.
      
       @param rhs Второй ресурс для сложения.
       @return Новый объект Resource, представляющий сумму двух ресурсов.
       @throw если объекта нет
      */
      Resource operator + (const Resource &rhs) const;
    /**
       @brief Оператор равенства для ресурсов. 
      
       Проверяет, равны ли два объекта Resource. 
      
       @param rhs Второй ресурс для сравнения. 
       @return true, если объекты равны; иначе false.
      */
    bool operator==(const Resource &rhs) const;

    /**
       @brief Оператор меньше для ресурсов. 
      
       Позволяет сравнивать два объекта Resource по цене. 
      
       @param rhs Второй ресурс для сравнения. 
       @return true, если текущий ресурс дешевле; иначе false. 
      */
    bool operator<(const Resource &rhs) const;

    /**
       @brief Оператор умножения для ресурсов. 
      
       Позволяет умножать ресурс на число. 
      
       @param n Коэффициент для умножения. 
       @return Новый объект Resource, представляющий результат умножения. 
      */
    Resource operator*(double n) const;
    /**
      @brief Считает проффит ресурса.
      Считает сколько ресурс принесет(или нет) прибыли.
      @return Число в формате double.
     */
      double proffit()const;

      
  };
  
  std::istream& operator>>(std::istream &os, Resource&rhs);
  std::ostream& operator<<(std::ostream &os, Resource&rhs);
}

#endif
