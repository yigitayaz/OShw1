#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include "parser.h"
using namespace std;
typedef struct bundle{
    char* name;
    vector<vector<string> > commandWithArguments;
    int processCount;
}bundle;
int main(){
    parsed_input parsedInput;
    char buffer[256];
    vector<bundle> bundleVector;
    int bundleAmount = 0;
    int returnValue;
    int isBundleCreation= false;
    while(1) {
        cin.getline(buffer,256);
        int size = strlen(buffer);
        buffer[size] = '\n';
        buffer[size+1] = '\0';
        returnValue = parse(buffer, isBundleCreation, &parsedInput);

        if(isBundleCreation){
            if(returnValue){
                cout << "pbs received" << endl;
                isBundleCreation = false;
            }
            else{
                vector<string> temp;
                for(char**arg = parsedInput.argv; *arg; arg++) {
                    cout << "Argument:" << *arg << endl;
                    string s(*arg);
                    temp.push_back(s);
                }

                bundleVector.back().commandWithArguments.push_back(temp);
                cout << bundleVector.back().commandWithArguments.back().back() << endl;
                bundleVector.back().processCount++;
            }
        }
        else{
            if(parsedInput.command.type == PROCESS_BUNDLE_CREATE){
                cout << "Bundle execution has been started. Bundle Name:" << parsedInput.command.bundle_name << endl;
                isBundleCreation = true;
                bundle b;
                b.name = new char[sizeof(parsedInput.command.bundle_name)]();
                strcpy(b.name,parsedInput.command.bundle_name);
                b.processCount = 0;
                bundleAmount++;
                bundleVector.push_back(b);
            }
            else if(parsedInput.command.type == PROCESS_BUNDLE_EXECUTION){
                for(int  i =0; i< parsedInput.command.bundle_count; i++){
                    cout << "Command Name: " << parsedInput.command.bundles[i].name << endl;
                    vector<bundle >::iterator it;
                    for( it = bundleVector.begin(); it != bundleVector.end();++it){
                        if(!strcmp(it->name,parsedInput.command.bundles[i].name)){
                            int rv;
                            
                        }
                    }
                }
            }
            else if(parsedInput.command.type == PROCESS_BUNDLE_STOP){
                cout << "First create a bundle or bundles!" << endl;
            }
            else{
                cout << "Quit has been received" << endl;
                break;
            }
        }

    }
    return 0;
}