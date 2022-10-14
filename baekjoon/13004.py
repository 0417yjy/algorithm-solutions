"""
13004 비밀 임무
----------------------------------- 문제 -----------------------------------
BOJ 기지에서는 비밀 임무를 위한 요원들을 골라내고 있다. 그들은 이 임무에 적합한 n명의 요원 후보를 골라내는 데 성공했다. 이 요원들은 모든 점에서 뛰어난 요원들이었지만, 단 하나의 문제가 있었다. 바로 너무 수다스럽다는 것이다.

이 문제를 해결하기 위해, 기지 감독관은 모든 요원 후보들을 한 줄로 세우고, 각 요원 후보들에게 "수다도" a_i를 부여하였다. 그 후, 감독관은 인접한 두 요원 후보를 선택하여 둘의 위치를 바꾸는 작업을 최대 s번 수행할 것이다. 이 작업이 모두 끝난 후, 앞에서부터 k명의 요원 후보들이 요원으로 선택될 것이다.

기지 감독관은 이렇게 선택된 k명의 요원의 "수다도"의 합을 최소로 하길 원한다. 둘의 위치를 바꾸는 작업을 어떤 식으로 수행해야, 이 합을 최소로 만들 수 있을까?
----------------------------------- 입력 -----------------------------------
첫 번째 줄에는 세 개의 자연수 n, k, s가 주어진다. (1 ≤ k ≤ n ≤ 150, 1 ≤ s ≤ 10^9)

다음 줄에는 각 요원의 수다도를 나타내는 정수 n개가 주어진다. (1 ≤ qi ≤ 1,000,000)
----------------------------------- 출력 -----------------------------------
처음 k명의 요원의 수다도의 합의 최솟값을 출력한다.
----------------------------------- 예제 -----------------------------------
3 2 2
2 4 1

3
----------------------------------- 예제 -----------------------------------
5 4 2
10 1 6 2 5

18
----------------------------------- 예제 -----------------------------------
5 2 3
3 1 4 2 5

3
"""
import itertools

# returns (selected element's index, unselected element's index, required turns, difference)


def getPairInfo(pair):
    return (pair[0][1][0], pair[1][1][0], pair[0][1][1] + pair[1][1][1] + 1, pair[0][0] - pair[1][0])

# returns switched indices and required turns
# if there is no pair to be switched, return (None, 0)


def getSwitchedPair(selectedDict: dict, unSelectedDict: dict, s: int):
    selectedItems = list(selectedDict.items())
    unSelectedItems = list(unSelectedDict.items())

    pairList = sorted(list(filter(lambda e: e[2] <= s and e[3] > 0, list(map(getPairInfo, list(
        itertools.product(selectedItems, unSelectedItems)))))), key=lambda e: (-e[3], e[2]))

    if len(pairList) > 0:
        return pairList[0]
    else:
        return None


# Main Script
n, k, s = map(int, input().split())
orgTalkList = list(map(int, input().split()))

# get best minimal value
sortedTalkList = orgTalkList.copy()
sortedTalkList.sort()

bestMin = sum(sortedTalkList[0:k])

talkList = orgTalkList.copy()

while s > 0:
    selectedList = talkList[:k]
    unSelectedList = talkList[k:]

    # get current value
    currentMin = sum(selectedList)

    # if current value is the best value, quit immediately
    if currentMin == bestMin:
        print(bestMin)
        quit()

    selectedDict = {}
    for i in range(len(selectedList)):
        # save required steps to go out
        selectedDict[selectedList[i]] = (i, k - i - 1)

    unSelectedDict = {}
    for i in range(len(unSelectedList)):
        # save required steps to go out
        unSelectedDict[unSelectedList[i]] = (k + i, i)

    currentSwitch = getSwitchedPair(selectedDict, unSelectedDict, s)
    if currentSwitch is None:
        print(currentMin)
        quit()
    else:
        selectedSwitchElement = selectedList.pop(currentSwitch[0])
        unSelectedSwitchElement = unSelectedList.pop(currentSwitch[1] - k)

        talkList = selectedList.copy()
        talkList.append(unSelectedSwitchElement)
        talkList.append(selectedSwitchElement)
        talkList.extend(unSelectedList)
        s -= currentSwitch[2]

print(sum(talkList[:k]))
quit()
