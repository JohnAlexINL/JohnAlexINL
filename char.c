#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Helpful resources --
    https://gist.github.com/JBlond/2fea43a3049b38287e5e9cefc87b2124
    https://symbl.cc/en/unicode/blocks
    https://onlinetools.com/unicode/convert-code-points-to-unicode
    https://onlinetools.com/unicode/convert-unicode-to-hex#tool
*/

#define black "\e[0;30m"
#define red "\e[0;31m"
#define green "\e[0;32m"
#define yellow "\e[0;33m"
#define blue "\e[0;34m"
#define purple "\e[0;35m"
#define cyan "\e[0;36m"
#define white "\e[0;37m"
#define reset "\e[0m"

#define strings_cli "char"
#define strings_nargs "expects name of charset -h or --help"
#define strings_xargs "given too many arguments, see -h or --help"
#define strings_version "1.0.0 by https://Modula.dev"
#define strings_help "\
    -v              prints the version number \n\
    -h              prints this help message \n\
charsets\n\
    color, \n\
    block, chess, cards, gamemisc"

void version() { printf("%s %s\n", strings_cli, strings_version); }
void help() { version(); printf("%s\n", strings_help); }
void error(char *message) { printf("%s (error): %s\n", strings_cli, message); }

static int usecolor = 0;
void charout(char *name, char *character, char *code, char *hex){
    printf("    %-16s \e[0;3%dm %s "green"%-12s "reset"%s\n", name, usecolor % 8, character, code, hex); usecolor++;
}

