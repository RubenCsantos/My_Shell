#include "shell.h"

int ultimo(int *numargs, char **args)
{
  if (strcmp (args[*numargs - 1], "&") == 0)
    {
      *numargs = *numargs - 1;
      args[*numargs] = NULL;
      return BG;
    }

  return FG;	
}

int containsPipe (int numArgs, char **args)
{
	int index;
 
 	for (index = 0; index < numArgs; index++)
 		if (args[index][0] == '|')
 		{
			return index;
 		}
 		
 return -1;
}

void execute (int numargs, char **args)
{
  int pid, status, pid2, indice = containsPipe(numargs, args);
  int p[2], codigo = ultimo (&numargs, args);

  if ((pid = fork ()) < 0)
    {											
      perror ("forks");		
      exit (1);													
    }

  if (pid == 0)
    {
    	numargs = redirects (numargs, args);
    	
    	if(indice == -1){

      	if (numargs == -1)
					exit (1);						
														
      	execvp (*args, args);	
    	}	
    												
    	else
		{
    	
    		args[indice] = NULL;
    		numargs -= 1;
    		
    		if(pipe(p) < 0)
    			exit(1);
    			
    		pid2 = fork();
    		
    		if(pid2 == 0)
    		{
    			numargs = indice;
    			
    			numargs = redirects (numargs, args);

          if (numargs == -1)
          exit (1);
    			  			
    			dup2(p[1], STDOUT_FILENO);
    			close(p[0]);
    			execvp(*args, args);
    		}
    		else
    		{
    			
    			args = args + indice +1;
    			numargs = numargs - indice -1;
    			
          numargs = redirects (numargs, args);

          if (numargs == -1)
          exit (1);
            
    			dup2(p[0], STDIN_FILENO);
    			close(p[1]);
    			execvp(*args, args);
    		}
    	}
    	
    perror (*args);
    exit(1);
    }												
  
  
  if (FG == codigo)
    {
      while (wait (&status) != pid)
				;
				//não faz nada 
    }
    
  return;
}

