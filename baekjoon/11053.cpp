/*
11053 가장 긴 증가하는 부분 수열
----------------------------------- 문제 -----------------------------------
수열 A가 주어졌을 때, 가장 긴 증가하는 부분 수열을 구하는 프로그램을 작성하시오.

예를 들어, 수열 A = {10, 20, 10, 30, 20, 50} 인 경우에 가장 긴 증가하는 부분 수열은 A = {10, 20, 30, 50} 이고, 길이는 4이다.
----------------------------------- 입력 -----------------------------------
첫째 줄에 수열 A의 크기 N (1 ≤ N ≤ 1,000)이 주어진다.

둘째 줄에는 수열 A를 이루고 있는 Ai가 주어진다. (1 ≤ Ai ≤ 1,000)
----------------------------------- 출력 -----------------------------------
첫째 줄에 수열 A의 가장 긴 증가하는 부분 수열의 길이를 출력한다.
----------------------------------- 예제 -----------------------------------
6
10 20 10 30 20 50

4
*/

#include <iostream>

using namespace std;

int main(void) {
    int n;
    int *arr, *cnt_arr;
    int max_cnt = 1;
    
    // get inputs
    cin >> n;
    arr = new int[n];
    cnt_arr = new int[n];
    for(int i=0;i<n;i++) {
        int num;
        cin >> num;
        arr[i] = num;
        cnt_arr[i] = 1; // initialize all elements to 1 in cnt_arr
    }

    // process
    // iterate from end - 1 (last one is always 1)
    for (int i = n - 2;i>=0;i--) {
        // iterate the right elements from current position
        int current = arr[i];
        int current_max = 1;
        int tmp_cnt = 1;

        for(int j=i + 1;j < n;j++) {
            // search only bigger than current
            if (arr[j] > current) {
                tmp_cnt = cnt_arr[j] + 1;
                if (current_max < tmp_cnt) {
                    // replace if bigger than current max value
                    current_max = tmp_cnt;
                }
            }
        }

        // set current position's cnt value
        cnt_arr[i] = current_max;

        // if this cnt value is bigger than global max value, replace it
        if (current_max > max_cnt) {
            max_cnt = current_max;
        }
    }

    // print
    cout << max_cnt << endl;

    return 0;
}