#pragma once

#include <vector>

std::string const DEFAULT_CONTENT = "1";
std::string const PLUS = "+";
std::string const MINUS = "-";
std::string const MULTIPLICATION = "*";
std::string const DIVISION = "/";
std::string const SIN = "sin";
std::string const COS = "cos";
std::string const EMPTY = "";

class CNode {
private:
	friend class CTree;
	CNode *parent;
	std::vector<CNode *> children;
	std::string content;
	double valueOfVariable;
	int level;
public:
	CNode();
	CNode(CNode &otherNode);
	~CNode();
	void setParent(CNode *nodeParent);
	void setContent(std::string nodeContent);
	void addChild();
	void addChild(CNode *child, CNode *parent);
	std::string getContent();
	CNode * getParent();
	CNode * getLastChild();
	int getNumberOfChildren();
	int getNumberOfArguments();
	CNode *getChild(int index);
	double getValueOfVariable();
	void setValueOfVariable(double value);
	void removeChild(int index);
	void changeNode(CNode *other);
	void setLevel(int l);
	int getLevel();
};