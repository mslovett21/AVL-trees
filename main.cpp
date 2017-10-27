/*******************************************************************************
  Title          : main.cpp
  Author         : Patrycja Krawczuk
  Created on     : March 14th, 2017
  Description    : Main for the program
  Purpose        :  
  Usage          : 
  Build with     : makefile, (g++ -std=c++11)
  Modifications  : 

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <iomanip>
#include <stdexcept>
using namespace std;


#include "tree_collection.h"
#include "avl.h"

//helper struct
struct TreesInBorough
{
  string name_of_borough;
  int number;

};


/*response_for_the_user()
* This method makes all needed calls to produce the table as specified 
* on page 3 of the assigment after a user provided a name of a tree species.
* The output contains names of species in the collection that matched to the user's input,
* info about how many of these trees are in each borough and how many trees are in each borogh
* in general. 
* @param  string           [in]     input_user
* @param  TreeCollection   [inout]  NYC_collection
* @post The table is printed into screen
EXAMPLE OF OUTPUT PRODUCED BY THE FUNCTION using user input "oak"
All matching species:
black oak
english oak
northern red oak
pin oak
schumard's oak
white oak
willow oak
Popularity in the city:
NYC:            28       (220)  12.73%
Manhattan:      3        (37)   8.11%
Bronx:          1        (19)   5.26%
Brooklyn:       6        (42)   14.29%
Queens:         13       (91)   14.29%
Staten Island:  5        (31) 1 6.13%

*/
void response_for_the_user(const string input_user,TreeCollection& NYC_collection);

/*delete_whitespaces()
* This method removes additional whitespaces (tabs, multiple blanks and so on) between words.
* It separates words of a string with single blank character ASCII (20)
* @param  string     [inout]  line_from_file;
* @returns string in which words are separated by one blank (no other whitesaces)
*/
string delete_whitespace(string line_from_file);

/*format_with_commas()
* The method takes integer and changes it to string adding commas between 
* groupings of three digits in large numbers 
* @param  string     [in]  value;
* @returns int as string with grouping commas
*/
string format_with_commas(int value);


/*validate_the_data()
* The method validates the data as specified in assigment on page 4
* @param  vector<string>   [in]     temp_vector
* @param  Tree             [inout]  tree_to_insert
* @returns true if data is valid, false otherwise
*/
bool validate_the_data(vector<string> temp_vector,Tree& tree_to_insert);

int main(int argc, char* argv[])
{

// Check the number of parameters
  if (argc < 2) 
  {   // Tell the user how to run the program- The program needs 2 arguments: name_of_program, commands_file
        cerr << "Usage (2 arguments): " << argv[0] << " command_file "<<endl;
  return 1;
  }
   
  ifstream data_file (argv[1]);
  //check if command file opens succesfully;
  if (data_file.is_open())
     {  } 
  else
  {
    cerr<<"File 1 "<<argv[1]<<" cannot be opened!"<<endl;
    return 1;
  }
  
  istringstream myiss;
  string temp_line, temp_string;
  vector<string> temp_vector;


  TreeCollection my_nyc_tree_collection;
  
  int invalid=0;
  //getline(data_file, metadata);
  //*********************************************************
  //* READ IN DATA FROM THE FILE                            *
  //*********************************************************
  while(getline(data_file, temp_line))
  {
    size_t found=0;
    size_t start=0;
    string temp;
    vector<size_t> found_quotes; 
    
   // cout<<"I got a new line"<<endl;      
      //I got a line of data, I check if there are double quotes, if double quotes exist I collect their location in a vector (found_quotes) 
      while(found<temp_line.size())
      {
        found=temp_line.find_first_of('"', start);
        if(temp_line[found]=='"')
        found_quotes.push_back(found);
        start=found+1;
      }
  //If number of locations of quotes in my vector is not EVEN then the line is invalid, ERROR
  if(found_quotes.size()%2==0)
  { 
          //If ZERO double quotes were found then parsing is easy
          if (found_quotes.size()!=0)
           // SPECIAL CASE possible multpile double quotes
          {
                int i=0;
              
                while(found_quotes.size()>i)
                {   //Here I am extracting parts of the string between double quotes
                    size_t current=0, replace_it=0;
                    size_t start=found_quotes[i];
                    size_t end=found_quotes[i+1]-start+1;
                    string temp_short=temp_line.substr(start,end);
                    
                    //Once I get the content inside the quotes I look for commas and repalce them with blanks
                    while(replace_it<temp_short.size())
                    { 
                        replace_it=temp_short.find_first_of(',', current);
                        if(temp_short[replace_it]==',')
                        temp_line[found_quotes[i]+replace_it]=' ';

                        current=replace_it+1;
                    }
                    i=i+2;
                }//while 
          }//end of if  
          myiss.str(temp_line);

          while(getline(myiss,temp_string,','))
            temp_vector.push_back(temp_string);

            myiss.clear();

          if (temp_vector.size()>40)
          {
            Tree tree_to_insert;
            bool valid_data=validate_the_data(temp_vector, tree_to_insert);

            //These two statements should run only if I'm 100 % sure that the data is valid
              if(valid_data==true)
              {
                  
                  my_nyc_tree_collection.insert(tree_to_insert);
              }   
              else
              {
               invalid++;
              }
           }//end of size of vector is 41
           else
           {
            invalid++;
            cerr<<"INVALID DATA"<<endl;
           }
        }//end of double quotes checker
          
      

      else
      { 

        invalid++;
      }//line is invalid skip it;
  

      temp_vector.clear();


}//big while loop for file
cout<<"Number of invalid lines in this file is "<<invalid<<endl;

  bool user_wants_to_continue=true;
  string response;

  //*********************************************************
  //*            INTERACTIVE MODE                           *
  //*********************************************************
  //my_nyc_tree_collection.print(cout);
  while(user_wants_to_continue)
  {

    cout<<"Please provide a name of a tree species you want to learn about or type 'quit'"<<endl;
    getline(cin, response);
    string fixed_response=delete_whitespace(response);
    
 

    if(fixed_response=="quit")
    {
      user_wants_to_continue=false;
    }
    else
    {
          response_for_the_user(fixed_response, my_nyc_tree_collection);
    }//end of else
 }//end of while

return 0;
}
         
 



