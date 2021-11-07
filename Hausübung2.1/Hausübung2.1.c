#include <stdio.h>
#include <stdlib.h>
int k,u,t=0;
int arr[1000];
int a,b,c,d;

void Process(){ // die gesamte Eingabe und Berechnung in void funk.(sozusagen Process) erfolgt, nicht in main funk.

printf("Pls enter a number for a,b,c,d\n");

    if((scanf("%d",&a) == 1)&& (scanf("%d",&b) == 1)&& (scanf("%d",&c) == 1)&& (scanf("%d",&d) == 1)){ //als Konsoleneingaben abfragt und inputs kontrolliert

        if(a>=0 && b>=0 && c>=0 && d>0){ //  Pruefung ob a >= 0, b >= 0, c >= 0, d > 0 sind

            printf("Numbers are entered in accordance with the procedure\n");

              for(int n=0;n<d;n++){ //alle Werte von n in For-Schleife nacheinander durchprobiert werden

        u= a*n*n+n*b+c;

        k=(u%d);

        if(k==0){ //an^2 + bn + c ohne Rest durch d teilbar
            arr[t]=n; //n Werte werden der Reihe zugeordnet
            t=t+1; //Organisiert die Anzahl der Elemente des Arrays, wobei jedes Mal um 1 erhoeht wird
        }

    }

}
        else {
    printf("your input is not valid , it should fit this a >= 0, b >= 0, c >= 0,d > 0 .\n");
    }
} else {
    printf("your input is not valid and not an integer\n");
    }
    if(arr[0]== 0 && arr[1]== 0 ){  //wenn es kein Element in der Reihe gibt ,oder man kann auch -> sizeof(arr) /sizeof(arr[0])
       if(d==1){
            printf("n equals to zero\n");
        }
        else{
        printf("No solutions for n.\n"); // keine Loeungen fuer n
        }
    }
    else{
        for(int o=0;o<t;o++){   //mit For-Schleife werden die Serie ausgegeben
            printf("****n = %d****\n",arr[o]);
        }
    }
}
int main()
{
    Process(); //Funktion wird in main aufgerufen
    return 0;
}
