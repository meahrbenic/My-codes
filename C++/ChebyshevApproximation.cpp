//NA 2017/2018: Zadaća 4, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#define pi 4*std::atan(1)

class ChebyshevApproximation {
    int m,n; 
    double xmin,xmax;
    std::vector<double> c;
    public:
    template <typename FunType>
    ChebyshevApproximation(FunType f, double xmin, double xmax, int n);
    void set_m(int m){if(m<=1 || n<m) throw std::domain_error("Bad order"); this->m=m+1;};
    void trunc(double eps);
    double operator()(double x) const;
    double derivative(double x) const;
    ChebyshevApproximation derivative() const;
    ChebyshevApproximation antiderivative() const;
    double integrate(double a, double b) const;
    double integrate() const;
};

template <typename FunType>
ChebyshevApproximation::ChebyshevApproximation(FunType f, double xmin, double xmax, int n): xmax(xmax),xmin(xmin),m(n),n(n){

    if(xmax<=xmin || n<1) throw std::domain_error("Bad parameters");
    std::vector<double> w(n+2);
    std::vector<double> v;
   // std::cout<<xmax<<" "<<xmin<<" "<<m<<" "<<n<<std::endl;
    for(int i=0; i<n+2;i++){
        w.at(i)=std::cos(pi*i/(2*n+2));
    }

    for(int i=0; i<n/2+1;i++){
        v.push_back( f( ( xmin+xmax + (xmax-xmin) * w.at(2*i+1) )/2 ) );
    }

    for(int i=n/2+1;i<n+1;i++){
         v.push_back( f( ( xmin+xmax - (xmax-xmin) * w.at(2*n+1-2*i) )/2 ) );
    }
    double s,p;
    for(int k=0; k<n+1; k++){
        s=0;
        for(int i=0; i<n+1;i++){
            p= (k*(2*i+1)) % (4*n+4);
            if(p >= 2*n+2) p= 4*n + 4 - p; 
            if(p>=n+1) s = s - v.at(i)*w.at(2*n+2-p);
            else s=s+ v.at(i)*w.at(p);
        }
        c.push_back( 2*s/(n+1));
    }
    //std::cout<<"okic";
}

 double ChebyshevApproximation::operator()(double x) const{
    if(x<xmin || x>xmax) throw std::domain_error("Bad argument");
    double t=(2*x - xmin - xmax)/(xmax-xmin);
    double p=1,q=t,r;
    double s=c.at(0)/2 + c.at(1)*t;

    for(int k=2; k<m; k++){
        r=2*t*q - p;
        s=s+ c.at(k)*r; 
        p=q;
        q=r;
    }
    return s;
 }

void ChebyshevApproximation::trunc(double eps){
    if(eps<0) throw std::domain_error("Bad tolerance");
    for(int i=m; i>-1; i--){
        if(i==0) throw std::domain_error("Bad tolerance");
        if(std::fabs(c.at(i))>eps) {
           set_m(i); 
           break;
        }
    }
}

double ChebyshevApproximation::derivative(double x) const{
    if(x<xmin || x>xmax) throw std::domain_error("Bad argument");
    double t=(2*x -xmin-xmax)/(xmax-xmin); 
    double p=1;
    double q=4*t;
    double s=c.at(1)+q*c.at(2);
    double r; 
    for(int k=3; k<m; k++){
        r= k*(2*t*q/ (k-1) -p/ (k-2));
        s=s+c.at(k)*r;
        p=q; 
        q=r;
    }
    return 2*s/(xmax-xmin); 
}

ChebyshevApproximation ChebyshevApproximation::derivative() const{
    ChebyshevApproximation izvod = *this;
    double mi= 4/(xmax-xmin); 
    izvod.c.at(m-1)=mi*m*c.at(m);
    izvod.c.at(m-2)=mi*(m-1)*c.at(m-1); 
    for(int k=m-3; k>=0; k--){
        izvod.c.at(k)= izvod.c.at(k+2) + mi*(k+1)*c.at(k+1);
    }
    return izvod; 
}

ChebyshevApproximation ChebyshevApproximation::antiderivative() const{
    ChebyshevApproximation integral = *this;
    integral.m++; 
    integral.c.resize(m+2);
    double mi=(xmax-xmin)/4; 
    for(int k=1; k<m; k++){
        integral.c.at(k)=mi/k*(c.at(k-1)-c.at(k+1)); 
    }
    integral.c.at(m)=mi/m*c.at(m-1); 
    integral.c.at(m+1)=mi/(m+1)*c.at(m); 
    return integral; 
}

