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
bool isSign(char c){
    return c=='+' || c=='-';
}

string normalizer(string expr) {
    string out;

    for(int i=0;i<expr.size();){
        if(isSign(expr[i])){
            int j=i;
            while(j<expr.size() && isSign(expr[j])) 
                j++;

            bool bol = false;
            int p = out.size()-1;

            while(p>=0 && out[p]==' ') 
                p--;

            if(p<0 || out[p]=='(') 
                bol = true;

            if(bol){
                int c=0;
                for(int k=i;k<j;k++)   
                    if(expr[k]=='-') 
                        c++;

                if(c%2==1) 
                    out.push_back('-');
            } else {
                int c=0;
                for(int k=i;k<j;k++) 
                    if(expr[k]=='-') 
                        c++;
                if(c%2==1) 
                    out+="-";
                else 
                    out+="+";
            }
            i=j;
        }
        else{
            out.push_back(expr[i]);
            i++;
        }
    }

    return out;
}

// Tokenizer
vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    string token;
    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (isspace(c)) continue;

        if (isdigit(c) || c == '.') {
            token = "";
            while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.')) {
                token += expr[i++];
            }
            --i;
            tokens.push_back(token);
        }
        else if (isalpha(c)) {
            token = "";
            while (i < expr.size() && (isalnum(expr[i]) || expr[i] == '_')) {
                token += expr[i++];
            }
            --i;
            tokens.push_back(token);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')' || c == '√') {
            tokens.push_back(string(1, c));
        }
        else {
            throw runtime_error("Invalid character: " + string(1, c));
        }
    }
    return tokens;
}

int main(){
    string user_input;
    getline(cin, user_input);
    user_input = normalizer(user_input);
    vector<string>tokens = tokenize(user_input);
    cout << user_input << endl;
    for (int i = 0; i < tokens.size(); i++) cout << tokens[i] << " ";
}
