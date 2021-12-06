#include "DocumentHandler.hpp"

//contructor for path containing xml file
btml::DocumentHandler::DocumentHandler(std::string path){
	parseRes = doc.load_file(path.c_str());
	body = doc.child("btml").child("body");
}


//private method used to recursively print the items in an xml document
void btml::DocumentHandler::printXmlTree(pugi::xml_node k, int indent){
  //if the node has a name, indent bassed upon its parent node and output node name and value
  if(std::string(k.name()).compare("")!= 0){
    //print indentation
    for(int i = 0; i < indent; i++){
      std::cout << "\t";
    }
    std::cout << "\033[38;5;28m" <<k.name() 
    << "\033[0m"<<": " << k.child_value() << " {";

    for(pugi::xml_attribute attr =k.first_attribute(); attr; attr = attr.next_attribute()){
      std::cout << attr.name()<<": " <<attr.value() << " ";
    }
    std::cout << "}\n";
    //increase the ident for the children of the current node
    indent++;
  }
  //recursive call to the function to output all child nodes
  for (pugi::xml_node child: k.children()){
    this->printXmlTree(child,indent);
  }
}
void btml::DocumentHandler::coutDOM(){
	this->printXmlTree(body);
}