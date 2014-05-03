#ifndef __NEIGHBOR_JOINER
#define __NEIGHBOR_JOINER

/* This class builds the UPGMA tree */

#include "grid.hpp"

using namespace std;

class NeighborJoiner{
public:
  grid g;

  NeighborJoiner(string grid_ifile):g(grid_ifile){
  }

  /*Allows the re-use of this object for different grid files */
  void swapGridFiles(string grid_ifile){
    g.setAndParse(grid_ifile);
  }

  /* Iterates over merge() until there is only one group */
  void makeTree(){
    if(g.groups.size()<3){
      cout<<"Need at least 3 groups to start"<<endl;
      exit(0);
    }
    while(g.groups.size()>1){
      //cout<<g.groups.size()<<endl;
      merge();
    }
  }


  void merge(){
    /* Make sure there are enough groups */
    if(g.groups.size()<2){
      cout<<"Grid requires more than 2 elements for neighbor joining."<<endl;
      exit(0);
    }

    /* Calculate r() values for all groups */
    for(int i = 0; i < g.groups.size();i++){
      double val=0.0;
      for(int j = 0; j < g.groups.size();j++){
	if(i==j)
	  continue;
	val+=g.weight_pool[pair<group *,group *>(g.groups[i],g.groups[j])];
      }
      g.groups[i]->height=val;
    }


    /* Find closest groups */
    vector<group *>::iterator loc1 = g.groups.begin();
    vector<group *>::iterator loc2 = g.groups.begin();
    loc2++;
    
    double min=g.groupDistanceNJ(*loc1,*loc2);
    //cout<<min<<endl;
    //exit(0);
    int count =0;
    for(vector<group *>::iterator i=g.groups.begin(); i!=g.groups.end(); i++){
      for(vector<group *>::iterator j=g.groups.begin(); j!=g.groups.end(); j++){
	if(i==j){
	  //cout<<"0\t";
	  continue;
	}
	double tmp=g.groupDistanceNJ(*i,*j);
	//cout<<tmp<<"\t";
	//cout<<tmp<<" "<<min<<endl;
	if(tmp<min){
	  loc1=i; loc2=j; min=tmp;
	}
      }
      //cout<<endl;
    }

    /* Make new group composed of old groups */
    group *new_group= new group(*loc1,*loc2, 0);
    
    /* Left group weight in subgroup */
    double r1r2=(new_group->left->height-new_group->right->height);
    double r2r1=(new_group->right->height-new_group->left->height);
    if(g.groups.size()>2){
      r1r2/=(g.groups.size()-2);
      r2r1/=(g.groups.size()-2);
    }
    double dlr=g.weight_pool[pair<group *,group *>(new_group->left,new_group->right)];
    //cout<<"r1r2: "<<r1r2<<" dlr: "<<dlr<<endl;
    new_group->left_weight=(dlr+r1r2)/2;

    /* Right group weight in subgroup */
    new_group->right_weight=(dlr+r2r1)/2;

    /* Erase old groups */
    g.groups.erase(loc2);
    g.groups.erase(loc1);
    
    /* Add new groups weights to graph */
    for(uint i = 0; i < g.groups.size(); i++){
      pair<group *, group *> tmp(new_group, g.groups[i]);
      pair<group *, group *> tmp2(g.groups[i], new_group);
      double gd=(g.weight_pool[pair<group *, group *>(new_group->left,g.groups[i])]+g.weight_pool[pair<group *, group *>(new_group->right,g.groups[i])]-g.weight_pool[pair<group *, group *>(new_group->left,new_group->right)])/2;
      g.weight_pool[tmp] = gd;
      g.weight_pool[tmp2]= gd;
    }

    /* Add new group to groups vector */
    g.groups.push_back(new_group);
    printTreeRec(new_group);
    cout<<"-------------------------------------------------"<<endl;
  }

  void printTree(){
    printTreeRec(g.groups[0]);
  }

  int printTreeRec(group *gr){
    if(gr->is_leaf==true){
      cout<<" id="<<gr->group_id<<" "<<gr->s;
      if(gr->left_weight<0||gr->right_weight<0)
	cout<<"*";
      cout<<endl;
      return 1;
    }
    int l=printTreeRec(gr->left);
    for(int i = 0; i < l;i++)
      cout<<"\t";
    //cout<<"intern l="<<gr->left_weight<<" r="<<gr->right_weight<<endl;
    cout<<"intern id="<<gr->group_id<<" l="<<gr->left->group_id<<" r="<<gr->right->group_id<<" l="<<gr->left_weight<<" r="<<gr->right_weight;
    if(gr->left_weight<0||gr->right_weight<0)
      cout<<"*";
    cout<<endl;
    printTreeRec(gr->right);
    return l+1;
  }

};



#endif
