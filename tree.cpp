#include <string>
#include <iostream>
#include <algorithm>
#include "tree.h"



//*********************************************************
//*           MEMBER FUNCTIONS OF THE CLASS               *
//*********************************************************
Tree::Tree()
{
    tree_id=0; 
    tree_dbh=0; 
    status_tree=" ";
    health_tree=" ";
    spc_common=" "; 
    zipcode=0;
    boroname=" "; 
    x_sp=0.00;
    y_sp=0.00;
  
}

Tree::Tree ( int id, int diam, string status, string health, 
           string spc, int zip, string boro, double x, double y)
{

    tree_id=id; 
    tree_dbh=diam; 
    status_tree=status;
    health_tree= health;
    spc_common=spc; 
    zipcode=zip;
    boroname=boro; 
    x_sp=x;
    y_sp=y;
  

}

string Tree::common_name() const
{
    return spc_common;
}

string Tree::borough_name()const
{
    return boroname;
}

double Tree::diameter()
{
    return tree_dbh;
}

//*********************************************************
//*           FRIEND FUNCTIONS                            *
//*********************************************************

ostream& operator<< (ostream & os, const Tree & t )
{
   cout<<t.tree_id<<" "<<t.tree_dbh<<" "<<t.status_tree<<" "<<t.health_tree<<" "<<t.spc_common<<" "<<t.zipcode<<" "<<t.boroname<<" ";
   cout<<t.x_sp<<" "<<t.y_sp<<endl;
   return os;
}


bool operator==(const Tree & t1, const Tree & t2)
{
    string t1_common= t1.spc_common;
    string t2_common= t2.spc_common;
    transform(t1_common.begin(), t1_common.end(), t1_common.begin(), ::tolower);
    transform(t2_common.begin(), t2_common.end(), t2_common.begin(), ::tolower);

    if ((t1_common==t2_common) && (t1.tree_id==t2.tree_id))
        return true;
    else
        return false;
}

bool operator<(const Tree & t1, const Tree & t2)
{
    string t1_common= t1.spc_common;
    string t2_common= t2.spc_common;
    transform(t1_common.begin(), t1_common.end(), t1_common.begin(), ::tolower);
    transform(t2_common.begin(), t2_common.end(), t2_common.begin(), ::tolower);

    if (t1_common < t2_common)
        return true;
    else if ((t1_common == t2_common) && (t1.tree_id < t2.tree_id))
        return true;
    else
        return false;
}


bool samename(const Tree& t1, const Tree & t2) 
{
    string t1_common= t1.spc_common;
    string t2_common= t2.spc_common;
    transform(t1_common.begin(), t1_common.end(), t1_common.begin(), ::tolower);
    transform(t2_common.begin(), t2_common.end(), t2_common.begin(), ::tolower);


    if(t1_common == t2_common)
        return true;
    else
        return false;
}

bool islessname(const Tree & t1, const Tree & t2)
{
    string t1_common= t1.spc_common;
    string t2_common= t2.spc_common;
    transform(t1_common.begin(), t1_common.end(), t1_common.begin(), ::tolower);
    transform(t2_common.begin(), t2_common.end(), t2_common.begin(), ::tolower);

    if(t1_common < t2_common)
        return true;
    else
        return false;

}



    

     


