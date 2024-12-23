#include <stdlib.h>
#include<stdio.h>
#include<string.h>

#define SIZE_BUFFER 256
int err(char *message) {
    printf("%s", message);
    return 1;
}

int help() {
    printf("fwork [param] [filename...]\n");
    printf("PARAMS\n-c [filename]\tCreate file\n");
    printf("-r [filename]\tRemove file\n");
    printf("-cp [filename, copyFilename]\tCopy file\n");
    printf("-m [filename, path]\tMoving file\n");
    printf("-help\tHelp list\n");
    return 1;
}

int createFile(char *filename) {
    FILE *fp = fopen(filename, "w");
    if(!fp) {
        err("[-]Error create file\n");
    }
    printf("[+]File created\n");
    fclose(fp);

    return 1;
};



int removeFile(char *filename) {
    if(remove(filename) == -1) {
        err("[-]File doesnt exist\n");
    } else {
        printf("[+]File remove\n");
    }
    return 1;
}

int moveFile(char *filename, char *path) {
    char *buffer = malloc(SIZE_BUFFER);
    FILE *fp = fopen(filename, "r");
    FILE *mfp = fopen(path, "w");
    if(fp && mfp) {
        while(fgets(buffer, SIZE_BUFFER, fp)!=NULL) {
            fputs(buffer, mfp);
        }
        remove(filename);
        printf("[+]File moving");
    } else {
        err("[-]Some of the file did not open");
    }
    return 1;
}


int copyFile(char *filename, char *copyFilename) {
    char *buffer = malloc(SIZE_BUFFER);
    FILE *fp = fopen(filename, "r");
    FILE *cpfp = fopen(copyFilename, "w");
    if(fp && cpfp) {
        while(fgets(buffer, SIZE_BUFFER, fp)!=NULL) {
            fputs(buffer, cpfp);
        }
    } else {
        err("[-]Some of the file did not open");
    }
    printf("[+]File copyed\n");
    return 1;

}


int main(int argc, char **argv) {
    if(argc == 2) {
        if(!(strcmp(argv[1], "-help"))) {
            help();
        } else {
            err("[-]Params not find. Enter -help for viewing params");
        }
    } else if(argc == 3) {
        if(strcmp(argv[1], "-c") == 0) {
            char *filename = argv[2];
            createFile(filename);
        } else if(strcmp(argv[1], "-r") == 0) {
            char *filename = argv[2];
            removeFile(filename);
        } else {
            err("[-]Error params. Enter -help for viewing params\n");
        }
    } else if(argc == 4) {
        if(strcmp(argv[1], "-cp") == 0) {
            char *filename = argv[2], *copyFilename = argv[3];
            copyFile(filename, copyFilename);
        } else if(strcmp(argv[1], "-m") == 0) {
            char *filename = argv[2], *path = argv[3];
            moveFile(filename, path);
        } else {
            err("[-] Error params. Enter -help for viewing params");
        }
    }else {
        err("[-]Bad params. Enter -help for viewing params");
    }
    return 0;
}
