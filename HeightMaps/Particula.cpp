/***************************************************
Materia:	Gráficas Computacionales
Tarea:	    7 - la Telota
Fecha:		22 de octubre del 2012
Autor:      Marco Chavez
***************************************************/
#include <stdio.h>
#include "Particula.h"

Particula::Particula(float x, float y, float z){
	this->posicion[0]=x;
	this->posicion[1]=y;
	this->posicion[2]=z;
}

Particula::Particula(int id,float* posicion){
	this->id=id;
	this->posicion[0]=posicion[0];
	this->posicion[1]=posicion[1];
	this->posicion[2]=posicion[2];
	setPosicion(posicion);
	this->velocidad[0]=0;
	this->velocidad[1]=0;
	this->velocidad[2]=0;
	clearForce();
	this->masa=1;
	calcularColor();
	this->fixed=false;
}

Particula::Particula(){
}

Particula::~Particula(void){
}

int Particula::getID(){
	return this->id;
}

void Particula::calcularColor(){
	int cociente=this->id/255;
	if(cociente<255){
		this->color[0]=0;
		this->color[1]=(unsigned char)cociente;
		this->color[2]=(unsigned char)(this->id%255);
	}
}

unsigned char* Particula::getColor(){
	return this->color;
}

float* Particula::getPosicion(){
	return this->posicion;
}

float* Particula::getPosAnt(){
	return this->posAnterior;
}

float* Particula::getVelocidad(){
	return this->velocidad;
}

float* Particula::getFuerza(){
	return this->fuerza;
}

void Particula::setPosicion(float* posicion){
	this->posAnterior[0]=this->posicion[0];
	this->posAnterior[1]=this->posicion[1];
	this->posAnterior[2]=this->posicion[2];
	this->posicion[0]=posicion[0];
	this->posicion[1]=posicion[1];
	this->posicion[2]=posicion[2];
}

void Particula::setVelocidad(float* velocidad){
	this->velocidad[0]=velocidad[0];
	this->velocidad[1]=velocidad[1];
	this->velocidad[2]=velocidad[2];
}

void Particula::addFuerza(float* fuerza){
	this->fuerza[0]+=fuerza[0];
	this->fuerza[1]+=fuerza[1];
	this->fuerza[2]+=fuerza[2];
}

void Particula::clearForce(){
	this->fuerza[0]=0;
	this->fuerza[1]=0;
	this->fuerza[2]=0;
}

bool Particula::getFixed(){
	return this->fixed;
}

void Particula::setFixed(bool b){
	this->fixed=b;
}

void Particula::addNormal(float* n){
	this->normal[0]+=n[0];
	this->normal[1]+=n[1];
	this->normal[2]+=n[2];
	totalNormales++;
}

float* Particula::getVectorUnitario(){
	float vectorUnitario[3];
	for(int i=0; i<3; i++){
		vectorUnitario[i] = this->normal[i]/totalNormales;
	}
	return vectorUnitario;
}

void Particula::clearNormal(){
	for(int i=0; i<3; i++){
		this->normal[i] = 0;
	}

}

void Particula::Verlet(float dt){
	//xi+1= 2xi – xi-1 + a*dt^2
	if(!this->fixed){
		float a[3];
		float nuevaPos[3];
		for(int i=0; i<3; i++){
			a[i] = this->fuerza[i]/this->masa;
			nuevaPos[i] = this->posicion[i] + (this->posicion[i] - this->posAnterior[i]) + 1 * a[i] * dt * dt;
		}
		this->setPosicion(nuevaPos);
	}
}