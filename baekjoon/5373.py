"""
5373 큐빙
----------------------------------- 문제 -----------------------------------
루빅스 큐브는 삼차원 퍼즐이다. 보통 루빅스 큐브는 3×3×3개의 작은 정육면체로 이루어져 있다. 퍼즐을 풀려면 각 면에 있는 아홉 개의 작은 정육면체의 색이 동일해야 한다.

큐브는 각 면을 양방향으로 90도 만큼 돌릴 수 있도록 만들어져 있다. 회전이 마친 이후에는, 다른 면을 돌릴 수 있다. 이렇게 큐브의 서로 다른 면을 돌리다 보면, 색을 섞을 수 있다.

이 문제에서는 루빅스 큐브가 모두 풀린 상태에서 시작한다. 윗 면은 흰색, 아랫 면은 노란색, 앞 면은 빨간색, 뒷 면은 오렌지색, 왼쪽 면은 초록색, 오른쪽 면은 파란색이다.

루빅스 큐브를 돌린 방법이 순서대로 주어진다. 이때, 모두 돌린 다음에 가장 윗 면의 색상을 구하는 프로그램을 작성하시오.

위의 그림은 루빅스 큐브를 푼 그림이다. 왼쪽 면은 시계방향으로 조금 돌려져 있는 상태이다.
----------------------------------- 입력 -----------------------------------
첫째 줄에 테스트 케이스의 개수가 주어진다. 테스트 케이스는 최대 100개이다. 각 테스트 케이스는 다음과 같이 구성되어져 있다.

* 첫째 줄에 큐브를 돌린 횟수 n이 주어진다. (1 ≤ n ≤ 1000)
* 둘째 줄에는 큐브를 돌린 방법이 주어진다. 각 방법은 공백으로 구분되어져 있으며, 첫 번째 문자는 돌린 면이다. U: 윗 면, D: 아랫 면, F: 앞 면, B: 뒷 면, L: 왼쪽 면, R: 오른쪽 면이다. 두 번째 문자는 돌린 방향이다. +인 경우에는 시계 방향 (그 면을 바라봤을 때가 기준), -인 경우에는 반시계 방향이다.
----------------------------------- 출력 -----------------------------------
각 테스트 케이스에 대해서 큐브를 모두 돌린 후의 윗 면의 색상을 출력한다. 첫 번째 줄에는 뒷 면과 접하는 칸의 색을 출력하고, 두 번째, 세 번째 줄은 순서대로 출력하면 된다. 흰색은 w, 노란색은 y, 빨간색은 r, 오렌지색은 o, 초록색은 g, 파란색은 b.
----------------------------------- 예제 -----------------------------------
4
1
L-
2
F+ B+
4
U- D- L+ R+
10
L- U- L+ U- L- U- U- L+ U+ U+

rww
rww
rww
bbb
www
ggg
gwg
owr
bwb
gwo
www
rww
"""

def rotate_side(m, d):    
    N = 3
    ret = [[0] * N for _ in range(N)]

    if d % 4 == 1:
        for r in range(N):
            for c in range(N):
                ret[c][N-1-r] = m[r][c]
    elif d % 4 == 2:
        for r in range(N):
            for c in range(N):
                ret[N-1-c][N-1-r] = m[r][c]
    elif d % 4 == 3:
        for r in range(N):
            for c in range(N):
                ret[N-1-c][r] = m[r][c]
    else:
        for r in range(N):
            for c in range(N):
                ret[r][c] = m[r][c]

    return ret

