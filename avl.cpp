/*******************************************************************************
  Title          : avl.cpp
  Author         : Patrycja Krawczuk
  Created on     : March 14th, 2017
  Description    : methods for AVL_Tree class
  Purpose        :  
  Usage          : 
  Build with     : makefile, (g++ -std=c++11)
  Modifications  : 

*******************************************************************************/
#include <string>
#include <iostream>
#include <list>
#include "avl.h"

using namespace std;


class AVL_Node
{
private:
	
	/**AVL_Node() - Default Constructor **/
	AVL_Node(): tree_data(0,0, "", "", "", 0, "", 0.0,0.0), left(NULL), right(NULL), height(-1){};
	~AVL_Node() {};

	AVL_Node( const Tree& tree_object, AVL_Node* left_tree=NULL,
											   AVL_Node* right_tree=NULL,
											   int new_height=-1 ):
											   tree_data(tree_object),
											   left(left_tree),
											   right(right_tree),
											   height(new_height) {};


    
	Tree tree_data;

	AVL_Node* left=NULL;

	AVL_Node* right=NULL;

	int height=-1;

	friend class AVL_Tree;
};


AVL_Tree::AVL_Tree( )
{
   tree_root=NULL;
   tree_size=0;

}


AVL_Tree::AVL_Tree( const AVL_Tree & tree)
{
    tree_root=copy(tree.tree_root);
} 
   
AVL_Tree::~AVL_Tree( )
{
	destroy(tree_root);
}                       // destructor
      
 
AVL_Node* AVL_Tree::copy(AVL_Node* curPtr) const
{
	if (curPtr==NULL)
	{
		return NULL;
	}
	else
	{
		return new AVL_Node(curPtr->tree_data, copy(curPtr->left), copy(curPtr->right));
	}
}
const Tree& AVL_Tree::find( const Tree & x ) const
{
	const AVL_Node* resultPtr;
    resultPtr=find(x,this->tree_root);

    if (resultPtr != NULL)
    {
    	return resultPtr->tree_data;
    }
    else
    {

    	return NOT_FOUND;
    }
     
}  

const Tree& AVL_Tree::findMin() const
{
    const AVL_Node* resultPtr;
    resultPtr=find_min(this->tree_root);

        if (resultPtr != NULL)
    {
    	return resultPtr->tree_data;
    }
    else
    {

    	return NOT_FOUND;
    }
}

const Tree& AVL_Tree::findMax() const
{
	const AVL_Node* resultPtr;
    resultPtr=find_max(this->tree_root);

        if (resultPtr != NULL)
    {
    	return resultPtr->tree_data;
    }
    else
    {

    	return NOT_FOUND;
    }

}
    
list<Tree> AVL_Tree::findallmatches( const Tree & x ) const
{
    list<Tree> my_tree_results;
    find_all_matches(x, tree_root, my_tree_results);
	return my_tree_results;
}


void AVL_Tree::find_all_matches(const Tree& x, const AVL_Node* curPtr, list<Tree>& my_tree_results) const
{
 

	if (curPtr == NULL)
	{
		return;
	}
	else{
		
		if(islessname(x, curPtr->tree_data))
		{ 
			find_all_matches(x, curPtr->left, my_tree_results);
		}
		else if(islessname(curPtr->tree_data, x))
		{

			find_all_matches(x, curPtr->right, my_tree_results);
		}
		else if(samename(x, curPtr->tree_data))
		{
			

			my_tree_results.push_back(curPtr->tree_data);
			if (curPtr->left !=NULL)
			{
				find_all_matches(x, curPtr->left, my_tree_results);
			}
			if(curPtr->right != NULL)
			{
				find_all_matches(x, curPtr->right, my_tree_results);
			}

		}
	
	}

}





    

void AVL_Tree::print( ostream& out ) const// the function can be understood as if:  print(ostream& out, const AVL_Tree* this)
{
	in_order_print(out, this->tree_root);
}



void AVL_Tree::in_order_print(ostream& output,const AVL_Node* curPtr) const
{
	if(curPtr != NULL)
	{
		in_order_print(output, curPtr->left);
		output<<curPtr->tree_data;// a tree
		output<<curPtr->height<<endl;
		in_order_print(output, curPtr->right);
	}
} 

bool AVL_Tree::insert_successful()
{
	if (insert_success==true)
		return true;
	else
		return false;
}

bool AVL_Tree::remove_successful()
{
	if (remove_success==true)
		return true;
	else
		return false;
}

void AVL_Tree::clear()
{
	destroy(tree_root);
}
    
void AVL_Tree::insert( const Tree& x)
{
	insert_the_node(tree_root, x);
}
    
void AVL_Tree::remove( const Tree& x)
{

	delete_the_node(tree_root, x);
}


int AVL_Tree::max(int lhs, int rhs)
{
	if(lhs<rhs)
		return rhs;
	else
		return lhs;
}




const AVL_Node*  AVL_Tree::find( const Tree& data_to_find, const AVL_Node* curPtr) const
{
	if(curPtr==NULL)
 	{
 		return curPtr;
 	}

 	else if(data_to_find < curPtr->tree_data)
 	{
 		find(data_to_find, curPtr->left);
 	}
 	else if(curPtr->tree_data < data_to_find)
 	{
 		find(data_to_find, curPtr->right);
 	}
 	else //found
 	{
 		return curPtr;
 	}


}


void AVL_Tree::destroy(AVL_Node* & curPtr)
{
	    if(curPtr !=NULL)
    {
    	destroy(curPtr->left);
    	destroy(curPtr->right);
    	delete curPtr;
    	curPtr=NULL;

    }
}


