/*
11729 하노이 탑 이동 순서
----------------------------------- 문제 -----------------------------------
세 개의 장대가 있고 첫 번째 장대에는 반경이 서로 다른 n개의 원판이 쌓여 있다. 각 원판은 반경이 큰 순서대로 쌓여있다. 이제 수도승들이 다음 규칙에 따라 첫 번째 장대에서 세 번째 장대로 옮기려 한다.

1. 한 번에 한 개의 원판만을 다른 탑으로 옮길 수 있다.
2. 쌓아 놓은 원판은 항상 위의 것이 아래의 것보다 작아야 한다.

이 작업을 수행하는데 필요한 이동 순서를 출력하는 프로그램을 작성하라. 단, 이동 횟수는 최소가 되어야 한다.
----------------------------------- 입력 -----------------------------------
첫째 줄에 첫 번째 장대에 쌓인 원판의 개수 N (1 ≤ N ≤ 20)이 주어진다.
----------------------------------- 출력 -----------------------------------
첫째 줄에 옮긴 횟수 K를 출력한다.

두 번째 줄부터 수행 과정을 출력한다. 두 번째 줄부터 K개의 줄에 걸쳐 두 정수 A B를 빈칸을 사이에 두고 출력하는데, 이는 A번째 탑의 가장 위에 있는 원판을 B번째 탑의 가장 위로 옮긴다는 뜻이다.
----------------------------------- 예제 -----------------------------------
3

7
1 3
1 2
3 2
1 3
2 1
2 3
1 3
*/

#include <iostream>
#include <stack>
#include <utility>
#include <climits>

using namespace std;

void print_stack_sub(stack<int> s) {
    if(s.empty()) {
        return;
    }

    int x = s.top();
    s.pop();

    print_stack_sub(s);

    cout << x << ' ';

    s.push(x);
}

void print_stack(stack<int> *stack_int) {
    for(int i=0;i<3;i++) {
        print_stack_sub(stack_int[i]);
        cout << endl;
    }
}

int get_hanoi_cnt(stack<int> *stack_arr, stack<pair<int,int>> history, int &cnt, stack<pair<int,int>> &answer) {
    print_stack(stack_arr);
    if(stack_arr[0].empty() && stack_arr[1].empty()) {
        return history.size();
    }

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(i != j) {
                // 다른 스택에 둘 수 있는지 체크
                if(stack_arr[j].empty() || stack_arr[j].top() > stack_arr[i].top()) {
                    // 마지막 히스토리와 같은건 제외
                    cout << "i: " << i << " j: " << j << endl;
                    if(!history.empty() && i == history.top().second && j == history.top().first)  {
                        cout << "was history" << endl;
                        // do nothing
                    } else {
                        // 가능하면 그렇게 옮기고, 다음 턴을 체크
                        stack<pair<int,int>> new_move_history = history;
                        new_move_history.push(make_pair(i, j));

                        // i의 탑을 j로 옮김
                        int moved = stack_arr[i].top();
                        stack_arr[i].pop();
                        stack_arr[j].push(moved);

                        int new_cnt = get_hanoi_cnt(stack_arr, new_move_history, cnt, answer);
                        if(new_cnt < cnt) {
                            cnt = new_cnt;
                            answer = new_move_history;
                        }

                        // 계산 끝났으면 다시 되돌려놓음
                        stack_arr[j].pop();
                        stack_arr[i].push(moved);
                    }   
                }
            }
        }
    }

    return cnt;
}

int main(void) {
    int n, cnt = INT_MAX;
    stack<int> stack_arr[3];
    stack<pair<int,int>> history_stack, answer_stack;

    cin >> n;

    // initialize
    for(int i=n;i>=1;i--) {
        stack_arr[0].push(i);
    }

    cnt = get_hanoi_cnt(stack_arr, history_stack, cnt, answer_stack);

    printf("%d\n", cnt);

    return 0;
}