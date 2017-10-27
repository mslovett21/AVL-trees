/*******************************************************************************
  Title          : avl.h
  Author         : Patrycja Krawczuk
  Created on     : March 14th, 2017
  Description    : Header file for AVL_Tree class, describes functionality of the class
  Purpose        :  
  Usage          : 
  Build with     : makefile, (g++ -std=c++11)
  Modifications  : 

*******************************************************************************/
#ifndef __AVL_H__
#define __AVL_H__

#include <string>
#include <iostream>
#include <list>
#include "tree.h"

class AVL_Node;

using namespace std;


class AVL_Tree
{
public:
    //default constructor for the class
    AVL_Tree  ( );   

    /** AVLTree() - copy constructor for the class
     * @param const  AVL_Tree      [inout] tree  
     * @pre     tree is a valid AVL_Tree object
     * @post    a copy of tree is created
     */
    AVL_Tree  ( const AVL_Tree & tree);

    //class destructor
    ~AVL_Tree ( );                       
      
    // SEARCH METHODS:

    /** find() - search method, 
    * This method searches the tree using spc_common as the primary key and tree_id as a secondary key
    * in order to find the x tree object, if not found it returns a special NOT_FOUND tree object by reference
    * @param const   Tree      [inout]  x 
    * @post  NONE
      @returns FOUND object if search was successful or NOT_FOUND tree object otherwise
    */
    const Tree& find    ( const Tree & x ) const; 


     /** findMin() - search method, 
    * This method searches the tree using spc_common as the primary key and tree_id as a secondary key
    * in order to find the left most object in the sorted tree aka the smalles element.
    * if not found it returns a special NOT_FOUND tree object by reference
    * @post  NONE
      @returns the smallest object in the tree or NOT_FOUND tree if the AVL_Tree is empty
    */
    const Tree& findMin () const;

    /** findMax() - search method, 
    * This method searches the tree using spc_common as the primary key and tree_id as a secondary key
    * in order to find the right most object in the sorted tree aka the biggest element.
    * if not found it returns a special NOT_FOUND tree object by reference
    * @post  NONE
      @returns the smallest object in the tree or NOT_FOUND tree if the AVL_Tree is empty
    */
    const Tree& findMax () const;

    /** findallmatches() - search method, 
    * This method searches the tree using spc_common as the key, 
    * It returns a list of trees with common name the same as the common name of parameter x
    * @param const   AVL_Tree      [inout]  x 
    * @post  list of matching Tree objects is returned
      @returns list of Tree objects or empty list of Trees if no matches found
    */
    list<Tree> findallmatches ( const Tree & x ) const;
    
    
    /** print(ostream& write_stream)
    * Prints the Tree object to the screen in the specified format.
    * Format:  208230 13 Alive Fair London planetree 10024 Manhattan 40.78 -73.97 , one per line
    * @param   ostream                [inout]  write_stream
    * @pre    working open stream is provided
    * @post   Tree objects are printed to the screen
    * @returns osream&
    */
    void   print   ( ostream& out ) const;
   

    /**clear();
    * deletes content of the AVL_tree
    * @post AVL_Tree is empty
    */
    void   clear(); 


    /**insert(const Tree & x)-allows adding new objects to the tree 
    * Insert methods first finds a right place for x object in sorted AVL_Tree.
    * This method compares the two trees using spc_common as the primary key and tree_id as a secondary key.
    * If x is a duplicate of another Tree object which exist in AVL_Tree it is not inserted.
    * @param  const Tree   x        [inout]  tree to insert
    * @pre    Tree contains valid data
    * @post   If x is not a duplicate, x is added to the tree
    */
    void   insert( const Tree& x);

    /**remove(const Tree & x)-allows removing objects from the tree 
    * Remove methods first finds the postion where x should be positioned in the tree. Then if object equal to x
    *(spc_common and tree_id) it is removed. If not tree equal to object x is found then no changes.
    * @param  const Tree   x        [inout]  tree to remove
    * @pre    Tree contains valid data
    * @post   If x is found in the tree, it is deleted, otherwise nothing happens
    */
    void   remove( const Tree& x);

    /**insert_successful();
    * provides means of communication between AVL_tree class and TreeCollection class
    *@return if last insertion was successful returns true, otherwise false
    */
    bool insert_successful();

    /**removes_successful();
    * provides means of communication between AVL_tree class and TreeCollection class
    *@return if last deletion was successful return true, otherwise false
    */
    bool remove_successful();

private:

    AVL_Node* tree_root;//root of the AVL tree

    bool insert_success=false;//helper used to check if last insertion was successful

    bool remove_success=false;//helper used to check if last deletion was successful

    int tree_size; //number of nodes in the avl tree 

    /** copy() - a method invoked by copy constructor
     * @param const  AVL_Tree      [inout] tree  
     * @pre     curPtr point to a  valid Avl_Tree to be copied
     * @post    a copy of tree is created, the pointer to the root of new tree is returned
     */

    AVL_Node* copy(AVL_Node* curPtr) const;

    /** find() - search method, 
    * This method searches the tree using spc_common as the primary key and tree_id as a secondary key
    * in order to find the x tree object, if not found it returns a special NOT_FOUND tree object by reference
    * @param const   Tree      [inout] data_to_find 
    * @param const   AVL_Node  [inout] curPtr
    * @post  NONE
      @returns pointer to FOUND object if search was successful or NULL pointer if serach not successful
    */
    const AVL_Node*  find( const Tree& data_to_find, const AVL_Node* curPtr) const;


