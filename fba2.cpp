/*
******************************************************************************
*      ------------------ FEED BACK AGENT ---------------------      *
******************************************************************************
*  Program to get feed backs from students about professors in their school.  *
*  Each of them should be answer questions either Excellent, Poor, Good, Fair *
*  And after each professors scores can be shawn and can made comparissan  *
******************************************************************************
*   the1.arun@gmail.com                   Written by: Arun. K. R (TheOne!!!)    *
*   0-9037036313                         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  *                              
******************************************************************************
*/

/*
* CUI.hpp Contains following header files
* #include <fstream.h>
* #include <graphics.h>
* #include <stdio.h>
* #include <conio.h>
* #include <stdlib.h>
* #include <time.h> 
* and it is used for Charecter User Interface
* It's object is defined at the time of declaring class and named objCUI
* with the help of constructor graphic sytem is defined there.
* so whenever the object remains in scope we can use graphic system
*/

#include "cui.hpp"

#ifdef abs
#undef abs
#endif

#include <ctype.h>
#include <dos.h>
#include <dir.h>
#include <string.h>
#include <process.h>	//To spwan SE_login.exe
#include <io.h>			//for filelength()
#include <iomanip.h>

#define ESC   0x1b				/* Define the escape key   Hex=1B;ASCII=27    */
#define ENTER 0x0d				/* Define the enter key     Hex= D;ASCII= 13    */
#define SPACE 0x20				/* Define the space key     Hex= 20;ASCII= 32  */
#define DOT   0x2e				/* Define the . (ie.,period) Hex=1D;ASCII=29    */



enum bool{mock=-1,false,true};
enum uState{fail,user,admin};
enum obj{dpt,prof};

typedef struct dptName
{
	int dptID;
	char dptName[25];
	long int dptPhone;
} objDpt;

typedef struct profName
{
	int profID;
	char profName[30];
	char *profAddress[5];		//hose name, local place, district, state, PIN
	long int profPhone[2];		//Mob and Home
	char all4Opt[3],each4Opt[10][3];
} objProf;


objDpt sDpt;
objProf sProf;

fstream filebuf;		// Creating A stream for file operation

const long DptSize=sizeof(sDpt);
const long ProfSize=sizeof(sProf);

extern int fileSize;                //To find  file size
extern int records;                // To display total number of staff

int chkID;
char keyPress;


void call();
uState LoginMnu();
char AdminMnu();
char UserMnu();
int FB_Form();
bool dptMnu();
bool profMnu();
bool addDpt();
bool remDpt();
bool addProf();
bool remProf();
int calcIndex();
void result();
bool fHndlChk(char*);
bool entryChk(/*char*,*/char* entry,obj);
bool getDetails(/*char*,*/obj,long*);
void clearScreen(int,int,int,int);

int chkFileSize(char*,int*);	//name of file argument and total records return (int *) and filesize usual return
int chkAnswer(char*);
bool YesNoChk(char *ans)
{
	if(*ans=='y'||*ans=='Y'||*ans==ESC) 
	return(true);
	else if(*ans=='n'||*ans=='N')
	return(false);
	else
	return(mock);
}


void main()
{
	clrscr();
	setcolor(BLACK);
	setlinestyle(1,1,NORM_WIDTH);
	rectangle(0,0,getmaxx(),getmaxy());
	setfillstyle(1,BLACK);
	floodfill(3,3,getmaxcolor());
	
	/* Plot some "stars"  */
	for (int j=0 ; j<1000; ++j )
	{
		sound(j*3);
		putpixel(random(getmaxx()), random(getmaxy()), random( getmaxcolor()-1 )+1);
		delay(3);
		nosound();
	}
	sleep(1);
	settextjustify(1,1);
	settextstyle(4,0,3);
	setcolor(GREEN);
	outtextxy(getmaxx()/2,getmaxy()/2,"\a WELCOME TO FEED BACK AGENT PROGRAM ");
	delay(3000);
	setcolor(BLACK);
	outtextxy(getmaxx()/2,getmaxy()/2,"\a WELCOME TO FEED BACK AGENT PROGRAM ");
	delay(500);
	clearScreen(1,2,80,25);
	
	if(chdir("F_B_A"))
	{
		mkdir("F_B_A");
		chdir("F_B_A");
		setdisk(3);
	}
	else
	{
		setdisk(3);
	}


	while(true)   //run for ever
	{
		call();
	}
	
}		





