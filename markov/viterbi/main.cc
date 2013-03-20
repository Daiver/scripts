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

//std::vector<int>
void Viterbi(std::vector<int> obs_seq)
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
                printf("++++++%f \n", tmp);
                if (tmp > max_value) {max_value = tmp;st = old_state;}
            }
            printf("======%d %f\n", st, max_value);
            tmp_V[j_state] = max_value;
            //tmp_path = path[j_state];
            path[j_state].push_back(st);
            //tmp_path.push_back(st);
            //new_path.push_back(tmp_path);
        }
        //path = new_path;
        V.push_back(tmp_V);
    }
    
    for(int j = 0; j < V.size(); j++)
    {
        for(int i = 0; i < V[j].size(); i++)
        {
            printf("%f ", V[j][i]);
        }
        printf("\n");
    }
    //return path[0];
    for(int j = 0; j < path.size(); j++)
    {
        for(int i = 0; i < path[j].size(); i++)
        {
            printf("%d ", path[j][i]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    printf("HI!\n");
    obs_seq.push_back(0);
    obs_seq.push_back(1);
    obs_seq.push_back(2);
    //obs_seq.push_back(2);
    //emission.print();
    //printf("%f\n", emission.get_element(0, 1));
    Viterbi(obs_seq);
    //trans.print();
    //start_prob.print();
    return 0;
}
