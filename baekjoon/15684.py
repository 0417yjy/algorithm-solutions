"""
15684 사다리 조작
----------------------------------- 문제 -----------------------------------
사다리 게임은 N개의 세로선과 M개의 가로선으로 이루어져 있다. 인접한 세로선 사이에는 가로선을 놓을 수 있는데, 각각의 세로선마다 가로선을 놓을 수 있는 위치의 개수는 H이고, 모든 세로선이 같은 위치를 갖는다. 아래 그림은 N = 5, H = 6 인 경우의 그림이고, 가로선은 없다.

초록선은 세로선을 나타내고, 초록선과 점선이 교차하는 점은 가로선을 놓을 수 있는 점이다. 가로선은 인접한 두 세로선을 연결해야 한다. 단, 두 가로선이 연속하거나 서로 접하면 안 된다. 또, 가로선은 점선 위에 있어야 한다.

위의 그림에는 가로선이 총 5개 있다. 가로선은 위의 그림과 같이 인접한 두 세로선을 연결해야 하고, 가로선을 놓을 수 있는 위치를 연결해야 한다.

사다리 게임은 각각의 세로선마다 게임을 진행하고, 세로선의 가장 위에서부터 아래 방향으로 내려가야 한다. 이때, 가로선을 만나면 가로선을 이용해 옆 세로선으로 이동한 다음, 이동한 세로선에서 아래 방향으로 이동해야 한다.

위의 그림에서 1번은 3번으로, 2번은 2번으로, 3번은 5번으로, 4번은 1번으로, 5번은 4번으로 도착하게 된다. 아래 두 그림은 1번과 2번이 어떻게 이동했는지 나타내는 그림이다.
	
사다리에 가로선을 추가해서, 사다리 게임의 결과를 조작하려고 한다. 이때, i번 세로선의 결과가 i번이 나와야 한다. 그렇게 하기 위해서 추가해야 하는 가로선 개수의 최솟값을 구하는 프로그램을 작성하시오.
----------------------------------- 입력 -----------------------------------
첫째 줄에 세로선의 개수 N, 가로선의 개수 M, 세로선마다 가로선을 놓을 수 있는 위치의 개수 H가 주어진다. (2 ≤ N ≤ 10, 1 ≤ H ≤ 30, 0 ≤ M ≤ (N-1)×H)

둘째 줄부터 M개의 줄에는 가로선의 정보가 한 줄에 하나씩 주어진다.

가로선의 정보는 두 정수 a과 b로 나타낸다. (1 ≤ a ≤ H, 1 ≤ b ≤ N-1) b번 세로선과 b+1번 세로선을 a번 점선 위치에서 연결했다는 의미이다.

가장 위에 있는 점선의 번호는 1번이고, 아래로 내려갈 때마다 1이 증가한다. 세로선은 가장 왼쪽에 있는 것의 번호가 1번이고, 오른쪽으로 갈 때마다 1이 증가한다.

입력으로 주어지는 가로선이 서로 연속하는 경우는 없다.
----------------------------------- 출력 -----------------------------------
i번 세로선의 결과가 i번이 나오도록 사다리 게임을 조작하려면, 추가해야 하는 가로선 개수의 최솟값을 출력한다. 만약, 정답이 3보다 큰 값이면 -1을 출력한다. 또, 불가능한 경우에도 -1을 출력한다.
----------------------------------- 예제 1 -----------------------------------
5 5 6
1 1
3 2
2 3
5 1
5 4

3
----------------------------------- 예제 2 -----------------------------------
6 5 6
1 1
3 2
1 3
2 5
5 5

3
"""
from itertools import combinations
from copy import deepcopy

def is_good_ladder(board):
    row = len(board)
    col = len(board[0])

    for i in range(col):
        current = i
        for j in range(row):
            if board[j][current] != 0:
                current += board[j][current]
        if current != i:
            return False

    return True
    

def insert_garos(p_board, garo_list):
    disabled_list = []
    for garo in garo_list:
        added_pair = garo['pair']

        try:
            disabled_list.index(added_pair)
            return False
        except:
            # 가로줄 두기
            p_board[added_pair[0]][added_pair[1]] = 1
            p_board[added_pair[0]][added_pair[1] + 1] = -1
            disabled_list.extend(garo['disable'])        
    
    return True

n, m, h = map(int, input().split())
board_org = [[0]*n for _ in range(m + 1)]
available_list = []

for i in range(m):
    ypos, xpos = map(int, input().split())
    board_org[ypos - 1][xpos - 1] = 1
    board_org[ypos - 1][xpos] = -1

if is_good_ladder(board_org):
    print(0)
    exit()

for i in range(n - 1):
    for j in range(m + 1):
        if board_org[j][i] == 0 and ((i < n - 1 and board_org[j][i + 1] == 0) or (i == n - 1)):
            element = {}
            element['pair'] = tuple([j, i])
            element['disable'] = []
            if i > 0:
                element['disable'].append(tuple([j, i - 1]))
            if i < n:
                element['disable'].append(tuple([j, i + 1]))

            available_list.append(element)

for i in range(1, 4):
    combis = list(combinations(available_list, i))
    for j in combis:
        board = deepcopy(board_org)
        if insert_garos(board, j):            
            if is_good_ladder(board):
                print(i)
                exit()

print(-1)