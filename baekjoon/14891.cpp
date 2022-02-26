#include <iostream>
#include <string>
#define GEARS_NUM 4
#define STATUS_NUM 8

using namespace std;

// 미리 돌리지 말고 큐에 저장해놨다가 한번에 하는걸로 하자

void rotate_gear(int *gear, int direction) {
    if(direction > 0) {
        // 시계
        int tmp = gear[STATUS_NUM - 1];        
        for(int i=STATUS_NUM - 1;i>0;i--) {
            gear[i] = gear[i - 1];
        }
        gear[0] = tmp;
    } else {
        // 반시계
        int tmp = gear[0];        
        for(int i=0;i<STATUS_NUM - 1;i++) {
            gear[i] = gear[i + 1];
        }
        gear[STATUS_NUM - 1] = tmp;
    }
}

int to_int(char c) {
    return c - '0';
}

int main(void) {
    char c_gears[GEARS_NUM][STATUS_NUM];
    int gears[GEARS_NUM][STATUS_NUM];
    int k;
    int answer;

    for(int i=0;i<GEARS_NUM;i++) {
        for(int j=0;j<STATUS_NUM;j++) {
            cin >> c_gears[i][j];
            gears[i][j] = to_int(c_gears[i][j]);
        }
    }

    cin >> k;

    for(int i=0;i<k;i++) {
        // 톱니 인덱스 2와 6번
        int idx, direction;
        cin >> idx >> direction;
        idx--; // 시작값을 0으로 맞추기 위해

        // 왼쪽부터
        int tmp_idx = idx;
        int tmp_direction = direction;

        int comp = gears[tmp_idx][6];
        for(int j=tmp_idx - 1;j>0;j--) {
            if(gears[j][2] != comp) {
                // 인접한 두 극이 다르면
                comp = gears[j][6]; // 미리 왼쪽 톱니 극 저장
                tmp_direction *= (-1); // 반대로 회전
                rotate_gear(gears[j], tmp_direction);
            } else {
                // 같으면 더 이상 탐색 안함
                break;
            }
        }


        // 오른쪽
        tmp_idx = idx;
        tmp_direction = direction;
        comp = gears[tmp_idx][2];
        for(int j=tmp_idx + 1;j<GEARS_NUM;j++) {
            if(gears[j][6] != comp) {
                // 인접한 두 극이 다르면
                comp = gears[j][2]; // 미리 왼쪽 톱니 극 저장
                tmp_direction *= (-1); // 반대로 회전
                rotate_gear(gears[j], tmp_direction);
            } else {
                // 같으면 더 이상 탐색 안함
                break;
            }
        }

        // 선택한 기어 회전
        rotate_gear(gears[idx], direction);

        for(int i=0;i<GEARS_NUM;i++) {
            for(int j=0;j<STATUS_NUM;j++) {
                cout << gears[i][j];
            }
            cout << endl;
        }

        
    }

    answer = gears[0][0] + gears[1][0] * 2 
           + gears[2][0] * 4 + gears[3][0] * 8;

    cout << answer;

    return 0;
}