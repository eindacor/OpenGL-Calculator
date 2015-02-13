#include "converter.h"

void settings::setRound(int n)
{
	if (n>ONES_PLACE)
	{
		cout << "Cannot satisfy request" << endl;
	}

	else round = n;
}

symbolItem::symbolItem(char c) : calcItem(SYMBOL)
{
	stored = c;

	switch (c)
	{
	case '+': symbolType = ADD;
		break;

	case '-': symbolType = SUBTRACT;
		break;

	case '*': symbolType = MULTIPLY;
		break;

	case 'x': symbolType = MULTIPLY;
		break;

	case '/': symbolType = DIVIDE;
		break;

	case '^': symbolType = EXPONENT;
		break;

	case '!': symbolType = FACTORIAL;
		break;

	case 'c': symbolType = ITERATION;
		break;

	default: symbolType = ERROR;
		break;
	}
}

parenItem::parenItem(char c) : calcItem(PAREN)
{
	stored = c;

	switch (c)
	{
	case '(': open = true;
		break;

	case ')': open = false;
		break;

	default: cout << "\nAn error has occured: " << __FILE__ << ", " << __LINE__;
		break;

	}

	parenID = 0;
}

numberPrimer::numberPrimer()
{
	decimalCount = 0;
	commaNumbers = 0;
	numbers = 0;

	decimal = false;
	comma = false;
	done = false;
	printExact = false;
	printStats = false;

	manualSet = false;
}

void numberPrimer::reset()
{
	decimalCount = 0;
	commaNumbers = 0;
	numbers = 0;

	decimal = false;
	comma = false;
	done = false;
	printExact = false;
	printStats = false;

	manualSet = false;
}

calcItem* calc_ptr::duplicate(calc_ptr &original)
{
	calcItem* temp = NULL;


	switch (original->getItemType())
	{
	case SYMBOL:
	{
		char originalChar = original->getStoredChar();
		temp = new symbolItem(originalChar);
		return temp;
	}

	case NUMBER:
	{
		bignum originalNumber = original->getStoredNumber();
		temp = new numberItem(originalNumber);
		return temp;
	}

	case PAREN:
	{
		char originalChar = original->getStoredChar();
		temp = new parenItem(originalChar);
		return temp;
	}

	default:
	{
		cout << endl << __FILE__ << " (line " << __LINE__ << "): An error has occurred.";
		break;
	}
	}

	return temp;
}

calc_ptr::calc_ptr(const calc_ptr &original)
{
	if (original.readStored() == NULL)
		stored = NULL;

	else
	{

		switch (original->getItemType())
		{
		case SYMBOL:
		{
			char originalChar = original->getStoredChar();
			stored = new symbolItem(originalChar);
			break;
		}

		case NUMBER:
		{
			bignum originalNumber = original->getStoredNumber();
			stored = new numberItem(originalNumber);
			break;
		}

		case PAREN:
		{
			char originalChar = original->getStoredChar();
			stored = new parenItem(originalChar);
			break;
		}

		default:
		{
			cout << endl << __FILE__ << " (line " << __LINE__ << "): An error has occurred.";
			stored = NULL;
			break;
		}
		}
	}
}


calc_ptr::calc_ptr(calcItem* original)
{
	if (original == NULL)
		stored = NULL;

	else
	{

		switch (original->getItemType())
		{
		case SYMBOL:
		{
			char originalChar = original->getStoredChar();
			stored = new symbolItem(originalChar);
			break;
		}

		case NUMBER:
		{
			bignum originalNumber = original->getStoredNumber();
			stored = new numberItem(originalNumber);
			break;
		}

		case PAREN:
		{
			char originalChar = original->getStoredChar();
			stored = new parenItem(originalChar);
			break;
		}

		default:
		{
			cout << endl << __FILE__ << " (line " << __LINE__ << "): An error has occurred.";
			stored = NULL;
			break;
		}
		}
	}
}

//verifies the symbol passed is valid
STYPE checkSymbol(char &c)
{
	switch (c)
	{
	case '+': return ADD;

	case '-': return SUBTRACT;

	case '*': return MULTIPLY;

	case '/': return DIVIDE;

	case '^': return EXPONENT;

	case '!': return FACTORIAL;

	case 'c': return ITERATION;

	default: return ERROR;
	}
}

//returns the number of the passed character
int checkNumber(char const &c)
{
	int i = c - '0';

	if (i >= 0 && i <= 9)
	{
		return i;
	}

	else
	{
		i = 10 + (c - 'A');
		return i;
	}
}

//verifies if the character passed is a space
bool isSpace(char const &c)
{
	return (c == ' ');
}

//verifies the character passed is a valid number within the current base
bool isNumber(char const &c, settings &user)
{
	return (checkNumber(c) >= 0 && checkNumber(c) <= (user.getBase() - 1));
}

//verifies the character passed is a valid symbol
bool isSymbol(char &c)
{
	return (checkSymbol(c) != ERROR);
}

