#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;




int main(){

    string a;

    fstream file;

    file.open("admin.txt", ios::in | ios::in);

    file>>a;

    cout<<a;

    file.close();


    return 0;
}