double ChebyshevApproximation::integrate(double a, double b) const{
    if(a<xmin || b>xmax) throw std::domain_error("Bad interval"); 
    ChebyshevApproximation nova(antiderivative()); 
    double ta=(2*a -xmin-xmax)/(xmax-xmin); 
    double pa=1;
    double qa=ta;
    double sa=ta*nova.c.at(1);

    for(int k=2; k<m+1; k++){
        double ra=2*ta*qa-pa;
        sa+=nova.c.at(k)*ra;
        pa=qa; 
        qa=ra; 
    }
    
    double tb=(2*b -xmin-xmax)/(xmax-xmin); 
    double pb=pa; 
    double qb=tb; 
    double sb=tb*nova.c.at(1);

    for(int k=2; k<m+1; k++){
        double rb=2*tb*qb-pb;
        sb+=nova.c.at(k)*rb;
        pb=qb; 
        qb=rb;
    }


    return sb-sa;
}

double ChebyshevApproximation::integrate() const{
    double mi = (xmax-xmin)/2; 
    double suma=0; 
    for(int k=1; k<=(m-1)/2; k++){
        suma=suma+ 2*c.at(2*k)/(1-4*k*k);
    }
    return mi*(c.at(0)+suma);
}

void TestRacunanje(){
    const double PI10 = 4 * std::atan(1);
    auto fn1 = [](double x){ return std::sin(x);};
    auto fn2 = [](double x){ return x*x-3*x+353;};

    ChebyshevApproximation sinuss(fn1,0,PI10,10); 
    ChebyshevApproximation polinom(fn2,10,10e4,10); 

    std::cout<< fn1(1) <<" "<<sinuss(1)<<" "<<sinuss.derivative(1)<<" "<<sinuss.derivative()(1)<<" "<<sinuss.integrate(0,pi/4)<<" "<<sinuss.integrate(); 
    std::cout<<std::endl; 
    std::cout<< fn2(1) <<" "<<polinom.derivative(100)<<" "<<polinom.derivative()(100)<<" "<<polinom.integrate(10,10e4)<<" "<<polinom.integrate(); 
}


