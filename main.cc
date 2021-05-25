#include <iostream>

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
        void getNames(string *name_list){
            //assigns the names it gests to the name array
        }

    
};
class logic{
    private:
        string keywords[200]; // we need to fill this to the max;


        void findVariables(string Filetext, string* var_name, int* var_adr){
            //runs a search through the string across all the standard varraible keywords we set;

            //and then retruns the values to *var_name and where it wasa found to *var_adr

        }
        void replaceNewVars(string &Filetext, string* var_name, int* var_adr)
        {
            //now replacese the old vars with the new stuff 
        }

    public:
        string autoSudgestname (string var, string* var_catch){
            // sudgestss a suitable name for the varibvle and returns it, and catcches it to prevent repetation

        }

};
class files : private logic{
    public:
        string readFiletoString(string filename){
            //it reads the file and returns it as a sting

        }
        bool writeToNewFile(string Filetext){
            //wtrites it back to a new file

        }

    
};

int main(){
    // class initializations--------------------
    utils utils;
    files files;
    logic logic;
    
    //setting upp constants ------------
    const string filename = utils.getLocalFiles();
    const string fileContent= files.readFiletoString(filename);

    const int NOC = utils.getNumberOfCoppies();
    const unsigned long int file_size = fileContent.length(); 
    
    //inintializing the variable arrays -----------------------------------
    string name_list[NOC];
    string var_name[file_size];  //where the variable names would  be stored
    int var_adrr[file_size][file_size]; //where the location of the variable in the file would be stored
    string var_catch[file_size*NOC]; //array where all the generated names would be cathched


    //
    /* code starts here




    */

}