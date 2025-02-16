//NA 2017/2018: Zadaća 4, Zadatak 2
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <stdexcept>

#define PI 4*std::atan(1)

template <typename FunType>
 std::pair<double, bool> RombergIntegration(FunType f, double a, double b, double eps = 1e-8, int nmax = 1000000, int nmin = 50){
    if( eps<0 || nmin<0 || nmax<0 || nmax<nmin) throw std::domain_error("Bad parameter");
    if(a>b){ a=a*(-1); b=b*(-1);}
    int N=2; 
    double h=(b-a)/N ; 
    double s= (f(a)+f(b))/2; 
    std::vector<double>I; 
    double Istaro=s; 
    int i=0; 
    while(N<nmax){
        for(int j=1; j<=N/2;j++){
            s=s+ f(a+(2*j-1)*h); 
        }
        I.push_back(h*s);
        double p=4; 
        for(int k=i-1; k>=0; k--){
            I.at(k)=(p*I.at(k+1)-I.at(k))/(p-1);
            p=p*4; 
        }
        if(N>nmin && std::fabs(I.at(0) - Istaro )<=eps){
             return std::make_pair(I.at(0),true);
        }
        Istaro=I.at(0); 
        h=h/2; 
        N=N*2; 
        i++; 
    }
    return std::make_pair(I.at(0), false);
 }

void zamjeni(double &a, double &b){
    double tmp;
    tmp=a; 
    a=b; 
    b=tmp;
}
template <typename FunType>
 std::pair<double, bool> TanhSinhIntegration(FunType f, double a, double b, double eps = 1e-8, int nmax = 1000000, int nmin = 20, double range = 3.5){
    if(eps<0 || nmin<0 || nmax<0 || nmax<nmin || range<0){
        throw std::domain_error("Bad parameter");
    }
    if(a>b) {
    double tmp=a; 
    a=b; 
    b=tmp;
    }
    double N=2; 
    double h=2*range/N; 
    double rvs =((std::cosh(-range)/(std::cosh(std::sinh(-range)*PI/2)*std::cosh(std::sinh(-range)*PI/2)))*f((a+b)/2+((b-a)/2)*std::tanh(PI/2*std::sinh(-range))));
    double f2=(std::cosh(range)/(std::cosh(std::sinh(range)*PI/2)*std::cosh(std::sinh(range)*PI/2)))*f((a+b)/2+((b-a)/2))*std::tanh(PI/2*std::sinh(range));   
    if (!std::isfinite(rvs)) rvs=0; 
    if(!std::isfinite(f2)) f2=0; 
    double s= (rvs+f2)/2; 
    double Istaro=s; 
    double I; 

    while(N<nmax){

        for(int i=1; i<=N/2; i++){
            double sr=(-range)+ (2*i-1)*h; 
            double p= std::cosh(sr)/(std::cosh(std::sinh(sr)*PI/2)*std::cosh(std::sinh(sr)*PI/2));
            double f3 = f((a+b)/2 +((b-a)/2)*std::tanh(PI/2*std::sinh(sr)) );
            //f((a+b)/2)+ ( (b-a)/2)*std::tanh(PI/2*std::sinh(sr));
            if(!std::isfinite(f3)) f3=0; 
            double f4= p*f3; 
            s=s+(PI/4*(b-a)*f4);
        }
        I=h*s; 
        if(N>nmin && std::fabs(I-Istaro)<=eps) return std::make_pair(I, true); 
        Istaro=I; 
        N=N*2; 
        h=h/2; 
    }
    return std::make_pair(I, false);
 }

template <typename FunType>
double AdaptiveAux(FunType f, double a, double b, double eps, double f1, double f2,double f3,double R, bool &nR ){
    double c= (a+b)/2; 
    double I1 = (b-a)*(f1+4*f3+f2)/6; 
    double h4= f((a+c)/2);
    if(!std::isfinite(h4)) h4=0; 
    double f4=h4; 
    double h5=f((c+b)/2); 
    if(!std::isfinite(h5)) h5=0;
    double f5=h5; 
    double I2 = (b-a)*(f1+4*f4+2*f3+4*f5+f2)/12; 
    if(std::fabs(I1-I2)<=eps) return I2; 
    if(R<=0){
        nR=false; return I2; 
    }
    return AdaptiveAux(f,a,c,eps,f1,f3,f4,R-1,nR)+AdaptiveAux(f,c,b,eps,f3,f2,f5,R-1,nR);
    }

