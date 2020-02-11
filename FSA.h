/* A Deterministic Finite-State Automaton
 *
 * Header file for FSA class
 *
 * Author: A. G. Werschulz
 * Date:   17 Jan 2019
 */

#pragma once

#include <fstream>
#include <string>
#include <vector>

class FSA 
{
    public:
        FSA(std::ifstream &ifs);
        FSA() = delete;                      // disallow 0-param ctor
        void trace(const std::string& in_string);
    private:
        std::vector<char> sigma;             // alphabet
        int num_states;                      // number of states
        int start_state;
        std::vector<int> accept_states;
        std::vector<std::vector<int>> state_table;

        template <typename T> int find(const std::vector<T> v, const T x);
        void get_state_table(std::ifstream &ifs);
};
