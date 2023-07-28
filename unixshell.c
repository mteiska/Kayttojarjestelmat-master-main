#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

//Authors: Kasper Gröhn ja Mika Teiska

char virhe_viesti[30] = "An error has occurred\n";
#define PUSKURI 64
#define EROTIN " \t\r\n\a"

// Aliohjelmien esittely:
int shellExit(char **taulukko);
int shellcd(char **taulukko);
int shellHelp(char **taulukko);
void virheViesti();
int shellStart(char **taulukko);
int shellExecute(char **taulukko);
char *shellRead(void);
char **jaarivit(char *rivi);

char *komennot[] = { // Sisäkomennot
  "cd",
  "exit",
  "help"
};

int (*sisaanrakennetut[]) (char **) = {
  &shellcd,
  &shellHelp,
  &shellExit
};
// Errorhandling-function
void virheViesti() 
{
  write(STDERR_FILENO, virhe_viesti, strlen(virhe_viesti));
}
int maara() {
  return sizeof(komennot) / sizeof(char *);
}
// Sisäänrakennettujen komentojen toteutukset:

int shellcd(char **taulukko) 
{
  if (taulukko[1] == NULL)
  {
    fprintf(stderr, "wish: expected argument to \"cd\"\n");
  } 
  else
  {
    if (chdir(taulukko[1]) != 0) {

      perror("wish");
    }
    }
  return 1;
}

int shellHelp(char **taulukko) 
{
  printf("Basic commands:\n");

  for (int i = 0; i < maara(); i++) 
  {
    printf("%s\n", komennot[i]);
  }
  return 1;
}

int shellExit(char **taulukko) 
{
  return 0;
}

int shellStart(char **taulukko) 
{
  int tila;
  pid_t pid;

  pid = fork();
  if (pid == 0) {
    // childProcess
    if (execvp(taulukko[0], taulukko) == -1) 
    {
      printf("wish: No such file or directory\n");
      exit(EXIT_FAILURE);
    }
  } 
  else if (pid < 0) 
  {
    // Virhe haaroituksessa
    virheViesti(); // Tulosta virheviesti stderr:iin
  } 
  else 
  {
    // parentProcess
    do 
    {
      if (waitpid(pid, &tila, WUNTRACED) == -1) 
      {
        virheViesti(); //Tulosta virheviesti.
      }
    } while (!WIFEXITED(tila) && !WIFSIGNALED(tila));
  }

  return 1;
}

int shellExecute(char **taulukko)
{
  if (taulukko[0] == NULL)
  {
    // Jos tulee tyhjä komento niin,
    return 1;
  }

  for (int i = 0; i < maara(); i++)
  {
    if (strcmp(taulukko[0], komennot[i]) == 0)
    {
      return (*sisaanrakennetut[i])(taulukko);
    }
  }

  return shellStart(taulukko);
}


char **jaarivit(char *rivi) 
{
  int koko = PUSKURI; 
  int paikka = 0;
  char **taulukko = malloc(koko * sizeof(char*));
  char *erottimet, **varmuustaulukko;

  if (!taulukko) 
  {
    virheViesti();
    exit(EXIT_FAILURE);
  }

  erottimet = strtok(rivi, EROTIN);
  while (erottimet != NULL)
  {
    taulukko[paikka] = erottimet;
    paikka++;

    if (paikka >= koko)
    {
      koko += PUSKURI;
      varmuustaulukko = taulukko;
      taulukko = realloc(taulukko, koko * sizeof(char*));
      if (!taulukko) 
      {
        free(varmuustaulukko);
        virheViesti(); // Tulosta virheviesti stderr:iin
        exit(EXIT_FAILURE);
      }
    }

    erottimet = strtok(NULL, EROTIN);
  }
  taulukko[paikka] = NULL;
  return taulukko;
}
char *shellRead(void) 
{
  char *rivi = NULL;
  ssize_t puskurin_koko = 0;
  if (getline(&rivi, &puskurin_koko, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);
    } else  {
      virheViesti(); // Tulosta virheviesti stderr:iin
      exit(EXIT_FAILURE);
    }
  }
  return rivi;
}

int main(int argc, char **argv) //Main-program
{
  char *rivi;
  char **taulukko;
  int status;
  bool testi = false;

  if (argc > 1) {
    testi = true;
  }

  do {
    if (!testi) {
      printf("wish> ");
      fflush(stdout);
    }

    rivi = shellRead();
    taulukko = jaarivit(rivi);

    if (taulukko[0] == NULL)
    {
      free(rivi);
      free(taulukko);
      continue;
    }

    if (strcmp(taulukko[0], "exit") == 0)
    {
      free(rivi);
      free(taulukko);
      break;
    }

    if (strcmp(taulukko[0], "cd") == 0)
    {
      shellcd(taulukko);
      free(rivi);
      free(taulukko);
      continue;
    }

    if (strcmp(taulukko[0], "help") == 0) 
    {
      shellHelp(taulukko);
      free(rivi);
      free(taulukko);
      continue;
    }

    status = shellExecute(taulukko);

    free(rivi);
    free(taulukko);

  } while (status);

  return 0;
}
///end