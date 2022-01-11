#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getstringfromuserinput(int size, char *s, const char *request)
{
  printf("%s", request);
  fgets(s, size, stdin);
  int l = strlen(s);
  if (s[l - 1] == '\n'){
    s[l - 1] = '\0';
  }
  return;
}

void lineNumbers(const char filename[], int *line)
{
  FILE *infile;
  int i = 0;
  char temporary[100];
  infile = fopen(filename, "r");
  for (; fgets(temporary, 60, infile) != NULL;) //loop does not continue when data is finished reading from file
    *line = ++i; //determines the number of lines at this time
  fclose(infile);
  return;
}

void readdatafromfile(double *xx, double *yy, double *zz, const char filename[], int count)
{
  FILE *infile;
  infile = fopen(filename, "r");

  for (int i = 0; i < count; ++i)
  {
    fscanf(infile, "%lf %lf %lf", &xx[i], &yy[i], &zz[i] ); //to read x , y and z lines
  }
  fclose(infile);
  return;
}

void writedatatofile(double *x, double *y, double *z, const char *filename, int count)
{
  double *xx;
  double *yy;
  FILE *outfile;
  outfile = fopen(filename, "w");
     // Allocate memory for pointers
    xx = (double *)malloc(count * sizeof(double *));
    yy = (double *)malloc(count * sizeof(double *));
  for (int i = 0; i < count; i++)
  {
    //to transform three-dimensional coordinates with the perspective projection into two-dimensional coordinates
    xx[i] = x[i]/z[i];
    yy[i] = y[i]/z[i];
    fprintf(outfile, "%lf %lf \n", xx[i], yy[i]); //writing in to file the new x and y values
  }
  fclose(outfile);
  return;
}

int main () {

    char infilename[100];

    char outfilename[100];

    int line;

    double *x;
    double *y;
    double *z;

    getstringfromuserinput(100, infilename, "Input File Address: ");

    getstringfromuserinput(100, outfilename, "Output File Address: ");

    lineNumbers(infilename, &line);

    // Allocate memory for pointers
    x = (double *)malloc(line * sizeof(double));

    y = (double *)malloc(line * sizeof(double));

    z = (double *)malloc(line * sizeof(double));

    readdatafromfile(x, y, z, infilename, line);

    writedatatofile(x, y, z, outfilename, line);

   return(0);
}
