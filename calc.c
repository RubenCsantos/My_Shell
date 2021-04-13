#include "shell.h"

void calc (char *value1, char *op, char *value2)
{

  float x= atof(value1);
  float y= atof(value2);

  if (strcmp (op, "+") == 0)
  {
    printf ("%f\n", (x+y));
  }

  if (strcmp (op, "-") == 0)
  {
    printf ("%f\n",  (x-y));
  }

  if (strcmp (op, "*") == 0)
  {
    printf ("%f\n",  (x*y));
  }


  if (strcmp (op, "/") == 0)
  {
    printf ("%f\n",  (x/y));
  }

  if (strcmp (op, "^") == 0)
  {
    printf ("%f\n", powf (x,y));
  }

}

void bits (char *value1, char *op, char *value2)
{
  
  int x= atof(value1);
  int y= atof(value2);

	if (strcmp (op, "&") == 0)
  {
    printf ("%d\n", (x & y));
  }
    
  if (strcmp (op, "^") == 0)
  {
    printf ("%d\n", (x ^ y));
  }
    
  if (strcmp (op, "|") == 0)
  {
    printf ("%d\n", (x | y));
  }
    
  if (strcmp (op, ">>") == 0)
  {
    printf ("%d\n", (x >> y));
  }
    
  if (strcmp (op, "<<") == 0)
  {
    printf ("%d\n", (x << y));
  }

}

void negative_bits(char *op, char *value)
{
	
  int a= atoi(value);

	if (strcmp (op, "~") == 0)
  {
    printf ("%d\n", ~(a));
  }

}

int isjpg(int fileDescriptor) //esboço da função
{
	unsigned char b[4];
	
	read(fileDescriptor,b,4);
 	lseek(fileDescriptor,0,SEEK_SET);//voltar ao inicio do ficheiro com lseek
	
	if ( b[0]==0xff && b[1]==0xd8 && b[2]==0xff && b[3]==0xe0)
 		return 1;
	
	return 0;
}
