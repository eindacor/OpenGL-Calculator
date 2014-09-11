#include "keypress.h"

bool key_handler::checkPress(int key, GLFWwindow* window)
{
	int state = glfwGetKey(window, key);

	//check list of keys pressed for a match, acts according to the press state
	for (list<int>::iterator i = keysPressed.begin(); i != keysPressed.end(); ++i)
	{
		if (*i == key)
		{
			if (state == GLFW_RELEASE)
			{
				keysPressed.erase(i);
			}
			return false;
		}		
	}

	switch (state)
	{
	case GLFW_PRESS: keysPressed.push_back(key); return true;
	case GLFW_RELEASE: return false;
	default: return false;
	}
}

KEYRETURN key_handler::checkKeys(line_group &lines, display_handler &display_context, settings &user_settings)
{
	GLFWwindow* window = display_context.getWindow();

	if (checkPress(GLFW_KEY_BACKSPACE, window))
	{
		lines.removeChar();
	}

	if (checkPress(GLFW_KEY_0, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar(')') : lines.addChar('0'));
	}

	if (checkPress(GLFW_KEY_1, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('!') : lines.addChar('1'));
	}

	if (checkPress(GLFW_KEY_2, window))
	{
		lines.addChar('2');
	}

	if (checkPress(GLFW_KEY_3, window))
	{
		lines.addChar('3');
	}

	if (checkPress(GLFW_KEY_4, window))
	{
		lines.addChar('4');
	}

	if (checkPress(GLFW_KEY_5, window))
	{
		lines.addChar('5');
	}

	if (checkPress(GLFW_KEY_6, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('^') : lines.addChar('6'));
	}

	if (checkPress(GLFW_KEY_7, window))
	{
		lines.addChar('7');
	}

	if (checkPress(GLFW_KEY_8, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('*') : lines.addChar('8'));
	}

	if (checkPress(GLFW_KEY_9, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('(') : lines.addChar('9'));
	}

	if (checkPress(GLFW_KEY_A, window))
	{
		lines.addChar('A');
	}

	if (checkPress(GLFW_KEY_B, window))
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
			return BASE;
		
		else lines.addChar('B');
	}

	if (checkPress(GLFW_KEY_C, window))
	{
		lines.addChar('C');
	}

	if (checkPress(GLFW_KEY_D, window))
	{
		lines.addChar('D');
	}

	if (checkPress(GLFW_KEY_E, window))
	{
		lines.addChar('E');
	}

	if (checkPress(GLFW_KEY_F, window))
	{
		lines.addChar('F');
	}

	if (checkPress(GLFW_KEY_G, window))
	{
		lines.addChar('G');
	}

	if (checkPress(GLFW_KEY_H, window))
	{
		lines.addChar('H');
	}

	if (checkPress(GLFW_KEY_I, window))
	{
		lines.addChar('I');
	}

	if (checkPress(GLFW_KEY_J, window))
	{
		lines.addChar('J');
	}

	if (checkPress(GLFW_KEY_K, window))
	{
		lines.addChar('K');
	}

	if (checkPress(GLFW_KEY_L, window))
	{
		lines.addChar('L');
	}

	if (checkPress(GLFW_KEY_M, window))
	{
		lines.addChar('M');
	}

	if (checkPress(GLFW_KEY_N, window))
	{
		lines.addChar('N');
	}

	if (checkPress(GLFW_KEY_O, window))
	{
		lines.addChar('O');
	}

	if (checkPress(GLFW_KEY_P, window))
	{
		lines.addChar('P');
	}

	if (checkPress(GLFW_KEY_Q, window))
	{
		lines.addChar('Q');
	}

	if (checkPress(GLFW_KEY_R, window))
	{
		lines.addChar('R');
	}

	if (checkPress(GLFW_KEY_S, window))
	{
		lines.addChar('S');
	}

	if (checkPress(GLFW_KEY_T, window))
	{
		lines.addChar('T');
	}

	if (checkPress(GLFW_KEY_U, window))
	{
		lines.addChar('U');
	}

	if (checkPress(GLFW_KEY_V, window))
	{
		lines.addChar('V');
	}

	if (checkPress(GLFW_KEY_W, window))
	{
		lines.addChar('W');
	}

	if (checkPress(GLFW_KEY_X, window))
	{
		lines.addChar('X');
	}

	if (checkPress(GLFW_KEY_Y, window))
	{
		lines.addChar('Y');
	}

	if (checkPress(GLFW_KEY_Z, window))
	{
		lines.addChar('Z');
	}

	if (checkPress(GLFW_KEY_SPACE, window))
	{
		lines.addChar(' ');
	}

	if (checkPress(GLFW_KEY_EQUAL, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('+') : lines.addChar('='));
	}

	if (checkPress(GLFW_KEY_MINUS, window))
	{
		lines.addChar('-');
	}

	if (checkPress(GLFW_KEY_SLASH, window))
	{
		lines.addChar('/');
	}

	if (checkPress(GLFW_KEY_PERIOD, window))
	{
		lines.addChar('.');
	}

	if (checkPress(GLFW_KEY_COMMA, window))
	{
		lines.addChar(',');
	}

	if (checkPress(GLFW_KEY_ENTER, window))
	{
		return ENTER;
		//lines.addLine(line(origin));
		//entered = lines.convertCurrentLine();
		//solution answer = solve(entered, previous, user_settings);
	}

	if (checkPress(GLFW_KEY_UP, window))
	{
		display_context.scrollTextColor(1);
	}

	if (checkPress(GLFW_KEY_DOWN, window))
	{
		display_context.scrollTextColor(-1);
	}

	if (checkPress(GLFW_KEY_LEFT, window))
	{
		display_context.scrollBackgroundColor(1);
	}

	if (checkPress(GLFW_KEY_RIGHT, window))
	{
		display_context.scrollBackgroundColor(-1);
	}

	return NULL_RETURN;
}