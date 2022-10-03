#ifndef structures_h
#define structures_h

// Basic C libraries.
#include <stdio.h>
#include <stdlib.h>

// Personal libraries.
#include "styles.h"

// Understand "convs" as meaning "conversations".
typedef struct message_board {
    int open_convs;
    int total_convs;
    int total_mem_reads, total_mem_writes;
    char conv_names[3][12]; // Three conv_names of 12 chars at most.
    char storage_ids[3][13]; // ID for each shared memory object (one per conv).
} message_board;

typedef struct conversation {
    char *name;
    int message_count;
} conversation;

void print_message_board_history(message_board board);
/**
 * Function that prints content of message_board structures.
 * 
 * @param board Structure of the message_board we're using.
 *
 */

void print_convs(message_board board);
/**
 * Function that prints current open conversations in program.
 * 
 * @param board Structure of the message_board we're using.
 *
 */

void print_id_data(message_board board, uint8_t current_conv);

#endif