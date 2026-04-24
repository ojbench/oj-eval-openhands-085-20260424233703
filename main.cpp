
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Forward declarations
void deleteTree(TreeNode* root);

// Build tree from extended preorder traversal
TreeNode* buildTree(vector<int>& values, int& index) {
    if (index >= static_cast<int>(values.size())) {
        return nullptr;
    }
    
    int val = values[index];
    index++;
    
    if (val == -1) {
        return nullptr;
    }
    
    TreeNode* node = new TreeNode(val);
    node->left = buildTree(values, index);
    node->right = buildTree(values, index);
    
    return node;
}

// Check if subtree contains any node with value 1
bool containsOne(TreeNode* root) {
    if (root == nullptr) {
        return false;
    }
    if (root->val == 1) {
        return true;
    }
    return containsOne(root->left) || containsOne(root->right);
}

// Prune subtrees that don't contain any node with value 1
TreeNode* pruneTree(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    
    // Recursively prune children first
    root->left = pruneTree(root->left);
    root->right = pruneTree(root->right);
    
    // If current subtree doesn't contain any 1, prune it
    if (!containsOne(root)) {
        deleteTree(root);
        return nullptr;
    }
    
    return root;
}

// Delete entire tree to prevent memory leaks
void deleteTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Generate extended preorder traversal
void preorderTraversal(TreeNode* root, vector<int>& result) {
    if (root == nullptr) {
        result.push_back(-1);
        return;
    }
    
    result.push_back(root->val);
    preorderTraversal(root->left, result);
    preorderTraversal(root->right, result);
}

int main() {
    vector<int> values;
    int num;
    
    // Read input until -2 is encountered
    while (cin >> num) {
        if (num == -2) {
            break;
        }
        values.push_back(num);
    }
    
    if (values.empty()) {
        cout << "-1" << endl;
        return 0;
    }
    
    // Build tree
    int index = 0;
    TreeNode* root = buildTree(values, index);
    
    // Prune tree
    root = pruneTree(root);
    
    // Generate output
    vector<int> result;
    preorderTraversal(root, result);
    
    // Output result (don't remove trailing -1s, keep full extended preorder)
    for (size_t i = 0; i < result.size(); i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;
    
    // Clean up memory
    deleteTree(root);
    
    return 0;
}
