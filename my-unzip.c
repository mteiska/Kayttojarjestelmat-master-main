#include <stdlib.h>
#include <stdio.h> // define the header file
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) { //If there are less than one file given give instructions on usage.
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }
    for (int i = 1; i < argc; i++) { //Running program as many times as there are given args
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("my-unzip: cannot open file\n");
            exit(1);
        }
        int count;

        char character;
        //Help to RLE https://stackoverflow.com/questions/20176338/rle-compression-algorithm-c

        while (fread(&count, sizeof(int), 1, fp) == 1) {
            int read_items = fread(&character, sizeof(char), 1, fp);
            if(read_items != 1){
            break;
        }

            for (int k = 0; k < count; k++) {
                printf("%c", character);
            }
        }
        fclose(fp);
    }
    return 0;
}