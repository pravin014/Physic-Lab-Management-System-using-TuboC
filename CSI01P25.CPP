//try to put options at side/top........sucess
//future updates:   1. drop dow box disaspers if mouse is not on it.
//                  2. drop box available in all functions
//		    3. give total stock/req value
//                  4. tt-view,edit
//                  5. stu-edit,delete
//                  6. stock,req-delete
//                  7. clearance level
//                  8. add logo, effects
//
//most recent //updated on (1/12/2016)
//added clearance level but not implemented.....
//use pa in all function............
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<ctype.h>
#include<dos.h>
void obcol(int,int,int);
void startupdisp();
void signindisp();
void signupdisp();
void startenddisp();
int logboxdisp();
int signinupdisp();
int signupindisp();
int mousein(int,int,int,int);
int mouseon(int C[],int,int col=1,int pa=5);
int pa[100];
int page=-10;
void pagedisp(int a=1,int opt[]=pa, int col=15);
struct varchar
{
int pos;
char ch[100];
int store;
varchar()
  { pos=0; strcpy(ch,"\0"); store=0; }
};

struct cor
{
int on,A[4];
cor()
  { on=0; A[1]=0; A[2]=0; A[3]=0; A[4]=0; }
void getcor1(int x[])
  {
  for(int i=0; i<4;i++)
    A[i]=x[i];
  }
void getcor2(int x1,int y1,int x2,int y2)
  {
  A[0]=x1; A[1]=y1; A[2]=x2; A[3]=y2;
  }
};

void date(int D[3],int aim=0,int x=-1,int y=-1)
{
int i=1,d[12]={31,28,31,30,31,30,31,31,30,31,30,31};
while(i)
{
if(x>=0&&y>=0) gotoxy(x,y);
if(aim!=1)cout<<" Enter date: ";
cin>>D[0]>>D[1]>>D[2];
if(D[1]>=1&&D[1]<=12&&D[0]>=1&&((aim==2&&D[2]>=2015)||D[2]>1900)&&((!D[2]%4&&D[0]<=29)||(D[0]<=d[D[1]-1])))
       i=0;
if(i)
  {
  cout<<"\n Enter a valid date ";
  gotoxy(1,5);cout<<"                      ";
  }
}
if(aim==2) { D[2]-=2015; }
}///0-cout ent date,store exact date////1-store ext date////2-cout ent date,store subtract date.

void readword(varchar &read,int aim=1,int x=-1,int y=-1,int no=10)
{
int asc;
asc=getch();

if(x>=0&&y>=0) gotoxy(x,y);
else if(read.store==1&&asc!=13)
	{ for(x=0;x<strlen(read.ch);x++) cout<<"\b \b";}

if(asc==13) { read.store=2;  read.pos=0; }
else if(asc==8)
	{ if(read.ch[0])
		{ read.ch[--read.pos]='\0';
		  if(aim==1||aim==3) cout<<read.ch;
		  if(aim==2) for(x=0;x<read.pos;x++) cout<<"*";
		  cout<<" \b";
		}
	}
else
  {
    read.store=1;
    if(aim<3||(aim==3&&isdigit(asc)))
       {
       read.ch[read.pos++]=asc;
       read.ch[read.pos]='\0';
       }
    if(aim==1||aim==3)    cout<<read.ch;
    if(aim==2)    for(x=0;x<read.pos;x++) cout<<"*";
    if(aim==3&&read.pos==no)    {  read.store=2; read.pos=0; }
  }
}////1-string////2-password////3-phno.

void readword2(varchar &read,int aim=1,int x=0,int y=0,int sf=0,int sd=0,int ss=1,int col=15,int p=2)//,int mx1=0,int mx2=650, int my1=0,int my2=480)
{
int asc,k;
asc=getch();

if(asc==13)
	{ read.store=(aim<=2)?2:3;  if(aim<=2) read.pos=0; }
else if(asc==8)
	{ if(read.ch[0])
	     { read.ch[--read.pos]='\0';
	       pagedisp(p);
	       //cout<<"1";
	       for(k=0;k<500;k++);
	       setcolor(col);
	       settextstyle(sf,sd,ss);
	       if(aim==1||aim==3)
		{ outtextxy(x,y,read.ch); }
	       if(aim==2||aim==4)
		  for(k=0;k<read.pos;k++)
			outtextxy(x+k*textwidth("*"),y,"*");
	     }
	}
else
  { settextstyle(sf,sd,ss); setcolor(col);
    read.store=1;
    read.ch[read.pos++]=asc;
    read.ch[read.pos]='\0';
    if(aim==1||aim==3)    outtextxy(x,y,read.ch);
    if(aim==2||aim==4)    for(k=0;k<read.pos;k++) outtextxy(x+k*(textwidth("*")),y,"*");

  }

}


void outtextxyc(int x,int y,char ch[],int c)
{ setcolor(c); outtextxy(x,y,ch); }

