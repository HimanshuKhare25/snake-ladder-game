#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Constants for the game board size and number of players
#define BOARD_SIZE 50
#define NUM_PLAYERS 2



int GlobalHorizontalArr[500];
int h_i = 0;
int GlobalDownArr[500];
int d_i = 0;


int S_GlobalHorizontalArr[500];
int S_h_i = 0;
int S_GlobalDownArr[500];
int S_d_i = 0;

// Structure to represent the game board
struct Board
{
    int snakes[BOARD_SIZE];  // Array to store the positions of snakes
    int ladders[BOARD_SIZE]; // Array to store the positions of ladders
};

// Function to initialize the game board
void initBoard(struct Board *board)
{
    // Initialize snakes and ladders arrays to -1
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        board->snakes[i] = -1;
        board->ladders[i] = -1;
    }
}




int checkI(int a){
    a = a-1;
    return (9 - (a/10));
}

int getUpElement(int a){
    if(a%10 == 0 ){
        return a+1;
    }
    int x = a;
    int y =a;
    y = y/10;
    y++;
    x = x%10;
    x--;
    
    return (y*10 + (10-x));
}
int getDownElement(int a){
    if(a%10 == 0 ){
        return a+1;
    }
    int x = a;
    int y =a;
    y = y/10;
    y--;
    x = x%10;
    x--;
    
    return (y*10 + (10-x));
}
bool linearSearch(int arr[],int index ,int value){
    for(int i =0; i<=index; i++){
        if(arr[i]==value) return true;
    }
    return false;
}


void addSnakes(struct Board *board, int start, int end)
{
    board->snakes[start] = end;
    int temp = start; 
    start = end;
    end = temp;


    int downArr[20];
    int horiZontalArr[20];
    int h=0;
    int d=0;
    int Up_i = checkI(start);
    int upElement = getUpElement(start);
    horiZontalArr[h++]=upElement;
    downArr[d++] = start;
    int i_UpElement = checkI(upElement);

    downArr[d++]=end;
    int End_i = checkI(end);
    int downElement = end;
    while(End_i < i_UpElement){
        downElement = getDownElement(downElement);
        downArr[d++] = downElement;
        End_i++;
    }

    if(downElement-1>upElement){
        while(downElement-1>upElement){
        upElement++;
        horiZontalArr[h++] = upElement;
        }
    }
    else if(downElement<upElement){
        while(downElement<upElement){
        upElement--;
        horiZontalArr[h++] = upElement;
        }
    }
    

    for(int k =0; k<h; k++){
        S_GlobalHorizontalArr[S_h_i++] = horiZontalArr[k];
    }
    S_GlobalHorizontalArr[S_h_i++] = -1;

    for(int k =0; k<d; k++){
        S_GlobalDownArr[S_d_i ++] = downArr[k];
    }
    S_GlobalDownArr[S_d_i ++] = -1;

    
}



void addLadders(struct Board *board, int start, int end)
{
    board->ladders[start] = end;
    int downArr[20];
    int horiZontalArr[20];
    int h=0;
    int d=0;
    int Up_i = checkI(start);
    int upElement = getUpElement(start);
    horiZontalArr[h++]=upElement;
    downArr[d++] = start;
    int i_UpElement = checkI(upElement);

    downArr[d++]=end;
    int End_i = checkI(end);
    int downElement = end;
    while(End_i < i_UpElement){
        downElement = getDownElement(downElement);
        downArr[d++] = downElement;
        End_i++;
    }

    if(downElement-1>upElement){
        while(downElement-1>upElement){
        upElement++;
        horiZontalArr[h++] = upElement;
        }
    }
    else if(downElement<upElement){
        while(downElement<upElement){
        upElement--;
        horiZontalArr[h++] = upElement;
        }
    }
    

    for(int k =0; k<h; k++){
        GlobalHorizontalArr[h_i++] = horiZontalArr[k];
    }
    GlobalHorizontalArr[h_i++] = -1;

    for(int k =0; k<d; k++){
        GlobalDownArr[d_i ++] = downArr[k];
    }
    GlobalDownArr[d_i ++] = -1;
}


bool hasSnake(struct Board *board, int position)
{
    if (board->snakes[position] != -1)
        return true; 
    else
        return false;
}


bool hasLadder(struct Board *board, int position)
{
    if (board->ladders[position] != -1)
        return true;
    else
        return false;
}


