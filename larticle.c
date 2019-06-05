#include "larticle.h"

void Larticle_Print(Larticle *larticle)
{
    printf("Larticle: \n\n");
    printf("Connections Length: %d\n\n", larticle->connections_length);
    printf("Potentials: \n\n");
    for (int i=0; i<NEURONS_AMOUNT; i++)
    {
        printf("%d:  %f\n",i,larticle->potentials[i]);
    }
    printf("\nConnections: \n\n");
    for (int i=0; i<NEURONS_CONNECTIONS; i++)
    {
        printf("%d->%d:  %f\n",larticle->connections[i][0],larticle->connections[i][1],larticle->weights[i]);
    }
}

void Larticle_Set_Potential(Larticle *larticle, int i, float value)
{
    larticle->potentials[i] = value;
}

int Larticle_Test_Connection(Larticle *larticle, int i, int n)
{
    int t = 1;
    n -= 1;
    if (n>0)
    {
        for (int j=0; j<larticle->connections_length+1; j++)
        {
            if (i==larticle->connections[j][1])
            {
                t = Larticle_Test_Connection(larticle, larticle->connections[j][0], n);
                if (t!=1)
                {
                    break;
                }
            }
        }
    }
    else
    {
        t = 0;
    }
    return t;
}
int Larticle_Add_Connection(Larticle *larticle, int i, int j, float weight)
{
	if (i != j && larticle->connections_length < NEURONS_CONNECTIONS -1)
	{
		larticle->connections_length += 1;
		larticle->connections[larticle->connections_length][0] = i;
		larticle->connections[larticle->connections_length][1] = j;
		larticle->weights[larticle->connections_length] = weight;
		if (!Larticle_Test_Connection(larticle,j,5))
		{
			larticle->connections[larticle->connections_length][0] = 0;
			larticle->connections[larticle->connections_length][1] = 0;
			larticle->weights[larticle->connections_length] = 0.0f;
			larticle->connections_length -= 1;
		return 0;
		}
		return 1;
	}
	else{return 0;}
}

void Larticle_Remove_Connection(Larticle *larticle, int i)
{
	if (i <= larticle->connections_length && i != -1)
	{
		larticle->connections[i][0] = larticle->connections[larticle->connections_length][0];
		larticle->connections[i][1] = larticle->connections[larticle->connections_length][1];

		larticle->weights[i] = larticle->weights[larticle->connections_length];
		larticle->connections_length -= 1;
	}
}
void Larticle_Change_Connection(Larticle *larticle, int i, float weight)
{
	if (i <= larticle->connections_length && i != -1)
	{
		larticle->weights[i] = weight;
	}
}

void Larticle_Add_Error(Larticle *larticle, int i, float error)
{
    larticle->errors[i] += error;
}

void Larticle_Set_Error(Larticle *larticle, int i, float error)
{
    larticle->errors[i] = error;
}
void Larticle_Reset(Larticle *larticle)
{
    for (int i=0; i<NEURONS_AMOUNT; i++)
    {
        larticle->potentials[i] = 0;
        larticle->errors[i] = 0.0;
        larticle->connections_length = -1;
    }
}

float Larticle_Calculate(Larticle *larticle, int i)
{
    float x = 0.0f;
    int t = 0;
    for (int j=0; j<larticle->connections_length+1; j++)
    {
        if (i==larticle->connections[j][1])
        {
            t = 1;
            x += larticle->weights[j] * Larticle_Calculate(larticle, larticle->connections[j][0]);
        }
    }
    if (t==1)
    {
    	if (x > - 50)
    	{
        	x = (float)1.0f/(1.0f+exp(-x));
        }
        else
        {
        	x = 0.0f;
        }
        larticle->potentials[i] = x;
        return x;
    }
    else
    {
        return larticle->potentials[i];
    }
}
void Larticle_Calculate_All(Larticle *larticle)
{
    for (int i=0; i< NEURONS_AMOUNT; i++)
    {
        Larticle_Calculate(larticle,i);
    }
}

void Larticle_Correct(Larticle *larticle, int i)
{
    Larticle_Calculate_All(larticle);
    float gradient = (larticle->errors[i] * larticle->potentials[i] * (1 - larticle->potentials[i]));
    for (int j=0; j<larticle->connections_length+1;j++)
    {
        if (i==larticle->connections[j][1])
        {
            larticle->weights[j] += (NEURONS_LEARNINGRATE * gradient * larticle->potentials[larticle->connections[j][0]]);
            larticle->errors[larticle->connections[j][0]] += gradient * larticle->weights[j];
            Larticle_Correct(larticle,larticle->connections[j][0]);
        }
    }
    larticle->errors[i] = 0.0f;
    Larticle_Calculate(larticle,i);
}

