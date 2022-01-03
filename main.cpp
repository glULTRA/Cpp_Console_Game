#include <iostream>

char gameMap[4][8] = 
{
    {'!','#','#','#','#','#','#','#'},
    {'#','#','#','@','#','#','#','#'},
    {'#','@','#','#','#','#','$','#'},
    {'@','#','#','#','#','@','#','#'},
};
char actionList[8] = {'w','s','a','d','i','k','j','l'};
char playerPos = gameMap[0][0];
typedef struct{
    int x = 0, y = 0;
} PlayerVector2;
PlayerVector2 playervec2{0,0};

void ShowGameMap();
void UpdateGame(char action);
bool IsUpdateMovementsApplied(int x, int y, char action);
bool IsActionPossible();

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
    //for(int i = 0; i < 4; i++){
    //    for(int j = 0; j < 8; j++)
    //    {
    //        if(action == gameMap[i][j]){
    //            //where is the player ? 
    //            if(IsUpdateMovementsApplied(i, j, action))
    //                return;
    //        }
    //    }
    //}
    if(action == 'l'){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 8; j++)
            {
                if(gameMap[i][j] == '#')
                {
                    if(playervec2.x == i && playervec2.y+1 == j)
                    {
                        gameMap[i][j] = ' ';
                        return;
                    }
                }
            }
        }
    }
    if(action == 'd'){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 8; j++)
            {
                if(gameMap[i][j] == ' ')
                {
                    if(playervec2.x == i && playervec2.y+1 == j)
                    {
                        playervec2.y += 1;
                        gameMap[i][j-1] = ' ';
                        gameMap[i][j] = '!';
                        return;
                    }
                }
            }
        }
    }
    if(action == 'k'){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 8; j++)
            {
                if(gameMap[i][j] == '#')
                {
                    if(playervec2.x + 1 == i && playervec2.y == j)
                    {
                        gameMap[i][j] = ' ';
                        return;
                    }
                }
            }
        }
    }
    if(action == 's'){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 8; j++)
            {
                if(gameMap[i][j] == ' ')
                {
                    if(playervec2.x + 1 == i && playervec2.y == j)
                    {
                        playervec2.x += 1;
                        gameMap[i-1][j] = ' ';
                        gameMap[i][j] = '!';
                        return;
                    }
                }
            }
        }
    }

    if(action == 'w'){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 8; j++)
            {
                if(gameMap[i][j] == ' ')
                {
                    if(playervec2.x - 1 == i && playervec2.y == j)
                    {
                        playervec2.x -= 1;
                        gameMap[i+1][j] = ' ';
                        gameMap[i][j] = '!';
                        return;
                    }
                }
            }
        }
    }

    if(action == 'i'){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 8; j++)
            {
                if(gameMap[i][j] == ' ')
                {
                    if(playervec2.x - 1 == i && playervec2.y == j)
                    {
                        gameMap[i][j] = ' ';
                        return;
                    }
                }
            }
        }
    }

    if(action == 'j'){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 8; j++)
            {
                if(gameMap[i][j] == '#')
                {
                    if(playervec2.x == i && playervec2.y - 1 == j)
                    {
                        gameMap[i][j] = ' ';
                        return;
                    }
                }
            }
        }
    }
    if(action == 'a'){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 8; j++)
            {
                if(gameMap[i][j] == ' ')
                {
                    if(playervec2.x == i && playervec2.y - 1 == j)
                    {
                        playervec2.y -= 1;
                        gameMap[i][j+1] = ' ';
                        gameMap[i][j] = '!';
                        return;
                    }
                }
            }
        }
    }
}

bool IsUpdateMovementsApplied(int x, int y, char action){
    if(action == 'l')
    {
        std::cout << x << ' ' << y << std::endl;
        gameMap[x][y] = ' '; 
        return true;
        action = ' ';
    }

    return false;
}

bool IsActionPossible(){
    return false;
}