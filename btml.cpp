#include <iostream>
#include "pugixml/pugixml.hpp"
#include "btml.hpp"
#include <sstream>
//constructor
btml::BtmlParser::BtmlParser(std::string path){
  res = doc.load_file(path.c_str());
  //get btml root node
  rootNode = doc.child("btml");
  //add btml tag as an option with only a spacer
  btml::option rootOp("","\033[0m","\n");
  this->addTag("btml",rootOp);

  //add p tag as an option with empty strings
  btml::option paraOp("","");
  this->addTag("p",paraOp);
  
  //add bold tag with bold escape characters
  btml::option boldOp("\033[1m","\033[0m");
  this->addTag("bold",boldOp);

  //add dim tag with dim escape characters
  btml::option dimOp( "\033[2m","\033[22m");
  this->addTag("dim",dimOp);

  //add invert tag with invert escape characters
  btml::option invertOp( "\033[7m","\033[27m");
  this->addTag("invert",invertOp);

  //add underline tag with underline escape characters
  btml::option underlineOp( "\033[4m","\033[24m");
  this->addTag("underline",underlineOp);

  btml::option listHolderOp("\n");
  this->addTag("ul",listHolderOp);
  btml::option listItemOp(" - ","");
  this->addTag("li",listItemOp);
}
// escape code option constructor
btml::option::option(std::string b, std::string e):begin(b),end(e),spacer(""){};

// spacer option constructor
btml::option::option(std::string space):begin(""),end(""),spacer(space){};
btml::option::option(std::string b, std::string e,std::string space):begin(b),end(e),spacer(space){};
// prints the XML tree
void btml::BtmlParser::coutXmlTree(pugi::xml_node k, int indent){
  //if the node has a name, indent bassed upon its parent node and output node name and value
  if(std::string(k.name()).compare("")!= 0){
    //print indentatioj
    for(int i = 0; i < indent; i++){
      std::cout << "\t";
    }
    std::cout << k.name() 
    <<": " << k.child_value() << " {";

    for(pugi::xml_attribute attr =k.first_attribute(); attr; attr = attr.next_attribute()){
      std::cout << attr.name()<<": " <<attr.value() << " ";
    }
    std::cout << "}\n";
    //increase the ident for the children of the current node
    indent++;
  }
  //recursive call to the function to output all child nodes
  for (pugi::xml_node child: k.children()){
    this->coutXmlTree(child,indent);
  }
}




void btml::BtmlParser::coutParseXml(pugi::xml_node root){
  //if the node has a name, indent bassed upon its parent node and output node name and value
  if(std::string(root.name()).compare("")!= 0){
    //print indentatioj
    btml::option outOpp = btmlTagMap.at(std::string(root.name()));
    std::string endseq = outOpp.end;
    std::cout << outOpp.begin;
    //color the text if there is a color atribute
    if(root.attribute("color")){
      std::string color = root.attribute("color").value();
      //get color strings
      std::string red =  color.substr(0,2);
      std::string green =  color.substr(2,2);
      std::string blue =  color.substr(4,2);
      //int rgb values
      int r = std::stoul(red, nullptr, 16);
      int g = std::stoul(green, nullptr, 16);
      int b = std::stoul(blue, nullptr, 16);
  
      std::string colorOut;

      //use background color escape instead of regular text color escape if background color is any value
      
        colorOut = "\033[38;2;"+ std::to_string(r) +";" + std::to_string(g) +";"+std::to_string(b) +"m";
        endseq += "\033[38;2;255;255;255m";
      

      std::cout << colorOut;
    }

    //check if background
    if(root.attribute("background")){
      std::string color = root.attribute("background").value();
      //get color strings
      std::string red =  color.substr(0,2);
      std::string green =  color.substr(2,4);
      std::string blue =  color.substr(4,6);
      
      //int rgb values
      int r = std::stoul(red, nullptr, 16);
      int g = std::stoul(green, nullptr, 16);
      int b = std::stoul(blue, nullptr, 16);
      std::string colorOut;

      //use background color escape instead of regular text color escape if background color is any value
 
      colorOut = "\033[48;2;"+ std::to_string(r) +";" + std::to_string(g) +";"+std::to_string(b) +"m";
      endseq += "\033[0m";
      

      std::cout << colorOut;
    }
    std::cout <<  root.child_value();

    
    //recursive call to the function to output all child nodes
    for (pugi::xml_node child: root.children()){
      this->coutParseXml(child);
      std::cout << outOpp.spacer;
    }
    std::cout << endseq;
  }
}

void btml::BtmlParser::coutParseDoc(){
  this->coutParseXml(rootNode);
}



//adds a tag to the btml parser
void btml::BtmlParser::addTag(std::string name, btml::option op){
  btmlTagMap.insert(std::pair<std::string,btml::option>(name,op));
}