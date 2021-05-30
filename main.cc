#include <iostream>

using namespace std;

//******************************************DONT WORRY ABOUT ANYTHING HERE, ITS JUST DATASTRUCTURES AND CONSTRUCTORS****


//---------my defined data types----------
typedef unsigned long int cnt;
typedef long int nat;

//----------------enums------------
enum log_t {error, success, info,check};
//---------------------------------


//---------this is the data structure of the code  named code-----------
struct code 
{
    /* data */
    string name; //name of the file
    string content; //contents of the file
    int coppies; //number of coppies
    cnt size;  //size of file
    
    struct{ // this contains information ablut the variables
        string* name; //names of vaiables wouldd be containedd here
        nat* location; //same with location of the variables in the file  ---p.s is a multidimentinal array
        string* catched; // this would store all the generated varables

    }var;

}code;
//-----------------------------------------------------------------

class utils{

    public:
        void getLocalFiles();//its to get all files in the directory  that it is run //then asks you to choose the file number // then returns the file name

        void getNumberOfCoppies();//its to ask the user the number of coppies he waint of the code

        void log(log_t type, string message); //its to log current progress
}utils;

class logic{
    public:
        string* keywords; // where we input new keywords;
        logic();
        void findVariables();//runs a search through the string across all the standard varraible keywords we set; and then retruns the values to *var_name and where it wasa found to *var_adr

        void replaceNewVars();//now replacese the old vars with the new stuff 


        string autoSuggestVars (string var); // suggest a suitable name for the varibvle and returns it, and catcches it to prevent repetation
}logic;

class files : private logic{
    public:
        void readFiletoString(); //it reads the file and returns it as a sting

        bool writeToNewFile();//wtrites it back to a new file
}files;


//*********************************************************************************
int main(){

    // ------------
    utils.getLocalFiles();
    files.readFiletoString();
    utils.getNumberOfCoppies(); 
    for (cnt i = 0; i < code.coppies; i++)
    {
        logic.findVariables();
        logic.replaceNewVars();
        if(files.writeToNewFile()){
            //success statement;
        }else{
            //error statement
        }
    }
}

//--------------START BUILDING HERE---------------

//-------core-----------
logic::logic(){
    string str_var[100] ={"int","string", "long", "double"}; //were to complete this list 
    keywords = str_var;

}
void utils::getLocalFiles(){

}
void files::readFiletoString(){

}
void utils::getNumberOfCoppies(){

}
void logic::findVariables(){


}
string logic::autoSuggestVars(string var){

}
void logic::replaceNewVars(){

}
bool files::writeToNewFile(){

}
//--------------------------
void utils::log(log_t type, string message){

}
