/***************************************************
Materia:	Gráficas Computacionales
Tarea:	    6 - Isosuperficies
Fecha:		8 de octubre del 2012
Autor:      Marco Chavez
***************************************************/

#include "Punto.h"
#include <stdio.h>

Punto::Punto(float nuevaX, float nuevaY, float nuevaZ, int nuevaR, int nuevaG, int nuevaB, float nuevaVx, float nuevaVy){
	x=nuevaX;
	y=nuevaY;
	z=nuevaZ;
	r=nuevaR;
	g=nuevaG;
	b=nuevaB;
	vx=nuevaVx;
	vy=nuevaVy;
	fixed = false;
}

Punto::Punto(){}

Punto::~Punto(void){
}

float Punto::getX(){
	return x;
}

float Punto::getY(){
	return y;
}

float Punto::getZ(){
	return z;
}

void Punto::setXYZ(float nuevaX, float nuevaY, float nuevaZ){
	x=nuevaX;
	y=nuevaY;
	z=nuevaZ;
}


int Punto::getR(){
	return r;
}

int Punto::getG(){
	return g;
}

int Punto::getB(){
	return b;
}

void Punto::setColor(int nuevaR, int nuevaG, int nuevaB){
	r=nuevaR;
	g=nuevaG;
	b=nuevaB;
}

float Punto::getVx(){
	return vx;
}

float Punto::getVy(){
	return vy;
}

void Punto::setVx(float nuevoVx){
	vx=nuevoVx;
}

void Punto::setVy(float nuevoVy){
	vy=nuevoVy;
}

bool Punto::isFixed(){
	return fixed;
}

void Punto::setFixed(bool nFixed){
	fixed = nFixed;
}