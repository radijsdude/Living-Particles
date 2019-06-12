#ifndef LARTICLES_H_INCLUDED
#include "larticles.h"
#endif
void Larticles_Initiate(Larticles *larticles)
{
	larticles->larticles_amount = -1;
	for (int i = 0; i < LARTICLES_START_AMOUNT; i++)
	{
		Larticle p;
		p.r = LARTICLE_SIZE;
		p.m = 5.0f;
		p.x = (float)rand()*UNIVERSE_SIZE/RAND_MAX;
		p.y = (float)rand()*UNIVERSE_SIZE/RAND_MAX;
		p.vx = 0.0f;
		p.vy = 0.0f;
		p.ax = 0.0f;
		p.ay = 0.0f;
		p.color[0] = 0;
		p.color[1] = 0;
		p.color[2] = 0;
		p.color[3] = 255;
		p.angle = (float)(rand()%200 - 100) / 100.0f * M_PI;
		p.anglespeed = 0.0f;
		p.time = LARTICLE_INITIATE_TIME;
		p.state = 0;

		p.health = 1000.0f;
		p.alive = 1;

		p.connections_length = -1;
		for (int i=0; i<NEURONS_AMOUNT; i++)
		{
			p.potentials[i] = NEURONS_START_POTENTIAL;
			p.errors[i] = 0.0f;
		}
		for (int i=0; i<NEURONS_CONNECTIONS; i++)
		{
			p.connections[i][0] = -13.0f;
			p.connections[i][1] = -13.0f;
			p.weights[i] = 0.0f;
		}
		Larticle_Create_Connections(&p);
		Larticles_Add(larticles, p);
	}
	Larticle_Calculate_All(&larticles->larticles[0]);
	Larticle_Print(&larticles->larticles[0]);
}


void Larticles_Add(Larticles *larticles, Larticle larticle)
{
		if (larticles->larticles_amount < LARTICLES_MAX -1)
		{
			larticles->larticles_amount += 1;
			larticles->larticles[larticles->larticles_amount] = larticle;
		}
}

void Larticles_Remove(Larticles *larticles, int i)
{
	larticles->larticles[i] = larticles->larticles[larticles->larticles_amount];
	larticles->larticles_amount -= 1;
}


