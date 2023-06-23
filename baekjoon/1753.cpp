/*
1753 최단경로
----------------------------------- 문제 -----------------------------------
방향그래프가 주어지면 주어진 시작점에서 다른 모든 정점으로의 최단 경로를 구하는 프로그램을 작성하시오. 단, 모든 간선의 가중치는 10 이하의 자연수이다.
----------------------------------- 입력 -----------------------------------
첫째 줄에 정점의 개수 V와 간선의 개수 E가 주어진다. (1 ≤ V ≤ 20,000, 1 ≤ E ≤ 300,000) 모든 정점에는 1부터 V까지 번호가 매겨져 있다고 가정한다. 둘째 줄에는 시작 정점의 번호 K(1 ≤ K ≤ V)가 주어진다. 셋째 줄부터 E개의 줄에 걸쳐 각 간선을 나타내는 세 개의 정수 (u, v, w)가 순서대로 주어진다. 이는 u에서 v로 가는 가중치 w인 간선이 존재한다는 뜻이다. u와 v는 서로 다르며 w는 10 이하의 자연수이다. 서로 다른 두 정점 사이에 여러 개의 간선이 존재할 수도 있음에 유의한다.
----------------------------------- 출력 -----------------------------------
첫째 줄부터 V개의 줄에 걸쳐, i번째 줄에 i번 정점으로의 최단 경로의 경로값을 출력한다. 시작점 자신은 0으로 출력하고, 경로가 존재하지 않는 경우에는 INF를 출력하면 된다.
----------------------------------- 예제 -----------------------------------
5 6
1
5 1 1
1 2 2
1 3 3
2 3 4
2 4 5
3 4 6

0
2
3
7
INF
*/

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void print_mat(int **adj_mat, int n) {
    cout << "================ start print matrix ================" << endl;
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cout << +adj_mat[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "================  end print matrix  ================" << endl;
}

int main(void) {
    int v, e;
    int idx_print;
    map<int, int> *map_list;

    // get input
    cin >> v >> e;
    map_list = new map<int, int>[v];

    // get the index of print
    cin >> idx_print;
    idx_print--; // to adjust index (start from 0)

    for (int i=0;i<e;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        map_list[u].insert({v, w});
    }
    // print_mat(adj_mat, v);

    // process
    vector<int> q;
    for(auto its = map_list[idx_print].begin();its != map_list[idx_print].end(); ++its) {
        int i = its->first;
        auto it = map_list[idx_print].find(i);
        if(it == map_list[idx_print].end()) {
            // do nothing
            continue;
        }

        q.push_back(i);
        while(!q.empty()) {
            int x = q.front();
            q.erase(q.begin());
            // cout << "select " << x << endl;
            for(auto itm = map_list[x].begin();itm != map_list[x].end(); ++itm) {
                int j = itm->first;
                bool modify_flag = false;
                // check if the first weight exists
                itm = map_list[idx_print].find(x);
                if(itm == map_list[idx_print].end()) {
                    continue;
                }

                // check if the second weight exists
                itm = map_list[x].find(j);
                if(itm == map_list[x].end()) {
                    continue;
                }

                // cout << "dest for selected " << j << endl;
                // i is the destination vertex
                // iterate on destination vertex
                auto direct_weight_it = map_list[idx_print].find(j);
                int calculated_weight = map_list[idx_print][x] + map_list[x][j];

                if (direct_weight_it == map_list[idx_print].end()) {
                    modify_flag = true;
                } else {
                    int direct_weight = (map_list[idx_print].find(j))->second;
                    if (calculated_weight < direct_weight) {
                        modify_flag = true;
                    }
                }

                // cout << "direct: " << +direct_weight << endl;
                // cout << "calc: " << +calculated_weight << endl;

                // if direct weight is longer, replace it
                if (modify_flag) {
                    map_list[idx_print][j] = calculated_weight;
                    
                    if(find(q.begin(), q.end(), j) == q.end()) {
                        q.push_back(j);
                    }
                    // cout << "push " << +j << endl;
                }
            }
        }
    }

    // print
    // print_mat(adj_mat, v);
    for(int i=0;i<v;i++) {
        if (idx_print == i) {
            cout << 0 << endl;
        }
        else {
            auto it = map_list[idx_print].find(i);
            if (it == map_list[idx_print].end()) {
                cout << "INF" << endl;
            }
            else {
                cout << map_list[idx_print][i] << endl;
            }
        }
    }

    // post-process
    delete[] map_list;

    return 0;
}