//////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////////*NOTE :  COMPILE USING THE CPP11 STANDARD*////////
//////////////////g++ -o test.exe main.cc -std=c++11/////////////////////
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
    string word_list[10000][500]; // keeeps all the worlds
    int max_line;
    
    struct{ // this contains information ablut the variables
        string name[10000]; //names of vaiables wouldd be containedd here
        nat location[10000][500][2]; //same with location of the variables in the file  ---p.s is a multidimentinal array
        string catched[10000]; // this would store all the generated varables
        int max_var;

    }var;
}code;

struct lib
{
    char excluded_chars[10];
    char special_chars[100];
    string keywords[100];
    string excluded_keywords[10];

}lib;

//-----------------------------------------------------------------
class logic;
class utils;
class files;

class utils{

    public:
        void getLocalFiles();//its to get all files in the directory  that it is run //then asks you to choose the file number // then returns the file name

        void getNumberOfCoppies();//its to ask the user the number of coppies he waint of the code

        void input(int& out);
       
        void log(log_t type, string message); //its to log current progress
        int get_index(string word, string* arr);
        
        bool is_in(char niddle, char* haystack);
        bool is_in(string niddle, string* haystack, int size);
        bool is_in(string niddle, char* haystack);

        void copy_arr(string* arr1, string *arr2, int size);
        void copy_arr(char* arr1, char *arr2, int size);
}utils;

class logic :public utils{
    public:
        void set_lib();

        void findVariables();//runs a search through the string across all the standard varraible keywords we set; and then retruns the values to *var_name and where it wasa found to *var_adr

        void replaceNewVars();//now replacese the old vars with the new stuff 

        void  line_spacer(string& line);// makes sure each line is well spaced

        void split_line(string line); //splits the line to an array of words 

        char get_first_char(string line); //returns the first character in a line, ignoring any whitespace

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
// logic.split_line("david is a boy");
    utils.getLocalFiles();
    files.readFiletoString();
        cout<<")))))))---"<<lib.excluded_chars[0];

    logic.findVariables();
    utils.getNumberOfCoppies(); 