//creates a bignum from a vector of integers
bignum numberFromVector(vector<int> &vec, int dec, settings &user)
{
	bignum temp;
	temp.setBase(user.getBase());

	for (int i = 0; i<vec.size(); i++)
	{
		int numberToUse = vec.at(vec.size() - i - 1);
		int locationToSet = ONES_PLACE + i;
		temp.setDigit(locationToSet, numberToUse);
	}

	for (int i = 0; i < dec; i++)
		temp /= 10;

	return temp;
}

//checks if a keyword has been entered
bool checkWord(string c, int start, string compare)
{
	int sizeCheck = start + compare.size();
	if (sizeCheck > c.size())
	{
		RETURN_FALSE;
	}

	for (int i = 0; i<compare.size(); i++)
	{
		if (c[start + i] != compare[i])
		{
			RETURN_FALSE;
		}
	}

	RETURN_TRUE;
}

//prints all elements within a list of calc_ptr's
void printListBasic(list<calc_ptr> &itemList, int line, string s)
{
	if (itemList.size() == 0)
	{
		cout << endl << s << " from line " << line << " is empty";
	}

	else
	{
		cout << endl << s << " from line " << line << " has " << itemList.size() << " item(s): ";

		int itemCounter = 0;
		for (list<calc_ptr>::iterator i = itemList.begin(); i != itemList.end(); ++i)
		{
			bignum temp = (*i)->getStoredNumber();

			switch ((*i)->getItemType())
			{
			case NUMBER:
				cout << " ";
				cout << temp.getNumberString(true, temp.getDecimalCount(), 0);
				break;

			case SYMBOL:
				cout << " " << (*i)->getStoredChar();
				break;

			case PAREN:
				cout << " " << (*i)->getStoredChar();
				break;

			default:
				cout << "\nItem " << itemCounter << " has not been defined properly: " << (*i)->getStoredChar();
				break;
			}

			itemCounter++;
		}
	}
	cout << endl;
}

//adds a bignum item to the list and returns an iterator pointing to it
list<calc_ptr>::iterator addNumberToList(list <calc_ptr> &itemList, list <calc_ptr>::iterator i, bignum bn)
{
	calcItem* temp = new numberItem(bn);
	calc_ptr toAdd(temp);

	itemList.insert(i, toAdd);

	--i;

	delete temp;
	temp = NULL;

	return i;
}

//adds a symbol/paren item to the list and returns an iterator pointing to it
list<calc_ptr>::iterator addCharToList(list <calc_ptr> &itemList, list <calc_ptr>::iterator i, char c)
{
	calcItem* temp = NULL;

	if (c == '(' || c == ')')
		temp = new parenItem(c);


	else temp = new symbolItem(c);

	calc_ptr toAdd(temp);

	itemList.insert(i, toAdd);

	--i;

	delete temp;
	temp = NULL;

	return i;
}

