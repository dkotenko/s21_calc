#include "smartcalc.h"
#include <stdio.h>
#include <stdlib.h>

void draw_plot(int steps, double min, double max, t_dlist *tokens)
{	
  FILE *fp=NULL;
  fp=fopen("plot.txt","w");
  double step = (max - min) / steps;
  t_calc_output output;
  
  for(double x=min; x < max; x+=step){
    output = rpn(tokens, x);
    fprintf(fp,"%lf\t %lf\n", x, output.output);
  }
  t_dlist_free(tokens, t_dlist_node_free_simple);
  fclose(fp);
}

void show_plot(void)
{
  system("gnuplot --persist -e 'plot \"plot.txt\" w l'");
}