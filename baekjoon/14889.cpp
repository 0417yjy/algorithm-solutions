#include <iostream>
#include <climits>
#include <cstdlib>

using namespace std;

bool *dupArr(bool *arr, int n) {
    bool *dup = new bool[n];
    for(int i=0;i<n;i++) {
        dup[i] = arr[i];
    }
    return dup;
}

void printArr(int *arr, int n) {
    for(int i=0;i<n;i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

int getSum(int **map, int *arr, int n) {
    int sum = 0;

    for(int i=0;i<n - 1;i++) {
        for(int j=i + 1;j<n;j++) {
            sum += map[arr[i]][arr[j]] + map[arr[j]][arr[i]];
        }
    }

    return sum;
}

int getMinDif(int **map, int n, bool *chosenPlayers, int cnt, int idx) {
    if(cnt == n/2) {
        // 두 팀의 합을 구해서 차이를 리턴
        int result;

        int *start_team = new int[n/2];
        int *link_team = new int[n/2];

        int start_idx = 0;
        int link_idx = 0;        

        for(int i=0;i<n;i++) {
            if(chosenPlayers[i]) {
                start_team[start_idx++] = i;
            } else {
                link_team[link_idx++] = i;
            }
        }
        // cout << "start team: ";
        // printArr(start_team, n/2) ;
        // cout << endl;
        // cout << "link team: ";
        // printArr(link_team, n/2) ;
        // cout << endl;

        // cout << "calculting..." << endl;
        // cout << "start team: " << getSum(map, start_team, n/2) << endl;
        // cout << "link team: " << getSum(map, link_team, n/2) << endl;
        result = abs(getSum(map, start_team, n/2) - getSum(map, link_team, n/2));

        delete [] start_team;
        delete [] link_team;

        // cout << "result is: " << result << endl;
        return result;
    }

    int min = INT_MAX;

    // cout << "idx: " << idx << endl << "cnt: " << cnt << endl;
    for(int i=idx + 1;i<n - (n / 2 - cnt);i++) {
        // cout << "i: " << i << endl;

        bool *tmp_players = dupArr(chosenPlayers, n);        
        int result;

        tmp_players[i] = true;
        result = getMinDif(map, n, tmp_players, cnt + 1, i);
        if(min > result) {
            min = result;
        }

        delete [] tmp_players;
    }

    return min;
}

int main(void) {
    int n;
    int **map;
    bool *players_arr;
    int answer;
    
    cin >> n;

    // allocate arrs
    map = new int*[n];
    for(int i=0;i<n;i++) {
        map[i] = new int[n];
    }

    players_arr = new bool[n];

    // init arrs
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cin >> map[i][j];
        }
    }

    for(int i=0;i<n;i++) {
        players_arr[i] = false;
    }

    // process
    // for(int i=0;i<n;i++) {
    //     for(int j=0;j<n;j++) {
    //         cout << map[i][j];
    //     }
    //     cout << endl;
    // }

    // for(int i=0;i<n;i++) {
    //     cout << players_arr[i];
    // }

    answer = getMinDif(map, n, players_arr, 0, -1);

    // print answer
    cout << answer;

    return 0;
}