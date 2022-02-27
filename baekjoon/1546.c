/*
1546 평균
----------------------------------- 문제 -----------------------------------
세준이는 기말고사를 망쳤다. 세준이는 점수를 조작해서 집에 가져가기로 했다. 일단 세준이는 자기 점수 중에 최댓값을 골랐다. 이 값을 M이라고 한다. 그리고 나서 모든 점수를 점수/M*100으로 고쳤다.

예를 들어, 세준이의 최고점이 70이고, 수학점수가 50이었으면 수학점수는 50/70*100이 되어 71.43점이 된다.

세준이의 성적을 위의 방법대로 새로 계산했을 때, 새로운 평균을 구하는 프로그램을 작성하시오.
----------------------------------- 입력 -----------------------------------
첫째 줄에 시험 본 과목의 개수 N이 주어진다. 이 값은 1000보다 작거나 같다. 둘째 줄에 세준이의 현재 성적이 주어진다. 이 값은 100보다 작거나 같은 음이 아닌 정수이고, 적어도 하나의 값은 0보다 크다.
----------------------------------- 출력 -----------------------------------
첫째 줄에 새로운 평균을 출력한다. 실제 정답과 출력값의 절대오차 또는 상대오차가 10-2 이하이면 정답이다.
----------------------------------- 예제 -----------------------------------
3
40 80 60

75.0
----------------------------------- 예제 -----------------------------------
3
10 20 30

66.666667
*/

#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    return (arg1 > arg2) - (arg1 < arg2);
}

double get_average(const double* arr, int size) {
    int i;
    double sum = 0;
    
    for(i=0;i<size;i++) {
        sum += arr[i];
    }

    return sum / size;
}

int main(void) {
    int n;
    int *org_arr;
    double *dirty_arr;
    int i;
    int max;
    double new_avg;

    scanf("%d", &n);
    org_arr = (int*)malloc(sizeof(int) * n);
    dirty_arr = (double*)malloc(sizeof(double) * n);

    for(i=0;i<n;i++) {
        scanf("%d", &org_arr[i]);
    }

    // 최댓값 구하기 (정렬해서)
    qsort(org_arr, n, sizeof(int), compare_ints);
    max = org_arr[n - 1];

    for(i=0;i<n;i++) {
        dirty_arr[i] = (double)org_arr[i] / max * 100;
    }

    printf("%lf", get_average(dirty_arr, n));

    free(org_arr);
    free(dirty_arr);
    return 0;
}