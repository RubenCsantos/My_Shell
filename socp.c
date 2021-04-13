#include "shell.h"

int BUFFSIZE = 128;


void socp (char *fonte, char *destino)
{

  int fdIn = open (fonte, O_RDONLY);
  if (fdIn < 0)
  {
    perror ("Erro ao abrir ficheiro!\n");
  }

  int fdOut = creat (destino, S_IRUSR | S_IWUSR);

  if (fdOut < 0)
  {
    perror ("Erro ao criar ficheiro!\n");
  }

  ioCopy (fdIn, fdOut);

  fprintf (stderr, "Copia feita com BlockSize %d\n", BUFFSIZE);
}

void ioCopy (int IN, int OUT)
{
  int n;
  char *buf = malloc (BUFFSIZE);

  while ((n = read (IN, buf, BUFFSIZE)) > 0)
    {
      if (write (OUT, buf, n) != n)
      {
	      perror ("Erro de escrita!\n");
      }
    }

  if (n < 0)
  {
    perror ("Erro de leitura!\n");
  }
}

void *socpwrapper (void *args)
{
  copiar_t * ponteiro = (copiar_t *) args;
  socp(ponteiro->fonte, ponteiro->destino);
  free(ponteiro);
  return NULL;
}