class pass
{
varchar uname,upword;
varchar rname,rmail;
int D[3];
int clearance;
varchar uphno;
public:
void ininfo()
    {
    cout<<"\n Enter user name : "; do{ readword(uname); }while(uname.store==1);
    cout<<"\n Enter password  : "; do{ readword(upword,2);}while(upword.store==1);
    }
int confrimp()
    {
    varchar temp;
    cout<<"\n Re-enter password: ";
    do{ readword(temp,2); }while(temp.store==1);
    if(!strcmp(upword.ch,temp.ch)) return 1;
    return 0;
    }
void incclear(int aim)
    {
    clearance=aim;
    }
void upinfo()
    {
    cout<<"\n Enter Name: ";      do{ readword(rname);}while(rname.store==1);
    cout<<"\n Enter Dob : ";        date(D,1);
    cout<<" Enter Phone no: ";    do{ readword(uphno,3);}while(uphno.store==1);   getch();
    cout<<"\n Enter Mail id : ";    do{ readword(rmail);}while(rmail.store==1);
    }
void disp()
    {
    cout<<"\n User name  :   "<<uname.ch;
    cout<<"\n Password   :   "<<upword.ch;
    }
void fulldisp()
    {
    cout<<"\n Name: "<<rname.ch;
    cout<<"\n Dob : "<<D[0]<<" "<<D[1]<<" "<<D[2];
    cout<<"\n Phone no: "<<uphno.ch;
    cout<<"\n Mail id : "<<rmail.ch;
    }
void getp()
    { do{ readword(upword,2); }while(upword.store==1);  }
void assign(varchar u,varchar p,int aim=0)
    {
    if(aim==1||!aim) uname=u;
    if(aim==2||!aim) upword=p;
    }
char* retun()
    { return uname.ch; }
char* retup()
    { return upword.ch; }
char* retrn()
    { return uname.ch; }
int retcl()
    { return clearance; }
pass()
    {
    clearance=0;       ////0-guest////1-user////2-admin
    }
};

void userdisp(pass a,int b=15);                  ////////////////////////

class stud
{
int rno;
varchar rname;
public:
void acpstud()
  {
  cout<<" Enter rno : ";  cin>>rno;
  cout<<" Enter name: ";  do{ readword(rname); }while(rname.store==1);
  }
void dispstud()
  {
  cout<<" Rno: "<<rno;
  cout<<"   Name: "<<rname.ch;
  }
void getno()
  { cout<<" Enter rno : ";  cin>>rno; }
void getname()
  { cout<<" Enter name: "; do{ readword(rname); }while(rname.store==1);  }
int retrno()
  { return rno; }
char* retname()
  { return rname.ch; }
stud()
  { rno=0; }
};

class att:public stud
{
int date[32][12][15];

public:
int acpatt(int d,int m,int y,int aim=0)
  {
  dispstud();
  if(aim) cout<<"\n press 1 if present, 0 is absent     ";
  for(int i=strlen(retname());i<25;i++)  { cout<<" ";  }       //for arranging orderly
  cin>>date[d][m][y];
  return date[d][m][y];
  }
int dispatt(int d,int m,int y)
  {
  dispstud();
  for(int i=strlen(retname());i<25;i++)  { cout<<" ";  }       //for arranging orderly
  if(date[d][m][y]) cout<<"present\n";
  else cout<<"absent\n";
  if(date[d][m][y]>0) return 1;
  else return 0;
  }
int retdate(int d,int m,int y)
  { return date[d][m][y]; }
att()
  {
  int i,j,k;
  for(i=0;i<31;i++)
   { for(j=0;j<12;j++)
       { for(k=0;k<15;k++)
	  { date[i][j][k]=0; } } }
  }
};

class stock
{
int sno;
char sname[50],sdes[50];
int sqty,sprice;
public:
void accept(int aim=0)
	{
	if(!aim) { cout<<" Item no          :   ";  cin>>sno;  }
	cout<<" Item name        :   ";  gets(sname);
	cout<<" Item description :   ";  gets(sdes);
	cout<<" Item quantity    :   ";  cin>>sqty;
	cout<<" Item price       :   ";  cin>>sprice;
	}
void display()
	{
	cout<<"\n Item no          :   "<<sno;
	cout<<"\n Item name        :   "<<sname;
	cout<<"\n Item description :   "<<sdes;
	cout<<"\n Item quantity    :   "<<sqty;
	cout<<"\n Item price       :   "<<sprice;
	}
void getno()
	{ cout<<"\n Item no          : "; cin>>sno; }
int retno()
	{ return sno; }
};

int norec()                                         /////////
{
att a;
int no=0;
ifstream temp("plmstu01.dat",ios::binary);
while(temp.read((char*)&a,sizeof(a)))
{ no++; }
return no;
}
int norec(char fname[50])                          ////////////
{
stock a;
int no=0;
ifstream temp(fname,ios::binary);
while(temp.read((char*)&a,sizeof(a)))
{ no++; }
return no;
}

