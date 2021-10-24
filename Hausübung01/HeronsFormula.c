#include <stdio.h>
#include <stdlib.h>
#include <math.h>

   int AreaofaTriangle(int a,int b, int c) //Berechnung des Flächeninhalts mittels der Heronschen Formel(Funktion)
{
   double s,Area;

   s = sqrt((a+b+c)*(a+b-c)*(a-b+c)*(-a+b+c));
   Area = (0.25)*s;
   printf("%f", Area);
   return Area;
}

int main()
{
    int a,b,c;
    printf("\n Pls enter number for a,b,c \n"); //Abfragung der Seitenlängen a, b und c als Nutzer_inneneingabe
    scanf("%d,%d,%d",&a,&b,&c);

    if ((a+b >c) && (a+c >b) && (b+c >a)) {      // Prüfung ob die Dreiecksungleichungen erfüllt sind
        printf("\n Heron's surface formula:\n");  //Ausgabe das Ergebnis
        AreaofaTriangle(a,b,c);
    }
    else {        // wenn eine dieser Ungleichungen nicht erfüllt sind
        printf("The values you entered are not suitable for creating triangles."); //Abbrechen mit einer Fehlermeldung
    }

    return 0;
}
