#ifndef validator_h
#define validator_h

// Basic C libraries.
#include <stdio.h>
#include <string.h>

// Personal libraries.
#include "structures.h"
#include "styles.h"

void validate_new_conv(message_board *msg_controller);
/**
 * Function to validate a new conversation can be created.
 *
 * @param msg_controller Main structure to control all messages in program.
 *
 */

 int change_conv();
/**
 * Function to change conversation between users.
 * 
 * @return Conversation number of conversation we're changing to.
 *
 */
 
#endif