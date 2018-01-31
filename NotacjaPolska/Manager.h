#pragma once

#include <string>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stack>
#include <iostream>
#include <fstream>
#include <conio.h>
#include "CTree.h"

std::string const INFO_BY_ZERO = "DZIELENIE PRZEZ ZERO, nie mozna obliczyc wartosci. ";
int const HALF_ANGLE = 180;
const std::string X = "x";
const std::string Y = "y";
const char END = ';';
const int ONE = 1;
const int TWO = 2;
const int THREE = 3;
const int FOUR = 4;
const int FIVE = 5;
const int SIX = 6;
const int SEVEN = 7;
const int EIGHT = 8;
const int NINE = 9;
const int TEN = 10;
const int ONE_HUNDERT = 100;



class Manager {
private:
	friend class CTree;
	std::string input;
	std::vector<std::string> inputVector;
	std::vector<CNode *> variablesNodes;
	std::vector<double> valuesOfVariables;
	
	std::vector<CTree *> population;
	std::vector <std::vector<double>> data;
	std::fstream file;
	std::vector<CTree *> populationOfParents;
	CTree *theBestSolution;
	
public:
	void enterFormulaIntoVector();
	bool isMathOperation(std::string str);
	bool isConstant(std::string str);
	bool isNameOfVariable(std::string str);
	//bool isNumber(std::string str);
	void buildTree(CTree *tree);
	bool shouldTreeBeRepair(CTree *tree);
	double calculateValue(CNode *currentRoot, bool *byZero);
	void writeVariables(CTree *tree);
	void setValuesOfVariables();
	CTree join(CTree mainTree);
	void repairNameOfVariable();
	void drawInterface(CTree *tree);
	//void test();

	int generateNumber(int min, int max);
	std::string generateNode();
	void generateFormula(int numberOfNodes);
	void initPopulation(int populationSize);
	void mutate(CTree *tree);
	CNode* findRandomNode(CTree *tree);
	void cross(CTree *firstTree, CTree *secondTree);
	void readFile(std::string path, bool *fileGood, bool *onlyNumbers);
	void evaluate();
	void select();
	void findTheBestSolution();
	void runCrossing(int probability); //prawdopodobieñstwo w procentach
	void runMutation(int probability);
	void gp(int sizeOfPopulation, int numberOfIterations, int probabilityOfCrosssing, int probabilityOfMutation);
	void printSolution();
	void dealocateMemeory();
	void writeToFile(std::string path, bool *fileGood);
	bool isNumber(std::string str);
};