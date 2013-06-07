#include <fstream>
#include "HMM.h"
#include "alg_impl.h"

std::vector<int> HMM::Viterbi(std::vector<int> &obs)
{
    return Viterbi_impl(this->num_of_states, *this->trans, *this->emission, *this->start_prob, obs);
}

std::vector<int> HMM::Forward_Backward(std::vector<int> &obs)
{
    Matrix emission_trans = emission->trans();
    Matrix start_prob_trans = start_prob->trans();
    return Forward_Backward_impl(this->num_of_states, *this->trans, emission_trans, start_prob_trans, obs);
}

void HMM::data_from_file(std::string fname, std::vector<int> *res, std::vector<int> *obs)
{    
    std::ifstream in(fname.c_str());
    std::string str;
    in>>str;
    in>>str;
    in>>str;
    while (!in.eof())
    {
        in>>str;
        if(in.eof()) break;
        in>>str;
        res->push_back(this->states[str]);
        in>>str;
        obs->push_back(this->obs_types[str]);
    }
    in.close();
}