int main ()
{
    TestRacunanje();
    
    std::cout<<"ostali "<<std::endl;
    //AT1 - ChebyshevApproximation - 1
const double PI10 = 4 * std::atan(1);
auto funsin = [](double x) { return std::sin(x); };
ChebyshevApproximation sinch(funsin, 0, PI10, 10);
std::cout << funsin(1) << " " << sinch(1);

std::cout<<std::endl;
std::cout<<std::endl;


    //AT2 - ChebyshevApproximation - 2
const double PI11 = 4 * std::atan(1);
auto funsin1 = [](double x) { return std::sin(x); };
ChebyshevApproximation sinch1(funsin1, 0, PI11, 10);
std::cout <<funsin1(1) << " " << sinch1.derivative(1) << " " << sinch1.derivative()(1)
<< " " << sinch1.derivative().derivative(1);
std::cout<<std::endl;
std::cout<<std::endl;


    //AT3 - ChebyshevApproximation - 3
const double PI12 = 4 * std::atan(1);
auto funsin2 = [](double x) { return std::sin(x); };
ChebyshevApproximation sinch2(funsin2, 0, PI12, 10);
std::cout << sinch2.integrate(0, PI12 / 2) << " " << sinch2.integrate();
std::cout<<std::endl;
std::cout<<std::endl;

    //AT4 - ChebyshevApproximation - 4
const double PI13 = 4 * std::atan(1);
auto funsin3 = [](double x) { return std::sin(x); };
ChebyshevApproximation sinch3(funsin3, 0, PI13, 10);
sinch3.trunc(0.001);
std::cout << funsin3(1) << " " << sinch3(1)<<std::endl;
std::cout <<funsin3(1) << " " << sinch3.derivative(1) << " " << sinch3.derivative()(1)
<< " " << sinch3.derivative().derivative(1)<<std::endl;
std::cout << sinch3.integrate(0, PI13 / 2) << " " << sinch3.integrate();
std::cout<<std::endl;
std::cout<<std::endl;

    //AT5 - ChebyshevApproximation - 5
const double PI14 = 4 * std::atan(1);
auto funsin4 = [](double x) { return std::sin(x); };
ChebyshevApproximation sinch4(funsin4, 0, PI14, 10);
sinch4.set_m(4);
std::cout << funsin4(1) << " " << sinch4(1)<<std::endl;
std::cout <<funsin4(1) << " " << sinch4.derivative(1) << " " << sinch4.derivative()(1)
<< " " << sinch4.derivative().derivative(1)<<std::endl;
std::cout << sinch4.integrate(0, PI14 / 2) << " " << sinch4.integrate();
std::cout<<std::endl;
std::cout<<std::endl;


 //AT6 - ChebyshevApproximation - Izuzetak 1
try
{
const double PIPI3 = 4 * std::atan(1);
auto sinf2 = [](double x) { return std::sin(x); };
ChebyshevApproximation chsin10(sinf2,PIPI3, -10, 10);
//Bad parametrers / Bad parameters
}
catch (std::domain_error e)
{
std::cout << "'" << e.what() << "'";
}
catch (...)
{
std::cout << "Pogresan tip izuzetka";
}
    //AT7 - ChebyshevApproximation - Izuzetak 2
try
{
const double PIPI4 = 4 * std::atan(1);
auto sinf3 = [](double x) { return std::sin(x); };
ChebyshevApproximation chsin11(sinf3,0, PIPI4,0);
//Bad parametrers / Bad parameters
}
catch (std::domain_error e)
{
std::cout << "'" << e.what() << "'";
}
catch (...)
{
std::cout << "Pogresan tip izuzetka";
}

    //AT8 - ChebyshevApproximation - Izuzetak 3
try
{
const double PIPI5 = 4 * std::atan(1);
auto sinf4 = [](double x) { return std::sin(x); };
ChebyshevApproximation chsin12(sinf4,0, PIPI5,10);
chsin12.set_m(1);
//Bad order
}
catch (std::domain_error e)
{
std::cout << "'" << e.what() << "'"<<std::endl;
}
catch (...)
{
std::cout << "Pogresan tip izuzetka"<<std::endl;
}
    try
{
const double PIPI6 = 4 * std::atan(1);
auto sinf5 = [](double x) { return std::sin(x); };
ChebyshevApproximation chsin13(sinf5,0, PIPI6,10);
chsin13.set_m(11);
//Bad order
}
catch (std::domain_error e)
{
std::cout << "'" << e.what() << "'";
}
catch (...)
{
std::cout << "Pogresan tip izuzetka";
}
//AT9 - ChebyshevApproximation - Izuzetak 4
try
{
const double PIPI7 = 4 * std::atan(1);
auto sinf6 = [](double x) { return std::sin(x); };
ChebyshevApproximation chsin14(sinf6,0, PIPI7,10);
std::cout<<chsin14(-2);
//Bad argument
}
catch (std::domain_error e)
{
std::cout << "'" << e.what() << "'"<<std::endl;
}
catch (...)
{
std::cout << "Pogresan tip izuzetka"<<std::endl;
}
    try
{
const double PIPI8 = 4 * std::atan(1);
auto sinf7 = [](double x) { return std::sin(x); };
ChebyshevApproximation chsin15(sinf7,0, PIPI8,10);
std::cout<<chsin15.derivative(20);
//Bad argument
}
catch (std::domain_error e)
{
std::cout << "'" << e.what() << "'";
}
catch (...)
{
std::cout << "Pogresan tip izuzetka";
}

//AT10 - ChebyshevApproximation - Izuzetak 5
try
{
const double PIPI9 = 4 * std::atan(1);
auto sinf8 = [](double x) { return std::sin(x); };
ChebyshevApproximation chsin16(sinf8,0, PIPI9,10);
std::cout << chsin16.integrate(-2, PIPI9 / 2);
//Bad interval
}
catch (std::domain_error e)
{
std::cout << "'" << e.what() << "'"<<std::endl;
}
catch (...)
{
std::cout << "Pogresan tip izuzetka"<<std::endl;
}
    try
{
const double PIPI10 = 4 * std::atan(1);
auto sinf9 = [](double x) { return std::sin(x); };
ChebyshevApproximation chsin17(sinf9,0, PIPI10,10);
std::cout << chsin17.integrate(0, 20);
//Bad interval
}
catch (std::domain_error e)
{
std::cout << "'" << e.what() << "'";
}
catch (...)
{
std::cout << "Pogresan tip izuzetka";
}
    //AT11 - ChebyshevApproximation - Izuzetak 6
try
{
const double PIPI5 = 4 * std::atan(1);
auto sinf4 = [](double x) { return std::sin(x); };
ChebyshevApproximation chsin12(sinf4,0, PIPI5,10);
chsin12.trunc(1000);
//Bad order
}
catch (std::domain_error e)
{
std::cout << "'" << e.what() << "'"<<std::endl;
}
catch (...)
{
std::cout << "Pogresan tip izuzetka"<<std::endl;
}

    //AT12 - ChebyshevApproximation - Izuzetak 7
try
{
const double PIPI5 = 4 * std::atan(1);
auto sinf4 = [](double x) { return std::sin(x); };
ChebyshevApproximation chsin12(sinf4,0, PIPI5,10);
chsin12.trunc(-5);
//Bad order
}
catch (std::domain_error e)
{
std::cout << "'" << e.what() << "'"<<std::endl;
}
catch (...)
{
std::cout << "Pogresan tip izuzetka"<<std::endl;
}

	return 0;
}