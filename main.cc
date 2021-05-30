//////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////////*NOTE :  COMPILE USING THE CPP11 STANDARD*////////
//////////////////g++ main -std=c++11/////////////////////
/////////////////////////////////////////////////////////




#include <iostream>
#include <sstream>  //to use string streamm to fix a bug i was getting getlocalfiles
#include <filesystem> // for file sysyem stuff
#include <fstream> //for reading and writing the file

using namespace std;
namespace fs = filesystem;

//******************************************DONT WORRY ABOUT ANYTHING HERE, ITS JUST DATASTRUCTURES AND CONSTRUCTORS****


//---------my defined data types----------
typedef unsigned long int cnt;
typedef long int nat;

//----------------enums------------
enum log_t {error,check, success, info};
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

        void input(int& out);
       
        void log(log_t type, string message); //its to log current progress
}utils;

class logic :public utils{
    public:
        string* keywords; // where we input new keywords;
        logic();
        void findVariables();//runs a search through the string across all the standard varraible keywords we set; and then retruns the values to *var_name and where it wasa found to *var_adr

        void replaceNewVars();//now replacese the old vars with the new stuff 


        string autoSuggestVars (string var); // suggest a suitable name for the varibvle and returns it, and catcches it to prevent repetation
}logic;

class files : private logic {
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
    string *filearr;      // a pointer to where the flies would be stored
    string path = "./";  //the path is set to current directory
    int i,maxx = 0,count = 0;

    cout<<"Welcome, please select the file you want to dub"<<endl;

    for(auto &nn :fs::directory_iterator(path)){  //this gets the number of files in the dir and stores it to max
         maxx +=1;
     }


    filearr = new (nothrow) string[maxx+1]; // creates a new array with the size of the dir
    if(filearr  == 0){ //error check
        log(error, "did not assign memory");
    }else{
        

        for(auto & fd : fs::directory_iterator(path)){ //loops throgh the dir

            filearr[count] = fd.path().string();
            cout<<count+1<<": "<<fd.path()<<endl;
            count += 1;
        }
        stage_1:
        input(i);
        if(i <= maxx and i>0 ){

            code.name = filearr[i-1]; //sets value of file name
            string message = "you've selected: "+filearr[i-1];
            log(info, message);  //logs out the current progress

        }else {
            log(error, "you selected an invalid number try again");
            goto stage_1;
        }
    }
}
void files::readFiletoString(){
    int count=0;
    string temp_file_dump;
    log(info, "loading file, please wait");
    t_lf:
    count++;
    ifstream thefile(code.name);
    if(thefile.is_open()){
        log(success, "file loaded successfully");
        log(info, "attepting to read file");
        while(! thefile.eof()){
            getline(thefile, temp_file_dump);
            code.content += temp_file_dump+"\n";

            //wait
        }
        log(success, "file read succesfully");

    }else ///error handling 
    {
        string message = "failed to load file, trying again";
        log(error, message);
        if(count <2){goto t_lf;}else
        {
            log(error, "sorry could not load file, try another file maybe");
            getLocalFiles();
            readFiletoString();
        }
    }




}
void utils::getNumberOfCoppies(){
    int num;
    cout<<"\n Enter number of coppies ";
    input_2:
    input(num);
    if(num <1){
        log(error, "number is too low, try again");
        goto input_2;
    }else{
        log(info, "registering the number of copies");
        int et=0;
        t_reg_coppies:
        et +=1;
        if(code.coppies = num){
            log(success, "number of copppies registerd succesfully");
        }else{
            log(error, "entry failed  trying again");
            if(et <5){goto t_reg_coppies;}
        }
    }

}
void logic::findVariables(){
    log(info, "sanning file ...");


}
string logic::autoSuggestVars(string var){

}
void logic::replaceNewVars(){

}
bool files::writeToNewFile(){

}
//--------------------------


void utils::log(log_t type, string message){
    if (message != ""){
        if(type == info){
            cout<<"\n-------------------------\nLOG::"<<message<<"\n-------------------------"<<endl;
        }else if(type == error ){
            cout<<"#########################\nERROR::"<<message<<"\n#########################"<<endl;
        }else if(type == success){
            cout<<"************************\nSUCCESS::"<<message<<"\n*************************"<<endl;
        }else if(type == check) {
        cout<<"\n~~~~~~~~~~~~~~~~~~~~~~***"<<message<<"****~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

        }

    }else{
        cout<<"\n~~~~~~~~~~~~~~~~~~~~~~***here****~~~~~~~~~~~~~~~~~~~~~~~\n";
    }

}
void utils::input(int &out){
    string in;
    cout<<"::";
    getline(cin, in);
    stringstream(in)>>out;
}
