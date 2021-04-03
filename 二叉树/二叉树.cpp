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
    void PreNode(bool output = false) {
        List.clear();
        PreNode(Node, output);
    }
    void InNode(bool output = false) {
        List.clear();
        InNode(Node, output);
    }
    void PostNode(bool output = false) {
        List.clear();
        PostNode(Node, output);
    }
    void DeleteNode(int key) {
        DeleteNode(Node, key);
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
            root->right = nullptr;*/
            return;
        }
        if (data < root->val)
            PreInsertNode(root->left, data);
        else
            PreInsertNode(root->right, data);
    }

    // 通过先序遍历删除对应参数
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
    binaryTree.PreNode(true);
    cout << endl;
    binaryTree.InNode(true);
    cout << endl;
    binaryTree.PostNode(false);
    for (int i = 0; i < binaryTree.List.size(); i++)
        cout << binaryTree.List[i]->val << " ";
    cout << endl;
    binaryTree.DeleteNode(5);
    binaryTree.InNode(true);
}
