#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class BinaryTree
{
public:
    TreeNode* Node;
    vector<TreeNode*> List;

    BinaryTree() {
        Node = nullptr;
    }
    void PreInsertNode(int data) {
        PreInsertNode(Node, data);
    }
    vector<TreeNode*> PreNode(bool output = false) {
        List.clear();
        PreNode(Node, output);
        return List;
    }
    vector<TreeNode*> InNode(bool output = false) {
        List.clear();
        InNode(Node, output);
        return List;
    }
    vector<TreeNode*> PostNode(bool output = false) {
        List.clear();
        PostNode(Node, output);
        return List;
    }
    // 删除后从左边找最右边的（比删除的小的）或者右边最左的（比删除的大的替换）
    void DeleteNode(int key) {
        if (Node == nullptr)
            return;
        TreeNode* keyNode = FindNode(Node, key);        // 要移出的点
        if (keyNode == nullptr)
            return;
        TreeNode* lastNode = keyNode;                   // 用于替换的上一个节点
        TreeNode* moveNode = keyNode;                   // 移动这个去替换
        if (keyNode->left) {
            moveNode = MaxNode(keyNode->left, &lastNode);   // 取左边最大值替换
            lastNode->right = moveNode->left;
            lastNode->left = nullptr;
        } else if (keyNode->right) {
            moveNode = MinNode(keyNode->right, &lastNode);  // 取右边最小值替换
            lastNode->left = moveNode->right;
            lastNode->right = nullptr;
        }
        // 如果替换的是首地址，则需要替换
        if (keyNode == Node) {
            Node = moveNode;
        }

        keyNode->val = moveNode->val;
        delete moveNode;
        InNode(false);   // 刷新链表
    }
    int MinNode() {
        return MinNode(Node)->val;
    }
    int MaxNode() {
        return MaxNode(Node)->val;
    }
    // 给定二叉树，先序和中序遍历结果，求出二叉树实际树结构
    TreeNode* BuildTree(vector<int>& preorder, vector<int>& inorder) {
        return BuildTree(preorder, inorder, 0, 0, inorder.size() - 1);
    }

    TreeNode* BuildTree(vector<int>& preorder, vector<int>& inorder, int root, int start, int end) {// 中序的start和end
        if (start > end) return NULL;
        TreeNode* tree = new TreeNode(preorder[root]);
        int i = start;
        while (i < end && preorder[root] != inorder[i]) i++;
        tree->left = BuildTree(preorder, inorder, root + 1, start, i - 1);
        tree->right = BuildTree(preorder, inorder, root + 1 + i - start, i + 1, end);
        return tree;
    }
    // 前序遍历，递归
    void PreNode(TreeNode* root, bool output = false) {
        if (root == nullptr)
            return;
        if (output)
            cout << root->val << " ";
        else
            List.push_back(root);
        PreNode(root->left, output);
        PreNode(root->right, output);
    }
    // 中序遍历，递归
    void InNode(TreeNode* root, bool output = false) {
        if (root == nullptr)
            return;
        InNode(root->left, output);
        if (output)
            cout << root->val << " ";
        else
            List.push_back(root);
        InNode(root->right, output);
    }
    // 后序遍历，递归
    void PostNode(TreeNode* root, bool output = false) {
        if (root != nullptr) {
            PostNode(root->left, output);
            PostNode(root->right, output);
            if (output)
                cout << root->val << " ";
            else
                List.push_back(root);
        }
    }
    // 先序插入二叉树
    void PreInsertNode(TreeNode* &root, int data) {
        if (root == nullptr) {
            root = new TreeNode(data);
            /*root = (TreeNode*)malloc(sizeof(TreeNode));     // new TreeNode(data);
            root->val = data;
            root->left = nullptr;
            root->right = nullptr; /**/
            return;
        }
        if (data < root->val)
            PreInsertNode(root->left, data);
        else
            PreInsertNode(root->right, data);
    }

    TreeNode* FindNode(TreeNode* root, int key) {
        if (root == nullptr || root->val == key)
            return root;
        if (root->val > key) {
            return FindNode(root->left, key);
        } else {
            return FindNode(root->right, key);
        }
        return nullptr;
    }
    TreeNode* MinNode(TreeNode* node) {
        if (node->left == nullptr)
            return node;
        return MinNode(node->left);
    }
    TreeNode* MinNode(TreeNode* node, TreeNode** lastNode) {
        if (node->left == nullptr)
            return node;
        *lastNode = node;
        return MinNode(node->left);
    }
    TreeNode* MaxNode(TreeNode* node) {
        if (node->right == nullptr)
            return node;
        return MaxNode(node->right);
    }
    TreeNode* MaxNode(TreeNode* node, TreeNode** lastNode) {
        if (node->right == nullptr)
            return node;
        *lastNode = node;
        return MaxNode(node->right);
    }

    // 通过先序遍历删除对应参数，这个删除头会有bug，于是仅供参考
    TreeNode* DeleteNode(TreeNode* root, int key) {
        if (!root)
            return nullptr;
        if (root->val == key) {
            if (root->left) {
                TreeNode* node = root->left;
                while (node->right) // 从删除结点的左节点开始往右找，找到右边为空的来替换原来的位置（取左边最大值替换）
                    node = node->right;
                node->right = root->right;
                return root->left;
            }
            return root->right;
        }
        if (root->val > key)
            root->left = DeleteNode(root->left, key);
        else
            root->right = DeleteNode(root->right, key);
        return root;
    }
};
int main()
{
    BinaryTree binaryTree;
    binaryTree.PreInsertNode(5);
    binaryTree.PreInsertNode(3);
    binaryTree.PreInsertNode(6);
    binaryTree.PreInsertNode(4);
    binaryTree.PreInsertNode(2);
    binaryTree.PreInsertNode(7);
    binaryTree.PreInsertNode(7);
    binaryTree.PreInsertNode(7);
    binaryTree.PreInsertNode(7);
    binaryTree.PreInsertNode(7);
    binaryTree.PreInsertNode(7);

    binaryTree.PreNode(true);
    cout << endl;
    binaryTree.InNode(true);
    cout << endl;
    binaryTree.PostNode(false);
    for (int i = 0; i < binaryTree.List.size(); i++)
        cout << binaryTree.List[i]->val << " ";
    cout << endl;
    cout << "Min " << binaryTree.MinNode() << endl;
    binaryTree.DeleteNode(7);
    binaryTree.InNode(true);
}
