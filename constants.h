

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
//#include <SDL2/SDL_ttf.h>
#include <string.h>

#define SCREEN_X 1260
#define SCREEN_Y 730

#define UNIVERSE_DAMAGE 0.2
#define LARTICLES_MAX 2000
#define LARTICLES_START_AMOUNT 1000
#define UNIVERSE_SIZE 4000.0
#define LARTICLE_COLISSION_MULTIPLYER 1.02
#define UNIVERSE_FORCE 1000000000.0
#define UNIVERSE_FRICTION 0.001
#define UNIVERSE_GRAVITY_WELL 200.0

#define LARTICLE_SPLIT_HEALTH 1100.0
#define LARTICLE_TIME 1000
#define LARTICLE_INITIATE_TIME LARTICLE_TIME - 300
#define LARTICLE_SPEED 0.1
#define LARTICLE_MAX_SPEED 2.0
#define LARTICLE_SIZE 10.0
#define LARTICLE_MAX_HEALTH 2000.0
#define LARTICLE_MAX_ANGLE_SPEED 3.14/24.0
#define LARTICLE_EAT_ANGLE M_PI / 16.0
#define LARTICLE_EAT_DAMAGE LARTICLE_MAX_HEALTH / 10.0
#define LARTICLE_EAT_PERCENTAGE 0.9
#define LARTICLE_ATTACK_DAMAGE LARTICLE_EAT_DAMAGE/5.0
#define LARTICLES_REGEN 0.5
#define LARTICLE_START_CONNECTIONS 20
#define LARTICLE_VISUAL_RANGE LARTICLE_SIZE * 30
#define LARTICLE_SIZE_SCALE 10
#define LARTICLE_FOV M_PI/12.0

#define NEURONS_START_POTENTIAL 0.5
#define NEURONS_AMOUNT 40
#define NEURONS_CONNECTIONS 100
#define NEURONS_WEIGHT_SIZE 100
#define NEURONS_WEIGHT_SCALE 10
#define NEURONS_LEARNINGRATE 1
#define NEURON_MUTATIONRATE 5

#define NEURON_SEE_X 0
#define NEURON_SEE_Y 1
#define NEURON_MOVE_X 2
#define NEURON_MOVE_Y 3
#define NEURON_MOVE_ANGLE 4
#define NEURON_ATTACK 5
#define NEURON_EAT 6
#define NEURON_GRAVITY 7
#define NEURON_TANGENTIAL 8
#define NEURON_SPLIT 9
#define NEURON_ALIVE 10
#define NEURON_STATE_1 11
#define NEURON_STATE_2 12
#define NEURON_STATE_3 13
#define NEURON_FIELD_ORIENTATION 14
#define NEURON_FIELD_DISTANCE 15
#define NEURON_SEE_ORIENTATION 16
#define NEURON_SEE_GRAVITY 17
#define NEURON_SEE_DISTANCE 18
#define NEURON_SEE 19
#define NEURON_FIELD_ANGLE 20
#define NEURON_SEE_ANGLE 21
#define NEURON_SEE_HEALTH 22
#define NEURON_SEE_STATE_1 23
#define NEURON_SENSE_ORIENTATION 24
#define NEURON_SENSE_GRAVITY 25
#define NEURON_SENSE_ANGLE 26
#define NEURON_SENSE_HEALTH 27
#define NEURON_SENSE_ANGLE_SPEED 28
#define NEURON_SEE_STATE_2 29
#define NEURON_SEE_STATE_3 30
#define NEURON_IN_1 31
#define NEURON_IN_2 32
#define NEURON_OUT_1 33
#define NEURON_OUT_2 34


//#define WIDTH 1800
//#define HEIGHT 1200

#endif
