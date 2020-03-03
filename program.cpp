//
//  program.cpp
//
//  Created by Risha Shah
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "list_tokens.h"
#include "gettoken.h"
#include "parse.h"
#include "parse_tree.h"

using namespace std;
int line = 0;
istream *input = &cin;
ifstream inFile;

int main(int argc, const char * argv[]) {
    
    for(int i =1; i<argc; i++){
        
        string vari(argv[i]);
        
            if (i == argc-1){
            
            inFile.open(vari);
            
            if( inFile.is_open() == false ) {
                cerr << "COULD NOT OPEN "<< vari << endl;
                return -1;
            }
            input = &inFile;
        }
        
        else{
            
            cerr << "TOO MANY FILENAMES" <<endl;
            return -1;
        }
        
        
        
    }
    
     ParseTree *tree = Prog(*input,line);
    if(tree ==0){
    //null 
    
    }
    
    if(tree !=0){
        //traverse tree 
        
        if(tree->NodeCount()!= 0){ 
        cout<<"NODE COUNT: " << tree->NodeCount()<<endl;
        }
        
        if((tree->NodeCount()- tree->leaves())!= 0){ 
        cout<<"INTERIOR COUNT: " << (tree->NodeCount()- tree->leaves())<< endl;
        }
        
        if(tree->ops()!= 0){ 
        cout<<"OPS COUNT: " << tree->ops()<<endl;
        }
        
        if(tree->strings()!= 0){ 
        cout<<"STRING COUNT: " << tree->strings()<<endl;
        }
        
        if(tree->maxdepth()!= 0){ 
        cout<<"MAX DEPTH: " << tree->maxdepth()<<endl;
        }
       
    }
 
   
    return 0;
}
