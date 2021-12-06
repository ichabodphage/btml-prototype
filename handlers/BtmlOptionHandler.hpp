#include <string>
#include <map>
//handler for managing BTML Options
namespace btml{
	 struct option{
    //begining and end escape characters
    std::string begin;
    std::string end;

    // spacer determines the string that fits inbetween elements
    std::string spacer;

    //escape key constructor
    option(std::string b,std::string e);

    //spacer constructor
    option(std::string space);

    //full constructor
    option(std::string b,std::string e,std::string space);
  };

	//class that manages Btml Options
	class BtmlOptionHandler{
	public:
		//a map that contains all the btml Options and their tags
		std::map<std::string, btml::option> optionMap;
		//constructor that instalizes standard btml options
		BtmlOptionHandler();

		//methods to insert options into the handler
		void addSpacerTag(std::string name,std::string spacerSeq);

		void addEscapeTag(std::string name,std::string b,std::string e);

		void addFullTag(std::string name,std::string b,std::string e,std::string s);

		option getOption(std::string tag);
	};
}