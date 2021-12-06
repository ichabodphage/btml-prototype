#include "BtmlStream.hpp"
void btml::BtmlStream::operator<<(std::string fileName){
	btml::BtmlParser parser(fileName);
	std::cout << parser.parseDoc();
}