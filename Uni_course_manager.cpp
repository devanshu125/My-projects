#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<iomanip.h>
 
class course
{
    int counum; //Course Number
    char couname[30]; //Course Name
    char coutime[10]; //Course Time
 public:
	void get_details(); //A function to get details from the user
    	void show_details(); //A function to show details entered by the user
  	int retcnum() //A function which returns the course number
  	{
      	    return counum;
  	}
};

void main()
{
    clrscr();
    course s;
    ofstream f1;
    f1.open("course.dat", ios::out | ios::binary); //Opens a binary file "course.dat" in writing mode
    int n;
    cout << "How many courses do you want to take this semester" << endl;
    cin >> n;
    for (int i = 0; i < n; i++) //Iteration over number of courses to be entered
     {
     	s.get_details(); //User enters details
	f1.write((char *)&s, sizeof(s)); //Writes details into the file 
     }
     
     f1.close();
     char ch,ch1;
    do
     {
	cout << "1.Append\n";
	cout << "2.Modify\n";
	cout << "3.Search\n";
	cout << "4.Delete\n";
	cout << "5.Display\n";
	cout << "6.Exit\n";
	cout << "Choice please\n";
	cin >> ch; //The choice entered by the user is stored in ch
	switch (ch)
	{
	     case '1': //append
		     ofstream f2;  
		     f2.open("course.dat", ios::app | ios::binary);
		     s.get_details();
		     f2.write((char *)&s, sizeof(s));
		     f2.close();
		     break;
	     
	     case '2': //modify
             	      ofstream f1;  
		      f1.open("course.dat", ios::out | ios::ate | ios::binary);
		      int p;
		      cout << "Enter the record you want to modify\n";
		      cin >> p;
		      int x = (p - 1) * sizeof(s);
		      f1.seekp(x, ios::beg);
		      s.get_details();
		      f1.write((char *)&s, sizeof(s));
		      f1.close();
		      break;
			
		case '3': //search
			ifstream f3; 
			int flop = 0; 
			f3.open("course.dat", ios::in | ios::binary);
			f3.seekg(0, ios::beg);
			int cn;
			cout<<"Enter the coursse number you want to search for\n";
			cin >> cn;
			while (f3.read((char *)&s, sizeof(s)))
			{
			    if (s.retcnum() == cn)
			    {
				s.show_details();
			    }
			    flop = 1;
			}

			if (flop == 0)
			{
			    cout << "Course number not found\n";
			}
			f3.close();
			break;
			
		case '4': //delete
			ofstream f1; 
			ifstream f2; 
			f2.open("course.dat", ios::in | ios::binary);
			f1.open("newcourse.dat",ios::out | ios::app | ios::binary);
			f2.seekg(0, ios::beg);
			int c = 0;
			while (f2.read((char *)&s, sizeof(s)))
			{
			    if(c != 3)  //To delete record number 3
			    f1.write((char *)&s, sizeof(s))
			    c++;

			}
			remove("course.dat");
			rename("newcourse.dat", "course.dat");
			f1.close();
			f2.close();
			break;
			
		case '5': //display
		    	  ifstream f5;     
		 	  f5.open("course.dat", ios::in | ios::binary);
			  f5.seekg(0, ios::beg);
			  while (f5.read((char *)&s, sizeof(s)))
		    	  {
			      s.show_details();   
		    	  }
		 	  f5.close();
			  break;
		
		case '6': //exit
			exit(0);
			break;
			
		}
		cout << "Do you want to continue???\n";
		cout << "If yes then press y else press n\n";
		cin >> ch1;
		while (ch1 == 'y'||ch1 == 'Y');
	}
	
	getch();

}

void course::get_details()
{
	cout << "Enter the course number\n"; 
    cin >> counum;
	cout<< "Enter the course name\n"; 
    gets(couname);
	cout << "Enter the course time\n"; 
    gets(coutime);
	
}

void course::show_details()
{
	cout << "The course number is" << counum;
	cout << "The course name is"; 
    puts(couname);
	cout << "The course time is"; 
    puts(coutime);
	
}
