#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <map>
#include <string>

#include "bot_interface.h"

#define prnt std::cout <<

#define CHARGE_TRESHOLD 1024
#define CHARGE_MAX 65536
#define INITIAL_CHARGE	1024
#define INITIAL_STRENGTH 1024
#define BIAS_CHARGE		512

#define PP 0
#define PK 1
#define PS 2
#define KP 3
#define KK 4
#define KS 5
#define SP 6
#define SK 7
#define SS 8

typedef struct{
	char a,b;
	int row;
}ConnectionCursor;

class Route {
private:
	int _value;
	std::vector<ConnectionCursor> _n;
	public:
	Route(){
		_value = 0;
		}	

	std::vector<ConnectionCursor> getConnections(){
		return _n;
	}

	void Victory(){
		_value = 1;
	}


	void Loss(){
		_value = -1;
	}

	void AddConnection(int a, int b, int row){
		ConnectionCursor c;
		c.a=a;
		c.b=b;
		c.row=row;
	}
};

class oLLi2 : Bot {

	signed long _c[9][9][999];

	oLLi2(){
		init();
	}


	void initializeConnections(){
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				for(int k=0;k<999;k++)
					_c[i][j][k] = INITIAL_CHARGE;
	}


	int init(){
		initializeConnections();
		return 1;
	}

};

