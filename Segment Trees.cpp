#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
private:
  vector<int> A;    // Input array
  vector<int> tree; // Segment tree
  int n;            // Size of input array

  // Build the tree recursively
  void build(int node, int start, int end)
  {
    if (start == end)
    {
      tree[node] = A[start];
    }
    else
    {
      int mid = (start + end) / 2;
      build(2 * node, start, mid);
      build(2 * node + 1, mid + 1, end);
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  // Update a single element
  void update(int node, int start, int end, int idx, int val)
  {
    if (start == end)
    {
      A[idx] += val;
      tree[node] += val;
    }
    else
    {
      int mid = (start + end) / 2;
      if (idx <= mid)
        update(2 * node, start, mid, idx, val);
      else
        update(2 * node + 1, mid + 1, end, idx, val);
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  // Query range sum
  int query(int node, int start, int end, int l, int r)
  {
    if (r < start || end < l)
      return 0;
    if (l <= start && end <= r)
      return tree[node];
    int mid = (start + end) / 2;
    int leftSum = query(2 * node, start, mid, l, r);
    int rightSum = query(2 * node + 1, mid + 1, end, l, r);
    return leftSum + rightSum;
  }

public:
  // Constructor
  SegmentTree(const vector<int> &input)
  {
    A = input;
    n = A.size();
    tree.resize(4 * n);
    build(1, 0, n - 1);
  }

  // Public update function
  void update(int idx, int val)
  {
    update(1, 0, n - 1, idx, val);
  }

  // Public query function
  int query(int l, int r)
  {
    return query(1, 0, n - 1, l, r);
  }
};
