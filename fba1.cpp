/*
  ******************************************************************************
  *            ------------------------------ FEED BACK AGENT -----------------------------                *
  ******************************************************************************
  * Program to get feed backs from students about professors in their school.                      *
  * Each of them should be answer questions either Excellent, Poor, Good, Fair                      *
  * And after each professors schores can be shawn and can made comparissan                    *
  ******************************************************************************
  *                                     Written by: Arun. K. R (TheOne!!!)                                                         *
  *                            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                           *                               
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
 * with the help of constructor graphic ystem is defined there.
 * so whenever the object remains in scope we can use graphic system
*/
#include "cui.hpp"
//#include "SecureLogIn.hpp"
#include <ctype.h>
#include <dos.h>
#include <string.h>

#define ESC     0x1b                    /* Define the escape key   Hex=1B;ASCII=27    */
#define ENTER   0x0d				    /* Define the enter key     Hex= D;ASCII= 13    */
#define F12     0x1d					/* Define the F12 key        Hex=1D;ASCII=29    */
#define DOT     0x2e					/* Define the . (ie.,period) Hex=1D;ASCII=29    */



// Class definition starts here and we have 2 classes

class cDepartments
	{
	 private:
	 
	 void prfnAddDpt();
	 void prfnRemoveDpt();
	 char dptName[25];
	 int dptPhone[12];
	 
	 
	 public:
	 	
	 void pufnDptAdmin(int);
	 void pufnGetDpts();	
	 char* pufnGetDptName()
		{
		 return(this->dptName);
		}
	 
	}objDpt;


class cProfessors
	{
	 private:
	 
	 char profName[30],profCode[3];
	 char *profAddress[5];		//hose name, local place, district, state, PIN
	 char *profPhone[2];		//Mob and Home
	 char all4Opt[3],each4Opt[10][3];
	 void prfnAddProf();
	 void prfnRemoveProf();
	 void prfnCalculateGrade(int,char,int,char*);
	 
	 
	 public:

	 void pufnProfAdmin(int);
	 void pufnFeedBackForm();
	 void pufnDisplayResult(int,char*,int);
	 char* pufnGetProf(int num)
		{
		 if(num==0)
			{
			 return(profName);
			}
		 else
			{
			 return(profCode);
			}
		}
	  
	}objProf;
	

// Class definition ends here with objects are created	

	
fstream filebuf;					// Creating A Buffer for file operation
const long DptSize=sizeof(objDpt);
const long ProfSize=sizeof(objProf);
//extern int fileSize;                //To find  file size
//extern int records                // To display total number of staff 
int chkAnswer(char*);
int YesNoChk(char *ans)
	{
	 if(*ans=='y'||*ans=='Y'||*ans==ESC||*ans==F12) 
	 return(1);
	 else if(*ans=='n'||*ans=='N')
	 return(0);
	 else
	 return(-1);
	}
//int chkFileSize(char*,int*);	//name of file argument and total records return (int *) and filesize usual return


// Declaration of functions in cDepartments Class starts here

void cDepartments::pufnDptAdmin(int num)
	{
	 filebuf.open("FbaDpts.FBA",ios::in|ios::out|ios::app|ios::binary);
	 filebuf.close();
	 switch (num)
		{
		 case 1: prfnAddDpt();
		         break;
		 case 2: prfnRemoveDpt();
		     	 break;
		 default: cout<<"\n Error!!! \n";
                 return;
		}
     clrscr();
	 return;
	}
	
