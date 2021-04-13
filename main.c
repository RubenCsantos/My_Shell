#include "shell.h"

char prompt[100];

int main ()
{
  int len;
  char linha[1024];		
  char *args[64];		

  strcpy (prompt, "RubenSHELL >>");
  while (1)
    {
      printf ("%s", prompt);

      if (fgets (linha, 1023, stdin) == NULL)
	    {
	      printf ("\n");
	      exit (0);
	    }
      len = strlen (linha);
      if (1 == len)
	    continue;	

      if (linha[len - 1] == '\n')
	    linha[len - 1] = '\0';
      int numargs = parse (linha, args);	

      if (!builtin (args, numargs))
	    {
	      execute (numargs, args);	
	    }
    }
  return 0;
}

int builtin (char **args, int numargs)
{

	if(0 == strcmp(args[0], "isjpg"))
		{
			int fd = open(args[1],O_RDONLY);
			int flag = isjpg(fd);
			
			if(flag == 1)
				printf("O ficheiro é jpg.\n");
			else
				printf("O ficheiro não é jpg.\n");
				
			return 1; //comando embutido
		}

	if (0 == strcmp(args[0], "bits") && (numargs == 4 || numargs == 3))
 		{
 			if(numargs == 4)
 				bits(args[1],args[2],args[3]);
 				
 			if(numargs == 3)
 				negative_bits(args[1], args[2]);
 			return 1 ; //commando embutido
		}

  if (0 == strcmp (args[0], "calc") && numargs == 4)
    {
      calc (args[1], args[2], args[3]);
      return 1;			//comando embutido
    }

  if (0 == strcmp (args[0], "socp"))
    {
      socp (args[1], args[2]);
      return 1;			//comando embutido
    }

  if (0 == strcmp (args[0], "obterinfo"))
    {
      printf ("SoShell 2020 versaõ 1.0\n");
      return 1;			//comando embutido
    }

  if (0 == strcmp (args[0], "cd"))
    {
      int err;

      if (NULL == args[1] || (strcmp (args[1], "~")) == 0)
	err = chdir (getenv ("HOME"));
      else
	err = chdir (args[1]);

      if (err < 0)
	perror (args[1]);
      return 1;			//comando embutido
    }

  if (0 == strcmp (args[0], "quemsoueu"))
    {
      system ("id");
      return 1;			//comando embutido
    }

  if (strlen (args[0]) > 4 && 0 == strncmp (args[0], "PS1=", 4))
    {
      strcpy (prompt, args[0] + 4);
      return 1;			//comando embutido
    }

  if (strcmp (args[0], "sair") == 0)
    {
      exit (0);
      return 1;
    }
  if (strncmp (args[0], "42", 2) == 0)
    {
      printf ("42 is the answer to life the universe and everything\n");
      return 1;			/* funcionalidade embutida */
    }

  if (strcmp (args[0], "avisoTeste")== 0)
  {
    aviso( args[1], atoi (args[2]));
    return 1;
  }

  if (strcmp (args[0], "aviso") == 0)
  {
    pthread_t th;
    aviso_t * ptr = (aviso_t *)malloc(sizeof(aviso_t));
    strcpy(ptr->msg, args[1]);
    ptr->tempo=atoi(args[2]);
    pthread_create (&th, NULL, avisowrapper, (void *)ptr);
    return 1;
  }

  if(strcmp (args[0], "socpth") ==0)
  {
    pthread_t th;
    copiar_t * ptr = (copiar_t *)malloc(sizeof(copiar_t));;
    strcpy(ptr->fonte, args[1]);
    strcpy(ptr->destino,args[2]);
    pthread_create (&th, NULL, socpwrapper, (void *)ptr);
    return 1;
  }

  if(0==strcmp (args[0], "maior"))
  {
    struct stat *a1, *a2;

    a1=(struct stat *)malloc(sizeof(struct stat));
    a2=(struct stat *)malloc(sizeof(struct stat));
    
    stat(args[1], a1);
    stat(args[2], a2);

    if(a1->st_size > a2->st_size)
     {
       printf("%s é o maior ficheiro com um tamanho de %ld KB\n",args[1], (a1->st_size / 1000));
     }
     else{
       printf("%s é o maior ficheiro com um tamanho de %ld KB\n",args[2], (a2->st_size / 1000));
     }
     return 1;
  }

  if(0==strcmp (args[0], "setx"))
  {
    struct stat *a1;

    a1=(struct stat *)malloc(sizeof(struct stat));

    stat(args[1], a1);

    chmod(args[1],a1->st_mode | S_IXUSR);

    return 1;
  }

  if(0==strcmp (args[0], "removerl"))
  {
    struct stat *a1;

    a1=(struct stat *)malloc(sizeof(struct stat));

    stat(args[1], a1);

    chmod(args[1],a1->st_mode & ~S_IRGRP & ~S_IROTH);

    return 1;
  }

  if(0==strcmp (args[0], "sols"))
  {

    struct dirent **files;

    char pathname[5000];

    if(args[1] == NULL)
    {
      strcpy(pathname, ".");
    }
    else
    {
      opendir(pathname);
    }


    int count=scandir(pathname,&files,file_select,alphasort);

    if(count <= 0)
    {
      printf("Não existem ficheiros na diretoria\n");

      return 1;
    }

    for(int i=0; i< count; i++)
    {
        printf("%s \n",files[i]->d_name );
    }

    return 1;
  }

  return 0;
}

int file_select(const struct dirent *entry)
{
  if ((strcmp(entry->d_name,".") == 0) || (strcmp(entry->d_name, "..")==0))
  
  return(0); //0 -> FALSE
  
  return(1);  //1 -> TRUE
}
