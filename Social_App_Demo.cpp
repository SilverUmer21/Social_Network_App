#include<iostream>  //File handling is done 19 April 2024
#include<fstream>
#include<string>
using namespace std;

class Helper
{
public:
    static int StringLenght(char* str)
    {
        int stringLen = 0;
        for (char* temp = str; *temp != '\0'; temp++)
            stringLen++;
        
        return stringLen;
    }


    static void StringCopy(char* dest, char* src) {
        char* tempDest = dest;
        for (char* tempSrc = src; *tempSrc != '\0'; tempSrc++, tempDest++)
        {
            *tempDest = *tempSrc;
        }
        *tempDest = '\0';
    }

    static char* GetStringFromBuffer(char* buffer)
    {
        int strLen = StringLenght(buffer);
        char* str = 0;
        if (strLen > 0)
        {
            str = new char[strLen + 1];
            StringCopy(str, buffer);
        }
        return str;
    }

    static bool SearchString(char* strtoFind, char* str)
    {
        for (int i = 0; str[i] != '\0'; i++)
        {
            int j;
            for (j = 0; strtoFind[j] != '\0'; j++)
            {
                if (str[i + j] != strtoFind[j])
                    break;
            }
            if (strtoFind[j] == '\0')
                return true;
        }
        return false;

    }
};

class Page
{
private:
    char* ID;
    char* Title;
public:
    void ReadDataFromFile(ifstream& file);

};

void Page::ReadDataFromFile(ifstream& file)
{
    
        char tempID[10];
        file >> tempID;
        int IDsize = Helper::StringLenght(tempID);
        ID = new char[IDsize + 1];
        Helper::StringCopy(ID, tempID);

        file.get();

        char tempTitle[80];
        file.getline(tempTitle, 80);

        int Tsize = Helper::StringLenght(tempTitle);
        Title = new char[Tsize + 1];
        Helper::StringCopy(Title, tempTitle);
        cout << ID<<" "<< Title<<endl;
    
}


class User
{
private:
    char* ID;
    char* First_name;
    char* Last_name;
    User** FriendList;
    Page** LikedPages;
public:
    void ReadDataFromFile(ifstream& file);
};


void User::ReadDataFromFile(ifstream& file)
{
    char tempID[10];
    file >> tempID;
    int IDsize = Helper::StringLenght(tempID);
    ID = new char[IDsize + 1];
    Helper::StringCopy(ID, tempID);

    char tempFname[80];
    char tempLname[80];
    file >> tempFname;
    file >> tempLname;

    int Fsize = Helper::StringLenght(tempFname);
    First_name = new char[Fsize + 1];
    Helper::StringCopy(First_name, tempFname);

    int Lsize = Helper::StringLenght(tempLname);
    Last_name = new char[Lsize + 1];
    Helper::StringCopy(Last_name, tempLname);
    
    cout << ID<<" " << First_name <<" " << Last_name << endl;

}

class Controller
{
private:
    User** AllUsers;
    Page** AllPages;
public:

    void LoadAllUsers(const string fileName);
    void LoadAllPages() {};
};

void Controller::LoadAllUsers(const string fileName)
{
    ifstream file(fileName);

    if (file.is_open())
        cout << "File " << fileName << " successfully opened." << endl;

    else
        cout << "Failed to open file " << fileName << "." << endl;

    int totalUsers;
    file >> totalUsers;
    AllUsers = new User * [totalUsers];

    for (int i = 0; i < totalUsers; ++i) {
        AllUsers[i] = new User; 
        AllUsers[i]->ReadDataFromFile(file);
    }
    int totalPages = 0;
    file >> totalPages;
    cout << "Page:"<<totalPages << endl;
    
    AllPages = new Page * [totalPages];
    for (int i = 0; i < totalPages; i++)
    {
        AllPages[i] = new Page;
        AllPages[i]->ReadDataFromFile(file);
    }

}

int main()
{
    Controller MainApp;
    MainApp.LoadAllUsers("Us.txt");
    cout << endl;
    return 0;
}
