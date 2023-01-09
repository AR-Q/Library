#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// the data in the database is Saved by this Pattern
// Books
// Id|Title|Genre|Writer|Publisher|LastBorrowedUserId|PublishDate|EditDate|LastBorrow|LendBack|IsAvaible|IsBorrowed|PunishMoney|PublishNumber|EditNumber
// - -> null
// each Data is Devided By ~

struct {
    string Id;
    string Title;
    string Genre;
    string Writer;
    string Publisher;
    string LastBorrowedUserId;
    string PublishDate;
    string EditDate;
    string LastBorrow;
    string LendBack;
    bool IsAvaible;
    bool IsBorrowed;
    int PunishMoney;
    int PublishNumber;
    int EditNumber;
} Books[1000];

int BookCount = 0;


// the data in the database is Saved by this Pattern
// Admins
// Id|Password|IsActive

struct {
    string Id;
    string Password;
    bool IsActive;
} Admins[1000];

int AdminCount = 0;


// the data in the database is Saved by this Pattern
// Users
// Id|Password|Name|Address|Phone|Birthday|StartMembership|EndMembership|DelayDays|AccessId|BorrowedBooks|IsActive

struct {
    string Id;
    string Password;
    string Name;
    string Address;
    string Phone;
    string Birthday;
    string StartMembership;
    string EndMembership;
    int DelayDays;
    int AccessId;
    int BorrowedBooks;
    bool IsActive;
} Users[1000];

int UserCount = 0;

struct {
    string Id;
    string Role; // Admin / User
} LogedInUser;

void RenderEachAdmin(int adminIndex,string data){

    string arr[3],temp = "";
    int j = 0;

    for(int i = 0;i<data.length();i++){

        if(data[i] == '|'){
            arr[j] = temp;
            j++;
            temp = "";
        }
        else if (i == data.length() - 1){
            temp += data[i];
            arr[j] = temp;
        }
        else{
            temp += data[i];
        }
    }

    Admins[adminIndex].Id = arr[0];
    Admins[adminIndex].Password = arr[1];
    Admins[adminIndex].IsActive = (bool) stoi(arr[2]);
}

void RenderAdmin(){

    string data,temp = "";

    fstream file;

    file.open("admin.txt", ios::in | ios::in);

    file>>data;

    file.close();

    if(data.length() == 0){

        cout<<"There is No Admin"<<endl;
        return;
    }

    for(int i = 0;i<data.length();i++){

        if(data[i] == '~'){

            RenderEachAdmin(AdminCount,temp);
            AdminCount++;
            temp = "";
        }
        else if(i == data.length() - 1){

            temp += data[i];
            RenderEachAdmin(AdminCount, temp);
            AdminCount++;
        }
        else{
            temp += data[i];
        }
    }

}

void RenderUser(){

}

void RenderBook(){

}

void Welcome(){

    cout<<"***************************************************"<<endl;
    cout<<"*  Welcome To The Library App Coded By ANONYMOUS  *"<<endl;
    cout<<"***************************************************"<<endl;
}

bool LoginAdmin(){

    string id,pass;

    cout<<"Enter Id : ";
    getline(cin,id);

    cout<<"Enter Password : ";
    getline(cin,pass);

    for(int i = 0;i<AdminCount;i++){

        if(Admins[i].Id == id && Admins[i].Password == pass && Admins[i].IsActive){

            LogedInUser.Id = id;
            LogedInUser.Role = "Admin";
            return true;
        }
    }

    return false;
}

void FirstMenu(){

    bool state = true,login;
    int command;

    while(state){

        system("cls");

        cout<<"***************************************************"<<endl;
        cout<<"* Login (Admin) [1]                               *"<<endl;
        cout<<"* Sign Up (Admin) [2]                             *"<<endl;
        cout<<"* Login (User) [3]                                *"<<endl;
        cout<<"* Sing Up (User) [4]                              *"<<endl;
        cout<<"* Exit [0]                                        *"<<endl;
        cout<<"***************************************************"<<endl;

        cout<<"Enter Your Command : ";
        cin>>command;

        switch (command) {

            case 0:
                state = false;
                break;

            case 1:
                login = LoginAdmin();
                if(login){
                    cout<<"Welcome "<<LogedInUser.Id<<endl;
                }
                else{
                    cout<<"User Not Found"<<endl;
                }
                break;

            case 2:
                // TODO SignUpAdmin();
                break;

            case 3:
                // TODO LoginUser();
                break;

            case 4 :
                // TODO SignUpUser();
                break;

            default:
                // ERROR
                break;
        }
    }


}

void AdminMenu(){

    bool state = true;
    int command;

    while(state){

        system("cls");

        cout<<"***************************************************"<<endl;
        cout<<"* Show All Books [1]                              *"<<endl;
        cout<<"* Add Book [2]                                    *"<<endl;
        cout<<"* Edit Book [3]                                   *"<<endl;
        cout<<"* Delete Book [4]                                 *"<<endl;
        cout<<"* Confirm Admin [5]                               *"<<endl;
        cout<<"* Confirm User [6]                                *"<<endl;
        cout<<"* Bann User [7]                                   *"<<endl;
        cout<<"* Exit [0]                                        *"<<endl;
        cout<<"***************************************************"<<endl;

        cout<<"Enter Your Command code : ";
        cin>>command;

        switch (command) {

            case 0:
                state = false;
                break;

            case 1:
                // TODO ShowAllBooks();
                break;

            case 2:
                // TODO AddBook();
                break;

            case 3:
                // TODO EditBook();
                break;

            case 4:
                // TODO DeleteBook();
                break;

            case 5:
                // TODO ConfirmAdmin();
                break;

            case 6:
                // TODO ConfirmUser();
                break;

            case 7:
                // TODO BannUser();
                break;

            default:
                // ERROR
                break;
        }
    }


}

void UserMenu(){

    cout<<"***************************************************"<<endl;
    cout<<"* Show All Books [1]                              *"<<endl;
    cout<<"* Search [2]                                      *"<<endl;
    cout<<"* Borrow Book [3]                                 *"<<endl;
    cout<<"* Return Book [4]                                 *"<<endl;
    cout<<"* Edit Information [5]                            *"<<endl;
    cout<<"* Pay Punishment Money [6]                        *"<<endl;
    cout<<"* Extension Borrow Book [7]                       *"<<endl;
    cout<<"* Exit [0]                                        *"<<endl;
    cout<<"***************************************************"<<endl;
}

string GetCurrentDate(){

    time_t now = time(0);

    tm *ltm = localtime(&now);

    string year = to_string(1900 + ltm->tm_year);
    string month = to_string(1 + ltm->tm_mon);
    string day = to_string(ltm->tm_mday);

    return year + "/" + month + "/" + day;
}

bool isNumber(string a){

    for(int i = 0;i<a.length();i++){

        int b = (int)a[i];
        if( b < 48 || b > 57 ){
            return false;
        }
    }

    return true;
}

bool isValidPhone(string phone){

    if(phone.length() != 11){
        return false;
    }

    return isNumber(phone);
}

void AddAdmin(){

    string Id,pass;
    bool isActive = false;

    do{
        cout<<"Enter Id : ";
        cin>>Id;
    } while (Id.length() > 0);

    do{
        cout<<"Enter Password : ";
        cin>>pass;
    } while (Id.length() > 0);

    fstream file;

    file.open("admin.txt", ios::out | ios::in);

    // TODO continiue

}

int main() {

    RenderAdmin();
    FirstMenu();


    return 0;
}
