#include "characters.h"

character::character(vec2 origin, char c)
{
	//establish base point of the character
	base_point = origin;
	character_width = 0;

	switch (c)
	{
	case ' ': character_width = 3; break;

	case '0':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(21);
		addPixel(23);
		addPixel(25);
		addPixel(27);
		addPixel(28);
		addPixel(30);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(41);
		addPixel(42);
		break;

	case '1':
		addPixel(5);
		addPixel(6);
		addPixel(7);
		addPixel(11);
		addPixel(16);
		addPixel(21);
		addPixel(26);
		addPixel(31);
		addPixel(35);
		addPixel(36);
		addPixel(41);
		break;

	case '2':
		addPixel(5);
		addPixel(6);
		addPixel(7);
		addPixel(8);
		addPixel(10);
		addPixel(15);
		addPixel(21);
		addPixel(27);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(41);
		addPixel(42);
		break;

	case '3':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(18);
		addPixel(23);
		addPixel(26);
		addPixel(27);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(41);
		addPixel(42);
		break;

	case '4':
		addPixel(8);
		addPixel(13);
		addPixel(18);
		addPixel(23);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(28);
		addPixel(30);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(40);
		addPixel(43);
		break;

	case '5':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(18);
		addPixel(23);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(30);
		addPixel(35);
		addPixel(40);
		addPixel(41);
		addPixel(42);
		addPixel(43);
		break;

	case '6':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(30);
		addPixel(35);
		addPixel(38);
		addPixel(41);
		addPixel(42);
		break;

	case '7':
		addPixel(6);
		addPixel(11);
		addPixel(16);
		addPixel(22);
		addPixel(27);
		addPixel(33);
		addPixel(38);
		addPixel(40);
		addPixel(41);
		addPixel(42);
		addPixel(43);
		break;

	case '8':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(26);
		addPixel(27);
		addPixel(30);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(41);
		addPixel(42);
		break;

	case '9':
		addPixel(8);
		addPixel(13);
		addPixel(18);
		addPixel(23);
		addPixel(26);
		addPixel(27);
		addPixel(28);
		addPixel(30);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(41);
		addPixel(42);
		break;

	case '+':
		addPixel(17);
		addPixel(22);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(28);
		addPixel(29);
		addPixel(32);
		addPixel(37);
		break;

	case '-':
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(28);
		addPixel(29);
		break;

	case '*':
		addPixel(15);
		addPixel(19);
		addPixel(21);
		addPixel(23);
		addPixel(27);
		addPixel(31);
		addPixel(33);
		addPixel(35);
		addPixel(39);
		break;

	case '/':
		addPixel(5);
		addPixel(10);
		addPixel(16);
		addPixel(21);
		addPixel(27);
		addPixel(32);
		addPixel(38);
		addPixel(43);
		break;

	case '(':
		addPixel(2);
		addPixel(6);
		addPixel(11);
		addPixel(15);
		addPixel(20);
		addPixel(25);
		addPixel(30);
		addPixel(36);
		addPixel(41);
		addPixel(47);
		break;

	case ')':
		addPixel(0);
		addPixel(6);
		addPixel(11);
		addPixel(17);
		addPixel(22);
		addPixel(27);
		addPixel(32);
		addPixel(36);
		addPixel(41);
		addPixel(45);
		break;

	case '!':
		addPixel(5);
		addPixel(15);
		addPixel(20);
		addPixel(25);
		addPixel(30);
		addPixel(35);
		addPixel(40);
		break;

	case '^':
		addPixel(30);
		addPixel(36);
		addPixel(42);
		addPixel(38);
		addPixel(34);
		break;

	case '=':
		addPixel(20);
		addPixel(21);
		addPixel(22);
		addPixel(23);
		addPixel(24);
		addPixel(30);
		addPixel(31);
		addPixel(32);
		addPixel(33);
		addPixel(34);
		break;

	case '.':
		addPixel(5);
		break;

	case ',':
		addPixel(0);
		addPixel(5);
		break;

	case '%':
		addPixel(15);
		addPixel(19);
		addPixel(21);
		addPixel(27);
		addPixel(33);
		addPixel(35);
		addPixel(39);
		break;

	case 'A':
		addPixel(5);
		addPixel(9);
		addPixel(10);
		addPixel(14);
		addPixel(15);
		addPixel(19);
		addPixel(20);
		addPixel(21);
		addPixel(22);
		addPixel(23);
		addPixel(24);
		addPixel(26);
		addPixel(28);
		addPixel(31);
		addPixel(33);
		addPixel(37);
		addPixel(42);
		break;

	case 'a':
		addPixel(6);
		addPixel(7);
		addPixel(8);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(21);
		addPixel(22);
		addPixel(23);
		addPixel(28);
		addPixel(31);
		addPixel(32);
		break;

	case 'B':
		addPixel(5);
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(30);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(40);
		addPixel(41);
		addPixel(42);
		break;

	case 'b':
		addPixel(5);
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(30);
		addPixel(35);
		addPixel(40);
		break;

	case 'C':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(20);
		addPixel(25);
		addPixel(30);
		addPixel(35);
		addPixel(38);
		addPixel(41);
		addPixel(42);
		break;

	case 'c':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(20);
		addPixel(23);
		addPixel(26);
		addPixel(27);
		break;

	case 'D':
		addPixel(5);
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(25);
		addPixel(28);
		addPixel(30);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(40);
		addPixel(41);
		addPixel(42);
		break;

	case 'd':
		addPixel(6);
		addPixel(7);
		addPixel(8);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(26);
		addPixel(27);
		addPixel(28);
		addPixel(33);
		addPixel(38);
		addPixel(43);
		break;

	case 'E':
		addPixel(5);
		addPixel(6);
		addPixel(7);
		addPixel(8);
		addPixel(10);
		addPixel(15);
		addPixel(20);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(30);
		addPixel(35);
		addPixel(40);
		addPixel(41);
		addPixel(42);
		addPixel(43);
		break;

	case 'e':
		addPixel(6);
		addPixel(7);
		addPixel(8);
		addPixel(10);
		addPixel(15);
		addPixel(16);
		addPixel(17);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(26);
		addPixel(27);
		break;

	case 'F':
		addPixel(5);
		addPixel(10);
		addPixel(15);
		addPixel(20);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(30);
		addPixel(35);
		addPixel(40);
		addPixel(41);
		addPixel(42);
		addPixel(43);
		break;

	case 'f':
		addPixel(6);
		addPixel(11);
		addPixel(16);
		addPixel(21);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(31);
		addPixel(36);
		addPixel(38);
		addPixel(42);
		break;

	case 'G':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(22);
		addPixel(23);
		addPixel(25);
		addPixel(30);
		addPixel(35);
		addPixel(38);
		addPixel(41);
		addPixel(42);
		break;

	case 'g':
		addPixel(1);
		addPixel(2);
		addPixel(8);
		addPixel(11);
		addPixel(12);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(25);
		addPixel(28);
		addPixel(31);
		addPixel(32);
		break;

	case 'H':
		addPixel(5);
		addPixel(8);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(28);
		addPixel(30);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(40);
		addPixel(43);
		break;

	case 'h':
		addPixel(5);
		addPixel(8);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(30);
		addPixel(35);
		addPixel(40);
		break;

	case 'I':
		addPixel(5);
		addPixel(6);
		addPixel(7);
		addPixel(11);
		addPixel(16);
		addPixel(21);
		addPixel(26);
		addPixel(31);
		addPixel(36);
		addPixel(40);
		addPixel(41);
		addPixel(42);
		break;

	case 'i':
		addPixel(5);
		addPixel(10);
		addPixel(15);
		addPixel(20);
		addPixel(25);
		addPixel(35);
		break;

	case 'J':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(18);
		addPixel(23);
		addPixel(28);
		addPixel(33);
		addPixel(38);
		addPixel(43);
		break;

	case 'j':
		addPixel(1);
		addPixel(2);
		addPixel(5);
		addPixel(8);
		addPixel(10);
		addPixel(13);
		addPixel(18);
		addPixel(23);
		addPixel(28);
		addPixel(38);
		break;

	case 'K':
		addPixel(5);
		addPixel(8);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(22);
		addPixel(25);
		addPixel(26);
		addPixel(30);
		addPixel(32);
		addPixel(35);
		addPixel(38);
		addPixel(40);
		addPixel(43);
		break;

	case 'k':
		addPixel(5);
		addPixel(8);
		addPixel(10);
		addPixel(12);
		addPixel(15);
		addPixel(16);
		addPixel(20);
		addPixel(22);
		addPixel(25);
		addPixel(28);
		addPixel(30);
		addPixel(35);
		addPixel(40);
		break;

	case 'L':
		addPixel(5);
		addPixel(6);
		addPixel(7);
		addPixel(8);
		addPixel(10);
		addPixel(15);
		addPixel(20);
		addPixel(25);
		addPixel(30);
		addPixel(35);
		addPixel(40);
		break;

	case 'l':
		addPixel(6);
		addPixel(11);
		addPixel(16);
		addPixel(21);
		addPixel(26);
		addPixel(31);
		addPixel(36);
		addPixel(40);
		addPixel(41);
		break;

	case 'M':
		addPixel(5);
		addPixel(9);
		addPixel(10);
		addPixel(14);
		addPixel(15);
		addPixel(19);
		addPixel(20);
		addPixel(24);
		addPixel(25);
		addPixel(29);
		addPixel(30);
		addPixel(32);
		addPixel(34);
		addPixel(35);
		addPixel(36);
		addPixel(38);
		addPixel(39);
		addPixel(40);
		addPixel(44);
		break;

	case 'm':
		addPixel(5);
		addPixel(7);
		addPixel(9);
		addPixel(10);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(19);
		addPixel(20);
		addPixel(22);
		addPixel(24);
		addPixel(25);
		addPixel(26);
		addPixel(28);
		break;

	case 'N':
		addPixel(5);
		addPixel(9);
		addPixel(10);
		addPixel(14);
		addPixel(15);
		addPixel(19);
		addPixel(20);
		addPixel(24);
		addPixel(25);
		addPixel(28);
		addPixel(29);
		addPixel(30);
		addPixel(32);
		addPixel(34);
		addPixel(35);
		addPixel(36);
		addPixel(39);
		addPixel(40);
		addPixel(44);
		break;

	case 'n':
		addPixel(5);
		addPixel(8);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		break;

	case 'O':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(25);
		addPixel(28);
		addPixel(30);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(41);
		addPixel(42);
		break;

	case 'o':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(26);
		addPixel(27);
		break;

	case 'P':
		addPixel(5);
		addPixel(10);
		addPixel(15);
		addPixel(20);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(30);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(40);
		addPixel(41);
		addPixel(42);
		break;

	case 'p':
		addPixel(0);
		addPixel(5);
		addPixel(10);
		addPixel(11);
		addPixel(12);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(26);
		addPixel(27);
		break;

	case 'Q':
		addPixel(2);
		addPixel(3);
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(25);
		addPixel(28);
		addPixel(30);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(41);
		addPixel(42);
		break;

	case 'q':
		addPixel(3);
		addPixel(4);
		addPixel(8);
		addPixel(11);
		addPixel(12);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(26);
		addPixel(27);
		break;

	case 'R':
		addPixel(5);
		addPixel(8);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(30);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(40);
		addPixel(41);
		addPixel(42);
		break;

	case 'r':
		addPixel(5);
		addPixel(10);
		addPixel(15);
		addPixel(20);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(23);
		break;

	case 'S':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(18);
		addPixel(22);
		addPixel(26);
		addPixel(30);
		addPixel(35);
		addPixel(38);
		addPixel(41);
		addPixel(42);
		break;

	case 's':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(17);
		addPixel(21);
		addPixel(25);
		addPixel(28);
		addPixel(31);
		addPixel(32);
		break;

	case 'T':
		addPixel(7);
		addPixel(12);
		addPixel(17);
		addPixel(22);
		addPixel(27);
		addPixel(32);
		addPixel(37);
		addPixel(40);
		addPixel(41);
		addPixel(42);
		addPixel(43);
		addPixel(44);
		break;

	case 't':
		addPixel(6);
		addPixel(11);
		addPixel(16);
		addPixel(21);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		addPixel(31);
		break;

	case 'U':
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(25);
		addPixel(28);
		addPixel(30);
		addPixel(33);
		addPixel(35);
		addPixel(38);
		addPixel(40);
		addPixel(43);
		break;

	case 'u':
		addPixel(6);
		addPixel(7);
		addPixel(8);
		addPixel(10);
		addPixel(13);
		addPixel(15);
		addPixel(18);
		addPixel(20);
		addPixel(23);
		addPixel(25);
		addPixel(28);
		break;

	case 'V':
		addPixel(7);
		addPixel(12);
		addPixel(16);
		addPixel(18);
		addPixel(21);
		addPixel(23);
		addPixel(25);
		addPixel(29);
		addPixel(30);
		addPixel(34);
		addPixel(35);
		addPixel(39);
		addPixel(40);
		addPixel(44);
		break;

	case 'v':
		addPixel(7);
		addPixel(11);
		addPixel(13);
		addPixel(16);
		addPixel(18);
		addPixel(20);
		addPixel(24);
		addPixel(25);
		addPixel(29);
		break;

	case 'W':
		addPixel(5);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(13);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(19);
		addPixel(20);
		addPixel(24);
		addPixel(25);
		addPixel(29);
		addPixel(30);
		addPixel(34);
		addPixel(35);
		addPixel(39);
		addPixel(40);
		addPixel(44);
		break;

	case 'w':
		addPixel(6);
		addPixel(8);
		addPixel(10);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(19);
		addPixel(20);
		addPixel(22);
		addPixel(24);
		addPixel(25);
		addPixel(27);
		addPixel(29);
		break;

	case 'X':
		addPixel(5);
		addPixel(9);
		addPixel(10);
		addPixel(14);
		addPixel(16);
		addPixel(18);
		addPixel(22);
		addPixel(27);
		addPixel(31);
		addPixel(33);
		addPixel(35);
		addPixel(39);
		addPixel(40);
		addPixel(44);
		break;

	case 'x':
		addPixel(5);
		addPixel(7);
		addPixel(10);
		addPixel(12);
		addPixel(16);
		addPixel(20);
		addPixel(22);
		addPixel(25);
		addPixel(27);
		break;

	case 'Y':
		addPixel(7);
		addPixel(12);
		addPixel(17);
		addPixel(22);
		addPixel(27);
		addPixel(31);
		addPixel(33);
		addPixel(35);
		addPixel(39);
		addPixel(40);
		addPixel(44);
		break;

	case 'y':
		addPixel(0);
		addPixel(6);
		addPixel(10);
		addPixel(12);
		addPixel(15);
		addPixel(17);
		addPixel(20);
		addPixel(22);
		break;

	case 'Z':
		addPixel(5);
		addPixel(6);
		addPixel(7);
		addPixel(8);
		addPixel(10);
		addPixel(16);
		addPixel(21);
		addPixel(27);
		addPixel(32);
		addPixel(38);
		addPixel(40);
		addPixel(41);
		addPixel(42);
		addPixel(43);
		break;

	case 'z':
		addPixel(5);
		addPixel(6);
		addPixel(7);
		addPixel(10);
		addPixel(16);
		addPixel(22);
		addPixel(25);
		addPixel(26);
		addPixel(27);
		break;

	default: break;
	}
}