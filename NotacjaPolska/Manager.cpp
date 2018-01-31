
#include "stdafx.h"
#include <cctype>
#include <algorithm>
#include <functional>
#include "Manager.h"



bool Manager::isMathOperation(std::string str) {
	if (str.compare(PLUS) == 0 
		|| str.compare(MINUS) == 0 
		|| str.compare(MULTIPLICATION) == 0 
		|| str.compare(DIVISION) == 0 
		|| str.compare(SIN) == 0 
		|| str.compare(COS)== 0
		) {
		return true;
	}
	else {
		return false;
	}
}

bool Manager::isConstant(std::string str) {
	return isNumber(str);
}

bool Manager::isNameOfVariable(std::string str) {
	return !isNumber(str) && !isMathOperation(str);
}

//bool Manager::isNumber(std::string str) {
//	char* p;
//	strtol(str.c_str(), &p, 10);
//	return *p == 0;
//}

bool Manager::shouldTreeBeRepair(CTree *tree) {
	int *counter = new int;
	(*counter) = 0;
	tree->preOrderAndCountDone(tree->root, counter);
	if ((*counter) != static_cast<int>(inputVector.size())-1) {
		delete counter;
		return true;
	}
	else {
		delete counter;
		return false;
	}
	
}

void Manager::buildTree(CTree *tree) {
	CNode *currentNode = tree->root;
	bool loopCondition = true;
	int i = 1;
	while (i < static_cast<int>(inputVector.size()) && loopCondition) {
		if (currentNode->getContent().compare("") == 0) {
			currentNode->setContent(inputVector[i]);
			if (isMathOperation(inputVector[i])) {
				currentNode->addChild();
				currentNode = currentNode->getLastChild();
				i++;
			}
			else {
				if (currentNode == tree->root) {
					loopCondition = false;
				}
				else {
					currentNode = currentNode->getParent();
				}
			}
		}
		else {
			if (currentNode->getNumberOfArguments() == currentNode->getNumberOfChildren()) {
				if (currentNode == tree->root) {
					loopCondition = false;
				}
				else {
					currentNode = currentNode->getParent();
				}
			}
			else {
				currentNode->addChild();
				currentNode = currentNode->getLastChild();
				i++;
			}
		}

	}
}

double Manager::calculateValue(CNode *currentRoot, bool *byZero) {
	if (isMathOperation(currentRoot->getContent())) {
		if (currentRoot->getContent() == PLUS) {
			return calculateValue(currentRoot->getChild(0), byZero) + calculateValue(currentRoot->getChild(1), byZero);
		}
		else if (currentRoot->getContent() == MINUS) {
			return calculateValue(currentRoot->getChild(0), byZero) - calculateValue(currentRoot->getChild(1), byZero);
		}
		else if (currentRoot->getContent() == MULTIPLICATION) {
			return calculateValue(currentRoot->getChild(0), byZero) * calculateValue(currentRoot->getChild(1), byZero);
		}
		else if (currentRoot->getContent() == DIVISION) {
			if (calculateValue(currentRoot->getChild(1), byZero) == 0) {
				(*byZero) = true;
				return 0;
			}
			else {
				return calculateValue(currentRoot->getChild(0), byZero) / calculateValue(currentRoot->getChild(1), byZero);
			}
		}
		else if (currentRoot->getContent() == SIN) {
			return sin(calculateValue(currentRoot->getChild(0), byZero) * (M_PI/HALF_ANGLE));
		}
		else { //if (currentRoot->getContent() == "cos") {
			return cos(calculateValue(currentRoot->getChild(0), byZero) * (M_PI / HALF_ANGLE));
		}
	}
	else {
		if (isConstant(currentRoot->getContent())) {
			return stod(currentRoot->getContent());
		}
		else {//if (isNameOfVariable(currentRoot->getContent())) {
			return currentRoot->getValueOfVariable();
		}
	}
}

void Manager::writeVariables(CTree *tree) {
	variablesNodes.clear();
	tree->preOrderAndWriteVariables(tree->root, &variablesNodes);
}