//determines validity of the list of elements
bool checkValid(list<calc_ptr> &itemList)
{
	if (itemList.size() == 0)
	{
		RETURN_FALSE;
	}

	//FAIL CONDITIONS IF THE LIST HAS ONLY ONE ELEMENT
	if (itemList.size() == 1)
	{
		list<calc_ptr>::iterator i = itemList.begin();

		if ((*i)->getItemType() == NUMBER)
		{
			RETURN_TRUE;
		}

		else RETURN_FALSE;
	}

	int oParenCount = 0;
	int cParenCount = 0;

	for (list<calc_ptr>::iterator i = itemList.begin(); i != itemList.end(); ++i)
	{
		if (itemList.size()>2 && i != itemList.begin() && i != std::next(itemList.begin(), 1))
		{
			list<calc_ptr>::iterator i3 = i;
			list<calc_ptr>::iterator i2 = std::prev(i, 1);
			list<calc_ptr>::iterator i1 = std::prev(i, 2);

			//  3 symbols in a row
			if ((*i1)->getItemType() == SYMBOL && (*i2)->getItemType() == SYMBOL && (*i3)->getItemType() == NUMBER && (*i3)->getStoredNumber().isNegative() == true)
			{
				RETURN_FALSE;
			}

			//  -- followed by a negative number   
			if ((*i1)->getItemType() == SYMBOL && (*i2)->getItemType() == SYMBOL && (*i3)->getItemType() == SYMBOL)
			{
				RETURN_FALSE;
			}
		}

		//FAIL CONDITIONS FOR FIRST ITEM:
		if (i == itemList.begin())
		{
			list<calc_ptr>::iterator after = std::next(i, 1);

			switch ((*i)->getItemType())
			{
			case PAREN:
				if ((*i)->getOpen())
				{
					//  ()
					if ((*after)->getItemType() == PAREN && (*after)->getOpen() == false)
					{
						RETURN_FALSE;
					}

					//  (*  
					if ((*after)->getItemType() == SYMBOL && (*after)->getSymbolType() != SUBTRACT)
					{
						RETURN_FALSE;
					}

					oParenCount++;
					break;
				}

				else
				{
					//  ) as first item
					RETURN_FALSE;
				}

				break;

			case SYMBOL: RETURN_FALSE;

			case NUMBER:
				//  34 52
				if ((*after)->getItemType() == NUMBER)
				{
					RETURN_FALSE;
				}

				//  -4!
				if ((*i)->getStoredNumber().isNegative() == true && (*after)->getItemType() == SYMBOL && (*after)->getSymbolType() == FACTORIAL)
				{
					RETURN_FALSE;
				}

				//  .4!
				if ((*i)->getStoredNumber().getDecimalCount()>0 && (*after)->getItemType() == SYMBOL && (*after)->getSymbolType() == FACTORIAL)
				{
					RETURN_FALSE;
				}

				break;

			default: RETURN_FALSE;
			}
		}

		//FAIL CONDITIONS FOR LAST ITEM
		list<calc_ptr>::iterator lastItem = std::prev(itemList.end(), 1);
		if (i == lastItem)
		{
			switch ((*i)->getItemType())
			{
			case PAREN:
				//  open paren as last item
				if ((*i)->getOpen())
				{
					RETURN_FALSE;
				}

				else
				{
					cParenCount++;
					break;
				}

				break;

			case SYMBOL:
				//  symbol other than ! as last item
				if ((*i)->getSymbolType() != FACTORIAL)
				{
					RETURN_FALSE;
				}

				break;

			case NUMBER: break;

			default: RETURN_FALSE;
			}
		}

		//FAIL CONDITIONS FOR MIDDLE ITEMS
		if (i != itemList.begin() && i != lastItem)
		{
			list<calc_ptr>::iterator after = std::next(i, 1);

			switch ((*i)->getItemType())
			{
			case PAREN:
				if ((*i)->getOpen())
				{
					//  ()
					if ((*after)->getItemType() == PAREN && (*after)->getOpen() == false)
					{
						RETURN_FALSE;
					}

					//  (*
					if ((*after)->getItemType() == SYMBOL && (*after)->getSymbolType() != SUBTRACT)
					{
						RETURN_FALSE;
					}

					oParenCount++;
				}

				else cParenCount++;

				break;

			case SYMBOL:
				//  !!
				if ((*after)->getItemType() == SYMBOL && (*after)->getSymbolType() == FACTORIAL && (*i)->getSymbolType() == FACTORIAL)
				{
					RETURN_FALSE;
				}

				//  *+
				if ((*after)->getItemType() == SYMBOL && (*after)->getSymbolType() != SUBTRACT && (*i)->getSymbolType() != FACTORIAL)
				{
					RETURN_FALSE;
				}

				//  ^.7
				if ((*i)->getSymbolType() == EXPONENT && (*after)->getItemType() == NUMBER && (*after)->getStoredNumber().getDecimalCount()>0)
				{
					RETURN_FALSE;
				}

				//  +)
				if ((*i)->getSymbolType() != FACTORIAL && (*after)->getItemType() == PAREN && (*after)->getOpen() == false)
				{
					RETURN_FALSE;
				}

				break;

			case NUMBER:
				//  34 51
				if ((*after)->getItemType() == NUMBER)
				{
					RETURN_FALSE;
				}

				// -4!
				if ((*i)->getStoredNumber().isNegative() == true && (*after)->getItemType() == SYMBOL && (*after)->getSymbolType() == FACTORIAL)
				{
					RETURN_FALSE;
				}

				//  .4!
				if ((*i)->getStoredNumber().getDecimalCount()>0 && (*after)->getItemType() == SYMBOL && (*after)->getSymbolType() == FACTORIAL)
				{
					RETURN_FALSE;
				}

				break;

			default: RETURN_FALSE;
			}
		}

		//more closed parentheses than open
		if (cParenCount>oParenCount)
		{
			RETURN_FALSE;
		}
	}

	//inequal paren counts
	if (oParenCount != cParenCount)
	{
		RETURN_FALSE;
	}

	else RETURN_TRUE;
}