void response_for_the_user(const string input_user, TreeCollection& NYC_collection )
{
  list<string> mylist;
  mylist=NYC_collection.get_matching_species(input_user);
  string tree_borough;
  string place;
  string temp_boro;

   //a helper vector;
  vector<TreesInBorough> FoundBorough;
  TreesInBorough NYC_boro{"NYC",0};
  FoundBorough.push_back(NYC_boro);
  TreesInBorough Manhattan_boro{"Manhattan",0};
  FoundBorough.push_back(Manhattan_boro);
  TreesInBorough Bronx_boro{"Bronx",0};
  FoundBorough.push_back(Bronx_boro);
  TreesInBorough Brooklyn_boro{"Brooklyn",0};
  FoundBorough.push_back(Brooklyn_boro);
  TreesInBorough Queens_boro{"Queens",0};
  FoundBorough.push_back(Queens_boro);
  TreesInBorough StatenIsland_boro{"Staten Island",0};
  FoundBorough.push_back(StatenIsland_boro);
  //I'm checking how many trees of specific kind are in each borough and adding the results
  list<string>::iterator i;
  for( i = mylist.begin(); i != mylist.end(); ++i)
  {
     for(int j=1; j<FoundBorough.size(); j++)
     {
      temp_boro=FoundBorough[j].name_of_borough;
      transform(temp_boro.begin(), temp_boro.end(), temp_boro.begin(), ::tolower);
      FoundBorough[j].number=FoundBorough[j].number+NYC_collection.count_of_trees_of_specific_type_in_boro(*i, temp_boro);
     }
  }
  //Counting how many in NYC over all
  for(int j=1; j<FoundBorough.size(); j++)
     {
      FoundBorough[0].number=FoundBorough[0].number+FoundBorough[j].number;
     }

  cout<<"All matching species:"<<endl;
  for( i = mylist.begin(); i != mylist.end(); ++i)
  {
    cout<<*i<<endl;
  }
  cout<<"Popularity in the city:"<<endl;

  double result;
  int all_in_boro_count;
  for(int i=0; i<FoundBorough.size(); i++)
  {
    temp_boro=FoundBorough[i].name_of_borough;
    transform(temp_boro.begin(), temp_boro.end(), temp_boro.begin(), ::tolower);
    all_in_boro_count=NYC_collection.count_of_trees_in_boro(temp_boro);
    result=(double)FoundBorough[i].number/(double)all_in_boro_count;
    result=result*100;
    
    cout<<setw(14)<<left<<FoundBorough[i].name_of_borough+":"<<"\t"<<left<<setw(7)<<format_with_commas(FoundBorough[i].number)<<"  ";
    cout<<right<<"("<<format_with_commas(all_in_boro_count)<<")"<<"\t";
    cout<<right<<fixed<<setprecision(2)<<result<<"\%"<<endl;
  }



}

string delete_whitespace(string line_from_file)
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

string format_with_commas(int value)
{
    stringstream mystream;
    mystream.imbue(std::locale(""));
    mystream <<fixed << value;
    return mystream.str();
}