void displayBoard(int player1Pos, int player2Pos)
{
    printf("\nGame Board:\n");
    printf(" __________________________________________________\n");
    int l =0;  //Horizontal
    int m =0;  //down

    for (int i = 0; i < 10; i++)
    {
        if(i%2==0){
            int a =1;
            for (int j = 0; j < 10; j++)
            {
                printf("|");
                int cell = (90 - i * 10 + j + 1) +10 - (j + a++);
                
                if (player1Pos == cell)
                {
                    printf("\033[0;94m[P1]\033[0m");
                }
                else if (player2Pos == cell)
                {
                    printf("\033[0;94m[P2]\033[0m");
                }
                // ##### for ladders ############
                
                else if(linearSearch(GlobalHorizontalArr,h_i,cell)){
                    // printf("==");
                    printf("\033[0;32m==\033[0m");
                    printf("%2d", cell);
                }
                else if(linearSearch(GlobalDownArr,d_i,cell)){
                    //printf("||");
                    printf("\033[0;32m||\033[0m");
                    printf("%2d", cell);
                }

                // ########## for snakes ##############
                
                else if(linearSearch(S_GlobalHorizontalArr,S_h_i,cell)){
                    // printf("==");
                    printf("\033[0;31m{}\033[0m");
                    printf("%2d", cell);
                }
                else if(linearSearch(S_GlobalDownArr,S_d_i,cell)){
                    //printf("||");
                    printf("\033[0;31m{}\033[0m");
                    printf("%2d", cell);
                }
                
                else
                {
                    printf(" %3d", cell);
                }
            }
        printf("|\n");
        printf("|____|____|____|____|____|____|____|____|____|____|\n");
        }
        else{
            for (int j = 0; j < 10; j++)
            {
                printf("|");

                int cell = (90 - i * 10 + j + 1);
                
                if (player1Pos == cell)
                {
                    printf("\033[0;94m[P1]\033[0m");
                }
                else if (player2Pos == cell)
                {
                    printf("\033[0;94m[P2]\033[0m");
                }

                // ##### for ladders ############
                
                else if(linearSearch(GlobalHorizontalArr,h_i,cell)){
                    // printf("==");
                    printf("\033[0;32m==\033[0m");
                    printf("%2d", cell);
                }
                else if(linearSearch(GlobalDownArr,d_i,cell)){
                    //printf("||");
                    printf("\033[0;32m||\033[0m");
                    printf("%2d", cell);
                }

                // ########## for snakes ##############
                
                else if(linearSearch(S_GlobalHorizontalArr,S_h_i,cell)){
                    // printf("==");
                    printf("\033[0;31m{}\033[0m");
                    printf("%2d", cell);
                }
                else if(linearSearch(S_GlobalDownArr,S_d_i,cell)){
                    //printf("||");
                    printf("\033[0;31m{}\033[0m");
                    printf("%2d", cell);
                }



                
                else
                {
                    printf(" %3d", cell);
                }
            }
        printf("|\n");
        printf("|____|____|____|____|____|____|____|____|____|____|\n");
        }
        
    }
}

int main()
{
    struct Board board;
    initBoard(&board);

    // Add snakes to the board
    // addSnakes(&board, 97, 78);
    addSnakes(&board, 57, 41);
    addSnakes(&board, 95, 78);
    addSnakes(&board, 93, 73);
    addSnakes(&board, 35, 7);
    // addSnakes(&board, 93, 73);
    // addSnakes(&board, 95, 75);
    // addSnakes(&board, 99, 78);

    // Add ladders to the board
    addLadders(&board, 82, 98);
    addLadders(&board, 72, 91);
    addLadders(&board, 50, 74);
    addLadders(&board, 8, 33);
    addLadders(&board, 21, 42);
    // addLadders(&board, 51, 67);
    // addLadders(&board, 63, 81);
    // addLadders(&board, 71, 91);
    // addLadders(&board, 17, 7);
    // addLadders(&board, 80, 99);

    srand(time(0));        // Seed the random number generator with current time
    int player1Pos = 1;    // Starting position for Player 1
    int player2Pos = 1;    // Starting position for Player 2
    int currentPlayer = 1; // Current player's turn (1 for Player 1, 2 for Player 2)
    bool gameover = false; // Game over flag

    printf("Welcome to Snake & Ladder game!\n");
//game loop
    while (!gameover)
    {
        // Display current game board
        displayBoard(player1Pos, player2Pos);

        // Roll the dice
        printf("Player %d, press enter to roll the dice.\n", currentPlayer);
        getchar();
        int dice = rand() % 6 + 1;
        printf("Player %d rolled a %d!\n", currentPlayer, dice);

        // Move the current player's position based on the dice roll
        int *currentPlayerPos;
        if (currentPlayer == 1)
        {
            currentPlayerPos = &player1Pos;
        }
        else
        {
            currentPlayerPos = &player2Pos;
        }
        
        *currentPlayerPos += dice;
        if (*currentPlayerPos > BOARD_SIZE)
        {
            *currentPlayerPos = BOARD_SIZE;
        }
        

        // Check if the current position has a snake or a ladder
        if (hasSnake(&board, *currentPlayerPos))
        {
            *currentPlayerPos = board.snakes[*currentPlayerPos];
            printf("Oops! Player %d got bitten by a snake and moved down to position %d.\n", currentPlayer, *currentPlayerPos);
        }
        else if (hasLadder(&board, *currentPlayerPos))
        {
            *currentPlayerPos = board.ladders[*currentPlayerPos];
            printf("Yay! Player %d found a ladder and moved up to position %d.\n", currentPlayer, *currentPlayerPos);
        }
        if(*currentPlayerPos+ dice>BOARD_SIZE){
            printf("Oops you can't move with this value!\n");
        }

        // Check if the current player  has won
        if (*currentPlayerPos >= BOARD_SIZE)
        {
            printf("Player %d wins!\n", currentPlayer);
            break;
            gameover = true;
        }

        else
        {
            // Switch to the other player's turn
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
        
    }

    return 0;
}