void call()
{
	uState uPower=LoginMnu();
	
	if(uPower==user)
	{
		char opt=UserMnu();
		
		while(opt=='F'||opt=='f')
		{
			FB_Form(); //call FBF
			opt=UserMnu();
		}
		
		if(opt=='X'||opt=='x')
		{
			call();
		}
		
	}	
	
	if(uPower==admin)
	{
		char choice=AdminMnu();
		
		while(choice)
		{
			switch(choice)
			{
			case 'D': case 'd': 
				dptMnu();
				break;
			case 'P': case 'p': 
				profMnu();
				break;
			case 'R': case 'r': 
				result();  
				break;
			case 'X': case 'x':
				uPower=fail;
				goto end;	
			default:
				/* nothing to do */;
			}
			choice=AdminMnu();
		}
		
	}
end:	
	if(uPower==fail)  
	{
		call();
	} 
	
}

uState LoginMnu()
{
	uState uPower=fail;
	cleardevice();
	objCUI.disMnuHed("LOGIN MENU");
	gotoxy(15,12);
	cout<<"[ A ] ---------> ADMINISTRATOR LOGIN ";
	gotoxy(15,15);
	cout<<"[ U ] ---------> USER LOGIN ";
	gotoxy(15,18);
	cout<<"[ X ] ---------> EXIT FROM APPLICATION ";
	gotoxy(15,29);
	cout<<"ENTER your Option  [U/A/X] : [   ]\b\b\b";
	char selection=getche();
	cout<<"\b"<<(char)toupper(selection);
	delay(500);
	
	if(selection=='A'||selection=='a')
	{
		//spwan SE_login.exe
		//if success then return TRUE else FALSE and if abnormal termination -1
		//if TRUE then USER=ADMIN
		uPower=admin;
	}
	else if (selection=='U'||selection=='u')
	{
		uPower=user;
	}
	else if (selection=='X'||selection=='x')
	{
		chdir("\\");
		exit(1);
	}
	else
	{
		uPower=LoginMnu();
	} 
	
	return(uPower);	
}

char AdminMnu()
{
	bool chk=false;
	char choice;
	cleardevice();
	objCUI.disMnuHed("ADMINISTRATION MENU");
	gotoxy(15,15);
	cout<<"[ D ] ---------> Department Administration ";
	gotoxy(15,17);
	cout<<"[ P ] ---------> Professor's Administration ";
	gotoxy(15,19);
	cout<<"[ R ] ---------> View Results ";
	gotoxy(15,21);
	cout<<"[ X ] ---------> Exit to LOGIN MENU ";
	gotoxy(15,29);
	cout<<"ENTER your Option [D/P/R/X] : [   ]\b\b\b";
	choice=getche();
	cout<<"\b"<<(char)toupper(choice);
	delay(500);
	
	char ans[]={'D','d','P','p','R','r','X','x'};
	for(int i=0;i<=7;i++)
	{
		if(choice==ans[i])
		{
			chk=true;
		}
	}
	
	if(chk==true)
	{
		return (choice);
	}
	else
	{
		return(AdminMnu());
	}
	
}

