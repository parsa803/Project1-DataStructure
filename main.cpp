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


// throw an error if the number under a sqrt is negetave !( does not work if the answer under it is negative --> √5-6 )!
void NegetiveSqrt(string s){
    for (int i = 0; i< s.size()-1;i++){
        if (s[i] == '√' and s[i+1] == '-'){
            throw runtime_error("No negative sqrts");
        }
    }
}


// Normalizer --> Correct user input
string normalizer(string expr) {
    auto isSign = [](char c) {
        return ( c == '+' || c == '-');
    };
    auto isMul = [] (char c){
        return (c == '*' || c == '/');
    };
    string out = "";
    string ans = "";

    // this part removes every extra operands in a cluster of '+'s and '-'s
    for(int i = 0; i < expr.size();) {
        if(isSign(expr[i])) {
            int j = i;
            while(j < expr.size() && isSign(expr[j])) j++;

            bool bol = false;
            int p = out.size() - 1;

            while(p >= 0 && out[p] == ' ') p--;

            if(p < 0 || out[p] == '(') bol = true;

            if(bol) {
                int c = 0;
                for(int k = i; k < j; k++)   
                    if(expr[k] == '-') c++;

                if(c%2==1) out.push_back('-');
            } 
            else {
                int c = 0;
                for(int k = i; k < j; k++) 
                    if(expr[k] == '-') c++;
                if(c%2==1) 
                    out+="-";
                else 
                    out+="+";
            }
            i = j;
        }
        else {
            out.push_back(expr[i]);
            i++;
        }
    }
    
    // this part removes every spaces in the input " "
    for (int i = 0;i < out.size(); i++){
        if (out[i] != ' ')
        ans += out[i];
    }
    
    out = ans;
    ans = "";

    // this part adds '*' behind '(' that do not have an operand behind them and after ')' that doesn't have an operand after them
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



// Tokenizer
vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    string token;
    for (int i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (isspace(c)) continue;

        if (isdigit(c)) { // integer float
            token = "";
            while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.')) {
                token += expr[i++];
            }
            --i;
            tokens.push_back(token);
        }
        else if (isalpha(c)) { // var
            token = "";
            while (i < expr.size() && (isalnum(expr[i]) || expr[i] == '_')) {
                token += expr[i++];
            }
            --i;
            tokens.push_back(token);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')' || c == '√') { // operand
            tokens.push_back(string(1, c));
        }
        else {
            throw runtime_error("Invalid character: " + string(1, c)); // error for invalid char like # @
        }
    }
    return tokens; // return a vector for use in tree  
}

int main(){
    string user_input;
    getline(cin, user_input);
    user_input = normalizer(user_input);
    vector<string>tokens = tokenize(user_input);
    cout << user_input << endl;
    for (int i = 0; i < tokens.size(); i++) cout << tokens[i] << " ";
}
