#include <stdlib.h>
#include <stdio.h> // define the header file
#include <string.h>

int main(int argc, char *argv[]) // args that are caught when running program
{
     if (argc < 2) { //If there are less than one file given give instructions on usage.
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) { //Running program as many times as there are given args
        char current = '\0'; //Terminator char
        char previous;
        int count = 0;
        FILE *fp = fopen(argv[i], "r");

        if (fp == NULL) //If opening file fails
        {
            printf("my-zip: cannot open file\n");
            exit(1);
        }
        //printf("CURRENT ON %c", current);
        while (current != EOF) {  //fgetc returns EOF if end of file
            current = fgetc(fp);
            //printf("Merkki on %c", current);
        // Help to RLE https://stackoverflow.com/questions/20176338/rle-compression-algorithm-c
            if (current == -1){
                break;
                }
            if (current == previous){ //If current character is same as previous make count go up by one
                count++;
            } else{
                if (count != 0) {
                    //printf("%d", count);
                    fwrite(&count, sizeof(int), 1, stdout); //Size of int is always 4 bytes
                    fwrite(&previous, sizeof(char), 1, stdout);
                    }
                previous = current;
                count = 1;

                }
            }
            fwrite(&count, sizeof(int), 1, stdout); // Last round writing in the file.
            fwrite(&previous, sizeof(char), 1, stdout);
            fclose(fp);
            }
            return 0;

        }
    

 
   

