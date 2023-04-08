#include <stdlib.h>
#include <stdio.h> // define the header file
#include <string.h>




int main(int argc, char *argv[]) // args that are taken to the program
{
    

   
    size_t linesize = 0;
    char *linebuffer;
    size_t buffersize = 0; // Defining variables for the program
    if(argv[1]== NULL){
       
        exit(0);
    }
    if(argc > 2 ){
        int i;
        //Looping through args to cat many files at once if many files are given
        for (i = 1; i <= argc -1 ; ++i){
            size_t linesize = 0;
            char *linebuffer;
            size_t buffersize = 0; 
          
          
            FILE *fp = fopen(argv[i], "r");
            
            if (fp == NULL) {
                printf("cannot open file\n");
                exit(1);
               
                }
            while (linesize != -1){
                linesize = getline(&linebuffer, &buffersize, fp);
                if(linesize == -1){
                    break;
                    }
                printf("%s", linebuffer);
                }
            fclose(fp);

         }


    }
    
    
    else{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("cannot open file\n");
        exit(1);

    }
    while (linesize != -1){
     
        linesize = getline(&linebuffer, &buffersize, fp);
           if(linesize == -1){
            break;
        }
        printf("%s", linebuffer);
        }
    fclose(fp);
    }



return 0;
}