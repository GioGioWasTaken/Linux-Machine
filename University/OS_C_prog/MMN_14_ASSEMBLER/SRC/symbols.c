#include "../Headers/symbols.h"
#include <stdio.h>

/* The purpose of this file, is to manage all the output files.*/


void writeEntry(FILE *entryOUT, char *entry_name, int addr) {
    /* Check if the file stream is valid*/
    if (entryOUT == NULL) {
        perror("Error opening entry file\n");
        return;
    }

    /* Write the entry in the format: entry_name  addr*/
    fprintf(entryOUT, "%-5s %04d\n", entry_name, addr);
}

void writeExtern(FILE *externOUT, char *extern_name, int addr) {
    /* Check if the file stream is valid*/
    if (externOUT == NULL) {
        perror("Error opening extern file\n");
        return;
    }

    /* Write the extern in the format: extern_name  addr, with addr being the address it was called from.*/
    fprintf(externOUT, "%-5s %04d\n", extern_name, addr);
}


void createEntryOutput(symbol_node **Head, char *entry_name) {
    symbol_node *current = *Head;
    FILE *entryOUT = NULL;
    int file_created = 0;  /* Flag to check if the file has been created*/

    while (current != NULL) {
        if (current->symbol.is_entry_line == 1) {
            if (!file_created) {
		printf("Creating .ent file...\n");
                /* Create the entry output file only once */
                entryOUT = fopen(entry_name, "w");
                if (entryOUT == NULL) {
                    perror("Error opening entry output file");
                    return;
                }
                file_created = 1;  /* Set the flag to avoid creating the file again*/
            }

            /* Write entry to file */
            writeEntry(entryOUT, current->symbol.label_name, current->symbol.address);
        }
        current = current->Next;  /* Move to the next node in the list*/
    }

    /* Close the file if it was created */
    if (file_created) {
	create_file(entryOUT);
        fclose(entryOUT);
    }
}





int setEntryAddress(char * directive_name, symbol_node ** Head){
    symbol_node * Current = *Head;

    while (Current != NULL) {
        if (Current->symbol.is_entry_line == 1) {
            symbol_node * Current_instruction = *Head;
            int label_found = 0;

            while (Current_instruction != NULL) {
                if (is_entry_or_extern) {
                    Current_instruction = Current_instruction->Next;
                } else if (strcmp(Current_instruction->symbol.label_name, Current->symbol.label_name) == 0) {
                    /* Found matching label*/
                    Current->symbol.address = Current_instruction->symbol.address;
                    label_found = 1;
                    break;
                } else {
                    Current_instruction = Current_instruction->Next;
                }
            }

            if (!label_found) {
                return NO_SUCH_LABEL;
            }
        }
        Current = Current->Next;
    }
    return SECOND_PASS_EXIT_SUCESS;
}



void deleteExternOutput(symbol_node **Head, char *output_name) {
    if (remove(output_name) != 0) {
        perror("An error was encoutned during execution, but the extern file could not be deleted, even though it was produced.");
    }
}


void createObjectOutput(char * object_name, MemoryCell Code[], int DC, int IC){
    printf("Creating .ob file...\n");
    FILE * obj_file = fopen(object_name, "w");
    int i, value;
    if (obj_file == NULL) {
        perror("Error opening object file\n");
        return;
    }
    /* Header of file: */
    fprintf(obj_file, "   %d %d\n", IC-100, DC);
    for(i=100; i<IC+DC; i++){
        value = readWord(Code[i]);
        fprintf(obj_file, "%04d %05o\n", i, value);
    }

}
