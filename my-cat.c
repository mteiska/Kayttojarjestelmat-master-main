#include <stdlib.h>
#include <stdio.h> // define the header file
#include <string.h>




int main(int argc, char *argv[]) // komentoriviargumentit jotka otetaan kiinni
{
    size_t linesize = 0;
    char *linebuffer;
    size_t buffersize = 0; // alustetaan getlinea varten muuttujia
    if(argv[1]== NULL){
        exit(0);
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("cannot open file\n");
        exit(1);

    }
    while (linesize != -1){
        linesize = getline(&linebuffer, &buffersize, fp);
        printf("%s", linebuffer);
        }
    fclose(fp);




return 0;
}