void Manager::setValuesOfVariables() {
	valuesOfVariables.clear();
	for (int i = 1; i < static_cast<int>(inputVector.size()); i++) {
		valuesOfVariables.push_back(stoi(inputVector[i]));
	}
	for (int i = 0; i < static_cast<int>(variablesNodes.size()); i++) {
		variablesNodes[i]->setValueOfVariable(valuesOfVariables[i]);
	}
}

CTree Manager::join(CTree mainTree) { 
	CTree *otherTree = new CTree();
	CTree *sumTree = new CTree();
	buildTree(otherTree);
	if (shouldTreeBeRepair(otherTree)) {
		otherTree->repairTree();
	}
	(*sumTree) = mainTree + (*otherTree);
	return (*sumTree);
}

void Manager::repairNameOfVariable() {
	for (int i = 1; i < static_cast<int>(inputVector.size()); i++) {
		if (!isMathOperation(inputVector[i]) && isNameOfVariable(inputVector[i])) {
			inputVector[i].erase(std::remove_if(inputVector[i].begin(), inputVector[i].end(), std::not1(std::ptr_fun((int(*)(int))std::isalnum))), inputVector[i].end());
		}
	}
}



//
//void Manager::test() {
//	inputVector.push_back("enter");
//	inputVector.push_back("+");
//	inputVector.push_back("1");
//	inputVector.push_back("2");
//	CTree tree;
//	buildTree(&tree);
//	inputVector.push_back("enter");
//	inputVector.push_back("*");
//	inputVector.push_back("3");
//	inputVector.push_back("4");
//	CTree sumTree = join(tree);
//	sumTree.preOrder(sumTree.getRoot());
//
//}


int Manager::generateNumber(int min, int max) {
	return (rand() % ((max - min) + 1)) + min;
}

std::string Manager::generateNode() {
	int number = generateNumber(ONE, NINE);
	if (number == ONE) {
		return SIN;
	}
	else if (number == TWO) {
		return X;
	}
	else if (number == THREE) {
		return PLUS;
	}
	else if (number == FOUR) {
		return MINUS;
	}
	else if (number == FIVE) {
		return Y;
	}
	else if (number == SIX) {
		return DIVISION;
	}
	else if (number == SEVEN) {
		return MULTIPLICATION;
	}
	else if (number == EIGHT) {
		return std::to_string(generateNumber(ONE, ONE_HUNDERT));
	}
	else if (number == NINE) {
		return COS;
	}
}

void Manager::generateFormula(int numberOfNodes) {
	inputVector.clear();
	for (int i = 0; i < numberOfNodes; i++) {
		inputVector.push_back(generateNode());
	}
}

void Manager::initPopulation(int populationSize) {
	for (int i = 0; i < populationSize; i++) {
		generateFormula(generateNumber(TWO, TEN));
		CTree *tree = new CTree();
		buildTree(tree);
		tree->repairTree();
		population.push_back(tree);
	}
}

//void Manager::mutate(CTree *tree) {
//	CNode *nodeToRemove = findRandomNode(tree);
//	if (nodeToRemove == tree->root) {
//		delete tree;
//		generateFormula(generateNumber(2, 10));
//		CTree *newSubtree = new CTree();
//		buildTree(newSubtree);
//		tree = newSubtree;
//		tree->repairTree();
//	}
//	else {
//		CNode *parentOfNodeToRemove = nodeToRemove->getParent();
//		int index = 0;
//		bool loop = true;
//		while (index < parentOfNodeToRemove->getNumberOfChildren() && loop) {
//			if (parentOfNodeToRemove->getChild(index) == nodeToRemove) {
//				loop = false;
//			}
//			else {
//				index++;
//			}
//		}
//		parentOfNodeToRemove->removeChild(index);
//		delete nodeToRemove;
//		generateFormula(generateNumber(2, 10));
//		CTree *newSubtree = new CTree();
//		buildTree(newSubtree);
//		parentOfNodeToRemove->addChild(newSubtree->root, parentOfNodeToRemove);
//		tree->repairTree();
//	}
//}

