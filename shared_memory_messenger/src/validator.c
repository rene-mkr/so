#include "validator.h"

/**
 * Function to validate a new conversation can be created.
 *
 * @param msg_controller Main structure to control all messages in program.
 *
 */
void validate_new_conv(message_board *msg_controller) {
    char temp_name[12]; // Temporary name to create new conversation.

    if (msg_controller->open_convs == 3) {
        print_color("red", "Only three conversations at once are supported.");
        return;
    }
    printf("\n\tContact name: ");
    scanf(" %s", temp_name);
    if (strlen(temp_name) > 12) {
        print_color("red", "Contact name must be less than 12 characters long.");
        return;
    }
    system("clear");
    strcpy(msg_controller->conv_names[msg_controller->open_convs], temp_name);
    strcpy(msg_controller->storage_ids[msg_controller->open_convs], "/");
    strcat(msg_controller->storage_ids[msg_controller->open_convs], temp_name);
    msg_controller->open_convs++;
    msg_controller->total_convs++;

    green(); printf("\n\tOpening chat with: %s\n\n", temp_name); default_color();
}

/**
 * Function to change conversation between users.
 * 
 * @return Conversation number of conversation we're changing to.
 *
 */
int change_conv() {
    int change_to;
    printf("\n\tWho do you want to text: ");
    scanf(" %d", &change_to);
    if (change_to < 0 || change_to > 3) {
        print_color("red", "Number given is not valid, set ID to 0.");
        return 0;
    }
    return change_to;
}