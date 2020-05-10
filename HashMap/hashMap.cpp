/*
 * hashMap.cpp
 *
 *  Created on: Nov 21, 2019
 *      Author: Brett Wagner
 */

#include "hashNode.hpp"
#include "hashMap.hpp"
#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
	first = "";
	numKeys = 0;
	mapSize = 23;
	h1 = hash1;
	c1 = coll1;
	collisionct1 = 0;
	collisionct2 = 0;
	map = new hashNode*[mapSize];
	for (int i = 0; i < mapSize; i++) {
		map[i] = new hashNode();
	}
}

void hashMap::addKeyValue(string k, string v) {
	int i = getIndex(k);
	if (map[i]->keyword != "") {
		map[i]->addValue(v);
		return;
	}
	hashNode *n = new hashNode(k, v);
	map[i] = n;
	if (numKeys == 0) {
		first = n->keyword;
	}
	numKeys++;
}

void hashMap::addNode(hashNode *n) {
	int h = getIndex(n->keyword);
	map[h] = n;
}

int hashMap::getIndex(string k) {
	int h;
	if (numKeys > .7 * mapSize) {
		reHash();
	}
	if (h1) {
		h = calcHash(k);
	} else {
		h = calcHash2(k);
	}
	if (map[h]->keyword == k) {
		return h;
	}
	if (map[h]->keyword != "") {
		collisionct1++;
		int c = -1;
		while (map[h]->keyword != "") {
			c += 1;
			if (map[h]->keyword == k) {
				return h;
			}
			if (c1) {
				h = collHash1(h);
			} else {
				h = collHash2(h);
			}
		}
		collisionct2 += c;
	}
	return h;
}

int hashMap::calcHash(string k) {
	int s = 0;
	for (int i = 0; i < k.length(); i++) {
		s += (int) k[i];
	}
	s += s / 3;
	return s % mapSize;
}

int hashMap::calcHash2(string k) {
	int s = 0;
	for (int i = 0; i < k.length(); i++) {
		s += (int) k[i];
	}
	return (s * 11) % mapSize;
}

bool prime(int p) {
	int sqt = sqrt(p);
	int i = 2;
	while (i < sqt) {
		if (p % i == 0) {
			return false;
		}
		i++;
	}
	return true;
}

void hashMap::getClosestPrime() {
	int d = mapSize * 2 + 1;
	while (prime(d)) {
		d += 1;
	}
	d -= 1;
	mapSize = d;
}

void hashMap::reHash() {
	int s = mapSize;
	hashNode **temp = map;
	getClosestPrime();
	map = new hashNode*[mapSize];
	for (int i = 0; i < mapSize; i++) {
		map[i] = new hashNode();
	}
	for (int i = 0; i < s; i++) {
		if (temp[i]->keyword != "") {
			addNode(temp[i]);
		}
	}
}

int hashMap::collHash1(int i) {
	if (i == mapSize - 1) {
		i = 0;
	} else {
		i++;
	}
	return i;
}

int hashMap::collHash2(int i) {
	if (mapSize - i - 1 >= 6) {
		i += 6;
	} else {
		i = 6 - (mapSize - i - 1);
	}
	return i;
}

//int hashMap::findKey(string k) {
//	int i;
//	if (h1) {
//		i = calcHash(k);
//	} else {
//		i = calcHash2(k);
//	}
//	int circle = i;
//	if (map[i]->keyword != k) {
//		while (map[i]->keyword != k) {
//			if (c1) {
//				collHash1(i);
//				if (i == circle) {
//					return -1;
//				}
//			} else {
//				collHash2(i);
//				if (i == circle) {
//					return -1;
//				}
//			}
//		}
//	}
//	return i;
//}

int hashMap::findKey(string k) {
	int i;
	if (h1) {
		i = calcHash(k);
	} else {
		i = calcHash2(k);
	}
	int circle = i;
	if (map[i]->keyword == k) {
		return i;
	} else {
		while (map[i]->keyword != k) {
			if (c1) {
				collHash1(i);
				if (i == circle) {
					return -1;
				}
			} else {
				collHash2(i);
				if (i == circle) {
					return -1;
				}
			}
		}
	}
	return i;
}

void hashMap::printMap() {
	for (int i = 0; i < mapSize; i++) {
		cout << map[i]->keyword << ": ";
		for (int j = 0; j < map[i]->valuesSize; j++) {
			cout << map[i]->values[j] << ", ";
		}
		cout << endl;
	}
}

//int main() {
//	hashMap test = hashMap(1, 1);
//	test.addKeyValue("a", "hello");
//	test.addKeyValue("a", "bye");
//	test.addKeyValue("a", "help");
//	test.printMap();
//}

