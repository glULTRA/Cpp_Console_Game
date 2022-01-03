#include <iostream>
#include <cmath>

#if (_MSC_VER >= 1200)
    #include <Windows.h>
#else
    #include <windows.h>
#endif

// Orginal Map
char gameMap[4][8] = 
{
    {'!','#','#','#','#','#','#','#'},
    {'#','#','#','@','#','#','#','#'},
    {'#','@','#','#','#','#','$','#'},
    {'@','#','#','#','#','@','#','#'},
};

// Player Position
int xpos = 0;
int ypos = 0;

int score = 0;
bool isWinTheGame = false;

void ShowGameMap();
void UpdateGame(char action);
void Movements(int x, int y, int xDir, int yDir);
void BreakDir(int x, int y, int xDir, int yDir);
void SearchForBlockGravity();

int main()
{
    ShowGameMap();
    GameLoop:
        /* <----- Update -----> */
        char action;
        std::cout << "Action :";
        std::cin >> action;
        if(isWinTheGame){
            std::cout << "\n\nGG Won !";
            return EXIT_SUCCESS;
        }
        UpdateGame(action);
        /* <----- Render -----> */
        // Clear
        system("cls");
        // Draw
        ShowGameMap();
    goto GameLoop;

}

void ShowGameMap(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            std::cout << gameMap[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void UpdateGame(char action)
{
    // User Input
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            /* 4 direction to go with w,a,s,d */
            if(action == 'd')
                Movements(i , j, 1, 0);
            if(action == 'a')
                Movements(i , j,-1, 0);
            if(action == 's')
                Movements(i , j, 0, 1);
            if(action == 'w')
                Movements(i , j, 0,-1);

            /* 4 Way to break i,j,k,l */
            if(action == 'i')
                BreakDir(i, j, 0,-1);
            if(action == 'k')
                BreakDir(i, j, 0, 1);
            if(action == 'j')
                BreakDir(i, j,-1, 0);
            if(action == 'l')
                BreakDir(i, j,+1, 0);
        }
    }
    // Fix Block Gravity.
    SearchForBlockGravity();


}

void Movements(int x, int y, int xDir, int yDir)
{
    if(gameMap[x][y] == ' ' || gameMap[x][y] == '$')
    {
        if(xpos+xDir == y && ypos+yDir == x)
        {
            if(gameMap[x][y] == '$')  isWinTheGame = true;
            xpos += xDir;
            ypos += yDir;
            gameMap[x-yDir][y-xDir] = ' ';
            gameMap[x][y] = '!';
        }
    }
}
void BreakDir(int x, int y, int xDir, int yDir)
{
    if(gameMap[x][y] == '#')
    {
        if(xpos + xDir == y && ypos + yDir == x)
        {
            // Check if block is above.
            if(gameMap[x-1][y] == '@'){
                gameMap[x-1][y] = ' '; 
                gameMap[x][y] = '@';
                return; 
            }
            gameMap[x][y] = ' ';
        }
    }
}

void SearchForBlockGravity(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            if(gameMap[i][j] == '@'){
                if(gameMap[i+1][j] == ' '){
                    gameMap[i][j] = ' ';
                    gameMap[i+1][j] = '@';
                }
            }
        }
    }
}