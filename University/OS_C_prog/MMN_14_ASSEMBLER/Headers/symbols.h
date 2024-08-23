#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include "utils.h"
#include "exit.h"
#include "memory.h"

#define is_entry_or_extern (Current_instruction->symbol.is_entry_line == 1 || \
                                  Current_instruction->symbol.is_external_line == 1)

/* this macro is used for more orderly boolean conditions */

typedef struct label_t {
    int address;
    char *label_name;
    /* The reason I implemented it as a pointer (and in first-pass.c allocated a full line length ot it ) and not a fixed-size char array of size 31,
     * is because the user might try to make a longer label despite it being illegal.
    I decided that a label name being too long should not crash the program.
    It's safer if it persists and exists under my conditions instead, when I check for label integrity. */
    int is_data_line ;
    int is_external_line;
    int is_entry_line;
} label_t;


/* Forward declaration of Macro_node */
typedef struct symbol_node symbol_node;

typedef struct symbol_node {
    label_t symbol;
    symbol_node * Next;
}symbol_node;


/**
 * @brief Writes an entry to the entry file.
 *
 * This function writes an entry with a given name and address to the specified entry output file.
 * The format of the entry in the file will be `entry_name addr`, where `addr` is zero-padded to 4 digits.
 *
 * @param entryOUT Pointer to the file where the entry will be written.
 * @param entry_name Name of the entry to be written.
 * @param addr Address associated with the entry.
 */
void writeEntry(FILE * entryOUT, char * entry_name, int addr );

/**
 * @brief Writes an external label to the extern file.
 *
 * This function writes an external label with a given name and the address the external label was called from. One label may be called many times.
 * The format of the entry in the file will be `extern_name addr`, where `addr` is zero-padded to 4 digits.
 *
 * @param externOUT Pointer to the file where the extern entry will be written.
 * @param extern_name Name of the external entry to be written.
 * @param addr Address the extern was called from.
 */

void writeExtern(FILE *externOUT, char *extern_name, int addr);

/**
 * @brief Creates an entry output file and writes entries for symbols marked as entry points.
 *
 * This function iterates through the list of symbols and writes the symbols that are marked as entry points
 * to a file with the specified name. It creates the file if it does not already exist and ensures that the
 * file is closed properly after writing.
 *
 * @param Head Pointer to the head of the symbol list.
 * @param entryOUT Name of the output file for entries.
 */

void createEntryOutput(symbol_node ** Head, char entryOUT[]);

/**
 * @brief Sets the entry address for labels marked as entries.
 *
 * This function iterates through the list of symbols to find symbols marked as entries
 * and attempts to find their corresponding addresses in the list of instructions. It updates
 * the entry symbol's address with the address from the instruction label if found.
 *
 * @param directive_name Name of the directive (not used in this implementation).
 * @param Head Pointer to the head of the symbol list.
 * @return int Returns NO_SUCH_LABEL if a label is not found, otherwise SECOND_PASS_EXIT_SUCCESS.
 */

int setEntryAddress(char * directive_name, symbol_node ** Head);

/**
 * @brief Deletes the extern output file if it exists.
 *
 * This function attempts to delete the specified file. If the file does not exist,
 * it considers the operation a success. This function is needed since the extern output file is produced during runtime,
 * and we don't produce files in case of errors.
 *
 * @param Head Pointer to the head of the symbol list (not used in this implementation).
 * @param output_name Name of the extern output file to be deleted.
 */

void deleteExternOutput(symbol_node **Head, char *output_name);

void createObjectOutput(char * object_name, MemoryCell Code[], int DC, int IC);

#endif