void cDepartments::prfnAddDpt()      //note: It's better to include a function to check wether the given dpt., name alredy exists or not
	{
	 int chkAns,count;
	 
	 objCUI.disMnuHed("ADD DEPARTMENTS");
	 filebuf.open("FbaDpts.FBA",ios::in|ios::out|ios::app|ios::binary|ios::nocreate);
	 
	 while(!filebuf)			//check file is connected or not
		{
		 gotoxy(12,15);
		 cerr<<"\n Error opening/creating file FbaDpts.FBA...\n";
		 sleep(2);
		filebuf.clear();
		 filebuf.open("FbaDpts.FBA",ios::in|ios::out|ios::app|ios::binary);
		 if(!filebuf.eof())
		 break;
		 else
		 return;
		} 
	
	 do
		{
		 clrscr();
		 char confirm;
		 objCUI.disMnuHed("ADD DEPARTMENTS");
		 gotoxy(12,12);
		 cout<<"Name of the department:";
		 gets(objDpt.dptName);
		 gotoxy(12,14);
		 cout<<"Phone number: "; int i;
		 cin>>objDpt.dptPhone[i];
		 gotoxy(15,18);
		 cout<<"Entered details are --->";
		 gotoxy(16,20);
		 cout<<"\" "<<dptName<<"\""; 
		 gotoxy(16,22);
		 cout<<"\""<<dptPhone<<"\"";
		 gotoxy(15,29);
		 cout<<"\aConfirm (Y/N) : [   ]\b\b\b";
		 confirm=getche();
		 cout<<"\b"<<confirm;
		 sleep(1);
		 chkAns=YesNoChk(&confirm);
		}while(chkAns<1);
	 char *ptrDptName=objDpt.dptName;
	 filebuf.write((char*)&objDpt,DptSize);					            	//Writes the entered details into the file "FbaDpts.FBA"				
	 filebuf.close();
	 strcat(ptrDptName,".FBA");
	 filebuf.open(ptrDptName,ios::in|ios::out|ios::ate|ios::binary);	    //Creat a file for newly enterd department
	 filebuf.close();
	}	
	
void cDepartments::prfnRemoveDpt()   //note: It's better to include a function to check wether there is atleast one entry in dpt's file
	{
	 char choice;
	 do
		{
		 clrscr();
		 objCUI.disMnuHed("REMOVE DEPARTMENTS");
		 gotoxy (6,12);
		 cout<<"------------------------------WARNING-------------------------------";
		 gotoxy (6,15);
		 cout<<"Deleting a department also deletes all professors in that department.";
		 gotoxy (6,18);
		 cout<<"Do you want to proceed(y/n):[   ]\b\b\b";
		 choice=getche();
		 cout<<choice;
		 sleep(1);
		}while(YesNoChk(&choice)>0);
	 if (YesNoChk(&choice)==0)
		{
		 return;
		} 
	 clrscr();
	 objCUI.disMnuHed("REMOVE DEPARTMENTS");
	 
	 objDpt.pufnGetDpts();
	 gotoxy (10,29);
	 cout<<"Select A department to delete:[   ]\b\b\b";
	 int i;
	 cin>>i;
	 if(i==ESC||i==F12||DOT)
		{
		 return;
		} 
	 i-=1;   //because i'th record is i-1'th record in C	
	 filebuf.open("FbaDpts.FBA",ios::out|ios::in|ios::app|ios::binary);
	 filebuf.seekg((i*DptSize),ios::beg);
	 filebuf.read((char*)&objDpt,DptSize);
	 char *ptrDName=objDpt.dptName;
	 char *tmpDName=ptrDName;
	 strcat(ptrDName,".FBA");
	 remove(ptrDName);
	 fstream tfile;
	 tfile.open("tmpDpt.FBA",ios::out|ios::in|ios::app|ios::binary);
	 filebuf.seekg(0,ios::beg);
	 while(filebuf.read((char*)&objDpt,DptSize))
		{
		 if(objDpt.dptName!=tmpDName)
		 tfile.write((char*)&objDpt,DptSize);
		}
	 filebuf.close();
	 tfile.close();
	 remove("FbaDpts.FBA");
	 rename("tmpDpt.FBA","FbaDpts.FBA");
	}
	
	
void cDepartments::pufnGetDpts()
	{
	 int i=1,j=12;
	 filebuf.open("FbaDpts.FBA",ios::out|ios::app|ios::binary);
	 filebuf.seekg(0,ios::beg);
	 while(filebuf)
		{
		 gotoxy(10,j++);
		 filebuf.read((char*)&objDpt,DptSize);
		 cout<<"("<<i++<<")  "<<objDpt.dptName;
		}
	 filebuf.close();
	 return;
	}

