#include <iostream>
#include <string>

using namespace std;

/* Write your own Classes, Structures, or Functions here */
int robot_x, robot_y, robot_d;
int clean_cnt = 0;

enum Directions {NORTH, EAST, SOUTH, WEST};
enum MapInfo {SPACE, WALL, CLEANED};

void destroyMap(int **map, int n) {
    for(int i=0;i<n;i++) {
        delete []map[i];
    }
    delete [] map;
}

bool searchLeft(int **map, int &x, int &y, int &direction) {
    direction = (direction - 1 < 0) ? WEST : direction - 1; // 반시계로 한번 돌은 방향
    
    switch(direction) {
        case NORTH:
            return map[x - 1][y] == SPACE;
        case EAST:
            return map[x][y + 1] == SPACE;
        case SOUTH:
            return map[x + 1][y] == SPACE;
        case WEST:
            return map[x][y - 1] == SPACE;
    }    
}

void moveForward(int &x, int &y, int &direction) {
    switch(direction) {
        case NORTH:
            x--;
            break;
        case EAST:
            y++;
            break;
        case SOUTH:
            x++;
            break;
        case WEST:
            y--;
            break;
    }
}

bool isBackwardSpace(int **map, int &x, int &y, int &direction) {
    switch(direction) {
        case NORTH:
            return map[x + 1][y] != WALL;
        case EAST:
            return map[x][y - 1] != WALL;
        case SOUTH:
            return map[x - 1][y] != WALL;
        case WEST:
            return map[x][y + 1] != WALL;
    }
}

void moveBackward(int &x, int &y, int &direction) {
    switch(direction) {
        case NORTH:
            x++;
            break;
        case EAST:
            y--;
            break;
        case SOUTH:
            x--;
            break;
        case WEST:
            y++;
            break;
    }
}

/* Main Function */
int main(void) {
    int n, m;
    int **map;
    int answer;


    /* Get input */
    cin >> n >> m;
    cin >> robot_x >> robot_y >> robot_d;

    map = new int*[n];    
    for(int i=0;i<n;i++) {
        map[i] = new int[m];
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            int input;
            cin >> input;

            map[i][j] = (int) input;
        }
    }

    /* Write your solution here */
    while(true) {
        bool goFlag = false;

        if(map[robot_x][robot_y] == SPACE) {
            // 1. 현재 위치를 청소한다.
            map[robot_x][robot_y] = CLEANED;
            clean_cnt++;
        }

        for(int i=0;i<4;i++) {
            if(searchLeft(map, robot_x, robot_y, robot_d)) { // 2.a. 왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음
                moveForward(robot_x, robot_y, robot_d); // 한 칸을 전진하고 1번부터 진행한다.
                goFlag = true;
                break;
            }
            // 2.b. 왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 돌아간다.
        }
        
        if(!goFlag) {
            // 2.c. 네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 
            if(isBackwardSpace(map, robot_x, robot_y, robot_d)) {
                moveBackward(robot_x, robot_y, robot_d); // 바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아간다.
            } else {
                // 2.d. 네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.
                break;
            }
        }
    }

    /* Print outputs here */
    answer = clean_cnt;
    cout << answer;


    return 0;
}