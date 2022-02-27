/*
4344 평균은 넘겠지
----------------------------------- 문제 -----------------------------------
대학생 새내기들의 90%는 자신이 반에서 평균은 넘는다고 생각한다. 당신은 그들에게 슬픈 진실을 알려줘야 한다.
----------------------------------- 입력 -----------------------------------
첫째 줄에는 테스트 케이스의 개수 C가 주어진다.

둘째 줄부터 각 테스트 케이스마다 학생의 수 N(1 ≤ N ≤ 1000, N은 정수)이 첫 수로 주어지고, 이어서 N명의 점수가 주어진다. 점수는 0보다 크거나 같고, 100보다 작거나 같은 정수이다.
----------------------------------- 출력 -----------------------------------
각 케이스마다 한 줄씩 평균을 넘는 학생들의 비율을 반올림하여 소수점 셋째 자리까지 출력한다.
----------------------------------- 예제 -----------------------------------
5
5 50 50 70 80 100
7 100 95 90 80 70 60 50
3 70 90 80
3 70 90 81
9 100 99 98 97 96 95 94 93 91

40.000%
57.143%
33.333%
66.667%
55.556%
*/


#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/* Write your own Classes, Structures, or Functions here */
double get_average(const int* arr, int size) {
    int i;
    double sum = 0;
    
    for(i=0;i<size;i++) {
        sum += (double) arr[i];
    }

    return sum / size;
}

/* Main Function */
int main(void) {
    int test_num;    

    /* Define the number of test cases */
    cin >> test_num;
    cin.ignore();
    string* answers = new string[test_num];

    for(int i=0;i<test_num;i++) {
        /* Get input */
        int n;
        cin >> n;

        int *scores = new int[n];
        for(int j=0;j<n;j++) {
            cin >> scores[j];
        }

        /* Write your solution here */
        double avg = get_average(scores, n);

        sort(scores, scores + n);

        int idx = n;
        for(int j=0;j<n;j++) {
            if((double) scores[j] > avg) {
                // 최초로 평균을 넘는 인덱스
                idx = j;
                break;
            }
        }

        double res = (double) (n - idx) / n * 100;

        /* Print outputs here */
        cout << fixed;
        cout.precision(3);
        cout << res << '%' << endl;
    }

	return 0;
}