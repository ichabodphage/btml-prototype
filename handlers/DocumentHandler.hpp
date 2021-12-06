#include "../pugixml/pugixml.hpp"
#include <iostream>
//class that handles the btml document
namespace btml{
	class DocumentHandler{
	private:
		//pretty printer for an xml dom
    void printXmlTree(pugi::xml_node k,int indent=0);
	public:
		//xml document var
    pugi::xml_document doc;

    //result of parsing xml document
    pugi::xml_parse_result parseRes;

    //body node
    pugi::xml_node body;

		DocumentHandler(std::string path);
		//prints out the full DOM
		void coutDOM();
	};
}