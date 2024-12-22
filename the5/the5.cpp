#include "the5.h"



int partition(std::vector<int>& v, int low, int high) {
    int pivot = v[high];
    int i = low - 1;
    int j = low;
    
    while (j < high) {
        if (v[j] < pivot) {
            ++i;
            int temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
        ++j;
    }
    
    int temp = v[i + 1];
    v[i + 1] = v[high];
    v[high] = temp;
    
    return i + 1;
}


void quicksort(std::vector<int>& v, int low, int high) {
    if (low < high) {
        int x = partition(v, low, high);
        quicksort(v, low, x - 1);
        quicksort(v, x + 1, high);
    }
}


void sort_vector(std::vector<int>& v) {
    if (v.empty()) return;
    quicksort(v, 0, v.size() - 1);
}


std::vector<std::vector<int>> construct_result(const std::vector<std::vector<int>>& sccs, const std::vector<int>& order) {
    std::vector<std::vector<int>> result;
    for (int scc_id : order) {
        result.push_back(sccs[scc_id]);
    }
    return result;
}



void tarjan(int node, std::vector<int>& ids, std::vector<int>& low, std::vector<int>& stack, 
            std::vector<bool>& on_stack, std::vector<std::vector<int>>& graph, 
            std::vector<std::vector<int>>& sccs, std::vector<int>& scc_map, int& id) {
    ids[node] = low[node] = id++;
    stack.push_back(node);
    on_stack[node] = true;


    for (int neighbor : graph[node]) {
        if (ids[neighbor] == -1) {
            tarjan(neighbor, ids, low, stack, on_stack, graph, sccs, scc_map, id);
            low[node] = std::min(low[node], low[neighbor]);
        } else if (on_stack[neighbor]) {
            low[node] = std::min(low[node], ids[neighbor]);
        }
    }

  
    if (ids[node] == low[node]) {
        std::vector<int> scc;
        while (true) {
            int current = stack.back();
            stack.pop_back();
            on_stack[current] = false;
            scc.push_back(current);
            scc_map[current] = sccs.size();
            if (current == node) {
                break;
            }
        }
        sort_vector(scc); 
        sccs.push_back(scc);
    }
}


void build_dag(const std::vector<std::vector<int>>& graph, const std::vector<int>& scc_map, 
               std::vector<std::vector<int>>& dag) {
    int n = graph.size();
    
    for (int i = 0; i < n; ++i) {
        for (int neighbor : graph[i]) {
            int scc_from = scc_map[i];
            int scc_to = scc_map[neighbor];
            if (scc_from != scc_to) {
                bool exists = false;
                for (int existing : dag[scc_from]) {
                    if (existing == scc_to) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    dag[scc_from].push_back(scc_to);
                }
            }
        }
    }
}


std::vector<int> topological_sort(const std::vector<std::vector<int>>& dag) {
    std::vector<int> in_degree(dag.size(), 0);
    for (const auto& neighbors : dag) {
        for (int neighbor : neighbors) {
            in_degree[neighbor]++;
        }
    }

    std::vector<int> order;
    std::vector<int> zero_in_degree;
    for (int i = 0; i < in_degree.size(); ++i) {
        if (in_degree[i] == 0) {
            zero_in_degree.push_back(i);
        }
    }

    while (!zero_in_degree.empty()) {
        
        int min_index = 0;
        for (size_t i = 1; i < zero_in_degree.size(); ++i) {
            if (zero_in_degree[i] < zero_in_degree[min_index]) {
                min_index = i;
            }
        }
        int current = zero_in_degree[min_index];
        zero_in_degree.erase(zero_in_degree.begin() + min_index);
        order.push_back(current);

        for (int neighbor : dag[current]) {
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) {
                zero_in_degree.push_back(neighbor);
            }
        }
    }
    
    return order;
}


std::vector<std::vector<int>> find_work_order(const std::vector<std::vector<bool>>& dependencies) {
    int n = dependencies.size();
    std::vector<std::vector<int>> graph(n), sccs;
    std::vector<int> ids(n, -1), low(n, -1), stack;
    std::vector<bool> on_stack(n, false);
    int id = 0;
    std::vector<int> scc_map(n, -1); 

    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dependencies[i][j]) {
                graph[i].push_back(j);
            }
        }
    }

   
    for (int i = 0; i < n; ++i) {
        if (ids[i] == -1) {
            tarjan(i, ids, low, stack, on_stack, graph, sccs, scc_map, id);
        }
    }

  
    std::vector<std::vector<int>> dag(sccs.size());
    build_dag(graph, scc_map, dag);
   
    std::vector<int> order = topological_sort(dag);

    return construct_result(sccs, order);
}