int  chk(pass p,int aim)
{
int rst=0;
pass cmp;
fstream temp("plmpass1.dat",ios::binary|ios::in|ios::out);
while(!temp.eof())
  {
  temp.read((char*)&cmp,sizeof(cmp));
  if(temp.eof())  { break; }
  else if(!strcmp(cmp.retun(),p.retun()))
     {
     rst=1;
     if(aim==1) { break; }
     if(aim==2||aim==3||aim==-2)
	{
	if(!strcmp(cmp.retup(),p.retup()))
	     {
	     rst=2;
	     if(aim==3)
		{
		rst=3;
		cout<<"\n Enter new password: ";
		p.getp();
		temp.seekg(temp.tellg()-sizeof(p),ios::beg);
		temp.write((char*)&p,sizeof(p));
		cout<<"\n Password changed successfully\n";
		}
	     }
	else if(aim>=0) cout<<"\n incorrect username/password";
	break;
	}
     }

  }
temp.close();
if(!rst&&aim!=1&&aim>=0) cout<<"\n Incorrect username/password";
return rst;
}

void chcl1(pass &p)            //change clearance
{
varchar read;
int ch=0;
pass admin;
pagedisp(-1); pagedisp(2);
gotoxy(1,6);
cout<<"\n Enter mode of change     ";
cin>>ch;
if(ch==1)
  {
  admin.ininfo();
  if(chk(admin,2)==2)
	ch=admin.retcl();
  else ch=0;
  }
else if(ch==2)
  {
  cout<<"Enter password : ";
  do{ readword(read,2); }while(read.store==1);
  if(strcmpi(read.ch,"topsecret INFO001"))
	ch=2;
  else { ch=0; cout<<"\n Incorrect password\n"; }
  }
if(ch==1)
  {
  cout<<"\n Enter clearance level (0/1)   ";
  cin>>ch;
  if(ch==1||ch==0) { p.incclear(ch); }
  }
else if(ch==2)
  {
  cout<<"\n Enter clearance level (0/1/2)   ";
  cin>>ch;
  if(ch==2||ch==1||ch==0) { p.incclear(ch); }
  }
if(ch>=0&&ch<=2)
{
pass a;
fstream P("plmpass1.dat",ios::binary|ios::in|ios::out);
while(P.read((char*)&a,sizeof(a)))
   {
   if(!strcmp(p.retun(),a.retun()))
       {
       P.seekg(P.tellg()-sizeof(p),ios::beg);
       P.write((char*)&p,sizeof(p));
       }
   }
P.close();
}
}


int signup(pass &p)
{
int rst=0;
if(!chk(p,1))
    {
    if(!p.confrimp())    { cout<<"\n Password mismatch "; return 0; }
    ofstream temp("plmpass1.dat",ios::binary|ios::app);
	cout<<"\n account created";
    p.upinfo();
    temp.write((char*)&p,sizeof(p));
    cout<<"\n Information successfully updated\n";
    temp.close();
    rst=1;
    }
else
  cout<<"\n username already exists\n";
return rst;
}

void userdetails()
{
int j=0;
pass a;
varchar p;
cout<<"\n Enter password: ";
do{ readword(p,2); }while(p.store==1);
ifstream P("plmpass1.dat",ios::binary);
if(!strcmp(p.ch,"topsecret info"))
while(P.read((char*)&a,sizeof(a)))
{
j++;
a.disp();
if(j%8==0) { getch(); pagedisp(-1); pagedisp(); }
}
else
cout<<" Incorrect Password\n";
P.close();
}

pass useredit(pass p)
{
pass a;
int mou;

while(mou!=2)
{
setcolor(7);
rectangle(40,200,90,230);
rectangle(120,200,170,230);
mou=mousein(40,200,90,230);  setcolor(9);
if(mou>=0)
    { setcolor(4);
      if(mou==1)
       { fstream P("plmpass1.dat",ios::binary|ios::in|ios::out);
	 while(P.read((char*)&a,sizeof(a)))
	   {
	   if(!strcmp(p.retun(),a.retun()))
		{
		pagedisp(-1); pagedisp();
		gotoxy(1,3);
		p.upinfo();
		P.seekg(P.tellg()-sizeof(p),ios::beg);
		P.write((char*)&p,sizeof(p));
		}
	   }
	 P.close();
       }
    }
settextstyle(6,0,1);
outtextxy(50,200,"Edit");
mou=mousein(120,200,170,230); setcolor(9);
if(mou>=0) { setcolor(4); if(mou==1) break; }
outtextxy(130,200,"Back");
}
pagedisp(-1);
return p;
}

pass giveuser(pass p)
{
pass a;
ifstream P("plmpass1.dat",ios::binary);
while(P.read((char*)&a,sizeof(a)))
    {
    if(!strcmp(p.retun(),a.retun()))
	{ break; }
    }
P.close();
return a;
}

