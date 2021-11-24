#include <stdio.h>
#include "Parser.h"

#define FILE_IN "C:\\Users\\Toor\\Desktop\\fill.asm"
#define FILE_OUT "C:\\Users\\Toor\\Desktop\\test.txt"


int start_assembler() {


    FILE *pfile_in = NULL;
    FILE *pfile_out = NULL;

    int c;
    size_t line_length;
    char fileInputLine[120];

    pfile_in = fopen(FILE_IN, "r");
    if(pfile_in == NULL) {
        fprintf(stderr, "Failed to open_asm_file %s\n", FILE_IN);
        return -1;
    }


    pfile_out = fopen(FILE_OUT, "w");
    if(pfile_out == NULL) {
        fprintf(stderr, "Failed to open_asm_file %s\n", FILE_OUT);
        return -1;
    }

    for (line_length=0; (c = fgetc(pfile_in)) != EOF; ++line_length) {
        fileInputLine[line_length] = c;
        if(c == '\n' || c == EOF) {
            fileInputLine[line_length]= '\0';
            char *arr = hasMoreCommands(fileInputLine, &line_length);
            if (arr != NULL) fputs(arr, pfile_out);
            line_length = -1;
        }
    }

    fclose(pfile_in);
    fclose(pfile_out);

    pfile_out = NULL;
    pfile_in = NULL;

    return 0;
}

int main() {

    return start_assembler();


}
