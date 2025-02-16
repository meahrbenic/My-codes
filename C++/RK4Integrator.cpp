//NA 2017/2018: Zadaća 5, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <vector>
#include <complex>
#include <limits>

 template<typename FunTip>
 double RK4Step(FunTip f, double x, double y, double h){
  double K1(f(x,y));
  double K2(f(x+h/2, y+h*K1/2));
  double K3(f(x+h/2, y+h*K2/2));
  double K4(f(x+h, y+h*K3));
  return y+h*(K1+2*K2+2*K3+K4)/6;
 }

 template <typename FunTip>
 std::vector<std::pair<double, double>> RK4Integrator(FunTip f, double x0, double y0, double xmax, double h, double eps = 1e-8, bool adaptive = false){
  std::vector<std::pair<double, double>> vektor;
  if(x0==xmax){
   vektor.push_back(std::pair<double, double> (x0, y0));
   return vektor;
  }
  double x(x0), y(y0);
  if(adaptive){
   if((xmax<x0 && h>0) || (xmax>x0 && h<0)){
    vektor.push_back(std::pair<double, double> (x0, y0));
    return vektor;
   }
   if(h>0){
    while(x<xmax){
     double u(RK4Step(f,x,y,h/2));
     double v(RK4Step(f,x+h/2,u,h/2));
     double w(RK4Step(f,x,y,h));
     double s(fabs(w-v)/h);
     if(s<=eps){
      double s1(x);
      x+=h;
      if(x>xmax){
       h=xmax-s1;
       x=s1;
       continue;
      }
      y=v;
      vektor.push_back(std::pair<double, double> (x, y));
     }
     double min;
     if(0.9*std::pow((eps/s),1./4)<5) min=0.9*std::pow((eps/s),1./4);
     else min=5;
     h*=min;
    }
   }
   else if(h<0){
    while(x>xmax){
     double u(RK4Step(f,x,y,h/2));
     double v(RK4Step(f,x+h/2,u,h/2));
     double w(RK4Step(f,x,y,h));
     double s(fabs(w-v)/h);
     if(fabs(s)<=eps){
      double s1(x);
      x+=h;
      if(x<xmax){
       h=xmax-s1;
       x=s1;
       continue;
      }
      y=v;
      vektor.push_back(std::pair<double, double> (x, y));
     }
     double min;
     if(0.9*std::pow((eps/s),1./4)<5) min=0.9*std::pow((eps/s),1./4);
     else min=5;
     h*=min;
    }
   }
  }
  else{
   int i(0);
   if(h>0){
    while(x<xmax){
     if(i==0) vektor.push_back(std::pair<double, double> (x, y));
     else{
      y=RK4Step(f,x,y,h);
      x+=h;
      vektor.push_back(std::pair<double, double> (x, y));
     }
     i++;
    }
   }
   else if(h<0){
    while(x>xmax){
     if(i==0) vektor.push_back(std::pair<double, double> (x, y));
     else{
      y=RK4Step(f,x,y,h);
      x+=h;
      vektor.push_back(std::pair<double, double> (x, y));
     }
     i++;
    }
   }
  }
  return vektor;
 }

int main ()
{
    // Test 1: Runge-Kutta y'=2x+y+1, od 0 do 1.5, h=0.1, neadaptivan
auto res = RK4Integrator([](double x, double y) { return 2 * x + y + 1; },
0, 1, 1.5, 0.1);
auto exact = [](double x) { return -3 - 2 * x + 4 * std::exp(x); };
for(int i = 0; i < res.size(); i++) {
    double x = res[i].first;
    std::cout << x << " " << res[i].second << " " << exact(x) << std::endl;
}
	return 0;
}