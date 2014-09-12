#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <JEPbignum.h>
#include <iterator>
#include <math.h>
#include <stdlib.h>

#define TEXT_PADDING 2
#define LINE_PADDING 2
#define MARGAINS 3

enum KEYRETURN {NULL_RETURN, ENTER, BASE, OPTIONS};
enum STYPE { FACTORIAL = 0, ITERATION, EXPONENT, MULTIPLY, DIVIDE, ADD, SUBTRACT, ERROR };
enum ITYPE { NONE = 0, NUMBER, SYMBOL, PAREN };

using namespace jep;

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;
using std::string;

#ifdef _DEBUG
#define SHOWNUMBER(x) cout << endl << __FILE__ << " (line " << __LINE__ << ") :\t" << #x << "= " ; x.printNumber(); cout << endl
#define QUERYNUMBER(x) cout << endl << __FILE__ << " (line " << __LINE__ << "), " << #x << ":\n" ; x.query(); cout << endl
#define DECLARE(x) cout << endl << __FILE__ << " (line " << __LINE__ << ") :\t" << #x << "= " << x
#define SHOW(x) cout << endl << __FILE__ << " (line " << __LINE__ << ") :\t" << #x << "= " << x
#define SHOWLINE cout << endl << endl << __FILE__ << ": " << __LINE__ << endl
#else
#define SHOWNUMBER(x)
#define QUERYNUMBER(x)
#define DECLARE(x)
#define SHOW(x)
#define SHOWLINE
#endif

using std::cout;
using std::endl;
using std::string;
using std::list;
using std::vector;
using glm::mat4;
using glm::vec4;
using glm::vec3;
using glm::vec4;
using glm::vec2;
using jep::bignum;

class display_handler;
class character;
class pixel;
class line;
class line_group;
class solution;
class settings;
class calcItem;
class numberItem;
class symbolItem;
class parenItem;
class calc_ptr;
class numberPrimer;

#include "display.h"
#include "converter.h"
#include "characters.h"
#include "keypress.h"

/*
CHARACTER PIXEL LOCATION MATRIX:

18	19	20
15	16	17
12	13	14
9	10	11
6	7	8
3	4	5
0	1	2

*/

#endif