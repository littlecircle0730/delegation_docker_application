#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main()
{
    // ifstream fJson("testRAM.json");
    // ifstream fJson("testOper.json");
    ifstream fJson("testIO.json");
    stringstream buffer;
    buffer << fJson.rdbuf();
    auto json = nlohmann::json::parse(buffer.str());



    string type = json["type"];
    string value = json["value"];
    cout << "\nType of instruction: " << type << "\n";
    cout << "\nValue of instruction: " << value << "\n";

    if(type=="RAM"){
        cout << "\nType is RAM\n";
        
        int size = std::stoi(value);

        size_t sz = size*10000000000; //we set size it in GB unit
        cout << sz << "\n";
        char *a = (char*)malloc(sz);
        memset(a, 'a', sz); // put 'a' into 4GB
        printf("%.4s", &a[sz-5]);
    }

    if(type=="Operation"){
        cout << "Type is Operation\n";

        string opeType = json["opeType"];
        
        int times = std::stoi(value);
        int n=1;

        for(int i=0; i<times; i++){
            cout << "the operation is: " << opeType << "\n";
            float f = static_cast <float> (remainder(rand(), 1000.0) + 1.0);
            // multiplication
            if(opeType=="add"){
                n+=f;
            }
            // substraction
            if(opeType=="sub"){
                n-=f;
            }
            // multiplication
            if(opeType=="mut"){
                n*=f;
            }
            // division
            if(opeType=="div"){
                n/=f;
            }
        }
    }

    if(type=="IO"){
        cout << "Type is IO\n";

        string ioType = json["IOType"];
        
        int times = std::stoi(value);
        int n=1;

        cout << "test for: " << ioType << "\n";

        
            // input a file
            if(ioType=="in"){
                string line;
                ifstream infile ("in.txt");
                if (infile.is_open())
                {
                    for(int i=0; i<times; i++){
                        (getline (infile,line));
                        // cout << line << '\n';
                    }
                    infile.close();
                }

                else cout << "Unable to open file"; 
            }
            // output a file
            if(ioType=="out"){
                ofstream outfile ("out.txt");
                if (outfile.is_open())
                {
                    for(int i=0; i<times; i++){
                        outfile << "This is a line.\n";
                    }
                    outfile.close();
                }
                else cout << "Unable to open file";
            }
    }   

    return 0;
}

