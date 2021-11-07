#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES

int x=0;
float r=0,u=0,v=0,angle;

void Process1(){ //die gesamte Eingabe und Berechnung in void funk.(sozusagen Process1) erfolgt, nicht in main funk.

    float vector1[3]; // array of size=3;
    float vector2[3];
    float cross_P[3];

    printf("Enter the first vector\n"); //die Koordinaten des Vektor1 R^3 als Konsoleneingaben entgegennimmt
    for(int i=0;i<3;i++){
    printf("%d. coordinate:\n",i+1);
    if (scanf("%f",&vector1[i])== 1){

    } else{
    printf("you entered not a valid value\n");
    exit(0);
    }
                }
    printf("Enter the second vector\n"); //die Koordinaten des Vektor2 R^3 als Konsoleneingaben entgegennimmt
    for(int k=0;k<3;k++){
    printf("%d. coordinate:\n",k+1);
    if(scanf("%f",&vector2[k])== 1){

    } else{
    printf("you entered not a valid value\n ");

    exit(0);

    }
                }

    //das Skalarprodukt = vector1*vector2
    for(; x < 3; x ++) { //vector1*vector2 = vector1[0]*vector2[0] + vector1[1]*vector2[1]+ vector1[2]*vector2[2]
    r += (vector1[x]*vector2[x]) ; // r = vektor1[x]*vektor2[x] + r

   }
    printf("Dot product: %f\n",r);

    //das Vektorprodukt = vector1 x vector2
    cross_P[0] = (vector1[1] * vector2[2]) - (vector1[2] * vector2[1]);
    cross_P[1] = (vector1[2] * vector2[0]) - (vector1[0] * vector2[2]);
    cross_P[2] = (vector1[0] * vector2[1]) - (vector1[1] * vector2[0]);

    printf("Cross product: ( %f, %f, %f)\n", cross_P[0], cross_P[1], cross_P[2]);


    for(int m = 0; m < 3; m ++) { //u = vector1*vector1 = vector1[0]*vector1[0] + vector1[1]*vector1[1]+ vector1[2]*vector1[2]
    u += vector1[m] * vector1[m];
   }
   printf(" u^2 = %f \n",u);

    for(int n = 0; n < 3; n ++) { //v = vector2*vector2 = vector2[0]*vector2[0] + vector2[1]*vector2[1]+ vector2[2]*vector2[2]
    v += vector2[n] * vector2[n];
   }
    printf(" v^2 = %f \n",v);

    if(v==0 || u==0){ //wenn u oder v der Nullvektor ist,können mathematische Operationen nicht durchgeführt werden.
        printf("you entered zero vector,program cannot calculate angle because of zero vector\n");
        exit(0);
    }
    //den Winkel zwischen den Vektoren
    angle = acos(r/(sqrt(u*v)))*(180.0 / M_PI); //das Ergebnis werden mit (180.0 / M_PI) noch in Grad umgerechnet .
    printf("Angle: %f degree\n",angle);
}

int main()
{

    Process1(); //Funktion wird in main aufgerufen

    return 0;
}