bool swapItems(list<calc_ptr> &itemList)
{
	//PRINTLIST(itemList);

	if (itemList.size()<2)
	{
		if (checkValid(itemList) == false)
		{
			RETURN_FALSE;
		}

		else RETURN_TRUE;
	}

	list<calc_ptr>::iterator i = itemList.begin();

	do
	{
		//PRINTLIST(itemList);

		if (checkValid(itemList) == false)
		{
			RETURN_FALSE;
		}

		//creates iterator for second element
		list <calc_ptr>::iterator second = std::next(itemList.begin(), 1);

		//checks groups of 3 elements, i1, i2, and i3
		if (itemList.size()>2 && i != (itemList.begin()) && i != second)
		{
			list<calc_ptr>::iterator i3 = i;
			list<calc_ptr>::iterator i2 = std::prev(i, 1);
			list<calc_ptr>::iterator i1 = std::prev(i, 2);

			//if the problem has 2 symbols followed by a number, checkvalid confirms the second symbol is a negative, which means the number is negative
			if ((*i1)->getItemType() == SYMBOL && (*i2)->getItemType() == SYMBOL && (*i3)->getItemType() == NUMBER && (*i1)->getSymbolType() != FACTORIAL)
			{
				itemList.erase(i2);
				bignum temp = (*i3)->getStoredNumber();
				temp.setNegative();
				addNumberToList(itemList, i3, temp);
				itemList.erase(i3);
				i = itemList.begin();
				continue;
			}

			//IF A PROBLEM SAYS "(-N", CONVERT THE N TO NEGATIVE AND ELIMINATE THE SYMBOL
			if ((*i1)->getItemType() == PAREN && (*i1)->getOpen() == true && (*i2)->getItemType() == SYMBOL && (*i3)->getItemType() == NUMBER)
			{
				itemList.erase(i2);
				bignum temp = (*i3)->getStoredNumber();
				temp.setNegative();
				addNumberToList(itemList, i3, temp);
				itemList.erase(i3);
				i = itemList.begin();
				continue;
			}
		}

		//first item
		if (i == itemList.begin())
		{
			list<calc_ptr>::iterator after = std::next(i, 1);

			switch ((*i)->getItemType())
			{
				//if the first item is a number and the next item is an open parenthesis
			case NUMBER:
				// "N(" becomes "N*("
				if ((*after)->getItemType() == PAREN && (*after)->getOpen() == true)
				{
					addCharToList(itemList, after, '*');
					i = itemList.begin();
					continue;
				}
				break;

			default: break;
			}
		}

		list<calc_ptr>::iterator lastItem = std::prev(itemList.end(), 1);

		//items between first and last
		if (i != itemList.begin() && i != lastItem)
		{
			list<calc_ptr>::iterator after = std::next(i, 1);

			switch ((*i)->getItemType())
			{
			case PAREN:
				// ")N" becomes ")*N"
				if ((*i)->getOpen() == false && (*after)->getItemType() == NUMBER)
				{
					addCharToList(itemList, after, '*');
					i = itemList.begin();
					continue;
				}

				// ")(" becomes ")*("
				if ((*i)->getOpen() == false && (*after)->getItemType() == PAREN && (*after)->getOpen() == true)
				{
					addCharToList(itemList, after, '*');
					i = itemList.begin();
					continue;
				}
				break;

			case SYMBOL:
				// "!(" becomes "!*("
				if ((*i)->getSymbolType() == FACTORIAL && (*after)->getItemType() == PAREN && (*after)->getOpen() == true)
				{
					addCharToList(itemList, after, '*');
					i = itemList.begin();
					continue;
				}
				break;

			case NUMBER:
				// "N(" becomes "N*("
				if ((*after)->getItemType() == PAREN && (*after)->getOpen() == true)
				{
					addCharToList(itemList, after, '*');
					i = itemList.begin();
					continue;
				}
				break;

			default: RETURN_FALSE;
			}
		}

		++i;

	} while (i != itemList.end());

	if (checkValid(itemList) == false)
	{
		RETURN_FALSE;
	}

	else
	{
		RETURN_TRUE;
	}
}

list<calc_ptr>::iterator simplifyRange(list <calc_ptr> &itemList, list <calc_ptr>::iterator i1, list <calc_ptr>::iterator i2, bignum bn)
{
	list <calc_ptr>::iterator insertionPoint = addNumberToList(itemList, i2, bn);
	itemList.erase(i1, insertionPoint);
	return insertionPoint;
}

//takes a simple problem (N+N) and converts it into a new number
void simplify_simpleProblem(list<calc_ptr> &itemList)
{
	//PRINTLIST(itemList);
	bignum temp;

	//setting iterators for the 1st, 2nd, and 3rd elements: i1, i2, and i3 respectively
	list<calc_ptr>::iterator i1 = itemList.begin();
	list<calc_ptr>::iterator i2 = std::next(itemList.begin(), 1);
	list<calc_ptr>::iterator i3 = std::next(itemList.begin(), 2);

	//generates a new number based on the symbol between the numbers passed
	switch ((*i2)->getSymbolType())
	{
	case ADD:
		temp = addNumbers((*i1)->getStoredNumber(), (*i3)->getStoredNumber());
		break;

	case SUBTRACT:
		temp = subtractNumbers((*i1)->getStoredNumber(), (*i3)->getStoredNumber());
		break;

	case MULTIPLY:
		temp = multiplyNumbers((*i1)->getStoredNumber(), (*i3)->getStoredNumber());
		break;

	case DIVIDE:
		temp = divideNumbers((*i1)->getStoredNumber(), (*i3)->getStoredNumber());
		break;

	case EXPONENT:
		temp = exponent((*i1)->getStoredNumber(), (*i3)->getStoredNumber());
		break;

	case ITERATION:
		temp = combinations((*i1)->getStoredNumber(), (*i3)->getStoredNumber());
		break;

	default: cout << __FILE__ << ", line " << __LINE__ << ": An error has occurred.";
		break;
	}

	//replaces the range given with the new number
	simplifyRange(itemList, itemList.begin(), itemList.end(), temp);
}

