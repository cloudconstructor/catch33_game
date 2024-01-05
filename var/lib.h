/* ==========================================
Filename: lib.h
Author: George Droulias
Email: d.cloud.constructor@gmail.com
Created: 2023-1-3
Updated: 2024-1-3
Version: 0.1 
Description: Lib file for catch33 game. Contains all functions. Made for learning purposes
============================================*/



#pragma once


bool openFileForReading(const string& filename) {
    // scorefile.open(filename, ios::in);
    scorefile.open(filename);
        return scorefile.is_open();
}


int readFromFile() {
    int textscore;

    if (openFileForReading("var/highscore.txt")) {
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


void writeToOutputFile(const int& content) {
    if (openFileForReading("var/highscore.txt")) {
        // int c = 22;
        // Reset the file position to the beginning
        scorefile.clear(); // Clear any error flags
        scorefile.seekg(0, ios::beg);
        scorefile << content << endl;
        scorefile.close(); // Close the file
    } else {
        cerr << "Failed to open the file." << endl;
    }  
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
        if(heroPosition < (GAME_WIDTH-HERO_WIDTH) ) {
            heroPosition = heroPosition+HEROPSPEED;
            clearCharacter(heroPosition, HERO_Y, 0);
        }
    }

    
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
    
    
    if(oldy>1){
        gotoxy(randcords[id] , oldy);    
        cout << " " << endl;
    }

    gotoxy(randcords[id] , ypos);
    if(rotation == 1) cout << "|" << endl;
    if(rotation == 2) cout << "\\" << endl;
    if(rotation == 3) cout << "-" << endl;
    if(rotation == 4) cout << "/" << endl;
        
    
}

// erase the enemy and refresh x position
void resetEnemy(int id, int enemyYPos){
    gotoxy(randcords[id] , enemyYPos-1);    
    cout << " " << endl;
    refreshRandomCord(id);
}

// Reset everything
void initGame(){
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


void SuccessSound(){
    Beep(500, 100);  
}

void FailSound(){
    Beep(370, 100);  
}

void introSound(){
    Beep(500, 700);
    // Sleep(10);
    // Beep(500, 80);
    // Beep(500, 80);
    Beep(800, 700);

}
