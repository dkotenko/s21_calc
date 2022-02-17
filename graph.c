#include<stdio.h>
#include<math.h>
int main(){
  FILE *fp=NULL;
  fp=fopen("circle.txt","w");
  //printf("Enter the radius of the circle to be plotted: ");
  //scanf("%lf",&r);

  int steps = 100000;
  int min = -199999;
  int max = 300000;
  int step = (max - min) / steps;
  int i = min;
  for(int i=0; i < max;i+=step){
    float f = (float)i;
    fprintf(fp,"%lf\t %lf\n",f < 0 ? 0 : 1,f);
  }
  return (0);
}