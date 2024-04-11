#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> par;
    vector<int> siz;

    void init(int h, int w){
        par.resize(h*w,-1);
        siz.resize(h*w,1);
    }

    int root(int x){
        if (par[x] == -1) return x;
        return par[x] = root(par[x]);
    }

    bool same(int r, int h){
        return root(r) == root(h);
    }

    void unite(int u, int v){
        int ru = root(u), rv = root(v);
        if (ru == rv) return;
        if (ru < rv) swap(ru,rv);
        par[rv] = ru;
        siz[ru] += siz[rv];
    }
};

void rand_dirc(int& x, int& y){
    int dirc[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    int r = rand()%4;
    x = dirc[r][0];
    y = dirc[r][1];
}

int rand_choose(unordered_set<int>& S, mt19937& mt){
    auto iter = S.begin();
    advance(iter, mt()%S.size());
    int x = *iter;
    return x;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    random_device rd;
    mt19937 mt(rd());

    int H, W;
    cin >> H >> W;
    UnionFind UF;

    if (H < 5) H = 5;
    if (W < 5) W = 5;

    if (H % 2 == 0) ++H;
    if (W % 2 == 0) ++W;

    cerr << H << " " << W << "\n";
    UF.init(H,W);

    unordered_set<int> Start;
    //壁伸ばし法によるH*Wの迷路の生成。
    for (int i = 0; i < H; ++i){
        for (int j = 0; j < W; ++j){
            if (i == 0 || j == 0 || i == H-1 || j == W-1){
                UF.unite(i*W+j, 0);
            }
            else if (!(i % 2) && !(j % 2)){
                Start.insert(i*W+j);
            }
        }
    }

    auto Extend = [&](int cnt) -> void {
        int s = rand_choose(Start, mt);
        int x = s%W; int dx;
        int y = s/W; int dy;
        bool stop = 0;
        for (int i = 0; i < cnt; ++i){
            while(1){
                rand_dirc(dx,dy);
                int nx = x+dx*2; int ny = y+dy*2;
                if (nx < 0 || nx >= W || ny < 0 || ny >= H) continue;
                if (UF.same(x*W+y, nx*W+ny)) break;
                if (UF.siz[UF.root(nx*W+ny)] > 1) stop = 1;
                UF.unite(x*W+y, (dx+x)*W+(dy+y));
                UF.unite(x*W+y, nx*W+ny);
                x = nx;
                y = ny;
                if (Start.count(s)) Start.erase(s);
                if (Start.count(x*W+y)) Start.erase(x*W+y);
                break;
            }
            if (stop) break;
        }
    };

    while (Start.size()){
        Extend(10);
    }

    for (int i = 0; i < H; ++i){
        for (int j = 0; j < W; ++j){
            if (UF.siz[UF.root(i*W+j)] > 1) cout << "# ";
            else cout << "  ";
        }
        cout << "\n";
    }
    return 0;
}