void Larticles_Doe(Larticles *larticles)
{

	for (int i=0; i<larticles->larticles_amount +1; i++)
	{
		if(larticles->larticles[i].health > 0.0f)
		{
			larticles->larticles[i].time += 1;
			
			Larticle_Gravitate(&larticles->larticles[i]);
			


			larticles->larticles[i].vx += larticles->larticles[i].ax;
			larticles->larticles[i].vy += larticles->larticles[i].ay;

			float sinn = sin(larticles->larticles[i].angle);
			float coss = cos(larticles->larticles[i].angle);

			if (larticles->larticles[i].time > LARTICLE_TIME)
			{
				
				larticles->larticles[i].r = LARTICLE_SIZE + larticles->larticles[i].health / LARTICLE_MAX_HEALTH *
				 LARTICLE_SIZE_SCALE;
				larticles->larticles[i].m = larticles->larticles[i].r;
				larticles->larticles[i].potentials[NEURON_ALIVE] = 1.0f;
				larticles->larticles[i].potentials[NEURON_IN_1] = larticles->larticles[i].potentials[NEURON_OUT_1];
				larticles->larticles[i].potentials[NEURON_IN_2] = larticles->larticles[i].potentials[NEURON_OUT_2];
				larticles->larticles[i].potentials[NEURON_SENSE_ANGLE] = larticles->larticles[i].angle;
				larticles->larticles[i].potentials[NEURON_SENSE_HEALTH] = (float)larticles->larticles[i].health /
				((float)LARTICLE_MAX_HEALTH);
				//larticles->larticles[i].potentials[NEURON_SENSE_ANGLE_SPEED] = larticles->larticles[i].anglespeed;

				Larticle_Calculate_All(&larticles->larticles[i]);
				
				float smax = 0.0f;
				larticles->larticles[i].state = 0;
				if (larticles->larticles[i].potentials[NEURON_STATE_1] > smax)
				{
					larticles->larticles[i].state = 1;
					smax = larticles->larticles[i].potentials[NEURON_STATE_1];
				}
				if (larticles->larticles[i].potentials[NEURON_STATE_2] > smax)
				{
					larticles->larticles[i].state = 2;
					smax = larticles->larticles[i].potentials[NEURON_STATE_2];
				}
				if (larticles->larticles[i].potentials[NEURON_STATE_3] > smax)
				{
					larticles->larticles[i].state = 3;
					smax = larticles->larticles[i].potentials[NEURON_STATE_3];
				}

				if(larticles->larticles[i].state ==1)
				{
					larticles->larticles[i].health += (float)LARTICLES_REGEN;
					larticles->larticles[i].color[0] = 0;
					larticles->larticles[i].color[1] = 0;
					larticles->larticles[i].color[2] = 255;
					if (larticles->larticles[i].potentials[NEURON_ATTACK] > 0.5f)
					{
						larticles->larticles[i].color[1] = 150;
					}
				}
				else
				{
					if(larticles->larticles[i].state == 2)
					{
						larticles->larticles[i].color[0] = 255;
						larticles->larticles[i].color[1] = 0;
						larticles->larticles[i].color[2] = 0;
						if (larticles->larticles[i].potentials[NEURON_ATTACK] > 0.5)
						{
							larticles->larticles[i].color[1] = 150;
						}
					}
					else
					{
						larticles->larticles[i].color[0] = 0;
						larticles->larticles[i].color[1] = 255;
						larticles->larticles[i].color[2] = 0;
						if (larticles->larticles[i].potentials[NEURON_ATTACK] > 0.5)
						{
							larticles->larticles[i].color[0] = 150;
						}
					}
				}

				if (larticles->larticles[i].state != 3 && larticles->larticles[i].state != 0)
				{
					larticles->larticles[i].health -= UNIVERSE_DAMAGE * 
					(float)larticles->larticles[i].connections_length/(float)NEURONS_CONNECTIONS;
				}

				larticles->larticles[i].vx += (1.0f/((float)LARTICLE_SPEED)*(coss*
				(larticles->larticles[i].potentials[NEURON_MOVE_X] - 0.5f) - sinn*
				(larticles->larticles[i].potentials[NEURON_MOVE_Y] - 0.5f)));
				larticles->larticles[i].vy += (1.0f/((float)LARTICLE_SPEED)*(coss*
				(larticles->larticles[i].potentials[NEURON_MOVE_Y] - 0.5f) + sinn*
				(larticles->larticles[i].potentials[NEURON_MOVE_X] - 0.5f)));
				float cx = larticles->larticles[i].x - (float)UNIVERSE_SIZE / 2.0f;
				float cy = larticles->larticles[i].y - (float)UNIVERSE_SIZE / 2.0f;
				larticles->larticles[i].potentials[NEURON_SENSE_GRAVITY] = (cx*cx+cy*cy)/((float)UNIVERSE_SIZE);
				if (cx != 0.0f && cy != 0.0f)
				{
					float cc = sqrt(cy*cy+cx*cx);
					float vx = (1.0f/(((float)LARTICLE_SPEED))*cx/cc*
					(larticles->larticles[i].potentials[NEURON_GRAVITY] - 0.5f));
					float vy = (1.0f/(((float)LARTICLE_SPEED))*cy/cc*
					(larticles->larticles[i].potentials[NEURON_GRAVITY] - 0.5f));
					larticles->larticles[i].vx += vx;
					larticles->larticles[i].vy += vy;


					float vvx = (float)(1.0f/((float)LARTICLE_SPEED)*cy/cc*
					(larticles->larticles[i].potentials[NEURON_TANGENTIAL] - 0.5f));
					float vvy = (float)(-1.0f/((float)LARTICLE_SPEED)*cx/cc*
					(larticles->larticles[i].potentials[NEURON_TANGENTIAL] - 0.5f));
					larticles->larticles[i].vx += vvx;
					larticles->larticles[i].vy += vvy;


					
				}

				if (larticles->larticles[i].potentials[NEURON_SPLIT] > 0.5f &&
				larticles->larticles[i].health > (float)LARTICLE_SPLIT_HEALTH*1.1f)
				{
					larticles->larticles[i].health -= (float)LARTICLE_SPLIT_HEALTH;
					Larticle p;
					p.x = larticles->larticles[i].x - 2.1f*(float)LARTICLE_SIZE*coss;
					p.y = larticles->larticles[i].y - 2.1f*(float)LARTICLE_SIZE*sinn;
					p.r = LARTICLE_SIZE;
					p.m = 5.0f;
					p.vx = larticles->larticles[i].vx;
					p.vy = larticles->larticles[i].vy;
					p.ax = 0.0f;
					p.ay = 0.0f;
					p.color[0] = 0;
					p.color[1] = 0;
					p.color[2] = 0;
					p.color[3] = 255;
					p.angle = (float)(rand()%200 - 100) / 100.0f * M_PI;
					p.anglespeed = 0.0f;
					p.time = 0;
					p.state = 0;

					p.health = (float)LARTICLE_SPLIT_HEALTH*0.9f;
					p.alive = 1;

					p.connections_length = -1;
					for (int i=0; i<NEURONS_AMOUNT; i++)
					{
						p.potentials[i] = (float)NEURONS_START_POTENTIAL;
						p.errors[i] = 0.0f;
					}
					for (int i=0; i<NEURONS_CONNECTIONS; i++)
					{
						p.connections[i][0] = -13.0f;
						p.connections[i][1] = -13.0f;
						p.weights[i] = 0.0f;
					}
					Larticle_Heridity(&larticles->larticles[i], &p);
					Larticles_Add(larticles, p);

				}
			}
			else
			{
				larticles->larticles[i].color[0] = 255;
				larticles->larticles[i].color[1] = 255;
				larticles->larticles[i].color[2] = 255;
			}


			//larticles->larticles[i].anglespeed *= (1.0f - 20.0f * UNIVERSE_FRICTION);
			larticles->larticles[i].angle += (larticles->larticles[i].potentials[NEURON_MOVE_ANGLE] - 0.5f) * M_PI;//larticles->larticles[i].anglespeed;
			if (larticles->larticles[i].angle >= M_PI)
			{
				larticles->larticles[i].angle = -M_PI;
			}
			if (larticles->larticles[i].angle < -M_PI)
			{
				larticles->larticles[i].angle = M_PI;
			}
			
			float see_d = 0.0f;
			float see_a = 0.0f;
			int insight = 0;
			float distance = (float)LARTICLE_VISUAL_RANGE;
			Larticle lsee;
			for (int j=0; j<larticles->larticles_amount +1; j++)
			{
				if(larticles->larticles[j].health>0.0f)
				{
					if (i!=j)
					{
						float dx = larticles->larticles[j].x - larticles->larticles[i].x;
						float dy = larticles->larticles[j].y - larticles->larticles[i].y;
						float dr = larticles->larticles[i].r + larticles->larticles[j].r;
						float d = dx*dx + dy*dy;
						if (d==0.0f)
						{
							d = 0.01f;
						}
						if (d < dr*dr)
						{
							Larticle_Collide(&larticles->larticles[i],&larticles->larticles[j]);
						}
						if (d < LARTICLE_VISUAL_RANGE * LARTICLE_VISUAL_RANGE)
						{
							float drr = 1.0f/d;
							float daa = (atan2(dy,dx) - larticles->larticles[i].angle) / d;
							see_d += drr;
							see_a += daa;

							float D =(larticles->larticles[i].x - larticles->larticles[j].x) *
							(larticles->larticles[i].y + sinn - larticles->larticles[j].y) -
							(larticles->larticles[i].y - larticles->larticles[j].y) *
							(larticles->larticles[i].x + coss - larticles->larticles[j].x);
							float rr = larticles->larticles[j].r + tan(LARTICLE_FOV) *  sqrt(d);
							if (D * D < rr * rr)
							{
								float sign = 1;
								if (sinn < 0.0f)
								{
									sign = -1;
								}
								float Dx1 = (D * sinn + sign * coss * sqrt(rr - D*D));
								float Dx2 = (D * sinn - sign * coss * sqrt(rr - D*D));
								float Dy1 = (D * coss + abs(sinn) * sqrt(rr - D*D));
								float Dy2 = ( - D * coss - abs(sinn) * sqrt(rr - D*D));
								int s = 0;
								if (coss >= 0.0f && Dx1 >= 0.0f)
								{
									if (sinn >= 0.0f && Dy1 >=0.0f)
									{
										s = 1;
									}
									if (sinn < 0.0f && Dy1 < 0.0f)
									{
										s = 1;
									}
								}
								if (coss < 0.0f && Dx1 < 0.0f)
								{
									if (sinn >= 0.0f && Dy1 >=0.0f)
									{
										s = 1;
									}
									if (sinn < 0.0f && Dy1 < 0.0f)
									{
										s = 1;
									}
								}
								if (s == 1)
								{
									insight = 1;
									if (distance < d)
									{
										lsee = larticles->larticles[j];
										distance = d;
									}
								}
							}

						}


					}


				}
				else
				{
					Larticles_Remove(larticles,j);
				}
			}
			if(insight == 1)
			{
				float sangle = atan2(larticles->larticles[i].y - UNIVERSE_SIZE / 2.0f, 
				larticles->larticles[i].x - UNIVERSE_SIZE / 2.0f);
				float langle = atan2(lsee.y - UNIVERSE_SIZE / 2.0f, lsee.x - UNIVERSE_SIZE / 2.0f);
				float dangle = atan2(larticles->larticles[i].y - lsee.y, larticles->larticles[i].x - lsee.x);
				larticles->larticles[i].potentials[NEURON_SEE_ORIENTATION] = langle;
				larticles->larticles[i].potentials[NEURON_SENSE_ORIENTATION] = sangle;
				larticles->larticles[i].potentials[NEURON_SEE_GRAVITY] = lsee.potentials[NEURON_SENSE_GRAVITY] - 
				larticles->larticles[i].potentials[NEURON_SENSE_GRAVITY];
				larticles->larticles[i].potentials[NEURON_SEE_DISTANCE] = distance /
				((float)UNIVERSE_SIZE*(float)UNIVERSE_SIZE);
				larticles->larticles[i].potentials[NEURON_SEE_STATE_1] = (float)lsee.potentials[NEURON_STATE_1];
				larticles->larticles[i].potentials[NEURON_SEE_STATE_2] = (float)lsee.potentials[NEURON_STATE_2];
				larticles->larticles[i].potentials[NEURON_SEE_STATE_3] = (float)lsee.potentials[NEURON_STATE_3];
				larticles->larticles[i].potentials[NEURON_SEE_ANGLE] = dangle - larticles->larticles[i].angle;
				larticles->larticles[i].potentials[NEURON_SENSE_ANGLE] = larticles->larticles[i].angle - langle;
				larticles->larticles[i].potentials[NEURON_SEE_HEALTH] = lsee.health/(larticles->larticles[i].health + 1.0f);
				larticles->larticles[i].potentials[NEURON_SEE] = 1.0f;
			}
			else
			{
				larticles->larticles[i].potentials[NEURON_SEE_ORIENTATION] = 0.0f;
				larticles->larticles[i].potentials[NEURON_SENSE_ORIENTATION] = 0.0f;
				larticles->larticles[i].potentials[NEURON_SEE_GRAVITY] = 0.0f;
				larticles->larticles[i].potentials[NEURON_SEE_DISTANCE] = 0.0f;
				larticles->larticles[i].potentials[NEURON_SEE_STATE_1] = 0.0f;
				larticles->larticles[i].potentials[NEURON_SEE_STATE_2] = 0.0f;
				larticles->larticles[i].potentials[NEURON_SEE_STATE_3] = 0.0f;
				larticles->larticles[i].potentials[NEURON_SEE_ANGLE] = 0.0f;
				larticles->larticles[i].potentials[NEURON_SENSE_ANGLE] = 0.0f;
				larticles->larticles[i].potentials[NEURON_SEE_HEALTH] = 0.0f;
				larticles->larticles[i].potentials[NEURON_SEE] = 0.0f;
			}
			
			larticles->larticles[i].potentials[NEURON_FIELD_DISTANCE] = see_d;
			larticles->larticles[i].potentials[NEURON_FIELD_ANGLE] = see_d;

			float dv = larticles->larticles[i].vx*larticles->larticles[i].vx +
			larticles->larticles[i].vy*larticles->larticles[i].vy;

			if (dv > (float)LARTICLE_MAX_SPEED*(float)LARTICLE_MAX_SPEED)
			{
				float sdv = sqrt(dv);
				larticles->larticles[i].vx = (float)LARTICLE_MAX_SPEED * larticles->larticles[i].vx / sdv;
				larticles->larticles[i].vy = (float)LARTICLE_MAX_SPEED * larticles->larticles[i].vy / sdv;
			}

			larticles->larticles[i].vx *= (1.0f - (float)UNIVERSE_FRICTION);
			larticles->larticles[i].vy *= (1.0f - (float)UNIVERSE_FRICTION);
			larticles->larticles[i].x += larticles->larticles[i].vx;
			larticles->larticles[i].y += larticles->larticles[i].vy;
			if (larticles->larticles[i].health > (float)LARTICLE_MAX_HEALTH)
			{
				larticles->larticles[i].health = LARTICLE_MAX_HEALTH;
			}
		}
		else
		{
			Larticles_Remove(larticles,i);
		}
	}
}
