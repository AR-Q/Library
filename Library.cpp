#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void clearAdmin() {
	ofstream file("admin.txt");
	file<<"";
	file.close();
}

void AdminMenu();
void UserMenu();

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
	string Name;
	string Role; // Admin / User
} LogedInUser;


bool isNumber(string a) {

	for(int i = 0; i<a.length(); i++) {

		int b = (int)a[i];
		if( b < 48 || b > 57 ) {
			return false;
		}
	}

	return true;
}

bool isValidPhone(string phone) {

	if(phone.length() != 11) {
		return false;
	}

	return isNumber(phone);
}

void RenderEachAdmin(int adminIndex,string data) {

	string arr[3],temp = "";
	int j = 0;

	for(int i = 0; i<data.length(); i++) {

		if(data[i] == '|') {
			arr[j] = temp;
			j++;
			temp = "";
		} else if (i == data.length() - 1) {
			temp += data[i];
			arr[j] = temp;
		} else {
			temp += data[i];
		}
	}

	Admins[adminIndex].Id = arr[0];
	Admins[adminIndex].Password = arr[1];
	Admins[adminIndex].IsActive = (bool) stoi(arr[2]);
}

void RenderAdmin() {

	string data,temp = "";

	fstream file;

	file.open("admin.txt", ios::in | ios::in);

	file>>data;

	file.close();

	if(data.length() == 0) {

		cout<<"There is No Admin"<<endl;
		return;
	}

	for(int i = 0; i<data.length(); i++) {

		if(data[i] == '~') {

			RenderEachAdmin(AdminCount,temp);
			AdminCount++;
			temp = "";
		} else if(i == data.length() - 1) {

			temp += data[i];
			RenderEachAdmin(AdminCount, temp);
			AdminCount++;
		} else {
			temp += data[i];
		}
	}

}

void RenderEachUser(int userIndex,string data) {

	string arr[12],temp = "";
	int j = 0;

	for(int i = 0; i<data.length(); i++) {

		if(data[i] == '|') {
			arr[j] = temp;
			j++;
			temp = "";
		} else if (i == data.length() - 1) {
			temp += data[i];
			arr[j] = temp;
		} else {
			temp += data[i];
		}
	}

	Users[userIndex].Id = arr[0];
	Users[userIndex].Password = arr[1];
	Users[userIndex].Name = arr[2];
	Users[userIndex].Address = arr[3];
	Users[userIndex].Phone = arr[4];
	Users[userIndex].Birthday = arr[5];
	Users[userIndex].StartMembership = arr[6];
	Users[userIndex].EndMembership = arr[7];
	Users[userIndex].DelayDays = stoi(arr[8]);
	Users[userIndex].AccessId = stoi(arr[9]);
	Users[userIndex].BorrowedBooks = stoi(arr[10]);
	Users[userIndex].IsActive = (bool) stoi(arr[11]);
}

void RenderUser() {
	
	string data,temp = "";

	fstream file;

	file.open("user.txt", ios::in | ios::in);

	file>>data;

	file.close();

	if(data.length() == 0) {

		cout<<"There is No User"<<endl;
		return;
	}

	for(int i = 0; i<data.length(); i++) {

		if(data[i] == '~') {

			RenderEachUser(UserCount,temp);
			UserCount++;
			temp = "";
		} else if(i == data.length() - 1) {

			temp += data[i];
			RenderEachUser(UserCount, temp);
			UserCount++;
		} else {
			temp += data[i];
		}
	}
}

void RenderBook() {

}

void Welcome() {

	cout<<"***************************************************"<<endl;
	cout<<"*  Welcome To The Library App Coded By ANONYMOUS  *"<<endl;
	cout<<"***************************************************"<<endl;
}

bool LoginAdmin() {

	string id,pass;

	cout<<"Enter Id : ";
//    getline(cin,id);
	cin>>id;

	cout<<"Enter Password : ";
//    getline(cin,pass);

	cin>>pass;

	for(int i = 0; i<AdminCount; i++) {

		if(Admins[i].Id == id && Admins[i].Password == pass && Admins[i].IsActive) {

			LogedInUser.Id = id;
			LogedInUser.Name = id;
			LogedInUser.Role = "Admin";
			return true;
		}
	}

	return false;
}

void _SignUpAdmin(string id,string pass) {

//	clearAdmin();

	string data = "";

	for(int i = 0; i<AdminCount; i++) {
		data += Admins[i].Id + "|" + Admins[i].Password + "|" + to_string(Admins[i].IsActive) + "~";
	}

	data += id + "|" + pass + "|0";
	
	ofstream file("admin.txt");
	file<<data;
	file.close();
}