char UserMnu()
{
	char opt;
	bool chk=false;
	cleardevice();
	objCUI.disMnuHed("USER MENU");
	gotoxy(15,15);
	cout<<"[ F ] ---------> FEED BACK FORM ";
	gotoxy(15,18);
	cout<<"[ X ] ---------> Exit to LOGIN MENU ";
	gotoxy(15,29);
	cout<<"ENTER your Option [F/X] : [   ]\b\b\b";
	opt=getche();
	cout<<"\b"<<(char)toupper(opt);
	delay(500);
	
	if(opt=='F'||opt=='f'||opt=='X'||opt=='x')
	{
		chk=true;
	}
	
	if(chk==true)
	{
		return (opt);
	}
	else
	{
		return (UserMnu());
	}
	
}

int FB_Form()
{
	return(mock);
}

bool dptMnu()
{
	char opt;
	bool chk,veryfy;
	cleardevice();
	objCUI.disMnuHed("DEPARTMENT ADMINISTRATION MENU");
	gotoxy(15,15);
	cout<<"[ A ] ---------> ADD A DEPARTMENT ";
	gotoxy(15,18);
	cout<<"[ R ] ---------> REMOVE A DEPARTMENT ";
	gotoxy(15,21);
	cout<<"[ X ] ---------> EXIT TO ADMINISTRATION MENU ";
	gotoxy(15,29);
	cout<<"ENTER your Option [A/R/X] : [   ]\b\b\b";
	opt=getche();
	cout<<"\b"<<(char)toupper(opt);
	delay(500);
	char ans[]={'A','a','R','r','X','x'};
	
	for(int i=0;i<=5;i++)
	{
		if(opt==ans[i])
		{
			chk=true;
		}
	}
	
	if(chk==true)
	{
		if(opt=='A'||opt=='a')
		{
			veryfy=addDpt();
		}
		else if(opt=='R'||opt=='r')
		{
			veryfy=remDpt();
		}
		else
		{
			return(true);
		}
		
		if (veryfy==false)		//hope this is not happen
		{
			gotoxy(15,25);
			cerr<<"\aFile Handle Error!!! file open failed\a";
			sleep(2);
			static int count;
			count+=1;
			dptMnu();
			if(count==2)  //after giving another try
			{
				gotoxy(15,25);
				cerr<<"\aFile Handle Error!!! Program exiting...\a";
				exit(-1);
			} 
		} 
	} 
	else
	{
		cout<<"\a";
		dptMnu();
	}
	return(mock);
}

bool profMnu()	
{
	char opt;
	bool chk,veryfy;
	cleardevice();
	objCUI.disMnuHed("PROFESSOR ADMINISTRATION MENU");
	gotoxy(15,15);
	cout<<"[ A ] ---------> ADD A PROFESSOR ";
	gotoxy(15,18);
	cout<<"[ R ] ---------> REMOVE A PROFESSOR ";
	gotoxy(15,21);
	cout<<"[ X ] ---------> EXIT TO ADMINISTRATION MENU ";
	gotoxy(15,29);
	cout<<"ENTER your Option [A/R/X] : [   ]\b\b\b";
	opt=getche();
	cout<<"\b"<<(char)toupper(opt);
	delay(500);
	char ans[]={'A','a','R','r','X','x'};
	
	for(int i=0;i<=5;i++)
	{
		if(opt==ans[i])
		{
			chk=true;
		}
	}
	
	if(chk==true)
	{
		if(opt=='A'||opt=='a')
		{
			veryfy=addProf();
		}
		else if(opt=='R'||opt=='r')
		{
			veryfy=remProf();
		}
		else
		{
			return(true);
		}
		
		if (veryfy==false)		//hope this is not happen
		{
			gotoxy(15,25);
			cerr<<"\aFile Handle Error!!! file open failed\a";
			sleep(2);
			static int count;
			count+=1;
			profMnu();
			if(count==2)  //after giving another try
			{
				gotoxy(15,25);
				cerr<<"\aFile Handle Error!!! Program exiting...\a";
				exit(-1);
			} 
		} 
	}	
	else
	{
		cout<<"\a";
		dptMnu();
	}
	return(mock);
}

