#include <stdlib.h>
#include <stdio.h> // define the header file
#include <string.h>

typedef struct lista //struct rakenne ja linked lista C-ohjelmoinnin perusteista esimerkkiä
{
    char line[120];
    struct lista *pNext;
} LISTA;

int main(int argc, char *argv[]) // komentoriviargumentit jotka otetaan kiinni
{
    size_t linesize = 0;
    char *linebuffer;
    size_t buffersize = 0; // alustetaan getlinea varten muuttujia
    if (argc > 3){
        fprintf(stderr,"usage: reverse <input> <output>.\n");
        exit(1);
    }
    char* arg1 = argv[1];
    char* arg2 = argv[2];

    if (arg1 = arg2) {
        fprintf(stderr, "Input and output file must differ.\n");
        exit(1);
    }
    LISTA *pAlku = NULL, *pLoppu = NULL;
    LISTA *pUusi;
    if (argv[1] != NULL){
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("error: cannot open file '%s'", argv[1]);
        exit(1);
    }
    
    while (linesize != -1)
    {
        if(fp != NULL){
        linesize = getline(&linebuffer, &buffersize, fp);
        }
        
        if (linesize == -1) {
            break;
        }
        fprintf(stdout, "%s", linebuffer);
        if ((pUusi = (LISTA *)malloc(sizeof(LISTA))) == NULL)
        {
            perror("malloc failed");
            exit(1);
        }
       
        strcpy(pUusi->line, linebuffer);
        pUusi->pNext = NULL;

        if (pAlku == NULL)
        {
            pAlku = pUusi;
            pLoppu = pUusi;
            
        }
        else
        {
            pLoppu->pNext = pUusi;
            pLoppu = pUusi;
            
        }
       
        
    }


    fclose(fp);
     pUusi = pAlku;
     printf("\nLista oikein päin printattuna. \n");
      while (pUusi != NULL) { /// Printataan lista oikein päin
          //printf("\n");
         printf("%s", pUusi->line);
         pUusi = pUusi->pNext;
     }
    }
    //If after file reading pAlku is still empty -> read from stdin 
    
    if(pAlku == NULL){
     while (linesize != -1)
    {
        
        linesize = getline(&linebuffer, &buffersize, stdin);
        
        printf("%ld", linesize);
        if (linesize == 1) {
            break;
        }
        fprintf(stdout, "%s", linebuffer); 
        if ((pUusi = (LISTA *)malloc(sizeof(LISTA))) == NULL)
        {
            perror("malloc failed");
            exit(1);
        }
       
        strcpy(pUusi->line, linebuffer);
        pUusi->pNext = NULL;

        if (pAlku == NULL)
        {
            pAlku = pUusi;
            pLoppu = pUusi;
            
        }
        else
        {
            pLoppu->pNext = pUusi;
            pLoppu = pUusi;
            
        }
       
    }
    }
   
//////////////////////////////////////////////////////////////////////////////////////////////////////
/*Kirjoitetaan linked listin kääntäminen toisinpäin*/

    LISTA* aiempi = NULL;
    LISTA* nykyinen = pAlku;
    LISTA* seuraava = NULL;
    printf("\nLista käännettynä. \n");
    while (nykyinen != NULL) {
        //printf("Lista käännettynä. \n");
        
        seuraava = nykyinen->pNext;
        
       
        nykyinen-> pNext = aiempi;
        
        aiempi = nykyinen;
        nykyinen = seuraava;
    }
    pAlku = aiempi;
    pUusi = pAlku;
    if (argv[1] != NULL){

    if(argv[2] == NULL){
     while (pUusi != NULL) {
        
          printf("%s\n", pUusi->line);
          pUusi = pUusi->pNext;
      }
      return 0;
    }
   
    FILE *fp2 = fopen(argv[2], "w");
    if (fp2 == NULL) {
        fprintf(stderr, "error: cannot open file '%s'", argv[2]);
        exit(1);
    }
    while (pUusi != NULL) {
     fprintf(fp2, "%s", pUusi->line);
     pUusi = pUusi->pNext;
    }
    fclose(fp2);
    }
    
      
}