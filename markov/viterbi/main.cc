#include <stdio.h>
#include <vector>
#include <string>
#include "Matrix.h"

const char *states[2] = {"health", "fever"};
int num_of_states = 2;

std::vector<int> obs_seq;
double trans_m[4] = {0.7, 0.3, 0.4, 0.6};
Matrix trans(2, 2, trans_m);

double start_m[2] = {0.6, 0.4};
Matrix start_prob(1, 2, start_m);

double emission_m[6] = {0.5, 0.4, 0.1, 0.1, 0.3, 0.6};
Matrix emission(2, 3, emission_m);

std::vector<int> Viterbi(std::vector<int> obs_seq)
{
    std::vector<std::vector<int> > path;
    std::vector<std::vector<double> > V;
    

    return path[0];
}

int main(int argc, char** argv)
{
    printf("HI!\n");
    //trans.print();
    //start_prob.print();
    emission.print();
    return 0;
}
