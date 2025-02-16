//NA 2017/2018: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <vector>
#include <complex>
#include <limits>


template <typename FunType>
 bool BracketRoot(FunType f, double x0, double &a, double &b, double hinit = 1e-5, double hmax = 1e10, double lambda = 1.4){
    if (hinit<=0 || hmax <=0 || lambda<=0) throw std::domain_error("Invalid parameters"); 
    double a0=x0; 
    double b0; 
    double f1(f(a0));
    double h= hinit; 
    while(fabs(h)<hmax){
        b0=a0+h; 
        double f2= f(b0); 
        if(f1*f2<=0){
            if(a0>b0) std::swap(a0,b0);
            a=a0; 
            b=b0; 
            return true;
        }
        h=lambda*h; 
        a0=b0; 
        f1=f2;
    }
    h=hinit; 
    a0=x0; 
    f1=f(x0); 
    while(fabs(h)<hmax){
        b0=a0-h; 
        double f2=f(b0); 
        if(f1*f2<=0){
            if(a0>b0) std::swap(a0,b0);
            a=a0;
            b=b0; 
            return true;
        }
        h=lambda*h; 
        b0=a0; 
        f2=f1;
    }
    return false;

}

enum RegulaFalsiMode {Unmodified, Illinois, Slavic, IllinoisSlavic};

template <typename FunType>
 double RegulaFalsiSolve(FunType f, double a, double b, RegulaFalsiMode mode = Slavic, double eps = 1e-10, int maxiter = 100){
     if(eps<=0 || maxiter<=0 ) throw std::domain_error("Invalid parameters"); 
bool s=false;
  bool il=false;
  double f1, f2;
  if(mode==RegulaFalsiMode::Illinois || mode==RegulaFalsiMode::IllinoisSlavic) il=true;
  if(mode==RegulaFalsiMode::Slavic || mode==RegulaFalsiMode::IllinoisSlavic){
   s=true;
   f1=f(a)/(1+fabs(f(a)));
   f2=f(b)/(1+fabs(f(b)));;
  }
  else{
   f1=f(a);
   f2=f(b);
  }
  if(f1*f2>0) throw std::range_error("Root must be bracketed");
  double c(a);
  double cold(b);
  int i(0);
  while(fabs(c-cold)>eps && i<maxiter){
   i++;
   cold=c;
   c=(a*f2-b*f1)/(f2-f1);
   double f3;
   if(s) f3=f(c)/(1+fabs(f(c)));
   else f3=f(c);
   if(f3==0) return c;
   if(f1*f3<0){
    f2=f1;
    b=a;
   }
   else if(il) f2/=2;
   a=c;
   f1=f3;
  }
  if(fabs(c-cold)<eps) return c;
  throw std::logic_error("Given accuracy has not achieved");

 }

template <typename FunType>
 double RiddersSolve(FunType f, double a, double b, double eps = 1e-10, int maxiter = 100){
     if(eps<=0 || maxiter<=0 ) throw std::domain_error("Invalid parameters"); 
     if(f(a)*f(b)>0) throw std::range_error("Root must be bracketed"); 
     int i=0; 
     double f1= f(a); 
     double f2= f(b); 
     while(std::fabs(b-a)>eps && i<maxiter){
         i++; 
         double c= (a+b)/2; 
         double f3=f(c); 
         if(f3==0) return c; 
         double d; 
         if(f1-f2<0) d=c-f3*(c-a)/std::sqrt(f3*f3-f1*f2);
         else if(f1-f2==0) d=c;
         else d=c+f3*(c-a)/std::sqrt(f3*f3-f1*f2); 
         double f4= f(d); 
         if(f4==0) return d; 
         if(f3*f4<=0) {
             a=c; 
             b=d; 
             f1=f3; 
             f2=f4; 

         }
         else if(f1*f4<=0){
             b=d; 
             f2=f4;
         }
         else{
             a=d; 
             f1=f4; 
         }
     } 
    if(std::fabs(b-a)<eps) return (a+b)/2; 
    throw std::logic_error("Given accuracy has not achieved"); 
 }

template <typename FunType1, typename FunType2>
 double NewtonRaphsonSolve(FunType1 f, FunType2 fprim, double x0, double eps = 1e-10, double damping = 0, int maxiter = 100){
    if(eps<=0 || maxiter<=0 ) throw std::domain_error("Invalid parameters"); 
    int i=0; 
    double dx=std::numeric_limits<double>::infinity(); 
    while(std::fabs(dx)>eps && i<maxiter){
        i++; 
        double v= f(x0); 
        if(v==0) return x0; 
        if(fprim(x0)==0) throw std::logic_error("Convergence has not achived"); 
        dx=v/fprim(x0); 
        x0=x0-dx; 
    }
    if(std::fabs(dx)<eps) return x0; 
    throw std::logic_error("Convergence has not achieved"); 
 }
