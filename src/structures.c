#include "structures.h"

/**
 * Function that prints content of message_board structures.
 * 
 * @param board Structure of the message_board we're using.
 *
 */
void print_message_board_history(message_board board) {
    green();
    system("clear");
    printf("\n\tYour message board had:\n\n\t\
    - Total conversations: %i\n\t\
    - Open conversations: %i\n", board.total_convs, board.open_convs);
    default_color();
}

/**
 * Function that prints current open conversations in program.
 * 
 * @param board Structure of the message_board we're using.
 *
 */
void print_convs(message_board board) {
    green();
    system("clear");
    printf("\n\t%i open conversation(s):\n\n", board.open_convs);
    for (int i = 0; i < board.open_convs; i++) printf("\t\t%i. %s\n", i, board.conv_names[i]);
    default_color();
}