
#include <bits/stdc++.h>
#include<conio.h>
using namespace std;
class book
{
protected:
    string author_name,publication_year,branch,book_name,book_id;
public:
    book()
    {
        author_name="";
        publication_year="";
        branch="";
        book_name="";
        book_id="";
    }
    void add_book();
    void storebook();
    void disp_book();
    int search_book(string t);
    void update_book(string t);
    void remove_book(string t);
    void disp_all_book();

};
class student:public book
{
    string student_name,student_id,student_branch,student_session,date_of_issue,date_of_return,mob_no;
public:
    student ()
    {
        student_name = "";
        student_id = "";
        student_branch="";
        student_session = "";
        date_of_issue= "";
        date_of_return = "";
    }
    bool validate_student(string,string);
    void get_student_data();
    void disp_student();
    void borrow_book();
    void return_book();
    void disp_student_info();
};
/////////////////////////////////////////////////// verify librarian /////////////////////////////////////////////////////////////
bool validate_librarian(string user_id,string pass)
{
    if(user_id=="mca" && pass=="12580")
        return true;
    else
        return false;
}
//////////////////////////////////////////////// Add book ////////////////////////////////////////////////////////////////////
void book::add_book()
{

    cout<<"ENTER BOOK NAME=";
    cin>>book_name;
    cout<<"ENTER BOOK ID=";
    cin>>book_id;
    cout<<"ENTER BOOK AUTHOR NAME=";
    cin>>author_name;
    cout<<"ENTER BOOK PUBLICATION YEAR=";
    cin>>publication_year;
    cout<<"ENTER BRANCH NAME OF BOOK=";
    cin>>branch;
    storebook();
}
////////////////////////////////////////////// Book Store ////////////////////////////////////////////////////////////////////////
void book::storebook()
{
    fstream fout;
    fout.open("file.dat",ios::app|ios::binary);
    fout.write((char*)this,sizeof(*this));
    fout.close();
}
///////////////////////////////////////////////// display single book /////////////////////////////////////////////////////////////
void book::disp_book()
{
    cout<<"\n Book id : "<<book_id<<"\n Book Name : "<<book_name<<"\n Author name : "<<author_name<<"\n Branch : "<<branch<<"\n Publication year : "<<publication_year
        <<endl;

}

////////////////////////////////////////////////// Search book //////////////////////////////////////////////////////////////////

int book::search_book(string t)
{
    int count=0;
    fstream fin;
    fin.open("file.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"\n file not found!";
    else
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if((t==book_name))
            {
                cout<<"\n**********************************************************************\n";
                disp_book();
                cout<<"\n**********************************************************************\n";
                count++;
            }
            fin.read((char*)this,sizeof(*this));
        }
        if(count==0)
        {
            cout<<"\n Record not found ";
            return 0;
        }
        else
            return 1;
        fin.close();
    }
}

////////////////////////////////////////////////// update book function //////////////////////////////////////////
void book::update_book(string t)
{
    fstream file1;
    file1.open("file.dat",ios::in|ios::out|ios::ate|ios::binary);
    file1.seekg(0);
    file1.read((char*)this,sizeof(*this));
    while(!file1.eof())
    {
        if(t==book_name)
        {
            cout<<"ENTER BOOK NAME=";
            cin>>book_name;
            cout<<"ENTER BOOK ID=";
            cin>>book_id;
            cout<<"ENTER BOOK AUTHOR NAME=";
            cin>>author_name;
            cout<<"ENTER BOOK PUBLICATION YEAR=";
            cin>>publication_year;
            cout<<"ENTER BRANCH NAME OF BOOK=";
            cin>>branch;
            file1.seekp(file1.tellp()-sizeof(*this));
            file1.write((char*)this,sizeof(*this));
        }
        file1.read((char*)this,sizeof(*this));
    }
    file1.close();
    cout<<"\n SUCCESSFULLY UPDATED!";
}

