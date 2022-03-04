/*
1978 소수 찾기
----------------------------------- 문제 -----------------------------------
주어진 수 N개 중에서 소수가 몇 개인지 찾아서 출력하는 프로그램을 작성하시오.
----------------------------------- 입력 -----------------------------------
첫 줄에 수의 개수 N이 주어진다. N은 100이하이다. 다음으로 N개의 수가 주어지는데 수는 1,000 이하의 자연수이다.
----------------------------------- 출력 -----------------------------------
주어진 수들 중 소수의 개수를 출력한다.
----------------------------------- 예제 -----------------------------------
4
1 3 5 7

3
*/

#include <stdio.h>
#include <stdbool.h>

int is_prime(int *arr, int check) {
    int i;    
    
    for(i=2;i<check;i++) {
        if(arr[i] == true) {
            if(check % i == 0) {
                // 나눠지면 소수 아님
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    int prime_arr[1001] = { false, false, true, true };
    int n;
    int i, j;
    int input;
    int prime_idx = 3;
    int prime_cnt = 0;

    scanf("%d", &n);

    for(i=0;i<n;i++) {
        scanf("%d", &input);

        if(input <= prime_idx) {
            // 이미 소수 판별이 끝난 경우
            if(prime_arr[input] == true) {
                prime_cnt++;
            }
        } else {
            // 아직 소수 판별이 안 된 경우
            for(j=prime_idx + 1;j<=input;j++) {
                prime_arr[j] = is_prime(prime_arr, j);
            }
            prime_idx = input;

            if(prime_arr[input] == true) {
                prime_cnt++;
            }
        }
    }

    printf("%d\n", prime_cnt);

    return 0;
}