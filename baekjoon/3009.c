/*
3009 네 번째 점
----------------------------------- 문제 -----------------------------------
세 점이 주어졌을 때, 축에 평행한 직사각형을 만들기 위해서 필요한 네 번째 점을 찾는 프로그램을 작성하시오.
----------------------------------- 입력 -----------------------------------
세 점의 좌표가 한 줄에 하나씩 주어진다. 좌표는 1보다 크거나 같고, 1000보다 작거나 같은 정수이다.
----------------------------------- 출력 -----------------------------------
직사각형의 네 번째 점의 좌표를 출력한다.
----------------------------------- 예제 -----------------------------------
5 5
5 7
7 5

7 7
----------------------------------- 예제 -----------------------------------
30 20
10 10
10 20

30 10
*/

#include <stdio.h>

int get_alone(int *arr) {
    int i;
    int num1 = -1;
    int num2 = -1;

    num1 = arr[0];
    num2 = arr[1];
    if(num1 == num2) {
        return arr[2];
    } else {
        if(num1 == arr[2]) {
            return num2;
        } else {
            return num1;
        }
    }
}

int main(void) {
    int x[3];
    int y[3];
    int i;
    int ax, ay;

    for(i=0;i<3;i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    printf("%d %d\n", get_alone(x), get_alone(y));
    return 0;
}