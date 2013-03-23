#ifndef __HMM_H__
#define __HMM_H__

#include <map>
#include <vector>
#include <string>
#include "Matrix.h"

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

#endif