bool addDpt()
{
	cleardevice();
	objCUI.disMnuHed("ADD DEPARTMENTS");
	filebuf.open("Dpts.FBA",ios::in|ios::out|ios::app|ios::binary|ios::nocreate);
	bool HndlChk=true,chkAns; 
	
	if(!filebuf)			//check file is connected or not
	{
		HndlChk=fHndlChk("Dpts.FBA");
	}
	
	if (HndlChk==false)
	{
		return(HndlChk);
	}
	else
	{
		char name[25];
		long int pnum;
		do
		{
lbl:
			cleardevice();
			char confirm;
			strset(name,' ');
			objCUI.disMnuHed("ADD DEPARTMENTS");
			gotoxy(12,12);
			cout<<"Name of the department:";
			cin>>name;
			gotoxy(12,14);
			cout<<"Phone number: "; 
			cin>>pnum;
			gotoxy(15,18);
			//filebuf.close();
			if(!entryChk(/*"Dpts.FBA",*/name,dpt))
			{
				cout<<"Entered details are --->";
				gotoxy(16,20);
				cout<<"\" "<<name<<"\"";
				gotoxy(16,22);
				cout<<"\""<<pnum<<"\"";
			}
			else
			{
				gotoxy(16,20);
				cerr<<"\aThat Department Already exists";
				sleep(1);
				goto lbl;
			} 
			gotoxy(15,29);
			cout<<"\aConfirm (Y/N) : [   ]\b\b\b";
			confirm=getche();
			cout<<"\b"<<(char)toupper(confirm);
			sleep(1);
			chkAns=YesNoChk(&confirm);
		}while(chkAns<true);
		
		//filebuf.open("Dpts.FBA",ios::in|ios::out|ios::app|ios::binary);
		
		if(chkAns==true)
		{
			static int deptID;
			filebuf.seekp(0,ios::end);
			filebuf.seekg(-1,ios::end);
			filebuf.read((char*)&sDpt,DptSize);
			if(!sDpt.dptID>=210)
			{
				deptID=210;
			}	
			else
			{
				deptID=sDpt.dptID+1;
			}	
			char *ptrDN=name;
			strset(sDpt.dptName,' ');
			strcat(sDpt.dptName,name);
			sDpt.dptPhone=pnum;
			sDpt.dptID+=deptID++;
			filebuf.write((char*)&sDpt,DptSize);					         // Writes the entered details into the file "Dpts.FBA"
			filebuf.close();
			strcat(ptrDN,".FBA");
			filebuf.open(ptrDN,ios::in|ios::out|ios::ate|ios::binary);	    // Creat a file for newly enterd department
			filebuf.close();
			return(HndlChk);
		}
	}
	return(mock); 	// to feed compiler
}

