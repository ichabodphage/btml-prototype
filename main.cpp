#include <iostream>
#include "pugixml/pugixml.hpp"
#include "btml.hpp"
int main() {

  btml::BtmlParser p("menu.xml");
  p.coutParseDoc();
  
} 