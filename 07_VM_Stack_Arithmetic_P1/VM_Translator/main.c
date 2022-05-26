#include "Parser.h"
#include <dirent.h>

const char *INPUT_DIR = "C:\\Users\\Toor\\Downloads\\nand2tetris\\projects\\08\\FunctionCalls\\FibonacciElement";
const char *INPUT_FILE = "C:\\Users\\Toor\\Desktop\\in-VM-code.vm";
const char *OUTPUT_FILE = "C:\\Users\\Toor\\Desktop\\out-ASM-code.txt";

int main(int argc, char **argv) {


    initializer(INPUT_FILE, OUTPUT_FILE);

    return 0;
}
