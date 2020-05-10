/*
 * lab7main.cpp
 *
 *  Created on: Nov 24, 2019
 *      Author: Brett Wagner
 */



#include "makeSeuss.hpp"
#include "hashMap.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;


int main(){
	srand(time(0));
	makeSeuss("DrSeuss.txt", "h1c1.txt", 1,1);
	makeSeuss("DrSeuss.txt", "h1c2.txt", 1,0);
	makeSeuss("DrSeuss.txt", "h2c2.txt", 0,0);
	makeSeuss("DrSeuss.txt", "h2c1.txt", 0,1);
}