//void arrow(){}
void block() {
    charout("Full", "\xE2\x96\x88", "U+2588", "\\xE2\\x96\\x88");
    charout("Dark Shade", "\xE2\x96\x93", "U+2593", "\\xE2\\x96\\x93");
    charout("Medium Shade", "\xE2\x96\x92", "U+2592", "\\xE2\\x96\\x92");
    charout("Light Shade", "\xE2\x96\x91", "U+2591", "\\xE2\\x96\\x91");
    charout("Upper Half", "\xE2\x96\x80", "U+2580", "\\xE2\\x96\\x80");
    charout("Lower Half", "\xE2\x96\x84", "U+2584", "\\xE2\\x96\\x84");
    charout("Left Half", "\xE2\x96\x8c", "U+258C", "\\xE2\\x96\\x8C");
    charout("Right Half", "\xE2\x96\x90", "U+2590", "\\xE2\\x96\\x90");
}
void cards(){
    charout("Heart Suit", "\xE2\x99\xA5", "U+2665", "\\xE2\\x99\\xA5");
    charout("Diamond Suit", "\xE2\x99\xA6", "U+2666", "\\xE2\\x99\\xA6");
    charout("Spade Suit", "\xE2\x99\xA0", "U+2660", "\\xE2\\x99\\xA0");
    charout("Club Suit", "\xE2\x99\xA3", "U+2663", "\\xE2\\x99\\xA3");
    charout("White Heart", "\xE2\x99\xA1", "U+2661", "\\xE2\\x99\\xA1");
    charout("White Diamond", "\xE2\x99\xA2", "U+2662", "\\xE2\\x99\\xA2");
    charout("White Spade", "\xE2\x99\xA4", "U+2664", "\\xE2\\x99\\xA4");
    charout("White Club", "\xE2\x99\xA7", "U+2667", "\\xE2\\x99\\xA7");
}
void chess(){
    charout("White King", "\xE2\x99\x94", "U+2654", "\\xE2\\x99\\x94");
    charout("White Queen", "\xE2\x99\x95", "U+2655", "\\xE2\\x99\\x95");
    charout("White Rook", "\xE2\x99\x96", "U+2656", "\\xE2\\x99\\x96");
    charout("White Bishop", "\xE2\x99\x97", "U+2657", "\\xE2\\x99\\x97");
    charout("White Knight", "\xE2\x99\x98", "U+2658", "\\xE2\\x99\\x98");
    charout("White Pawn", "\xE2\x99\x99", "U+2659", "\\xE2\\x99\\x99");
    charout("Black King", "\xE2\x99\x9A", "U+265A", "\\xE2\\x99\\x9A");
    charout("Black Queen", "\xE2\x99\x9B", "U+265B", "\\xE2\\x99\\x9B");
    charout("Black Rook", "\xE2\x99\x9C", "U+265C", "\\xE2\\x99\\x9C");
    charout("Black Bishop", "\xE2\x99\x9D", "U+265D", "\\xE2\\x99\\x9D");
    charout("Black Knight", "\xE2\x99\x9E", "U+265E", "\\xE2\\x99\\x9E");
    charout("Black Pawn", "\xE2\x99\x9F", "U+265F", "\\xE2\\x99\\x9F");
}
void color(){
    charout("black", "\xE2\x96\x88", "\\e[0;30m", "\\x1B\\x5B\\x30\\x3b\\x33\\x30\\x6D");
    charout("red", "\xE2\x96\x88",   "\\e[0;31m", "\\x1B\\x5B\\x30\\x3b\\x33\\x31\\x6D");
    charout("green", "\xE2\x96\x88", "\\e[0;32m", "\\x1B\\x5B\\x30\\x3b\\x33\\x32\\x6D");
    charout("yellow", "\xE2\x96\x88","\\e[0;33m", "\\x1B\\x5B\\x30\\x3b\\x33\\x33\\x6D");
    charout("blue", "\xE2\x96\x88",  "\\e[0;34m", "\\x1B\\x5B\\x30\\x3b\\x33\\x34\\x6D");
    charout("purple", "\xE2\x96\x88","\\e[0;35m", "\\x1B\\x5B\\x30\\x3b\\x33\\x35\\x6D");
    charout("cyan", "\xE2\x96\x88",  "\\e[0;36m", "\\x1B\\x5B\\x30\\x3b\\x33\\x36\\x6D");
    charout("white", "\xE2\x96\x88", "\\e[0;37m", "\\x1B\\x5B\\x30\\x3b\\x33\\x37\\x6D");
    printf("    reset             "reset"\xE2\x96\x88"green" \\e[0m "reset"       \\x1B\\x5B\\x30\\x6D\n"); /* this one manually so our coloring doesn't goof */
}
void gamemisc(){
    charout("Hammer & sickle", "☭", "U+262D", "\\xE2\\x98\\xAD");
    charout("Lorraine Cross", "☨", "U+2628", "\\xE2\\x98\\xA8");
    charout("Jerusalem Cross", "☩", "U+2629", "\\xE2\\x98\\xA9");
    charout("Peace Symbol", "☮", "U+262E", "\\xE2\\x98\\xAE");
    charout("Heaven Trigram", "☰", "U+2630", "\\xE2\\x98\\xB0");
    charout("Solid Smiley", "☻", "U+263A", "\\xE2\\x98\\xBA");
    charout("Smiley Face", "☺", "U+263B", "\\xE2\\x98\\xBB");
    charout("d6 Face 1", "⚀", "U+2680", "\\xE2\\x9A\\x80");
    charout("d6 Face 2", "⚁", "U+2681", "\\xE2\\x9A\\x81");
    charout("d6 Face 3", "⚂", "U+2682", "\\xE2\\x9A\\x82");
    charout("d6 Face 4", "⚃", "U+2683", "\\xE2\\x9A\\x83");
    charout("d6 Face 5", "⚄", "U+2684", "\\xE2\\x9A\\x84");
    charout("d6 Face 6", "⚅", "U+2685", "\\xE2\\x9A\\x85");
    charout("White Flag", "⚐", "U+2690", "\\xE2\\x9A\\x90");
    charout("Black Flag", "⚑", "U+2691", "\\xE2\\x9A\\x91");
    charout("Crossed Swords", "⚔", "U+2694", "\\xE2\\x9A\\x94");
    charout("Medical Staff", "⚕", "U+2695", "\\xE2\\x9A\\x95");
    charout("Alembic", "⚗", "U+2696", "\\xE2\\x9A\\x96");
    charout("Gear", "⚙", "U+2699", "\\xE2\\x9A\\x99");
    charout("High Voltage", "⚡", "U+26A1", "\\xE2\\x9A\\xA1");
    charout("Squared Key", "⚿", "U+26BF", "\\xE2\\x9A\\xBF");
    charout("Crossed Shield", "⛨", "U+26E8", "\\xE2\\x9B\\xA8");
    charout("Book", "🕮", "U+1F56E", "\\xF0\\x9F\\x95\\xAE");
}

int main(int argc, char** argv){

    switch(argc) {
        default: error(strings_xargs); exit(1);
        case 1: error(strings_nargs); exit(1);
        case 2: {
            if(strncmp("-h", argv[1], 2)==0 || strncmp("--help", argv[1], 6)==0) { help(); exit(0); }
            if(strncmp("-v", argv[1], 2)==0 || strncmp("--version", argv[1], 9)==0) { version(); exit(0); }
            if(strcmp("color", argv[1])==0)     { color(); exit(0); }
            //if(strcmp("arrow", argv[1])==0)     { arrow(); exit(0); }
            if(strcmp("block", argv[1])==0)     { block(); exit(0); }
            if(strcmp("chess", argv[1])==0)     { chess(); exit(0); }
            if(strcmp("cards", argv[1])==0)     { cards(); exit(0); }
            if(strcmp("gamemisc", argv[1])==0)  { gamemisc(); exit(0); }
        } break;
    }

}
