#include <catch2/catch_test_macros.hpp>
#define CATCH_CONFIG_MAIN

#include "Resource.hpp"
#include "Table.hpp"

#include <sstream>
#include <catch2/catch_all.hpp>
using namespace prog2;


TEST_CASE( "Initializing Constructors" ) {
  Resource a;
  REQUIRE(a.getName() == "Resource");
  REQUIRE(a.getCons() == 0.0);
  REQUIRE(a.getEffi() == 0.0);
  REQUIRE(a.getPrice() == 0);

  a.setName("Heher");
  a.setCons(1.0);
  a.setEffi(2.0);
  a.setPrice(3);

  REQUIRE(a.getName() == "Heher");
  REQUIRE(a.getCons() == 1.0);
  REQUIRE(a.getEffi() == 2.0);
  REQUIRE(a.getPrice() == 3);

  Resource b("Tovar1", 100);
  Resource c("Tovar2", 500, 1000, 50);
  
  REQUIRE(b.getName() == "Tovar1");
  REQUIRE(c.getName() == "Tovar2");
  REQUIRE(b.getPrice() == 100);
  REQUIRE(c.getPrice() == 50);
  REQUIRE(b.getCons() == 0.0);
  REQUIRE(c.getCons() == 500);
  REQUIRE(b.getEffi() == 0);
  REQUIRE(c.getEffi() == 1000);
}

TEST_CASE("operators"){
  Resource a("Tovar1", 500, 1000, 100);
  Resource b("Tovar1", 1000, 1500, 500);
  Resource c("Tovar2", 200, 2000, 1000);
  REQUIRE_THROWS(a + c);
  REQUIRE_NOTHROW(a+b);
  Resource e = a + b;

  REQUIRE(e.getName() == "Tovar1");
  REQUIRE(e.getCons() == 1500);
  REQUIRE(e.getEffi() == 2500);
  REQUIRE(e.getPrice() == 100);

  Resource d("Tovar2", 200, 2000, 1000);
  REQUIRE(a == b);
  REQUIRE(d < a);
  Resource g = d * 5;
  
  REQUIRE(g.getName() == "Tovar2");
  REQUIRE(g.getCons() == 1000);
  REQUIRE(g.getEffi() == 10000);
  REQUIRE(g.getPrice() == 1000);
}

TEST_CASE("proffit"){
  Resource a("Test", 99, 100, 100);
  REQUIRE(a.proffit() == 700);
}

TEST_CASE("Table funcs"){
  Resource r1("1", 100, 200, 100);
  Resource r2("2", 200, 100, 100);
  Resource r3("3", 300, 0, 10);

  Resource a[2]{r1, r2};
  Table t(a, 2);
  REQUIRE(t["1"] == r1);
  REQUIRE_THROWS(t["3"]);
  t += r3;
  REQUIRE(t["3"] == r3);
  REQUIRE(t.proffit() == -21000);

  t * 2;

  REQUIRE(t.proffit() == -42000);

  REQUIRE_THROWS(t.rename("4", "5"));
  t.rename("3", "4");
  REQUIRE(t["4"].getPrice() == 10);
  REQUIRE(t["4"].getCons() == 600);
  REQUIRE(t["4"].getEffi() == 0);

  REQUIRE(t.del_res("5") == false);
  REQUIRE(t.del_res("4") == true);

  Resource small[0];
  Table table(small, 0);
  REQUIRE(table.check_size() == prog2::Table::empty);
  Resource odin("odin", 1);
  table += odin;

  REQUIRE(table.check_size() == prog2::Table::partially);

}

TEST_CASE("outputs"){
  Resource d("1", 100, 200, 300);
  std::stringstream out;  
  out << d;
  REQUIRE(out.str() == "1 consumption: 100 efficiency: 200 price: 300");
}
