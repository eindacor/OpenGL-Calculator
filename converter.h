#ifndef CONVERTER_H
#define CONVERTER_H

#include "header.h"

#define MAXENTERED 256
#define RETURN_ERROR return solution(bignum(), __LINE__)
#define RETURN_OK(x) return solution(x, 0)
#define RETURN_FALSE return false
#define RETURN_TRUE return true
#define PRINTLIST(x)

class solution
{
public:
	solution(bignum bn, int n) : solved(bn), error(n) {};
	~solution(){};

	bignum getSolved() { return solved; }
	int getError() { return error; }

	void operator = (solution s) { solved = s.getSolved(); error = s.getError(); }

private:
	bignum solved;
	int error;
};

class settings
{
public:
	settings() { round = ONES_PLACE; percent = false; showDigits = false; base = 10; }
	settings(int n, bool b, bool d) { round = n; percent = b; showDigits = d; base = 10; }
	~settings(){};

	void setRound(int n);
	void setBase(int n) { base = n; }
	void percentOff() { percent = false; }
	void percentOn() { percent = true; }
	void showDigitsOff() { showDigits = false; }
	void showDigitsOn() { showDigits = true; }

	int getRound() { return round; }
	bool getPercent() { return percent; }
	bool getShowDigits() { return showDigits; }
	int getBase() { return base; }

private:
	int round;
	bool percent;
	bool showDigits;
	int base;
};

class calcItem
{
public:
	calcItem(ITYPE it) { itemType = it; }
	~calcItem(){};

	ITYPE getItemType() { return itemType; }

	virtual bignum getStoredNumber() { return bignum(0); }
	virtual STYPE getSymbolType() { return ERROR; }
	virtual char getStoredChar() { return '0'; }
	virtual int getParenID() { return 0; }
	virtual void setParenID(int n) {};
	virtual bool getOpen() { return false; }

private:
	ITYPE itemType;
};

class numberItem : public calcItem
{
public:
	numberItem(bignum bn) : calcItem(NUMBER), stored(bn) {};
	~numberItem(){};

	bignum getStoredNumber() { return stored; }

private:
	bignum stored;
};

class symbolItem : public calcItem
{
public:
	symbolItem(char c);
	~symbolItem(){};

	char getStoredChar() { return stored; }
	STYPE getSymbolType() { return symbolType; }

private:
	char stored;
	STYPE symbolType;
};

class parenItem : public calcItem
{
public:
	parenItem(char c);
	~parenItem(){};

	int getParenID() { return parenID; }
	void setParenID(int n) { parenID = n; }
	char getStoredChar() { return stored; }

	bool getOpen() { return open; }

private:
	char stored;
	int parenID;
	bool open;
};

class calc_ptr
{
public:
	calc_ptr(const calc_ptr &original);
	calc_ptr(calcItem* original);
	~calc_ptr(){ delete stored; }

	calcItem* getStored() { return stored; }
	calcItem* readStored() const { return stored; }
	void setStored(calcItem* &original) { stored = original; }
	void setNull() { stored = NULL; }

	calcItem& operator* () const
	{
		return *(stored);
	}

	calcItem* operator-> () const
	{
		return stored;
	}

	static calcItem* duplicate(calc_ptr &original);

private:
	calcItem* stored;
};


class numberPrimer
{
public:
	numberPrimer();
	~numberPrimer(){};

	int getDecimalCount() { return decimalCount; }
	int getCommaNumbers() { return decimalCount; }
	int getNumbers() { return numbers; }

	void incrementDecimalCount() { decimalCount++; }
	void incrementCommaNumbers() { decimalCount++; }
	void incrementNumbers() { numbers++; }

	void setCommaNumbers(int n) { commaNumbers = n; }

	bool getDecimal() { return decimal; }
	bool getComma() { return comma; }
	bool getDone() { return done; }
	bool getPrintExact() { return printExact; }
	bool getPrintStats() { return printStats; }
	bool getManualSet() { return manualSet; }

	void setDecimal(bool b) { decimal = b; }
	void setComma(bool b) { comma = b; }
	void setDone(bool b) { done = b; }
	void setPrintExact(bool b) { printExact = b; }
	void sgetPrintStats(bool b) { printStats = b; }
	void sgetManualSet(bool b) { manualSet = b; }

	void reset();

private:
	int decimalCount;
	int commaNumbers;
	int numbers;

	bool decimal;
	bool comma;
	bool done;
	bool printExact;
	bool printStats;
	bool manualSet;
};

solution solve(string &entered, bignum &previous, settings &user);
STYPE checkSymbol(char &c);
int checkNumber(char const &c);
bool isSpace(char const &c);
bool isNumber(char const &c, settings &user);
bool isSymbol(char &c);
bignum numberFromVector(vector<int> &vec, int dec, settings &user);
bool checkWord(string c, int start, string compare);
void printListBasic(list<calc_ptr> &itemList, int line, string s);
list<calc_ptr>::iterator addNumberToList(list <calc_ptr> &itemList, list <calc_ptr>::iterator i, bignum bn);
list<calc_ptr>::iterator addCharToList(list <calc_ptr> &itemList, list <calc_ptr>::iterator i, char c);
bool checkValid(list<calc_ptr> &itemList);
bool swapItems(list<calc_ptr> &itemList);
list<calc_ptr>::iterator simplifyRange(list <calc_ptr> &itemList, list <calc_ptr>::iterator i1, list <calc_ptr>::iterator i2, bignum bn);
void simplify_simpleProblem(list<calc_ptr> &itemList);
void simplify_factorialProblem(list<calc_ptr> &itemList);
void simplify_pfemdasProblem(list<calc_ptr> &itemList);
bool simplify(list<calc_ptr> &itemList);
bool generateProblem(string &c, list <calc_ptr> &itemList, settings &user, bignum previous);
solution solve(string &entered, bignum &previous, settings &user);
bool changeBase(string c, settings &user);

#endif