/*

std::complex<double> operator* (std::complex<double>a, std::complex<double>b){
    
return std::complex<double> (a.real()*b.real()-a.imag()*b.imag(), a.real()*b.imag()+a.imag()*b.real());
}

std::pair<std::complex<double>, bool> Laguerre(std::vector<std::complex<double>> p, int n, std::complex<double> x, double eps, int kmax){
 
  std::complex<double> deltax=(std::numeric_limits<double>::infinity(), 0);
  int k(1);
  while(abs(deltax)>eps && k<kmax){
   std::complex<double> f=p[n];
   std::complex<double> d(0,0);
   std::complex<double> s(0);
   for(int i=n-1;i>=0;i--){
    s=s*x+2*d;
    d=d*x+f;
    f=f*x+p[i];
   }
   if(f.real()==0 && f.imag()==0) return std::pair<std::complex<double>, bool> (x, true);
   std::complex<double> r(sqrt((n-1)*((n-1)*d*d-n*f*s)));
   if(abs(d+r)>abs(d-r)) deltax=n*f/(d+r);
   else deltax=n*f/(d-r);
   x=x-deltax;
   k++;
  }
  if(abs(deltax)<=eps) return std::pair<std::complex<double>, bool> (x, true);
  return std::pair<std::complex<double>, bool> (x, false);
}

std::vector<std::complex<double>>PolyRoots(std::vector<std::complex<double>> coefficients, double eps = 1e-10,int maxiters = 100, int maxtrials = 10){
    if(eps<=0 || maxiters<=0 || maxtrials<=0 ) throw std::domain_error("Invalid parameters"); 
    std::vector<std::complex<double>> x1(coefficients.size()); 
    std::complex<double> x; 
    for(int i=coefficients.size()-1; i>0; i--){
        int t=1; 
        bool c=false; 
        while(!c && (t<maxtrials)){
        x=std::complex<double> ((double) rand()/(RAND_MAX)*20-10, (double) rand()/(RAND_MAX)*20-10);            
        std::pair<std::complex<double>, double> par(Laguerre(coefficients, i, x, eps, maxiters)); 
            x=par.first; 
            c=par.second; 
            t++;
        }
    if(!c) throw std::domain_error("Convergence has not achived"); 
    if(std::fabs(imag(x))<eps) x=std::complex<double> (real(x), 0);
    x1[i]=x; 
    std::complex<double> v=coefficients[i]; 
    for(int j=i-1; j>=0; j--){
        std::complex<double> w= coefficients[j];
        coefficients[j]=v; 
        v=w+x*v;
    }
    }
    x1.erase(x1.begin()); 
    return x1; 
 }


std::vector< std::complex<double>> PolyRoots(std::vector<double> coefficients, double eps = 1e-10,int maxiters = 100, int maxtrials = 10){
    
 if(eps<=0 || maxiters<=0 || maxtrials<=0) throw std::domain_error("Invalid parameters");
 int i(coefficients.size()-1);
 std::vector<std::complex<double>> x1(coefficients.size());
 std::complex<double> x;
 std::vector<std::complex<double>> coef(coefficients.size());
 for(int i=0;i<coef.size();i++){
  coef[i].real(coefficients[i]);
  coef[i].imag(0);
 }
 while(i>=1){
  int t(1);
  bool c(false);
  while(!c && (t<maxtrials)){
   x=std::complex<double> ((double) rand()/(RAND_MAX)*20-10, (double) rand()/(RAND_MAX)*20-10);
   std::pair<std::complex<double>, double> par(Laguerre(coef, i, x, eps, maxiters));
   x=par.first;
   c=par.second;
   t++;
  }
  if(!c) throw std::domain_error("Convergence has not achieved");
  if(std::fabs(imag(x))<=eps){
   x=std::complex<double> (real(x), 0);
   x1[i]=x;
   double v(coefficients[i]);
   for(int j=i-1;j>=0;j--){
    double w(coefficients[j]);
    coefficients[j]=v;
    v=w+x.real()*v;
   }
   i--;
  }
  else{
   x1[i]=x;
   x1[i-1]=conj(x);
   double alfa(2*real(x));
   double beta(abs(x)*abs(x));
   double u(coefficients[i]);
   double v(coefficients[i-1]+alfa*u);
   for(int j=i-2;j>=0;j--){
    double w(coefficients[j]);
    coefficients[j]=u;
    u=v;
    v=w+alfa*v-beta*coefficients[j];
   }
   i=i-2;
  }
 }
 x1.erase(x1.begin());
 return x1;
}
 */

 
 std::complex<double> operator*(std::complex<double> a, std::complex<double> b){
  return std::complex<double> (a.real()*b.real()-a.imag()*b.imag(), a.real()*b.imag()+a.imag()*b.real());
 }
 
 std::pair<std::complex<double>, bool> Laguerre(std::vector<std::complex<double>> p, int n, std::complex<double> x, double eps, int kmax){
  std::complex<double> deltax=(std::numeric_limits<double>::infinity(), 0);
  int k(1);
  while(abs(deltax)>eps && k<kmax){
   std::complex<double> f=p[n];
   std::complex<double> d(0,0);
   std::complex<double> s(0);
   for(int i=n-1;i>=0;i--){
    s=s*x+2*d;
    d=d*x+f;
    f=f*x+p[i];
   }
   if(f.real()==0 && f.imag()==0) return std::pair<std::complex<double>, bool> (x, true);
   std::complex<double> r(sqrt((n-1)*((n-1)*d*d-n*f*s)));
   if(abs(d+r)>abs(d-r)) deltax=n*f/(d+r);
   else deltax=n*f/(d-r);
   x=x-deltax;
   k++;
  }
  if(abs(deltax)<=eps) return std::pair<std::complex<double>, bool> (x, true);
  return std::pair<std::complex<double>, bool> (x, false);
 }
 
