/*
25304 ������
----------------------------------- ���� -----------------------------------
�ؿ��̴� ���� �ֿ� ��鼭 ó������ �ڽ�Ʈ�ڸ� �� �ô�. ���� ������. �׷���, �� �� ������ �ʾҴµ� �����ϰ� ���� �ݾ��� ������ ���̴�! �ؿ��̴� �������� ���鼭 ��Ȯ�ϰ� ���� ���� �´��� Ȯ���غ��� �Ѵ�.

�������� ����,

������ �� ������ ���ݰ� ����
������ ���ǵ��� �� �ݾ�
�� ����, ������ ������ ���ݰ� ������ ����� �� �ݾ��� �������� ���� �� �ݾװ� ��ġ�ϴ��� �˻��غ���.
----------------------------------- �Է� -----------------------------------
ù° �ٿ��� �������� ���� �� �ݾ� X�� �־�����.

��° �ٿ��� �������� ���� ������ ������ ������ �� $N$�� �־�����.

���� $N$���� �ٿ��� �� ������ ���� $a$�� ���� $b$�� ������ ���̿� �ΰ� �־�����.
----------------------------------- ��� -----------------------------------
������ ������ ���ݰ� ������ ����� �� �ݾ��� �������� ���� �� �ݾװ� ��ġ�ϸ� Yes�� ����Ѵ�. ��ġ���� �ʴ´ٸ� No�� ����Ѵ�.
----------------------------------- ���� -----------------------------------
260000
4
20000 5
30000 2
10000 6
5000 8
Yes
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int testSum = 0;
    int realSum = 0;
    int tot = 0;

    cin >> testSum;
    cin >> tot;

    for (int i = 0;i < tot;i++) {
        int price, num;
        cin >> price >> num;

        realSum += price * num;
    }

    if (realSum == testSum) {
        cout << "Yes";
    }
    else {
        cout << "No";
    }

    return 0;
}