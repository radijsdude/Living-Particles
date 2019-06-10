#ifndef LARTICLES_H_INCLUDED
#define LARTICLES_H_INCLUDED
#ifndef LARTICLE_H_INCLUDED
#include "larticle.c"
#endif
typedef struct
{
	Larticle larticles[LARTICLES_MAX];
	int larticles_amount;
}Larticles;


void Larticles_Initiate(Larticles *larticles);
void Larticles_Doe(Larticles *larticles);

void Larticles_Add(Larticles *larticles, Larticle larticle);
void Larticles_Remove(Larticles *larticles, int i);
#endif
