#include <stdio.h>
#include <vector>
#include <string>
#include "Matrix.h"
#include <fstream>
#include <map>
#include <algorithm>

std::map<std::string, int> states;
std::map<std::string, int> obs_types;
int num_of_states = 2;

std::vector<int> obs_seq;
double trans_m[4] = {0.969, 0.029, 0.063, 0.935};
Matrix trans(2, 2, trans_m);

double start_m[2] = {0.526, 0.474};
Matrix start_prob(1, 2, start_m);

double emission_m[6] = {0.005, 0.775, 0.220, 0.604, 0.277, 0.119};
Matrix emission(2, 3, emission_m);

std::vector<int> Viterbi(std::vector<int> obs_seq)
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

void Stat_Test(std::vector<int> obs, std::vector<int> res, std::vector<int> ans, const int state_for_detect)
{
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
    double F_score = (double)tp/(tp+fn+fp);
    printf("True positive: %d\nTrue negative: %d\nFalse positive: %d\nFalse negative: %d\nF-score: %f \n", tp, tn, fp, fn, F_score);
}

Matrix make_obs(int obs, Matrix emission)
{
    Matrix res(num_of_states, num_of_states);
    for(int i = 0; i < num_of_states; i++)
    {
        res.set_element(i, i, emission.get_element(obs, i));
    }
    return res;
}

std::vector<int> Forward_Backward(Matrix trans, Matrix emission, Matrix start_prob, std::vector<int> obs_seq)
{
    std::vector<Matrix> obs;
    for (int i = 0; i < obs_seq.size(); i++) obs.push_back(make_obs(obs_seq[i], emission));
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

int main(int argc, char** argv)
{
    states["St1"] = 0;
    states["St2"] = 1;
    obs_types["a"] = 0;
    obs_types["b"] = 1;
    obs_types["c"] = 2;

    std::vector<int> obs;
    std::vector<int> res;
    std::ifstream in("hmmdata");
    std::string str;
    in>>str;
    in>>str;
    in>>str;
    while (!in.eof())
    {
        in>>str;
        if(in.eof()) break;
        in>>str;
        res.push_back(states[str]);
        in>>str;
        obs.push_back(obs_types[str]);
    }
    in.close();
    std::vector<int> ans = Viterbi(obs);
    Stat_Test(obs, res, ans, 0);
    ans = Forward_Backward(trans, emission.trans(), start_prob.trans(), obs);
    Stat_Test(obs, res, ans, 0);
    return 0;
}