def rotate_cube(side, direction):
    global cube
    U = cube[0]
    D = cube[1]
    F = cube[2]
    B = cube[3]
    L = cube[4]
    R = cube[5]
    if side == 'U':
        if direction == '+':
            """
            U+
            F[0행] = R[0행]
            L[0행] = F[0행]
            B[0행] = L[0행]
            R[0행] = B[0행]
            """
            R_copy = R[0].copy()
            F_copy = F[0].copy()
            L_copy = L[0].copy()
            B_copy = B[0].copy()

            cube[0] = rotate_side(U, 1)
            F[0] = R_copy
            L[0] = F_copy
            B[0] = L_copy
            R[0] = B_copy
        elif direction == '-':
            """
            U-
            F[0행] = L[0행]
            L[0행] = B[0행]
            B[0행] = R[0행]
            R[0행] = F[0행]
            """
            L_copy = L[0].copy()
            B_copy = B[0].copy()
            R_copy = R[0].copy()
            F_copy = F[0].copy()

            cube[0] = rotate_side(U, 3)
            F[0] = L_copy
            L[0] = B_copy
            B[0] = R_copy
            R[0] = F_copy
    
    elif side == 'D':
        if direction == '+':
            """
            D+
            F[2행] = L[2행]
            L[2행] = B[2행]
            B[2행] = R[2행]
            R[2행] = F[2행]
            """
            L_copy = L[2].copy()
            B_copy = B[2].copy()
            R_copy = R[2].copy()
            F_copy = F[2].copy()

            cube[1] = rotate_side(D, 1)
            F[2] = L_copy
            L[2] = B_copy
            B[2] = R_copy
            R[2] = F_copy

            
        elif direction == '-':
            """
            D-
            F[2행] = R[2행]
            L[2행] = F[2행]
            B[2행] = L[2행]
            R[2행] = B[2행]
            """
            R_copy = R[2].copy()
            F_copy = F[2].copy()
            L_copy = L[2].copy()
            B_copy = B[2].copy()

            cube[1] = rotate_side(D, 3)
            F[2] = R_copy
            L[2] = F_copy
            B[2] = L_copy
            R[2] = B_copy
    
    elif side == 'L':
        if direction == '+':
            """
            L+
            F[0열] = U[0열]
            D[0열] = F[0열]
            B[0열] = D[0열]
            U[0열] = B[0열]
            """
            U_copy = (U[0][0], U[1][0], U[2][0])
            F_copy = (F[2][0], F[1][0], F[0][0])
            D_copy = (D[0][0], D[1][0], D[2][0])
            B_copy = (B[2][0], B[1][0], B[0][0])

            cube[4] = rotate_side(L, 1)

            F[0][0] = U_copy[0]
            F[1][0] = U_copy[1]
            F[2][0] = U_copy[2]
            D[0][0] = F_copy[0]
            D[1][0] = F_copy[1]
            D[2][0] = F_copy[2]
            B[0][0] = D_copy[0]
            B[1][0] = D_copy[1]
            B[2][0] = D_copy[2]
            U[0][0] = B_copy[0]
            U[1][0] = B_copy[1]
            U[2][0] = B_copy[2]
        elif direction == '-':
            """
            L-
            F[0열] = D[0열]
            D[0열] = B[0열]
            B[0열] = U[0열]
            U[0열] = F[0열]
            """
            U_copy = (U[0][0], U[1][0], U[2][0])
            F_copy = (F[2][0], F[1][0], F[0][0])
            D_copy = (D[0][0], D[1][0], D[2][0])
            B_copy = (B[2][0], B[1][0], B[0][0])

            cube[4] = rotate_side(L, 3)

            F[0][0] = D_copy[0]
            F[1][0] = D_copy[1]
            F[2][0] = D_copy[2]
            D[0][0] = B_copy[0]
            D[1][0] = B_copy[1]
            D[2][0] = B_copy[2]
            B[0][0] = U_copy[0]
            B[1][0] = U_copy[1]
            B[2][0] = U_copy[2]
            U[0][0] = F_copy[0]
            U[1][0] = F_copy[1]
            U[2][0] = F_copy[2]
    
    elif side == 'R':
        if direction == '+':
            """
            R+
            F[2열] = D[2열]
            D[2열] = B[0열]
            B[0열] = U[2열]
            U[2열] = F[2열]
            """
            D_copy = (D[0][2], D[1][2], D[2][2])
            B_copy = (B[0][2], B[1][2], B[2][2])
            U_copy = (U[0][2], U[1][2], U[2][2])
            F_copy = (F[0][2], F[1][2], F[2][2])

            cube[5] = rotate_side(R, 1)

            F[0][2] = D_copy[0]
            F[1][2] = D_copy[1]
            F[2][2] = D_copy[2]
            D[0][2] = B_copy[0]
            D[1][2] = B_copy[1]
            D[2][2] = B_copy[2]
            B[0][0] = U_copy[0]
            B[1][0] = U_copy[1]
            B[2][0] = U_copy[2]
            U[0][2] = F_copy[0]
            U[1][2] = F_copy[1]
            U[2][2] = F_copy[2]
        elif direction == '-':
            """
            R-
            F[2열] = U[2열]
            D[2열] = F[2열]
            B[0열] = D[2열]
            U[2열] = B[0열]
            """
            D_copy = (D[0][2], D[1][2], D[2][2])
            B_copy = (B[0][0], B[1][0], B[2][0])
            U_copy = (U[0][2], U[1][2], U[2][2])
            F_copy = (F[0][2], F[1][2], F[2][2])

            cube[5] = rotate_side(R, 3)

            F[0][2] = U_copy[0]
            F[1][2] = U_copy[1]
            F[2][2] = U_copy[2]
            D[0][2] = F_copy[0]
            D[1][2] = F_copy[1]
            D[2][2] = F_copy[2]
            B[0][0] = D_copy[0]
            B[1][0] = D_copy[1]
            B[2][0] = D_copy[2]
            U[0][2] = B_copy[0]
            U[1][2] = B_copy[1]
            U[2][2] = B_copy[2]
    
    if side == 'F':
        if direction == '+':
            """
            F+
            U[2행] = L[2열]
            D[2행] = R[0열]
            L[2열] = D[2행]
            R[0열] = U[2행]
            """
            L_copy = (L[0][2], L[1][2], L[2][2])
            R_copy = (R[0][0], R[1][0], R[2][0])
            D_copy = (D[2][0], D[2][1], D[2][2])
            U_copy = (U[2][0], U[2][1], U[2][2])

            cube[2] = rotate_side(F, 1)

            U[2][0] = L_copy[0]
            U[2][1] = L_copy[1]
            U[2][2] = L_copy[2]
            D[2][0] = R_copy[0]
            D[2][1] = R_copy[1]
            D[2][2] = R_copy[2]
            L[0][2] = D_copy[0]
            L[1][2] = D_copy[1]
            L[2][2] = D_copy[2]
            D[0][0] = U_copy[0]
            D[1][0] = U_copy[1]
            D[2][0] = U_copy[2]
        elif direction == '-':
            """
            F-
            U[2행] = R[0열]
            D[2행] = L[2열]
            L[2열] = U[2행]
            R[0열] = D[2행]
            """
            L_copy = (L[0][2], L[1][2], L[2][2])
            R_copy = (R[0][0], R[1][0], R[2][0])
            D_copy = (D[2][0], D[2][1], D[2][2])
            U_copy = (U[2][0], U[2][1], U[2][2])

            cube[2] = rotate_side(F, 3)

            U[2][0] = R_copy[0]
            U[2][1] = R_copy[1]
            U[2][2] = R_copy[2]
            D[2][0] = L_copy[0]
            D[2][1] = L_copy[1]
            D[2][2] = L_copy[2]
            L[0][2] = U_copy[0]
            L[1][2] = U_copy[1]
            L[2][2] = U_copy[2]
            D[0][0] = D_copy[0]
            D[1][0] = D_copy[1]
            D[2][0] = D_copy[2]

    if side == 'B':
        if direction == '+':
            """
            B+
            U[0행] = R[2열]
            D[0행] = L[0열]
            L[0열] = U[0행]
            R[2열] = D[0행]
            """
            R_copy = (R[0][2], R[1][2], R[2][2])
            L_copy = (L[0][0], L[1][0], L[2][0])
            U_copy = (U[0][0], U[0][1], U[0][2])
            D_copy = (D[0][0], D[0][1], D[0][2])

            cube[3] = rotate_side(B, 1)

            U[0][0] = R_copy[0]
            U[0][1] = R_copy[1]
            U[0][2] = R_copy[2]
            D[0][0] = L_copy[0]
            D[0][1] = L_copy[1]
            D[0][2] = L_copy[2]
            L[0][0] = U_copy[0]
            L[1][0] = U_copy[1]
            L[2][0] = U_copy[2]
            D[0][2] = D_copy[0]
            D[1][2] = D_copy[1]
            D[2][2] = D_copy[2]

        elif direction == '-':
            """
            B-
            U[0행] = L[0열]
            D[0행] = R[2열]
            L[0열] = D[0행]
            R[2열] = U[0행]
            """
            L_copy = (L[0][0], L[1][0], L[2][0])
            R_copy = (R[0][2], R[1][2], R[2][2])
            D_copy = (D[0][0], D[0][1], D[0][2])
            U_copy = (U[0][0], U[0][1], U[0][2])

            cube[3] = rotate_side(B, 3)

            U[0][0] = L_copy[0]
            U[0][1] = L_copy[1]
            U[0][2] = L_copy[2]
            D[0][0] = R_copy[0]
            D[0][1] = R_copy[1]
            D[0][2] = R_copy[2]
            L[0][0] = U_copy[0]
            L[1][0] = U_copy[1]
            L[2][0] = U_copy[2]
            D[0][2] = D_copy[0]
            D[1][2] = D_copy[1]
            D[2][2] = D_copy[2]


test_cases = int(input())

for _ in range(test_cases):
    times = int(input())
    moves = input().split()
    # 0: U
    # 1: D
    # 2: F
    # 3: B
    # 4: L
    # 5: R
    cube = [
        [
            ['w', 'w', 'w'],
            ['w', 'w', 'w'],
            ['w', 'w', 'w']   
        ],
        [
            ['y', 'y', 'y'],
            ['y', 'y', 'y'],
            ['y', 'y', 'y']
        ],
        [
            ['r', 'r', 'r'],
            ['r', 'r', 'r'],
            ['r', 'r', 'r']
        ],
        [
            ['o', 'o', 'o'],
            ['o', 'o', 'o'],
            ['o', 'o', 'o']
        ],
        [
            ['g', 'g', 'g'],
            ['g', 'g', 'g'],
            ['g', 'g', 'g']
        ],
        [
            ['b', 'b', 'b'],
            ['b', 'b', 'b'],
            ['b', 'b', 'b']
        ],
    ]
 
    for move in moves:
        rotate_cube(move[0], move[1])
        for cu in cube:
            for c in cu:
                print(c)
            print()
    for j in cube[0]:                
        print(j[0] + j[1] + j[2])