char* filename(int x=-1,int y=-1)
{
char cname[50],fname[50]="plms";
if(x>=0&&y>=0) gotoxy(x,y);
cout<<"\ Enter class  "; cin>>cname;
strcat(fname,cname); strcat(fname,".dat");
return fname;
}

void stodisp(char fname[50])
{
int i=0;
ifstream S(fname,ios::binary);
stock o;
while(S.read((char*)&o,sizeof(o)))
	{ if(i%3==0)
	    {
	    pagedisp(-1); pagedisp(2); i=0; gotoxy(1,7);
	    if(!strcmpi(fname,"plmsto_1.dat")) cout<<" Stock details  ";
	    else if(!strcmpi(fname,"plmreq_1.dat")) cout<<" Requirement details  ";
	    }
	  cout<<"\n"; o.display(); i++;
	  if(i%3==0) { getch(); }
	}
S.close();
}

void stoinput(char fname[50])
{
stock get,a;
pagedisp(-1); pagedisp(2);
gotoxy(1,6);
if(!strcmpi(fname,"plmsto_1.dat")) cout<<" Stock\n";
else if(!strcmpi(fname,"plmreq_1.dat")) cout<<" Requirement\n";

ifstream P(fname,ios::binary);
get.getno();
while(P.read((char*)&a,sizeof(a)))
  {
  if(get.retno()==a.retno())
     {	cout<<" given item no. already exits. try another no.\n";
	P.close(); return; }
  }
P.close();
get.accept(1);
fstream S(fname,ios::binary|ios::app);
S.write((char*)&get,sizeof(get));
S.close();
cout<<" Added one item\n";
}

void stoedit(char fname[50])
{
int no;
stock a;
fstream temp(fname,ios::binary|ios::in|ios::out);
gotoxy(1,6);
if(!strcmpi(fname,"plmsto_1.dat")) cout<<" Stock\n";
else if(!strcmpi(fname,"plmreq_1.dat")) cout<<" Requirement\n";
cout<<"\n Enter item no:  ";
cin>>no;
while(temp.read((char*)&a,sizeof(a)))
  {
  if(no==a.retno())
   {
   cout<<"\n old entries: "; a.display();
   cout<<"\n new entries:\n";a.accept();
   temp.seekg(temp.tellg()-sizeof(a),ios::beg);
   temp.write((char*)&a,sizeof(a));
   temp.close(); return;
   }
  }
cout<<"\n item no. not found\n";
temp.close();
}

void studinput()
{
pagedisp(-1); pagedisp(2);
char fname[50]; strcpy(fname,filename(1,7));
att cmp,a;
ifstream P(fname,ios::binary);
cmp.getno();
while(P.read((char*)&a,sizeof(a)))
  {
  if(cmp.retrno()==a.retrno())
     {	cout<<" Given roll no. already exits.\n";
	P.close(); return; }
  }
P.close();
cmp.getname();
fstream S(fname,ios::binary|ios::app);
S.write((char*)&cmp,sizeof(cmp));
S.close();
cout<<"\n Added one record\n";
}

void studattinput()
{
pagedisp(-1); pagedisp(2);
char fname[50]; strcpy(fname,filename(1,7));
att cmp,a;
int D[3],no=0,to=0;
date(D,2,1,8);
fstream P(fname,ios::binary|ios::in|ios::out);
cout<<"\n press 1 if present, 0 is absent\n";
while(P.read((char*)&a,sizeof(a)))
  {
  to++;
  no+=a.acpatt(D[0],D[1],D[2]);
  P.seekg(P.tellg()-sizeof(a),ios::beg);
  P.write((char*)&a,sizeof(a));
  if(to%10==0) { pagedisp(-1); pagedisp(2); gotoxy(1,6); }
  }
cout<<"\n No. on roll:"<<to;
cout<<"\n No. of students present:"<<no;
cout<<"\n No. of absentees:"<<to-no;
P.close();
}

void studisp()
{
char fname[50]; strcpy(fname,filename(1,7));
int j=0;
att a;
ifstream P(fname,ios::binary);
while(P.read((char*)&a,sizeof(a)))
   {
   if(j%15==0) { gotoxy(1,8); cout<<" Student Details\n";}
   cout<<"\n";
   a.dispstud();
   j++; if(j%15==0) { getch(); pagedisp(-1); pagedisp(); j=0; }
   }
P.close();
}

void stuattdisp(int aim=0)
{
att a;
char fname[50]; strcpy(fname,filename(1,6));
int D[3],no=0,to=0;
date(D,2,1,7);
ifstream P(fname,ios::binary);
gotoxy(1,8);
while(P.read((char*)&a,sizeof(a)))
   {
   to++;
   if(!aim) {
	    no+=a.dispatt(D[0],D[1],D[2]);
	    if(to%15==0) { getch(); pagedisp(-1); pagedisp(); gotoxy(1,8); }
	    }
   else if(aim==1) no+=a.retdate(D[0],D[1],D[2]);
   }
cout<<"\n No. on roll:"<<to;
cout<<"\n No. of students present:"<<no;
cout<<"\n No. of absentees:"<<to-no;
P.close();
}

