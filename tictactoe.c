#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void display_board(char a0, char a1, char a2, char a3, 
                   char a4, char a5, char a6, char a7, char a8){
    // Clear the screen on linux machines
    #ifdef _linux_
        system("clear");
    
    // Clear the screen on windows machines
    #elif _WIN32
        system("cls");
    #else

    #endif
    
    printf(" %c | %c | %c \n", a0, a1, a2);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", a3, a4, a5);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", a6, a7, a8);
}

int get_user_input(){
    int user_input;
    printf("Enter a number where you want to place your symbol: ");
    scanf("%d", &user_input);
   
    return user_input;
}

int main()
{
    //char player_name[20];
    //printf("Please enter your name: ");
   //scanf("%s", &player_name);

    int user_input; // Store the return value from get_user_input()
    int computer_choice; // Store the return value from rand()
    
    /* Store the symbol 'X' into the user-selected spot and symbol 'O' into the
    computer-selected spot. */
    char player_input_arr [3][3];
    char input_arr[9]; // approach2
    int available_slot_found = 0;
    bool game_over = 0;
    int x; // row index
    int y; // column index
    int i; // loop counter for row
    int j; // loop counter for column
    // rand() function will generate a number between 0 and n
    int n = 8;
    // Setting a seed for the rand() function
    srand(time(NULL));
    
/*
    // Initialize every slot in input_arr with 'T'.
    for(int i = 0; i<3; ++i){
        for(int j = 0; j<3; ++j){
            player_input_arr[i][j] = 'T';
        }
    }   
*/
// Initialize every slot in input_arr with 'T'.
    for(int i = 0; i < 9; ++i){
        input_arr[i] = 'T';
    } 
    
    display_board('0', '1', '2', '3', '4', '5', '6', '7', '8');
    user_input = get_user_input();
    input_arr[user_input] = 'X'; // approach2
    // Find the row and column indices for the user-chosen spot 
    /*
    x = user_input / 3;
    y = user_input % 3;
    player_input_arr[x][y] = 'X';
   */

    // Generate a random number between 0 and n
    computer_choice = rand() % n;
    printf("%d\n", computer_choice); // Test purpose: to see the generated number

    // Place symbol 'O' into computer-chosen spot
    for(int i = 0; i <= computer_choice; ++i){
        if (input_arr[i] == 'T'){
            if (available_slot_found == computer_choice){
                input_arr[i] = 'O';
            }
            else {
                available_slot_found += 1;
            }
        }
    }

    do {
        // Get user input
        // Place user's symbol
        // Display updated board
        // Get computer's input
        // Place computer's symbol
        // Display updated board
        // Check winning cases
        // Matching Rows
        if (input_arr[0] == input_arr[1] && input_arr[1] == input_arr[2])
            break;
        if (input_arr[3] == input_arr[4] && input_arr[4] == input_arr[5])
            break;
        if (input_arr[6] == input_arr[7] && input_arr[7] == input_arr[8])
            break;
        // Matching Columns
        if (input_arr[0] == input_arr[3] && input_arr[3] == input_arr[6])
            break;
        if (input_arr[1] == input_arr[4] && input_arr[4] == input_arr[7])
            break;
        if (input_arr[2] == input_arr[5] && input_arr[5] == input_arr[8])
            break;
        // Matching Diagonals
        if (input_arr[0] == input_arr[4] && input_arr[4] == input_arr[8])
            break;
        if (input_arr[2] == input_arr[4] && input_arr[4] == input_arr[6])
            break;
    } while(!game_over)

// Print winning msg
// Ask if the user wants to play again
 

/*
    // keep getting inputs until there's no available slot left
    for(i = 0; i < 9; ++i) {
        computer_choice = rand() % n;
        printf("%d\n", computer_choice); // Test purpose: to see the generated number
        //if ()

        --n;
    }
*/
/*
    // Display the updated board (with the symbol placed in the chosen spot)
    display_board(player_input_arr[0][0], player_input_arr[0][1], player_input_arr[0][2],
                  player_input_arr[1][0], player_input_arr[1][1], player_input_arr[1][2],
                  player_input_arr[2][0], player_input_arr[2][1], player_input_arr[2][2]);

*/
    // Approach2
    display_board(input_arr[0], input_arr[1], input_arr[2], input_arr[3], input_arr[4], 
                  input_arr[5], input_arr[6], input_arr[7], input_arr[8]);

    // Print data stored in input_arr
    for(i = 0; i < 9; ++i) {
        printf("%c\n", input_arr[i]);
    }

    /*
    // Print data stored in user_input_arr
    for(i = 0; i<3; ++i){
        for(j = 0; j<3; ++j){
            printf("%c\n", player_input_arr[i][j]);
        }
    }
*/

    return 0;
}
