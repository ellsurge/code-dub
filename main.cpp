#include <iostream>
#include <array>

using namespace std;

class utils{
    public:
     string getLocalFiles(){
         //its to get all files in the directory  that it is run
         //then asks you to choose the file number 
         // then returns the file name
     }
     int getNumberOfCoppies(){
         //its to ask the user the number of coppies he waint of the code
    }
    
};
class files{
    public:
    string readFiletoString(string filename){
        //it reads the file and returns it as a sting

    }
    void findVariables(string Filetext){


    }
};

int main(){
    utils utils;
    files files;
    
    string filename = utils.getLocalFiles();
    int NOC = utils.getNumberOfCoppies();
    string fileContent= files.readFiletoString(filename);





    return 0; 
}