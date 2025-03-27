#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "version.h"
#include "../src/file.c"

#define version_path ".git/version.h"
const char gitperm[] = "chmod +x " version_path;
const char gitscript[] = "#!/bin/bash\nmversion commit\n";
const char scriptpath[] = ".git/hooks/post-commit";
const char gitadd[] = "git add -f " version_path;
const char gitlink[] = "ln -s ./" version_path " ./%s";

const char strings_help[] = "mversion helps manage the version-number string\n\
run \"mversion init\" in a git repository to set up the git hook\n\
run \"mversion set\" to prompt and overwrite the version number\n\
run \"mversion {filename}\" to get a symbolic link to the `version.h`\n\
the `.git/version.h` file will contain a single define that looks like\n\
    #define strings_version \"0.0.0\"\n";

enum { MAJOR, MINOR, PATCH };
const char TAGS[][8] = {
    [MAJOR] = "MAJOR",
    [MINOR] = "MINOR",
    [PATCH] = "PATCH"
};

char cmdbuf[80];

// #define strings_version "##.##.##"
void getVersion(uint32_t *nums) {
    char buffer[80];
    int r = file_read(version_path, buffer, sizeof(buffer)); 
    if ( r <= 0 ) { nums[0] = -1; nums[1] = -1; nums[2] = -1; return; }
    char *header = (char *)(buffer + 25);
    nums[0]  = strtol(header, &header, 10);
    nums[1]  = strtol(header++, &header, 10);
    nums[2]  = strtol(header++, &header, 10);
}

int writeVersion(uint32_t *nums) {
    static char buffer[80];
    sprintf(buffer, "#define strings_version \"%d.%d.%d\"", nums[0], nums[1], nums[2]);
    return file_write(version_path, buffer, sizeof(buffer));
}

void updateVersion(uint32_t *nums, char *commit) {
    int index = 2; // minor by default
    int i; for (i=0;i<3;i++) { if (strncmp(commit, TAGS[i], 5)==0) { index = i; break; } }
    nums[i] ++;
}

char *commit_message() {
    FILE *fp;
    static char commit_msg[1024];
    fp = popen("git log -1 --pretty=%B", "r");
    if (fp == NULL) { perror("Failed to run git log"); return NULL; }
    fgets(commit_msg, sizeof(commit_msg), fp);
    fclose(fp); return commit_msg;
}

void initVersion(uint32_t *nums){
    int i; for(i=0;i<3;i++) {
        printf("    %s > ", TAGS[i]);
        fgets(cmdbuf, sizeof(cmdbuf), stdin);
        nums[i] = strtol(cmdbuf, NULL, 10);
    }
}

int main(int argc, char **argv) {
    uint32_t version_numbers[3] = {0};
    if ( argc == 1 ) { printf(strings_help); exit(0); }
    else if ( strcmp(argv[1], "init")==0 ) {
        if (!file_exists(".git")) { fprintf(stderr, "cwd is not a git repository\n"); exit(1); }
        int w = file_write((char*)scriptpath, (char*)gitscript, sizeof(gitscript));
        if ( w <= 0 ) { fprintf(stderr, "unable to write to %s\n", scriptpath); exit(1); }
        system(gitperm);
        if ( file_exists(version_path) ) { printf("Warning: `version.h` already exists, overwriting\n"); } else { printf("Initialized version as 0.0.0\n"); }
        writeVersion(version_numbers);
    }
    else if ( strcmp(argv[1], "set")==0) {
        if (!file_exists(".git")) { fprintf(stderr, "cwd is not a git repository\n"); exit(1); }
        printf("Enter the new version number.\n");
        initVersion(version_numbers);
        writeVersion(version_numbers);
    }
    else if ( strcmp(argv[1], "commit")==0 ) {
        if (!file_exists(".git")) { fprintf(stderr, "cwd is not a git repository\n"); exit(1); }
        if (!file_exists("version.h")) {
            printf("No version information found.\n");
            initVersion(version_numbers);
            writeVersion(version_numbers);
        }
        else {
            getVersion(version_numbers);
            if ( version_numbers[0] == -1 ) {
                printf("Invalid version information found.\n");
                initVersion(version_numbers);
                writeVersion(version_numbers);
            }
            char *message = commit_message();
            updateVersion(version_numbers, message);
            writeVersion(version_numbers);
        }
        printf("... Updating " version_path );
    }
    else if ( argv[1][0] == '-' ) {
        char tag = argv[1][1]; if ( tag == '-' ) { tag = argv[1][2]; }
        switch ( tag ) {
            default:  fprintf(stderr, "Unknown command %s\n", argv[1]); exit(1);
            case 'v': printf("mversion v %s\n", strings_version); exit(0);
            case 'h': printf(strings_help); exit(0);
        }
    }
    else {
        printf("... creating symlink %s to .git/version.h\n", argv[1]);
        sprintf(cmdbuf, gitlink, argv[1]);
        int s = system(cmdbuf);
        if ( s != 0 ) { fprintf(stderr, "failed to create symlink\n"); exit(1); }
    }
}