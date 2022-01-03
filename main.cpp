#include <iostream>

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

void ShowGameMap();
void UpdateGame(char action);
void Movements(int x, int y, int xDir, int yDir);
void BreakDir(int x, int y, int xDir, int yDir);

int main()
{
    ShowGameMap();
    GameLoop:
        /* <----- Update -----> */
        char action;
        std::cout << "Action :";
        std::cin >> action;
        UpdateGame(action);
        /* <----- Render -----> */
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
}

void Movements(int x, int y, int xDir, int yDir)
{
    if(gameMap[x][y] == ' ' || gameMap[x][y] == '$')
    {
        if(xpos+xDir == y && ypos+yDir == x)
        {
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
        if(xpos + xDir == y && ypos + yDir == x)
            gameMap[x][y] = ' ';
}