/*
  
  CS302/ECE46810

  Name: Javier Campos

  Assignment: #1

  Due Date: 1/21/2019


  
  Filter program written in C that formats a stream of input numbers. Program outputs the stream of numbers into organized columns. The       precision of each number can be formated as well. These two settings can be changed through a configure file, environmental variables or   through
  a command line/prompt.



  Default Values:

    Precision=13

    Columns=3

*/



#include <stdlib.h>

#include <stdio.h>



int main(int argc, char *argv[])

{


  int precision = 13;

  int columns = 3;



  // Override default values with values from the config file

  FILE *fp;
  if( (fp = fopen("filter.cfg","r")) != NULL)

  {

    fscanf(fp, "%d %d", &precision, &columns);

  }



  // Override default values through environment variables

  char *op = getenv("CS302HW1PRECISION");

  if(op != NULL)

  {

    precision = atoi(op);

  }



  char *po = getenv("CS302HW1COLUMNS");

  if(po != NULL)

  {

    columns = atoi(po);

  }



  // Override default values from command line arguements

  switch(argc)

  {

    case 2:

      precision = atoi(argv[1]);

      break;

    case 3:

      precision = atoi(argv[1]);

      columns = atoi(argv[2]);

      break;

    default:

    break;

  }



  double x;

  int counter = 0; // Tracks when to start a new row

  //width is equal to precision + 5 (maximum digit is only 10,000)

  int width = precision + 5;


  
  // Reads input and prints formated output until EOF is reached

  while( scanf("%lf", &x) != EOF)

  {

    counter = counter + 1;

    printf("%*.*f  ", width, precision, x);


    if(counter == columns)

    {
      
      printf("\n");

      counter = 0;

    }

  }



  printf("\n");



  return 0;

}
