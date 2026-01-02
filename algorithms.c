#include <stdio.h>
#include <stdlib.h>

/*
 * algorithms.c
 * 简明算法集合（面试参考）
 * - 排序：冒泡排序、插入排序
 * - 查找：顺序查找、折半查找（递归与迭代）
 * - 二叉树：节点定义，递归/迭代前中后序遍历，层序遍历，释放
 *
 * 文件目的：把常见基础算法做成清晰、可直接运行的示例，便于阅读理解。
 */

/* 交换两个整数（小工具）
 * 步骤：
 * 1. 保存 *a 到临时变量 t
 * 2. 将 *b 赋给 *a
 * 3. 将 t 赋回 *b
 */
static void swap_int(int *a, int *b) { int t = *a; *a = *b; *b = t; }

/*
 * 冒泡排序（Bubble Sort）
 * - 原地排序，稳定
 * - 时间复杂度：最坏 O(n^2)，最好 O(n)（若已有序）
 * - 优化：如果一趟没有交换则提前结束
 */
/*
 * 冒泡排序（Bubble Sort）逐步注释：
 * 外层 i 表示已经把末尾的 i 个元素放到正确位置，需做 n-1 次外循环
 * 内层 j 将相邻两个元素比较并使较大值向右 "冒泡"
 * 如果一轮内层没有发生交换（swapped == 0），说明数组已排序，可提前退出
 * 步骤示例：
 * 1. i 从 0 到 n-2
 * 2. 初始化 swapped = 0
 * 3. j 从 0 到 n-2-i：若 a[j] > a[j+1]，交换并置 swapped=1
 * 4. 若 swapped 为 0，跳出外层循环
 */
void bubble_sort(int *a, int n) {
    for (int i = 0; i < n-1; ++i) {
        int swapped = 0;
        for (int j = 0; j < n-1-i; ++j) {
            if (a[j] > a[j+1]) { swap_int(&a[j], &a[j+1]); swapped = 1; }
        }
        if (!swapped) break; /* 已有序，提前退出 */
    }
}

/*
 * 插入排序（Insertion Sort）
 * - 对于前半部分已排序的数组，将当前元素插入正确位置
 * - 稳定，最好 O(n)，平均/最坏 O(n^2)
 */
/*
 * 插入排序逐步注释：
 * 思路：把第 i 个元素插入到 [0..i-1] 已排序区间的合适位置
 * 步骤：
 * 1. 从 i=1 开始，取 key = a[i]
 * 2. 将 j 初始化为 i-1
 * 3. 向右移动比 key 大的元素（a[j] -> a[j+1]），直到找到插入位置
 * 4. 将 key 放到 a[j+1]
 */
void insertion_sort(int *a, int n) {
    for (int i = 1; i < n; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) { a[j+1] = a[j]; --j; }
        a[j+1] = key;
    }
}

/*
 * 顺序查找（线性查找）
 * - 未排序数组时使用，时间复杂度 O(n)
 * - 返回首次匹配的下标，未找到返回 -1
 */
/*
 * 线性查找逐步注释：
 * 1. 从索引 0 到 n-1 依次比较 a[i] 和 target
 * 2. 若相等则返回下标 i
 * 3. 若遍历结束仍未匹配，返回 -1
 */
int linear_search(int *a, int n, int target) {
    for (int i = 0; i < n; ++i) if (a[i] == target) return i;
    return -1;
}

/*
 * 折半查找（迭代版，Binary Search）
 * - 数组必须有序
 * - 时间复杂度 O(log n)
 */
/*
 * 折半查找（迭代）逐步注释：
 * 1. 维护闭区间 [l, r]
 * 2. 计算中点 m = l + (r-l)/2，比较 a[m] 与 target
 * 3. 若相等返回 m；若 a[m] < target 则将 l 移到 m+1；否则将 r 移到 m-1
 * 4. 当 l > r 时停止，表示未找到
 */
int binary_search_iter(int *a, int n, int target) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (a[m] == target) return m;
        else if (a[m] < target) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

/* 递归版折半查找 */
/* 递归版折半查找逐步注释：
 * 1. 若 l>r，返回 -1（区间为空）
 * 2. 计算 m，比较 a[m] 和 target
 * 3. 递归到左区间或右区间
 */
int binary_search_rec(int *a, int l, int r, int target) {
    if (l > r) return -1;
    int m = l + (r - l) / 2;
    if (a[m] == target) return m;
    if (a[m] < target) return binary_search_rec(a, m+1, r, target);
    return binary_search_rec(a, l, m-1, target);
}

/* 二叉树节点定义：简单整数值与左右指针 */
typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

/* 辅助：创建新节点 */
Node* newNode(int v) { Node *n = malloc(sizeof(Node)); n->val = v; n->left = n->right = NULL; return n; }

/* 递归遍历（经典实现）逐步说明：
 * - 前序（根-左-右）：先访问根，再递归左子树，再递归右子树
 * - 中序（左-根-右）：递归左子树，访问根，递归右子树
 * - 后序（左-右-根）：递归左子树，递归右子树，访问根
 */
void inorder(Node *r) { if (!r) return; inorder(r->left); printf("%d ", r->val); inorder(r->right); }
void preorder(Node *r) { if (!r) return; printf("%d ", r->val); preorder(r->left); preorder(r->right); }
void postorder(Node *r) { if (!r) return; postorder(r->left); postorder(r->right); printf("%d ", r->val); }

/* 迭代中序遍历（模拟递归的栈）
 * 原理：沿左子树入栈直到 NULL，然后弹栈访问并走右子树
 */
