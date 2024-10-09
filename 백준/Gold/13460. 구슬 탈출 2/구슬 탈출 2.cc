#include <iostream>
#include <vector>
#include <deque>
#include <tuple>
#include <string>

using namespace std;

typedef struct {
    int y;
    int x;
    int move;
} Pos;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

Pos Move(vector<string> &board, Pos cur, int d) {
    int y = cur.y;
    int x = cur.x;
    int move = 0;

    while (board[y + dy[d]][x + dx[d]] != '#' && board[y][x] != 'O') {
        y += dy[d];
        x += dx[d];
        move++;
    }
    return Pos{y, x, move};
}

void Bfs(vector<string> &board, Pos red, Pos blue) {
    deque<tuple<Pos, Pos, int>> queue;

    queue.emplace_back(red, blue, 0);

    while (!queue.empty()) {
        Pos r, b;
        int c;
        tie(r, b, c) = queue.front();
        queue.pop_front();

        if (c > 10) {
            cout << "-1" << endl;
            return;
        }
        if (board[r.y][r.x] == 'O') {
            cout << c << endl;
            return;
        }

        for (int d = 0; d < 4; d++) {
            Pos nr = Move(board, r, d);
            Pos nb = Move(board, b, d);
            if (nr.y == nb.y && nr.x == nb.x) {
                if (board[nb.y][nb.x] == 'O') {
                    continue;
                }

                if (nr.move < nb.move) {
                    nb.y -= dy[d];
                    nb.x -= dx[d];
                } else {
                    nr.y -= dy[d];
                    nr.x -= dx[d];
                }
            }

            queue.emplace_back(nr, nb, c + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n = 0, m = 0;
    cin >> n >> m;
    cin.ignore();

    vector<string> board(n);
    Pos red;
    Pos blue;

    for (int y = 0; y < n; y++) {
        cin >> board[y];
        cin.ignore();
        for (int x = 0; x < m; x++) {
            if (board[y][x] == 'R') {
                red = Pos{y, x, 0};
            } else if (board[y][x] == 'B') {
                blue = Pos{y, x, 0};
            }
        }
    }

    Bfs(board, red, blue);

    return 0;
}
