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
    for (int i = 0; i < board.open_convs; i++) 
        printf("\t\t%i. %s, file at: %s)\n", i, board.conv_names[i], board.storage_ids[i]);
    default_color();
}

/**
 * Function that prints data from a given user ID.
 *
 * @param board Structure of the message_board we're using.
 * @param current_conv Value of the conversation we're trying to print.
 *
 */
void print_id_data(message_board board, uint8_t current_conv) {
    if (current_conv >= 0 && current_conv <= 3) {
        green();
        printf("\n\tCurrent conversation with: %s", board.conv_names[current_conv]); 
        printf("\n\tConversation path in shared memory is: %s", board.storage_ids[current_conv]);
        printf("\n\tConversation ID is set to: %u\n", current_conv);
        default_color();
    } else {
        print_color("red", "Number given is not valid");
    }
}