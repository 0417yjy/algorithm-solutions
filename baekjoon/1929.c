/*
1929 소수 구하기
----------------------------------- 문제 -----------------------------------
M이상 N이하의 소수를 모두 출력하는 프로그램을 작성하시오.
----------------------------------- 입력 -----------------------------------
첫째 줄에 자연수 M과 N이 빈 칸을 사이에 두고 주어진다. (1 ≤ M ≤ N ≤ 1,000,000) M이상 N이하의 소수가 하나 이상 있는 입력만 주어진다.
----------------------------------- 출력 -----------------------------------
한 줄에 하나씩, 증가하는 순서대로 소수를 출력한다.
----------------------------------- 예제 -----------------------------------
3 16

3
5
7
11
13
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(void) {
    int *prime_arr;
    int m, n;
    int i, j;
    int sum = 0;

    scanf("%d %d", &m, &n);

    prime_arr = (int*)malloc(sizeof(int) * (n + 1));    

    // 소수 배열 만들기    
    prime_arr[0] = false;
    prime_arr[1] = false;
    for(i=2;i<=n;i++) {
        prime_arr[i] = true;
    }

    for(i=2;i<=n;i++) {
        if(prime_arr[i] == true) {
            for(j=2;i*j<=n;j++) {
                prime_arr[i*j] = false;
            }
        }
    }

    // 소수 합 구하기
    for(i=m;i<=n;i++) {
        if(prime_arr[i] == true) {
            printf("%d\n", i);
        }
    }

    free(prime_arr);
    return 0;
}