////////////////////////////////////////////////////////////////remove book /////////////////////////////////////////////
void book::remove_book(string t)
{
    fstream fin;
    fstream fout;
    fin.open("file.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"\n File not found!";
    else
    {
        fout.open("tempfile.dat",ios::out);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(!(book_name==t))
                fout.write((char*)this,sizeof(*this));
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("file.dat");
        rename("tempfile.dat","file.dat");
        cout<<"\n SUCCESSFULLY DELETED! ";
    }
}
///////////////////////////////////////////// Display all books/////////////////////////////////////////////////////////////////
void book::disp_all_book()
{
    fstream fin;
    fin.open("file.dat",ios::in);
    if (!fin)
        cout<<"\n File not found!";
    else
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            cout<<"\n**********************************************************************\n";
            disp_book();
            cout<<"\n**********************************************************************\n";
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
    }
}
//////////////////////////////////////////////////// verify Student //////////////////////////////////////////////////////////////
bool student::validate_student(string user_id,string pass)
{
    int count=0;
    fstream fin;
    fin.open(user_id+".dat",ios::in|ios::out|ios::binary|ios::app);
    if(!fin)
    {
        cout<<"INVALID USER ID"<<endl;
        return 0;
    }
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof())
    {
        if(pass==mob_no)
        {
            return 1;
            count++;
        }
        fin.read((char*)this,sizeof(*this));
    }
    fin.close();

    if(count==0)
    {
        cout<<"INVALID PASSWORD"<<endl;
        return 0;
    }
}
void student::get_student_data()
{
    fstream fout;
    cout<<"ENTER STUDENT NAME=";
    cin>>student_name;
    cout<<"ENTER REG NO=";
    cin>>student_id;
    cout<<"ENTER SESSION=";
    cin>>student_session;
    cout<<"ENTER BRANCH=";
    cin>>student_branch;
    cout<<"ENTER MOBILE NO=";
    cin>>mob_no;
    cout<<"\nUSE REG NO AS USER ID AND MOB NO AS PASSWORD!\n";
    fout.open(student_id+".dat",ios::out);
    fout.write((char*)this,sizeof(*this));
    fout.close();


}
///////////////////////////////////////////////// display student /////////////////////////////////////////////////////////////
void student::disp_student()
{
    cout<<"student name="<<student_name<<"\nreg no="<<student_id<<"\nstudent session="<<student_session<<"\nbranch="<<student_branch<<"\ndate of book issue="<<date_of_issue<<"\ndate of book return="<<date_of_return;
}

///////////////////////////////////////////////Borrow book function///////////////////////////////////////////////////////////////////////
void student::borrow_book()
{

    cout<<"ENTER BOOK NAME=";
    cin>>book_name;
    int t=search_book(book_name);
    if(t==0  )
        cout<<"BOOK NOT FOUND"<<endl;
    else
    {
        cout<<"ENTER DATE OF BOOK ISSUE=";
        cin>>date_of_issue;
        fstream fout;
        fout.open(student_id+".dat",ios::out|ios::binary);
        fout.write((char*)this,sizeof(*this));
        fout.close();

    }

}

/////////////////////////////////////////////////return book //////////////////////////////////////////////////////////////////
void student::return_book()
{
    cout<<"ENTER DATE OF BOOK RETURN=";
    cin>>date_of_return;
    fstream fout;
    fout.open(student_id+".dat",ios::out|ios::binary);
    fout.write((char*)this,sizeof(*this));
    fout.close();
}


void student::disp_student_info()
{
    fstream fin;
    fin.open(student_id+".dat",ios::in|ios::binary);
    if (!fin)
        cout<<"\n file not found!";
    else
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            cout<<"\n**********************************************************************\n";
            disp_student();
            cout<<"\n**********************************************************************\n";
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
    }


}

////////////////////////////////////////////////////// librarian menu ///////////////////////////////////////////////////////////
void LibrarianMenu()
{
    cout << "\n*******LIBRARIAN MENU*******" << endl;
    cout<<"1.ADD BOOK"<<endl;
    cout<<"2.REMOVE BOOK"<<endl;
    cout<<"3.UPDATE BOOK"<<endl;
    cout<<"4.LIST OF ALL BOOKS"<<endl;
    cout<<"5.SEARCH BOOK"<<endl;
    cout<<"6.GO TO MAIN MENU"<<endl;
    cout<<"7.EXIT"<<endl;
}
///////////////////////////////////////////////////// main menu ///////////////////////////////////////////////////////////////
void MainMenu()
{
    cout << "\n*******MAIN MENU*******" << endl;
    cout<<"1.LIBRARIAN LOGIN"<<endl;
    cout<<"2.STUDENT LOGIN"<<endl;
    cout<<"3.EXIT"<<endl;
}

