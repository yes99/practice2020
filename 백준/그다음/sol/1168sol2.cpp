#include <iostream>
#include <vector>
#include <cmath>

void Solve(void);

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    Solve();
}

void MakeTree(std::vector<int> &segmentTree, int arrSize)
{
    int t = ceil(log2(arrSize));
    int treeSize = 1 << (t + 1);

    segmentTree.resize(treeSize);
}

int UpdateTree(int val, std::vector<int> &segmentTree, int nodeIndex, int arrStart, int arrEnd, int arrTarget)
{
    if (arrTarget < arrStart || arrEnd < arrTarget)
        return segmentTree[nodeIndex];

    if (arrStart == arrEnd)
    {
        if (arrStart == arrTarget)
            segmentTree[nodeIndex] = val;
        return segmentTree[nodeIndex];
    }

    int arrMid = (arrStart + arrEnd) / 2;
    segmentTree[nodeIndex] = UpdateTree(val, segmentTree, nodeIndex * 2, arrStart, arrMid, arrTarget) + UpdateTree(val, segmentTree, nodeIndex * 2 + 1, arrMid + 1, arrEnd, arrTarget);
    return segmentTree[nodeIndex];
}

int QuerySum(std::vector<int> &segmentTree, int lowIndex, int highIndex, int nodeIndex, int arrStart, int arrEnd)
{
    if (arrEnd < lowIndex || highIndex < arrStart)
        return 0;

    if (lowIndex <= arrStart && arrEnd <= highIndex)
        return segmentTree[nodeIndex];

    int arrMid = (arrStart + arrEnd) / 2;
    return QuerySum(segmentTree, lowIndex, highIndex, nodeIndex * 2, arrStart, arrMid) + QuerySum(segmentTree, lowIndex, highIndex, nodeIndex * 2 + 1, arrMid + 1, arrEnd);
}

int QueryIndex(std::vector<int> &segmentTree, int val, int nodeIndex, int arrStart, int arrEnd)
{
    if (arrStart == arrEnd)
        return arrStart;

    int arrMid = (arrStart + arrEnd) / 2;
    if (val <= segmentTree[nodeIndex * 2])
        return QueryIndex(segmentTree, val, nodeIndex * 2, arrStart, arrMid);
    else
        return QueryIndex(segmentTree, val - segmentTree[nodeIndex * 2], nodeIndex * 2 + 1, arrMid + 1, arrEnd);
}

void Solve(void)
{
    int n, k;
    std::cin >> n >> k;

    std::vector<int> segmentTree;
    MakeTree(segmentTree, n);
    for (int i = 1; i <= n; i++)
        UpdateTree(1, segmentTree, 1, 1, n, i);

    std::vector<int> result;

    while (segmentTree[1])
    {
        int needSum = k;
        if (result.size())
            needSum = (QuerySum(segmentTree, 1, result.back(), 1, 1, n) + k) % segmentTree[1];

        if (0 == needSum)
            needSum = segmentTree[1];

        result.push_back(QueryIndex(segmentTree, needSum, 1, 1, n));
        UpdateTree(0, segmentTree, 1, 1, n, result.back());
    }

    std::cout << "<";
    for (int i = 0; i < n; i++)
        std::cout << result[i] << (i == n - 1 ? ">" : ", ");
}