bool remDpt()
{
	cleardevice();
	objCUI.disMnuHed("REMOVE DEPARTMENTS");
	filebuf.open("Dpts.FBA",ios::in|ios::out|ios::app|ios::binary|ios::nocreate);
	bool HndlChk=true,chkAns;
	
	if(!filebuf)			//check file is connected or not
	{
		HndlChk=fHndlChk("Dpts.FBA");
	}
	
	if (HndlChk==false)
	{
		return(HndlChk);
	}
	else
	{
		
		do
		{
lbl:
			cleardevice();
			char confirm;
			long IDpos;
			bool chkExists=getDetails(/*"Dpts.FBA",*/dpt,&IDpos);
			objCUI.disMnuHed("REMOVE DEPARTMENTS");
			if(chkExists==false)
			{
				filebuf.close();
				return(false);
			}
			else
			{
				//filebuf.open("Dpts.FBA",ios::in|ios::out|ios::app|ios::binary|ios::nocreate);
				filebuf.seekg(IDpos,ios::beg);
				filebuf.read((char*)&sDpt,DptSize);
				gotoxy(15,18);
				cout<<"Selected details are --->";
				gotoxy(16,20);
				cout<<"\" "<<sDpt.dptName<<"\"";
				gotoxy(16,22);
				cout<<"This will permenently deletes this department and any professors in it";
			}
			gotoxy(15,29);
			cout<<"\aConfirm (Y/N) : [   ]\b\b\b";
			confirm=getche();
			cout<<"\b"<<(char)toupper(confirm);
			sleep(1);
			chkAns=YesNoChk(&confirm);
		}while(chkAns<true);
		
		if(chkAns==true)
		{
			char *ptrDN=sDpt.dptName;
			strcat(ptrDN,".FBA");
			remove(ptrDN);
			//filebuf.open("Dpts.FBA",ios::out|ios::app|ios::binary);
			filebuf.seekg(0,ios::beg);
			fstream tmp;
			tmp.open("tmp.FBA",ios::in|ios::app|ios::binary);
			tmp.seekg(0,ios::beg);
			while(filebuf)
			{
				filebuf.read((char*)&sDpt,DptSize);
				tmp.write((char*)&sDpt,DptSize);
			}
			filebuf.close();
			tmp.close();
			remove("Dpts.FBA");
			rename("tmp.FBA","Dpts.FBA");
			return(HndlChk);
		}
	}
	return(mock);	//to feed compiler
}

bool addProf()
{
	cleardevice();
	objCUI.disMnuHed("ADD PROFESSORS");
	filebuf.open("Dpts.FBA",ios::in|ios::out|ios::app|ios::binary|ios::nocreate);
	bool HndlChk=true,chkAns;
	
	if(!filebuf)			//check file is connected or not
	{
		HndlChk=fHndlChk("Dpts.FBA");
	}
	
	if (HndlChk==false)
	{
		return(HndlChk);
	}
	long IDpos;
	bool chkExists=getDetails(/*"Dpts.FBA",*/dpt,&IDpos);
	if(chkExists==false)
	{
		filebuf.close();
		return(false);
	}
	else
	{
		//filebuf.open("Dpts.FBA",ios::in|ios::out|ios::app|ios::binary|ios::nocreate);
		filebuf.seekg(IDpos,ios::beg);
		filebuf.read((char*)&sDpt,DptSize);
		char *ptrFn=strcat(sDpt.dptName,".FBA");
		filebuf.close();
		filebuf.open(ptrFn,ios::in|ios::out|ios::app|ios::binary|ios::nocreate);
		while(!filebuf)			//check file is connected or not
		{
			HndlChk=fHndlChk(ptrFn);
		}
		
		if (HndlChk==false)
		{
			return(HndlChk);
		}
		else
		{
			//routine for add professor
			char name[30];
			long int pnum[2];
			char *address[5];
			do
			{
lbl:			
				cleardevice();
				char confirm;
				objCUI.disMnuHed("ADD PROFESSORS");
				gotoxy(12,9);
				cout<<"Name of the professor:";
				cin>>name;
				gotoxy(12,10);
				cout<<"House Name: "; 
				cin>>address[0];
				gotoxy(12,11);
				cout<<"Locality  : "; 
				cin>>address[1];
				gotoxy(12,12);
				cout<<"District  : "; 
				cin>>address[2];
				gotoxy(12,13);
				cout<<"State     : "; 
				cin>>address[3];
				gotoxy(12,14);
				cout<<"PIN		 : "; 
				cin>>address[4];
				gotoxy(12,15);
				cout<<"Phone( H ): "; 
				cin>>pnum[0];
				gotoxy(12,16);
				cout<<"Phone(Mob): "; 
				cin>>pnum[1];
				gotoxy(15,18);
				//filebuf.close();
				if(!entryChk(/*ptrFn,*/name,prof))
				{
					cout<<"Entered details are --->";
					gotoxy(16,19);
					cout<<"\" "<<name<<"\"";
					gotoxy(16,20);
					cout<<"\""<<address[0]<<"\"";
					gotoxy(16,21);
					cout<<"\""<<address[1]<<"\"";
					gotoxy(16,22);
					cout<<"\""<<address[2]<<"\"";
					gotoxy(16,23);
					cout<<"\""<<address[3]<<"\"";
					gotoxy(16,24);
					cout<<"\""<<address[4]<<"\"";
					gotoxy(16,25);
					cout<<"\""<<pnum[0]<<"\"";
					gotoxy(16,26);
					cout<<"\""<<pnum[1]<<"\"";
				}
				else
				{
					gotoxy(16,20);
					cerr<<"\aThat Professor Already exists";
					sleep(1);
					goto lbl;
				} 
				gotoxy(15,29);
				cout<<"\aConfirm (Y/N) : [   ]\b\b\b";
				confirm=getche();
				cout<<"\b"<<(char)toupper(confirm);
				sleep(1);
				chkAns=YesNoChk(&confirm);
			}while(chkAns<true);	
			
			//filebuf.open(ptrFn,ios::in|ios::out|ios::app|ios::binary);

			if(chkAns==true)
			{
				static int proffID;
				filebuf.seekg(-1,ios::end);
				filebuf.read((char*)&sProf,ProfSize);
				if(!sProf.profID>=210)
				{
					proffID=210;
				}	
				else
				{
					proffID=sProf.profID+1;
				}	
				strcat(sProf.profName,name);
				strcat(sProf.profAddress[0],address[0]);
				strcat(sProf.profAddress[1],address[1]);
				strcat(sProf.profAddress[2],address[2]);
				strcat(sProf.profAddress[3],address[3]);
				strcat(sProf.profAddress[4],address[4]);
				sProf.profPhone[0]=pnum[0];
				sProf.profPhone[1]=pnum[1];
				sProf.profID+=proffID++;
				filebuf.write((char*)&sProf,ProfSize);					         // Writes the entered details into the file "Dpts.FBA"
				filebuf.close();
				return(HndlChk);
			}
		}	
		
	}
	return(mock);	//to feed compiler
}

