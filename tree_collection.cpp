/*******************************************************************************
  Title          : tree_collection.cpp
  Author         : Patrycja Krawczuk
  Created on     : March 14th, 2017
  Description    : Methods for TreeCollection class
  Purpose        :  
  Usage          : 
  Build with     : makefile, (g++ -std=c++11)
  Modifications  : 

*******************************************************************************/
#include "tree_collection.h"
#include <string>

//HELPER CLASS
class Borough_Tree
{

public:

	Borough_Tree();

	Borough_Tree(string name, int number): borough_name(name), number_of_trees(number) {};

	~Borough_Tree() {};

	
private:

	string borough_name;

	int number_of_trees;

	friend class TreeCollection;


};


TreeCollection::TreeCollection ( )
{

}
TreeCollection::~TreeCollection ( )
{
	nyc_tree.clear();
}

int TreeCollection::total_tree_count()
{
	return TreeBorough[0].number_of_trees; 
} 



int TreeCollection::count_of_tree_species ( const string & species_name )
{
	Tree find_tree(0,0,"","",species_name,0,"",0,0);
	list<Tree> tree_list;
	tree_list=nyc_tree.findallmatches(find_tree);
	int size=tree_list.size();
	return size;

} 
    

int TreeCollection::count_of_trees_in_boro( const string & boro_name )
{
	string place;
	for(int i=0; i<TreeBorough.size(); i++)
    {
    	place=TreeBorough[i].borough_name;
    	transform(place.begin(), place.end(), place.begin(), ::tolower);
    	if(place==boro_name)
    		return TreeBorough[i].number_of_trees;
    }
    
    	return 0;
} 

int TreeCollection::count_of_trees_of_specific_type_in_boro(const string& species_name, const string boro_name)
{
	//First I find all the Trees of the given type
	Tree find_tree(0,0,"","",species_name,0,"",0,0);
	list<Tree> tree_list;
	tree_list=nyc_tree.findallmatches(find_tree);
	
	Tree the_tree;
	string tree_borough;
	int counter=0;

    //I'm ready to traverse through the list and find count of trees in the specific borough
    list<Tree>::iterator j;
    for( j = tree_list.begin(); j != tree_list.end(); ++j)
    {
    	the_tree=*j;
        tree_borough=the_tree.borough_name();
        transform(tree_borough.begin(), tree_borough.end(), tree_borough.begin(), ::tolower);
        if(tree_borough==boro_name)
        {
        	counter++;
        }
	}
	return counter;
}




list<string> TreeCollection::get_matching_species(const string & species_name)
{
 
	list<string> mylist;
	list<Tree> tree_results;
	find_matching_names(species_name,mylist);
	return mylist;

} 


void TreeCollection::find_matching_names(const string& orginal_name, list<string>& list_of_matches)
{
	set<string>::iterator i;
	string result_user=orginal_name;
	string result_species;
	
	for( i = TreeSpecies.begin(); i != TreeSpecies.end(); ++i)
	{
		vector<string> v_tree_species;
		result_species=delete_whitespace(*i);

		if(match_strings(result_species, result_user))
		{
			list_of_matches.push_back(*i);
		}
	}
		
}


bool TreeCollection::match_strings( string& tree_species, string& user_input)
{
	size_t found=tree_species.find(user_input);

	if(found!=string::npos)
		return true;
	else
		return false;
}





string TreeCollection::delete_whitespace(string line_from_file)
{

  int i=0;
  string result=""; 
  while(i<line_from_file.size())
  {
    string temp="";
    while((isspace(line_from_file[i])==false) && (line_from_file[i]!='-') && (i<line_from_file.size()))//while not a whitespace
    {

      temp=temp+line_from_file[i];
      i++;
    }
    if(temp.size()>0)//I actually found some valid content
    {
      transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
      if(result=="")
      {
      	result=temp;
      }
      else
      {
      	result=result+" "+temp;
      }
    }
    i++;
  }
 // cout<<" I am returning this from delete white space "<<result<<endl;
  return result;

}

void TreeCollection::print( ostream& out ) const
{
	this->nyc_tree.print(out);

}


void TreeCollection::clear()
{
	nyc_tree.clear();
	TreeBorough.clear();
	TreeSpecies.clear();
}


void TreeCollection::add_common_name(string name)
{
	bool found = (std::find(TreeSpecies.begin(), TreeSpecies.end(), name) != TreeSpecies.end());

	if (found==true){
	 ;}//do nothing
	 else{
	 	TreeSpecies.insert(name);
	 }

}


void TreeCollection::fill_borough_vector()
{
	Borough_Tree NYC_boro("NYC", 0);
	TreeBorough.push_back(NYC_boro);

	Borough_Tree Manhattan_boro("Manhattan", 0);
	TreeBorough.push_back(Manhattan_boro);
	
	Borough_Tree Bronx_boro("Bronx", 0);
	TreeBorough.push_back(Bronx_boro);

	Borough_Tree Brooklyn_boro("Brooklyn", 0);
	TreeBorough.push_back(Brooklyn_boro);

	Borough_Tree Queens_boro("Queens", 0);
	TreeBorough.push_back(Queens_boro);
	
	Borough_Tree StatenIsland_boro("Staten Island", 0);
	TreeBorough.push_back(StatenIsland_boro);



}


void TreeCollection::insert( const Tree& x)
{
	this->nyc_tree.insert(x);

	if(TreeBorough.size()==0)
	{
		fill_borough_vector();
	}
    
    //if the insert was succesful update the count
	if(nyc_tree.insert_successful())
	{	
		string temp_name;
		temp_name=x.common_name();
		transform(temp_name.begin(), temp_name.end(), temp_name.begin(), ::tolower);
		add_common_name(temp_name);
		string boro_name = x.borough_name();
		transform(boro_name.begin(), boro_name.end(), boro_name.begin(), ::tolower);
		string place;


	    for(int i=1; i<TreeBorough.size(); i++)
	    {
	    	place=TreeBorough[i].borough_name;
	    	transform(place.begin(), place.end(), place.begin(), ::tolower);
	    	if(place==boro_name)
	    	{
	    		TreeBorough[i].number_of_trees++;
	    		TreeBorough[0].number_of_trees++;
	    		i=TreeBorough.size();//break from the loop
	    	}
	    }
	}//end of if

}

Tree TreeCollection::find(const Tree& x)
{
	Tree found=nyc_tree.find(x);
	return found;
}


    
void TreeCollection::remove( const Tree& x)
{
   nyc_tree.remove(x);
   if (nyc_tree.remove_successful())
   {	
		string boro_name = x.borough_name();
		transform(boro_name.begin(), boro_name.end(), boro_name.begin(), ::tolower);
		string place;

	    for(int i=1; i<TreeBorough.size(); i++)
	    {
	    	place=TreeBorough[i].borough_name;
	    	transform(place.begin(), place.end(), place.begin(), ::tolower);
	    	if(place==boro_name)
	    	{
	    		TreeBorough[i].number_of_trees--;
	    		TreeBorough[0].number_of_trees--;
	    		i=TreeBorough.size();//break from the loop
	    	}
	    }
   }

}