// Declaration of functions in cDepartments Class ends here	


// Declaration of functions in cProfessors Class starts here

void cProfessors::pufnProfAdmin(int num)
	{
	 switch (num)
		{
		 case 3: prfnAddProf();
				 break;
		 case 4: prfnRemoveProf();
				 break;
		 default: cout<<"\n Wrong Selection \n";
				 return;
		}
	 clrscr();
	 return;		
	}			

void cProfessors::prfnAddProf()  //note: It's better to include a function to check wether there is atleast one entry in dpt's file
	{
	 clrscr();
	 objCUI.disMnuHed("ADD PROFESSORS");
	 objDpt.pufnGetDpts();
	 int i;
	 gotoxy(10,29);
	 cout<<"Select a department to add professors: ";
	 cin>>i;
	 if(i==ESC||i==F12||DOT)
		{
		 return;
		} 
	 i-=1;	
	 filebuf.open("FbaDpts.FBA",ios::in|ios::out|ios::app|ios::binary);
	 filebuf.seekg((i*DptSize),ios::beg);
	 filebuf.read((char*)&objDpt,DptSize);
	 char *ptrDptN=objDpt.pufnGetDptName();
	 filebuf.close();
	 filebuf.open(ptrDptN,ios::in|ios::app|ios::binary);
	 gotoxy(12,12);
	 cout<<"Professor's Name:";
	 cin>>objProf.profName;
	 gotoxy(12,14);
	 cout<<"Professor code  :";
	 cin>>objProf.profCode;
	 gotoxy(12,16);
	 cout<<"PHONE NUMBER ---> ";
	 gotoxy(12,18);
	 cout<<"Mobile : ";
	 cin>>profPhone[0];
	 gotoxy(12,19);
	 cout<<"Residence : ";
	 cin>>profPhone[1];
	 gotoxy(12,21);
	 cout<<"ADDRESS ---> ";
	 gotoxy(12,22);
	 cout<<"House Name: ";
	 cin>>profAddress[0]; 
	 gotoxy(12,23);
	 cout<<"Place (locality): ";
	 cin>>profAddress[1];
	 gotoxy(12,24);
	 cout<<"District: ";
	 cin>>profAddress[2];
	 gotoxy(12,25);
	 cout<<"State: ";
	 cin>>profAddress[3];
	 gotoxy(12,26);
	 cout<<"PIN code: ";
	 cin>>profAddress[4];
	 filebuf.write((char*)&objProf,ProfSize);
	 filebuf.close();
	 }
	 
void cProfessors::prfnRemoveProf()  //note: It's better to include a function to check wether there is atleast one entry in dpt's file
	{
	 objCUI.disMnuHed("REMOVE PROFESSORS");
	 objDpt.pufnGetDpts();
	 cout<<"\nSelect a department to remove professors:";
	 int i;
	 cin>>i;
	 filebuf.open("FbaDpts.FBA",ios::in|ios::out|ios::app|ios::binary);
	 filebuf.seekg((i*DptSize),ios::beg);
	 filebuf.read((char*)&objDpt,DptSize);
	 char *ptrDptN=objDpt.pufnGetDptName();
	 filebuf.close();
	 filebuf.open(ptrDptN,ios::in|ios::app|ios::binary);
	 filebuf.seekg(0,ios::beg);
	 i=0;
	 while(filebuf)
		{
		 filebuf.read((char*)&objProf,ProfSize);
		 cout<<"\n("<<++i<<") "<<objProf.profName;
		}
	 int total=i;
	 cout<<"\n Select a professor to remove:";
	 cin>>i;
	 int k=total-i;
	 filebuf.seekp((i*ProfSize),ios::beg);
	 filebuf.seekg(((i+1)*ProfSize),ios::beg);
	 while(k>0)
		{
		 filebuf.read((char*)&objProf,ProfSize);
		 filebuf.write((char*)&objProf,ProfSize);
		 k--;
		}
	}

