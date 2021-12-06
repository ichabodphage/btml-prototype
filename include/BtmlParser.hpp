#include <iostream>
#include <map>
#include "../handlers/BtmlOptionHandler.hpp"
#include "../handlers/DocumentHandler.hpp"

//Btml parser parses a btml document into text
namespace btml{

  //btml parser class
  class BtmlParser{
	private:
		//parses an XML document using the tagmap for formating
    std::string parseXml(pugi::xml_node * root);
  public:
    //handler for btml options
    btml::BtmlOptionHandler optionHandler;
		//handler for btml documents
		btml::DocumentHandler document;
    //constructor using path of xml file
    BtmlParser(std::string path);
    //parses the doc variable
    std::string parseDoc();
		//parses and returns correct escape characters for color atributes
		std::string parseColor(const char * hex,bool isbg = false);
  };
}