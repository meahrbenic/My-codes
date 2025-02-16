#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dajMax(vector<int> &v){
    int max=v[0]; 
    for(int i=0; i<v.size(); i++)
        if(v[i]>max) max=v[i];
    return max; 
}

void prebroj(vector<int>&v, int exp){
    vector<int> povratni(v.size());
    vector<int> brojac(10); 
    for(int i=0; i<v.size(); i++){
        brojac[ ( v[i]/exp) % 10 ]++; 
    }
    for(int i=1; i<10; i++){
        brojac[i]+=brojac[i-1];
    }
    for(int i=v.size()-1; i>=0; i--){
        povratni[ brojac[ ( v[i]  /exp)%10 ]-1 ]= v[i];
        brojac[ ( v[i]  /exp)%10 ]--;
    }
    for(int i=0; i<v.size(); i++){ 
        v[i]=povratni[i];
    }
} 

void radixSort(vector<int> &a){
    int max=dajMax(a); 
    for(int i=1; max/i>0 ; i*=10) prebroj(a,i);
}

void popravi(vector<int> &a,int i, int v){
    int l,d; 
    while(! (i<v && i>= (v/2)) ) {
        l=2*i+1; 
        d=2*i+2; 
        if(d<v && a[d]>a[l]) 
            l=d; 
        if(a[i]>a[l]) 
            break; 
        int pom=i; 
        i=l; 
        swap(a[pom], a[i]);
    }
}

void stvoriGomilu( vector<int> &a ){
    for(int i= a.size()/2 ; i>=0; i--) 
        popravi(a,i,a.size()); 
}

void umetniUGomilu(vector<int> &a, int umet,int &velicina){
    a.push_back(umet); 
    velicina++; 
    int tmp=a.size()-1; 
    while(tmp!=0 && a[tmp] > a[(tmp-1)/2]){
        swap( a[tmp] , a[(tmp-1)/2] ); 
        tmp= (tmp-1)/2;
    }
}

int izbaciPrvi(vector<int> &a, int &velicina){
    if(a.size()!=0){
        velicina--; 
        swap(a[0], a[velicina] );
        if(velicina!=0) popravi(a,0,velicina);
    }
    return a[velicina];
}

void gomilaSort(vector<int> &a){
    int v; 
    int x; 
    stvoriGomilu(a); 
    for(int i=0; i<a.size(); i++){
        if(i==0) v=a.size();
        x=izbaciPrvi(a,v);
    }
}

int main(){
    std::vector<int> ts; 
    ts.push_back(123); 
    ts.push_back(1235); 
    ts.push_back(53213); 
    ts.push_back(2944643); 
    ts.push_back(6436); 
    
    auto b=ts; 
    stvoriGomilu(ts);
    
    radixSort(b); 
    gomilaSort(ts);
    bool testOk = true;
    for(int i(0);i<ts.size();i++){
        if(ts[i]!=b[i]) testOk = false;;
    }
    if(testOk) cout<<"OK";
/**/
    return 0; 
}