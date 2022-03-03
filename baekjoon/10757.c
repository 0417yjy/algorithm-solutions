/*
10757 큰 수 A+B
----------------------------------- 문제 -----------------------------------
두 정수 A와 B를 입력받은 다음, A+B를 출력하는 프로그램을 작성하시오.
----------------------------------- 입력 -----------------------------------
첫째 줄에 A와 B가 주어진다. (0 < A,B < 10^10000)
----------------------------------- 출력 -----------------------------------
첫째 줄에 A+B를 출력한다.
----------------------------------- 예제 -----------------------------------
9223372036854775807 9223372036854775808
18446744073709551615
----------------------------------- 예제 -----------------------------------
999 1
1000
*/

#include <stdio.h>
#include <string.h>

void swap(char* a, char *b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse_arr(char *arr, int size) {
    int i;
    
    for(i=0;i<size / 2;i++) {
        if(i < size - 1 - i) {
            swap(&arr[i], &arr[size - 1 - i]);
        }
    }
}

void print_arr(char *arr, int size) {
    int i;
    for(i=0;i<size;i++) {
        printf("%c", arr[i]);
    }
    printf("\n");
}

int main(void) {
    char a[10001] = {0};
    char b[10001] = {0};
    char res[10002];    
    char carry = 0;
    char sum;
    int longer_length;
    int i;

    scanf("%s %s", a, b);
    
    reverse_arr(a, strlen(a));
    reverse_arr(b, strlen(b));

    longer_length = strlen(a) > strlen(b) ? strlen(a) : strlen(b);

    for(i=0;i<longer_length;i++) {
        sum = a[i] + b[i] + carry - '0';
        if(sum < '0') {
            sum += '0';
        }
        
        if(sum > '9') {
            sum -= 10;
            carry = 1;
        } else {
            carry = 0;
        }

        res[i] = sum;
    }
    
    if(carry > 0) {
        res[longer_length] = '1';
        res[longer_length + 1] = '\0';
    } else {
        res[longer_length] = '\0';
    }

    reverse_arr(res, strlen(res));
    print_arr(res, strlen(res));

    return 0;
}