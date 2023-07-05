/*
7576 토마토
----------------------------------- 문제 -----------------------------------
철수의 토마토 농장에서는 토마토를 보관하는 큰 창고를 가지고 있다. 토마토는 아래의 그림과 같이 격자 모양 상자의 칸에 하나씩 넣어서 창고에 보관한다. 

창고에 보관되는 토마토들 중에는 잘 익은 것도 있지만, 아직 익지 않은 토마토들도 있을 수 있다. 보관 후 하루가 지나면, 익은 토마토들의 인접한 곳에 있는 익지 않은 토마토들은 익은 토마토의 영향을 받아 익게 된다. 하나의 토마토의 인접한 곳은 왼쪽, 오른쪽, 앞, 뒤 네 방향에 있는 토마토를 의미한다. 대각선 방향에 있는 토마토들에게는 영향을 주지 못하며, 토마토가 혼자 저절로 익는 경우는 없다고 가정한다. 철수는 창고에 보관된 토마토들이 며칠이 지나면 다 익게 되는지, 그 최소 일수를 알고 싶어 한다.

토마토를 창고에 보관하는 격자모양의 상자들의 크기와 익은 토마토들과 익지 않은 토마토들의 정보가 주어졌을 때, 며칠이 지나면 토마토들이 모두 익는지, 그 최소 일수를 구하는 프로그램을 작성하라. 단, 상자의 일부 칸에는 토마토가 들어있지 않을 수도 있다.
----------------------------------- 입력 -----------------------------------
첫 줄에는 상자의 크기를 나타내는 두 정수 M,N이 주어진다. M은 상자의 가로 칸의 수, N은 상자의 세로 칸의 수를 나타낸다. 단, 2 ≤ M,N ≤ 1,000 이다. 둘째 줄부터는 하나의 상자에 저장된 토마토들의 정보가 주어진다. 즉, 둘째 줄부터 N개의 줄에는 상자에 담긴 토마토의 정보가 주어진다. 하나의 줄에는 상자 가로줄에 들어있는 토마토의 상태가 M개의 정수로 주어진다. 정수 1은 익은 토마토, 정수 0은 익지 않은 토마토, 정수 -1은 토마토가 들어있지 않은 칸을 나타낸다.

토마토가 하나 이상 있는 경우만 입력으로 주어진다.
----------------------------------- 출력 -----------------------------------
여러분은 토마토가 모두 익을 때까지의 최소 날짜를 출력해야 한다. 만약, 저장될 때부터 모든 토마토가 익어있는 상태이면 0을 출력해야 하고, 토마토가 모두 익지는 못하는 상황이면 -1을 출력해야 한다.
----------------------------------- 예제 -----------------------------------
6 4
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 1

8
----------------------------------- 예제 -----------------------------------
6 4
0 -1 0 0 0 0
-1 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 1

-1
----------------------------------- 예제 -----------------------------------
6 4
1 -1 0 0 0 0
0 -1 0 0 0 0
0 0 0 0 -1 0
0 0 0 0 -1 1

6
----------------------------------- 예제 -----------------------------------
5 5
-1 1 0 0 0
0 -1 -1 -1 0
0 -1 -1 -1 0
0 -1 -1 -1 0
0 0 0 0 0

14
----------------------------------- 예제 -----------------------------------
2 2
1 -1
-1 1

0
*/

#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void print_board(int **board, int row, int col) {
    for(int i=0;i<row;i++) {
        for(int j=0;j<col;j++) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

bool check_board(int **board, int row, int col) {
    // return false if there is 0 in the board
    for(int i=0;i<row;i++) {
        for(int j=0;j<col;j++) {
            if(board[i][j] == 0) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    int row, col;
    int **board;
    int days_cnt = -1;
    set<pair<int,int>> target_tomatoes;
    bool end_flag = false;

    // get input
    cin >> col >> row;
    board = new int*[row];
    for(int i=0;i<row;i++) {
        board[i] = new int[col];
    }
    for(int i=0;i<row;i++) {
        for(int j=0;j<col;j++) {
            int input;
            cin >> input;
            board[i][j] = input;

            if (input == 1) {
                target_tomatoes.insert(make_pair(i, j));
            }
        }
    }

    // process
    while (!end_flag) {
        if (target_tomatoes.empty()) {
            end_flag = true;
        }
        else {
            set<pair<int,int>> tmp_set(target_tomatoes.begin(), target_tomatoes.end());
            // copy(target_tomatoes.begin(), target_tomatoes.end(), tmp_set.begin());
            target_tomatoes.clear();

            for(auto it = tmp_set.begin();it != tmp_set.end();it++) {
                int current_x = it->first;
                int current_y = it->second;

                for(int i=0;i<4;i++) {
                    int moved_x = current_x + dx[i];
                    int moved_y = current_y + dy[i];

                    if(moved_x < 0 || moved_x >= row || moved_y < 0 || moved_y >= col || board[moved_x][moved_y] == -1) {
                        // out of boundary or no tomato
                        continue;
                    }

                    if(board[moved_x][moved_y] == 0) {
                        board[moved_x][moved_y] = 1;
                        target_tomatoes.insert(make_pair(moved_x, moved_y));
                    }
                }
            }

            days_cnt++;
            // print_board(board, row, col);
        }
    }

    // print
    if (!check_board(board, row, col)) {
        cout << -1 << endl;
    } else {
        cout << days_cnt << endl;
    }

    return 0;
}