#include <iostream>
#include "pugixml/pugixml.hpp"
#include <map>
namespace btml{

  //btml option struct 
  struct option{
    //begining and end escape characters
    std::string begin;
    std::string end;

    // spacer determines the string that fits inbetween elements
    std::string spacer;

    //constructor for initializing begin and end, spacer is instalized as a blank string
    option(std::string b,std::string e);

    //constructor for option that just includes spacing
    option(std::string space);
    //constructor holding escape characters and spacers
    option(std::string b,std::string e,std::string space);
  };
  
  
  //btml parser class
  class BtmlParser{
  public:
    //maps certian XML tags to BTML formating characters
    std::map<std::string, btml::option> btmlTagMap;
    //xml document var
    pugi::xml_document doc;

    //result of parsing xml document
    pugi::xml_parse_result res;

    //main XML node for traversal
    pugi::xml_node rootNode;

    //constructor using path of xml file
    BtmlParser(std::string path);

    //adds a tag to the btml tag map
    void addTag(std::string name, btml::option op);

    //displays a JSON like output of all the data in an XML node,
    void coutXmlTree(pugi::xml_node k,int indent=0);

    //displays the document object model tree along with its values
    void coutDOM(){
      this->coutXmlTree(this->rootNode);
    }
    //parses an XML document using the tagmap for formating
    void coutParseXml(pugi::xml_node root);
    //parses the doc variable
    void coutParseDoc();
  };
}