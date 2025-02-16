#include <cmath>
#include <iostream>
#include <vector>

void Krug(std::vector<int> og, std::vector<int> &pomocni, int indeks){
    bool krug=false;
    if(og.size()!=0){
    for(int i=0; i<pomocni.size(); i++){
        if(i+indeks == og.size() && krug==false){ 
        //  std:std::cout<<" dosli smo do kraja ovog og "<<i<<" "<<indeks<<" "<< og.size()<< std::endl;
            indeks=0;  
            krug=true;
        }
        if(!krug) pomocni.at(i)=og.at(i+indeks);
        else{
           // std::cout<<"indeks: "<< indeks<<"  i "<<i<<std::endl; 
            pomocni.at(i)=og.at(indeks+0);
            indeks++; 
        }
    }
    }
}

int CiklickaPermutacija(std::vector<int> vek1, std::vector<int> vek2) {
    std::vector<int> pomocni(vek1.size()); 

    if(vek1.size()!=vek2.size()) return -1; 
    if(vek1.size()==vek2.size() && vek1.size()==0) return 0; 

    for(int i=0; i<vek1.size(); i++){
        //nadjemo broj koji je isti kao prvi 
        if(vek2.at(0) == vek1.at(i)){  
            //od i pa nadalje potrpamo u pomocni 
            //vratimo se na pocetak vek1 i to potrpamo u ostatak pomocnog 
            Krug(vek1, pomocni, i ); 
            if(vek2==pomocni) return i; 
        }
    }
    return -1;
}

int main() {

  std::vector<int> prva, druga;
  std::cout << "Prva sekvenca: ";
  // unos
  int br;
  for (;;) {
    std::cin >> br;
    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      break;
    }
    prva.push_back(br);
  }

  std::cout << "Druga sekvenca: ";
  for (;;) {
    std::cin >> br;
    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      break;
    }
    druga.push_back(br);
  }

  if (CiklickaPermutacija(prva, druga) == -1) std::cout << "Druga sekvenca nije ciklicka permutacija prve.";  
  else std::cout << "Druga sekvenca je ciklicka permutacija prve s pomakom " << CiklickaPermutacija(prva, druga) << ".";

  return 0;
}
