#include <iostream>
using namespace std;

int main(){
    int arr[5]= {1,2    ,3,4,5};
    int *ap  = arr;
    for (; *ap !=0; ++ap){
        cout <<* ap<<endl ;

    }
    // cout<<ap<<endl;
// cout<<ap[0]<<endl;
    // cout<<ap++<<endl;
    // cout<<*ap<<endl;
    // cout<<&ap<<endl;
    // cout<<&ap[0]<<endl;
    // cout<<ap++;
}
