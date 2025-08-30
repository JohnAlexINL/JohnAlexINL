#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

#define PURPLE  "\e[0;35m"
#define RED     "\e[0;31m"
#define GREEN   "\e[0;32m"
#define BLUE    "\e[0;34m"
#define WHITE   "\e[0m"

int file_size(char *filename) { struct stat buffer; return (stat(filename, &buffer) == 0) ? buffer.st_size : -1; }
int file_read(char *filename, char *buffer, int max) {
    FILE *fp = fopen(filename, "rb");
    if ( fp == NULL ) { return false; }
    int cursor = 0; char c; while(cursor < max -1) {
      c = fgetc(fp);
      if( feof(fp) ) { break; }
      buffer[cursor] = c; cursor++;
   } fclose(fp); return cursor;
}

int main (int argc, char **argv) {
    if (argc != 2) { printf("hexdump usage: hexdump {filename}\n"); exit(1); }
    char * filename = argv[1];
    int size = file_size(filename); if ( size <= 0 ) { printf("File %s is either empty or does not exist\n", filename); exit(1); }
    char buffer[size+1]; 
    int read = file_read(filename, buffer, size); if ( read <= 0 ) { printf("Failed to read file %s\n", filename); exit(1); }
    
    // Heading
    printf(GREEN "         0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F     10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F\n");
    
    int i=0; for(i=0;i<size-1;i++) {
            // NONCHAR
        if          ( buffer[i] == 0 || buffer[i] >= 127 ) { printf(RED); }
            // TTY
        else if     ( buffer[i] < 32 ) { printf(PURPLE); }
            // SYMBOLS
        else if     ( buffer[i] <= 64 ) { printf(GREEN); }
        else if     ( buffer[i] <= 96 && buffer[i] >= 91 ) { printf(GREEN); }
        else if     ( buffer[i] >= 123 ) { printf(GREEN); }
            // OTHER CHARACTERS
        else { printf(WHITE); }

        if ( i % 32 == 0 ) { printf(GREEN "%04x\t", i);  }
        if ( i % 32 == 31 ) { printf("\n"); }
        else if ( i % 32 == 16 ) { printf("    "); }

        printf("%02x ", buffer[i]);

    }   if ( i % 32 != 31 ) { printf("\n"); }
}
