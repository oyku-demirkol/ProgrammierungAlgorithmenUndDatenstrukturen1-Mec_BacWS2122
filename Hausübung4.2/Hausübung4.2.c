#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void alloctxt(char ***txtData, int count) //txtData 2d pointer array , count=line
{
  // Allocate memory for pointers to columns
  char **wordCount;
  wordCount = (char **)malloc(count * sizeof(char *)); //line
  // Allocate the actual memory for data column by column
  for (int i = 0; i <count; ++i)
    wordCount[i] = (char *)malloc(60 * sizeof(char *)); //inside of line
  // Return root pointer of 2D array via pointer parameter
  *txtData = wordCount; //txtData pointer to outside
  return;
}

void counteR(const char filename[], int *count)
{
  FILE *infile;
  int i = 0;
  char holder[100];
  infile = fopen(filename, "r");
  for (; fgets(holder, 60, infile) != NULL;) //loop does not continue when data is finished reading from file
    *count = ++i; //determines the number of lines at this time
  fclose(infile);
  return;
}

void writedatatofile(char **data, const char *filename, int count)
{
  FILE *outfile;
  outfile = fopen(filename, "w");
  for (int i = 0; i < count; i++)
  {
    fprintf(outfile, "%s", data[i]); //writing in to file
  }
  fclose(outfile);
  return;
}

void getstringfromuserinput(int size, char *s, const char *request)
{
  printf("%s", request);
  fgets(s, size, stdin);
  int l = strlen(s);
  if (s[l - 1] == '\n')
    s[l - 1] = '\0';
  return;
}

void bubblesort(char **data, int count)
{
  char *aux;
  for (int i = 0; i < count; i++)
  {
    for (int j = 0; j < count - i - 1; j++)
    {
      if (strcmp(data[j], data[j + 1]) > 0) //strcmp = comparing strings
      {
        aux = data[j];
        data[j] = data[j + 1];
        data[j + 1] = aux;
      }
    }
  }
  return;
}

void readdatafromfile(char **data, const char filename[], int count)
{
  FILE *infile;
  infile = fopen(filename, "r");
  for (int i = 0; i < count; ++i)
  {
    fgets(data[i], 60, infile); //reads a line from the specified stream and stores it into the string pointed to by str
  }
  fclose(infile);
  return;
}

int main()
{

  char infilename[100];

  char outfilename[100];

  char **mydata;

  int count;
  getstringfromuserinput(100, infilename, "Name der Eingabedatei: ");
  getstringfromuserinput(100, outfilename, "Name der Ausgabedatei: ");
  counteR(infilename, &count);
  printf("%d lines", count);
  alloctxt(&mydata, count); //txtData = mydata , count = count (but different counts)
  readdatafromfile(mydata, infilename, count);
  bubblesort(mydata, count);
  writedatatofile(mydata, outfilename, count);
  return 0;
}
