#include "shell.h"
#define FILE_MODE ( S_IRUSR | S_IWUSR )



int redirects (int numargs, char *args[])
{

  if (numargs < 3)
    return numargs;

  if (strcmp (args[numargs - 2], ">") == 0)
    {

      int ficheiro = creat (args[numargs - 1], FILE_MODE);
      if (ficheiro < 0)
	{
	  perror (NULL);
	  return -1;		
	}

      dup2 (ficheiro, STDOUT_FILENO);
      close (ficheiro);
      args[numargs - 2] = NULL;
      numargs = numargs - 2;
    }

  if (numargs>1 && strcmp (args[numargs - 2], ">>") == 0)
    {

      int ficheiro = open (args[numargs - 1], O_WRONLY | O_APPEND | O_CREAT, FILE_MODE);
      if (ficheiro < 0)
	{
	  perror (NULL);
	  return -1;
	}

      dup2 (ficheiro, STDOUT_FILENO);
      close (ficheiro);
      args[numargs - 2] = NULL;
      numargs = numargs - 2;
    }

  if (numargs>1 && strcmp (args[numargs - 2], "<") == 0)
    {

      int ficheiro = open (args[numargs - 1], O_RDONLY, FILE_MODE);
      if (ficheiro < 0)
	{
	  perror ("FILE DOESN'T EXISTS");
	  return -1;
	}

      dup2 (ficheiro, STDIN_FILENO);
      close (ficheiro);
      args[numargs - 2] = NULL;
      numargs = numargs - 2;
    }

		if (numargs>1 && strcmp(args[numargs -2], "2>") == 0)
			{
			int ficheiro = open (args[numargs - 1], O_WRONLY | O_APPEND | O_CREAT, FILE_MODE);
			if (ficheiro < 0)
			{
	  		perror (NULL);
	  		return -1;
			}
			
			dup2 (ficheiro, STDERR_FILENO);
      close (ficheiro);
      args[numargs - 2] = NULL;
      numargs = numargs - 2;
		}

  return numargs;
}
