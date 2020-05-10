/*
 * hashNode.cpp
 *
 *  Created on: Nov 18, 2019
 *      Author: Brett Wagner
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "hashNode.hpp"

using namespace std;

hashNode::hashNode() {
	keyword = "";
	valuesSize = 0;
	currSize = 0;
	values = NULL;
}

hashNode::hashNode(string s) {
	keyword = "";
	valuesSize = 0;
	currSize = 0;
	values = NULL;
	keyword = s;
	valuesSize = 100;
	currSize += 1;
	values = new string[valuesSize];
}

hashNode::hashNode(string s, string v) {
	keyword = "";
	valuesSize = 0;
	currSize = 0;
	values = NULL;
	keyword = s;
	valuesSize = 100;
	values = new string[valuesSize];
	values[0] = v;
	currSize += 1;
}

void hashNode::addValue(string v) {
	values[currSize] = v;
	currSize += 1;
	if (currSize == valuesSize) {
		dblArray();
	}
}

void hashNode::dblArray() {
	int old = valuesSize;
	valuesSize = valuesSize * 2;
	string *temp = new string[valuesSize];
	for (int i = 0; i < old; i++) {
		temp[i] = values[i];
	}
	delete[] values;
	values = temp;
}

string hashNode::getRandValue() {
	if (currSize == 0) {
		return "";
	} else {
		return values[rand() % currSize];
	}
}


//int main(){
//	hashNode n = hashNode("a","Hello");
//	cout<<n.getRandValue();
//}
