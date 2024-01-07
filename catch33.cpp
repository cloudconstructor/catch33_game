/* ==========================================
Filename: catch33.cpp
Author: George Droulias
Email: d.cloud.constructor@gmail.com
Created: 2023-12-29
Updated: 2024-1-3
Version: 0.1 
Description: Main file for catch33 game. Made for learning purposes
Game Purpose: Catch as many of the falling spinning things before you run out of lives in order to beat the highscore

============================================*/

#include "var/header.h"
#include "var/lib.h"


int main(){

    initGame();
    introSound();
    
    int rotation1 = 0; // a flag to give rotation animation to enemies
    int rotation2 = 0; // a flag to give rotation animation to enemies
    int rotation3 = 0; // a flag to give rotation animation to enemies
    int rotation4 = 0; // a flag to give rotation animation to enemies
    
    while(true){

        if(gameState == 1){
            heroXpos = detectKeyPress(heroXpos);
            
            // Draw hero
            gotoxy(heroXpos, heroYPos);
            cout << "|__|" << endl;

        
            
            // every enemyspeed loops the position of enemies is refreshed
            if(step_counter == enemySpeed) {
                

                // reset the counter
                step_counter = 0;

                // refresh the enemies
                if(enemies >= 1) {
                    if((randcords[0] >= heroXpos && randcords[0] <= heroXpos+HERO_WIDTH) && enemyYPos1 == heroYPos){
                        resetEnemy(0, enemyYPos1);
                        enemyYPos1 = 2;
                        score++;
                        catch_counter++;
                        SuccessSound();
                    } else if(enemyYPos1 == GAME_HEIGHT){
                        resetEnemy(0, enemyYPos1);
                        enemyYPos1 = 2;
                        lives--;
                        FailSound();
                    } else {
                        drawEnemy(0, enemyYPos1, rotation1);
                        enemyYPos1++;
                        if(rotation1 == 4) rotation1 = 1;
                        else rotation1++;
                    }
                    
                }

                if(enemies >= 2) {
                    
                    if((randcords[1] >= heroXpos && randcords[1] <= heroXpos+HERO_WIDTH) && enemyYPos2 == heroYPos){
                        resetEnemy(1, enemyYPos2);
                        enemyYPos2 = 2;
                        score++;
                        catch_counter++;
                        SuccessSound();
                    } else if(enemyYPos2 == GAME_HEIGHT){
                        resetEnemy(1, enemyYPos2);
                        enemyYPos2 = 2;
                        lives--;
                        FailSound();
                    } else {
                        drawEnemy(1, enemyYPos2, rotation2);
                        enemyYPos2++;
                        if(rotation2 == 4) rotation2 = 1;
                        else rotation2++;
                    }
                    
                }

                if(enemies >= 3) {
                    if((randcords[2] >= heroXpos && randcords[2] <= heroXpos+HERO_WIDTH) && enemyYPos3 == heroYPos){
                        resetEnemy(2, enemyYPos3);
                        enemyYPos3 = 2;
                        score++;
                        catch_counter++;
                        SuccessSound();
                    } else if(enemyYPos3 == GAME_HEIGHT){
                        resetEnemy(2, enemyYPos3);
                        enemyYPos3 = 2;
                        lives--;
                        FailSound();
                    } else {
                        drawEnemy(2, enemyYPos3, rotation3);
                        enemyYPos3++;
                        if(rotation3 == 4) rotation3 = 1;
                        else rotation3++;
                    }
                }

                if(enemies >= 4) {
                    if((randcords[3] >= heroXpos && randcords[3] <= heroXpos+HERO_WIDTH) && enemyYPos4 == heroYPos){
                        resetEnemy(3, enemyYPos4);
                        enemyYPos4 = 2;
                        score++;
                        catch_counter++;
                        SuccessSound();
                    } else if(enemyYPos4 == GAME_HEIGHT){
                        resetEnemy(3, enemyYPos4);
                        enemyYPos4 = 2;
                        lives--;
                        FailSound();
                    } else {
                        drawEnemy(3, enemyYPos4, rotation4);
                        enemyYPos4++;
                        if(rotation4 == 4) rotation4 = 1;
                        else rotation4++;
                    }
                }
            } else {
                step_counter++;
            }

            // Number of enemies on screen at the start of the game
            if(enemy_counter == 55 && enemies<4){
                enemy_counter =0;
                enemies++;
            } else {
                enemy_counter++;
            }

            
            // make game harder
            if(catch_counter == HARDER_EVERY){
                catch_counter = 0;
                game_level++;
                enemySpeed--;
            }

            // Detect game over
            if(lives <= 0){
                gameState = 2;
            }

            // Print Game Stats
            gotoxy(5, 2);
            cout << "Score: " << setw(3) << setfill('0') << score << endl;

            gotoxy(23, 2);
            cout << "Level: " << setw(3) << setfill('0') << game_level << endl;

            gotoxy(40, 2);
            if(lives <=3) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED);
                cout << "Lives: " << setw(2) << setfill('0') << lives << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            } else {
                cout << "Lives: " << setw(2) << setfill('0') << lives << endl;
            }


            Sleep(20);
            
        }


        // Title Screen
        if(gameState == 0){

            // Game logo
            gotoxy(8, 5);
            cout << "   ___   _   _____  ___        __________" << endl;
            gotoxy(8, 6);
            cout << "  / __\\ /_\\ /__   \\/ __\\ /\\  /\\___ /___ /" << endl;
            gotoxy(8, 7);
            cout << " / /   //_\\\\  / /\\/ /   / /_/ / |_ \\ |_ \\" << endl;
            gotoxy(8, 8);
            cout << "/ /___/  _  \\/ / / /___/ __  / ___) |__) |" << endl;
            gotoxy(8, 9);
            cout << "\\____/\\_/ \\_/\\/  \\____/\\/ /_/ |____/____/" << endl;


            // Highest score recorded
            gotoxy(21,12);
            cout << "Highest score:" << highscore << endl;
            
            // Game menu
            gotoxy(15, 15);
            cout << "Press [A] key to Start game" << endl;
            gotoxy(22, 16);
            cout << "CTRL+C to exit" << endl;


            if (GetAsyncKeyState('A') & 0x8000) {
                initGame();
                gameState = 1;
            }

            Sleep(80);
        }

        // Game over screen
        if(gameState == 2){
            
            gotoxy(24, 9);
            cout << "GAME OVER!" << endl;
            gotoxy(21, 10);
            cout << "Your score was:" << score << endl;
            gotoxy(15, 11);

            // Save highscore
            if(score > highscore){
                writeToOutputFile(score);
            }
            GameOver();
            
            Sleep(5000);
            initGame();
            gameState = 0;

        }
       
    }

    closeFiles();
    return 0;
}