void simplify_factorialProblem(list<calc_ptr> &itemList)
{
	//PRINTLIST(itemList);
	list<calc_ptr>::iterator i1 = itemList.begin();
	list<calc_ptr>::iterator i2 = std::next(itemList.begin(), 1);

	bignum factResult = factorial((*i1)->getStoredNumber());

	itemList.clear();
	addNumberToList(itemList, itemList.end(), factResult);
}

void simplify_pfemdasProblem(list<calc_ptr> &itemList)
{
	//PRINTLIST(itemList);
	bignum temp;

	while (itemList.size()>1)
	{
		bool listChanged = false;

		//runs through each type of problem from pfemdas prioritization, checks for applicable equations, simplifies, them, and replaces them with a value
		for (int typeCheck = 0; typeCheck<7; ++typeCheck)
		{
			//PRINTLIST(itemList);
			STYPE symbolType = (STYPE)typeCheck;

			//runs through all elements, checking for that symbol
			for (list<calc_ptr>::iterator i = itemList.begin(); i != itemList.end(); ++i)
			{
				//if the symbol found matches the current pfemdas symbol
				if ((*i)->getItemType() == SYMBOL && (*i)->getSymbolType() == typeCheck)
				{
					//special case for factorial symbol
					if ((*i)->getSymbolType() == FACTORIAL)
					{
						//create iterator for number before the symbol, simplify
						list<calc_ptr>::iterator before = std::prev(i, 1);
						list<calc_ptr>::iterator after = std::next(i, 1);
						temp = factorial((*before)->getStoredNumber());
						simplifyRange(itemList, before, after, temp);
						listChanged = true;
					}

					else
					{
						//create iterators for the numbers before and after the symbol found
						list<calc_ptr>::iterator before = std::prev(i, 1);
						list<calc_ptr>::iterator after = std::next(i, 1);
						switch (typeCheck)
						{
						case EXPONENT: temp = exponent((*before)->getStoredNumber(), (*after)->getStoredNumber());
							break;

						case ITERATION: temp = combinations((*before)->getStoredNumber(), (*after)->getStoredNumber());
							break;

						case MULTIPLY: temp = multiplyNumbers((*before)->getStoredNumber(), (*after)->getStoredNumber());
							break;

						case DIVIDE: temp = divideNumbers((*before)->getStoredNumber(), (*after)->getStoredNumber());
							break;

						case ADD: temp = addNumbers((*before)->getStoredNumber(), (*after)->getStoredNumber());
							break;

						case SUBTRACT: temp = subtractNumbers((*before)->getStoredNumber(), (*after)->getStoredNumber());
							break;

						default: cout << __FILE__ << ", line " << __LINE__ << ": An error has occurred.";
							break;
						}
						simplifyRange(itemList, before, std::next(after, 1), temp);
						listChanged = true;
					}
				}//if symbol matches target symbol

				if (listChanged == true)
					break;
			}//for loop checking list for target symbol

			if (listChanged == true)
				break;
		}//for loop cycling through the pfemdas order
	}//while loop to simplify until a final number exists
}

bool simplify(list<calc_ptr> &itemList)
{
	if (checkValid(itemList) == false)
	{
		RETURN_FALSE;
	}

	int parenCount = 0;
	int parenHigh = 0;

	//count parentheses
	for (list<calc_ptr>::iterator pCount = itemList.begin(); pCount != itemList.end(); ++pCount)
	{
		if ((*pCount)->getItemType() == PAREN)
		{
			if ((*pCount)->getOpen() == true)
			{
				parenCount++;
				if (parenCount>parenHigh)
					parenHigh = parenCount;

				(*pCount)->setParenID(parenCount);
			}

			else
			{
				(*pCount)->setParenID(parenCount);
				parenCount--;
			}
		}
	}

	//if there are any parentheses in the problem, find elements within the highest parentheses and simplify them
	if (parenHigh>0)
	{
		list<calc_ptr> replace;
		list<calc_ptr>::iterator insertionPoint;
		list<calc_ptr>::iterator rangeToReplace_start;
		list<calc_ptr>::iterator rangeToReplace_end;
		bool add = false;

		list<calc_ptr>::iterator i = itemList.begin();

		do
		{
			if ((*i)->getItemType() == PAREN && (*i)->getParenID() == parenHigh)
			{
				if ((*i)->getOpen() == true)
				{
					rangeToReplace_start = i;
					add = true;
				}

				else
				{
					rangeToReplace_end = std::next(i, 1);
					insertionPoint = std::next(i, 1);
					itemList.erase(rangeToReplace_start, rangeToReplace_end);
					simplify(replace);

					itemList.insert(insertionPoint, replace.begin(), replace.end());
					replace.clear();

					RETURN_TRUE;
				}
			}

			else if (add == true)
			{
				replace.insert(replace.end(), (*i));
			}

			++i;

		} while (i != itemList.end());
	}

	else
	{
		//must be a single number, do nothing
		if (itemList.size() == 1)
		{
			RETURN_TRUE;
		}

		//only 2 items, must be factorial
		if (itemList.size() == 2)
		{
			simplify_factorialProblem(itemList);
			RETURN_TRUE;
		}

		//only 3 items, must be a simple problem
		else if (itemList.size() == 3)
		{
			simplify_simpleProblem(itemList);
			RETURN_TRUE;
		}

		//more than 3 items, must be a problem with multiple elements
		else
		{
			simplify_pfemdasProblem(itemList);
			RETURN_TRUE;
		}
	}
}