int signinbuttons(int &j,int &log)
{
settextstyle(7,0,1); outtextxyc(10,4,"EXIT",(mousein(5,5,60,27)==0)?12:4);

j=mousein(355,275,495,300);
if(j>=0)

   { settextstyle(3,0,1);
     outtextxyc(395,275,"Sign in",3);
     if(j==1)  { log=-1; return -1; }   }
else
   { settextstyle(3,0,1);
     outtextxyc(395,275,"Sign in",1); }

j=mousein(352,321,502,340);
if(j>=0)
   { settextstyle(5,0,1);
     outtextxyc(355,315,"Create an account?",8);
     if(j==1)  { log=-2; return -1; }   }
else
  { settextstyle(5,0,1);
     outtextxyc(355,315,"Create an account?",9); }
return 0;
}

int signin(pass &temp)
{
varchar read,read2;
int j=1,log=0;
pagedisp(-7);
while(log==0)
{
if(mousein(5,5,60,27)==1)  { log=-3; break;}         //click exit option
if(mousein(415,200,545,225)==1||j==1)
	{
	  if(read.store==3) { read.store=1; read.pos=strlen(read.ch); }
	  while(1)
	   {
	   if(kbhit())
		{ readword2(read,3,420,200,1,0,1,9,-7);
		  for(j=0;j<strlen(read2.ch);j++)
		     outtextxyc(420+j*textwidth("*"),230,"*",9); }

	   if(mousein(415,200,545,225)<=-2)
		     {  j=0; break; }
	   if(read.store==3) { j=2; break; }
	   if(signinbuttons(j,log)==-1) break;
	   }
	}
if(mousein(415,230,545,255)==1||j==2)
	{
	  if(read2.store==3) { read2.store=1; read2.pos=strlen(read2.ch); }
	  while(1)
	   {
	   if(kbhit())
		{ readword2(read2,4,420,230,1,0,1,9,-7);
		  outtextxyc(420,200,read.ch,9);  j=0;}
	   if(mousein(415,230,545,255)<=-2)
			break;
	   if(read2.store==3&&j!=2) { log=-1; break; }
	   if(signinbuttons(j,log)==-1) break;
	   }
	j=0;
	}
signinbuttons(j,log);
}
read.store=2; read2.store=2;
read.pos=0;   read2.pos=0;
temp.assign(read,read2);
return log;
}

