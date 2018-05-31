#include "catch.hpp"

#include <elelel/hostspp/vector>

TEST_CASE("Element") {
  namespace hosts = elelel::hosts;
  
  WHEN("Constructing from strings") {
    hosts::ip ip_direct("Direct string");
    REQUIRE(std::string(ip_direct) == "Direct string");
    const std::string const_str("Const string");
    hosts::ip ip_const(const_str);
    REQUIRE(std::string(ip_const) == "Const string");
    std::string move_str("Move str");
    hosts::ip ip_move(std::move(move_str));
    REQUIRE(std::string(ip_move) == "Move str");
    hosts::ip ip_assigned_const;
    ip_assigned_const = const_str;
    REQUIRE(std::string(ip_assigned_const) == "Const string");
    std::string move_assign_str("Move assign str");
    hosts::ip ip_assigned_move;
    ip_assigned_move = std::move(move_assign_str);
    REQUIRE(std::string(ip_assigned_move) == "Move assign str");
  }
  WHEN("Constructing from other") {
    const hosts::ip ip_copy_src("Copy src");
    hosts::ip ip_copy_dst(ip_copy_src);
    REQUIRE(std::string(ip_copy_dst) == "Copy src");
    hosts::ip ip_move_src("Move src");
    hosts::ip ip_move_dst(std::move(ip_move_src));
    REQUIRE(std::string(ip_move_dst) == "Move src");
    hosts::ip ip_assigned_copy;
    ip_assigned_copy = ip_copy_src;
    REQUIRE(std::string(ip_assigned_copy) == "Copy src");
    hosts::ip ip_assign_move("Move assign");
    hosts::ip ip_assigned_move;
    ip_assigned_move = std::move(ip_assign_move); 
    REQUIRE(std::string(ip_assigned_move) == "Move assign");
  }

  // Disallow implicit canonical/alias conversion for now
  /*
  WHEN("Checking canonical/alias interoperability") {
    hosts::canonical c("Canonical");
    c = hosts::alias("Make this alias hostname canonical");
    REQUIRE(std::string(c) == "Make this alias hostname canonical");
    hosts::alias a("Alias");
    a = hosts::canonical("Make this canonical hostname alias");
    REQUIRE(std::string(a) == "Make this canonical hostname alias");
    }*/
}

TEST_CASE("Vector with preservation") {
  namespace hosts = elelel::hosts;
  hosts::vector<> v;

  WHEN("Creating hosts lines") {
    v.push_back();
    REQUIRE(v.size() == 1);
    v.push_back("  # Comment1");
    REQUIRE(v.size() == 2);
    v.push_back("1.2.3.2 canonical2   alias2_1 alias2_2   # Comment2");
    REQUIRE(v.size() == 3);
    v.push_back(hosts::ip(" 1.2.3.3 "), hosts::canonical(" canonical3 "));
    REQUIRE(v.size() == 4);
    v.push_back(hosts::ip("1.2.3.4"), hosts::canonical("canonical4"), hosts::comment("Comment4"));
    REQUIRE(v.size() == 5);
    v.push_back(hosts::ip("1.2.3.5"), hosts::canonical("canonical5"), hosts::alias("Alias5_1"), hosts::alias("Alias5_2"));
    REQUIRE(v.size() == 6);
    v.push_back(hosts::ip("1.2.3.6"), hosts::canonical("canonical6"), hosts::alias("Alias6_1"), hosts::alias("Alias6_2"), hosts::comment("Comment6"));
    REQUIRE(v.size() == 7);
    v.push_back("1.2.3.7 canonical7 #");
    REQUIRE(v.size() == 8);
    
    THEN("Check each line's contents") {
      THEN("Line 0") {
        auto& l = v[0];
        REQUIRE(l.preserved_string() == nullptr);
        REQUIRE(bool(l.ip()) == false);
        REQUIRE(bool(l.canonical()) == false);
        REQUIRE(l.aliases().size() == 0);
        REQUIRE(bool(l.comment()) == false);
        REQUIRE(std::string(l) == "");
      }

      THEN("Line 1") {
        auto& l = v[1];
        REQUIRE(l.preserved_string() != nullptr);
        REQUIRE(l.preserved_string() == std::string("  # Comment1"));
        REQUIRE(bool(l.ip()) == false);
        REQUIRE(bool(l.canonical()) == false);
        REQUIRE(l.aliases().size() == 0);
        REQUIRE(l == hosts::comment(" Comment1"));
        REQUIRE(std::string(l) == "  # Comment1");
      }

      THEN("Line 2") {
        auto& l = v[2];
        REQUIRE(l.preserved_string() != nullptr);
        REQUIRE(l.preserved_string() == std::string("1.2.3.2 canonical2   alias2_1 alias2_2   # Comment2"));
        REQUIRE(l == hosts::ip("1.2.3.2"));
        REQUIRE(l == hosts::canonical("canonical2"));
        REQUIRE(l.aliases().size() == 2);
        REQUIRE(l.aliases()[0] == hosts::alias("alias2_1"));
        REQUIRE(l.aliases()[1] == hosts::alias("alias2_2"));
        REQUIRE(l == hosts::comment(" Comment2"));
      }

      THEN("Line 3") {
        auto& l = v[3];
        REQUIRE(l.preserved_string() == nullptr);
        REQUIRE(l == hosts::ip("1.2.3.3"));
        REQUIRE(l == hosts::canonical("canonical3"));
        REQUIRE(l.aliases().size() == 0);
        REQUIRE(bool(l.comment()) == false);
      }

      THEN("Line 4") {
        auto& l = v[4];
        REQUIRE(l.preserved_string() == nullptr);
        REQUIRE(l == hosts::ip("1.2.3.4"));
        REQUIRE(l == hosts::canonical("canonical4"));
        REQUIRE(l.aliases().size() == 0);
        REQUIRE(l == hosts::comment("Comment4"));
      }

      THEN("Line 5") {
        auto& l = v[5];
        REQUIRE(l.preserved_string() == nullptr);
        REQUIRE(l == hosts::ip("1.2.3.5"));
        REQUIRE(l == hosts::canonical("canonical5"));
        REQUIRE(l.aliases().size() == 2);
        REQUIRE(l.aliases()[0] == hosts::alias("Alias5_1"));
        REQUIRE(l.aliases()[1] == hosts::alias("Alias5_2"));
      }

      THEN("Line 6") {
        auto& l = v[6];
        REQUIRE(l.preserved_string() == nullptr);
        REQUIRE(l == hosts::ip("1.2.3.6"));
        REQUIRE(l == hosts::canonical("canonical6"));
        REQUIRE(l.aliases().size() == 2);
        REQUIRE(l.aliases()[0] == hosts::alias("Alias6_1"));
        REQUIRE(l.aliases()[1] == hosts::alias("Alias6_2"));
        REQUIRE(l == hosts::comment("Comment6"));
      }

      THEN("Line 7") {
        auto& l = v[7];
        REQUIRE(l.preserved_string() != nullptr);
        REQUIRE(l.preserved_string() == std::string("1.2.3.7 canonical7 #"));
        REQUIRE(l.ip() == hosts::ip("1.2.3.7"));
        REQUIRE(l.canonical() == hosts::canonical("canonical7"));
        REQUIRE(l.aliases().size() == 0);
        REQUIRE(bool(l.comment()) == false);
      }
    }
  }
}
