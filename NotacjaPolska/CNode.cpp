
#include "stdafx.h"
#include "CNode.h"
#include <iostream>

CNode::CNode() {
	content = EMPTY;
	valueOfVariable = 1;
}

CNode::CNode(CNode &otherNode) {
	parent = NULL;
	if (!otherNode.children.empty()) {
		CNode *child;
		for (int i = 0; i < (int)(otherNode.children.size()); i++) {
			child = new CNode(*otherNode.children[i]);
			(*child).parent = this;
			children.push_back(child);
		}
	}
	content = otherNode.content;
	valueOfVariable = otherNode.valueOfVariable;
}

CNode::~CNode() {
	for (int ii = 0; ii < (int)children.size(); ii++)
		delete children.at(ii);
}

void CNode::setParent(CNode *nodeParent) {
	parent = nodeParent;
}

void CNode::setContent(std::string nodeContent) {
	content = nodeContent;
}

void CNode::addChild() {
	CNode *child = new CNode;
	children.push_back(child);
	child->setParent(this);
}

void CNode::addChild(CNode *child, CNode *parent) {
	children.push_back(child);
	child->setParent(parent);
}

std::string CNode::getContent() {
	return content;
}

CNode * CNode::getLastChild() {
	return children.back();
}

CNode * CNode::getParent() {
	return parent;
}

int CNode::getNumberOfChildren() {
	return children.size();
}

int CNode::getNumberOfArguments() {
	if (content == SIN || content == COS) {
		return 1;
	}
	else if(content == PLUS || content == MINUS || content == MULTIPLICATION || content == DIVISION){
		return 2;
	}
	else {
		return 0;
	}
}

CNode * CNode::getChild(int index) {
	return children[index];
}

double CNode::getValueOfVariable() {
	return valueOfVariable;
}

void CNode::setValueOfVariable(double value) {
	valueOfVariable = value;
}

void CNode::removeChild(int index) {
	//if(children[index] != NULL)
	children.erase(children.begin() + index);
}

void CNode::changeNode(CNode *other) {
	children.back() = other;
}

void CNode::setLevel(int l) {
	level = l;
}

int CNode::getLevel() {
	return level;
}