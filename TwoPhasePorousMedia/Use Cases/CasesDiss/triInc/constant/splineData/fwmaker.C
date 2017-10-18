#include <iostream>

using namespace std;

int main()
{
  int np(10);
  double Sw[np], fw[np], kr_w[np], kr_o[np], dSw, Swr(0), Sor(0);
  
  double mu_o = 1;
  double mu_w = 0.5;
  
  dSw = 1.0/(np-1);

  for(int i(0);i<np;i++)
  {
    Sw[i] = i*dSw;
    
    kr_w[i] = ((Sw[i]-Swr)/(1-Swr-Sor))*((Sw[i]-Swr)/(1-Swr-Sor));
    kr_o[i] = ((1-Sw[i]-Swr)/(1-Swr-Sor))*((1-Sw[i]-Swr)/(1-Swr-Sor));
    fw[i] = (kr_w[i]/mu_w)/(kr_w[i]/mu_w + kr_o[i]/mu_o);
  }
  
  for(int i(0);i<np;i++)
  cout<<Sw[i]<<endl;
  
  for(int i(0);i<np;i++)
  cout<<fw[i]<<endl;
  
  return 0;
}