//void Manager::mutate(CTree *tree) {
//	CNode *nodeToRemoveParent = findRandomNode(tree);
//	int numberOfChildren = nodeToRemoveParent->getNumberOfChildren();
//	if (numberOfChildren != 0) {
//		CNode *nodeToRemove = nodeToRemoveParent->getLastChild();
//		nodeToRemoveParent->removeChild(numberOfChildren - 1);
//		delete nodeToRemove;
//		
//	}
//	generateFormula(generateNumber(2, 10));
//	CTree *newSubtree = new CTree();
//	buildTree(newSubtree);
//	nodeToRemoveParent->addChild(newSubtree->root, nodeToRemoveParent);
//	tree->repairTree();
//}


void Manager::mutate(CTree *tree) {
	if (tree->root->getNumberOfChildren() != 0) {
		CNode *nodeToRemove;
		do {
			nodeToRemove = findRandomNode(tree);
		} while (nodeToRemove->getNumberOfChildren() != 0);
		CNode *nodeToRemoveParent = nodeToRemove->getParent();
		//delete nodeToRemove;
		CNode *newNode = new CNode();
		newNode->setContent(generateNode());
		newNode->setParent(nodeToRemoveParent);
		tree->repairTree();
	}
	else {
		generateFormula(generateNumber(TWO, TEN));
		CTree *newSubtree = new CTree();
		buildTree(newSubtree);
		newSubtree->repairTree();
	}
}

CNode* Manager::findRandomNode(CTree *tree) {
	std::vector<CNode *> nodes;
	tree->makeVectorOfNodes(tree->root, &nodes);
	int index = generateNumber(0, nodes.size() - 1);
	return nodes[index];
}

void Manager::cross(CTree *firstTree, CTree *secondTree) {
	CNode *firstRoot = findRandomNode(firstTree);
	CNode *secondRoot = findRandomNode(secondTree);
	CNode *tmp = firstRoot->getParent();
	firstRoot->setParent(secondRoot->getParent());
	secondRoot->setParent(tmp);
}

void Manager::readFile(std::string path, bool *fileGood, bool *onlyNumbers) {
	file.open(path, std::fstream::in);
	if (file.is_open()) {
		(*fileGood) = true;
		std::string line;
		std::string number;
		while (!file.eof())
		{
			getline(file, line);
			if (line[line.size() - 1] != END) {
				line += END;
			}
			std::vector<double> four;
			int i = 0;
			while (i < static_cast<int>(line.size())) {
				if (line[i] == END) {
					if (isNumber(number)) {
						four.push_back(stod(number));
						number = EMPTY;
					}
					else {
						(*onlyNumbers) = false;
					}
				}
				else {
					number += line[i];
				}
				i++;
			}
			data.push_back(four);
		}
		file.close();
	}
	else {
		(*fileGood) = false;
	}
}

void Manager::evaluate() {
	//std::cout << data[0][0] << std::endl;
	//std::cout << data[0][1] << std::endl;
	
	for (int i = 0; i < (int) population.size(); i++) {
		bool byZero = false;
		population[i]->valueOfTheAdaptationFunction = 0;
		
		for (int j = 0; j < (int) data.size() && !byZero; j++) {
			/*std::cout << data[j][0] << std::endl;
			std::cout << data[j][1] << std::endl;
			std::cout << data[j][2] << std::endl;*/
			population[i]->setValuesOfVariables(data[j][0], data[j][1], population[i]->root);
			double value = calculateValue(population[i]->getRoot(), &byZero);
			//std::string t;
			//population[i]->preOrder(population[i]->root, &t);
			//std::cout << t << "value "<< value << std::endl;
			if (byZero) {
				population[i]->valueOfTheAdaptationFunction = INT_MAX;
			}
			else {
				population[i]->valueOfTheAdaptationFunction += (data[j][TWO] - value)*(data[j][TWO] - value);
			}
			 
		}
	}
	findTheBestSolution();
}