void cProfessors::pufnFeedBackForm()
	{
	 objCUI.disMnuHed("FEED BACK FORM");
	 int select;
	 objDpt.pufnGetDpts();
	 cout<<"\n Select a department:";
	 cin>>select;
	 filebuf.open("FbaDpts.FBA",ios::in|ios::out|ios::app|ios::binary);
	 filebuf.seekg((select*DptSize),ios::beg);
	 filebuf.read((char*)&objDpt,DptSize);
	 char *ptrDptN=objDpt.pufnGetDptName();
	 filebuf.close();
	 filebuf.open(ptrDptN,ios::in|ios::out|ios::app|ios::binary);
	 filebuf.seekg(0,ios::beg);
	 select=1;
	 while(!filebuf)
		{
		 filebuf.read((char*)&objProf,ProfSize);
		 cout<<"\n"<<select<<")"<<objProf.profName<<"\t"<<objProf.profCode;
         select++;
		}
     cout<<"\n Select a Professor to make a feed back:";
	 cin>>select;
	 filebuf.close();
	 clrscr();
	 objCUI.disMnuHed("FEED BACK FORM");
	 gotoxy(1,1);
	 cout<<"Enter \t\t E for Exellent \t\t G for Good \t\t F for Fair \t\t P for Poor ";
	 char recive;
	 do
		{
		 gotoxy(3,3);
		 cout<<"1.  The knowledge of Teacher in the subject                  :  [ ]\b\b";
	     cin>>recive;
		}while(!chkAnswer(&recive)==1);
	 objProf.prfnCalculateGrade(0,recive,select,ptrDptN);
	 do
		{
		 gotoxy(3,5);
		 cout<<"2.  Method of teaching                                       :  [ ]\b\b";
         cin>>recive;
		}while(!chkAnswer(&recive)==1);
	 objProf.prfnCalculateGrade(1,recive,select,ptrDptN);
	 do
		{
		 gotoxy(3,7);
		 cout<<"3.  The Teacher's personal aquaintancewith students          :  [ ]\b\b";
	     cin>>recive;
		}while(!chkAnswer(&recive)==1);
	 objProf.prfnCalculateGrade(2,recive,select,ptrDptN);
	 do
		{
		 gotoxy(3,9);
		 cout<<"4.  Teacher's ability to make the students toask questions   :  [ ]\b\b";
	     cin>>recive;
		}while(!chkAnswer(&recive)==1);
	 objProf.prfnCalculateGrade(3,recive,select,ptrDptN);
	 do
		{
		 gotoxy(3,11);
		 cout<<"5.  Willingness to help and guide students outside the class :  [ ]\b\b";
	     cin>>recive;
		}while(!chkAnswer(&recive)==1);
	 objProf.prfnCalculateGrade(4,recive,select,ptrDptN);
	 do
		{
		 gotoxy(3,13);
		 cout<<"6.  Ability to maintain discipline and control in the class  :  [ ]\b\b";
	     cin>>recive;
		}while(!chkAnswer(&recive)==1);
	 objProf.prfnCalculateGrade(5,recive,select,ptrDptN);
	 do
		{
		 gotoxy(3,15);
		 cout<<"7.  Special care for weak students                           :  [ ]\b\b";
	     cin>>recive;
		}while(!chkAnswer(&recive)==1);
	 objProf.prfnCalculateGrade(6,recive,select,ptrDptN);
	 do
		{
		 gotoxy(3,17);
		 cout<<"8.  The Teacher's preperation for the class                  :  [ ]\b\b";
	     cin>>recive;
		}while(!chkAnswer(&recive)==1);
	 objProf.prfnCalculateGrade(7,recive,select,ptrDptN);
	 do
		{
		 gotoxy(3,19);
		 cout<<"9.  The teacher's way of presenting ideas                    :  [ ]\b\b";
	     cin>>recive;
		}while(!chkAnswer(&recive)==1);
	 objProf.prfnCalculateGrade(8,recive,select,ptrDptN);
	 do
		{
		 gotoxy(3,21);
		 cout<<"10. Prompness in evaluatingassignments and test papers       :  [ ]\b\b";
	     cin>>recive;
		}while(!chkAnswer(&recive)==1);
	 objProf.prfnCalculateGrade(9,recive,select,ptrDptN);
	 do
		{
		 gotoxy(3,23);
		 cout<<"11. Term-wise competions of portions                         :  [ ]\b\b";
	     cin>>recive;
		}while(!chkAnswer(&recive)==1);
	 objProf.prfnCalculateGrade(10,recive,select,ptrDptN);

	}

