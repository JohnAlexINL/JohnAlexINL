#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/stat.h>

int file_read(const char *filename, char *buffer, int max) {
    FILE *fp = fopen(filename, "rb");
    if ( fp == NULL ) { return false; }
    int cursor = 0; char c; while(cursor < max -1) {
      c = fgetc(fp);
      if( feof(fp) ) { break; }
      buffer[cursor] = c; cursor++;
   } fclose(fp); return cursor;
}

int file_size(const char *filename) {
    struct stat statbuf;
    if (stat(filename, &statbuf) != 0) { return -1; }
    return statbuf.st_size;
}

typedef struct {
  int64_t checked;
  int64_t todo;
} counter_t;

const char *check_markers[] = { "- [x]", "[x]", "|x|", "🎉", "✅", "✓", "🗹", "❖", "|🎉|","|✅|", "|✓|", "|🗹|", "|❖|" };
const char *todo_markers[] = { "- []", "- [ ]", "- [_]", "✗", "✘", "❌", "❎", "⮽", "|✗|", "|✘|", "|❌|", "|❎|", "|⮽|", "TODO", "> [!TODO", "// TODO", "; TODO" };

#define CHECK_MARKERS (sizeof(check_markers) / sizeof(check_markers[0]))
#define TODO_MARKERS  (sizeof(todo_markers) / sizeof(todo_markers[0]))
#define green  "\e[0;32m"
#define red    "\e[0;31m"
#define blue   "\e[0;34m"
#define plain  "\e[0m"

void printCount(const char *string, counter_t tally) {
    char printString[80];
    if ( tally.checked == 0 && tally.todo == 0 ) { sprintf(printString, blue "%-32s %-8s" plain "--\n", string, "" ); }
    else { sprintf(printString, plain "%-32s" green " %8d " red "%-d" plain "\n", string, tally.checked, tally.todo ); }
    printf("%s", printString);
}

counter_t countFile(const char *filename) {
    counter_t tally = { 0, 0 };
    size_t size = file_size(filename); if (size == 0) { return tally; }
    char *buffer = malloc(size + 1); if (!buffer) { return tally; }    
    file_read(filename, buffer, size + 1); char *line = strtok(buffer, "\n");
    while (line) {
        for (size_t i = 0; i < CHECK_MARKERS; i++) { if (strncmp(line, check_markers[i], strlen(check_markers[i])) == 0) { tally.checked++; break; }}
        for (size_t i = 0; i < TODO_MARKERS; i++) { if (strncmp(line, todo_markers[i], strlen(todo_markers[i])) == 0) { tally.todo++; break; }}
        line = strtok(NULL, "\n");
    }   free(buffer);
    printCount(filename, tally);
    return tally;
}

#define USAGE "usage: todo <list of files>\n"
#define LICENSE blue "MIT License," green "(C) " plain "Modula.dev 2025\n"
int main(int argc, char **argv) {
    if ( argc < 2 ) { printf(USAGE); exit(1); }
    if ( argv[1][0]=='-') { printf(LICENSE USAGE); exit(0); };
    counter_t tally = {0, 0};
    for (int i = 1; i < argc; i++) {
        counter_t local = countFile(argv[i]);
        tally.checked += local.checked;
        tally.todo += local.todo;
    }
    if (argc > 2) { printCount("", tally); }
    return 0;
}
