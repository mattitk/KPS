#pragma once


#include "../includes.h"

#include "route.h"

#include "../bot_interface.h"

#define prnt std::cout<<

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


class My_bot_kauppila2 : public Bot {
public:
	signed long _c[9][9][999];
	Route _r;

	My_bot_kauppila2(){
		init();
		if(!load_connections()) write_connections();
	}

	virtual bool am_i_learning(){
		return true;
	}

	virtual void set_value(signed int value){
		_r.SetValue(value);

		// learning...........
		for(ConnectionCursor c : _r.getConnections()){
			_c[c.a][c.b][c.row] += value;
		}
		printf("\nValue set! value %d\n", value);
		write_connections();
		//getch();
	}

	virtual std::string get_name(){
		return "oLLi3";
	}

	virtual int get_throw(int round){
		int col=0;
		int col2=0;
		if(!round)
			return rand()%3;

		if(opp_throw[round-1]==0 && own_throw[round-1]==0)
			col=0;
		else if(opp_throw[round-1]==0 && own_throw[round-1]==1)
			col=1;
		else if(opp_throw[round-1]==0 && own_throw[round-1]==2)
			col=2;
		else if(opp_throw[round-1]==1 && own_throw[round-1]==0)
			col=3;
		else if(opp_throw[round-1]==1 && own_throw[round-1]==1)
			col=4;
		else if(opp_throw[round-1]==1 && own_throw[round-1]==2)
			col=5;
		else if(opp_throw[round-1]==2 && own_throw[round-1]==0)
			col=6;
		else if(opp_throw[round-1]==2 && own_throw[round-1]==1)
			col=7;
		else if(opp_throw[round-1]==2 && own_throw[round-1]==2)
			col=8;

		int best_x=0;
		int best_value = 0;
		for(int x=0;x<9;x++){
			if(_c[col][x][round-1] > best_value){
				best_value = _c[col][x][round-1];
				best_x = x;
			}
		}
		_r.AddConnection(col,best_x,round-1);
		switch(best_x){
			case KK:
				return ROCK;
				break;
			case KS:
				return ROCK;
				break;
			case KP:
				return ROCK;
				break;
			case SK:
				return SCISSORS;
				break;
			case SS:
				return SCISSORS;
				break;
			case SP:
				return SCISSORS;
				break;
			case PK:
				return PAPER;
				break;
			case PS:
				return PAPER;
				break;
			case PP:
				return PAPER;
				break;
			default:
				return rand()%3;
				break;
		}
	}


	void initialize_connections(){
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				for(int k=0;k<999;k++)
					_c[i][j][k] = rand()%INITIAL_CHARGE;
	}

	signed int load_connections(){
		FILE *f = fopen("oLLi3.connections", "r");
		if(!f) return 0;
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				for(int k=0;k<999;k++)
						fscanf(f, "%ld\n", &_c[i][j][k]);
		fclose(f);
	}


	int write_connections(){
		FILE *f = fopen("oLLi3.connections", "w");
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				for(int k=0;k<999;k++)
						fprintf(f, "%ld\n", _c[i][j][k]);
		fclose(f);
	}

	int init(){
		initialize_connections();
		return 1;
	}

};

