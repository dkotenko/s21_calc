#include<stdlib.h>
#include<math.h>
int main(){
	system("gnuplot --persist -e 'plot \"circle.txt\" w l'");
	return 0;
}