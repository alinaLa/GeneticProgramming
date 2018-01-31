
#include "stdafx.h"
#include "CTree.h"

CTree::CTree() {
	root = new CNode;
}

CTree::~CTree() {
	delete root;
}

CTree::CTree(CTree &otherTree) {
	root = new CNode(*otherTree.root);
}

void CTree::setRoot(CNode *nodeRoot) {
	root = nodeRoot;
}

CNode * CTree::getRoot() {
	return root;
}

void CTree::preOrder(CNode *currentRoot, std::string *preOrderTree) {
	(*preOrderTree) += currentRoot->content + S_SPACE;
	if (!(currentRoot->children.empty())) {
		for (int i = 0; i < static_cast<int>(currentRoot->children.size()); i++) {
			preOrder(currentRoot->children[i], preOrderTree);
		}
	}
}

void CTree::makeVectorOfNodes(CNode *currentRoot, std::vector<CNode *> *nodes) {
	(*nodes).push_back(currentRoot);
	if (!(currentRoot->children.empty())) {
		for (int i = 0; i < static_cast<int>(currentRoot->children.size()); i++) {
			makeVectorOfNodes(currentRoot->children[i], nodes);
		}
	}
}

void CTree::repairTree() {
	repairHelper(this->root);
	repairHelper(this->root); //wywo³ujê drugi raz, bo tyle mo¿e byæ argumentów do operacji
	preOrderAndRepair(this->root);
}

int CTree::generateNumber(int min, int max) {
	return (rand() % ((max - min) + 1)) + min;
}

void CTree::preOrderAndRepair(CNode *currentRoot) {
	if (currentRoot->getContent().compare(EMPTY) == 0) {
		currentRoot->setContent(std::to_string(generateNumber(1, 100)));
	}
	if (!(currentRoot->children.empty())) {
		for (int i = 0; i < static_cast<int>(currentRoot->children.size()); i++) {
			preOrderAndRepair(currentRoot->children[i]);
		}
	}
}

void CTree ::repairHelper(CNode *currentRoot) {
	if (currentRoot->getNumberOfArguments() != currentRoot->getNumberOfChildren()) {
		currentRoot->addChild();
	}
	if (!(currentRoot->children.empty())) {
		for (int i = 0; i < static_cast<int>(currentRoot->children.size()); i++) {
			repairHelper(currentRoot->children[i]);
		}
	}
}

bool CTree::isMathOperation(std::string str) {
	if (str.compare(PLUS) == 0
		|| str.compare(MINUS) == 0
		|| str.compare(MULTIPLICATION) == 0
		|| str.compare(DIVISION) == 0
		|| str.compare(SIN) == 0
		|| str.compare(COS) == 0
		) {
		return true;
	}
	else {
		return false;
	}
}

bool CTree::isConstant(std::string str) {
	return isNumber(str);
}

bool CTree::isNameOfVariable(std::string str) {
	return !isNumber(str)&&!isMathOperation(str);
}

bool CTree::isNumber(std::string str) {
	char* p;
	strtol(str.c_str(), &p, 10);
	return *p == 0;
}


void CTree::preOrderAndCountDone(CNode *currentRoot, int *counter) {
	if (currentRoot->getNumberOfArguments() == currentRoot->getNumberOfChildren()) {
		(*counter)++;
	}
	if (!(currentRoot->children.empty())) {
		for (int i = 0; i < static_cast<int>(currentRoot->children.size()); i++) {
			preOrderAndCountDone(currentRoot->children[i], counter);
		}
	}
}


void CTree::preOrderAndWriteVariables(CNode *currentRoot, std::vector<CNode *> *variablesNodes) {
	if (isNameOfVariable(currentRoot->getContent())) {
		bool isThisVariableInVector = false;
		for (int i = 0; i < static_cast<int>(variablesNodes->size()); i++) {
			if ((*variablesNodes)[i]->getContent() == currentRoot->getContent()) {
				isThisVariableInVector = true;
			}
		}
		if (!isThisVariableInVector) {
			variablesNodes->push_back(currentRoot);
		}
	}
	if (!(currentRoot->children.empty())) {
		for (int i = 0; i < static_cast<int>(currentRoot->children.size()); i++) {
			preOrderAndWriteVariables(currentRoot->children[i], variablesNodes);
		}
	}
}

CNode * CTree::findConstOrVariable(CNode *root) {
	CNode *node = NULL;
	while (!root->children.empty()) {
		root = root->getLastChild();
		node = root;
	}
	return node;
}

