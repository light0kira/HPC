#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

/* Main Program */

int main()
{
float          *Array, *Check, serial_sum, sum, partialsum;
int             array_size, i;

printf("Enter the size of the array\n");
scanf("%d", &array_size);

if (array_size <= 0) {
printf("Array Size Should Be Of Positive Value ");
exit(1);
}
/* Dynamic Memory Allocation */

Array = (float *)malloc(sizeof(float) * array_size);
Check = (float*)malloc(sizeof(float) * array_size);

/* Array Elements Initialization */

for (i = 0; i < array_size; i++) {
Array[i] = i * 5;
Check[i] = Array[i];
}

printf("The Array Elements Are \n");

for (i = 0; i < array_size; i++)
printf("Array[%d]=%f\n", i, Array[i]);

sum = 0.0;
partialsum = 0.0;

/* OpenMP Parallel For Directive And Critical Section */

#pragma omp parallel for shared(sum)
for (i = 0; i < array_size; i++) {
#pragma omp critical
sum = sum + Array[i];

}

serial_sum = 0.0;

/* Serail Calculation */
for (i = 0; i < array_size; i++)
serial_sum = serial_sum + Check[i];


if (serial_sum == sum)
printf("\nThe Serial And Parallel Sums Are Equal\n");
else {
printf("\nThe Serial And Parallel Sums Are UnEqual\n");
exit(1);
}

/* Freeing Memory */
free(Check);
free(Array);

printf("\nThe SumOfElements Of The Array Using OpenMP Directives Is %f\n", sum);
printf("\nThe SumOfElements Of The Array By Serial Calculation Is %f\n", serial_sum);
}