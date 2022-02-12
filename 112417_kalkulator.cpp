#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int to_int(string s){
    int a = 1;
    if (s[0] == '-'){
        a = -1;
        s = s.substr(1, s.size() - 1);
    }
    int res = 0;
    for (int i = 0; i < s.size(); i++){
        res *= 10;
        res += s[i] - '0';
    }
    return res * a;
}

string to_str(int x){
    int f = 0;
    if (x < 0){
        x *= -1;
        f = 1;
    }
    string s;
    while(x){
        s += x % 10 + '0';
        x /= 10;
    }
    reverse(s.begin(), s.end());
    if (f == 0)
        return s;
    else
        return "-" + s;
}

string parse(string s){
    vector <string> tokens;
    string operations = "*/+-";
    for (int i = 0; i < s.size(); i++){
        if (operations.find(s[i]) != string::npos or i == 0){
            if (s[i] != '(' and !isdigit(s[i])) tokens.push_back(s.substr(i, 1));
            int k = i + 1, balance = 0;
            if (s[i] == '(') balance++;
            for (k; k < s.size(); k++){
                if (s[k] == '(') balance++;
                if (s[k] == ')') balance--;
                if (operations.find(s[k]) != string::npos and balance == 0){
                    break;
                }
            }
            if (s[i] == '(' or isdigit(s[i])) tokens.push_back(s.substr(i, k - i));
            else tokens.push_back(s.substr(i + 1, k - i - 1));
            i = k - 1;
        }
    }

//    for (int i = 0; i < tokens.size(); i++){
//        cout << tokens[i] << " ";
//    }
//    cout << endl;

    for (int i = 0; i < tokens.size(); i++){
        if (tokens[i][0] == '('){
            tokens[i] = parse(tokens[i].substr(1, tokens[i].size() - 2));
        }
    }

    int res = 0;
    int k = 0;
    auto iter = tokens.cbegin();
    for (int i = 0; i < tokens.size(); i++){
        if (tokens[i] == "*"){
            k = to_int(tokens[i - 1]) * to_int(tokens[i + 1]);
            tokens.erase(iter + i - 1, iter + i + 2);
            tokens.insert(iter + i - 1, to_str(k));
            i--;
        }
        else if (tokens[i] == "/"){
            k = to_int(tokens[i - 1]) / to_int(tokens[i + 1]);
            tokens.erase(iter + i - 1, iter + i + 2);
            tokens.insert(iter + i - 1, to_str(k));
            i--;
        }
    }

    for (int i = 0; i < tokens.size(); i++){
        if (tokens[i] == "+"){
            k = to_int(tokens[i - 1]) + to_int(tokens[i + 1]);
            tokens.erase(iter + i - 1, iter + i + 2);
            tokens.insert(iter + i - 1, to_str(k));
            i--;
        }
        else if (tokens[i] == "-"){
            k = to_int(tokens[i - 1]) - to_int(tokens[i + 1]);
            tokens.erase(iter + i - 1, iter + i + 2);
            tokens.insert(iter + i - 1, to_str(k));
            i--;
        }
    }
    return tokens[0];
}


int main(){
    string s;
    cin >> s;
    string k = parse(s);
    cout << to_int(k);
}