/////////////////////////////////////////////////////// student menu ///////////////////////////////////////////////////////////
void StudentMenu()
{
    cout << "\n*******STUDENT MENU*******" << endl;
    cout<<"1.BORROW A BOOK"<<endl;
    cout<<"2.RETURN A BOOK"<<endl;
    cout<<"3.LIST OF ALL BOOKS"<<endl;
    cout<<"4.GO TO MAIN MENU"<<endl;
    cout<<"5.EXIT"<<endl;
}


//////////////////////////////////////////////////////////////////////////// Main Function //////////////////////////////////////
int main()
{
    book b1;
    student s1;
    int ch,ch1,ch2;

    do
    {
menu:
        system("cls");
        MainMenu();
        cout << "Enter your choice=";
        cin>>ch;
        system("cls");
        switch(ch)
        {
        case 1:
        {
            string user,pass;
            cout << "\n*******LIBRARIAN LOGIN*******" << endl;
            cout<<"1.ENTER USERNAME=";
            cin>>user;
            cout<<"2.ENTER PASSWORD=";
            cin>>pass;

            if(validate_librarian(user,pass))
            {
                cout<<"\n Librarian login successfully ";
                getch();
                system("cls");

                while(1)
                {
                    LibrarianMenu();

                    cout<<" ENTER YOUR CHOICE = ";
                    cin>>ch1;
                    switch(ch1)
                    {
                    case 1:
                    {
                        char t='y';
                        while(t=='y'||t=='Y')
                        {
                            b1.add_book();
                            b1.disp_book();
                            cout<<" DO YOU WANT TO ADD ANY MORE BOOK(y/n) : ";
                            cin>>t;
                        }

                    }

                    break;
                    case 2 :
                    {
                        cout<<"\n Enter book name : ";
                        string s1;
                        cin>>s1;
                        b1.remove_book(s1);
                        break;
                    }
                    case 3:
                    {
                        cout<<"\n Enter book name : ";
                        string s1;
                        cin>>s1;
                        b1.update_book(s1);
                        break;
                    }

                    case 4:
                    {
                        b1.disp_all_book();
                        getch();
                        break;
                    }

                    case 5:
                    {
                        cout<<"\n Enter book name : ";
                        string s1;
                        cin>>s1;
                        b1.search_book(s1);
                        break;
                    }
                    case 6:
                        goto menu;
                        break;
                    case 7:
                        return 0;

                    default :
                        cout<<"\n Wrong Choice !";
                        break;
                    }
                }
            }
            else
            {
                cout<<"\n you have entered wrong username or password ! try again.";
            }


        }
        break;

        case 2:
        {

            system("cls");
            while(1)
            {
                int ch;
                cout<<"\n1.LOGIN FOR ALREADY REGISTERED STUDENT"<<endl;
                cout<<"2.NOT REGISTERED?? GET REGISTERED HERE"<<endl;
                cout<<"3.GO TO MAIN MENU"<<endl;
                cout<<"enter your choice=";
                cin>>ch;
                switch(ch)
                {
                case 1:
                {
                    string user,pass;
                    cout << "\n*******STUDENT LOGIN*******" << endl;
                    cout<<"1.ENTER REG. NO =";
                    cin>>user;
                    cout<<"2.ENTER PASSWORD=";
                    cin>>pass;

                    if(s1.validate_student(user,pass))
                    {
                        cout<<"student login successfully";
                        getch();
                        while(1)
                        {

                            system("cls");

                            StudentMenu();
                            cout<<"ENTER YOUR CHOICE=";
                            cin>>ch2;


                            switch(ch2)
                            {
                            case 1:
                                s1.borrow_book();
                                s1.disp_student_info();
                                break;
                            case 2:
                                s1.return_book();
                                s1.disp_student_info();
                                break;
                            case 3:
                                b1.disp_all_book();
                                break;
                            case 4:
                                goto menu;
                                break;
                            case 5:
                                return 0;
                            default :
                                cout<<"\n Wrong Choice !";

                            }
                            getch();
                        }
                        break;
                    }
                    break;
                }
                case 2:
                {
                    s1.get_student_data();
                    break;
                }
                case 3:
                    goto menu;
                    break;
                default:
                    cout<<"wrong choice"<<endl;
                }

            }
            break;
        }
        case 3:
            return 0;
        default:
            cout<<"wrong choice"<<endl;
        }
    }

    while(1);
    return 0;
}