void AVL_Tree::insert_the_node(AVL_Node* &curPtr, const Tree& data_to_insert)
 {
 	insert_success=false;
 	if(curPtr==NULL)
 	{
 		 curPtr= new(AVL_Node);  //first you need to allocate memeory for your AVL_node object
 		 curPtr->tree_data=data_to_insert;
 		 insert_success=true;
 	}
     //the operator < returns true if LHS is less than RHS
 	else if( data_to_insert < curPtr->tree_data)
 	{
 		insert_the_node(curPtr->left, data_to_insert);

 		if(height(curPtr->left)-height(curPtr->right)==2)
 		{
 			if(data_to_insert < (curPtr->left)->tree_data)
 				LL_rotation(curPtr);
 			else
 				LR_rotation(curPtr);
 		}
 	}

 	//the operato< returns true if LHS is greater than RHS
 	else if( curPtr->tree_data < data_to_insert )
 	{
 		insert_the_node(curPtr->right, data_to_insert);

 		if(height(curPtr->right)-height(curPtr->left)==2)
 		{
 			if((curPtr->right)->tree_data < data_to_insert)
 				RR_rotation(curPtr);
 			else
 				RL_rotation(curPtr);
 		}
 	} 
 	else if ( curPtr->tree_data == data_to_insert)
 		{  //cout<<"I claim this is a duplicate"<<endl;
 	       
 	    }
 	else
 		{
 			//cout<<"Consider a duplicate by mistake"<<endl;
 		

 		}
 	curPtr->height=max(height(curPtr->left), height(curPtr->right))+1;


 }

 void AVL_Tree::delete_the_node(AVL_Node* &curPtr, const Tree& data_to_delete)
{
	remove_success=false;

	if(curPtr==NULL)
		return;
	else if( data_to_delete < curPtr->tree_data)
	{
		delete_the_node(curPtr->left, data_to_delete);

		//check the heights
		if(height(curPtr->right)-height(curPtr->left)==2)
 		{
 			if(height((curPtr->right)->right) >= height((curPtr->right)->left))
 				RR_rotation(curPtr);
 			else
 				RL_rotation(curPtr);
 		}

	}
	else if( curPtr->tree_data < data_to_delete)
 	{
 		delete_the_node(curPtr->right, data_to_delete);

 		if(height(curPtr->left)-height(curPtr->right)==2)
 		{
 			if(height((curPtr->left)->left) >= height((curPtr->left)->right))
 				LL_rotation(curPtr);
 			else
 				LR_rotation(curPtr);
 		}
 	}
 	else
 	{
 	  if((curPtr->left!=NULL) && (curPtr->right!=NULL))
 	  {	

 	  	curPtr->tree_data= (find_relative_min(curPtr->right)->tree_data);
	 	delete_the_node(curPtr->right, curPtr->tree_data );
 	  
 		if(height(curPtr->left)-height(curPtr->right)==2)
 		{
 			if(height((curPtr->left)->left) >= height((curPtr->left)->right))
 				LL_rotation(curPtr);
 			else
 				LR_rotation(curPtr);
 		}
 	  }
 	  else
 	  {
 	  	
 	  	AVL_Node* old_node= curPtr;
 	  	curPtr=(curPtr->left !=NULL) ? curPtr->left : curPtr->right;
 	  	delete old_node;
 	  	remove_success=true;
 	  }
 	}

 	if(curPtr != NULL)
 	{
 		curPtr->height= max(height(curPtr->left), height(curPtr->right)) +1;
 	}


}  



AVL_Node* AVL_Tree::find_relative_min(AVL_Node* curPtr)
{
		if(curPtr==NULL)
	{
		return NULL;
	}

	if(curPtr->left==NULL)
	{
		return curPtr;
	}
	return find_relative_min(curPtr->left);
}


const AVL_Node* AVL_Tree::find_min(const AVL_Node* curPtr) const
{
		if(curPtr==NULL)
	{
		return NULL;
	}

	if(curPtr->left==NULL)
	{
		return curPtr;
	}
	return find_min(curPtr->left);
}


const AVL_Node* AVL_Tree::find_max(const AVL_Node* curPtr) const
{
		if(curPtr==NULL)
	{
		return NULL;
	}

	if(curPtr->left==NULL)
	{
		return curPtr;
	}
	return find_max(curPtr->right);
}


int AVL_Tree::height(AVL_Node* curPtr)
{
	return curPtr == NULL ? -1 : curPtr->height; 
}


void AVL_Tree::LL_rotation(AVL_Node* & curPtr)
{
	AVL_Node* temp= curPtr->left;
	curPtr->left=temp->right;
	temp->right=curPtr;

	curPtr->height=max(height(curPtr->left), height(curPtr->right))+1;
	temp->height=max(height(temp->left), curPtr->height)+1;
	curPtr=temp;
	temp=NULL;

}


void AVL_Tree::RR_rotation(AVL_Node* & curPtr)
{
	AVL_Node* temp= curPtr->right;
	curPtr->right=temp->left;
	temp->left=curPtr;

	curPtr->height=max(height(curPtr->left), height(curPtr->right))+1;
	temp->height=max(height(temp->right), curPtr->height)+1;
	curPtr=temp;
	temp=NULL;
}


void AVL_Tree::LR_rotation(AVL_Node* & curPtr)
{
	RR_rotation(curPtr->left);
	LL_rotation(curPtr);
}


void AVL_Tree::RL_rotation(AVL_Node* & curPtr)
{
	LL_rotation(curPtr->right);
	RR_rotation(curPtr);
}



