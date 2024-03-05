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
    int flag = 0;
    if (instruction.size() != 4) {
        vector <string> temp = {"lb", "ld", "lh", "lw"};
        if (instruction.size() == 3 && find(temp.begin(),temp.end(),instruction[0])!=temp.end())
            flag = 1;
        else
            return "Invalid instruction format";
    }

    string opcode_temp = codes_map[instruction[0]][0];
    string func3_temp = codes_map[instruction[0]][1];


    int opcode = stoi(opcode_temp, nullptr, 16);
    int func3 = stoi(func3_temp, nullptr, 16);
    int rd = stoi(instruction[1].substr(1));
    int imm, rs1;

    
    if (!flag)
    {   
        rs1 = stoi(instruction[2].substr(1));
        if (instruction[3][0] == '0' && (instruction[3][1] == 'x' || instruction[3][1] == 'X'))
            imm = stoi(instruction[3].substr(2), nullptr, 16);
        else
            imm = stoi(instruction[3]);
    }
    else
    {
        string str = instruction[2];
        size_t start_pos = str.find('(');
        size_t end_pos = str.find(')');


        string imm_str = str.substr(0,start_pos);
        if (imm_str[0] == '0' && (imm_str[1] == 'x' || imm_str[1] == 'X'))
            imm = stoi(imm_str.substr(2), nullptr, 16);
        else
            imm = stoi(imm_str);
        

        rs1 = stoi((str.substr(start_pos+1,end_pos - start_pos -1)).substr(1));
    }


    ll machineCode = (imm << 20) | (rs1 << 15) | (rs1 << 15) | (func3 << 12) | (rd << 7) | opcode;
    stringstream ss;
    ss << hex << "0x" << uppercase << std::setw(8) << std::setfill('0') << machineCode;


    cout << ss.str()<< endl;
    return ss.str();
}





string Sformat (vector <string> &instruction)
{
    if (instruction.size() != 3)
        return "Invalid instruction format";

    string opcode_temp = codes_map[instruction[0]][0];
    string func3_temp = codes_map[instruction[0]][1];


    int opcode = stoi(opcode_temp, nullptr, 16);
    int func3 = stoi(func3_temp, nullptr, 16);
    int rs2 = stoi(instruction[1].substr(1));
    int imm, rs1;


    string str = instruction[2];
    size_t start_pos = str.find('(');
    size_t end_pos = str.find(')');


    string imm_str = str.substr(0,start_pos);
    if (imm_str[0] == '0' && (imm_str[1] == 'x' || imm_str[1] == 'X'))
        imm = stoi(imm_str.substr(2), nullptr, 16);
    else
        imm = stoi(imm_str);
    int imm1,imm2;
    imm1 = (imm>>5) & 127;
    imm2 = (imm) & 31;

    rs1 = stoi((str.substr(start_pos+1,end_pos - start_pos -1)).substr(1));


    ll machineCode = (imm1 << 25) | (rs2 << 20) | (rs1 << 15) | (func3 << 12) | (imm2 << 7) | opcode;
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