void Larticle_Create_Connections(Larticle *larticle)
{
	int amount = ((int)rand()%LARTICLE_START_CONNECTIONS);
	for (int i=0; i<amount; i++)
	{
		int t = 0;
		int test = 0;
		while (t == 0 && test < 200)
		{
			test += 1;
			int tt = 1;
			int i1 = ((int)rand()%NEURONS_AMOUNT);
			int i2 = ((int)rand()%NEURONS_AMOUNT);
			if (i1==i2)
			{
				tt = 0;
			}
			for (int j=0; j< larticle->connections_length;j++)
			{
				if (i1==larticle->connections[j][0]&&i2==larticle->connections[j][1])
				{
					tt = 0;
				}
			}
			float weight = ((float)(rand()%(2*NEURONS_WEIGHT_SIZE) - NEURONS_WEIGHT_SIZE)/NEURONS_WEIGHT_SCALE);
			if (tt==1)
			{
				t = Larticle_Add_Connection(larticle,i1,i2,weight);
			}
		}

	}
}

void Larticle_Gravitate(Larticle *larticle)
{
	float dx = (float)(larticle->x - UNIVERSE_SIZE / 2.0f);
	float dy = (float)(larticle->y - UNIVERSE_SIZE / 2.0f);
	if (dx == 0.0f)
	{
		dx = 0.1f;
	}
	if (dy == 0.0f)
	{
		dy = 0.1f;
	}
	float fx = (float)(-dx / ((float)UNIVERSE_FORCE) * (dx * dx + dy * dy));
	float fy = (float)(-dy / ((float)UNIVERSE_FORCE) * (dx * dx + dy * dy));
	larticle->ax = fx;
	larticle->ay = fy;
}

void Larticle_Heridity(Larticle *larticle1, Larticle *larticle2)
{
	for (int i = 0; i < larticle1->connections_length +1; i++)
	{
		larticle2->connections[i][0] = larticle1->connections[i][0];
		larticle2->connections[i][1] = larticle1->connections[i][1];
		larticle2->weights[i] = larticle1->weights[i];
	}
	larticle2->connections_length = larticle1->connections_length;
	int mr = rand() % NEURON_MUTATIONRATE;
	for (int m = 0; m < mr; m++)
	{
		int r = rand() % 102;
		if (r < 33)
		{
			int ri = rand()%NEURONS_AMOUNT;
			int rj = rand()%NEURONS_AMOUNT;
			float rweight = ((float)(rand()%(2*(int)NEURONS_WEIGHT_SIZE) - (float)NEURONS_WEIGHT_SIZE)
			/((float)NEURONS_WEIGHT_SCALE));
			Larticle_Add_Connection(larticle2, ri, rj, rweight);
		}
		else
		{
			if (r < 66)
			{
				if (larticle2->connections_length > 0)
				{
					int ri = rand()%larticle2->connections_length;
					Larticle_Remove_Connection(larticle2,ri);
				}
			}
			else
			{
				if (r < 99)
				{
					if (larticle2->connections_length > 0)
					{
						int ri = rand()%larticle2->connections_length;
						float rweight = ((float)(rand()%(2*(int)NEURONS_WEIGHT_SIZE) -
						(float)NEURONS_WEIGHT_SIZE)/((float)NEURONS_WEIGHT_SCALE));
						Larticle_Change_Connection(larticle2,ri,rweight);
					}
				}
				else
				{
					Larticle_Create_Connections(larticle1);
				}
			}
		}
	}
}