bool remProf()
{
	cleardevice();
	objCUI.disMnuHed("REMOVE PROFESSORS");
	filebuf.open("Dpts.FBA",ios::in|ios::out|ios::app|ios::binary|ios::nocreate);
	bool HndlChk=true,chkAns;
	
	if(!filebuf)			//check file is connected or not
	{
		HndlChk=fHndlChk("Dpts.FBA");
	}
	
	if (HndlChk==false)
	{
		return(HndlChk);
	}
	
	long IDpos;
	bool chkExists=getDetails(/*"Dpts.FBA",*/dpt,&IDpos);
	
	if(chkExists==false)
	{
		filebuf.close();
		return(false);
	}
	else
	{
		//filebuf.open("Dpts.FBA",ios::in|ios::out|ios::app|ios::binary|ios::nocreate);
		filebuf.seekg(IDpos,ios::beg);
		filebuf.read((char*)&sDpt,DptSize);
		char *ptrFn=strcat(sDpt.dptName,".FBA");
		filebuf.close();
		filebuf.open(ptrFn,ios::in|ios::out|ios::app|ios::binary|ios::nocreate);
		while(!filebuf)			//check file is connected or not
		{
			HndlChk=fHndlChk(ptrFn);
		}
		
		if (HndlChk==false)
		{
			return(HndlChk);
		}
		else
		{
			//routine for remove professor
			do
			{
				chkExists=getDetails(/*ptrFn,*/prof,&IDpos);
				if(chkExists==false)
				{
					filebuf.close();
					return(false);
				}
				else
				{
					//filebuf.open(ptrFn,ios::in|ios::out|ios::app|ios::binary|ios::nocreate);
					filebuf.seekg(IDpos,ios::beg);
					filebuf.read((char*)&sProf,ProfSize);
					gotoxy(15,18);
					cout<<"Selected details are --->";
					gotoxy(16,20);
					cout<<"\" "<<sProf.profName<<"\"";
					gotoxy(16,22);
					cout<<"This will permenently deletes this professor and results obtained";
				}
				gotoxy(15,29);
				cout<<"\aConfirm (Y/N) : [   ]\b\b\b";
				char confirm=getche();
				cout<<"\b"<<(char)toupper(confirm);
				sleep(1);
				chkAns=YesNoChk(&confirm);
			}while	(chkAns<true);
			if(chkAns==true)
			{
				//filebuf.open(ptrFn,ios::out|ios::app|ios::binary);
				filebuf.seekg(0,ios::beg);
				fstream tmp;
				tmp.open("tmp.FBA",ios::in|ios::app|ios::binary);
				tmp.seekg(0,ios::beg);
				while(filebuf)
				{
					filebuf.read((char*)&sProf,ProfSize);
					tmp.write((char*)&sProf,ProfSize);
				}
				filebuf.close();
				tmp.close();
				remove(ptrFn);
				rename("tmp.FBA",ptrFn);
				return(true);
			}
		}
		
	}
	return(mock);	//to feed compiler
}