CTree CTree::operator+(CTree otherTree) {
	CTree *mainTree = new CTree(*this);
	CNode *nodeToRemove = mainTree->findConstOrVariable(mainTree->root);
	otherTree.root->setParent(nodeToRemove->getParent());
	int index = 0;
	while (nodeToRemove->getParent()->getChild(index) != nodeToRemove) {
		index++;
	}
	nodeToRemove->getParent()->removeChild(index);
	nodeToRemove->getParent()->addChild();
	nodeToRemove->getParent()->changeNode(otherTree.root);
	return (*mainTree);
}

void CTree::operator=(CTree &otherTree) {
	if (this->root != NULL) {
		delete root;
	}
	this->root = new CNode(*otherTree.root);
}

void CTree::printLeavs() {
	std::vector<CNode *> *leavs = new std::vector<CNode *>;
	std::vector<std::string> *wektor = new std::vector<std::string>;
	preorderAndFindLeavs(root, leavs);
	for (int i = 0; i < (int)leavs->size(); i++) {
		printLeavsHelp((*leavs)[i], root, wektor);
		std::cout << root->getContent();
		for (int j = (int) wektor->size() - 1; j >= 0; j--) {
			std::cout << " -> " + (*wektor)[j];
		}
		std::cout << std::endl;
		wektor->clear();
	}
	delete leavs;
	delete wektor;
}

void CTree::printLeavsHelp(CNode *node, CNode *root, std::vector<std::string> *wektor) {
	if (node != root) {
		wektor->push_back(node->getContent());
		printLeavsHelp(node->parent, root, wektor);
	}
}

void CTree::preorderAndFindLeavs(CNode *currentRoot, std::vector<CNode *> *leavs) {
	if (!(currentRoot->children.empty())) {
		for (int i = 0; i < static_cast<int>(currentRoot->children.size()); i++) {
			preorderAndFindLeavs(currentRoot->children[i], leavs);
		}
	}
	else {
		leavs->push_back(currentRoot);
	}
}

void CTree::setValuesOfVariables(double x, double y, CNode *currentRoot) {
	if (currentRoot->content == X) {
		currentRoot->setValueOfVariable(x);
	}
	else if (currentRoot->content == Y) {
		currentRoot->setValueOfVariable(y);
	}
	if (!(currentRoot->children.empty())) {
		for (int i = 0; i < static_cast<int>(currentRoot->children.size()); i++) {
			setValuesOfVariables(x, y, currentRoot->children[i]);
		}
	}
}

//void CTree::repeatParents(CNode *currentRoot) {
//	for (int i = 0; i < (int) currentRoot->children.size(); i++) {
//		currentRoot->children[i]->setParent(currentRoot);
//	}
//	if (!(currentRoot->children.empty())) {
//		for (int i = 0; i < static_cast<int>(currentRoot->children.size()); i++) {
//			repeatParents(currentRoot->children[i]);
//		}
//	}
//}

void CTree::setLevels(CNode *currentRoot, int lastLevel) {
	currentRoot->setLevel(lastLevel);
	for (int i = 0; i < currentRoot->getNumberOfChildren(); i++) {
		setLevels(currentRoot->getChild(i), lastLevel + 1);
	}
}

void CTree::cutTree(int maxLevel) {
	setLevels(root, 0);
	cutTreeHelper(root, maxLevel);
	std::vector<CNode *> leavs;
	preorderAndFindLeavs(root, &leavs);
	for (int i = 0; i < leavs.size(); i++) {
		if (isMathOperation(leavs[i]->getContent())) {
			int number = generateNumber(1, 3);
			if (number == 1) {
				leavs[i]->setContent(X);
			}
			else if (number == 2) {
				leavs[i]->setContent(std::to_string(generateNumber(1, 100)));
			}
			else if (number == 3) {
				leavs[i]->setContent(Y);
			}
		}
	}
}

void CTree::cutTreeHelper(CNode *currentRoot, int maxLevel) {
	if (currentRoot->getLevel() == maxLevel) {
		for (int i = 0; i < currentRoot->getNumberOfChildren(); i++) {
			delete currentRoot->getChild(i);

		}
		while (currentRoot->getNumberOfChildren() != 0) {
			currentRoot->removeChild(0);
		}
	}
	if (!(currentRoot->children.empty())) {
		for (int i = 0; i < static_cast<int>(currentRoot->children.size()); i++) {
			(currentRoot->children[i], maxLevel);
		}
	}
}