#include <iostream>
using namespace std;

int getPaths(int **map, int n, int l) {
    int paths = 0;

    for(int i=0;i<n;i++) {
        // 가로로 확인
        bool flag = true;
        bool *bridge_placed = new bool[n];

        for(int i=0;i<n;i++) {
            bridge_placed[i] = false;
        }

        // cout << "checking " << i << endl;

        for(int j=0;j<n - 1;j++) {
            if(map[i][j] == map[i][j + 1]) {
                // 다음 타일과 높이가 같으면 패스
                continue;
            } else if(map[i][j] - map[i][j + 1] == 1) {
                // cout << "j: " << j << endl;
                // 다음 타일이 현재보다 1 낮으면

                // 길이 L만큼 놓을 수 있는지?
                if(n - 1 >= j + l) {
                    int height = map[i][j + 1];
                    // 경사를 놓을 수 있게 평평한지                    
                    for(int k=1;k<l;k++) {
                        if(height != map[i][j + 1 + k]) {
                            // cout << "no plat" << endl;
                            flag = false;
                            break;
                        }
                    }
                    if(flag) {
                        // 경사가 놓아졌으면, j를 경사를 놓은 마지막 타일로 옮김
                        for(int k=0;k<l;k++) {
                            bridge_placed[j + 1 + k] = true;
                            // cout << j + 1 + k << ' ';
                        }
                        // cout << endl;
                        j += l - 1;
                    }
                } else {
                    // cout << "too short" << endl;
                    flag = false;
                    break;
                }
            } else if(map[i][j] - map[i][j + 1] == -1) {
                // 다음 타일이 현재보다 1 높으면
                // cout << "j: " << j << endl;

                // 길이 L만큼 놓을 수 있는지? OR 경사로가 있진 않은지
                if(0 <= j - l + 1 && !bridge_placed[j]) {
                    int height = map[i][j];
                    // 경사를 놓을 수 있게 평평한지 OR 경사로가 있진 않은지
                    for(int k=1;k<l;k++) {
                        if(height != map[i][j - k] || bridge_placed[j - k]) {
                            flag = false;
                            break;
                        }
                    }
                    if(flag) {
                        // 경사 놓기
                        for(int k=0;k<l;k++) {
                            bridge_placed[j - k] = true;
                            // cout << j - k << ' ';
                        }
                        // cout << endl;
                    }
                } else {
                    flag = false;
                    break;
                }
            } else {
                // 아니면 실패
                flag = false;
                break;
            }
        }

        if(flag) {
            // 길 확인
            // cout << i << " path" << endl;
            paths++;
        }

        delete [] bridge_placed;
    }

    for(int i=0;i<n;i++) {
        // 세로로 확인
        bool flag = true;
        bool *bridge_placed = new bool[n];

        for(int i=0;i<n;i++) {
            bridge_placed[i] = false;
        }

        // cout << "checking " << i << endl;

        for(int j=0;j<n - 1;j++) {
            if(map[j][i] == map[j + 1][i]) {
                // 다음 타일과 높이가 같으면 패스
                continue;
            } else if(map[j][i] - map[j + 1][i] == 1) {
                // cout << "j: " << j << endl;
                // 다음 타일이 현재보다 1 낮으면

                // 길이 L만큼 놓을 수 있는지?
                if(n - 1 >= j + l) {
                    int height = map[j + 1][i];
                    // 경사를 놓을 수 있게 평평한지                    
                    for(int k=1;k<l;k++) {
                        if(height != map[j + 1 + k][i]) {
                            // cout << "no plat" << endl;
                            flag = false;
                            break;
                        }
                    }
                    if(flag) {
                        // 경사가 놓아졌으면, j를 경사를 놓은 마지막 타일로 옮김
                        for(int k=0;k<l;k++) {
                            bridge_placed[j + 1 + k] = true;
                        }
                        j += l - 1;
                    }
                } else {
                    // cout << "too short" << endl;
                    flag = false;
                    break;
                }
            } else if(map[j][i] - map[j + 1][i] == -1) {
                // 다음 타일이 현재보다 1 높으면
                // cout << "j: " << j << endl;

                // 길이 L만큼 놓을 수 있는지? & 경사로가 있진 않은지
                if(0 <= j - l + 1 && !bridge_placed[j]) {
                    int height = map[j][i];
                    // 경사를 놓을 수 있게 평평한지 OR 경사로가 있진 않은지
                    for(int k=1;k<l;k++) {
                        if(height != map[j - k][i] || bridge_placed[j - k]) {
                            flag = false;
                            break;
                        }
                    }
                    if(flag) {
                        // 경사 놓기
                        for(int k=0;k<l;k++) {
                            bridge_placed[j - k] = true;
                        }
                    }
                } else {
                    flag = false;
                    break;
                }
            } else {
                // 아니면 실패
                flag = false;
                break;
            }
        }

        if(flag) {
            // 길 확인
            // cout << i << " path" << endl;
            paths++;
        }

        delete [] bridge_placed;
    }

    return paths;
}

int main(void) {
    int n, l;
    int **map;
    int answer;

    cin >> n >> l;

    map = new int*[n];
    for(int i=0;i<n;i++) {
        map[i] = new int[n];
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cin >> map[i][j];
        }
    }

    answer = getPaths(map, n, l);

    cout << answer;

    return 0;
}