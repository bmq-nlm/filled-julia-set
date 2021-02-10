#include <bits/stdc++.h>
#include <complex>
#include <cmath>
#include <math.h> 
using namespace std;

const complex<double> I(0.0, 1.0);
const complex<double> C(0.295916253 -0.48239385*I); 
const int MAX_ITER(1000);
const int SIZE(1000);
const double ZOOM(1000);
const double STEP(0.004);
const complex<double> RE_START(0.295916253);
const complex<double> IM_START(-0.48239385);  
const string FILENAME("BITMAP.txt");

double julia(complex<double> c, complex<double> z0){
  complex<double> z = z0;
  int n = 0;
  double smoothNumIt = exp(-abs(z));
  double bound = max(2.0, abs(C));
  while(abs(z) <= bound and n < MAX_ITER){
    z = (z*z) + c;
    smoothNumIt += exp(-abs(z));
    n += 1;
  }
    if (n == MAX_ITER){
      return MAX_ITER;
  }

    return smoothNumIt;

}

double to_hue(double point_escape, double max_escape){
  return point_escape/MAX_ITER;
}

complex<double> plane(int x, int y){
  return (RE_START + (1/ZOOM)*STEP*(x-SIZE/2)) + (IM_START + (1/ZOOM)*STEP*(SIZE/2-y))*I;
}

int main(){
double bitmap[SIZE][SIZE] ={};
double maxEscape = 0;

for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      bitmap[i][j] = julia(C, plane(i,j));
      if (bitmap[i][j] != MAX_ITER){
          maxEscape = max(maxEscape, bitmap[i][j]);
      }
    }
}

   for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      if (bitmap[i][j]  == MAX_ITER){
        bitmap[i][j] = to_hue(bitmap[i][j] , MAX_ITER);
      }
      else{
        bitmap[i][j] = to_hue(bitmap[i][j] , maxEscape);
      }

    }
  }

  ofstream bitMat;
  bitMat.open (FILENAME);
  for (int j = 0; j < SIZE; j++){
    for (int i = 0; i < SIZE; i++){
      bitMat << bitmap[i][j] << " ";
    }
    bitMat << '\n';
  }
  bitMat.close();
}