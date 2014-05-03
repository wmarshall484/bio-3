#ifndef __UPGMA_BUILDER
#define __UPGMA_BUILDER

/* This class builds the UPGMA tree */

#include "grid.hpp"

using namespace std;

class UPGMABuilder{
public:
  grid g;

  UPGMABuilder(string grid_ifile):g(grid_ifile){
  }

  /*Allows the re-use of this object for different grid files */
  void swapGridFiles(string grid_ifile){
    g.setAndParse(grid_ifile);
  }

  /* Iterates over merge() until there is only one group */
  void makeTree(){
    while(g.groups.size()!=1){
      //cout<<g.groups.size()<<endl;
      merge();
    }
  }

  /* The merge function performs one merge operation; e.g., it
     iterates over each pair of groups in the grid, finds the ones
     that are "closest" to one another, merges them into another
     group, deletes the former two groups from the list, and adds the
     weights of the new group to every other group to the
     weight_pool */

  void merge(){
    /* Make sure there are enough groups */
    if(g.groups.size()<2){
      cout<<"Grid has been collapsed as much as possible."<<endl;
      exit(0);
    }

    /* Find closest groups */
    vector<group *>::iterator loc1 = g.groups.begin();
    vector<group *>::iterator loc2 = g.groups.begin();
    loc2++;
    /*for(int i = 0; i < (&(*loc1))->leafs.size();i++){
      cout<<(&(*loc1))->leafs[i]->group_id<<endl;
    }
    cout<<endl;
    for(int i = 0; i < (&(*loc2))->leafs.size();i++){
      cout<<(&(*loc2))->leafs[i]->group_id<<endl;
    }

    exit(0);*/

    double min=g.groupDistance(*loc1,*loc2);
    
    //cout<<min<<endl;
    //exit(0);
    for(vector<group *>::iterator i=g.groups.begin(); i!=g.groups.end(); i++){
      for(vector<group *>::iterator j=i; j!=g.groups.end(); j++){
	if(i==j) continue;
	//cout<<(*i)->group_id<<" "<<(*j)->group_id<<endl;
	//continue;
	double tmp=g.groupDistance(*i,*j);
	if(tmp<min){
	  loc1=i; loc2=j; min=tmp;
	}
      }
    }

    /* Make new group composed of old groups */
    group *new_group= new group(*loc1,*loc2, min/2);

    /* Erase old groups */
    g.groups.erase(loc2);
    g.groups.erase(loc1);
    
    /* Generate new weights for the new group */
    for(uint i = 0; i < g.groups.size(); i++){
      pair<group *, group *> tmp(new_group, g.groups[i]);
      pair<group *, group *> tmp2(g.groups[i], new_group);
      double gd=g.groupDistance(new_group, g.groups[i]);
      g.weight_pool[tmp] = gd;
      g.weight_pool[tmp2]= gd;
    }

    /* Add new group to groups vector */
    g.groups.push_back(new_group);
    //printTreeRec(new_group);
    //cout<<"-------------------------------------------------"<<endl;
  }

  void printTree(){
    printTreeRec(g.groups[0]);
  }

  int printTreeRec(group *gr){
    if(gr->is_leaf==true){
      cout<<gr->s<<" id="<<gr->group_id<<endl;
      return 1;
    }
    int l=printTreeRec(gr->left);
    for(int i = 0; i < l;i++)
      cout<<"\t";
    cout<<"intern id="<<gr->group_id<<" l="<<gr->left->group_id<<" r="<<gr->right->group_id<<" lw="<<gr->left_weight<<" rw="<<gr->right_weight<<" h="<<gr->height<<endl;
    printTreeRec(gr->right);
    return l+1;
  }

};

#endif
