// textgame1.cpp
// Just a test game to learn some c++ 
// things falling from above and you have to catch them all! Game speeds up every HARDER_EVERY constant val
// made with the worst way possible, no oop at all!

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
int highscore;
int lives = 10;

int catch_counter = 0;
int game_level = 1;


bool openFileForReading(const string& filename) {
    scorefile.open(filename, ios::in);
    return scorefile.is_open();
}


int readFromFile() {
    int textscore;

    if (openFileForReading("highscore.txt")) {
        // Reset the file position to the beginning
        scorefile.clear(); // Clear any error flags
        scorefile.seekg(0, ios::beg);
        scorefile >> textscore;
        scorefile.close(); // Close the file
        
    } else {
        cerr << "Failed to open the file." << endl;
    }

    return textscore;
}


float readFloatFromFile(std::fstream& file) {
    float value;
    file >> value;
    return value;
}

void writeToOutputFile(const string& content) {
    scorefile << content << endl;
}

void closeFiles() {
    scorefile.close();
}


// Moves the cursor to a specific position
BOOL gotoxy(const WORD x, const WORD y) {
    COORD xy;
    xy.X = x;
    xy.Y = y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

// Creates the box
void drawBox(int xmax , int ymax){

    // resetConsoleTextColor();
    // Horizontal
    for(int x = 1; x<=xmax; x++){
        gotoxy(x,0);
        cout << "#";

        gotoxy(x,ymax+1);
        cout << "#";
    }
    // Vertical
    for(int y = 0; y<=ymax+1; y++){
        gotoxy(1,y);
        cout << "#";

        gotoxy(xmax+1,y);
        cout << "#";
    }
    
}

// Clears the old characters to give the illusion of animation
void clearCharacter(int x, int y, int xDir) {
    int oldx;
    if(xDir == 0) oldx = x-1;
    else if(xDir == 1) oldx = x+HERO_WIDTH;

    gotoxy(oldx, HERO_Y);
    if(oldx >0){
        cout << "  " << endl;
    }
    
}

// just a cls for now..
void clearScreen(){
    system("cls");
}

// Move hero
int detectKeyPress(int heroPosition){

    if (GetAsyncKeyState(VK_LEFT) & 0x8001){
        if(heroPosition>HERO_X_START) {
            heroPosition = heroPosition-HEROPSPEED;
            clearCharacter(heroPosition, HERO_Y, 1);
        }
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8001){
        if(heroPosition < GAME_WIDTH-1 ) {
            heroPosition = heroPosition+HEROPSPEED;
            clearCharacter(heroPosition, HERO_Y, 0);
        }
    }

    // Sleep(10);
    return heroPosition;
}

// Fill in the random corrds for the falling things
void createRandomCords(){
    for(int i =0;i<=3;i++){
        randcords[i] = rand() % 53 + 2;
    }
}

//when an enemy falls refresh its position
void refreshRandomCord(int id){
    randcords[id] = rand() % 53 + 2;
}


// Draw the enemy and delete old pos
void drawEnemy(int id, int ypos, int rotation){
    int oldy = ypos-1;
    
    // if(ypos <= GAME_HEIGHT){
        if(oldy>1){
            gotoxy(randcords[id] , oldy);    
            cout << " " << endl;
        }

        gotoxy(randcords[id] , ypos);
        if(rotation == 1) cout << "|" << endl;
        if(rotation == 2) cout << "\\" << endl;
        if(rotation == 3) cout << "-" << endl;
        if(rotation == 4) cout << "/" << endl;
        // else cout << "@" << endl;
        
    // }
}

// erase the enemy and refresh x position
void resetEnemy(int id, int enemyYPos){
    gotoxy(randcords[id] , enemyYPos-1);    
    cout << " " << endl;
    refreshRandomCord(id);
}

// Reset everything
void initGame(){
    // int randcords[4];
    // gameState = 1;
    heroXpos = HERO_X_START;
    heroYPos = HERO_Y;
    enemySpeed = ENEMY_START_SPEED;
    enemyYPos1 = 2;
    enemyYPos2 = 2; 
    enemyYPos3 = 2; 
    enemyYPos4 = 2;

    enemy_counter = 0;
    enemies = 1;
    step_counter = 0;
    score = 0;
    highscore = readFromFile();
    lives = LIVES;
    catch_counter = 0;
    game_level = 1;

    clearScreen();
    drawBox(GAME_WIDTH, GAME_HEIGHT);
    createRandomCords();
}




int main(){

    initGame();
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
                    } else if(enemyYPos1 == GAME_HEIGHT){
                        resetEnemy(0, enemyYPos1);
                        enemyYPos1 = 2;
                        lives--;
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
                    } else if(enemyYPos2 == GAME_HEIGHT){
                        resetEnemy(1, enemyYPos2);
                        enemyYPos2 = 2;
                        lives--;
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
                    } else if(enemyYPos3 == GAME_HEIGHT){
                        resetEnemy(2, enemyYPos3);
                        enemyYPos3 = 2;
                        lives--;
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
                    } else if(enemyYPos4 == GAME_HEIGHT){
                        resetEnemy(3, enemyYPos4);
                        enemyYPos4 = 2;
                        lives--;
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
            if(lives == 0){
                if(score>highscore){
                    writeToOutputFile(to_string(score));
                }
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


            // highscore
            gotoxy(21,12);
            cout << "Highest score:" << highscore << endl;
            

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
            gotoxy(15, 11);
            
            Sleep(5000);
            initGame();
            gameState = 0;

        }


        
    }

    closeFiles();
    return 0;
}