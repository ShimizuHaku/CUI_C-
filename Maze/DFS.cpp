#include <bits/stdc++.h>
using namespace std;

void rotate(int& x, int& y){
    swap(x,y);
    x*=-1;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    int H, W;
    cin >> H >> W;
    vector<string> maze(H);
    for (int i = 0; i < H; ++i) cin >> maze[i];

    vector<vector<int>> dist(H, vector<int>(W, -1));
    dist[1][1] = 0;
    auto dfs = [&](auto self, int x, int y, int dx, int dy) -> void {
        for (int i = 0; i < 3; ++i){
            rotate(dx,dy);
            int nx = x + dx, ny = y + dy;
            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
            if (maze[nx][ny] == '#') continue;
            if (dist[nx][ny] == -1 || dist[nx][ny] > dist[x][y]+1){
                dist[nx][ny] = dist[x][y]+1;
                self(self,nx,ny,dx,dy);
            }
        }
    };

    dfs(dfs,1,1,0,-1);

    int px = H-2, py = W-2;
    int dx = 0, dy = 1;
    while (1) {
        for (int i = 0; i < 3; ++i){
            rotate(dx,dy);
            int nx = px + dx, ny = py + dy;
            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
            if (maze[nx][ny] == '#') continue;
            if (dist[nx][ny]+1 == dist[px][py]){
                maze[nx][ny] = '.';
                px = nx;
                py = ny;
                break;
            }
            else{
                maze[nx][ny] = ' ';
            }
        }
        if (px == 1 && py == 1) break;
    }

    for (int i = 0; i < H; ++i){
        for (int j = 0; j < W; ++j){
            cout << maze[i][j] <<  " ";
        }
        cout << "\n";
    }
    return 0;
}

