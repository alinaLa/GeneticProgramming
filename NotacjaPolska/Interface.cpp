#include "stdafx.h"
#include "Interface.h"


void Manager::enterFormulaIntoVector() {
	inputVector.clear();
	std::getline(std::cin, input);
	input += S_SPACE;
	std::string command = EMPTY;
	int i = 0;
	while (i < static_cast<int>(input.size())) {
		if (input[i] == C_SPACE && command.compare(EMPTY) != 0) {
			inputVector.push_back(command);
			command = EMPTY;
		}
		else {
			command += input[i];
		}
		i++;
	}

	/*for (int i = 0; i < static_cast<int>(inputVector.size()); i++) {
	std::cout << inputVector[i] << std::endl;
	}*/

}

void Manager::drawInterface(CTree *tree) {
	std::string *preOrderTree = new std::string;
	bool *byZero = new bool;
	while (true) {
		enterFormulaIntoVector();
		if (inputVector[0] == COMMAND_ENTER) {
			(*preOrderTree) = EMPTY;
			repairNameOfVariable();
			CTree *newTree = new CTree();
			buildTree(newTree);
			if (shouldTreeBeRepair(newTree)) {
				std::cout << INFO_WRONG_FORMULA << std::endl;
				newTree->repairTree();
			}
			std::cout << INFO1;
			newTree->preOrder(newTree->getRoot(), preOrderTree);
			std::cout << (*preOrderTree);
			std::cout << std::endl;
			delete tree;
			tree = newTree;
		}
		else if (inputVector[0] == COMMAND_VARS) {
			bool onlyNumbers = true;
			for (int i = 1; i < static_cast<int>(inputVector.size()); i++) {
				if (!isNumber(inputVector[i])) {
					onlyNumbers = false;
				}
			}
			if (onlyNumbers) {
				writeVariables(tree);
				for (int i = 0; i < static_cast<int>(variablesNodes.size()); i++) {
					std::cout << variablesNodes[i]->getContent() << S_SPACE;
				}
				std::cout << std::endl;
			}
			else {
				std::cout << INFO_WRONG_PARAMETERS << std::endl;
			}
		}
		else if (inputVector[0] == COMMAND_PRINT) {
			(*preOrderTree) = EMPTY;
			tree->preOrder(tree->getRoot(), preOrderTree);
			std::cout << (*preOrderTree);
			std::cout << std::endl;
		}
		else if (inputVector[0] == COMMAND_COMP) {
			(*byZero) = false;
			writeVariables(tree);
			if (inputVector.size() - 1 == variablesNodes.size()) {
				setValuesOfVariables();
				double value = calculateValue(tree->getRoot(), byZero);
				if ((*byZero)) {
					std::cout << INFO_BY_ZERO;
				}
				else {
					std::cout << std::fixed << std::showpoint;
					std::cout << std::setprecision(PRECISION);
					std::cout << VALUE << value << std::endl;
				}
			}
			else {
				std::cout << INFO2 << std::endl;
			}
		}
		else if (inputVector[0] == COMMAND_JOIN) {
			repairNameOfVariable();
			CTree *sumTree = new CTree();
			(*sumTree) = join(*tree);
			tree = sumTree;
		}
		else if (inputVector[0] == COMMAND_EXIT) {
			delete preOrderTree;
			delete byZero;
			exit(0);
		}
		else if (inputVector[0] == "printleavs") {
			tree->printLeavs();
		}
		else {
			std::cout << INFO_WRONG_COMMAND << std::endl;
		}
	}
}

void Manager::printSolution() {
	//return;
	std::string solution;
	theBestSolution->preOrder(theBestSolution->root, &solution);
	std::cout << INFO_THE_BEST_SOLUTION << solution << std::endl;
	std::cout << INFO_VALUE_OF_THE_FUNCTION << theBestSolution->valueOfTheAdaptationFunction;
}