bool generateProblem(string &c, list <calc_ptr> &itemList, settings &user, bignum previous)
{
	vector<int> numberVector;

	bignum temp;
	temp.setBase(user.getBase());

	numberPrimer primer;

	int counter = c.size();

	for (int i = 0; i<counter; i++)
	{
		//if "answer" has been entered, add previous number and advance the counter
		if (checkWord(c, i, "ans"))
		{
			if (primer.getNumbers()>0)
			{
				temp = numberFromVector(numberVector, primer.getDecimalCount(), user);
				addNumberToList(itemList, itemList.end(), temp);
				primer.reset();
				numberVector.clear();

				//add * between the number and pi
				addCharToList(itemList, itemList.end(), '*');
			}

			addNumberToList(itemList, itemList.end(), previous);
			numberVector.clear();

			i += 3;
		}

		if (i == counter)
			break;

		//if it isn't a space, number, symbol, end marker, or decimal point, return error
		if (isSpace(c[i]) == false &&
			isNumber(c[i], user) == false &&
			isSymbol(c[i]) == false &&
			c[i] != ',' &&
			c[i] != '(' &&
			c[i] != ')' &&
			c[i] != '.')
		{
			RETURN_FALSE;
		}

		if (c[i] == ',')
		{
			if (primer.getComma() == false)
			{
				if (primer.getDecimal() == true || primer.getNumbers() == 0 || primer.getNumbers() > 3)
				{
					RETURN_FALSE;
				}

				else primer.setComma(true);
			}

			else if (primer.getCommaNumbers() != 3)
			{
				RETURN_FALSE;
			}

			primer.setCommaNumbers(0);
		}

		//if it's a space
		else if (isSpace(c[i]) == true)
		{
			//if it's preceeded by a number, finish the number and add to the problem
			if (isNumber(c[i - 1], user))
			{
				temp = numberFromVector(numberVector, primer.getDecimalCount(), user);
				addNumberToList(itemList, itemList.end(), temp);
				primer.reset();
				numberVector.clear();
			}
		}

		//if it's a number
		else if (isNumber(c[i], user))
		{
			numberVector.push_back(checkNumber(c[i]));
			primer.incrementNumbers();

			if (primer.getComma() == true)
				primer.incrementCommaNumbers();

			if (primer.getDecimal() == true)
				primer.incrementDecimalCount();
		}

		//if it's a symbol
		else if (checkSymbol(c[i]) != ERROR)
		{
			//if the primer has been primed with numbers, add that number to the problem
			if (primer.getNumbers()>0)
			{
				temp = numberFromVector(numberVector, primer.getDecimalCount(), user);
				addNumberToList(itemList, itemList.end(), temp);
				primer.reset();
				numberVector.clear();
			}

			//add the symbol item to the problem 
			addCharToList(itemList, itemList.end(), c[i]);
		}

		//if it's a parenthesis
		else if (c[i] == '(' || c[i] == ')')
		{
			//if the primer has been primed with numbers, add that number to the problem
			if (primer.getNumbers()>0)
			{
				temp = numberFromVector(numberVector, primer.getDecimalCount(), user);
				addNumberToList(itemList, itemList.end(), temp);
				primer.reset();
				numberVector.clear();
			}

			//add the paren item to the problem  
			addCharToList(itemList, itemList.end(), c[i]);
		}

		//if it's a decimal point
		else if (c[i] == '.')
		{
			//if there's already been a decimal point, return error
			if (primer.getDecimal() == true)
			{
				RETURN_FALSE;
			}

			//if there isn't a number after, return error
			else if (isNumber(c[i + 1], user) == false)
			{
				RETURN_FALSE;
			}

			//if the comma segment is incomplete
			else if (primer.getComma() == true && primer.getCommaNumbers() != 3)
			{
				RETURN_FALSE;
			}

			else primer.setDecimal(true);
		}
	}

	//if the primer has been primed with numbers, add that number to the problem
	if (primer.getNumbers()>0)
	{
		temp = numberFromVector(numberVector, primer.getDecimalCount(), user);
		addNumberToList(itemList, itemList.end(), temp);
		primer.reset();
		numberVector.clear();
	}

	RETURN_TRUE;
}