void main()
{
union REGS i,o;
int gd=DETECT,gm;
int log=0,clr=1,mou=0;
int mx,my,mco=0;
int j,k=0;
char ch;
varchar read,read2;
pass user,temp;
for(j=0;j<100;j++)    pa[j]=-2;     ////-2-nothing,-1 selected,0+ mouseon colour
cor c[100];
for(j=0;j<100;j++)
c[j].getcor2(0,0,0,0);

c[51].getcor2(10,34,92,60);c[52].getcor2(92,34,184,60);c[53].getcor2(184,34,276,60);c[54].getcor2(276,34,368,60);c[55].getcor2(368,34,460,60);
c[61].getcor2(10,76,92,94);c[62].getcor2(10,96,92,114);c[63].getcor2(10,116,92,134);c[64].getcor2(10,136,92,154);
c[66].getcor2(92,76,184,94);c[67].getcor2(92,96,184,114);c[68].getcor2(92,116,184,134);
c[71].getcor2(184,76,276,94);c[72].getcor2(184,96,276,114);
c[76].getcor2(276,76,368,94);c[77].getcor2(276,96,368,114);c[78].getcor2(276,116,368,134);c[79].getcor2(276,136,368,154);
c[81].getcor2(368,76,460,94);c[82].getcor2(368,96,460,114);c[83].getcor2(368,116,460,134);c[84].getcor2(368,136,460,154);

clrscr();
initgraph(&gd,&gm,"c://Turboc3//bgi");
getch();

i.x.ax=1; int86(0x33,&i,&o);

startupdisp();
start:
startenddisp();

setcolor(1);
sign:
log=signin(user);
if(log==-2)
   {                                    //////graphics...
   pagedisp(-1);
   cout<<"\n NEW ACCOUNT\n";
   while(log!=1)
     { user.ininfo();  log=signup(user);
       if(log!=1)
	 {
	 cout<<"\n Press B to go back   "; cin>>ch;
	 if(ch=='B'||ch=='b')  goto sign;
	 }
     }
   }
if(log==-1)
   {
   if(chk(user,-2)==2)
	{ user=giveuser(user); log=1; outtextxy(100,200," Logged In"); }
   }
if(log!=-3&&log!=1)
   {
   pagedisp(-1);
   pagedisp(-7);
   while(1)
     {
     settextstyle(0,0,1);
     outtextxyc(320,360,"Incorrect username/password",4);
     if(kbhit()||mousein(0,0,640,420)>=1) { goto sign; }
     }
   }
if(log==-3) { log=0; }
pagedisp(-1); pagedisp(3);
page=2;
while(log)
{
mco=0;
if(read.store==2) { strcpy(read.ch,"\0"); read.store=0; }
if(page<2) { page=2; settextstyle(1,0,1); outtextxyc(50,420,read.ch,6); }
pagedisp(page); userdisp(user,mou);

if(page==3) { settextstyle(1,0,1); outtextxyc(50,420,read.ch,6); }

if(kbhit())  {  if(clr==1)
		 { read.store=1; pagedisp(-1); pagedisp(page); userdisp(user,mou); clr=0; }
		pagedisp(-1);
		readword2(read,1,50,420,1,0,1,6,2);

	     }

i.x.ax=3;   int86(0x33,&i,&o);
mx=o.x.cx;   my=o.x.dx;   mco=o.x.bx;

mou=mousein(0,3,620,400);
if(mou>0&&page==3) { page=2; pagedisp(-1); pagedisp(page); }
if(mou==2) { gotoxy(1,1); cout<<" "<<mx<<" "<<my<<(!mx%100,' ')<<(!my%100,' '); clr=2; }
else if(clr==2) { gotoxy(1,1); cout<<"        "; gotoxy(1,3); }

for(j=51;j<=55;j++)
     if(mouseon(c[j].A,j)==-1)  {  pa[1]=j;  break; }
if(pa[1]>=51&&pa[1]<=55)
  for(k=56+(pa[1]%10)*5;k<=60+(pa[1]%10)*5;k++)
     if(mouseon(c[k].A,k)==-1) 	{ pa[1]=k; break; }

if(!(j>55&&pa[j]==-1))  pagedisp(2);
if(pa[pa[1]]==-2) pa[1]=-2;

mou=mousein(495,3,610,26);
if(mou>=0)  { if(mou==1) { page=logboxdisp(); pagedisp(-1); pagedisp(page); } mou=12; }
else { mou=9; }



if(!strcmpi(read.ch,"graphon"))  { gotoxy(6,25); cout<<"graphon  "; cin>>page; }
if(!strcmpi(read.ch,"graphoff")) { page=2; }

if((read.store==2&&!strcmpi(read.ch,"stockdetails"))||pa[78]==-1) { pa[78]=-2; pa[54]=-2; stodisp("plmsto_1.dat");  page=3; }
if((read.store==2&&!strcmpi(read.ch,"stockinput"))||pa[76]==-1)   { pa[76]=-2; pa[54]=-2; stoinput("plmsto_1.dat"); page=3; }
if((read.store==2&&!strcmpi(read.ch,"stockedit"))||pa[77]==-1)    { pa[77]=-2; pa[52]=-2; stoedit("plmsto_1.dat");  page=3; }

if((read.store==2&&!strcmpi(read.ch,"reqdetails"))||pa[83]==-1) { pa[83]=-2; pa[55]=-2; stodisp("plmreq_1.dat");  page=3; }
if((read.store==2&&!strcmpi(read.ch,"reqinput"))||pa[81]==-1)   { pa[81]=-2; pa[55]=-2; stoinput("plmreq_1.dat"); page=3; }
if((read.store==2&&!strcmpi(read.ch,"reqedit"))||pa[82]==-1)    { pa[82]=-2; pa[55]=-2; stoedit("plmreq_1.dat");  page=3; }

if((read.store==2&&!strcmpi(read.ch,"stuinput"))||pa[61]==-1)   { pa[61]=-2; pa[51]=-2; studinput();  page=3; }
if((read.store==2&&!strcmpi(read.ch,"studisp"))||pa[63]==-1)    { pa[63]=-2; pa[51]=-2; studisp();    page=3; }

if((read.store==2&&!strcmpi(read.ch,"stuattinput"))||pa[66]==-1)  { pa[66]=-2; pa[52]=-2;  studattinput(); page=3; }
if((read.store==2&&!strcmpi(read.ch,"stuattdisp"))||pa[67]==-1)   { pa[67]=-2; pa[52]=-2; stuattdisp();   page=3; }
if((read.store==2&&!strcmpi(read.ch,"stuattreport"))||pa[68]==-1) { pa[68]=-2; pa[52]=-2; stuattdisp(1);  page=3; }

pa[62]=-2; pa[64]=-2; pa[79]=-2; pa[84]=-2;
pa[71]=-2; pa[72]=-2;

if((read.store==2&&(!strcmpi(read.ch,"profile")||!strcmpi(read.ch,"useredit")))||page==-4)
     { gotoxy(1,4); user.fulldisp(); user=useredit(user); page=3; }
if((read.store==2&&!strcmpi(read.ch,"changepassword"))||page==-3)
     { gotoxy(1,4);     temp.ininfo();
       if(!strcmp(temp.retun(),user.retun())) { chk(temp,3); }
       else cout<<"\n Incorrect username/password";   page=3; }
if((read.store==2&&!strcmpi(read.ch,"logout"))||page==-2)
	{ pagedisp(-1); setcolor(6); settextstyle(3,0,1);
	  outtextxy(500,2," Logged out");
	  log=0; goto start; }
if(read.store==2&&!strcmpi(read.ch,"userdetails")) { userdetails(); page=3; }
if(read.store==2&&!strcmpi(read.ch,"clearance")) { chcl1(user); }


if(read.store==2&&!strcmpi(read.ch,"clrscr")) { clrscr(); cleardevice(); }
if(read.store==2&&!strcmpi(read.ch,"exit")||page==-5)  { break; }
}
//getch();
}