    for (cnt i = 0; i < code.coppies; i++)
    {
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
void logic::set_lib(){
    string keywords[] ={"int","string", "long", "double", "namespace", "using", "std", "main"}; //were to complete this list 
    char special_chars [] = {'=', '&', '*','[', ']', '{', '}',  '(', ')',';','<', '>','!', '@', '$', '%', '^','_','+', '-', '~', '`', ':', '\'', '"',  '|', ',','?'};

    char excluded_chars[] = { '#','/','.','\\'};
    string var_keywords[] = {"class","private", "public", "void", "protected", "struct"};
    // string excluded_keywords[] = {"using"};

    copy_arr(excluded_chars, lib.excluded_chars, sizeof(excluded_chars));
    copy_arr(special_chars, lib.special_chars, sizeof(special_chars));
    // cout<<"$$$$--"<<lib.excluded_chars[0];
    copy_arr(var_keywords,lib.excluded_keywords, sizeof(var_keywords)/sizeof(var_keywords[0]));

    copy_arr(keywords, lib.keywords,sizeof(keywords)/sizeof(keywords[0]) );
    // copy_arr(excluded_keywords, lib.excluded_keywords, sizeof(excluded_keywords)/sizeof(excluded_chars[0]));
    

}
void utils::getLocalFiles(){
    string *filearr;      // a pointer to where the flies would be stored
    string path = "./";  //the path is set to current directory
    int i,maxx = 0,count = 0;

    cout <<"Welcome, please select the file you want to dub"<<endl;

    for(auto nn : fs::directory_iterator(path)){  //this gets the number of files in the dir and stores it to max
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
    string temp_file_dump, line;
    log(info, "loading file, please wait");
    t_lf:
    count++;
    ifstream thefile(code.name);
    if(thefile.is_open()){
        log(success, "file loaded successfully");
        log(info, "setting up labrary");
        code.max_line =0;
        set_lib();
        log(info, "attepting to read file");

        while(! thefile.eof()){
            getline(thefile, temp_file_dump);

            if(is_in(get_first_char(temp_file_dump), lib.excluded_chars)){
               

            }else{

            line_spacer(temp_file_dump);
            }
            code.max_line += 1;
            log(info, "uploading line to buff array");
            split_line(temp_file_dump);
            code.content += temp_file_dump+"\n";
        }
        log(success, "file read succesfully");
        for(int i =0; i<code.max_line; i++){
            for(auto a: code.word_list[i]){
                if(a != ""){
                cout<<a<<" ";
                }
            }
            cout<<endl;
        }
        // cout<<code.word_list;

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
void logic::split_line(string line){

    string buff; 
    if(is_in(get_first_char(line), lib.excluded_chars)){
        code.word_list[code.max_line][0] = line;
    }else{
        for(auto i =0; i<line.length(); i++){
            if(line[i]  != ' '){
                buff += line[i];
            }else if(line[i] == ' ' && buff.length()>0){
                code.word_list[code.max_line][i] = buff;
                buff.clear();
            }else{
                buff.clear();
            }


        }
    }
}
char logic::get_first_char(string line){

    char output = line[0];
    for (int i = 0; i < line.length(); i++)
    {
        /* code */
        if(line[i] != ' '){ 
             output = line[i];
            break;

        }else{
        }
    }
    return output;
    
}
void logic::findVariables(){
    code.var.max_var =0;
    log(info, "sanning file ...");
    for(auto cl =0; cl<code.max_line; cl++ ){
        int cw=0;
        // log(info, "here----------");
        // cout<<code.max_line;
        
        for(int i=0; i<sizeof(code.word_list[cl])/sizeof(code.word_list[cl][0]); i++){
            if(is_in(code.word_list[cl][i], lib.keywords, sizeof(code.word_list[cl][i])/sizeof(code.word_list[cl][i][0])) || is_in(code.word_list[cl][i], lib.excluded_chars) || is_in(code.word_list[cl][i], lib.excluded_keywords, sizeof(code.word_list[cl][i])/sizeof(code.word_list[cl][i][0])) || is_in(code.word_list[cl][i], lib.special_chars)){
                
            }else{
                if(is_in(code.word_list[cl][cw-1], lib.excluded_keywords,sizeof(code.word_list[cl][cw-1])/sizeof(code.word_list[cl][cw-1][0])) || code.word_list[cl][cw+1] == "="){
                    if(!is_in(code.word_list[cl][i],code.var.name, sizeof(code.word_list[cl][i])/sizeof(code.word_list[cl][i][0]))){// setup code.var.name
                        code.var.name[code.var.max_var+1] = code.word_list[cl][i];
                        code.var.location[code.var.max_var+1][0][0] = cl;
                        code.var.location[code.var.max_var+1][0][1] = cw;
                        code.var.max_var +=1;
                        cout<<"******((("<<code.word_list[cl][i]<<endl;
                    }
                }
            }
        cw += 1;
        }
    }


}
void logic::line_spacer(string& line){

    for (int i = 0; i <line.length(); i++)
    {
        if( line[i] == ' ' && line[i+1] == ' ' ){
            line.erase(i, 1);
        }

        if(is_in(line[i], lib.special_chars) xor is_in(line[i+1], lib.special_chars) && line[i] != ' ' ){ //adding spacec
            line.insert(i+1,1,' ');
        }

    }

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
int utils::get_index(string word, string* arr){
    int count;

    for (int i = 0 ; i <code.var.max_var; i--)
    {
        if(arr[i] == word){
            count = i;
            break;
        }
    }
    
    return count; 
}
bool utils::is_in(char niddle, char* haystack){
    bool init;

    for(; *haystack !=0; haystack++){
        if(niddle == *haystack ){
            init = true;
            break;
        }else{
            init =  false;
            continue;
        }
    }
    return init; 
}
bool utils::is_in(string niddle, string* haystack, int size){
    bool init;
    for(int i=0; i<size; i++){

        if(niddle == haystack[i] ){
            init = true;

            break;
        }else{
            init =  false;
            continue;
        }
    }
    return init; 
}
bool utils::is_in(string niddle, char* haystack){
    bool init;

    for(; *haystack !=0; haystack++){
        if(logic.get_first_char(niddle) == *haystack ){
            init = true;
            break;
        }else{
            init =  false;
            continue;
        }
    cout<<"(((((((((((((--here"<<endl;

    }
    return init; 
}
void utils::copy_arr(string *arr1, string *arr2, int size){
    int count =0;
    for(int i=0; i<size; i++){
        arr2[i] = arr1[i];
    }
}
void utils::copy_arr(char *arr1, char *arr2, int size){
    int count =0;
    for(int i=0; i<size; i++){
        arr2[i] = arr1[i];
    }
}
