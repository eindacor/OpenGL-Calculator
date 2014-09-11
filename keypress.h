#ifndef KEYPRESS_H
#define KEYPRESS_H

#include "header.h"

class key_handler
{
public:
	key_handler(){};
	~key_handler(){};

	bool checkPress(int key, GLFWwindow* window);
	KEYRETURN key_handler::checkKeys(line_group &lines, display_handler &display_context, settings &user_settings);

private:
	list<int> keysPressed;

};

#endif