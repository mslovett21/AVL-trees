/*******************************************************************************
  Title          : tree.h
  Author         : Patrycja Krawczuk
  Created on     : March 14th, 2017
  Description    : header file for Tree class, describes functionality of the Tree class
  Purpose        :  
  Usage          : 
  Build with     : makefile, (g++ -std=c++11)
  Modifications  : 

*******************************************************************************/
#ifndef __Tree_H__
#define __Tree_H__
#include <string>
#include <iostream>

using namespace std;

class Tree
{
public:

    //Default constructor for the class
    Tree();

    /** Tree(...) - class constructor with parameters
     * assigns given values to the member variables, 
     * DATA HAS TO BE PREVIOUSLY VALIDATED IN THE MAIN
     * @param int      id            [in]  tree's id
     * @param int      diam          [in]  tree's diameter
     * @param string   status        [in]  tree's status
     * @param string   health        [in]  tree's health
     * @param string   spc           [in]  tree's common name
     * @param int      zip           [in]  tree's location -zip code
     * @param string   boro          [in]  tree's location -borough
     * @param double   x             [in]  tree's location -latitute  
     * @param double   y             [in]  tree's location -longitute
     * @pre   DATA WAS VALIDATED IN THE MAIN.CPP ALL THE VALUES ARE WITHIN RANGES 
     * @post  object is assigned all valid values
     */
    Tree ( int id, int diam, string status, string health, 
           string spc, int zip, string boro, double x, double y );

    /**operator ==(const Tree & t1, const Tree & t2); - overload comparision == operator 
    * Given two Tree objects, it returns true IFF they have the same species common name 
    * (spc_common) and tree_id (case insensitive)
    * This is a friend function
    * @param  const Tree   t1        [inout]  LHS object to compare
    * @param  const Tree   t2        [inout]  RHS object to compare
    * @pre    NONE
    * @post   NONE
    * @returns bool TRUE if equel, FALSE if not
    */
    friend bool operator==(const Tree & t1, const Tree & t2);

    /**operator <(const Tree & t1, const Tree & t2); - overload comparision < operator 
    * This method compares the two trees using spc_common as the primary key and tree_id as a secondary key
    * and returns true if t1 is less than t2 in this ordering and false otherwise
    * This is a friend function
    * @param  const Tree   t1        [inout]  LHS object to compare
    * @param  const Tree   t2        [inout]  RHS object to compare
    * @pre    NONE
    * @post   NONE
    * @returns bool TRUE if t1 less, FALSE otherwise
    */
    friend bool operator<(const Tree & t1, const Tree & t2);


    /** operator <<(ostream& write_stream, const Tree & t )
    * Prints the Tree object to the screen in the specified format.
    * Format:  208230 13 Alive Fair London planetree 10024 Manhattan 40.78 -73.97
    * This is a friend function
    * @param   ostream                [inout]  write_stream
    * @param   const Tree             [input]  Tree object to print
    * @pre    working open stream is provided
    * @post   Tree object is printed to the screen
    * @returns osream&
    */
    friend ostream& operator<< (ostream & os, const Tree & t );


    /**samename(const Tree & t1, const Tree & t2);  
    * Given two Tree objects, it returns true IFF they have the same species common name 
    * (spc_common) 
    * This is a friend function
    * @param  const Tree   t1        [inout]  LHS object to compare
    * @param  const Tree   t2        [inout]  RHS object to compare
    * @pre    NONE
    * @post   NONE
    * @returns bool TRUE if equel, FALSE if not
    */
    friend bool samename(const Tree & t1, const Tree & t2);


    /**islessname(const Tree & t1, const Tree & t2); 
    * This method compares the two trees using spc_common, returns true IFF the first Tree object's
    * spc_common member is smaller than that of the second (as a string) (case insensitive)
    * This is a friend function
    * @param  const Tree   t1        [inout]  LHS object to compare
    * @param  const Tree   t2        [inout]  RHS object to compare
    * @pre    NONE
    * @post   NONE
    * @returns bool TRUE if t1 less, FALSE otherwise
    */
    friend bool islessname(const Tree & t1, const Tree & t2);

    /**common_name(); const
    * This returns spc_common of the calling Tree
    * @pre    NONE
    * @post   NONE
    * @returns spc_common
    */
    string common_name() const;


   /**borough_name(); const
    * This returns name of the borough where the Tree is located
    * @pre    NONE
    * @post   NONE
    * @returns boroname
    */
    string borough_name()const;

    /**diameter(); const
    * This returns diameter of the tree
    * @pre    NONE
    * @post   NONE
    * @returns tree_dbh
    */
    double diameter();

private:


    int tree_id; //=non-negative integer that uniquely identifies the tree

    int tree_dbh; //non-negative integer that specifies tree diameter

    string status_tree; //valid values "Alive", "Dead", "Stump", or the empty string, (case insensitive)

    string health_tree; //a string valid values "Good", "Fair", "Poor", or the empty string, (case insensitive)

    string spc_common; //the common name of the tree, possibly empty

    int zipcode;// positive digits 5 or less (add leading zeroes)

    string boroname; // valid values "Manhattan", "Bronx", "Brooklyn", "Queens", "Staten Island" (case insensitive)

    double x_sp; //x coordinate

    double y_sp; //y coordinate
     

};

//Global variable NOT FOUND tree, returned when find function fails to find a Tree object user looked for 
const Tree NOT_FOUND(0,0, "NOT FOUND", "NOT FOUND", "NOT FOUND", 0, "NOT FOUND", 0.0, 0.0);

#endif /* __Tree_H__ */


