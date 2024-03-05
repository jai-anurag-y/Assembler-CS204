#include <bits/stdc++.h>
#include "lookup.cpp"
using namespace std;
#define ll long long int




string Rformat (vector <string> &instruction)
{
    // Validate instruction format
    if (instruction.size() != 4) {
        return "Invalid instruction format";
    }

    string opcode_temp = codes_map[instruction[0]][0];
    string func3_temp = codes_map[instruction[0]][1];
    string func7_temp = codes_map[instruction[0]][2];

    int opcode = stoi(opcode_temp, nullptr, 16);
    int func3 = stoi(func3_temp, nullptr, 16);
    int func7 = stoi(func7_temp, nullptr, 16);

    int rd = stoi(instruction[1].substr(1)); 
    int rs1 = stoi(instruction[2].substr(1)); 
    int rs2 = stoi(instruction[3].substr(1)); 

    ll machineCode = (func7 << 25) | (rs2 << 20) | (rs1 << 15) | (func3 << 12) | (rd << 7) | opcode;
    stringstream ss;
    ss << hex << "0x" << uppercase << std::setw(8) << std::setfill('0') << machineCode;
    
    cout << ss.str()<< endl;
    return ss.str(); 
}





string Iformat (vector <string> &instruction)
{
    // Validate instruction format
    if (instruction.size() != 4) {
        return "Invalid instruction format";
    }

    string opcode_temp = codes_map[instruction[0]][0];
    string func3_temp = codes_map[instruction[0]][1];


    int opcode = stoi(opcode_temp, nullptr, 16);
    int func3 = stoi(func3_temp, nullptr, 16);
    int rd = stoi(instruction[1].substr(1)); 
    int rs1 = stoi(instruction[2].substr(1));
    int imm;
    if (instruction[3][0] == '0' && (instruction[3][1] == 'x' || instruction[3][1] == 'X'))
        imm = stoi(instruction[3].substr(2), nullptr, 16);
    else
        imm = stoi(instruction[3]);


    ll machineCode = (imm << 20) | (rs1 << 15) | (rs1 << 15) | (func3 << 12) | (rd << 7) | opcode;
    stringstream ss;
    ss << hex << "0x" << uppercase << std::setw(8) << std::setfill('0') << machineCode;


    cout << ss.str()<< endl;
    return ss.str();
}





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

