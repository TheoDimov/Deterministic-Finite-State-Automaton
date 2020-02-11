/**********************************************************************
*
* Programming Project #1: A Deterministic Finite-State Automaton
*
* This is the implementation of a deterministic finite state automaton
* 
* Reads a string as input and traces its progress through the FSA, at the 
* end of which, prints whether or not the FSA accepts the string.
*
* Author: Todor G. Dimov <tdimov@fordham.edu>
* Date: 3 February 2019
*
**********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include "FSA.h"

using namespace std;

// precondition: num_states & sigma vector are initialized
// creates the state table for the FSA based on the initialized 
// private member variales
void FSA :: get_state_table(ifstream &ifs)
{
    // resizing the interior matrices 
  	state_table.resize(num_states, vector<int>(sigma.size())); 

    // line: used to hold string from getline()
	string line;
	int n;

    // loop to fill state_table 
	for(int i = 0; i < num_states; i++){
		getline(ifs, line);		
		stringstream stream(line);
		for(int j = 0; j < sigma.size(); j++){
			stream >> n;	
			state_table[i][j] = n;				
		}
	}
}

// precondition: $ifs is pointing to a data file stream
// initializes private member variables of FSA
FSA :: FSA(ifstream &ifs)
{
	string line;
	for (int i = 0; i < 5; i++)
	{
		if (i == 0){	
			getline(ifs, line);		
			copy(line.begin(),line.end(),back_inserter(sigma));	
		}
		else if (i == 1){
			getline(ifs, line);
			num_states = stoi (line, nullptr, 10);  
		}
		else if (i == 2){
			getline(ifs, line);
			start_state = stoi (line, nullptr,10);
		}
		else if (i == 3){
			getline(ifs, line);		
			stringstream stream(line);
			int n;
			while(stream >> n){
            	accept_states.push_back(n);
            }
        }
		else if  (i == 4){
			get_state_table(ifs);
		}
	}   
}

// precondition: in_string points to a string
// displays the traced states and whether or not
// it was an accepted string
void FSA :: trace(const string& in_string)
{   
    // endstate is the last state which is traced
    int endstate = start_state - 1;
    bool accept_dec = false, correct_input = true;

    // checks string for wrong input
    for (int k = 0; k < in_string.size(); k++){   
        for (int q = 0; q < sigma.size(); q++){
            if (sigma[q] == in_string[k]){
                correct_input = true;
                break;
            }
            else
                correct_input = false;
        }

    }
    if (correct_input == false)
    {
        cout << "Illegal input!\n";
        exit (EXIT_FAILURE);
    }

    // traces the FSA and updates the endstate
    cout << "State trace: " << start_state << " ";    
    for (int k = 0; k < in_string.size(); k++){   
        for (int q = 0; q < sigma.size(); q++){
            if (in_string[k] == sigma[q]){
                cout << state_table[endstate][q] << " ";
                endstate = state_table[endstate][q] - 1;
            }
            else
                continue;
        }
    }
    
    // checks to see if endstate is one of the accepted states 
    // and prompts the result
    for (int i = 1; i <= accept_states[0]; i++){
        if (endstate + 1 == accept_states[i]){
            accept_dec = true;
            break;
        }
    } 
    if (accept_dec == true)
        cout << " ... accepted\n";
    else
        cout << " ... not accepted\n";
}