solution solve(string &entered, bignum &previous, settings &user)
{
	list<calc_ptr> itemList;
	bool usePrevious = false;

	bignum temp;

	//populate list
	if (generateProblem(entered, itemList, user, previous) == false)
		RETURN_ERROR;


	//if nothing has been entered, return previous
	if (itemList.size() == 0)
	{
		addNumberToList(itemList, itemList.end(), previous);
		usePrevious = true;
	}

	//if it starts with a symbol
	list<calc_ptr>::iterator start = itemList.begin();
	if ((*start)->getItemType() == SYMBOL)
	{
		//if it's anything other than subtract, add previous
		if ((*start)->getSymbolType() != SUBTRACT)
		{
			addNumberToList(itemList, itemList.begin(), previous);
			usePrevious = true;
		}

		//if its subtract
		else if (itemList.size()>1)
		{
			list<calc_ptr>::iterator after = std::next(start, 1);

			//if the 2nd is a subtract symbol, add previous
			if ((*after)->getItemType() == SYMBOL && (*after)->getSymbolType() == SUBTRACT)
			{
				addNumberToList(itemList, itemList.begin(), previous);
				usePrevious = true;
			}

			//if the 2nd is a number 
			if ((*after)->getItemType() == NUMBER)
			{
				//if the calculator is clear, set the number to negative and remove the symbol
				if (previous == 0)
				{
					bignum firstNumber = (*after)->getStoredNumber();
					firstNumber.setNegative();
					itemList.erase(start);
					itemList.erase(after);
					addNumberToList(itemList, itemList.begin(), firstNumber);
				}

				//if there was a number stored, add it to the problem
				else
				{
					addNumberToList(itemList, itemList.begin(), previous);
					usePrevious = true;
				}
			}
		}
		else RETURN_ERROR;
	}

	//initial swap
	if (swapItems(itemList) == false)
	{
		RETURN_ERROR;
	}

	//simplification loop
	do
	{
		simplify(itemList);

		if (swapItems(itemList) == false)
		{
			RETURN_ERROR;
		}

	} while (itemList.size()>1);


	list<calc_ptr>::iterator solved = itemList.begin();
	temp = (*solved)->getStoredNumber();

	RETURN_OK(temp);
}

/*
void printHelp()
{
	cout << "This calculator accepts problems in the following formats:\n\n";
	cout << "\tAddition\n\t        12345.6789 + 98765.4321\n\n";
	cout << "\tSubtraction\n\t        12345.6789 - 98765.4321\n\n";
	cout << "\tMultiplication\n\t        12345.6789 * 98765.4321\n\n";
	cout << "\tDivision\n\t        12345.6789 / 98765.4321\n\n";
	cout << "\tExponent\n\t        12345.6789 ^ 98765.4321\n\n";
	cout << "\tFactorial\n\t        123!\n\n";
	cout << "- To use the previous value, enter the rest of the calculation like so: \"+ 12345\"\n\n";
	cout << "- To change bases, enter \"base 12\" or \"binary\", \"decimal\", etc.\n\n";
	cout << "- To show/hide statistics, enter \"show stats\" or \"hide stats\".\n\n";
	cout << "- To reset the calculator, enter \"clear\" or \"reset\".\n\n";
	cout << "- To end your session, type \"exit\".\n\n";
	cout << "NOTE: Factorials and base conversions of large decimals can be very time\n";
	cout << "consuming. To exit out of the program mid-calculation, press ctrl+C.\n\n";

	// "01234567890123456789012345678901234567890123456789012345678901234567890123456789"
}
*/

