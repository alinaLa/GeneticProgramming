#pragma once

#include <iostream>
#include "CNode.h"
#include "Manager.h"

std::string const S_SPACE = " ";

class CTree {
	friend class Manager;
private:
	CNode *root;
	
	double valueOfTheAdaptationFunction;

public:
	CTree();
	CTree(CTree &otherTree);
	~CTree();
	void setRoot(CNode *nodeRoot);
	CNode *getRoot();
	void preOrder(CNode *currentRoot, std::string *preOrderTree);
	void makeVectorOfNodes(CNode *currentRoot, std::vector<CNode *> *nodes);
	void repairTree();
	void preOrderAndRepair(CNode *root);
	void repairHelper(CNode *currentRoot);
	bool isMathOperation(std::string str); 
	bool isConstant(std::string str);
	bool isNameOfVariable(std::string str);
	bool isNumber(std::string str);
	void preOrderAndCountDone(CNode *currentRoot, int *counter);
	void preOrderAndWriteVariables(CNode *currentRoot, std::vector<CNode *> *variablesNodes);
	CNode *findConstOrVariable(CNode *root);
	CTree operator+(CTree otherTree);
	void operator=(CTree &otherTree);

	void printLeavs();
	void printLeavsHelp(CNode *node, CNode *root, std::vector<std::string> *wektor);
	void preorderAndFindLeavs(CNode *currentRoot, std::vector<CNode *> *leavs);
	void setValuesOfVariables(double x, double y, CNode *currentRoot);
	int generateNumber(int min, int max);
	void cutTree(int maxLevel);
	void setLevels(CNode *currentRoot, int lastLevel);
	void cutTreeHelper(CNode *currentRoot, int maxLevel);
};