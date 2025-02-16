//TP 2021/2022: Zadaća 2, Zadatak 5
#include <iostream>
#include <cmath>
#include <type_traits>
#include <stdexcept>
#include <functional>
#include <vector>
#include <deque>

template <typename pok>
int Velicina(pok pok1, pok pok2){
    int br=0; 
    while(pok1!=pok2){
        br++;
        pok1++; 
    }
    return br; 
}

template <typename TipElemenata> 
void UnistiMatricu(TipElemenata **mat, int br_redova){
    if(!mat) return; 
    for(int i=0; i<br_redova; i++) delete[] mat[i];
    delete[] mat; 
}

template <typename TipElemenata> 
TipElemenata **StvoriMatricu(int br_redova, int br_kolona){
    TipElemenata **mat = new TipElemenata*[br_redova];
    int brojac=0; 
    try{
        while(brojac<br_redova) mat[brojac++]=new TipElemenata[br_kolona]; 
    }
    catch(...){
        UnistiMatricu(mat, br_redova);
        throw;
    }
    return mat; 
}

template <typename iterTip1,typename iterTip2, typename funTip>
auto GeneraliziraniSpoljasnjiProizvod(iterTip1 apoc,iterTip1 akr, iterTip2 bpoc, iterTip2 bkr, funTip f){
    int m=Velicina(apoc,akr); 
    int n=Velicina(bpoc,bkr);
    decltype( f(*apoc,*bpoc)) **C=nullptr;
    auto pomocniPrvi=apoc; 
    auto pomocniDrugi=bpoc; 
    try{
        C = StvoriMatricu<decltype(f(*apoc,*bpoc))>(m,n);
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                C[i][j]= f(*pomocniPrvi,*pomocniDrugi);
                pomocniDrugi++;
            }
            for(int k=0; k<n; k++) pomocniDrugi--;
            pomocniPrvi++;
        }
    }
    catch(...){
        UnistiMatricu(C, m);
        throw std::range_error("Nema dovoljno memorije!"); 
    }  
    return C; 
}

int funkcija( int x, int y){
    return x+2*y; 
}

int main ()
{
    
    std::cout<<"Duzina prve sekvence: "; 
    int duzina1=0; 
    std::cin>>duzina1; 
    std::cout<<"Elementi prve sekvence: "; 
    std::vector<double> vektor(duzina1); 
    for(int i=0; i<duzina1; i++){
        std::cin>>vektor.at(i);
    }

    std::cout<<"Duzina druge sekvence: "; 
    int duzina2=0; 
    std::cin>>duzina2; 
    std::cout<<"Elementi druge sekvence: "; 
    std::deque<double> dek(duzina2); 
    for(int i=0; i<duzina2; i++){
        std::cin>>dek.at(i);
    }
    double (*pok_na_fun)(double, double);
    pok_na_fun = [](double x, double y) { return x + 2*y; };

    try{
    double **p=GeneraliziraniSpoljasnjiProizvod(vektor.begin(),vektor.end(),dek.begin(),dek.end(), pok_na_fun);
    std::cout<<"Generalizirani spoljasnji proizvod uz f(x,y)=x+2y: "<<std::endl;
    for(int i=0; i<duzina1; i++){
        for(int j=0; j<duzina2; j++){
            std::cout<<p[i][j]<<" ";
        }
        std::cout<<std::endl; 
    }
    UnistiMatricu(p,duzina1);
    }
    catch(std::range_error e){
        std::cout<<e.what();
    }
   
	return 0;
}
