#ifndef __ALG_IMPL_H__
#define __ALG_IMPL_H__
#include <vector>
#include "Matrix.h"

std::vector<int> Viterbi_impl(long num_of_states, Matrix &trans, Matrix &emission, Matrix &start_prob, std::vector<int> &obs_seq);
std::vector<int> Forward_Backward_impl(long num_of_states, Matrix &trans, Matrix& emission, Matrix &start_prob, std::vector<int> &obs_seq);

#endif
