#include <bits/stdc++.h>
#include "format.cpp"
using namespace std;
#define ll long long int

int dataAddress = 0x10000000;



int main() {

    map<string,int> varmap;
    map<int,string> dataSegment;

    ifstream inputFile("ex.asm");
    ofstream dataOutputFile("output_data.mc");
    ofstream dataTokenFile("output_token.mc");
    string line;
    int flag=0;

    while (getline(inputFile, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        stringstream ss(line);
        vector<string> tokens;
        string token,temp;
        while (ss >> token) {
            for(char c: token){
                if(c==','){
                    tokens.push_back(temp);
                    dataTokenFile<<temp<<endl;
                    temp="";
                }else{
                    temp+=c;
                }     
            }
            if(!temp.empty()){
                tokens.push_back(temp);
                dataTokenFile<<temp<<endl;
            }
            temp="";
        }





        if (tokens[0] == ".text") 
        {
            flag=0;
            continue;
        } 
        else if (tokens[0] == ".data") 
        {
            flag=1;
            continue;
        }

        if(flag)
        {
            tokens[0].pop_back();
            if (tokens[1][0] == '.') 
            {    
                if(datatype_map.find(tokens[1])!=datatype_map.end())
                {
                    varmap[tokens[0]] = dataAddress;
                    int i=2;
                    string s = tokens[i];
                    while(i!=tokens.size())
                    {
                        dataSegment[dataAddress] = s;
                        dataAddress += datatype_map[tokens[1]];
                        i++;
                        if(i!=tokens.size()){
                            s=tokens[i];
                        }
                        
                    }   
                }
                else if(tokens[1] == ".asciiz")
                {
                    varmap[tokens[0]] = dataAddress;
                    int i=2,a=tokens.size();
                    string s = tokens[i];
                    while(i<a)
                    {
                        for (char c : s) 
                        {
                            if(c=='"'){
                                continue;
                            }
                            dataSegment[dataAddress] = c;
                            dataAddress += 1;
                        }
                        dataSegment[dataAddress] = "0";
                        dataAddress += 1;
                        i++;
                        if(i!=a){
                            s=tokens[i];
                        }
                    }
                }
            }

            
        }
    }

    for(auto it: dataSegment)
    {
        dataOutputFile<<"0x"<<std::hex<<it.first<<" "<<it.second<<endl;
    }

    // for(auto it: varmap)
    // {
    //     dataOutputFile<<it.first<<" "<<std::hex<<it.second<<endl;
    // }

    inputFile.close();
    dataOutputFile.close();
    dataTokenFile.close();

    return 0;
}