int calcIndex()
{
	return(mock);	//to feed compiler
}

void result()	
{
	return;
}

bool fHndlChk(char* FName)
{
	gotoxy(12,15);
	filebuf.clear();
	filebuf.open(FName,ios::in|ios::out|ios::app|ios::binary);
	if(!filebuf)
	{
		cerr<<"\a Error in opening the file "<<FName<<"...";
		sleep(2);
		return (false);
	} 
	else
	return (true);
}

bool entryChk(/*char* fname,*/char* entry,obj objID) //TRUE for sDpt FALSE for sProf
{
	//filebuf.open(fname,ios::in|ios::out|ios::app|ios::binary);
	filebuf.seekg(0,ios::beg);
	
	if(objID==dpt)
	{
		while(filebuf)
		{
			filebuf.read((char*)&sDpt,DptSize);
			if(!abs(stricmp(sDpt.dptName,entry)))
			{
				//filebuf.close();
				return(true);
			}
		}
		//filebuf.close();	
		return(false);
	} 
	
	if(objID==prof)
	{
		while(filebuf)
		{
			filebuf.read((char*)&sProf,ProfSize);
			if(!abs(stricmp(sProf.profName,entry)))
			{
				//filebuf.close();
				return(true);
			}
		}
		//filebuf.close();	
		return(false);		
	}
	
	return(mock);  	//to feed compiler	
}

void clearScreen(int bX,int bY,int lX,int lY)   //fstarting (x,y)  AND  ending (x,y)
{
	textbackground(BLACK);
	textcolor(BLACK);
	for(int x=bX;x<=lX;x++)			// fill entire screen with <spaces> so the screen become black if we change color we get translatory effct
	{
		for(int y=bY;y<=lY;y++)
		{
			gotoxy(x,y);
			cprintf(" ");
		}
	}
}