    /** find_all_matches() - search method, 
    * This method searches the tree using spc_common as the key, 
    * It returns a list of trees with common name the same as the common name of parameter x
    * It does it by modifying my_tree_list passed to it as argument
    * @param const   Tree      [inout]  x                -find matches of that tree
    * @param const AVL_Node    [inout]  curPtr           -pointer to the AVL_Tree
    * @param list<Tree>        [inout]  my_tree_results  -list to put results into
    * @post  maching results are in my_tree_results
    */
    void find_all_matches(const Tree& x, const AVL_Node* curPtr, list<Tree>& my_tree_results) const;

    /** destroy() - destructor for the class
     * @param const  AVL_Node   [inout] curPtr 
     * @pre     curPtr point to the root of the Avltree
     * @post    AVL tree is empty, rroot pointer points to NULL
     */
    void destroy(AVL_Node* & curPtr);

    /** find_relative_min - search method, 
    * This method searches the tree using spc_common as the primary key and tree_id as a secondary key
    * in order to find the left most object in the sorted tree aka the smalles element.
    * the minimum in found on the subtree of the AVL_tree
    * @param AVL_Node   [inout] curPtr
    * @post  NONE
      @returns the pointer to the smallest object in the subtree or NULL pointer if subtree is empty
    */
    AVL_Node* find_relative_min( AVL_Node* curPtr);


    /** find_min - search method, 
    * This method searches the tree using spc_common as the primary key and tree_id as a secondary key
    * in order to find the left most object in the sorted tree aka the smalles element.
    * the minimum in found on the subtree of the AVL_tree
    * @post  NONE
      @returns the pointer to the smallest object in the subtree or NULL pointer if subtree is empty
    */
    const AVL_Node* find_min( const AVL_Node* curPtr) const;


    /** find_max - search method, 
    * This method searches the tree using spc_common as the primary key and tree_id as a secondary key
    * in order to find the left most object in the sorted tree aka the smalles element.
    * the minimum in found on the subtree of the AVL_tree
    * @post  NONE
      @returns the pointer to the biggest object in the subtree or NULL pointer if subtree is empty
    */
    const AVL_Node* find_max(const AVL_Node* curPtr) const;


    /**delete_the_node()-allows removing objects from the tree 
    * Remove methods first finds the postion where x should be positioned in the tree. Then if object equal to x
    *(spc_common and tree_id) it is removed. If not tree equal to object x is found then no changes.
    * @param  const AVL_Node*   curPtr          [inout]  node to the root of the tree
    * @param  const Tree        data_to_delete  [inout]  Tree to find and delete
    * @pre    Tree contains valid data
    * @post   If data_to_delete is found in the tree, it is deleted, otherwise nothing happens
    */
    void delete_the_node(AVL_Node* &curPtr, const Tree& data_to_delete);



    /**insert()-allows adding new objects to the tree 
    * Insert methods first finds a right place for x object in sorted AVL_Tree.
    * This method compares the two trees using spc_common as the primary key and tree_id as a secondary key.
    * If x is a duplicate of another Tree object which exist in AVL_Tree it is not inserted.
    * @param   const AVL_Node*   curPtr          [inout]  node to the root of the tree
    * @param  const Tree        tree_to_insert  [inout]  tree to insert
    * @pre    Tree contains valid data
    * @post   If tree_to_insert is not a duplicate, it is added to the tree
    */
    void insert_the_node(AVL_Node* &curPtr, const Tree& tree_to_insert);

    /** in_order_print()
    * Prints the Tree object to the screen in the specified format.
    * Format:  208230 13 Alive Fair London planetree 10024 Manhattan 40.78 -73.97 , one per line
    * @param   ostream                    [inout]  write_stream
    * @param   const AVL_Node*   curPtr   [inout]  node to the root of the tree
    * @pre    working open stream is provided
    * @post   Tree objects are printed to the screen
    * @returns osream&
    */
    void in_order_print(ostream& output,const AVL_Node* curPtr) const;

    /** height()
    * Returns the height of the node in the tree,is node is NULL its height is -1
    * @param   const AVL_Node*   curPtr   [inout]  node to the root of the tree
    * return int height */
    int height(AVL_Node* curPtr);

    /** max()
    * Evaluates which argument is bigger and return it
    * @param   int  rhs [in]  
    * @param   int  lhs [in]
    * return max of two arguments */
    int max(int lhs, int rhs);

    /** RR_rotation()
    * This is a standart AVL RR_rotation
    * @param   const AVL_Node*   curPtr   [inout]  node to the root of the tree
    * @post rotation was performed, if not enough nodes in the tree-no changes */
    void RR_rotation(AVL_Node* & curPtr);

    /** LL_rotation()
    * This is a standard AVL LL rotation
    * @param   const AVL_Node*   curPtr   [inout]  node to the root of the tree
    * @post rotation was performed, if not enough nodes in the tree-no changes */
    void LL_rotation(AVL_Node* & curPtr);

    /** LR_rotation()
    * This is a standard AVL LR rotation
    * @param   const AVL_Node*   curPtr   [inout]  node to the root of the tree
    * @post rotation was performed, if not enough nodes in the tree-no changes */
    void LR_rotation(AVL_Node* & curPtr);

    /** RL_rotation()
    * This is a standard AVL RL rotation
    * @param   const AVL_Node*   curPtr   [inout]  node to the root of the tree
    * @post rotation was performed, if not enough nodes in the tree-no changes */
    void RL_rotation(AVL_Node* & curPtr);

};

#endif /* __AVL_H__ */

