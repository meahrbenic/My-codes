//NA 2017/2018: Zadaća 5, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <vector>
#include <complex>
#include <limits>

template <typename FunTip>
 double FindMinimum(FunTip f, double x0, double eps = 1e-8, double hinit = 1e-5, double hmax = 1e10, double lambda = 1.4){
  if(eps<=0 || hinit<=0 || hmax<=0 || lambda<=0) throw std::domain_error("Invalid parameters");
  /*double h(hinit);
  if(f(x0)<f(x0)) h=-h;
  double f1, f2, f0;
  double a, b, c;
  while(fabs(h)<hmax){
   f0=f(x0);
   f1=f(x0-h);
   f2=f(x0+h);
   if(f1>f0 && f2>f0){
    a=x0-h;
    c=x0;
    b=x0+h;
    break;
   }
   h=lambda*h;
   a=b;
   f1=f2;
  }
  if(fabs(h)>=hmax) throw std::logic_error("Minimum has not found");
  double k(1+sqrt(5)/2);
  double d;
  if(fabs(c-a)<fabs(b-c)){
   d=b-(b-c)/k;
  }
  else{
   d=c;
   c=c+(c-a)/k;
  }
  double u(f(c)), v(f(d));
  while(fabs(b-a)<eps){
   if(u<v){
    b=d;
    d=c;
    c=a+(c-a)/k;
    v=u;
    u=f(c);
   }
   else{
    a=c;
    c=d;
    d=b-(b-d)/k;
    u=v;
    v=f(d);
   }
  }
  if(fabs(b-a)<eps) return (a+b)/2;
  throw std::logic_error("Minimum has not found");*/

    double a, b,c; 
    a=x0-hinit; 
    b=x0-hinit;
    c=x0; 
    bool found = false; 
    while(std::abs(hinit)<hmax){
        if(f(c+hinit) < f(c)){
            b=c+hinit; 
            a=c-hinit; 
        }
        else if(f(c-hinit)<c){
            b=c-hinit;
            a=b-hinit; 
        }
        else{
            a=c-hinit;
            b=c+hinit;
            found = true; 
            break;
        }
        c=b; 
        hinit=hinit*lambda;
    }

    if(!found) throw std::logic_error("Minimum has not found"); 
    double zlatni = (1+std::sqrt(5))/2; 
    double d; 
    if(std::abs(c-a)<std::abs(b-c)){
        d=b-(b-c)/zlatni; 
    }
    else{
        d=c; 
        c=a+(c-a)/zlatni;
    }
    double U=f(c); 
    double V=f(d); 
    while(std::abs(b-a)>eps){
        if(U<V){
            b=d; 
            d=c; 
            c=a+ (c-a)/zlatni; 
            V=U; 
            U=f(c);
        }
        else{
            a=c; 
            c=d; 
            d=b-(b-d)/zlatni; 
            U=V; 
            V=f(d);
        }
    }
    return (a+b)/2; 
 }

int main ()
{
    // Test 1: Test minimuma, pocetna tacka lijevo od minimuma
std::cout << FindMinimum([](double x) { return 1 + (x - 5) * (x - 5); }, 1);
	return 0;
}