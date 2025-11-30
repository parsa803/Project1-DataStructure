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

string normalizer(string s) {
    string out;

    for(int i=0;i<s.size();){
        if(isSign(s[i])){
            int j=i;
            while(j<s.size() && isSign(s[j])) 
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
                    if(s[k]=='-') 
                        c++;

                if(c%2==1) 
                    out.push_back('-');
            } else {
                int c=0;
                for(int k=i;k<j;k++) 
                    if(s[k]=='-') 
                        c++;
                if(c%2==1) 
                    out+="-";
                else 
                    out+="+";
            }
            i=j;
        }
        else{
            out.push_back(s[i]);
            i++;
        }
    }

    return out;
}

int main(){
    string user_input;
    getline(cin, user_input);
    user_input = normalizer(user_input);

    cout << user_input;
}