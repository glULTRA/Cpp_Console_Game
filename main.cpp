#include <iostream>

char gameMap[4][8] = 
{
    {'!','#','#','#','#','#','#','#'},
    {'#','#','#','@','#','#','#','#'},
    {'#','@','#','@','#','#','$','#'},
    {'@','#','#','@','#','@','#','#'},
};
char actionList[8] = {'w','s','a','d','i','k','j','l'};
char playerPos = gameMap[0][0];

void ShowGameMap();
void UpdateGame(char action);
void UpdateMovements(char action);

int main()
{
    GameLoop:
        ShowGameMap();
        char action;
        std::cin >> action;
        UpdateGame(action);
    goto GameLoop;

}

void ShowGameMap(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            std::cout << gameMap[i][j] << std::endl;
        }
        std::cout << std::endl;
    }
}
void UpdateGame(char action){
    
}

void UpdateMovements(char action){

}