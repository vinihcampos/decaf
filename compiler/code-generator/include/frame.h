#ifndef _FRAME_
#define _FRAME_

#include <vector>
#include <string>

class Frame{
	public:
		std::string label;
		int id;
		std::vector<std::string> formals;

		Frame(std::string label_, int id_, std::vector<std::string> formals_) :
		label{label_}, id{id_}, formals{formals_}{}

};

#endif