void Manager::findTheBestSolution() {
	theBestSolution = population[0];
	for (int i = 1; i < population.size(); i++) {
		if (population[i]->valueOfTheAdaptationFunction < theBestSolution->valueOfTheAdaptationFunction) {
			theBestSolution = population[i];
		}
	}
}

void Manager::select() {
	int n = 0;
	populationOfParents.clear();
	while (n < population.size()) {
		int firstIndex = generateNumber(0, population.size() - 1);
		int secondIndex;
		do {
			secondIndex = generateNumber(0, population.size() - 1);
		} while (secondIndex == firstIndex);
if (population[firstIndex]->valueOfTheAdaptationFunction >= 0 && population[secondIndex]->valueOfTheAdaptationFunction != 0) {
	populationOfParents.push_back(
		population[firstIndex]->valueOfTheAdaptationFunction < population[secondIndex]->valueOfTheAdaptationFunction ?
		population[firstIndex] : population[secondIndex]);
}
else if (population[firstIndex]->valueOfTheAdaptationFunction >= 0) {
	populationOfParents.push_back(population[firstIndex]);
}
else {
	populationOfParents.push_back(population[secondIndex]);
}
n++;
	}

}

void Manager::runCrossing(int probability) {
	std::vector<CTree *> children;
	while ((int)populationOfParents.size() > 1) {
		int firstIndex = generateNumber(0, populationOfParents.size() - 1);
		int secondIndex;
		do {
			secondIndex = generateNumber(0, populationOfParents.size() - 1);
		} while (secondIndex == firstIndex);
		int chance = generateNumber(ONE, ONE_HUNDERT);
		CTree *newParentFirst = new CTree(*populationOfParents[firstIndex]);
		CTree *newParentSecond = new CTree(*populationOfParents[secondIndex]);
		if (chance <= probability) {
			cross(newParentFirst, newParentSecond);
		}
		children.push_back(newParentFirst);
		children.push_back(newParentSecond);
		if (firstIndex > secondIndex) {
			populationOfParents.erase(populationOfParents.begin() + firstIndex);
			populationOfParents.erase(populationOfParents.begin() + secondIndex);
		}
		else {
			populationOfParents.erase(populationOfParents.begin() + secondIndex);
			populationOfParents.erase(populationOfParents.begin() + firstIndex);
		}
	}
	while ((int)populationOfParents.size() != 0) {
		children.push_back(populationOfParents[0]);
		populationOfParents.erase(populationOfParents.begin());
	}
	population.clear();
	for (int i = 0; i < (int)children.size(); i++) {
		population.push_back(children[i]);
	}
	//population = children;
	//children.clear();
}

void Manager::runMutation(int probability) {
	for (int i = 0; i < (int)population.size(); i++) {
		if (generateNumber(ONE, ONE_HUNDERT) <= probability) {
			mutate(population[i]);
		}
	}
}

void Manager::gp(int sizeOfPopulation, int numberOfIterations, int probabilityOfCrosssing, int probabilityOfMutation) {
	initPopulation(sizeOfPopulation);

	//return;
	evaluate();

	int i = 0;
	while (i < numberOfIterations) {
		select();
		runCrossing(probabilityOfCrosssing);
		//return;

		runMutation(probabilityOfMutation);
		evaluate();
		i++;
	}
}

void Manager::dealocateMemeory() {
	for (int i = 0; i < (int)population.size(); i++) {
		delete population[i];
	}
}

void Manager::writeToFile(std::string path, bool *fileGood) {
	std::fstream fileToWrite(path, std::ios::out);
	if (fileToWrite.good()) {
		(*fileGood) = true;
		std::string solution;
		theBestSolution->preOrder(theBestSolution->root, &solution);
		fileToWrite << solution;
	}
	else {
		(*fileGood) = false;
	}
}

bool Manager::isNumber(std::string str)
{
	for (int i = 0; i < str.size(); i++){
		if (str[i] == ',') {
			str[i] = '.';
		}
	}
	char *end;
	double result = strtod(str.c_str(), &end);
	if (end == str.c_str() || *end != '\0') return false;
	return true;
}

