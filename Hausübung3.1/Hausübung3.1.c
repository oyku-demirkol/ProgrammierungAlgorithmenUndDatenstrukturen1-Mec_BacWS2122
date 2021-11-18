#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define g 9.80665 //g bezeichnet die Fallbeschleunigung g = 9.80665 ms^-2

void Process1(float *T, float *Ve, float *h)
{

  *T = sqrt((2 *( *h)) / g); //die Fallzeit T bis zum Boden errechnet
  *Ve = g * (*T);          //die End- (Aufschlag-)geschwindigkeit vE
}

void Process2(float *T, float *Ve)
{
  printf("Period %f and Speed %f", *T, *Ve);
}

char *Process3()
{
  char *arr_Y = calloc(sizeof(char), 100);
  fgets(arr_Y, 100, stdin);
  return arr_Y;
}

void Process(float *T, float *Ve, float *h)
{

  printf("Pls enter a number for h(the height h of a free fall):\n"); //das interaktiv die Hoehe h eines freien Falls (in Metern) abfragt

  do
  {
    char *arr_Y = Process3();

    if (sscanf(arr_Y,"%f", h) && (*h >= 0)) //Zum Abfangen von Fehleingaben
    {

      Process1(T, Ve, h);

      Process2(T, Ve);
      break;
    }
    else
    {
      printf("Enter a valid Number \n");
    }
  } while (1 == 1);
}
int main()
{
  float T, Ve, h;
  Process(&T, &Ve, &h); //Funktion wird in main aufgerufen

  return 0;
}
