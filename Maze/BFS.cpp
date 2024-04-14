#include <bits/stdc++.h>
using namespace std;

void rotate(int& dx, int& dy){
    swap(dx, dy);
    dx *= -1;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    int H, W;
    cin >> H >> W;
    vector<string> maze(H);
    for (int i = 0; i < H; ++i) cin >> maze[i];

    vector<vector<int>> dist(H, vector<int>(W, -1));
    queue<pair<int, int>> que;
    que.push({1,1});
    dist[1][1] = 0;

    while(!que.empty()){
        int dx = 0, dy = -1;
        auto [nx, ny] = que.front();
        que.pop();
        for (int i = 0; i < 4; ++i){
            rotate(dx,dy);
            if (nx+dx < 0 || nx+dx >= H || ny+dy < 0 || ny+dy >= W) continue;
            if (maze[nx+dx][ny+dy] == '#') continue;
            if (dist[nx+dx][ny+dy] != -1) continue;
            dist[nx+dx][ny+dy] = dist[nx][ny]+1;
            que.push({nx+dx, ny+dy});
        }
        if (dist[H-2][W-2] != -1) break;
    }

    int tx = H-2, ty = W-2;
    while (1) {
        int dx = 0, dy = -1;
        for (int i = 0; i < 4; ++i){
            rotate(dx, dy);
            if (tx+dx < 0 || tx+dx >= H || ty+dy < 0 || ty+dy >= W) continue;
            if (maze[tx+dx][ty+dy] == '#') continue;
            if (dist[tx+dx][ty+dy] == dist[tx][ty]-1){
                maze[tx+dx][ty+dy] = '.';
                tx += dx;
                ty += dy;
                break;
            }else maze[tx+dx][ty+dy] = ' ';
        }
    }

    for (int i = 0; i < H; ++i){
        for (int j = 0; j < W; ++j){
            cout << maze[i][j] << " ";
        }
        cout << '\n';
    }
    return 0;
}