std::vector<std::complex<double>>PolyRoots(std::vector<std::complex<double>> coefficients, double eps = 1e-10, int maxiters = 100, int maxtrials = 10){
 if(eps<=0 || maxiters<=0 || maxtrials<=0) throw std::domain_error("Invalid parameters");
 std::vector<std::complex<double>> x1(coefficients.size());
 std::complex<double> x;
 for(int i=coefficients.size()-1;i>0;i--){
  int t(1);
  bool c(false);
  while(!c && (t<maxtrials)){
   x=std::complex<double> ((double) rand()/(RAND_MAX)*20-10, (double) rand()/(RAND_MAX)*20-10);
   std::pair<std::complex<double>, double> par(Laguerre(coefficients,i,x,eps,maxiters));
   x=par.first;
   c=par.second;
   t++;
  }
  if(!c) throw std::domain_error("Convergence has not achieved");
  if(fabs(imag(x))<=eps) x=std::complex<double> (real(x), 0);
  x1[i]=x;
 std::complex<double> v(coefficients[i]);
  for(int j=i-1;j>=0;j--){
   std::complex<double> w(coefficients[j]);
   coefficients[j]=v;
   v=w+x*v;
   }
  }
 x1.erase(x1.begin());
 return x1;
}


std::vector< std::complex<double>> PolyRoots(std::vector<double> coefficients, double eps = 1e-10, int maxiters = 100, int maxtrials = 10){
 if(eps<=0 || maxiters<=0 || maxtrials<=0) throw std::domain_error("Invalid parameters");
 int i(coefficients.size()-1);
 std::vector<std::complex<double>> x1(coefficients.size());
 std::complex<double> x;
 std::vector<std::complex<double>> coef(coefficients.size());
 for(int i=0;i<coef.size();i++){
  coef[i].real(coefficients[i]);
  coef[i].imag(0);
 }
 while(i>=1){
  int t(1);
  bool c(false);
  while(!c && (t<maxtrials)){
   x=std::complex<double> ((double) rand()/(RAND_MAX)*20-10, (double) rand()/(RAND_MAX)*20-10);
   std::pair<std::complex<double>, double> par(Laguerre(coef, i, x, eps, maxiters));
   x=par.first;
   c=par.second;
   t++;
  }
  if(!c) throw std::domain_error("Convergence has not achieved");
  if(fabs(imag(x))<=eps){
   x=std::complex<double> (real(x), 0);
   x1[i]=x;
   double v(coefficients[i]);
   for(int j=i-1;j>=0;j--){
    double w(coefficients[j]);
    coefficients[j]=v;
    v=w+x.real()*v;
   }
   i--;
  }
  else{
   x1[i]=x;
   x1[i-1]=conj(x);
   double alfa(2*real(x));
   double beta(abs(x)*abs(x));
   double u(coefficients[i]);
   double v(coefficients[i-1]+alfa*u);
   for(int j=i-2;j>=0;j--){
    double w(coefficients[j]);
    coefficients[j]=u;
    u=v;
    v=w+alfa*v-beta*coefficients[j];
   }
   i=i-2;
  }
 }
 x1.erase(x1.begin());
 return x1;
}

int main ()
{ // Test 15: PolyRoots, verzija sa kompleksnim vektorom, nule -3, -2 i -1
std::vector<std::complex<double>> coeff{6, 11, 6, 1};
std::vector<std::complex<double>> sols{-3, -2, -1};
std::vector<std::complex<double>> z = PolyRoots(coeff);
for(int i = 0; i < z.size(); i++)
    std::cout << (std::abs(z[i]-sols[i]) < 1e-8) << std::endl;

	return 0;
}