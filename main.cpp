#include <iostream>
#include "UPGMABuilder.hpp"

using namespace std;


int main(){
  UPGMABuilder u("infile.grid");
  //u.g.print();
  u.makeTree();
  cout<<u.g.groups.size()<<endl;
  //for(int i = 0; i < u.g.groups[0]->leafs.size();i++){
  //  cout<<u.g.groups[0]->leafs[i]->group_id<<endl;
  //}
  u.printTree();
  return 0;
}