/* 迭代中序遍历逐步注释：
 * 1. 用指针 cur 从根开始
 * 2. 一直向左走并把路径节点入栈，直到 cur 为 NULL
 * 3. 弹栈节点并访问它，然后将 cur 指向该节点的右子树
 * 4. 重复直到栈空且 cur 为 NULL
 */
void inorder_iter(Node *root) {
    Node **stk = NULL; int cap = 0, top = 0; Node *cur = root;
    while (cur || top) {
        while (cur) {
            if (top >= cap) { cap = cap ? cap*2 : 16; stk = realloc(stk, cap*sizeof(Node*)); }
            stk[top++] = cur; cur = cur->left;
        }
        cur = stk[--top]; printf("%d ", cur->val); cur = cur->right;
    }
    free(stk);
}

/* 迭代前序遍历
 * 原理：使用栈，先 push 右子再左子，保证左子先被处理
 */
/* 迭代前序遍历逐步注释：
 * 1. 将根压栈
 * 2. 循环：弹栈访问当前节点
 * 3. 先压入右子，再压入左子（保证左子先被弹出访问）
 */
void preorder_iter(Node *root) {
    if (!root) return;
    int cap = 16, top = 0; Node **stk = malloc(cap * sizeof(Node*)); stk[top++] = root;
    while (top) {
        Node *n = stk[--top]; printf("%d ", n->val);
        if (n->right) { if (top >= cap) { cap *= 2; stk = realloc(stk, cap*sizeof(Node*)); } stk[top++] = n->right; }
        if (n->left) { if (top >= cap) { cap *= 2; stk = realloc(stk, cap*sizeof(Node*)); } stk[top++] = n->left; }
    }
    free(stk);
}

/* 迭代后序遍历（双栈法）
 * 原理：第一个栈按根右左入栈，弹出时推入第二栈，最后第二栈按顺序即为左右根
 */
/* 迭代后序遍历逐步注释（双栈法）：
 * 1. 将根压入栈 s1
 * 2. 循环：从 s1 弹出节点 n，推入 s2；将 n 的左、右子（若存在）压入 s1
 * 3. 最后按 s2 弹出顺序访问即为后序（左-右-根）
 */
void postorder_iter(Node *root) {
    if (!root) return;
    Node **s1 = NULL, **s2 = NULL; int c1=0,c2=0,cap1=0,cap2=0;
    if (c1 >= cap1) { cap1 = 16; s1 = realloc(s1, cap1*sizeof(Node*)); }
    s1[c1++] = root;
    while (c1) {
        Node *n = s1[--c1];
        if (c2 >= cap2) { cap2 = cap2?cap2*2:16; s2 = realloc(s2, cap2*sizeof(Node*)); }
        s2[c2++] = n;
        if (n->left) { if (c1 >= cap1) { cap1*=2; s1 = realloc(s1, cap1*sizeof(Node*)); } s1[c1++] = n->left; }
        if (n->right) { if (c1 >= cap1) { cap1*=2; s1 = realloc(s1, cap1*sizeof(Node*)); } s1[c1++] = n->right; }
    }
    while (c2) { printf("%d ", s2[--c2]->val); }
    free(s1); free(s2);
}

/* 层序遍历（宽度优先搜索，BFS）
 * 使用队列（数组模拟），按层从左到右访问
 */
/* 层序遍历逐步注释（队列实现）：
 * 1. 使用数组模拟队列，head 指向当前弹出位置，tail 指向下一个入队位置
 * 2. 将根入队
 * 3. 循环：出队节点 n，访问它；若 n 有左/右子则入队
 * 4. 直到队列空
 */
void level_order(Node *root) {
    if (!root) return;
    int cap = 16, h=0,t=0; Node **q = malloc(cap*sizeof(Node*)); q[t++] = root;
    while (h < t) {
        Node *n = q[h++];
        printf("%d ", n->val);
        if (n->left) { if (t>=cap){cap*=2;q=realloc(q,cap*sizeof(Node*));} q[t++]=n->left; }
        if (n->right){ if (t>=cap){cap*=2;q=realloc(q,cap*sizeof(Node*));} q[t++]=n->right; }
    }
    free(q);
}

/* 递归释放整棵树，避免内存泄漏 */
void freeTree(Node *r) { if (!r) return; freeTree(r->left); freeTree(r->right); free(r); }

/* ---------------- 演示 main ---------------- */
int main(void) {
    int a1[] = {5,2,9,1,5,6}; int n1 = sizeof(a1)/sizeof(a1[0]);
    int a2[6]; for (int i=0;i<n1;++i) a2[i]=a1[i];

    printf("原数组: "); for (int i=0;i<n1;++i) printf("%d ", a1[i]); printf("\n");
    bubble_sort(a1, n1);
    printf("冒泡排序: "); for (int i=0;i<n1;++i) printf("%d ", a1[i]); printf("\n");

    insertion_sort(a2, n1);
    printf("插入排序: "); for (int i=0;i<n1;++i) printf("%d ", a2[i]); printf("\n");

    int t = 5;
    printf("线性查找 %d: idx=%d\n", t, linear_search(a1, n1, t));
    printf("折半查找 %d: idx=%d\n", t, binary_search_iter(a1, n1, t));

    /* 构造测试二叉树（手动） */
    Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);

    printf("\n递归前序: "); preorder(root); printf("\n");
    printf("递归中序: "); inorder(root); printf("\n");
    printf("递归后序: "); postorder(root); printf("\n");

    printf("\n迭代前序: "); preorder_iter(root); printf("\n");
    printf("迭代中序: "); inorder_iter(root); printf("\n");
    printf("迭代后序: "); postorder_iter(root); printf("\n");
    printf("层序: "); level_order(root); printf("\n");

    freeTree(root);
    return 0;
}
