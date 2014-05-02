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
      cout<<g.groups.size()<<endl;
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
    vector<group>::iterator loc1 = g.groups.begin();
    vector<group>::iterator loc2 = g.groups.begin(); loc2++;
    double min=g.groupDistance(*loc1,*loc2);
    for(vector<group>::iterator i=g.groups.begin(); i!=g.groups.end(); i++){
      for(vector<group>::iterator j=i; j!=g.groups.end(); j++){
	j++; if(j==g.groups.end()) continue;
	double tmp=g.groupDistance(*i,*j);
	if(tmp<min){
	  loc1=i; loc2=j; min=tmp;
	}
      }
    }

    /* Make new group composed of old groups */
    group new_group(&(*loc1),&(*loc2), min/2);

    /* Erase old groups */
    g.groups.erase(loc2);
    g.groups.erase(loc1);
    
    /* Generate new weights for the new group */
    for(uint i = 0; i < g.groups.size(); i++){
      pair<group, group> tmp(new_group, g.groups[i]);
      g.weight_pool[tmp] = g.groupDistance(new_group, g.groups[i]);
    }

    /* Add new group to groups vector */
    g.groups.push_back(new_group);
  }

};

#endif