
#ifndef LARTICLE_H_INCLUDED
#define LARTICLE_H_INCLUDED

#include "constants.h"
typedef struct
{
	float r;
	float m;
	float x;
	float y;
	float vx;
	float vy;
	float ax;
	float ay;
	float angle;
	float anglespeed;
	int color[4];
	int state;


	int alive;
	int time;

	float health;

	int connections_length;
	float potentials[NEURONS_AMOUNT];
	float errors[NEURONS_AMOUNT];
	int connections[NEURONS_CONNECTIONS][2];
	float weights[NEURONS_CONNECTIONS];
}Larticle;

void Larticle_Collide(Larticle *larticle1, Larticle *larticle2);
void Larticle_Gravitate(Larticle *larticle);

void Larticle_Print(Larticle *larticle);
void Larticle_Set_Potential(Larticle *larticle, int i, float value);
int Larticle_Test_Connection(Larticle *larticle, int i, int n);
int Larticle_Add_Connection(Larticle *larticle, int i, int j, float weight);
void Larticle_Add_Error(Larticle *larticle, int i, float error);
void Larticle_Set_Error(Larticle *larticle, int i, float error);
void Larticle_Reset(Larticle *larticle);
float Larticle_Calculate(Larticle *larticle, int i);
void Larticle_Calculate_All(Larticle *larticle);
void Larticle_Create_Connections(Larticle *larticle);
void Larticle_Remove_Connection(Larticle *larticle, int i);
void Larticle_Heridity(Larticle *larticle1, Larticle *larticle2);
void Larticle_Change_Connection(Larticle *larticle, int i, float weight);
#endif
