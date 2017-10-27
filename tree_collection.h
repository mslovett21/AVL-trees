/*******************************************************************************
  Title          : tree_collection.h
  Author         : Patrycja Krawczuk
  Created on     : March 14th, 2017
  Description    : Header file for Tree Collection class, describes functionality of the class
  Purpose        :  
  Usage          : 
  Build with     : makefile, (g++ -std=c++11)
  Modifications  : 

*******************************************************************************/
#ifndef __Tree_Collection_H__
#define __Tree_Collection_H__

#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <set>

#include "avl.h"
#include "tree.h"



class Borough_Tree;

using namespace std;

class TreeCollection
{
public:
     
    //deault constructor for the class
    TreeCollection ( );

    //destructor for the class
    ~TreeCollection ( );

    /** total_tree_count()  
    * This method returns the total number of Tree objects stored in the collectiom
      @returns number of trees 
    */
    int total_tree_count(); 

    /*count_of_tree_species()
    * This method returns the number of Tree objects in the collection whose spc_common species
    * name matches the species_name specified by the parameter. If the method is called 
    * on non-exisiting species, the return value is 0
    * @param const   string     [inout]  species_name 
      @returns count of tree species or 0 if none found
    */
    int count_of_tree_species ( const string & species_name ); 


    /*count_of_tree_in_boro()
    * This method returns the number of Tree objects in the collection that are located in the
    * borough specified by the parameter. If the method is called with a non-exisitng borough name returns 0
    * on non-exisiting species, the return value is 0
    * @param const   string     [inout]  boro_name 
    */
    int count_of_trees_in_boro( const string & boro_name ); 


    /*get_matching_species()
    * This method returns a list<string> object containing a list of all the actual tree species 
    * that match a given parameter string species_name. The list does not contain any duplicates and might be empty
    * @param const   string     [inout]  species_name
    * @return list of matching species 
    */
    list<string> get_matching_species(const string & species_name);

    /*count_of_trees_of_specific_type_in_boro()
    * This method returns the number of Tree objects in the collection that are located in the
    * borough specified by the parameter and whose spc_common species name matches the species_name 
    * specified by the other parameter. If non-exisitng borough or species return 0
    * @param const   string     [inout]  boro_name 
    * @param const   string     [inout]  species_name
    */
    int count_of_trees_of_specific_type_in_boro(const string &species_name, const string boro_name);
   

    /*print   ( ostream& out ) const;
    * Prints the Tree object to the screen in the specified format.
    * Format:  208230 13 Alive Fair London planetree 10024 Manhattan 40.78 -73.97 , one per line
    * @param   ostream                [inout]  write_stream
    * @pre    working open stream is provided
    * @post   Tree objects are printed to the screen if the collection is not empty
    * @returns osream&
    */
    void   print   ( ostream& out ) const;

     /*clear   ();
    * Clears the collection, deletes all the Trees in the collection.
    * It also empties TreeBorough and TreeSpecies vectors.
    * @post   The collection is empty
    */
    void   clear(); 

    /**insert(const Tree & x)-allows adding new objects to the tree 
    * Insert methods first finds a right place for x object in the sorted collection.
    * This method compares the two trees using spc_common as the primary key and tree_id as a secondary key.
    * If x is a duplicate of another Tree object which exist in AVL_Tree it is not inserted.
    * @param  const Tree   x        [inout]  tree to insert
    * @pre    Tree contains valid data
    * @post   If x is not a duplicate, x is added to the tree
    */
    void   insert( const Tree& x);  // insert element x


    /**remove(const Tree & x)-allows removing objects from the tree 
    * Remove methods first finds the postion where x should be positioned in the tree. Then if object equal to x
    *(spc_common and tree_id) it is removed. If not tree equal to object x is found then no changes.
    * @param  const Tree   x        [inout]  tree to remove
    * @pre    Tree contains valid data
    * @post   If x is found in the tree, it is deleted, otherwise nothing happens
    */
    void   remove( const Tree& x);  // remove element x



    /** find() - search method, 
    * This method searches the tree using spc_common as the primary key and tree_id as a secondary key
    * in order to find the x tree object, if not found it returns a special NOT_FOUND tree object by reference
    * @param const   Tree      [inout]  x 
    * @post  NONE
      @returns FOUND object if search was successful or NOT_FOUND tree object otherwise
    */
    Tree find(const Tree& x);




  

private:

      /*find_matching_name()
    * This method takes search TreeSpecies set and finds names that matches to the orginal_name (user's input)
    * The rules of matching are as desrcibed in the assigment on page 3.
    * Matching names are added to v list. This method call other helper functions to complete the task.
    * @param const   string     [inout]  orginal_name
    * @param list<string>       [inout]  v
    * @return 
    */
    void find_matching_names(const string& orginal_name, list<string>& v);

      /*add_common_name()
    * This method add a name of the tree (spc_common) to TreeSpecies
    * if that name is not already in the set. 
    * @param  string     [inout]  name
    */
    void add_common_name(string name);

    /*delete_whitespaces()
    * This method removes additional whitespaces (tabs, multiple blanks and so on) between words.
    * It separates words of a string with single blank character ASCII (20)
    * @param  string     [inout]  line_from_file;
    * @returns string in which words are separated by one blank (no other whitesaces)
    */
    string delete_whitespace(string line_from_file);


    /*match_strings()
    * This method takes two strings and checks if tree_species matches user_input
    * The rules of matching are as desrcibed in the assigment on page 3.
    * @param   string       [inout]  tree_species
    * @param   string       [inout]  user_input
    * @return true if match, false otherwise
    */

    bool match_strings( string& tree_species, string& user_input);

    /*fill_borough_vector()
    * This is a helper function that fills out TreeBorogh vector with names of valid NYC boroughs
    * and assignes to each borough number 0 as startig number of trees there.
    * @post the TreeBorough vector contains approciate data
    */
    void fill_borough_vector();

  	set<string> TreeSpecies;//set that stores the set of all spc_common names that were found in the input data

	  vector<Borough_Tree> TreeBorough;//name of each NYC borough and how many trees from the data set are there

	  AVL_Tree nyc_tree;//stores tree objects
	
};


#endif /* Tree_Collection_H__ */

