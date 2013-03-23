#include "alg_impl.h"

std::vector<int> Viterbi_impl(long num_of_states, Matrix &trans, Matrix &emission, Matrix &start_prob, std::vector<int> &obs_seq)
{
    std::vector<std::vector<int> > path;
    std::vector<std::vector<double> > V;
    std::vector<double> tmp_V;
    for(int i = 0; i < num_of_states; i++)
    {
        std::vector<int> tmp_path;
        tmp_V.push_back(emission.get_element(i, obs_seq[0]) * start_prob.get_element(0, i));
        tmp_path.push_back(i);
        path.push_back(tmp_path);
    }
    V.push_back(tmp_V);

    for(int i_obs = 1; i_obs < obs_seq.size(); i_obs++)
    {
        std::vector<std::vector<int> > new_path;
        for(int j_state = 0; j_state < num_of_states; j_state++)
        {
            std::vector<int> tmp_path;
            double max_value = 0.0;
            int st = -1;
            for(int old_state = 0; old_state < num_of_states; old_state++)
            {
                double tmp = emission.get_element(j_state, obs_seq[i_obs]) * V[i_obs - 1][old_state] * trans.get_element(old_state, j_state);
                if (tmp > max_value) {max_value = tmp;st = old_state;}
            }
            tmp_V[j_state] = max_value;
            tmp_path = path[st];            
            tmp_path.push_back(j_state);
            new_path.push_back(tmp_path);
        }
        path = new_path;
        V.push_back(tmp_V);
    }
    double max = 0.0;
    int max_state = -1;
    for(int i = 0; i < num_of_states; i++)
    {
        if(V[V.size() - 1][i] > max) {max = V[V.size() - 1][i]; max_state = i;}
    }
    return path[max_state];
}


Matrix make_obs_for_forward_backward(int obs, long num_of_states, Matrix &emission)
{
    Matrix res(num_of_states, num_of_states);
    for(int i = 0; i < num_of_states; i++)
    {
        res.set_element(i, i, emission.get_element(obs, i));
    }
    return res;
}

//Алгоритм вперед-назад. Использует несколько иначе сформированные матрицы, нежели Витерби
std::vector<int> Forward_Backward_impl(long num_of_states, Matrix &trans, Matrix& emission, Matrix &start_prob, std::vector<int> &obs_seq)
{
    std::vector<Matrix> obs;
    for (int i = 0; i < obs_seq.size(); i++) obs.push_back(make_obs_for_forward_backward(obs_seq[i], num_of_states, emission));
    Matrix trans_trans = trans.trans();
    std::vector<Matrix> F;
    F.push_back(start_prob);
    for(int i = 0; i < obs.size(); i++)
    {
        F.push_back(
            obs[i].dot(&trans_trans).dot(&F[F.size() - 1]).normalize()
        );
    }
    Matrix b_start(num_of_states, 1);
    for(int i = 0; i < num_of_states; i++) b_start.set_element(i, 0, 1.0);
    std::vector<Matrix> B;
    B.push_back(b_start);
    for(int i = obs.size() - 1; i >= 0; i--)
    {
        B.push_back(
            trans.dot(&obs[i]).dot(&B[B.size() - 1]).normalize()
        );
    }
    std::vector<Matrix> gamma;
    for (int i = 0; i < F.size(); i++)
    {
        gamma.push_back(
            F[i].mul(&B[B.size() - i - 1]).normalize()
        );
    }
    std::vector<int> res;
    for(int i = 1; i < gamma.size(); i++) res.push_back(gamma[i].max_value_index());
    return res;
}


