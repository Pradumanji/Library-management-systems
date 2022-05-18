

#include <bits/stdc++.h>
#include<conio.h>
using namespace std;



class book
{
protected:
    string author_name,publication_year,branch,book_name,book_id;
   // int no_of_same_book;
public:
    book()
    {
        author_name="";
        publication_year="";
        branch="";
        book_name="";
        book_id="";
       // no_of_same_book=0;
    }
    void add_book();
    void remove_book(string t);
    void update_book(string t);
    int search_book(string t);
    void list_book();
    void disp_book();
    void storebook();
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
    void disp_all_student();
    void disp_student();
    void borrow_book();
    void return_book();
};
////////////////////////////////////////////////////////////////remove book /////////////////////////////////////////////
void book::remove_book(string t)
{
    ifstream fin;
    ofstream fout;
    fin.open("file3.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"\n File not found!";
    else
    {
        getch();
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
        getch();
        remove("file3.dat");
        getch();
        rename("tempfile.dat","file3.dat");
        cout<<"\n SUCCESSFULLY DELETED! ";
    }
}
////////////////////////////////////////////////// Search book //////////////////////////////////////////////////////////////////

int book::search_book(string t)
{
    int count=0;
    ifstream fin;
    fin.open("file3.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"\n file not found!";
    else
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if((t==book_name))
            {
                disp_book();
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
////////////////////////////////////////////// Book Store ////////////////////////////////////////////////////////////////////////
void book::storebook()
{
    ofstream fout;
    fout.open("file3.dat",ios::app|ios::binary);
    fout.write((char*)this,sizeof(*this));
    fout.close();
}
////////////////////////////////////////////// Book Store ////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////// Display all books/////////////////////////////////////////////////////////////////
void book::disp_all_book()
{
    ifstream fin;
    fin.open("file3.dat",ios::in|ios::app);
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
///////////////////////////////////////////////// display single book /////////////////////////////////////////////////////////////
void book::disp_book()
{
    cout<<"\n Book id : "<<book_id<<"\n Book Name : "<<book_name<<"\n Author name : "<<author_name<<"\n Branch : "<<branch<<"\n Publication year : "<<publication_year
        <<endl;

}


void student::disp_all_student()
{


    fstream fin;
    fin.open(student_id+".dat",ios::in|ios::binary|ios::app);
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
///////////////////////////////////////////////// display single book /////////////////////////////////////////////////////////////
void student::disp_student()
{
    cout<<"student name="<<student_name<<"\nreg no="<<student_id<<"\nstudent session="<<student_session<<"\nbranch="<<student_branch<<"\ndate of book issue="<<date_of_issue<<"\ndate of book return="<<date_of_return;
}
/////////////////////////////////////////////////return book //////////////////////////////////////////////////////////////////
void student::return_book()
{
    cout<<"ENTER DATE OF BOOK RETURN=";
    cin>>date_of_return;
    ofstream fout;
    fout.open(student_id+".dat",ios::out|ios::binary|ios::app);
    //fout<<book_name<<date_of_issue;
    fout.write((char*)this,sizeof(*this));
    fout.close();
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
       // no_of_same_book--;
        cout<<"ENTER DATE OF BOOK ISSUE=";
        cin>>date_of_issue;
        ofstream fout;
        fout.open(student_id+".dat",ios::out|ios::binary|ios::app);
        //fout<<book_name<<date_of_issue;
        fout.write((char*)this,sizeof(*this));
        fout.close();

    }



}

/////////////////////////////////////////////////Return book //////////////////////////////////////////////////////////////////

///////////////////////////////////////////////Borrow book function///////////////////////////////////////////////////////////////////////
/*void book::borrow_book()
{
    cout<<"ENTER BOOK NAME=";
    cin>>book_name;
    cout<<"ENTER BOOK AUTHOR NAME=";
    cin>>author_name;
    cout<<"ENTER BRANCH NAME OF BOOK=";
    cin>>branch;
    no_of_same_book--;

}*/
//////////////////////////////////////////////// Add book ////////////////////////////////////////////////////////////////////
void book::add_book()
{

    cout<<"ENTER BOOK NAME=";
    cin>>book_name;
    // getline(cin,book_name);
    cout<<"ENTER BOOK ID=";
    cin>>book_id;

    cout<<"ENTER BOOK AUTHOR NAME=";
    cin>>author_name;
    //getline(cin,author_name);
    cout<<"ENTER BOOK PUBLICATION YEAR=";
    cin>>publication_year;
    cout<<"ENTER BRANCH NAME OF BOOK=";
    cin>>branch;
   // cout<<"ENTER NO OF BOOKS=";
  //  cin>>no_of_same_book;
    storebook();
}
////////////////////////////////////////////////// update book function /////////////////////////////////////////////////////////
void book::update_book(string t)
{
    fstream file1;
    file1.open("file3.dat",ios::in|ios::out|ios::ate|ios::binary);
    file1.seekg(0);
    file1.read((char*)this,sizeof(*this));
    while(!file1.eof())
    {
        if(t==book_name)
        {
           /* cout<<"ENTER BOOK NAME=";
            cin>>book_name;
            // getline(cin,book_name);
            cout<<"ENTER BOOK ID=";
            cin>>book_id;


            cout<<"ENTER BOOK AUTHOR NAME=";
            cin>>author_name;
            //getline(cin,author_name);
            cout<<"ENTER BOOK PUBLICATION YEAR=";
            cin>>publication_year;
            cout<<"ENTER BRANCH NAME OF BOOK=";
            cin>>branch;
            cout<<"ENTER NO OF BOOKS=";
            cin>>no_of_same_book; */
            add_book();
            file1.seekp(file1.tellp()-sizeof(*this));
            file1.write((char*)this,sizeof(*this));
        }
        file1.read((char*)this,sizeof(*this));
    }
    file1.close();
    cout<<"\n SUCCESSFULLY UPDATED!";
}
/////////////////////////////////////////////////// verify librarian /////////////////////////////////////////////////////////////
bool validate_librarian(string a,string b)
{
    if(a=="mca" && b=="12580")
        return true;
    else
        return false;
}
//////////////////////////////////////////////////// verify Student //////////////////////////////////////////////////////////////
bool student::validate_student(string a,string b)
{
    /* pair<string,string> pr;
     pr= {a,b};
     vector<pair<string,string>> student;
     student.push_back({"sweety","1411999"});
     student.push_back({"sakshi","281999"});
     student.push_back({"praduman","1672001"});
     for(auto it:student)
     {
         //cout<<it.first<<" "<<it.second<<endl;
         auto pr1=it;
         if(pr1==pr)
             return true;
     }
     return false;*/



    ifstream fin;
    fin.open(a+".dat");
    if(!fin)
    {
        cout<<"INVALID USER ID"<<endl;
        return 0;
    }
    if(b==mob_no)
        return 1;
    else
    {
        cout<<"INVALID PASSWORD"<<endl;
        return 0;
    }
}


void student::get_student_data()
{
    //student s;
    ofstream fout;
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
    //fout<<"name="<<student_name<<endl<<"reg no="<<student_id<<endl<<"session="<<student_session<<endl<<"branch="<<student_branch<<endl<<"mobile no="<<mob_no<<endl;
    fout.close();


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
                    cout<<"1.ENTER USERNAME=";
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
                                s1.disp_all_student();
                                break;
                            case 2:
                                s1.return_book();
                                s1.disp_all_student();
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