template <typename FunType>
 std::pair<double, bool> AdaptiveIntegration(FunType f, double a, double b,double eps = 1e-10, int maxdepth = 30, int nmin = 1){
    if(eps<0 || maxdepth<0 || nmin<0) throw std::domain_error("Bad parameter"); 
    double s=0; 
    double h = (b-a)/nmin; 
    bool nR=true;
    for(int i=1; i<=nmin; i++){
        double hl=f(a); 
        if(!std::isfinite(hl)) hl=0; 
        double hl2=f(a+b); 
        if(!std::isfinite(hl)) hl=0; 
        double mh=hl; 
        hl=f(a+h/2); 
        if(!std::isfinite(hl)) hl=0; 
        double b=hl;
        s+=AdaptiveAux(f,a,a+h,eps, hl2,mh, b,maxdepth, nR);
        a+=h;  
    } 
    if(a>b) return std::make_pair(-s, nR); 
    return std::make_pair(s, nR);
 }

void Test(){
    auto sinus= [](double x){return std::sin(x);};
    auto kr = [](double x){return 1/std::sqrt(x);};
    auto polinom = [](double x){return x*x + 3*x + 435;};

    std::cout<<"TANHSINHHHH "<<std::endl; 
    std::cout<<TanhSinhIntegration(sinus,0,PI).first<<std::endl; 
    std::cout<<TanhSinhIntegration(kr,0,1).first<<std::endl;
    std::cout<<TanhSinhIntegration(polinom,10,10e4).first<<std::endl;

    std::cout<<"ADAPTIVEE "<<std::endl; 
    std::cout<<AdaptiveIntegration(sinus,0,PI).first<<std::endl; 
    std::cout<<AdaptiveIntegration(kr,0,1).first<<std::endl;
    std::cout<<AdaptiveIntegration(polinom,10,10e4).first<<std::endl;
    
    std::cout<<"ADAPTIVEE "<<std::endl; 
    std::cout<<AdaptiveIntegration(sinus,0,PI).first<<std::endl; 
    std::cout<<AdaptiveIntegration(kr,0,1).first<<std::endl;
    std::cout<<AdaptiveIntegration(polinom,10,10e4).first<<std::endl;

    std::cout<<"ADAPTIVEE "<<std::endl; 
    std::cout<<RombergIntegration(sinus,0,PI).first<<std::endl; 
    std::cout<<RombergIntegration(kr,0,1).first<<std::endl;
    std::cout<<RombergIntegration(polinom,10,10e4).first<<std::endl;
}


int main ()
{
    //AT24 - TanhSinh integration - 1
auto rez = TanhSinhIntegration([](double x) { return std::log(std::abs(x-1.372)); }, 0, 2, 1e-5, 2000000);
  std::cout << rez.first << " " << rez.second;;

    const double pi= 4*std::atan(1);
    auto sinus = [](double x){return std::sin(x);};
    std::cout<<"ROMBERG POKUSAJ"<<std::endl; 
    std::cout<<RombergIntegration(sinus,0, pi).first<<std::endl; 

//AT2 - Romberg integration - 2
auto inv1 = [](double x) { return 1 / x; };
auto riga = RombergIntegration(inv1, 1, 2);
std::cout << riga.first << " " << riga.second;

//AT13 - Adaptive integration - 4
auto sinc = [](double x) { return x == 0 ? 1 : std::sin(x) / x; };
auto aig =  AdaptiveIntegration(sinc, 0, 1e8, 1e-10, 23);
std::cout << aig.first << " " << aig.second;

    Test();

	return 0;
}