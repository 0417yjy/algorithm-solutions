"""
21921 블로그
----------------------------------- 문제 -----------------------------------
찬솔이는 블로그를 시작한 지 벌써 
N일이 지났다.

요즘 바빠서 관리를 못 했다가 방문 기록을 봤더니 벌써 누적 방문 수가 6만을 넘었다.

찬솔이는 
X일 동안 가장 많이 들어온 방문자 수와 그 기간들을 알고 싶다.

찬솔이를 대신해서 
X일 동안 가장 많이 들어온 방문자 수와 기간이 몇 개 있는지 구해주자.
----------------------------------- 입력 -----------------------------------
첫째 줄에 블로그를 시작하고 지난 일수 
N와 
X가 공백으로 구분되어 주어진다.

둘째 줄에는 블로그 시작 
1일차부터 
N일차까지 하루 방문자 수가 공백으로 구분되어 주어진다.
----------------------------------- 출력 -----------------------------------
첫째 줄에 
X일 동안 가장 많이 들어온 방문자 수를 출력한다. 만약 최대 방문자 수가 0명이라면 SAD를 출력한다.

만약 최대 방문자 수가 0명이 아닌 경우 둘째 줄에 기간이 몇 개 있는지 출력한다.
----------------------------------- 예제 -----------------------------------
5 2
1 4 2 5 1

7
1
----------------------------------- 예제 -----------------------------------
7 5
1 1 1 1 1 5 1

9
2
----------------------------------- 예제 -----------------------------------
5 3
0 0 0 0 0

SAD
"""
n, x = map(int, input().split())
visit_list = list(map(int, input().split()))

window = visit_list[0:x]
max_visit = sum(window)
max_visit_cnt = 1

current_visit = max_visit
for i in range(1, n - x + 1):
    # window = visit_list[i:i + x]
    # print(window)
    current_visit -= visit_list[i - 1]
    current_visit += visit_list[i + x - 1]
    if max_visit < current_visit:
        max_visit = current_visit
        max_visit_cnt = 1
    elif max_visit == current_visit:
        max_visit_cnt += 1

if max_visit == 0:
    print('SAD')
else:
    print(max_visit)
    print(max_visit_cnt)