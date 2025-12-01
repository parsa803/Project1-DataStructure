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

bool isMul(char c){
    return c=='*' || c=='/';
}

string normalizer(string expr) {
    string out;
    string ans = "";

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

    for (int i = 0;i < out.size(); i++){
        if (out[i] != ' ')
        ans += out[i];
    }
    out = ans;
    ans = "";

    for (int i = 0;i < out.size();i++){
        if (out[i] == '(' && i != 0){
            if (!isSign(out[i-1]) && !isMul(out[i-1])){
                ans += '*';
                ans += '(';
            }
        }
        else if (out[i] == ')' && i != out.size()-1){
            if (out[i+1] != ')'){
                ans += ')';
            }
            else if (!isSign(out[i+1]) && !isMul(out[i+1])){
                ans += ')';
                ans += '*';
            }
        }
        else{
            ans += out[i];
        }
    }

    return ans;
}

void NegetiveSqrt(string s){
    for (int i = 0; i< s.size()-1;i++){
        if (s[i] == '√' and s[i+1] == '-'){
            throw runtime_error("No negative sqrts");
        }
    }
}

int main(){
    string user_input;
    getline(cin, user_input);
    user_input = normalizer(user_input);

    cout << user_input;
}