bool getDetails(/*char* fname,*/obj objID,long* fpos)		//TRUE for sDpt FALSE for sProf
{
	restorecrtmode();
	
	int k;

	void footer();
	bool findIdentity(obj,long*);
	void scrollDisplay(int,obj,long*);
	window(0,0,40,25);
	
	
	//filebuf.open(fname,ios::in|ios::out|ios::app|ios::binary|ios::nocreate);
	filebuf.seekg(0,ios::beg);
		
	if(filebuf==NULL)	//There is not atleast a single item 
	{
		setgraphmode(getgraphmode());
		//filebuf.close();
		return(false);	
	}
	
	if(objID==dpt)
	{
		//dispaly Dpartments
		gotoxy(0,1);
		cout<<"=================================================================\n";
		cout<<"  dptID  #   		 Department Name\n";
		cout<<"=================================================================\n";
		k=7;
		for(k=7;k<18;k+=2)  //ie., for 6 entries in active window
		{
			while(filebuf && k<18)
			{
				gotoxy(1,k);
				filebuf.read((char*)&sDpt,DptSize);
				cout<<setw(8)<<sDpt.dptID<<" # "<<setw(25)<<sDpt.dptName;
			}
		}	
		scrollDisplay(17,objID,fpos);
		setgraphmode(getgraphmode());
		//filebuf.close();
		return(true);
	}
	if(objID==prof)
	{
		//display professors in selected department
		gotoxy(0,1);
		cout<<"=================================================================\n";
		cout<<"  profID  #              Professor Name\n";
		cout<<"=================================================================\n";
		k=7;
		while(filebuf&&k<18)
		{
			for(k=7;;k+2)  //ie., for 12 entries in active window
			{
				gotoxy(1,k);
				filebuf.read((char*)&sProf,ProfSize);
				cout<<setw(8)<<sProf.profID<<" # "<<setw(30)<<sProf.profName;
			}
		}
		scrollDisplay(17,objID,fpos);
		setgraphmode(getgraphmode());
		//filebuf.close();
		return(true);
	}
	setgraphmode(getgraphmode());
	filebuf.close();
	return(mock);	//to feed compiler
}


void footer()
{
	gotoxy(1,22);
	cout<<"[Enter ID and press enter for select that entry\nOR Enter to view remaining list]";
	gotoxy(1,20);
	cout<<"====================================================================";
	gotoxy(1,21);
	cout<<"Enter appropriate ID : ";
}

bool findIdentity(obj objID,long* fpos)
{
	filebuf.seekg(0,ios::beg);
	if(objID==dpt)
	{
		while(filebuf)
		{
			filebuf.read((char*)&sDpt,DptSize);
			if(chkID==sDpt.dptID)
			{
				*fpos=filebuf.tellg();
				return(true);
			}
		}
		return(false);
	}
	if(objID==prof)
	{
		while(filebuf)
		{
			filebuf.read((char*)&sProf,ProfSize);
			if(chkID==sProf.profID)
			{
				*fpos=filebuf.tellg();
				return(true);
			}
		}
		return(false);
	}
	return(mock);
}	

void scrollDisplay(int i,obj objID,long* fpos)
{
	while(i==17)
	{
		gotoxy(1,21);
		delline();
		delline();
		delline();
		footer();
		char keyPress=cin.peek();
		if(keyPress==ESC)
		{
			return;
		}
		else if(keyPress!='\n')
		{
			cin>>chkID;
			bool verify=findIdentity(objID,fpos);
			if(verify==true)
			{
				i=18;
			}
			else
			{
				gotoxy(1,21);
				delline();
				delline();
				delline();
				gotoxy(1,24);
				cout<<"\a You entered a wrong ID...Plese enter a valied ID.";
				sleep(2);
				gotoxy(1,24);
				delline();
				i=17;
			}
		}
		else
		{
			if(filebuf)
			{	
				gotoxy(1,21);
				delline();
				delline();
				delline();
				gotoxy(1,7);
				delline();
				i=17;
				gotoxy(1,i);
				if(objID==dpt)
				{
					filebuf.read((char*)&sDpt,DptSize);
					cout<<setw(8)<<sDpt.dptID<<" # "<<setw(25)<<sDpt.dptName;
				}
				else
				{
					filebuf.read((char*)&sProf,ProfSize);
					cout<<setw(8)<<sProf.profID<<" # "<<setw(30)<<sProf.profName;
				}
			}
			else
			{	
				gotoxy(1,21);
				delline();
				delline();
				delline();
				gotoxy(1,24);
				cout<<"\a All items are shewed...Plese enter an ID.";
				sleep(2);
				gotoxy(1,24);
				delline();
				i=17;
			}
		}
	}
}	