void Larticle_Collide(Larticle *larticle1, Larticle *larticle2)
{
	float anglespeed = (float)((larticle1->anglespeed - larticle2->anglespeed)/2.0);
	larticle1->anglespeed = anglespeed;
	larticle2->anglespeed = -anglespeed;
	float m1 = (float)(larticle1->m);
        float m2 = (float)(larticle2->m);
        float cosY = (float)((larticle1->x - larticle2->x) / (larticle1->r + larticle2->r));
        float sinY = (float)((larticle1->y - larticle2->y) / (larticle1->r + larticle2->r));
        float v1x = (float)(larticle1->vx);
        float v1y = (float)(larticle1->vy);
        float v2x = (float)(larticle2->vx);
        float v2y = (float)(larticle2->vy);
        float dc = (0.1f);
	larticle1->vx = (float)(LARTICLE_COLISSION_MULTIPLYER*((v1x * cosY + v1y * sinY) * (m1 - m2) + 2.0f * m2 * (v2x * cosY + v2y * sinY)) * cosY / (m1 + m2) - (v1y * cosY - v1x * sinY) * sinY);
	larticle1->vy = (float)(LARTICLE_COLISSION_MULTIPLYER*((v1x * cosY + v1y * sinY) * (m1 - m2) + 2.0f * m2 * (v2x * cosY + v2y * sinY)) * sinY / (m1 + m2) + (v1y * cosY - v1x * sinY) * cosY);
	larticle2->vx = (float)(LARTICLE_COLISSION_MULTIPLYER*((v2x * cosY + v2y * sinY) * (m2 - m1) + 2.0f * m1 * (v1x * cosY + v1y * sinY)) * cosY / (m1 + m2) - (v2y * cosY - v2x * sinY) * sinY);
	larticle2->vy = (float)(LARTICLE_COLISSION_MULTIPLYER*((v2x * cosY + v2y * sinY) * (m2 - m1) + 2.0f * m1 * (v1x * cosY + v1y * sinY)) * sinY / (m1 + m2) + (v2y * cosY - v2x * sinY) * cosY);

	if (larticle1->x >= larticle2->x)
	{
		larticle1->x += dc;
		larticle2->x -= dc;
	}
	else
	{
		larticle1->x -= dc;
		larticle2->x += dc;
	}
	if (larticle1->y >= larticle2->y)
	{
		larticle1->y += dc;
		larticle2->y -= dc;
	}
	else
	{
		larticle1->y -= dc;
		larticle2->y += dc;
	}
	if(larticle1->time > LARTICLE_TIME && larticle1->potentials[NEURON_EAT] > 0.5f)
	{
		float dh = 1.0f;
		if(((larticle1->state == 2) && (larticle2->state == 1))
		||((larticle1->state == 3)&&(larticle2->state == 2))
		||((larticle1->state == 1)&&(larticle2->state == 3))
		||(larticle1->state == 2&&(larticle2->state == 0))
		)
		{
			if (larticle1->state == 1)
			{
				dh = 0.5f;
			}
			if (larticle2->health>(float)LARTICLE_EAT_DAMAGE*dh)
			{
				larticle2->health -= (float)LARTICLE_EAT_DAMAGE*dh;
				larticle1->health += (float)LARTICLE_EAT_PERCENTAGE*LARTICLE_EAT_DAMAGE*dh;
			}
			else
			{
				larticle1->health += (float)LARTICLE_EAT_PERCENTAGE*larticle2->health;
				larticle2->health = -10.0f;
				larticle2->alive = 0;
			}
		}

	}
	if(larticle1->time > LARTICLE_TIME && larticle1->potentials[NEURON_ATTACK] > 0.5f)
	{
		larticle2->health -= (float)LARTICLE_ATTACK_DAMAGE;
	}
	if(larticle2->time > LARTICLE_TIME && larticle2->potentials[NEURON_EAT] > 0.5f)
	{
		float dh = 1.0f;
		if(((larticle2->state == 2)&&(larticle1->state == 1))
		||((larticle2->state == 3)&&(larticle1->state == 2))
		||((larticle2->state == 1)&&(larticle1->state == 3))
		||(larticle2->state == 2)&&(larticle1->state == 0))
		{
			if (larticle2->state == 1)
			{
				dh = 0.5f;
			}
			if (larticle1->health>(float)LARTICLE_EAT_DAMAGE*dh)
			{
				larticle1->health -= (float)LARTICLE_EAT_DAMAGE*dh;
				larticle2->health += (float)LARTICLE_EAT_PERCENTAGE*LARTICLE_EAT_DAMAGE*dh;
			}
			else
			{
				larticle2->health += (float)LARTICLE_EAT_PERCENTAGE*larticle1->health;
				larticle1->health = -10.0f;
				larticle1->alive = 0;
			}
		}
	}
	if(larticle2->time > LARTICLE_TIME && larticle2->potentials[NEURON_ATTACK] > 0.5f)
	{
		larticle1->health -= (float)LARTICLE_ATTACK_DAMAGE;
	}
}














