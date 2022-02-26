#include <iostream>

using namespace std;

enum DIRECTION_4{NORTH, EAST, SOUTH, WEST};
enum DIRECTION_2{HORIZON, VERTICAL};
enum MAP_TYPE{NOVISION, TYP1, TYP2, TYP3, TYP4, TYP5, WALL, VISION};

int **copy_map(int** map, int n, int m) {
    int **newMap;

    newMap = new int*[n];
    for(int i=0;i<n;i++) {
        newMap[i] = new int[m];
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            newMap[i][j] = map[i][j];
        }
    }

    return newMap;
}

void destroy_map(int **map, int n) {
    for(int i=0;i<n;i++) {
        delete [] map[i];
    }
    delete [] map;
}

void set_one_direction_vision(int **map, int n, int m, int x, int y, int direction) {
    map[x][y] = VISION;

    switch(direction) {
        case NORTH:
            for(int i=x;i>=0;i--) {
                if(map[i][y] == WALL) {
                    // 벽이면 더 이상 볼 수 없음
                    break;
                } else {
                    if(map[i][y] == NOVISION) {
                        map[i][y] = VISION;
                    }                    
                }
            }
            break;
        case EAST:
            for(int j=y;j<m;j++) {
                if(map[x][j] == WALL) {
                    break;
                } else {
                    if(map[x][j] == NOVISION) {
                        map[x][j] = VISION;
                    }    
                }
            }
            break;
        case SOUTH:
            for(int i=x;i<n;i++) {
                if(map[i][y] == WALL) {
                    // 벽이면 더 이상 볼 수 없음
                    break;
                } else {
                    if(map[i][y] == NOVISION) {
                        map[i][y] = VISION;
                    }    
                }
            }
            break;
        case WEST:
            for(int j=y;j>=0;j--) {
                if(map[x][j] == WALL) {
                    break;
                } else {
                    if(map[x][j] == NOVISION) {
                        map[x][j] = VISION;
                    }    
                }
            }
            break;
    }
}

void set_cctv_vision(int **map, int n, int m, int x, int y, int cctv_type, int direction) {
    switch(cctv_type) {
        case TYP1:
            set_one_direction_vision(map, n, m, x, y, direction);
            break;
        case TYP2:
            switch(direction) {
                case HORIZON:
                    set_one_direction_vision(map, n, m, x, y, WEST);
                    set_one_direction_vision(map, n, m, x, y, EAST);
                    break;
                case VERTICAL:
                    set_one_direction_vision(map, n, m, x, y, NORTH);
                    set_one_direction_vision(map, n, m, x, y, SOUTH);
                    break;
            }
            break;
        case TYP3:
            for(int i=direction;i<=direction + 1;i++) {
                if(i < 0) {
                    i = WEST;
                } else if(i > WEST) {
                    i = NORTH;
                }

                set_one_direction_vision(map, n, m, x, y, i);
            }
            break;
        case TYP4:
            for(int i=direction - 1;i<=direction + 1;i++) {
                if(i < 0) {
                    i = WEST;
                } else if(i > WEST) {
                    i = NORTH;
                }

                set_one_direction_vision(map, n, m, x, y, i);
            }
            break;
        case TYP5:
            for(int i=0;i<4;i++) {
                set_one_direction_vision(map, n, m, x, y, i);
            }
            break;
    }
}

void get_min_unseen_area(int **map, int n, int m, int s_x, int s_y, int remain, int &min) {
    if(remain == 0) {
        int cnt = 0;

        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                if(map[i][j] == NOVISION) {
                    cnt++;
                }
            }
        }

        // for(int i=0;i<n;i++) {
        //     for(int j=0;j<m;j++) {
        //         cout << map[i][j] << ' ';
        //     }
        //     cout << endl;
        // }

        if(min > cnt) {
            min = cnt;
        }
    } else {
        // get first cctv
        int x = -1, y = -1;
        int cctv_type;     
        int **tmp_map;   

        for(int i=s_x;i<n;i++) {
            for(int j=s_y;j<m;j++) {
                if(map[i][j] >= TYP1 && map[i][j] <= TYP5) {
                    x = i;
                    y = j;
                    cctv_type = map[i][j];
                    break;
                }
            }
            if(x != -1) {
                break;
            }
        }

        // cout << x << y << cctv_type << endl;

        // cctv 타입에 따라 반복수를 달리
        switch(cctv_type) {
            case TYP1: case TYP3: case TYP4:
                for(int i=0;i<4;i++) {
                    tmp_map = copy_map(map, n, m);
                    set_cctv_vision(tmp_map, n, m, x, y, cctv_type, i);
                    get_min_unseen_area(tmp_map, n, m, x, y, remain - 1, min);
                    destroy_map(tmp_map, n);
                }
                break;
            case TYP2:
                for(int i=0;i<2;i++) {
                    tmp_map = copy_map(map, n, m);
                    set_cctv_vision(tmp_map, n, m, x, y, cctv_type, i);
                    get_min_unseen_area(tmp_map, n, m, x, y, remain - 1, min);
                    destroy_map(tmp_map, n);
                }
                break;
            case TYP5:
                tmp_map = copy_map(map, n, m);
                set_cctv_vision(tmp_map, n, m, x, y, cctv_type, 0);
                get_min_unseen_area(tmp_map, n, m, x, y, remain - 1, min);
                destroy_map(tmp_map, n);
                break;
        }
    }
}

int get_cctv_cnt(int **map, int n, int m) {
    int cnt = 0;

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(map[i][j] >= TYP1 && map[i][j] <= TYP5) {
                cnt++;
            }
        }
    }

    return cnt;
}

int main(void) {
    int n, m;
    int **map;
    int cnt;
    int answer;
    int min;

    cin >> n >> m;

    map = new int*[n];
    for(int i=0;i<n;i++) {
        map[i] = new int[m];
    }
    min = n*m;

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> map[i][j];
        }
    }

    cnt = get_cctv_cnt(map, n, m);
    
    get_min_unseen_area(map, n, m, 0, 0, cnt, min);

    cout << min;

    destroy_map(map, n);
    return 0;    
}