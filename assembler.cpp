#include <bits/stdc++.h>
using namespace std;
#define ll long long int


int main() {
    ifstream inputFile("ex.asm");
    ofstream dataTokenFile("output_token.mc");
    string line;

    while (getline(inputFile, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        stringstream ss(line);
        vector<string> tokens;
        string token;
        int a;
        while (ss >> token) {
            a = token.size()-1;
            if(token[a]==','){
                token.pop_back();
            }
            tokens.push_back(token);
            dataTokenFile<<token<<endl;
        }
     }

     inputFile.close();
     dataTokenFile.close();

    return 0;
}

