/* ==========================================
Filename: header.h
Author: George Droulias
Email: d.cloud.constructor@gmail.com
Created: 2023-1-3
Updated: 2024-1-3
Version: 0.1 
Description: Header file for catch33 game. Made for learning purposes
============================================*/



#pragma once


#include <iostream>
#include <fstream>
#include <iomanip>  
#include <windows.h>
#include <string>



using namespace std;
fstream scorefile;



#define GAME_WIDTH 55
#define GAME_HEIGHT 20
#define HERO_X_START 2
#define HEROPSPEED  1
#define HERO_WIDTH  3 //(+1) starting poing
#define HERO_Y  (GAME_HEIGHT - 2)
#define ENEMY_START_SPEED 13 //smaller = faster
#define HARDER_EVERY 10 //it will speed up after 33 catches
#define LIVES 10




int randcords[4];
int gameState = 0; // 0 menu , 1 playing, 2 game over 
int heroXpos = HERO_X_START;
int heroYPos = HERO_Y;
int enemySpeed = ENEMY_START_SPEED;
int enemyYPos1 = 2;
int enemyYPos2 = 2; 
int enemyYPos3 = 2; 
int enemyYPos4 = 2;

int enemy_counter = 0;
int enemies = 1;
int step_counter = 0;
int score = 0;
int highscore = 0;
int lives = 10;

int catch_counter = 0;
int game_level = 1;