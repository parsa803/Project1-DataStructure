#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cctype>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

// Tree Nodes
struct TreeNode {
    string value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(const string& v) : value(v), left(nullptr), right(nullptr) {}
    ~TreeNode() {
        delete left;
        delete right;
    }
};