#include <iostream>
#include <ctime> // to generate random numbers

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
char mapList[3] = {'#', '@', '$'};

// Player Position
int xpos = 0;
int ypos = 0;
int blockLevel = 4;

static int score = 0;
bool isWinTheGame = false;

void GenerateRandomMap();
bool IsMapGoodToPlay();
void ShowGameMap();
void UpdateGame(char action);
bool Movements(int x, int y, int xDir, int yDir);
void BreakDir(int x, int y, int xDir, int yDir);
void SearchForBlockGravity();

int main()
{
    // Play Again
    PlayAgain:
    // Generating random Numbers.
    srand(time(NULL));
    // Generate Random Map and Check The Map Again.
    do{
        GenerateRandomMap();
    }while(!IsMapGoodToPlay());
    
    // Show Game Map.
    ShowGameMap();

    // Starting Game Loop.
    GameLoop:
        /* <----- Update -----> */
        char action;
        std::cout << "Action :";
        std::cin >> action;
        UpdateGame(action);
        /* <----- Render -----> */
        // Clear
        system("cls");
        // Draw
        ShowGameMap();
        if(isWinTheGame){
            static int level = 0;
            score+=5;
            ++level;
            std::cout << "\nGG You Win !\n";
            std::cout << "Score :" << ' ' << score << std::endl;
            std::cout << "Level :" << ' ' << level << std::endl;
            isWinTheGame = false;
            xpos = 0;
            ypos = 0;
            gameMap[0][0] = '!';
            blockLevel++;
            goto PlayAgain;
            return EXIT_SUCCESS;
        }
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
                if(Movements(i , j, 1, 0)) 
                    break;
            if(action == 'a')
                if(Movements(i , j,-1, 0))
                    break;
            if(action == 's')
                if(Movements(i , j, 0, 1))
                    break;
            if(action == 'w')
                if(Movements(i , j, 0,-1))
                    break;

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

bool Movements(int x, int y, int xDir, int yDir)
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
            return true;
        }
    }
    return false;
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

void GenerateRandomMap(){
    char getMapList[32];
    int interval  = 0;
    int counterOfDollar = 0;
    int counterOfBlock  = 0;
    int entireBlockInRow = 0;
    int entireBlockInCol = 0;
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 8; j++){
            // Skip Touching the player.
            if(i == 0 && j == 0) continue;
            // Touch other things.
            Retry:
                int getRandom = rand()%3;
                gameMap[i][j] = mapList[rand()%3];

                // We should set $ at 5 - 8 position at least.
                if(gameMap[i][j] == '$' && j < 5)
                    goto Retry;
                
                // We shouldn't make to much block maybe 10 is enough.
                if(gameMap[i][j] == '@')
                    counterOfBlock++;

                if(counterOfBlock > blockLevel)
                {
                    counterOfBlock--;
                    goto Retry;
                }
                // We should check if player's both side is not blocked.
                if(gameMap[i][j] == gameMap[0][1] || gameMap[i][j] == gameMap[1][0]){
                    if(gameMap[i][j] == '@'){
                        counterOfBlock--;
                        goto Retry;
                    }
                }

                // We should check if entire row or column is not blocked.
                entireBlockInRow = 0;
                entireBlockInCol = 0;
                for(int row = 0; row < 4; row++)
                {
                    if(gameMap[row][j] == '@')
                        entireBlockInRow++;
                    if(entireBlockInRow > 3)
                    {
                        entireBlockInRow--;
                        counterOfBlock--;
                        goto Retry;
                    }
                }
                for(int col = 0; col < 8; col++)
                {
                    if(gameMap[i][col] == '@')
                        entireBlockInRow++;
                    if(entireBlockInCol > 7)
                    {
                        entireBlockInCol--;
                        counterOfBlock--;
                        goto Retry;
                    }
                }
                // We should only set one dollar $.
                if(gameMap[i][j] == '$')
                    counterOfDollar++;
                if(counterOfDollar > 1)
                {
                    counterOfDollar--;
                    goto Retry;
                }
        }
    }
    if(counterOfBlock < blockLevel)
        GenerateRandomMap();
    
}

bool IsMapGoodToPlay(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            if(gameMap[i][j] == gameMap[j][i]){
                if(gameMap[i][j] == '@' && gameMap[j][i] == '@')
                {
                    return false;
                }
            } 
                    
        }
    }
    return true;
}