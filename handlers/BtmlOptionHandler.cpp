#include "BtmlOptionHandler.hpp"
// escape code option constructor with empty spacer
btml::option::option(std::string b, std::string e):
	begin(b),
	end(e),
	spacer(""){};

// spacer option constructor
btml::option::option(std::string space):
	begin(""),
	end(""),
	spacer(space){};
	
//option constructor with escape codes and spacer
btml::option::option(std::string b, std::string e,std::string space):
	begin(b),
	end(e),
	spacer(space){};

//constructor that initalizes all of the standard btml options
btml::BtmlOptionHandler::BtmlOptionHandler(){
	//main body tag
	this->addFullTag("body","","\033[0m","\n");
	
	//regular formating tags tags
	this->addEscapeTag("p","","");
	this->addEscapeTag("bold","\033[1m","\033[0m");
	this->addEscapeTag("dim","\033[2m","\033[22m");
	this->addEscapeTag("invert","\033[7m","\033[27m");
	this->addEscapeTag("underline","\033[4m","\033[24m");
	this->addEscapeTag("li", " - ","");

	//special formating tags
	this->addSpacerTag("ul", "\n");

}
//inserts a spacer tag into the BtmlOptionHandler
void btml::BtmlOptionHandler::addSpacerTag(std::string name,std::string spacerSeq){
	optionMap.insert(
		std::pair<std::string,btml::option>
		(name,option(spacerSeq)
		));
}

//inserts an escape key tag in the BtmlOptionHandler
void btml::BtmlOptionHandler::addEscapeTag(std::string name,std::string b,std::string e){
	optionMap.insert(
		std::pair<std::string,btml::option>
		(name,option(b,e)
		));
}

//inserts an escape key tag in the BtmlOptionHandler
void btml::BtmlOptionHandler::addFullTag(std::string name,std::string b,std::string e,std::string s){
	optionMap.insert(
		std::pair<std::string,btml::option>
		(name,option(b,e,s)
		));
}

//gets an option from the option handler
btml::option btml::BtmlOptionHandler::getOption(std::string name){
	return optionMap.at(name);
}