bool validate_the_data(vector<string> temp_vector, Tree& tree_to_insert)
{
  string tree_status, tree_health, borough_name;
  int tree_id, tree_diameter, zipcode;
  double x_tree,y_tree;
  bool valid_data=true;
  string temp;
      

//DATA ID: has to be  non-negative integer that uniquely identifies the tree
            try {
              tree_id=stoi(temp_vector[0]);
              if (tree_id<0){
                valid_data=false;
                
              }
            }
            catch(invalid_argument& e){
                 valid_data=false;
                
            }
            catch(...)
            {
              valid_data=false;
            
            }
        //Additional validation since stoi accepts letters
            temp=temp_vector[0];
            for (int i=0; i<temp.size(); i++)
            {
              if (temp[i]>57 ||(temp[i]<48))
                valid_data=false;
            }

//DATA DIAMETER: has to be non-negative
            try {
              tree_diameter=stoi(temp_vector[3]);
              if (tree_diameter<0){
                valid_data=false;
              }
            }
            catch(invalid_argument& e){
                 valid_data=false;
            }
            catch(...)
            {
              valid_data=false;
            }
            //Additional validation since stoi accepts letters
            temp=temp_vector[0];
            for (int i=0; i<temp.size(); i++)
            {
              if (temp[i]>57 ||(temp[i]<48))
                valid_data=false;
            }

//DATA STATUS: The only acceptable values are: "Alive", "Stump", "Dead", "", (case insensitive)
            string tempS=temp_vector[6];

            transform(tempS.begin(), tempS.end(), tempS.begin(), ::tolower);
            if ((tempS=="alive") ||(tempS=="dead") || (tempS=="stump") ||(tempS==""))
            {
              tree_status=temp_vector[6];
            }
            else
            {
              valid_data=false;
            }
            
//DATA HEALTH: The only acceptable values are: "Good", "Fair", "Poor", "", (case insensitive)
            string tempH=temp_vector[7];
            transform(tempH.begin(), tempH.end(), tempH.begin(), ::tolower);
            if ((tempH=="good") ||(tempH=="fair") || (tempH=="poor") ||(tempH==""))
            {
              tree_health=temp_vector[7];
            }
            else
            {
              valid_data=false;
            }

//DATA COMMON NAME  :

            string tree_spc_common=temp_vector[9];

//DATA ZIPCODE:// max 5 digits positive
            try {
              zipcode=stoi(temp_vector[25]);
              if ((zipcode<0) || (zipcode>99999)){
                valid_data=false;
              }
            }
            catch(invalid_argument& e){
                 valid_data=false;
            }
            catch(...)
            {
              valid_data=false;
            }
            //Additional validation since stoi accepts letters
            temp=temp_vector[25];
            for (int i=0; i<temp.size(); i++)
            {
              if ((temp[i]>57) ||(temp[i]<48))
              {
                valid_data=false;
              }
                
            }
            
//DATA BOROUGH: The only acceptable values are: "manhattan", "bronx", "brooklyn", "queens",
//"staten island" (case insensitive)

            string tempB=temp_vector[29];
            transform(tempB.begin(), tempB.end(), tempB.begin(), ::tolower);
            if ((tempB=="manhattan") ||(tempB=="bronx") || (tempB=="brooklyn") ||(tempB=="queens")
              || (tempB=="staten island"))
            {
              borough_name=temp_vector[29];
            }
            else
            {
              valid_data=false;
            }


//PLANE x coordinate
            try {
              
               x_tree=stod(temp_vector[39]);  
            }
            catch(invalid_argument& e){
                 valid_data=false;
            }
            catch(...)
            {
              valid_data=false;
            }
          //Additional validation since stoi accepts letters
            temp= delete_whitespace(temp_vector[39]);
            for (int i=0; i<temp.size(); i++)
            {
              if ((temp[i]>57) ||(temp[i]<48))
                {
                  if((temp[i]==46) || (temp[i]==43) || (temp[i]==65))
                    ;
                  else{
                  valid_data=false;
                }
               }
            }
//PLANE y coordinate
            try {
                
                y_tree=stod(temp_vector[40]);

               }
            catch(invalid_argument& e){
                 valid_data=false;
            }
            catch(...)
            {
              valid_data=false;
            }
          //Additional validation since stoi accepts letters we allow 1.47868e+06
          temp=delete_whitespace(temp_vector[40]);
          for (int i=0; i<temp.size(); i++)
            {
              if ((temp[i]>57) ||(temp[i]<48))
                {
                  if((temp[i]==46) || (temp[i]==43) || (temp[i]==65))
                    ;
                  else{
                  valid_data=false;
                }
               }
            }


            if(valid_data==true)
            {
              Tree temp(tree_id,tree_diameter,tree_status,tree_health,tree_spc_common,zipcode,borough_name,x_tree,y_tree);
              tree_to_insert=temp;
            }
            else
            {
              cerr<<"INVALID DATA"<<endl;
            }

            return valid_data;

}