int mousein(int x1,int y1,int x2,int y2)
{
union REGS i,o;
int mx,my,mco;
i.x.ax=1;   int86(0x33,&i,&o);
i.x.ax=3;   int86(0x33,&i,&o);
mx=o.x.cx;   my=o.x.dx;   mco=o.x.bx;
if(mx>=x1&&mx<=x2&&my>=y1&&my<=y2)
   return mco;
else if(mx<x1||mx>x2||((mx>=x1&&mx<=x2)&&(my<y1||my>y2)))
   return (-1*mco)-1;                           /////everything out is subtracted by 1
}

int mouseon(int c[4],int p,int col,int pag)//(int x1,int y1,int x2,int y2,int p,int col,int pag)
{
int mou=mousein(c[0],c[1],c[2],c[3]);
if(mou>=0&&pa[p]!=-1&&page<pag) { pa[p]=col; if(mou==1) { pa[p]=-1; pagedisp(-1); return -1; } }
else if(pa[p]==-1&&mou<=-2)  { pa[p]=-2; pagedisp(-1); }
else if(pa[p]>=0&&mou<0) { pa[p]=-2; pagedisp(-1); }
return 0;
}

int signinupdisp()
{
setcolor(8);
int chk=mousein(224,328,392,345);
if(chk>=0)
   {
   setcolor(1);
   if(chk==1) { return 2; }
   }
outtextxy(225,325,"Create a account?");
return 1;
}

void startupdisp()
{
for(int j=0;j<=5;j++)
     {
     setcolor(j+1);
     settextstyle(1,0,j+2);
     outtextxy(270-j*28,200-j*3,"PHYSICS LAB");
     outtextxy(245-j*25,250-j*2,"MANAGEMENT");
     delay(100);
     if(j!=5){cleardevice();}
     }
getch();
for(j=5;j>0;j--)
     {
     setcolor(j+3);
     settextstyle(1,0,j+2);
     outtextxy(j*2+145,55*j-55,"PHYSICS LAB");
     outtextxy(345-j*44,55*j-55,"MANAGEMENT");
     delay(100);
     if(j>1){cleardevice();}
     }
}

void startenddisp()
{
setcolor(4);
settextstyle(1,0,3);
outtextxy(147,0,"PHYSICS LAB");
outtextxy(301,0,"MANAGEMENT");
setcolor(1);
line(0,30,650,30);
line(135,0,135,30);
line(460,0,460,30);
}

void signindisp()
{
setcolor(7);
rectangle(150,110,480,370);     //next box
rectangle(140,100,490,380);     //outermost box
rectangle(200,275,430,310);     //enter box
rectangle(260,186,470,212);     //un box
rectangle(260,218,470,244);     //pass box
settextstyle(3,0,1);
setcolor(8);
outtextxy(270,185,"Username");
outtextxy(270,219,"Password");
outtextxy(280,135,"Signin");
outtextxy(160,185,"Username: ");
outtextxy(160,219,"Password:");
}
void signupdisp()
{
cleardevice();
setcolor(7);
rectangle(150,110,480,370);
rectangle(140,100,490,380);
settextstyle(3,0,1);
setcolor(8);

}

