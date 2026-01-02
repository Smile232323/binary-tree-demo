# 算法伪代码与示意（algorithms.c）

本文档为 `algorithms.c` 中主要函数提供简明伪代码、关键步骤与复杂度说明，便于面试复习。

---

## 1. swap_int(a, b)
目的：交换两个整数的值。

伪代码：
```
function swap_int(a, b):
    t = *a
    *a = *b
    *b = t
```
复杂度：O(1)

---

## 2. bubble_sort(a, n)
目的：对数组 a[0..n-1] 升序排序（冒泡）。

伪代码：
```
function bubble_sort(a, n):
    for i from 0 to n-2:
        swapped = false
        for j from 0 to n-2-i:
            if a[j] > a[j+1]:
                swap(a[j], a[j+1])
                swapped = true
        if not swapped: break
```
关键点：每次内层循环把最大（未排序）元素放到右端；若一轮无交换则数组已排序。
时间复杂度：最坏/平均 O(n^2)，最好 O(n)（已有序时）。

---

## 3. insertion_sort(a, n)
目的：插入排序，将当前元素插入已排序区间。

伪代码：
```
function insertion_sort(a, n):
    for i from 1 to n-1:
        key = a[i]
        j = i - 1
        while j >= 0 and a[j] > key:
            a[j+1] = a[j]
            j = j - 1
        a[j+1] = key
```
关键点：适合小规模或近乎有序数据；稳定排序。
复杂度：最好 O(n)，平均/最坏 O(n^2)。

---

## 4. linear_search(a, n, target)
目的：线性查找，返回首次匹配下标或 -1。

伪代码：
```
function linear_search(a, n, target):
    for i from 0 to n-1:
        if a[i] == target: return i
    return -1
```
复杂度：O(n)

---

## 5. binary_search_iter(a, n, target)
目的：迭代二分查找，数组必须有序。

伪代码：
```
function binary_search_iter(a, n, target):
    l = 0; r = n - 1
    while l <= r:
        m = l + (r - l) // 2
        if a[m] == target: return m
        else if a[m] < target: l = m + 1
        else: r = m - 1
    return -1
```
复杂度：O(log n)

---

## 6. binary_search_rec(a, l, r, target)
目的：递归二分查找。

伪代码：
```
function binary_search_rec(a, l, r, target):
    if l > r: return -1
    m = l + (r - l) // 2
    if a[m] == target: return m
    if a[m] < target: return binary_search_rec(a, m+1, r, target)
    else: return binary_search_rec(a, l, m-1, target)
```
复杂度：O(log n)

---

## 二叉树部分（Node, 遍历）
节点定义：`Node { val, left, right }`

### 递归遍历
前序（根-左-右）：
```
function preorder(node):
    if node is null: return
    visit(node)
    preorder(node.left)
    preorder(node.right)
```
中序（左-根-右）：
```
function inorder(node):
    if node is null: return
    inorder(node.left)
    visit(node)
    inorder(node.right)
```
后序（左-右-根）：
```
function postorder(node):
    if node is null: return
    postorder(node.left)
    postorder(node.right)
    visit(node)
```

复杂度：每棵树遍历均为 O(n) 时间，O(h) 递归栈空间（h 为高度）。

### 迭代中序（栈模拟）
伪代码：
```
function inorder_iter(root):
    stack = empty
    cur = root
    while cur != null or stack not empty:
        while cur != null:
            push(stack, cur)
            cur = cur.left
        cur = pop(stack)
        visit(cur)
        cur = cur.right
```
要点：入栈沿左分支，弹栈访问，转向右分支。

示意：对树
    1
   / \
  2   3
 / \  /
4  5 6

中序访问顺序：4 2 5 1 6 3

### 迭代前序（栈）
伪代码：
```
function preorder_iter(root):
    if root is null: return
    stack = [root]
    while stack not empty:
        n = pop(stack)
        visit(n)
        if n.right != null: push(stack, n.right)
        if n.left != null: push(stack, n.left)
```
要点：先压右后压左，保证左先被处理。

前序示意：1 2 4 5 3 6

### 迭代后序（双栈法）
伪代码：
```
function postorder_iter(root):
    if root is null: return
    s1 = [root]
    s2 = []
    while s1 not empty:
        n = pop(s1)
        push(s2, n)
        if n.left != null: push(s1, n.left)
        if n.right != null: push(s1, n.right)
    while s2 not empty: visit(pop(s2))
```
说明：s2 最终得到的顺序即为后序（左右根）。

### 层序遍历（队列）
伪代码：
```
function level_order(root):
    if root is null: return
    q = queue()
    enqueue(q, root)
    while q not empty:
        n = dequeue(q)
        visit(n)
        if n.left != null: enqueue(q, n.left)
        if n.right != null: enqueue(q, n.right)
```
示意（按层）：
1
2 3
4 5 6

复杂度：O(n) 时间，O(n) 队列空间（最坏一层所有节点）。

---

## 额外建议
- 若需更正式的流程图，可把上面伪代码转换为 Mermaid 或 PlantUML 图形。
- 我可以把此文档扩展为 `README.md` 中的章节或导出为 PDF。

---

文件结束。
