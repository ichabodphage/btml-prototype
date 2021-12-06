#include "BtmlParser.hpp"

//output class for parsed Btml
namespace btml{
	class BtmlStream{
	public:
		void operator<< (std::string fileName);
	};
}