#include <stdlib.h>
#include <stdio.h> // define the header file
#include <string.h>




int main(int argc, char *argv[]) // komentoriviargumentit jotka otetaan kiinni
{

    size_t linesize = 0;
    char *linebuffer;
    size_t buffersize = 0; // alustetaan getlinea varten muuttujia
    
    if(argc == 1){
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }
    
    //If no word given print whole while contents
    //printf("%s %s %s %s", argv[0], argv[1], argv[2], argv[3]);
    if(argv[1]== NULL){
    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL) {
        printf("my-grep: cannot open file\n");
        exit(1);

    }
        while (linesize != -1){
        linesize = getline(&linebuffer, &buffersize, fp);
        printf("%s", linebuffer);
        }
    fclose(fp);
    }

    if(argv[2]==NULL){
      char *line_stdin =NULL;

   
    printf("Give line to grep:\n");
    linesize = getline(&line_stdin, &buffersize, stdin);
    if(strstr(line_stdin,argv[1])){
    printf("%s",line_stdin);
    return 0;
    }

    }
    //Normal grep if 
    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL) {
        printf("my-grep: cannot open file\n");
        exit(1);

    }
    while (linesize != -1){
        linesize = getline(&linebuffer, &buffersize, fp);
         
        if(linesize != -1){
         if(strstr(linebuffer,argv[1])){
           
            printf("%s",linebuffer);
        }
        }
        
        }

    fclose(fp);

    if(argc > 3 ){
        int i;
         for (i = 2; i >=argc; ++i){
            FILE *fp = fopen(argv[i], "r");
             if (fp == NULL) {
                printf("my-grep: cannot open file\n");
                exit(1);

             }
            while (linesize != -1){
                linesize = getline(&linebuffer, &buffersize, fp);
                if(strstr(linebuffer,argv[1])){
                    printf("%s",linebuffer);
                    }
        
                }
                fclose(fp);


         }
    }




return 0;
}