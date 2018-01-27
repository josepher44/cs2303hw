/* triangle.c  -- Joe Gallagher */
#include <stdio.h>
#include <math.h>

//Computes the distance between two points input as X and Y coordinates
float distanceFormula(float x1, float y1, float x2, float y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int main(void)

{
    //Declare coordinates
    float A_x, A_y, B_x, B_y, C_x, C_y;
    
    //Declare side lengths
    float AB, BC, CA;
    
    //Declare computed values
    float Circ, Area;

    //Take input values from user
    printf("Enter the x and y coordinates of point A, seperated by spaces:- ");
    scanf("%f %f", &A_x, &A_y);
    printf("Enter the x and y coordinates of point B, seperated by spaces:- ");
    scanf("%f %f", &B_x, &B_y);
    printf("Enter the x and y coordinates of point C, seperated by spaces:- ");
    scanf("%f %f", &C_x, &C_y);
    
    //Calculate side lengths, using distance formula
    AB=distanceFormula(A_x, A_y, B_x, B_y);
    BC=distanceFormula(B_x, B_y, C_x, C_y);
    CA=distanceFormula(C_x, C_y, A_x, A_y);
    
    //Print side lengths
    printf("Length of AB is %f\n", AB);
    printf("Length of BC is %f\n", BC);
    printf("Length of CA is %f\n", CA);
    
    //Calculate circumference and area
    Circ=AB+BC+CA;
    Area=sqrt(0.5*Circ*(0.5*Circ-AB)*(0.5*Circ-BC)*(0.5*Circ-CA));
    
    //Print circumference and area
    printf("Circumference of BC is %f\n", Circ);
    printf("Area is %f\n", Area);
    
    return 0;
}


