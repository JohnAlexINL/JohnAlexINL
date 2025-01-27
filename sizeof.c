#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

const char sizefixes[][16] = {
    "", "kilo", "mega", "giga",
    "tera", "peta", "exa",
    "zetta", "yotta", "bronto",
};

unsigned int filesize(const char *filename) {
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
    sprintf(result, "%d bytes", size);}
    else {
    sprintf(result, "%d %sbytes (%d bytes)",
        topsize, class, size
    );}
    return result;
}

int main ( int argc, char ** argv) {
    if ( argc == 1 ) { printf("sizeof usage: sizeof <list of files>\n"); exit(1); }
    int i; for(i=1; i<argc; i++) {
        unsigned int size = filesize(argv[i]);
        if ( size == -1 ) { printf("%-32s {NULL}\n", argv[i]); continue; }
        printf("%-32s %s\n", argv[i], strsize(size));
    }   return 0;
}
