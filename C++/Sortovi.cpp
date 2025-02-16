#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

template <typename Tip>
void bubble_sort(Tip* niz, int vel){
    for(int i=vel-1; i>=1; i--){
        for(int j=1; j<=i; j++){
            if(niz[j-1]>niz[j]){
                auto pom=niz[j-1]; 
                niz[j-1]=niz[j]; 
                niz[j]=pom; 
            }
        }
    }
}

template <typename Tip>
void selection_sort(Tip* niz, int vel){
    for(int i=0; i<vel; i++){
        auto min=niz[i];
        auto pmin=i; 
        for(int j=i+1; j<vel; j++){
            if(niz[j]<min){
                min=niz[j];
                pmin=j; 
            } 
        }
        niz[pmin]=niz[i];
        niz[i]=min; 
    }
}

template <typename Tip>
void zamijeni(Tip* niz, const int i, const int j){
    auto pom=niz[i]; 
    niz[i]=niz[j]; 
    niz[j]=pom; 
}

template <typename Tip> 
int Particija(Tip* niz, const int prvi, const int zadnji){
    Tip pivot = niz[prvi];
    int p = prvi+1; 
    while(p<=zadnji){
        if(niz[p] <= pivot) p++; 
        else break; 
    }
    for(int i=p+1; i<=zadnji; i++){
        if(niz[i] < pivot){
            zamijeni(niz, p, i);
            p++; 
        }
    }
    zamijeni(niz,prvi,p-1); 
    return p-1; 
}

template <typename Tip>
void QS(Tip*niz, const int prvi, const int zadnji){
    if(prvi<zadnji){
        int j=Particija(niz, prvi, zadnji);
        QS(niz,prvi, j-1); 
        QS(niz, j+1, zadnji);
    }
}

template <typename Tip>
void quick_sort(Tip* niz, int vel){
    QS(niz, 0, vel-1); 
}


template <typename Tip>
void Merge(Tip* niz,const int l, const int p,const int q, const int u){
    int i=0; 
    int j=q-l; 
    int k=l; 
    Tip* B=new Tip[u-l+1]; 
    for(int m=0; m<=u -l; m++){
        B[m]=niz[l+m];
    }
    while(i<=p-l && j<=u-l){
        if(B[i]<B[j]) niz[k] =B[i++];
        else niz[k]=B[j++];
        k++;
    }
    while(i<=p-l) niz[k++]=B[i++]; 
    while(j<=u-l) niz[k++]=B[j++]; 

    delete [] B; 
}

template <typename Tip>
void MS(Tip* niz,const int l, const int u){
    if(u>l){
        int p=(l+u-1)/2; 
        int q=p+1; 
        MS(niz,l,p); 
        MS(niz,q,u); 
        Merge(niz,l,p,q,u);
    }
}

template <typename Tip>
void merge_sort(Tip* niz, int vel){
    MS(niz, 0, vel-1);
}

void ucitaj(string filename, int*& niz, int &vel){
    ifstream ulaz(filename.c_str()); 
    if(!ulaz) throw "Otvaranje datoteke neuspješno!"; 
    std::vector<int> v;
    int numb; 
    while(ulaz){
        ulaz>>numb;
        v.push_back(numb); 
    }
    vel=v.size()-1; 
    niz=new int[vel]; 
    copy(v.begin(), v.end()-1,niz);
}

void generisi(string filename, int vel){
    ofstream izlaz(filename.c_str());
    if(!izlaz) throw "Kreiranje datoteke neuspješno!"; 
    srand(time(NULL)); 
    int br; 
    for(int i=0; i<vel; i++){
        br= rand(); 
        izlaz<<br; 
    }
}


int main(){

    int niz[]={1,4,7,2,3,9,5,8,0};

    bubble_sort(niz,9);
    for(int i=0; i<9; i++){
        std::cout<<niz[i]<<" ";
    }

    std::cout<<std::endl; 

    std::string s[6] = {"b", "c","aa","a", "s", "ddd"}; 
    
    selection_sort(s,6);

    for(int i=0; i<6; i++){
        std::cout<<s[i]<<" ";
    }
    std::cout<<std::endl; 
    int niz1[]={1,2,3,4,5,6,7,8,10,11,12,13,14,15,16,17,0};
    quick_sort(niz1,17);
    for(int i=0; i<17; i++){
        std::cout<<niz1[i]<<" ";
    }
    std::cout<<std::endl; 
    int niz2[] ={124,13552,363,14,634,846,1241,862,245,467,13425,64};
    
    merge_sort(niz2,10);
    for(int i=0; i<12; i++){
        std::cout<<niz2[i]<<" ";
    }
    return 0; 
}