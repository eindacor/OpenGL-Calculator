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
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('%') : lines.addChar('5'));
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
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('A') : lines.addChar('a'));
	}

	if (checkPress(GLFW_KEY_B, window))
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
			return BASE;
		
		else
		{
			(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
				glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('B') : lines.addChar('b'));
		}
	}

	if (checkPress(GLFW_KEY_C, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('C') : lines.addChar('c'));
	}

	if (checkPress(GLFW_KEY_D, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('D') : lines.addChar('d'));
	}

	if (checkPress(GLFW_KEY_E, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('E') : lines.addChar('e'));
	}

	if (checkPress(GLFW_KEY_F, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('F') : lines.addChar('f'));
	}

	if (checkPress(GLFW_KEY_G, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('G') : lines.addChar('g'));
	}

	if (checkPress(GLFW_KEY_H, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('H') : lines.addChar('h'));
	}

	if (checkPress(GLFW_KEY_I, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('I') : lines.addChar('i'));
	}

	if (checkPress(GLFW_KEY_J, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('J') : lines.addChar('j'));
	}

	if (checkPress(GLFW_KEY_K, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('K') : lines.addChar('k'));
	}

	if (checkPress(GLFW_KEY_L, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('L') : lines.addChar('l'));
	}

	if (checkPress(GLFW_KEY_M, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('M') : lines.addChar('m'));
	}

	if (checkPress(GLFW_KEY_N, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('N') : lines.addChar('n'));
	}

	if (checkPress(GLFW_KEY_O, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('O') : lines.addChar('o'));
	}

	if (checkPress(GLFW_KEY_P, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('P') : lines.addChar('p'));
	}

	if (checkPress(GLFW_KEY_Q, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('Q') : lines.addChar('q'));
	}

	if (checkPress(GLFW_KEY_R, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('R') : lines.addChar('r'));
	}

	if (checkPress(GLFW_KEY_S, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('S') : lines.addChar('s'));
	}

	if (checkPress(GLFW_KEY_T, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('T') : lines.addChar('t'));
	}

	if (checkPress(GLFW_KEY_U, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('U') : lines.addChar('u'));
	}

	if (checkPress(GLFW_KEY_V, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('V') : lines.addChar('v'));
	}

	if (checkPress(GLFW_KEY_W, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('W') : lines.addChar('w'));
	}

	if (checkPress(GLFW_KEY_X, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('X') : lines.addChar('x'));
	}

	if (checkPress(GLFW_KEY_Y, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('Y') : lines.addChar('y'));
	}

	if (checkPress(GLFW_KEY_Z, window))
	{
		(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ? lines.addChar('Z') : lines.addChar('z'));
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