#include <iostream>

char gameMap[4][8] = 
{
    {'!','#','#','#','#','#','#','#'},
    {'#','#','#','@','#','#','#','#'},
    {'#','@','#','#','#','#','$','#'},
    {'@','#','#','#','#','@','#','#'},
};
typedef struct{
    int x = 0, y = 0;
} PlayerVector2;
PlayerVector2 playerpos{0,0};

void ShowGameMap();
void UpdateGame(char action);

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
            /* 4 direction with w,a,s,d*/
            if(action == 'd')
            {
                if(gameMap[i][j] == ' ' || gameMap[i][j] == '$')
                {
                    if(playerpos.x == i && playerpos.y+1 == j)
                    {
                        playerpos.y += 1;
                        gameMap[i][j-1] = ' ';
                        gameMap[i][j] = '!';
                        return;
                    }
                }
            }
            
            if(action == 's'){
                if(gameMap[i][j] == ' ' || gameMap[i][j] == '$')
                {
                    if(playerpos.x + 1 == i && playerpos.y == j)
                    {
                        playerpos.x += 1;
                        gameMap[i-1][j] = ' ';
                        gameMap[i][j] = '!';
                        return;
                    }
                }
            }
            if(action == 'w'){
                if(gameMap[i][j] == ' ' || gameMap[i][j] == '$')
                {
                    if(playerpos.x - 1 == i && playerpos.y == j)
                    {
                        playerpos.x -= 1;
                        gameMap[i+1][j] = ' ';
                        gameMap[i][j] = '!';
                        return;
                    }
                }
            }
            if(action == 'a')
            {
                if(gameMap[i][j] == ' ' || gameMap[i][j] == '$')
                {
                    if(playerpos.x == i && playerpos.y - 1 == j)
                    {
                        playerpos.y -= 1;
                        gameMap[i][j+1] = ' ';
                        gameMap[i][j] = '!';
                        return;
                    }
                }
            }

            /* 4 Way to break i,j,k,l */
            if(action == 'i')
            {
                if(gameMap[i][j] == '#')
                {
                    if(playerpos.x - 1 == i && playerpos.y == j)
                    {
                        gameMap[i][j] = ' ';
                        return;
                    }
                }
            }
            if(action == 'k')
            {
                if(gameMap[i][j] == '#')
                {
                    if(playerpos.x + 1 == i && playerpos.y == j)
                    {
                        gameMap[i][j] = ' ';
                        return;
                    }
                }
            }
            if(action == 'j'){
                if(gameMap[i][j] == '#')
                {
                    if(playerpos.x == i && playerpos.y - 1 == j)
                    {
                        gameMap[i][j] = ' ';
                        return;
                    }
                }
            }
            if(action == 'l')
            {
                if(gameMap[i][j] == '#')
                {
                    if(playerpos.x == i && playerpos.y+1 == j)
                    {
                        gameMap[i][j] = ' ';
                        return;
                    }
                }
            }            
        }
    }
}