void SignUpAdmin() {

	string Id,pass;
	bool check;

	do {
		system("cls");
		check = true;
		cout<<"*******************Sign Up*************************"<<endl;
		cout<<"Enter Your Id : ";
		cin>>Id;
		cout<<"Enter Your Password : ";
		cin>>pass;

		for(int i = 0; i<AdminCount; i++) {

			if(Admins[i].Id == Id) {
				check = false;
			}
		}

		if(!check) {
			cout<<endl<<"Admin With Id Already Exist"<<endl;
			cout<<"Please try again ";
			sleep(1);
		}

	} while(!check);

	_SignUpAdmin(Id,pass);
	cout<<"***************Sign Up Success*********************"<<endl;
	RenderAdmin();
	sleep(1);

}

bool LoginUser(){
	
	string id,pass;

	cout<<"Enter Id : ";
//    getline(cin,id);
	cin>>id;

	cout<<"Enter Password : ";
//    getline(cin,pass);

	cin>>pass;

	for(int i = 0; i<UserCount; i++) {

		if(Users[i].Id == id && Users[i].Password == pass && Users[i].IsActive) {

			LogedInUser.Id = id;
			LogedInUser.Name = Users[i].Name;
			LogedInUser.Role = "User";
			return true;
		}
	}

	return false;
}

void _SignUpUser(string id,string pass,string name,string adress,string phone,string birthday) {

	string data = "";

	for(int i = 0; i<UserCount; i++) {
		data += Users[i].Id + "|" + Users[i].Password + "|" + Users[i].Name + "|" + Users[i].Address + "|" + Users[i].Phone + "|" + Users[i].Birthday + "|" + Users[i].StartMembership + "|" + Users[i].EndMembership + "|" + to_string(Users[i].DelayDays) + "|" + to_string(Users[i].AccessId) + "|" + to_string(Users[i].BorrowedBooks) + "|" + to_string(Users[i].IsActive) + "~";
	}

	data += id + "|" + pass + "|" + name + "|" + adress + "|" + phone + "|" + birthday + "|-|-|0|0|0|0";
	
	ofstream file("user.txt");
	file<<data;
	file.close();
}

void SignUpUser() {

	string Id,pass,name,adress,phone,birthday;
	bool check;

	do {
		system("cls");
		check = true;
		cout<<"*******************Sign Up*************************"<<endl;
		cout<<"Enter Your Id : ";
		cin>>Id;
		cout<<"Enter Your Password : ";
		cin>>pass;
		cout<<"Enter Your Name : ";
		cin>>name;
		cout<<"Enter Your Adress : ";
		cin>>adress;
		cout<<"Enter Your Phone : ";
		cin>>phone;
		cout<<"Enter Your Birthday (yyyy/mm/dd): ";
		cin>>birthday;
		
		if(!isValidPhone(phone)){
			cout<<"Your Phone Number is not valid !!!";
			sleep(1);
			continue;
		}

		for(int i = 0; i<UserCount; i++) {

			if(Users[i].Id == Id) {
				check = false;
			}
		}

		if(!check) {
			cout<<endl<<"User With Id Already Exist"<<endl;
			cout<<"Please try again ";
			sleep(1);
		}

	} while(!check);

	_SignUpUser(Id,pass,name,adress,phone,birthday);
	cout<<"***************Sign Up Success*********************"<<endl;
	RenderUser();
	sleep(1);

}


void FirstMenu() {

	bool state = true,login;
	int command;

	while(state) {

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
				if(login) {
					cout<<"Welcome "<<LogedInUser.Name<<endl;
					sleep(1);
					AdminMenu();
				} else {
					cout<<"User Not Found"<<endl;
					sleep(1);
				}
				break;

			case 2:
				SignUpAdmin();
				break;

			case 3:
				login = LoginUser();
				if(login) {
					cout<<"Welcome "<<LogedInUser.Name<<endl;
					sleep(1);
					UserMenu();
				} else {
					cout<<"User Not Found"<<endl;
					sleep(1);
				}
				break;

			case 4 :
				SignUpUser();
				break;

			default:
				// ERROR
				break;
		}
	}


}

void AdminMenu() {

	bool state = true;
	int command;

	while(state) {

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

void UserMenu() {

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

//string GetCurrentDate(){
//
////    time_t now = time(0);
//
////    tm *ltm = localtime(&now);
//
//    string year = to_string(1900 + ltm->tm_year);
//    string month = to_string(1 + ltm->tm_mon);
//    string day = to_string(ltm->tm_mday);
//
//    return year + "/" + month + "/" + day;
//}



int main() {

	RenderAdmin();
	RenderUser();
	FirstMenu();
	
	return 0;
}