int chkAnswer(char *ans)
	{
	 if(*ans=='E'||*ans=='G'||*ans=='F'||*ans=='P')
		{
		 return(1);
		}
	 else if(*ans=='e'||*ans=='g'||*ans=='f'||*ans=='p')
		{
		 return(1);
		}
	 else
		{
		 cout<<"\a";
		 return(0);
		}
	}

void cProfessors::prfnCalculateGrade(int qNum,char answer,int record,char* ptrDptN=NULL)
	{
	 filebuf.open(ptrDptN,ios::in|ios::out|ios::app|ios::binary);
	 filebuf.seekg((record*ProfSize),ios::beg);
	 filebuf.seekp((record*ProfSize),ios::beg);
	 filebuf.read((char*)&objProf,ProfSize);
     answer=toupper(answer);
	 switch(answer)
		{
		 case 'E':
			 objProf.all4Opt[0]+=1;
			 objProf.each4Opt[qNum][0]+=1;
			 filebuf.write((char*)&objProf,ProfSize);
			 filebuf.close();
			 break;
		 case 'G':
			 objProf.all4Opt[1]+=1;
			 objProf.each4Opt[qNum][1]+=1;
			 filebuf.write((char*)&objProf,ProfSize);
			 filebuf.close();
			 break;
		 case 'F':
			 objProf.all4Opt[2]+=1;
			 objProf.each4Opt[qNum][2]+=1;
			 filebuf.write((char*)&objProf,ProfSize);
			 filebuf.close();
			 break;
       case 'P':
			 objProf.all4Opt[3]+=1;
			 objProf.each4Opt[qNum][3]+=1;
			 filebuf.write((char*)&objProf,ProfSize);
			 filebuf.close();
			 break;
		 default :	cout<<"\n Invalied selection";
		}
	 return;
	}

void cProfessors::pufnDisplayResult(int need,char* ptrDptN,int record=0)
	{
	 switch(need)
		{
		 case 6:			//Compare all professors in a department.
			{
			 filebuf.open(ptrDptN,ios::out|ios::app|ios::binary);
			 filebuf.seekp(0,ios::beg);
			 cout<<"\n Professor Name \t\t\t Toatal E \t Toatal G \t Total F \t Total P";
			 while(!filebuf)
				{
				 filebuf.read((char*)&objProf,ProfSize);
				 cout<<objProf.profName<<"\t\t"<<objProf.all4Opt[0]<<"\t"<<objProf.all4Opt[1]<<"\t"<<objProf.all4Opt[2]<<"\t"<<objProf.all4Opt[3];
				}
			 filebuf.close();
           	}
		 case 7:			// Display full details of a professor.
			{
			 filebuf.open(ptrDptN,ios::out|ios::app|ios::binary);
			 filebuf.seekp((record*ProfSize),ios::beg);
			 filebuf.read((char*)&objProf,ProfSize);
			 cout<<"\n Name :"<<objProf.profName;
			 cout<<"\n Department :"<<*ptrDptN;
			 int i=1,j=0;
			 cout<<"\n Question No. \t Exellent's \t Good's \t Fair's \t Poor's";
			 while(i>=11)
				{
				 cout<<"\n Q"<<i++<<"\t"<<objProf.each4Opt[j][0]<<"\t"<<objProf.each4Opt[j][1]<<"\t"<<objProf.each4Opt[j][2]<<"\t"<<objProf.each4Opt[j][3];
             i++;
				}
     		 cout<<"\n \t\t Total:"<<objProf.all4Opt[0]<<"\t"<<objProf.all4Opt[1]<<"\t"<<objProf.all4Opt[2]<<"\t"<<objProf.all4Opt[3];
			filebuf.close();
			}
		}
	}

