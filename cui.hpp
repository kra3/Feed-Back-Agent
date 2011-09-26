/*
* Author : Arun.K.R <the1.arun@gmail.com>
* Created: Nov, 2005
*/

#include <fstream.h>
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>



class cInterface
{ 
 private:
 
 int gdriver, gmode, errorcode;
 int right,bottom;
 void fillData(int);	
 void disTime(int);
 void drawFrame(int,int);
 
 public:
 
 cInterface()
	{
	 gdriver = DETECT;
	 initgraph(&gdriver, &gmode, "G:\\MyFavor\\TC\\BGI");
	 errorcode = graphresult();
	 if (errorcode != grOk)  /* an error occurred */
		{
		 printf("Graphics error: %s\n", grapherrormsg(errorcode));
		 printf("Press any key to halt:");
		 getch();
		 exit(1); /* terminate with an error code */
		}
	 right=getmaxx();
	 bottom=getmaxy();
	} 
	
 ~cInterface()
	{
	 closegraph();
	} 
  void disMnuHed(char*);
}objCUI; 	

void cInterface:: disMnuHed(char* hed)
	{
	 drawFrame(right,bottom);
	 fillData(right);
	 disTime(right);
	 moveto(300,72);
	 settextstyle(7,0,3);
	 settextjustify(1,1);
	 setcolor(10);
	 outtext(hed);
	}

void cInterface::disTime(int right)
	{
	 /* to hold time */
	 struct tm *time_now;
	 time_t secs_now;
	 char str[15];

	 tzset();
	 time(&secs_now);
	 time_now = localtime(&secs_now);
	 strftime(str,15," %A",time_now);
	 moveto(right/14,27);
	 settextjustify(0,1);
	 setcolor(10);
	 outtext(str);
	 strftime(str,15,"%b %d %Y",time_now);
	 moveto(right/20,45);
	 settextjustify(0,0);
	 setcolor(10);
	 outtext(str);
	}

void cInterface::drawFrame(int right,int bottom)			 // draw CUI
	{
	 setcolor(11);
	 setlinestyle(SOLID_LINE,1,NORM_WIDTH);
	 rectangle(2,2,right-2,bottom-2);	 		 //outer rectangle
	 rectangle(9,9,right-9,57);             	 //rectangle covering Heading
	 setlinestyle(SOLID_LINE,1,THICK_WIDTH);
	 rectangle(6,6,right-6,bottom-6);      		 //Innner recangle
	 line(6,60,right-6,60);                		 //makes upper line for Menu display
	 line(6,90,right-6,90);                		 //makes bottom line for menu display
	 line(6,440,right-6,440);              		 //makes line for selection section
	 
	 /* Plot some "stars"  for a sky like enviornment*/
	 for (int j=0 ; j<1000; ++j )
		{
		 putpixel(random(getmaxx()), random(getmaxy()), random( getmaxcolor()-1 )+1);
		} 
	}
	
void cInterface::fillData(int right)
{
 settextstyle(4,0,4);		         	 //font,direction,size
 settextjustify(1,0); 	        	     //horiz'n'vert direction
 moveto(right/2,38);           		     //move CP to position
 setcolor(14);
 outtext("FEED BACK AGENT");
 settextstyle(0,0,1);					 //font,direction,size
 settextjustify(1,1);					 //horiz'n'vert direction
 moveto(right/2,48);
 setcolor(12);
 outtext("Govt. Modal Boys HSS, Thrissur");

 setcolor(10);
 settextjustify(0,2);
 outtextxy(right-81,30,"ARUN.K.R");
 outtextxy(right-101,45,"10+1 Computer Science");
 setcolor(11);
 outtextxy(right-115,15,"Devoloped by:");
}
