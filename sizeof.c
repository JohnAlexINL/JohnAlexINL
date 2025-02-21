#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define green  "\e[0;32m"
#define blue   "\e[0;34m"
#define yellow "\e[0;33m"
#define plain  "\e[0m"

const char sizefixes[][16] = {
    "", "kilo", "mega", "giga",
    "tera", "peta", "exa",
    "zetta", "yotta", "bronto",
};

uint64_t filesize(const char *filename) {
    struct stat statbuf;
    if (stat(filename, &statbuf) != 0) { return -1; }
    return statbuf.st_size;
}

char *strsize(unsigned int size) {
    char *result = malloc(64); const char *class;
    int kin = 0; int topsize = size;
    while ( topsize >= 1024 && kin < sizeof(sizefixes) ) {
        topsize = topsize >> 10; kin ++;
    }   class = sizefixes[kin];
    if ( kin == 0 ) {
    sprintf(result, "%ld bytes", size);}
    else {
    sprintf(result, plain "%d %sbytes " blue " (%ld bytes)" plain,
        topsize, class, size
    );}
    return result;
}

#define USAGE "sizeof usage: sizeof <list of files>\n"
#define LICENSE blue "MIT License, " yellow " (C) " plain " Modula.dev 2025\n"
int main ( int argc, char ** argv) {
    if ( argc == 1 ) { printf(USAGE); exit(1); }
    if ( argv[1][0] == '-' ) { printf(LICENSE USAGE); exit(0); }
    uint64_t sum = 0;
    int i; for(i=1; i<argc; i++) {
        uint64_t size = filesize(argv[i]);
        if ( size == -1 ) { printf("%-32s {NULL}\n", argv[i]); continue; }
        printf(green "%-32s " plain "%s\n", argv[i], strsize(size)); sum += filesize(argv[i]);
    }   printf("%-32s " plain "%s total\n", "", strsize(sum));
    return 0;
}
