#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void display_board(char a0, char a1, char a2, char a3, 
                   char a4, char a5, char a6, char a7, char a8)
{
    #if _WIN32
        // Clear the screen on windows machines
        system("cls");
    #else
        // Clear the screen on linux/mac machines
        system("clear");
    #endif
    
    printf(" %c | %c | %c \n", a0, a1, a2);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", a3, a4, a5);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", a6, a7, a8);
}

int get_user_input()
{
    int user_input;
    printf("Enter the number where you want to place your symbol: ");
    scanf("%d", &user_input);
   
    return user_input;
}
// Checks for three matching symbols. If found, returns the symbol. 
char check_winning_cases (char a0, char a1, char a2, char a3, 
                   char a4, char a5, char a6, char a7, char a8)
{
        // Matching Rows
        if (input_arr[0] == input_arr[1] && input_arr[1] == input_arr[2])
            return input_arr[0];
        else if (input_arr[3] == input_arr[4] && input_arr[4] == input_arr[5])
            return input_arr[3];
        else if (input_arr[6] == input_arr[7] && input_arr[7] == input_arr[8])
            return input_arr[6];
        // Matching Columns
        else if (input_arr[0] == input_arr[3] && input_arr[3] == input_arr[6])
            return input_arr[0];
        else if (input_arr[1] == input_arr[4] && input_arr[4] == input_arr[7])
            return input_arr[1];
        else if (input_arr[2] == input_arr[5] && input_arr[5] == input_arr[8])
            return input_arr[2];
        // Matching Diagonals
        else if (input_arr[0] == input_arr[4] && input_arr[4] == input_arr[8])
            return input_arr[0];
        else if (input_arr[2] == input_arr[4] && input_arr[4] == input_arr[6])
            return input_arr[2];
        // No one wins, so the game is a draw. 'd' stands for 'draw'
         else if (n < 0)
            return 'd';
        // 'c' indicates to continue with the game loop
        else
            return 'c'; 
}

char game()
{
    int computer_choice; // Store the return value from rand()
    // Store 'X' into the user-selected slot and 'O' into computer-selected slot.
    // Initialize every slot in input_arr with 0 to 8 consecutive integers
    char input_arr[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    int available_slot_found = 0;
    // Represents the number of available slot on the tic-tac-toe board. rand() 
    // function will generate a number between 0 and n.
    int n = 9;
    int i; // Loop counter
    int game_over = 0;
    // Store the return value from check_winning_cases()
    char result;
      
    display_board(input_arr[0], input_arr[1], input_arr[2], input_arr[3], input_arr[4], 
                  input_arr[5], input_arr[6], input_arr[7], input_arr[8]);

    do {
        // Get user input and assign the symbol 'X' into input_arr[]
        input_arr[get_user_input()] = 'X';
        // Decrease the number of available slot by 1
        --n;
        // Display updated board
        display_board(input_arr[0], input_arr[1], input_arr[2], input_arr[3], input_arr[4], 
                      input_arr[5], input_arr[6], input_arr[7], input_arr[8]);
        // Check winning cases after user's input
        result = check_winning_cases();
        if (result != 'c')
             return result;
        // Get computer's input
        // Generate a random number between 0 and n
        computer_choice = rand() % n;
        printf("n: %d, computer's choice: %d\n", n, computer_choice); // Test purpose: to see the generated number

        // Place symbol 'O' into computer-chosen spot
        for(int i = 0; i <= computer_choice; ++i){
            if (input_arr[i] != 'X' || input_arr[i] != 'O'){
                if (available_slot_found == computer_choice){
                    input_arr[i] = 'O';
                }
                else {
                    available_slot_found += 1;
                }
            }
        }
        // Decrease the number of available slot by 1. Decrementing the value 
        // of n makes sure that the random number generated the next time is 
        // within the correct range (same as the available slot)
        --n;
        // Display updated board
        display_board(input_arr[0], input_arr[1], input_arr[2], input_arr[3], input_arr[4], 
                      input_arr[5], input_arr[6], input_arr[7], input_arr[8]);
        // Check winning cases after computer's input
        result = check_winning_cases();
        if (result != 'c')
            return result;
    } while(!game_over);
}

// Print winning msg
void print_msg(char winner_symbol)
{ 
    switch(winner_symbol) {
        case 'X':
            printf("YAY!! YOU'VE WON!\n");
            break;
        case 'O':
            printf("THE COMPUTER WON!\n");
            break;
        default:
            printf("THE GAME WAS A DRAW\n");
    }
}

int main()
{
    char continue_playing;
    int result; // Store the return value from game() function
    // Setting a seed for the rand() function
    srand(time(NULL));

    result = game();

    print_msg(result);

    // Ask if the user wants to play again
    printf("Do you want to play again?(Enter 'Y' for YES or 'N' for NO) \n");
    scanf("%c", &continue_playing);
    if(continue_playing == 'Y' || continue_playing == 'y'){
        game();
    }
    else
        exit;

    return 0;
}
