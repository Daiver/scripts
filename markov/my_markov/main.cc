#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <map>

#include "Matrix.h"
#include "alg_impl.h"

void Stat_Test(std::vector<int> &obs, std::vector<int> &res, std::vector<int> &ans, const int state_for_detect, std::string alg_name)//Вычисляет А-меру, и т.д
{
    printf("Alg: %s\n", alg_name.c_str());
    int fp = 0, tp = 0, tn = 0, fn = 0;
    printf("set length %ld\n", res.size());
    for(int i = 0; i < ans.size(); i++)
    {
        if(res[i] == state_for_detect)
        {
            if (ans[i] == state_for_detect) tp++;
            else fn++;
        }
        else
        {
            if (ans[i] != state_for_detect) tn++;
            else fp++;
        }
    }
    double F_score = (double)(2.* tp)/(2.*tp+fn+fp);
    printf("True positive: %d\nTrue negative: %d\nFalse positive: %d\nFalse negative: %d\nF-score: %f \n\n", tp, tn, fp, fn, F_score);
}

class HMM
{
public:
    HMM()
    {
        double trans_m[4] = {0.969, 0.029, 0.063, 0.935};
        this->trans = new Matrix(2, 2, trans_m);

        double start_m[2] = {0.526, 0.474};
        this->start_prob = new Matrix(1, 2, start_m);

        double emission_m[6] = {0.005, 0.775, 0.220, 0.604, 0.277, 0.119};
        this->emission = new Matrix(2, 3, emission_m);

        states["St1"] = 0;
        states["St2"] = 1;
        this->num_of_states = 2;
        obs_types["a"] = 0;
        obs_types["b"] = 1;
        obs_types["c"] = 2;
    }

    ~HMM()
    {
        delete this->emission;
        delete this->trans;
        delete this->start_prob;
    }

    void data_from_file(std::string fname, std::vector<int> *res, std::vector<int> *obs);
    std::vector<int> Viterbi(std::vector<int> &obs);
    std::vector<int> Forward_Backward(std::vector<int> &obs);

private:
    int num_of_states;
    Matrix *emission;
    Matrix *trans;
    Matrix *start_prob;
    std::map<std::string, int> states;
    std::map<std::string, int> obs_types;
};

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

int main(int argc, char** argv)
{
    HMM hmm;
    std::vector<int> obs;
    std::vector<int> res;
    hmm.data_from_file("hmmdata", &res, &obs);
    std::vector<int> ans = hmm.Viterbi(obs);
    Stat_Test(obs, res, ans, 0, "Viterbi");
    ans = hmm.Forward_Backward(obs);
    Stat_Test(obs, res, ans, 0, "Forward-Backward");
    return 0;
}
