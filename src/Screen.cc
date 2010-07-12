#include "Screen.h"
#include <iostream>

using namespace PF;

typedef unsigned int uint;

Screen::Screen(){
}

void Screen::init(){
	allocateColors();
}

Screen::~Screen(){
	for(uint i=0; i<x; i++)
		delete[] colors[i];
	delete[] colors;
}

int Screen::allocateColors(){
	colors = new Color* [x];
	for(unsigned int i=0;i<(unsigned int)x;i++)
		colors[i]=new Color[y];
	return 0;
}


int Screen::setColor(uint x, uint y, Color c){
	colors[x][y]=c;
	return 0;
}

void Screen::setColor(uint number, const Color& color){
	colors[number % x][number/x]=color;
}
