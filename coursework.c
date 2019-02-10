#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// My name is Jorge Oliver
float average(float *temp) {
  float sum = 0;
  for (int i=0; i<(sizeof(temp)/sizeof(temp[0]));i++) {
    sum = sum + temp[i];
  }
  return (sum/(sizeof(temp)/sizeof(temp[0])));
}
int main(int n , char *args[n]) {
  float U;float dx;float num;int N;char name;
  FILE *in = fopen (args[0], "r");
  FILE *ans = fopen("answer.txt","w");
  if (in == NULL) printf("error\n");
  //if (in != NULL){
    char *s = "";
    fgets(s,10,in);
    while (! feof(in)){
        sscanf(s, "%c %f", name, &num);
        if (name == 'U') {
          U = num;
        }
        else {
          dx = num;
        }
        fgets(s, 10, in);
    }
    N= (int)(1 + 1/dx) ;
    float location[N];
    for (int i=0; i<N; i++) {
      location[i] = i * dx ;
    }
    float *temperature;
    temperature =(float *) calloc(N,sizeof(float));
    temperature[0] = 0; temperature[N-1] = 0;
    for (int i=1; i<(N-1); i++) {
        temperature[i] = U * (1 - location[i]);
    }
    double dt=0.5 * pow ( dx, 2);
    double t=0;
    while (average(temperature) != 0.1){
      t = t + dt;
      temperature[0]=0;
      temperature[N-1]=0;
      for (int i=1; i<N-1; i++) {
        temperature[i]= temperature[i] + 0.5 * (temperature[i+1] - 2*temperature[i] + temperature[i-1]);
      }
    }
    fprintf( ans, "%f\n", t);
    fclose(ans);
    fclose(in);
    free(temperature);
  //}
  // else {
  // fprintf(ans,"-1");
  // fclose(ans);
  // }
}
