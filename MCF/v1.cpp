#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int to,cap,rev,cost;
};

class MinCostFlow{
public:
    vector<vector<Edge>> G;
    vector<bool> used;
    vector<int> dist;
    vector<int> prev;

    void init(int N){
        G.resize(N);
        used.resize(N,0);
        dist.resize(N,1e9);
        prev.resize(N,-1);
    }

    void add_edge(int from, int to, int cap, int cost){
        int rev_from = G[to].size();
        int rev_to = G[from].size();
        G[from].push_back({to,cap,rev_to,cost});
        G[to].push_back({from,0,rev_from,-cost});
    }

    void bellman_ford(int s, int t){
        dist[s] = 0;
        for (int i = 0; i < G.size(); i++){
            for (int j = 0; j < G.size(); j++){
                for (auto&& e : G[j]){
                    if (e.cap > 0 && dist[j] + e.cost < dist[e.to]){
                        cerr << "dist[" << j << "] = " << dist[j] << ", dist[" << e.to << "] = " << dist[e.to] << ", e.cost = " << e.cost << "\n";
                        dist[e.to] = dist[j] + e.cost;
                        prev[e.to] = j;
                    }
                }
            }
        }
    }

    int flow(int s, int t){
        int flow = 0;
        int cost = 0;
        while(1){
            fill(used.begin(),used.end(),0);
            bellman_ford(s,t);
            int f = 1e9;
            for (int i = t; i != s; i = prev[i]){
                for (auto&& e : G[prev[i]]){
                    if (e.to == i){
                        f = min(f,e.cap);
                    }
                }
            }
            cerr << "f = " << f << "\n";
            if (f == 0) break;
            flow += f;
            cost += f * dist[t];
        }
        return flow;
    }
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector A(N,vector<int>(N));
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            cin >> A[i][j];
        }
    }

    MinCostFlow Z;
    Z.init(N*2+2);
    for (int i = 0; i < N; ++i){
        Z.add_edge(0,i+1,1,0);
        Z.add_edge(i+N+1,N*2+1,1,0);
    }

    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            Z.add_edge(i+1,N+1+A[i][j],1,j+1);
        }
    }

    int f = Z.flow(0,N*2+1);
    cout << f << "\n";
    for (int i = 0; i < N; ++i){
        cout << "(" << i+1 << "," << Z.prev[N+i+1] + 1 << ")\n";
    }
    return 0;
}
