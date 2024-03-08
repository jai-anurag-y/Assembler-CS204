#include <bits/stdc++.h>
#include "format.cpp"
using namespace std;
#define ll long long int

int dataAddress = 0x10000000;
int pc = 0;



int main() {

    map<string,int> varmap;
    map<int,string> dataSegment;
    map<string,int> label;

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
                    if(tokens.size()!=3){
                        dataOutputFile<<"Error for "<<tokens[0]<<endl;
                        break;
                    }
                    varmap[tokens[0]] = dataAddress;
                    string s = tokens[2];
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
                }
            }

            
        }
    
        else{
            if(type_map.find(tokens[0])!=type_map.end())
            {
                char type = type_map[tokens[0]];
                switch(type){
                case 'r':
                    {
                        dataOutputFile<<"0x"<<std::hex<<pc<<" "<<Rformat(tokens)<<endl;
                        pc+=4;
                        break;
                    }
                case 'i':
                    {
                        dataOutputFile<<"0x"<<std::hex<<pc<<" "<<Iformat(tokens)<<endl;
                        pc+=4;
                        break;
                    }
                case 's':
                    {
                        dataOutputFile<<"0x"<<std::hex<<pc<<" "<<Sformat(tokens)<<endl;
                        pc+=4;
                        break;
                    }
                case 'b':
                    {
                        tokens[3]=to_string(label[tokens[3]]-pc);
                        dataOutputFile<<"0x"<<std::hex<<pc<<" "<<SBformat(tokens)<<endl;
                        pc+=4;
                        break;
                    }
                case 'u':
                    {
                        dataOutputFile<<"0x"<<std::hex<<pc<<" "<<Uformat(tokens)<<endl;
                        pc+=4;
                        break;
                    }
                case 'j':
                    {
                        tokens[2]=to_string(label[tokens[2]]-pc);
                        dataOutputFile<<"0x"<<std::hex<<pc<<" "<<UJformat(tokens)<<endl;
                        pc+=4;
                        break;
                    }    
                default:
                {
                    dataOutputFile<<"Error"<<endl;
                }
                }
            }
            else if(tokens.size()==1){
                tokens[0].pop_back();
                label[tokens[0]] = pc;
            }
        }
    }

    dataOutputFile<<endl<<"Data Segment"<<endl;

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

