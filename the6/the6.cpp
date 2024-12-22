#include "the6.h"



const float INF = std::numeric_limits<float>::infinity();

void initialize_distance_matrix(std::vector<std::vector<float>>& dist, const std::vector<std::vector<std::pair<int, int>>>& network) {
    int n = network.size();
    int i = 0;
    while (i < n) {
        int j = 0;
        while (j < network[i].size()) {
            int neighbor = network[i][j].first;
            int weight = network[i][j].second;
            dist[i][neighbor] = weight;
            ++j;
        }
        dist[i][i] = INF;
        ++i;
    }
}




void floyd_warshall(std::vector<std::vector<float>>& dist) {
    int n = dist.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}




void compute_outgoing_shortest_paths(std::vector<float>& SP1, const std::vector<std::vector<float>>& dist) {
    int n = dist.size();
    int i = 0;
    while (i < n) {
        int j = 0;
        while (j < n) {
            if (i != j) {
                float current_distance = dist[i][j];
                if (current_distance < INF) {
                    if (SP1[i] == INF || current_distance < SP1[i]) {
                        SP1[i] = current_distance;
                    }
                }
            }
            ++j;
        }
        
        if (SP1[i] == INF) {
            SP1[i] = -1;
        }
        ++i;
    }
}





void compute_friendship_scores(std::vector<std::vector<float>>& scores, const std::vector<std::vector<float>>& dist, const std::vector<float>& SP1) {
    int n = dist.size();
    int i = 0;
    while (i < n) {
        int j = 0;
        while (j <= i) {
            bool both_inf = (dist[i][j] == INF && dist[j][i] == INF);
            bool one_inf = (dist[i][j] == INF || dist[j][i] == INF);
            
            if (both_inf) {
                scores[i][j] = -1;
            } else {
                bool both_valid_SP1 = (SP1[i] != -1 && SP1[j] != -1);
                if (one_inf) {
                    scores[i][j] = 0;
                } else {
                    if (!both_valid_SP1) {
                        scores[i][j] = 0;
                    } else {
                        float SP2_ij = dist[i][j];
                        float SP2_ji = dist[j][i];
                        scores[i][j] = (SP1[i] / SP2_ij) * (SP1[j] / SP2_ji);
                    }
                }
            }

            if (i != j) {
                scores[j][i] = scores[i][j];
            }
            ++j;
        }
        ++i;
    }
}




std::vector<std::vector<float>> get_friendship_scores(const std::vector<std::vector<std::pair<int, int>>>& network) {
    int n = network.size();
    std::vector<std::vector<float>> dist(n, std::vector<float>(n, INF));
    initialize_distance_matrix(dist, network);
    
    floyd_warshall(dist);

    std::vector<float> SP1(n, INF);
    compute_outgoing_shortest_paths(SP1, dist);

    std::vector<std::vector<float>> scores(n, std::vector<float>(n, -1));
    compute_friendship_scores(scores, dist, SP1);

    return scores;
}