// Declaration of functions in cProfessors Class ends here



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
	 textbackground(BLACK);
	 textcolor(BLACK);
	 for(int x=1;x<=80;x++)			// fill entire screen with <spaces> so the screen become black if we change color we get translatory effct
	     {
	      for(int y=2;y<=25;y++)
		  {
		   gotoxy(x,y);
		   cprintf(" ");
		  }
	      }

	 int repeatCond=1;
	 do
		{
		 clrscr();
		 objCUI.disMnuHed("MENU");
		 gotoxy(15,10);
		 cout<<"[1]   Add a Department";
		 gotoxy(15,12);
		 cout<<"[2]   Remove a Department";
		 gotoxy(15,14);
		 cout<<"[3]   Add a Professor";
		 gotoxy(15,16);
		 cout<<"[4]   Remove a Professor";
		 gotoxy(15,18);
		 cout<<"[5]   Feed Back Form";
		 gotoxy(15,20);
		 cout<<"[6]   Compare all professors in a department";
		 gotoxy(15,22);
		 cout<<"[7]   Display full details of a Professor";
		 gotoxy(15,24);
		 cout<<"[8]   Exit From Application";
		 gotoxy(12,29);
		 int i,selection;
		 char *ptrDptN;
		 cout<<"\aSelect an item, [1/2/3/4/5/6/7/8] : [   ]\b\b\b";
		 cin>>selection;
		 delay(1000);
		 clrscr();
		 switch(selection)
			{
			 case 1: case 2:
				 objDpt.pufnDptAdmin(selection);
				 repeatCond=1;
				 break;
			 case 3: case 4:
				 objProf.pufnProfAdmin(selection);
				 repeatCond=1;
				 break;
			 case 5:
				 objProf.pufnFeedBackForm();
				 repeatCond=1;
				 break;
			 case 6:
				 objDpt.pufnGetDpts();
				 cout<<"\n Select a department to compare professors:[ ]\b\b";
				 cin>>i;
				 filebuf.open("FbaDpts.FBA",ios::in|ios::out|ios::app|ios::binary);
				 filebuf.seekg((i*DptSize),ios::beg);
				 filebuf.read((char*)&objDpt,DptSize);
				 ptrDptN=objDpt.pufnGetDptName();
				 filebuf.close();
				 objProf.pufnDisplayResult(selection,ptrDptN,0);
				 repeatCond=1;
				 break;
			 case 7:
				 objDpt.pufnGetDpts();
				 cout<<"\n Select a department to compare professors:[ ]\b\b";
				 cin>>i;
				 filebuf.open("FbaDpts.FBA",ios::in|ios::out|ios::app|ios::binary);
				 filebuf.seekg((i*DptSize),ios::beg);
				 filebuf.read((char*)&objDpt,DptSize);
				 ptrDptN=objDpt.pufnGetDptName();
				 filebuf.close();
				 filebuf.open(ptrDptN,ios::out|ios::app|ios::binary);
				 filebuf.seekg(0,ios::beg);
				 i=1;
				 while(filebuf!=NULL)
					{
					 filebuf.read((char*)&objProf,ProfSize);
					 cout<<"\n("<<i++<<")"<<objProf.pufnGetProf(1)<<"\t"<<objProf.pufnGetProf(0);
					}
				 cout<<"\n Select the professor to display details:[ ]\b\b";
				 cin>>i;
				 objProf.pufnDisplayResult(selection,ptrDptN,i);
				 repeatCond=1;
				 break;
			 case 8:
				 repeatCond=0;
				 break;
			 default:
				 cout<<"\n Wrong Choice\a\a";
				 repeatCond=1;
			}
		}while(repeatCond==1);
	 return;
    }


