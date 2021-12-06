#include "BtmlParser.hpp"

//constructor
btml::BtmlParser::BtmlParser(std::string path):
	optionHandler(),
	document(path){}

std::string btml::BtmlParser::parseXml(pugi::xml_node * root){
	std::string output = "";
  //if the node has a name, indent bassed upon its parent node and output node name and value
  if(std::string(root->name()).compare("")!= 0){
    //print indentatioj
    btml::option outOpp = optionHandler.getOption(std::string(root->name()));
    std::string endseq = outOpp.end;
    output += outOpp.begin;
    //color the text if there is a color atribute
    if(root->attribute("color")){
      output += this->parseColor(root->attribute("color").value());
      endseq += "\033[38;2;255;255;255m";
    }
    //check if background
    if(root->attribute("background")){
      output += this->parseColor(root->attribute("background").value(),true);
      endseq += "\033[0m";
    }
    output += root->child_value();

    //recursive call to the function to output all child nodes
    for (pugi::xml_node child : root->children()){
      output += this->parseXml(&child);
      output += outOpp.spacer;
    }
    return output += endseq;
  }
	return output;
}

std::string btml::BtmlParser::parseDoc(){
  return this->parseXml(&document.body);
}

std::string btml::BtmlParser::parseColor(const char * hex,bool isbg){
			
      //int rgb values
      int r = std::stoul(std::string(hex,hex+2), nullptr, 16);
      int g = std::stoul(std::string(hex+2,hex+4), nullptr, 16);
      int b = std::stoul(std::string(hex+4,hex+6), nullptr, 16);
			std::string beginSeq;
			if(isbg){
				beginSeq = "\033[48;2;";
			}else{
				beginSeq = "\033[38;2;";
			}
			return beginSeq + std::to_string(r) +";" + std::to_string(g) +";"+std::to_string(b) +"m";
}


