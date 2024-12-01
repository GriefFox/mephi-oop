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

  REQUIRE_THROWS(t.del_res("5"));
  REQUIRE_NOTHROW(t.del_res("1"));
}

TEST_CASE("table find check"){
  Resource r1("1", 1);
  Resource r2("2", 1);
  Resource r3("3", 1);
  Resource r4("4", 1);
  Resource r5("5", 1);
  Resource rs[5]{r1,r2,r3,r4,r5};
  Table t(rs, 5);

  REQUIRE(t["1"] == r1);
  REQUIRE(t["2"] == r2);
  REQUIRE(t["3"] == r3);
  REQUIRE(t["4"] == r4);
  REQUIRE(t["5"] == r5);
}
TEST_CASE("check_size tests"){
  Resource small[0];
  Table table(small, 0);
  REQUIRE(table.check_size() == prog2::Table::empty);
  Resource odin("odin", 1);
  table += odin;

  REQUIRE(table.check_size() == prog2::Table::partially);
  Resource dva("dva", 2);
  table += dva;
  REQUIRE(table.check_size() == prog2::Table::full);
  Resource tri("tri", 3);
  table += tri;
  REQUIRE(table.check_size() == prog2::Table::partially);

}

TEST_CASE("moving/coping constructors"){
  Table t1;
  Resource r1("1", 1);
  t1+=r1;
  Table tc = t1;
  
  REQUIRE(tc.check_size() == t1.check_size() );
  REQUIRE((tc["1"]) == (t1["1"]));
  Table tm;
  tm = std::move(t1);

  REQUIRE(t1.check_size() == prog2::Table::empty);

  REQUIRE(tm.check_size() == prog2::Table::partially);
  REQUIRE((tm["1"]) == (tc["1"]));

  Table tc1;
  tc1 = tm;
  REQUIRE(tc1.check_size() == tm.check_size());
  REQUIRE(tc1["1"] == tm["1"]);
  }

TEST_CASE("outputs"){
  Resource d("1", 100, 200, 300);
  std::stringstream out;  
  out << d;
  REQUIRE(out.str() == "1 consumption: 100 efficiency: 200 price: 300");
  Table t;
  t += d;
  out.str(std::string());
  out << t;
  REQUIRE(out.str() == "1 consumption: 100 efficiency: 200 price: 300\n");
  }

TEST_CASE("inputs resource"){
  std::string str = "tovar 100 200 300\n";
  std::istringstream istream(str);
  Resource r;
  istream >> r;
  REQUIRE(r.getName() == "tovar");
  REQUIRE(r.getCons() == 100);
  REQUIRE(r.getEffi() == 200);
  REQUIRE(r.getPrice() == 300);
}

TEST_CASE("input table"){
  std::string str = "1\ntovar 100 200 300\n";
  std::istringstream istream(str);
  Table t;
  istream >> t;
  REQUIRE(t.check_size() == prog2::Table::partially);
  Resource test("tovar", 100, 200, 300);
  REQUIRE((t["tovar"]) == test);
}