void pagedisp(int p,int opt[],int col)
{
if(p==-1)  { clrscr(); cleardevice(); }
if(p!=-1)  { startenddisp(); setcolor(7); rectangle(10,415,620,450); }
if(p>=2)
	{
	setcolor(1);
	rectangle(10,34,460,60);
	line(92,34,92,60);   line(184,34,184,60);
	line(276,34,276,60); line(368,34,368,60);

	settextstyle(0,0,1);
	outtextxyc(25,45,"STUDENT",(opt[51]>0)?opt[51]:12);
	outtextxyc(99,45,"ATTENDANCE",(opt[52]>0)?opt[52]:12);
	outtextxyc(192,45,"TIME TABLE",(opt[53]>0)?opt[53]:12);
	outtextxyc(302,45,"STOCK",(opt[54]>0)?opt[54]:12);
	outtextxyc(372,45,"REQUIREMENT",(opt[55]>0)?opt[55]:12);

	}
if(p>=2&&opt[51]==-1)
   {
   settextstyle(0,0,1);
   setcolor(1);
   rectangle(10,60,92,155);
   outtextxyc(39,75,"Add" ,(opt[61]>0)?opt[61]:12);
   outtextxyc(37,95,"Edit",(opt[62]>0)?opt[62]:12);
   outtextxyc(37,115,"View",(opt[63]>0)?opt[63]:12);
   outtextxyc(29,135,"Delete",(opt[64]>0)?opt[64]:12);
   }
if(p>=2&&opt[52]==-1)
   {
   settextstyle(0,0,1);
   setcolor(1);
   rectangle(92,60,184,135);
   outtextxyc(122,75,"Take",(opt[66]>0)?opt[66]:12);
   outtextxyc(122,95,"View",(opt[67]>0)?opt[67]:12);
   outtextxyc(116,115,"Report",(opt[68]>0)?opt[68]:12);
   }
if(p>=2&&opt[53]==-1)
   {
   settextstyle(0,0,1);
   setcolor(1);
   rectangle(184,60,276,115);
   outtextxyc(215,75,"View",(opt[71]>0)?opt[71]:12);
   outtextxyc(215,95,"Edit",(opt[72]>0)?opt[72]:12);
   }
if(p>=2&&opt[54]==-1)
   {
   settextstyle(0,0,1);
   setcolor(1);
   rectangle(276,60,368,155);
   outtextxyc(303,75,"Input" ,(opt[76]>0)?opt[76]:12);      //////
   outtextxyc(307,95,"Edit",(opt[77]>0)?opt[77]:12);
   outtextxyc(307,115,"View",(opt[78]>0)?opt[78]:12);
   outtextxyc(299,135,"Delete",(opt[79]>0)?opt[79]:12);
   }
if(p>=2&&opt[55]==-1)
   {
   settextstyle(0,0,1);
   setcolor(1);
   rectangle(368,60,460,155);
   outtextxyc(395,75,"Input" ,(opt[81]>0)?opt[81]:12);
   outtextxyc(399,95,"Edit",(opt[82]>0)?opt[82]:12);
   outtextxyc(399,115,"View",(opt[83]>0)?opt[83]:12);
   outtextxyc(391,135,"Delete",(opt[84]>0)?opt[84]:12);
   }
if(p==-7)
    {
    pagedisp(-1);
    startenddisp();
    setcolor(7);
    rectangle(300,120,550,350);         //signin box
    rectangle(5,5,60,27);               //exit box
    settextstyle(7,0,1); outtextxyc(10,4,"EXIT",4);
    settextstyle(7,0,4);
    outtextxyc(340,135,"Spark Tech",6);
    settextstyle(3,0,1);
    outtextxyc(315,200,"Username  ",4);
    outtextxyc(315,230,"Password  ",4);
    outtextxyc(395,275,"Sign in",1);
    settextstyle(5,0,1);
    outtextxyc(355,315,"Create an account?",9);
    setcolor(7);
    rectangle(415,200,545,225);
    rectangle(415,230,545,255);
    rectangle(355,275,495,300);
    }

}

void userdisp(pass p,int col)
{
setcolor(7);
rectangle(495,3,610,26);
setcolor(col);
settextstyle(6,0,1);
outtextxy(550-4*strlen(p.retrn())+4,0,p.retrn());
}
//-7 - signin -6 - signup -5 - exit -4 - profile -3 - password -2 - logout
//-1 - clear  1 - blank border  2 - select option  3 - in function
//51 - student    //52 - Att    //53 - TT    //54 - Stock    //55 - Req
//61-65 - Student    //66-70 - Att     //71-75 - TT
//76-80 - Stock      //81-85 - Req
int logboxdisp()
{
int x,y,z,a,m=1;
setcolor(7);
rectangle(495,31,610,150);
settextstyle(3,0,1);
while(m>=0)
{
x=y=z=a=6;
m=mousein(526,33,570,54);  if(m>=0) { x=8; if(m==1) return -4; }
setcolor(x); outtextxy(550-21-3,35,"Profile");
m=mousein(526,58,570,79);  if(m>=0) { y=8; if(m==1) return -3; }
setcolor(y); outtextxy(550-32-3,60,"Password");
m=mousein(526,83,570,104); if(m>=0) { z=8; if(m==1) return -2; }
setcolor(z); outtextxy(550-21-3,85,"Signout");
m=mousein(526,108,570,129); if(m>=0){ a=8; if(m==1) return -5; }
setcolor(a); outtextxy(550-12-3,110,"Exit");
m=mousein(495,0,610,150);
}
pagedisp(-1);
return 1;
}

