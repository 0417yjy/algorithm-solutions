#include <iostream>
#include <string>
#include <queue>

using namespace std;

enum Operators{ADD, SUB, MUL, DIV};

int *copyArr(int *arr, int n) {
    int *newArr = new int[n];
    for(int i=0;i<n;i++) {
        newArr[i] = arr[i];
    }

    return newArr;
}

void getMinMax(int *arr, int *op_cnt, int n, int &min, int &max) {
    if(n == 2) {
        // 남은 숫자가 2개이면 계산
        int op;
        int result;

        // 마지막 연산자 구하기
        for(int i=0;i<4;i++) {
            if(op_cnt[i] == 1) {
                op = i;
                break;
            }
        }

        // 계산
        switch(op) {
            case ADD:
                result = arr[0] + arr[1];
                break;
            case SUB:
                result = arr[0] - arr[1];
                break;                    
            case MUL:
                result = arr[0] * arr[1];
                break;
            case DIV:
                result = arr[0] / arr[1];
                break;
        }

        if(result < min) {
            min = result;
        }
        if(result > max) {
            max = result;
        }
    }
    else {
        // 
        for(int i=0;i<4;i++) {
            if(op_cnt[i] > 0) {            
                int *sub_op_cnt = copyArr(op_cnt, 4);
                sub_op_cnt[i]--;

                int *sub_arr = new int[n - 1];

                switch(i) {
                    case ADD:
                        sub_arr[0] = arr[0] + arr[1];
                        break;
                    case SUB:
                        sub_arr[0] = arr[0] - arr[1];
                        break;                    
                    case MUL:
                        sub_arr[0] = arr[0] * arr[1];
                        break;
                    case DIV:
                        sub_arr[0] = arr[0] / arr[1];
                        break;
                }

                for(int i=1;i<n - 1;i++) {
                    sub_arr[i] = arr[i + 1];
                }

                getMinMax(sub_arr, sub_op_cnt, n - 1, min, max);

                delete []sub_op_cnt;
                delete []sub_arr;
            }
        }
    }

    
}

int main(void) {
    int n;
    int *arr;
    int op_cnt[4];
    int min =  1000000000;
    int max = -1000000000;

    // input for number array
    cin >> n;

    arr = new int[n];
    for(int i=0;i<n;i++) {
        cin >> arr[i];
    }

    // input for operators
    for(int i=0;i<4;i++) {
        cin >> op_cnt[i];
    }

    getMinMax(arr, op_cnt, n, min, max);
    
    cout << max << endl << min;

    delete [] arr;
    return 0;
}