bool changeBase(string c, settings &user)
{
	if (c == "base 2" || c == "base2" || c == "binary")
	{
		user.setBase(2);
		return true;
	}

	if (c == "base 3" || c == "base3" || c == "ternary")
	{
		user.setBase(3);
		return true;
	}

	if (c == "base 4" || c == "base4" || c == "quaternary")
	{
		user.setBase(4);
		return true;
	}

	if (c == "base 5" || c == "base5" || c == "quinary")
	{
		user.setBase(5);
		return true;
	}

	if (c == "base 6" || c == "base6" || c == "senary")
	{
		user.setBase(6);
		return true;
	}

	if (c == "base 7" || c == "base7" || c == "septenary")
	{
		user.setBase(7);
		return true;
	}

	if (c == "base 8" || c == "base8" || c == "octonary")
	{
		user.setBase(8);
		return true;
	}

	if (c == "base 9" || c == "base9" || c == "nonary")
	{
		user.setBase(9);
		return true;
	}

	if (c == "base 10" || c == "base10" || c == "decimal")
	{
		user.setBase(10);
		return true;
	}

	if (c == "base 11" || c == "base11" || c == "undenary")
	{
		user.setBase(11);
		return true;
	}

	if (c == "base 12" || c == "base12" || c == "dozenal" || c == "duodecimal")
	{
		user.setBase(12);
		return true;
	}

	if (c == "base 13" || c == "base13" || c == "tridecimal")
	{
		user.setBase(13);
		return true;
	}

	if (c == "base 14" || c == "base14" || c == "quattuordecimal")
	{
		user.setBase(14);
		return true;
	}

	if (c == "base 15" || c == "base15" || c == "quindecimal")
	{
		user.setBase(15);
		return true;
	}

	if (c == "base 16" || c == "base16" || c == "sexadecimal" || c == "hexadecimal")
	{
		user.setBase(16);
		return true;
	}

	if (c == "base 17" || c == "base17" || c == "septendecimal")
	{
		user.setBase(17);
		return true;
	}

	if (c == "base 18" || c == "base18" || c == "octodecimal")
	{
		user.setBase(18);
		return true;
	}

	if (c == "base 19" || c == "base19" || c == "nonadecimal")
	{
		user.setBase(19);
		return true;
	}

	if (c == "base 20" || c == "base20" || c == "vigesimal")
	{
		user.setBase(20);
		return true;
	}

	if (c == "base 21" || c == "base21")
	{
		user.setBase(21);
		return true;
	}

	if (c == "base 22" || c == "base22")
	{
		user.setBase(22);
		return true;
	}

	if (c == "base 23" || c == "base23")
	{
		user.setBase(23);
		return true;
	}

	if (c == "base 24" || c == "base24")
	{
		user.setBase(24);
		return true;
	}

	if (c == "base 25" || c == "base25")
	{
		user.setBase(25);
		return true;
	}

	if (c == "base 26" || c == "base26")
	{
		user.setBase(26);
		return true;
	}

	if (c == "base 27" || c == "base27")
	{
		user.setBase(27);
		return true;
	}

	if (c == "base 28" || c == "base28")
	{
		user.setBase(28);
		return true;
	}

	if (c == "base 29" || c == "base29")
	{
		user.setBase(29);
		return true;
	}

	if (c == "base 30" || c == "base30")
	{
		user.setBase(30);
		return true;
	}

	if (c == "base 31" || c == "base31")
	{
		user.setBase(31);
		return true;
	}

	if (c == "base 32" || c == "base32")
	{
		user.setBase(32);
		return true;
	}

	if (c == "base 33" || c == "base33")
	{
		user.setBase(33);
		return true;
	}

	if (c == "base 34" || c == "base34")
	{
		user.setBase(34);
		return true;
	}

	if (c == "base 35" || c == "base35")
	{
		user.setBase(35);
		return true;
	}

	if (c == "base 36" || c == "base36")
	{
		user.setBase(36);
		return true;
	}

	return false;
}

/*

settings user(ONES_PLACE, false, false);

int analyze(line passed, settings user)
{
	

	string entered;
	bool exit = false;
	bignum previous;
	previous.updateDigits();

	//program loop
	while (exit == false)
	{
		entered.clear();

		//updates stored number if base has changed since last problem
		if (previous.getBase() != user.getBase())
			previous.convertBase(user.getBase());

		cout << "\n";
		displayNumber(previous, user, false, true);
		cout << "\n\n";

		std::getline(cin, entered);

		cout << "-----------------------" << endl;

		//checks if user requested a base change
		if (changeBase(entered, user))
		{
			continue;
		}

		if (entered == "clear" || entered == "reset")
		{
			bignum reset(0);
			reset.setBase(user.getBase());
			previous = reset;
			continue;
		}

		if (entered == "show stats")
		{
			cout << "\nNumber stats are visible\n\n";
			user.showDigitsOn();
			continue;
		}

		if (entered == "hide stats")
		{
			cout << "\nNumber stats are hidden\n\n";
			user.showDigitsOff();
			continue;
		}

		if (entered == "help")
		{
			printHelp();
			continue;
		}

		if (entered != "exit" && entered != "EXIT" && entered != "Exit")
		{
			solution answer(solve(entered, previous, user));

			if (answer.getError()>0)
			{
				cout << endl << "Invalid Input (Error " << answer.getError() << ")";
			}

			else
			{
				previous = answer.getSolved();
			}
		}

		else exit = true;

		cout << endl;
	}
}


ORIGINAL MAIN BELOW
{

settings user(ONES_PLACE, false, false);

string entered;
bool exit = false;
bignum previous;
previous.updateDigits();

//program loop
while (exit == false)
{
entered.clear();

//updates stored number if base has changed since last problem
if (previous.getBase() != user.getBase())
previous.convertBase(user.getBase());

cout << "\n";
displayNumber(previous, user, false, true);
cout << "\n\n";

std::getline(cin, entered);

cout << "-----------------------" << endl;

//checks if user requested a base change
if (changeBase(entered, user))
{
continue;
}

if (entered == "clear" || entered == "reset")
{
bignum reset(0);
reset.setBase(user.getBase());
previous = reset;
continue;
}

if (entered == "show stats")
{
cout << "\nNumber stats are visible\n\n";
user.showDigitsOn();
continue;
}

if (entered == "hide stats")
{
cout << "\nNumber stats are hidden\n\n";
user.showDigitsOff();
continue;
}

if (entered == "help")
{
printHelp();
continue;
}

if (entered != "exit" && entered != "EXIT" && entered != "Exit")
{
solution answer(solve(entered, previous, user));

if (answer.getError()>0)
{
cout << endl << "Invalid Input (Error " << answer.getError() << ")";
}

else
{
previous = answer.getSolved();
}
}

else exit = true;

cout << endl;
}
}
*/