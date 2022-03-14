#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
class Emp
{
public :

	int empid;
	char name[25];
	char work[25];
	int adhn;
	int s;
	int w;
	int l;
	int n;
	int t;
	int c;

	void getdata()
	{
   	cout<<"\nENTER EMPID";
		cin>>empid;
		cout<<"\n ENTER NAME";
		gets(name);
		cout<<"\n ENTER WORK TYPE";
		gets(work);
		cout<<"\n ENTER ADHAAR NO.";
		cin>>adhn;
		cout<<"\n ENTER CONTACT NO.";
		cin>>n;
		cout<<"\n ENTER TOTAL WORKING DAYS";
		cin>>w;
		cout<<"\n ENTER TOTAL NO OF LEAVE";
		cin>>l;
		cout<<"\n ENTER SALARY PER DAY";
		cin>>s;
		t=w*s;

	}

	void putdata()
	{cout<<name<<"\n emp id:"<<empid<<"\n adhaar no.:"<<adhn<<"\n work type:"<<work<<"\n contact no.:"<<c<<"\n working days:"<<w<<"\n leaves:"<<l<<"\nper day salary:"<<s<<"\n salary:"<<t;}

	int getempid()
	{
		return empid;
	}

	void add();                                 //WE HAVE TO GIVE THE FUNCCTION PROTOTYPE IN THE CLASS
	void search();
	void del();
	void modify()
	{
		cout<<name<<"\n emp id:"<<empid<<"\n adhaar no.:"<<adhn<<"\n work type:"<<work<<"\ncontact no.:"<<c<<"\n working days:"<<w<<"\n leaves:"<<l<<"\nper day salary:"<<s<<"\n salary:"<<t;

		cout<<"\n\n\n ENTER NEW DETAILS";
		char nm[25];
		char nwork[25];
		int nw;
		int nl;
		int ns;
		int nadhn;
		int nc;
		int nid;
      cout<<"\n new name:(press'.'to retain the old one)";
		gets(nm);
		cout<<"\n new work type:(press'.'to retain the old one)";
		gets(nwork);
		cout<<"\n new adhaar no.:(press'-1'to retain the old one)";
		cin>>nadhn;
		cout<<"\n new contact no.:(press'-1'to retain the old one)";
		cin>>nc;
		cout<<"\n new working days:(press'-1'to retain the old one)";
		cin>>nw;
		cout<<"\n new leave days:(press'-1'to retain the old one)";
		cin>>nl;
		cout<<"\n new per day salary:(press'-1'to retain the old one)";
		cin>>ns;
		if(strcmp(nm,".")!=0)
			strcpy(name,nm);
		if(strcmp(nwork,".")!=0)
			strcpy(nwork,work);
		if(nl!=-1)
			l=nl;
		if(nw!=-1)
			w=nw;
		if(nc!=-1)
      	c=nc;
		if(nadhn!=-1)
			adhn=nadhn;
		if(ns!=-1)
			s=ns;

		t=w*s;
	}
}s1,stud;

void Emp::add()
{
	ofstream fo("emp.dat",ios::app|ios::binary);
	char ans='y';
	while(ans=='y')
	{
		s1.getdata();
		fo.write((char*)&s1,sizeof(s1));
		cout<<"\n RECORD ADDED TO FILE";
		cout<<"\n WANT TO ENTER MORE RECORD(y or n)";
		cin>>ans;
	}
	fo.close();
}

void Emp::search()
{
	int id;
	char found='n';
	ifstream fi("emp.dat",ios::in);
	cout<<"\n ENTER EMP ID TO SEARCH FOR";
	cin>>id;
	while(!fi.eof())
	{
		fi.read((char*)&s1,sizeof(s1));
		if(s1.getempid()==id)
		{
			s1.putdata();
			found='y';
			break;
		}
	}
	if(found=='n')
	cout<<"\n emp id not found";

	fi.close();
}


void Emp::del()
{
	ifstream fio("emp.dat",ios::in);
	ofstream file("temp.dat",ios::out);
	int i;
	char f='f';
	char confirm='n';
	cout<<"\n ENTER ID OF EMPLOYEES WHOSE RECORD NEED TO BE DELETED";
	cin>>i;
	while(!fio.eof())
	{
		fio.read((char*)&s1,sizeof(s1));              //Add '&' before class object
		if(s1.getempid()==i)
		{
			s1.putdata();
			f='t';
			cout<<"\n ARE YOU SURE YOU WANT TO DELETE THIS RECORD?(y or n)";
			cin>>confirm;
			if(confirm=='n')
			{
				file.write((char*)&s1,sizeof(s1));
			}
			else                              //CAN'T LEAVE IT EMPTY
			{
				cout<<"\n RECORD SUCCESSFULLY DELETED ";
			}
      }
   }
   if(f=='f')
   {	cout<<"\n RECORD NOT FOUND!!";  }
	fio.close();
   file.close();
   remove("emp.dat");
   rename("temp.dat","emp.dat");         //FORGOT TO ENCLOSE emp.dat

   ifstream kavi("emp.dat",ios::in);
   cout<<"\n NOW THE FILE CONTAIN-/n";
   while(!kavi.eof())
   {
   	kavi.read((char*)&s1,sizeof(s1));
      if(kavi.eof())break;
      s1.putdata();
   }
      kavi.close();
}

void main()
{
	int a;
	clrscr();
	cout<<"\t  WELCOME TO AMRIT HOTEL EMPLOYEE SALARY MANAGEMENT PROGRAM\n\n\n";
	cout<<"\t\t\tWHAT WOULD YOU LIKE TO DO\n\n";
	cout<<"\t\t\t1-ADD EMPLOYEE\n";
	cout<<"\t\t\t2-SEARCH EMPLOYEE\n";
	cout<<"\t\t\t3-DELETE EMPLOYEE\n";
	cout<<"\t\t\t4-MODIFY EMPLOYEE DETAILS\n";
   cout<<"\n\t\t\t  ENTER YOUR CHOICE : ";
	cin>>a;
	if(a==1)
	{
		s1.add();
   }
	else if(a==2)
	{
		s1.search();
	}
   else if(a==3)
	{
		s1.del();
	}
	else if(a==4)
	{
		fstream fio("emp.dat",ios::in|ios::out|ios::binary);
		int q;long pos;char v='f';
		cout<<"\nENTER ID OF EMPLOYEE WHOSE DATA NEEDA TO BE TRANSFORMED";
		cin>>q;
		while(!fio.eof())
		{
			pos=fio.tellg();
			fio.read((char*)&s1,sizeof(s1));
			if(s1.getempid()==q)
			{
				s1.modify();
				fio.seekg(pos);
				fio.write((char*)&s1,sizeof(s1));
				v='t';
				break;
			}
      }
		if(v=='f')
		cout<<"\n record not found!!";
		fio.seekg(0);
		cout<<"\n NOW THE FILE CONTAIN ";
		while(!fio.eof())
		{
			fio.read((char*)&stud,sizeof(stud));
			stud.putdata();
		}
		fio.close();
	}

	else
	{
		exit(0);
	}
	getch();
}
