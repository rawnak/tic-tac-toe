#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void display_board(char* arr)
{
    #if _WIN32
        // Clear the screen on windows machines
//        system("cls");
    #else
        // Clear the screen on linux/mac machines
//        system("clear");
    #endif
    
    printf(" %c | %c | %c \n", arr[0], arr[1], arr[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", arr[3], arr[4], arr[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", arr[6], arr[7], arr[8]);
}

// Takes an array pointer as parameter
int get_user_input(char* arr)
{
    int user_input;
    // Keep asking for user input until a valid input is entered
    while(1)
    {
        printf("Enter the number where you want to place your symbol: ");
        scanf("%d", &user_input);

        // Check for input validity. Print error message for invalid input.
        if (user_input < 0 || user_input > 8)
            printf("Error: Invalid input! Input has to be between 0 and 8.\n");

        else if (arr[user_input] == 'X' || arr[user_input] == 'O')
            printf("Error: The spot is already taken\n");
        else
            return user_input;
    }
}

void get_computer_input(char* arr, int num_of_available_slot)
{
    int computer_choice; // Store the return value from rand()
    int available_slot_found = 0;
    int i; // Loop counter
    // Check if there's potential slot for computer to win
    // Generate a random number between 1 and num_of_available_slot
    
    computer_choice = rand() % num_of_available_slot;
    printf("computer_choice = %d\n", computer_choice);

    // Test purpose: to see the generated number and the number of
    // available spot
    printf("Remaining available spot: %d, computer's choice: %d\n", num_of_available_slot, computer_choice);
    // Place symbol 'O' into computer-chosen spot
    // TODO explain why the loop may need to run 9 times
    for(int i = 0; i <= 8; ++i){
        // Check if 'i'th spot is available. If available, then check if 
        // this is the desired slot. If so, then place the symbol.
        if (arr[i] != 'X' && arr[i] != 'O'){
            if (available_slot_found == computer_choice){
                arr[i] = 'O';
                // Reset availavle_slot_found variable for the next turn
               // available_slot_found = 0;
                break;
            }
            else {
                available_slot_found += 1;
            }
        }
    }
}

// Checks for three matching symbols. If found, returns the symbol. 
char check_winning_cases (char* arr)
{
    // Matching Rows
    if (arr[0] == arr[1] && arr[1] == arr[2])
        return arr[1];
    else if (arr[3] == arr[4] && arr[4] == arr[5])
        return arr[3];
    else if (arr[6] == arr[7] && arr[7] == arr[8])
        return arr[6];
    // Matching Columns
    else if (arr[0] == arr[3] && arr[3] == arr[6])
        return arr[0];
    else if (arr[1] == arr[4] && arr[4] == arr[7])
        return arr[1];
    else if (arr[2] == arr[5] && arr[5] == arr[8])
        return arr[2];
    // Matching Diagonals
    else if (arr[0] == arr[4] && arr[4] == arr[8])
        return arr[0];
    else if (arr[2] == arr[4] && arr[4] == arr[6])
        return arr[2];
    // 'c' indicates to continue with the game loop
    else
        return 'c'; 
}

char game()
{
    // Store 'X' into the user-selected slot and 'O' into computer-selected slot.
    // Initialize every slot in input_arr with 0 to 8 consecutive integers
    char input_arr[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    // Represents the number of available slots on the tic-tac-toe board. rand() 
    // function will generate a number between 0 and n.
    int n = 9;
    // Store the return value from check_winning_cases()
    char result;
    int potential_slot_found;
      
    display_board(input_arr);

    do {
        // Get user input and assign the symbol 'X' into input_arr[]
        input_arr[get_user_input(input_arr)] = 'X';
        // Decrease the number of available slot by 1
        --n;
        // Display updated board
        display_board(input_arr);
        // Check winning cases after user's input
        result = check_winning_cases(input_arr);
        if (result != 'c')
             return result;

        get_computer_input(input_arr, n);

        // Decrease the number of available slot by 1. Decrementing the value 
        // of n makes sure that the random number generated the next time is 
        // within the correct range (same as the available slot)
        --n;

        // Display updated board
        display_board(input_arr);
        // Check winning cases after computer's input
        result = check_winning_cases(input_arr);
        if (result != 'c')
            return result;
        // No winner found and there is no more available slot, so the game is 
        // a draw. 'd' stands for 'draw'
        else if (n == 0)
            return 'd';

    } while(1);
}

// Print winning msg
void print_game_result(char winner_symbol)
{ 
    switch(winner_symbol) {
        case 'X':
            printf("CONGRATULATIONS!! YOU'VE WON!\n");
            break;
        case 'O':
            printf("THE COMPUTER WON!\n");
            break;
        default:
            printf("THE GAME WAS A DRAW\n");
    }
}

int play_game() { 
    char continue_playing;
    int result; // Store the return value from game() function
    
    result = game();
    print_game_result(result);

    // Ask if the user wants to play again
    printf("Do you want to play again?(Enter 'Y' for YES or 'N' for NO): ");
    scanf(" %c", &continue_playing);
    if(continue_playing == 'Y' || continue_playing == 'y')
        return 1;
    else
        return 0;
}

int main()
{
    int play_again;
    // Setting a seed for the rand() function
    srand(time(NULL));
    
    // Keep running the function play_game() until the user doesn't want
    // to play anymore.
    do {
        play_again = play_game();
    } while(play_again);

    return 0;
}
