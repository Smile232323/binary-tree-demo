/*
 * 简单二叉搜索树（BST）实现示例
 * 支持：插入、删除、查找、中/前/后序遍历、释放内存
 * 演示在 main() 中构建并操作一棵小树
 */

#include <stdio.h>
#include <stdlib.h>

/* 节点定义：存储整数键和左右子节点指针 */
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

/* 创建并初始化新节点（O(1)） */
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

/* 按 BST 规则递归插入键（平均 O(h)）
   相同键将被忽略（不插入重复值） */
Node* insert(Node* root, int key) {
    if (root == NULL) return newNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root; /* 返回（可能未变）子树根 */
}

/* 中序遍历：左 - 根 - 右 （对 BST 输出升序） */
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

/* 前序遍历：根 - 左 - 右 */
void preorder(Node* root) {
    if (!root) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

/* 后序遍历：左 - 右 - 根 */
void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

/* 返回以 node 为根的子树中键最小的节点（最左节点） */
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left) current = current->left;
    return current;
}

/* 删除键为 key 的节点，返回删除后子树的根（平均 O(h)）
   处理三种情况：无子节点、一个子节点、两个子节点 */
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root; /* 空树 */
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        /* 找到待删除节点 */
        if (root->left == NULL) {
            Node* temp = root->right; /* 右子代顶替 */
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left; /* 左子代顶替 */
            free(root);
            return temp;
        }
        /* 两个子节点：用右子树的最小节点（中序后继）替换 */
        Node* temp = minValueNode(root->right);
        root->key = temp->key; /* 复制值 */
        root->right = deleteNode(root->right, temp->key); /* 删除后继节点 */
    }
    return root;
}

/* 在 BST 中查找 key，找到返回节点指针，未找到返回 NULL */
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

/* 递归释放整棵树的节点，避免内存泄漏 */
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
/* 示例：构建一棵树并演示插入、遍历、查找、删除 */
int main(void) {
    Node* root = NULL;
    int vals[] = {50, 30, 20, 40, 70, 60, 80};
    int n = sizeof(vals) / sizeof(vals[0]);
    for (int i = 0; i < n; ++i) root = insert(root, vals[i]);

    printf("Inorder: "); inorder(root); printf("\n"); /* 20 30 40 50 60 70 80 */
    printf("Preorder: "); preorder(root); printf("\n");
    printf("Postorder: "); postorder(root); printf("\n");

    int s = 40;
    printf("Search %d: %s\n", s, search(root, s) ? "found" : "not found");
    s = 100;
    printf("Search %d: %s\n", s, search(root, s) ? "found" : "not found");

    printf("\nDelete 20\n");
    root = deleteNode(root, 20);
    printf("Inorder: "); inorder(root); printf("\n");

    printf("Delete 30\n");
    root = deleteNode(root, 30);
    printf("Inorder: "); inorder(root); printf("\n");

    printf("Delete 50\n");
    root = deleteNode(root, 50);
    printf("Inorder: "); inorder(root); printf("\n");

    freeTree(root);
    return 0;
}
