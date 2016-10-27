#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#include<iostream>
using namespace std;

char all[1000][1000][100];
char str[1000][100];
char str1[1000][100];
int table[200][200];
char tablei[100][100];
int ti=0,tj=0;
char wenfa[100][100];
char *wenfafile;
char *tablefile;
int name;
int r=0,c=0;

struct  timeval
{
	long  tv_sec;//秒
	long  tv_usec;//微妙
};

struct  timezone
{
	int tz_minuteswest;/*和greenwich 时间差了多少分钟*/
	int tz_dsttime;/*type of DST correction*/
};

void disData();

typedef struct LinkNode
{
	char name[20];
	char att[100][20];
	int attnum;
	char type[100][20];
	char yuan[100][100][20];
	int yuannum;
	char index[20];
	struct LinkNode *next;
}LinkNode,*LinkList;
LinkList L;


void InitList(LinkList &L)
{
	L=new LinkNode;
	L->next=NULL;
}

typedef struct IndexNode
{
	char name[20];
	char tablename[20];
	char att[20];
	int length;
	char sort[20];// 1 asc , 0 desc
	char context[100][20];
	char index[100][20];
	struct IndexNode *next;
}IndexNode,*IndexList;
IndexList I;


void InitIndexList(IndexList &I)
{
	I=new IndexNode;
	I->next=NULL;
}


typedef struct UserNode
{
	char name[20];
	int ct;
	char create[100][20];
	int cnum;
	char insert[100][20];
	int inum;
	char delet[100][20];
	int dnum;
	char update[100][20];
	int unum;
	char select[100][20];
	int snum;
	char alter[100][20];
	int anum;
	char drop[100][20];
	int drnum;
	struct UserNode *next;
}UserNode,*UserList;
UserList U;


void InitUserList(UserList &U)
{
	U=new UserNode;
	U->ct=0;
	U->cnum=0;
	U->anum=0;
	U->dnum=0;
	U->drnum=0;
	U->inum=0;
	U->snum=0;
	U->unum=0;
	U->next=NULL;
}



//栈模板
typedef struct stacknode
{
	char data[100];
	struct stacknode *next;
}stacknode,*linkstack;

void initstack(linkstack &s)
{
	s=new stacknode();
	s=NULL;
}

void push(linkstack &s,char e[100])
{
	linkstack p=new stacknode;
	strcpy(p->data,e);
	p->next=s;
	s=p;
}

void pop(linkstack &s)
{
	linkstack p;
	p=s;
	s=s->next;
	delete p;
}

int emptystack(linkstack s)
{

    if(s==NULL)
		return 1;
	else
		return 0;
}

char* gettop(linkstack s)
{
	char e[100];
    if(!emptystack(s)) 
		strcpy(e,s->data);
	return e;
}

///////////////////////////////////////////

typedef struct numnode
{
	int data;
	struct numnode *next;
}numnode,*numstack;

void initstackn(numstack &s)
{
	s=new numnode();
	s=NULL;
}

void pushn(numstack &s,int e)
{
	numstack p=new numnode;
	p->data=e;
	p->next=s;
	s=p;
}

void popn(numstack &s)
{
	numstack p;
	p=s;
	s=s->next;
	delete p;
}

linkstack S2;
numstack S1;

///////////////////////////////////////////

char keywords[32][20]={"alter","table","drop","add","char",
"int","varchar","float","index","create",
"on","asc","desc","delete","from",
"where","and","or","drop","view",
"insert","into","values","select","from","update","set","as","grant","revoke","on","to"};

int check()
{
	LinkList p=L->next;
	while(p)
	{
		if(!strcmp(p->name,str1[2]))
		{
			cout<<"Error!"<<endl;
			return 1;
		}
		p=p->next;
	}
	return 0;
}

void turn()
{
	for(int a=0;a<1000;a++)
	{
		strcpy(str[a],"");
		strcpy(str1[a],"");

	}
	int i=0,j=0;
	char ch;
	FILE *fp,*fpw;
	fp=fopen("0.txt","rb");
	fpw=fopen("1.txt","wb");
	ch=fgetc(fp);
	while(ch!=';'&&ch!=-1)
	{
		int tag=0;
		if(ch=='#')
		{
			continue;
		}
		if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='_'))
		{
			char temp1[100]="";
			while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||(ch>='_'))
			{
				if(ch>='A'&&ch<='Z')
					temp1[tag++]=ch+32;
				else
					temp1[tag++]=ch;
				ch=fgetc(fp);
			}
			temp1[tag]='\0';
			int key=0;
			for(int a=0;a<32;a++)
			{
				if(!strcmp(keywords[a],temp1))
					key=1;
			}
			for(int b=0;b<tag;b++)
			{
				if((ch>='A'&&ch<='Z'))
				{
					temp1[b]=temp1[b]+32;
				}
			}
			strcpy(str1[i++],temp1);
			if(key==1)
				fputs(temp1,fpw);
			else
				fputs("id",fpw);
			fputs(" ",fpw);
		}
		if(ch==';')
		{
			break;
		}
		if(ch=='='||ch=='>'||ch=='<'||ch=='!')
		{
			char temp[100]="";
			tag=0;
			while(ch=='='||ch=='>'||ch=='<'||ch=='!')
			{
				temp[tag++]=ch;
				ch=fgetc(fp);
			}
			temp[tag]='\0';
			fputs("r",fpw);
			strcpy(str1[i++],temp);
			fputs(" ",fpw);
		}
		if((ch>='0'&&ch<='9'))
		{
			tag=0;
			char temp3[100]="";
			while((ch>='0'&&ch<='9'))
			{
				temp3[tag++]=ch;
				ch=fgetc(fp);
			}
			fputs("num",fpw);
			strcpy(str1[i++],temp3);
		}
		if(ch==39||ch=='*'||ch==','||ch=='('||ch==')')
		{
			tag=0;
			char temp2[100]="";
			temp2[tag++]=ch;
			temp2[tag]='\0';
			fputs(temp2,fpw);
			strcpy(str1[i++],temp2);
			fputs(" ",fpw);
		}
		else
			if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='_'))
				continue;
		else
		{
			fputs(" ",fpw);
		}
		ch=fgetc(fp);
	}
	strcpy(str[i++],"\0");
	fclose(fp);
	fclose(fpw);
}

void input()
{
	int i=0,j=0;
	char ch;
	FILE *fp;
	fp=fopen("1.txt","rb");
	ch=fgetc(fp);
	int tagg=0;
	while(ch!=-1)
	{
		int tag=0;
		if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch=='_'))
		{
			char temp1[100]="";
			while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
			{
				temp1[tag++]=ch;
				ch=fgetc(fp);
			}
			temp1[tag]='\0';
			strcpy(str[i++],temp1);
			if(tagg==0)
			{
				if(strcmp(temp1,"create")==0)
				{
					name=1;
					wenfafile="create1.txt";
					tablefile="tablecreate1.txt";
				}
				if(strcmp(temp1,"alter")==0)
				{
					name=2;
					wenfafile="alter.txt";
					tablefile="tablealter.txt";
				}
				if(strcmp(temp1,"drop")==0)
				{
					name=3;
					wenfafile="drop.txt";
					tablefile="tabledrop.txt";
				}
				if(strcmp(temp1,"delete")==0)
				{
					name=4;
					wenfafile="delete.txt";
					tablefile="tabledelete.txt";
				}
				if(strcmp(temp1,"insert")==0)
				{
					name=5;
					wenfafile="insert.txt";
					tablefile="tableinsert.txt";
				}
				if(strcmp(temp1,"update")==0)
				{
					name=6;
					wenfafile="update.txt";
					tablefile="tableupdate.txt";
				}
				if(strcmp(temp1,"select")==0)
				{
					name=7;
					wenfafile="select.txt";
					tablefile="tableselect.txt";
				}
				if(strcmp(temp1,"grant")==0)
				{
					name=8;
					wenfafile="gr.txt";
					tablefile="tablegr.txt";
				}
				if(strcmp(temp1,"revoke")==0)
				{
					name=9;
					wenfafile="gr.txt";
					tablefile="tablegr.txt";
				}
				tagg=1;
			}
		}
		if(ch!=' ')
		{
			tag=0;
			char temp2[100]="";
			temp2[tag++]=ch;
			temp2[tag]='\0';
			strcpy(str[i++],temp2);
		}
		ch=fgetc(fp);
	}
	strcpy(str[i++],"#");
	strcpy(str[i++],"\0");
	fclose(fp);
}

void dis()
{
	int i=0;
	while(strcmp(str[i],"\0"))
	{
		cout<<str[i++]<<" ";
	}
}

void readtable()
{
	int i=0;
	char ch;
	FILE *fp;
	fp=fopen(tablefile,"rb");
	ch=fgetc(fp);
	for(int a=0;a<100;a++)
	{
		strcpy(tablei[a],"");
	}
	while(ch!='\n')
	{
		int tag=0;
		while(ch=='|'||ch==' ')
			ch=fgetc(fp);
		if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch=='_'))
		{
			char temp1[100]="";
			while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
			{
				temp1[tag++]=ch;
				ch=fgetc(fp);
			}
			temp1[tag]='\0';
			strcpy(tablei[i++],temp1);
		}
		else
			if((ch>='0'&&ch<='9')||(ch=='-'))
			{
				char temp3[100]="";
				while((ch>='0'&&ch<='9'))
				{
					temp3[tag++]=ch;
					ch=fgetc(fp);
				}
				temp3[tag]='\0';
				strcpy(tablei[i++],temp3);
			}
		else
			if(ch!='|'&&ch!=' ')
			{
				tag=0;
				char temp2[100]="";
				temp2[tag++]=ch;
				temp2[tag]='\0';
				strcpy(tablei[i++],temp2);
			}
		ch=fgetc(fp);
		tj=i-1;
	}
	ch=fgetc(fp);
	for(int ii=0;ii<200;ii++)
		for(int jj=0;jj<200;jj++)
			table[ii][jj]=200;
	/////////////////////////////////////////
	ti=0;
	while(ch!=-1)
	{
		int j=0;
		int flag=0;
		while(ch!='\n')
		{
			int tag=0;
			while(ch!='|')
				ch=fgetc(fp);

			while((ch<'0'||ch>'9')&&(ch!='-'))
			{
				ch=fgetc(fp);
				if(ch=='|')
					j++;
				if(ch=='\n')
				{
					flag=1;
					break;
				}
			}
			if(flag==1)
				break;

			char num[10]="";
			int n=0;
			
			while((ch>='0'&&ch<='9')||(ch=='-'))
			{
				num[n++]=ch;
				ch=fgetc(fp);
			}
			num[n]='\0';
			if(ch=='|')
				j++;
			else
			{
				int temp=strtod(num,NULL);
				table[ti][j++]=temp;
			}

			ch=fgetc(fp);
		}
		ti++;
		ch=fgetc(fp);
	}
	fclose(fp);
}

void distable()
{
	int i,j;
	cout<<"	";
	for(i=0;i<tj;i++)
		cout<<tablei[i]<<"	";
	for(i=0;i<ti;i++)
	{
		cout<<i<<"	";
		for(j=0;j<tj;j++)
		{
			if(table[i][j]==200)
				cout<<"	";
			else
				cout<<table[i][j]<<"	";
		}
	}
}

void readwenfa()
{
	int i=0,j=0;
	char ch;
	FILE *fp;
	fp=fopen(wenfafile,"rb");
	ch=fgetc(fp);
	while(ch!=-1)
	{
		j=0;
		while(ch!='\n'&&ch!=-1)
		{
			wenfa[i][j++]=ch;
			ch=fgetc(fp);
		}
		wenfa[i][j]='\0';
		i++;
		ch=fgetc(fp);
	}
}

int num=1;
void writestage(int t)
{
	cout<<"	"<<num++<<":	";
	numstack p=S1;
	linkstack q=S2;
	while(p!=NULL)
	{
		cout<<p->data<<"	";
		p=p->next;
	}
	cout<<"||	";
	while(q!=NULL)
	{
		cout<<q->data<<"	";
		q=q->next;
	}
	cout<<"||	";
	while(strcmp(str[t],"\0"))
	{
		cout<<str[t++]<<" ";
	}
	cout<<" ||	";
	//system("pause");
}

int intoStack()
{
	initstackn(S1);//状态栈
	initstack(S2);//符号栈
	pushn(S1,0);
	push(S2,"#");

	int i,j,t=0,a;
	int key=0;
	while(1)
	{
		i=S1->data;
		for(a=0;a<tj;a++)
			if(!strcmp(str[t],tablei[a]))
				break;
		if(a==tj)
		{
			cout<<"Error!"<<endl;
			return 0;
		}
		else
		{
			j=a;
			if(table[i][j]==200)
			{
				return 0;
			}
			if(table[i][j]==0)
			{
				cout<<"接受"<<endl;
				return 1;
			}
			if(table[i][j]>0)
			{
				pushn(S1,table[i][j]);
				push(S2,str[t]);
				t++;
			}
			if(table[i][j]<0)
			{
				int temp=(-table[i][j])-1;//文法编号有歧义
				//if(name==6)
				//	temp=temp+1;
				int num=2;
				int id=0;
				char change[100]="";
				while(wenfa[temp][num]!='\0')//根据文法样式不同修改
				{
					//if((wenfa[temp][num]>='a'&&wenfa[temp][num]<='z')||(wenfa[temp][num]>='A'&&wenfa[temp][num]<='Z')||wenfa[temp][num]=='('||wenfa[temp][num]==')')
					if(wenfa[temp][num]!=' '&&wenfa[temp][num]!='\n'&&wenfa[temp][num]!='\r')
						change[id++]=wenfa[temp][num];
					num++;
				}
				change[num-2]='\0';
				num=strlen(change);
				linkstack p;
				int tag=0;
				char yanzheng[100]="";
				p=S2;
				while(p!=NULL&&num!=0)
				{
					num=num-strlen(p->data);
					strcpy(yanzheng,strcat(p->data,yanzheng));
					tag++;
					p=p->next;
				}
				if(strcmp(yanzheng,change))
				{
					return 0;
				}
				else
				{
					int a;
					for(a=0;a<tag;a++)
						pop(S2);
					for(a=0;a<tag;a++)
						popn(S1);
					char s[100]="";
					s[0]=wenfa[temp][0];
					s[1]='\0';
					push(S2,s);
					for(a=0;a<tj;a++)
						if(!strcmp(s,tablei[a]))
							break;
					if(a==tj)
					{
						return 0;
					}
					else
					{
						j=a;
						pushn(S1,table[S1->data][j]);
					}
				}
			}
		}
		//writestage(t);
	}
} 

void create1()
{
	int ss=check();
	if(ss==1)
		return;
	int i=0;
	i=2;
	LinkList q=new LinkNode;
	q->attnum=0;
	q->yuannum=0;
	LinkList p=L;
	strcpy(q->name,str1[i]);
	strcpy(q->index,"0000");
	i=i+2;
	while(strcmp(str1[i],"\0"))
	{
		strcpy(q->att[q->attnum],str1[i++]);
		if(!strcmp(str[i],"char"))//str1->str
		{
			char ch;
			int j=0;
			char temp[20]="char";
			ch=str1[i+2][j++];
			int tag=4;
			if(ch>='0'&&ch<='9')
			{
				while(ch>='0'&&ch<='9')
				{
					temp[tag++]=ch;
					ch=str1[i+2][j++];
				}
				temp[tag]='\0';
				strcpy(q->type[q->attnum],temp);
				i=i+5;
			}
			else
			{
				strcpy(q->type[q->attnum],str1[i]);
				i=i+2;
			}
		}
		else
			if(!strcmp(str1[i],"int"))
			{
				strcpy(q->type[q->attnum],str1[i]);
				i=i+2;
			}
		else
		{
			i=i+2;
		}
		q->attnum++;
	}
	//////////////////////////////可存入属性及元组个数
	while(p->next)
	{
		p=p->next;
	}
	q->next=NULL;
	p->next=q;
	//cout<<endl;
}

void bubbleSort(char pnData[100][20], int nLen,char key[20])
{
	bool isOk=false; 
	for (int i=0;i<nLen-1&&!isOk;++i)
	{
		isOk=true;
		for(int j=nLen-1;j>i;--j)
		{
			if(!strcmp(key,"asc"))
			{
				if(strcmp(pnData[j],pnData[j-1])>0)
				{
					char nTemp[20];
					strcpy(nTemp,pnData[j]);
					strcpy(pnData[j],pnData[j-1]);
					strcpy(pnData[j-1],nTemp);
					isOk=false;
				}
			}
			if(!strcmp(key,"desc"))
			{
				if(strcmp(pnData[j],pnData[j-1])<0)
				{
					char nTemp[20];
					strcpy(nTemp,pnData[j]);
					strcpy(pnData[j],pnData[j-1]);
					strcpy(pnData[j-1],nTemp);
					isOk=false;
				}
			}
		}
	}
}

void index(IndexList &q,int i,LinkList p)
{
	for(int j=0;j<q->length;j++)
	{
		for(int a=0;a<q->length;a++)
		{
			if(!strcmp(q->context[j],p->yuan[a][i]))
			{
				int tag=(a*p->attnum+i)*20;
				itoa(tag,q->index[j],10);
				break;
			}
		}
	}
}

void indexcon()
{
	LinkList p=L->next;
	IndexList q;
	int i,j;
	while(p)
	{
		if(strcmp(p->index,"0000"))
		{
			q=I->next;
			while(q)
			{
				if(!strcmp(p->index,q->name))
				{
					q->length=p->yuannum;
					for(i=0;i<p->attnum;i++)
					{
						if(!strcmp(q->att,p->att[i]))
						{
							for(j=0;j<q->length;j++)
							{
								strcpy(q->context[j],p->yuan[j][i]);
							}
							bubbleSort(q->context,q->length,q->sort);
							index(q,i,p);
							//return;
						}
					}
				}
				q=q->next;
			}
		}
		p=p->next;
	}
	
}

void create2()
{
	cout<<"index!"<<endl;
	int i=0,j=0;
	LinkList p=L->next;
	IndexList s=I->next;
	IndexList q;
	while(s)
	{
		if(!strcmp(s->name,str1[2]))
		{
			cout<<"Error!"<<endl;
			return;
		}
		s=s->next;
	}
	while(p)
	{
		if(!strcmp(p->name,str1[2]))
		{
			cout<<"Error!"<<endl;
			return;
		}
		p=p->next;
	}
	p=L->next;
	while(p)
	{
		if(!strcmp(p->name,str1[4]))
		{
			strcpy(p->index,str1[2]);
			q=new IndexNode;
			s=I;
			strcpy(q->name,str1[2]);
			strcpy(q->tablename,str1[4]);
			strcpy(q->att,str1[6]);
			q->length=p->yuannum;
			strcpy(q->sort,str1[7]);
			while(s->next)
			{
				s=s->next;
			}
			q->next=NULL;
			s->next=q;
			return;
		}
		p=p->next;
	}
	if(p==NULL)
		cout<<"Error!"<<endl;
}

void create3()
{
	cout<<"	创建视图"<<endl;
}

void create()
{
	if(!strcmp(str[1],"table"))
		create1();
	if(!strcmp(str[1],"index"))
		create2();
	if(!strcmp(str[1],"view"))
		create3();
}

void addItem1()
{
	int i=0;
	i=2;
	LinkList p=L->next;
	IndexList q=I->next;
	r=0;
	int key=0;
	while(p)
	{
		if(!strcmp(p->name,str1[i]))
		{
			i=i+4;
			while(strcmp(str1[i],"\0"))
			{
				strcpy(p->yuan[p->yuannum][r],str1[i]);
				i=i+4;
				if(!strcmp(str1[i],"\0")&&r<p->attnum-1)
				{
					cout<<"Error!"<<endl;
					strcpy(p->yuan[p->yuannum][r],"");
					return;
				}		
				else	
					r++;
			}
			p->yuannum++;
			return;//break;
		}
		p=p->next;
	}
	if(p==NULL)
		cout<<"Error!"<<endl;	
}

void addItem2()
{
	int i=0;
	i=2;
	LinkList p=L;
	IndexList q=I->next;
	r=0;
	char temp[100][100],tempy[100][100];
	int t=0,ty=0;
	int key=0;
	while(p)
	{
		if(!strcmp(p->name,str1[i]))
		{
			i=i+2;
			while(strcmp(str1[i],"values"))
			{
				strcpy(temp[t++],str1[i]);
				i=i+2;
			}
			i=i+3;

			while(strcmp(str1[i],"\0"))
			{
				strcpy(tempy[ty++],str1[i]);
				i=i+4;
			}
			if(t>p->attnum)
			{
				cout<<"Error!"<<endl;
				return;
			}
			else
				if(t!=ty)
				{
					cout<<"Error!"<<endl;
					return;
				}
			else
			{
				for(int b=0;b<p->attnum;b++)
				{
						strcpy(p->yuan[p->yuannum][b],"");
				}
				for(int a=0;a<t;a++)
				{
					for(int b=0;b<p->attnum;b++)
					{
						if(!strcmp(temp[a],p->att[b]))
							strcpy(p->yuan[p->yuannum][b],tempy[a]);
					}
				}
				p->yuannum++;
				return;//break
			}
		}
		p=p->next;
	}
	if(p==NULL)
		cout<<"Error!"<<endl;	
}

void addItem()
{
	if(!strcmp(str[3],"values"))
		addItem1();
	if(!strcmp(str[3],"("))
		addItem2();
}

void delItem()//or的位置问题
{
	int key=0;
	int i=0;
	int t=0;
	i=2;
	LinkList p=L;
	int mark[20];
	int arnum=0;
	char markcon[20][20];
	int tag=0;
	while(strcmp(str[t],"\0"))
	{
		if(!strcmp(str[t++],"where"))
		{
			tag=1;
			break;
		}
	}
	if(tag==0)
	{
		while(p)
		{
			if(!strcmp(p->name,str1[i]))
			{
				for(int s=0;s<p->yuannum;s++)
					for(int u=0;u<p->attnum;u++)
						strcpy(p->yuan[s][u],"");
				p->yuannum=0;
				break;
			}
			p=p->next;
		}
	}
	else
	{
		i=0;
		p=L;
		t=0;
		while(strcmp(str[i],"\0"))
		{
			if(!strcmp(str[i++],"or"))
			{
				key=1;
			}
		}
		for(int a=0;a<20;a++)
		{
			strcpy(markcon[a],"");
		}
		i=2;
		while(p)
		{
			if(!strcmp(p->name,str1[i]))
			{
				while(strcmp(str1[i],"\0"))
				{
					i=i+3;
					for(int j=0;j<p->attnum;j++)
					{
						if(!strcmp(p->att[j],str1[i]))
						{
							mark[t]=j;
							char temp[10]="";
							if(!strcmp(p->type[j],"int"))
							{
								i=i+2;
							}
							else
								i=i+3;
							strcpy(markcon[t++],str1[i]);
							break;
						}
					}
				}
				if(!strcmp(markcon[0],""))
				{
					cout<<"Error!"<<endl;
					return;
				}
				if(t>p->attnum)
				{
					cout<<"Error!"<<endl;
					return;
				}
				int temp[100];
				int s=0,w=0;
				if(key==0)
				{
					int a=0;
					int b=0;
					for(b=0;b<p->yuannum;b++)
					{
						w=0;
						for(a=0;a<t;a++)
						{
							if(!strcmp(p->yuan[b][mark[a]],markcon[a]))
							{
								w++;
							}
						}
						if(w==t)
						{
							temp[s++]=b;
						}
					}
					for(int e=0;e<s;e++)
					{
							for(int d=0;d<p->attnum;d++)
							{
								strcpy(p->yuan[temp[e]][d],p->yuan[p->yuannum-1][d]);
							}
						for(int f=0;f<p->attnum;f++)
						{
							strcpy(p->yuan[p->yuannum-1][d],"");
						}
						p->yuannum--;
					}
				}
				else
				{
					int a=0;
					int b=0;
					for(b=0;b<p->yuannum;b++)
					{
						for(a=0;a<t;a++)
						{
							for(int g=0;g<p->yuannum;g++)
							{
								if(!strcmp(p->yuan[b][mark[a]],markcon[a]))
								{
									for(int e=b;e<p->yuannum;e++)
									{
										for(int d=0;d<p->attnum;d++)
										{
											strcpy(p->yuan[e][d],p->yuan[e+1][d]);
										}
									}
									for(int f=0;f<p->attnum;f++)
									{
										strcpy(p->yuan[p->yuannum-1][f],"");
									}
									p->yuannum--;
									g--;
								}
							}
						}						
					}
				}
				return;
			}
			p=p->next;
		}
	}
	if(p==NULL)
		cout<<"Error!"<<endl;
}

void chItem()
{
	int key=0;
	int i=0;
	while(strcmp(str[i],"\0"))
	{
		if(!strcmp(str[i++],"or"))
			key=1;
	}
	i=1;
	LinkList p=L;
	int mark[20];
	int arnum=0;
	char markcon[20][20];
	int t=0;
	int tag=0;
	int k=0;
	for(int a=0;a<20;a++)
	{
		strcpy(markcon[a],"");
	}
	while(p)
	{
		if(!strcmp(p->name,str1[i]))
		{
			for(int u=0;u<p->attnum;u++)
			{
				if(!strcmp(p->att[u],str1[3]))
				{
					tag=u;
				}
			}
			if(!strcmp(p->att[tag],"int"))
			{
				i=i+7;
				k=1;
			}
			else
				i=i+9;
			while(strcmp(str[i],"\0"))
			{
				for(int j=0;j<p->attnum;j++)
				{
					if(!strcmp(p->att[j],str1[i]))
					{
						mark[t]=j;
						char temp[10]="";
						if(!strcmp(p->type[j],"int"))
						{
							i=i+2;
						}
						else
							i=i+3;
						strcpy(markcon[t++],str1[i]);
						break;
					}
				}
				i=i+5;
			}
			if(!strcmp(markcon[0],""))
			{
				cout<<"Error!"<<endl;
				return;
			}
			if(t>p->attnum)
			{
				cout<<"Error!"<<endl;
				return;
			}
			int temp[100];
			int s=0,w=0;
			if(key==0)
			{
					int a=0;
					int b=0;
					for(b=0;b<p->yuannum;b++)
					{
						w=0;
						for(a=0;a<t;a++)
						{
							if(!strcmp(p->yuan[b][mark[a]],markcon[a]))
							{
								w++;
							}
						}
						if(w==t)
						{
							temp[s++]=b;
						}
					}
					for(int e=0;e<s;e++)
					{
						if(k==1)
							strcpy(p->yuan[temp[e]][tag],str1[5]);
						else
							strcpy(p->yuan[temp[e]][tag],str1[6]);
					}
			}
			else
			{
					int a=0;
					int b=0;
					for(b=0;b<p->yuannum;b++)
					{
						for(a=0;a<t;a++)
						{
							for(int g=0;g<p->yuannum;g++)
							{
								if(!strcmp(p->yuan[b][mark[a]],markcon[a]))
								{
									if(k==1)
										strcpy(p->yuan[b][tag],str1[5]);
									else
										strcpy(p->yuan[b][tag],str1[6]);
								}
							}
						}						
					}
			}
			break;
		}
		p=p->next;
	}
	if(p==NULL)
		cout<<"Error!"<<endl;
}

void addAttribute()
{
	int i=2;
	LinkList p=L;
	r=0;
	while(p)
	{
		if(!strcmp(p->name,str1[i]))
		{
			i=i+3;
			while(strcmp(str1[i],"\0"))
			{
				strcpy(p->att[p->attnum],str1[i++]);
				if(!strcmp(str[i],"char"))//str1->str
				{
					char ch;
					int j=0;
					char temp[20]="char";
					ch=str1[i+2][j++];
					int tag=4;
					if(ch>='0'&&ch<='9')
					{
						while(ch>='0'&&ch<='9')
						{
							temp[tag++]=ch;
							ch=str1[i+2][j++];
						}
						temp[tag]='\0';
						strcpy(p->type[p->attnum],temp);
						i=i+5;
					}
					else
					{
						strcpy(p->type[p->attnum],str1[i]);
						i=i+2;
					}
				}
				else
					if(!strcmp(str[i],"int"))
					{
						strcpy(p->type[p->attnum],str1[i]);
						i=i+2;
					}
				else
				{
					i=i+2;
				}
				for(int s=0;s<p->yuannum;s++)
					strcpy(p->yuan[s][p->attnum],"");
				p->attnum++;
			}
			break;
		}
		p=p->next;
	}
	if(p==NULL)
		cout<<"Error!"<<endl;
}

void delAttribute()
{
	int i=2;
	LinkList p=L;
	while(p)
	{
		if(!strcmp(p->name,str1[i]))
		{
			i=i+3;
			for(int a=0;a<p->attnum;a++)
			{
				if(!strcmp(p->att[a],str1[i]))
				{
					for(int b=a;b<p->attnum;b++)
					{
						strcpy(p->att[b],p->att[b+1]);
						for(int c=0;c<p->yuannum;c++)
						{
							strcpy(p->yuan[c][b],p->yuan[c][b+1]);
						}
					}
					strcpy(p->att[p->attnum-1],"");
					for(int c=0;c<p->yuannum;c++)
					{
						strcpy(p->yuan[c][p->attnum-1],"");
					}
					p->attnum--;
					
				}
			}
			break;
		}
		p=p->next;
	}
	if(p==NULL)
		cout<<"Error!"<<endl;
}

void delTable()
{
	int i=2;
	LinkList p=L;
	while(p->next)
	{
		if(!strcmp(p->next->name,str1[i]))
		{
			p->next=p->next->next;
			return;
		}
		p=p->next;
	}
	if(p==NULL)
		cout<<"Error!"<<endl;
}

void delIndex()
{
	cout<<"delIndex!"<<endl;
	int i=2;
	IndexList p=I;
	LinkList q=L->next;
	while(p->next)
	{
		if(!strcmp(p->next->name,str1[i]))
		{
			while(q)
			{
				if(!strcmp(p->next->tablename,q->name))
				{
					strcpy(q->index,"0000");
					break;
				}
				q=q->next;
			}
			p->next=p->next->next;
			return;
		}
		p=p->next;
	}
	if(p==NULL)
		cout<<"Error!"<<endl;
}

///////////////////////////////////////////////////
/////单关系/////////////////////////////////////////
///////////////////////////////////////////////////

void selectResult1()//*索引
{
	clock_t start=clock();

	cout<<"	索引!"<<endl;
	LinkList p=L->next;
	IndexList q;
	int i,j;
	while(p)
	{
		if(!strcmp(p->name,str1[3]))
		{
			if(strcmp(p->index,"0000"))
			{
				cout<<"		"<<p->name<<endl;
				for(i=0;i<p->attnum;i++)
				{
					cout<<"	"<<p->att[i]<<"	";
				}
				cout<<endl<<endl;
				q=I->next;
				while(q)
				{
					if(!strcmp(p->index,q->name))
					{
						for(i=0;i<q->length;i++)
						{
							FILE *fp;
							fp=fopen(p->name,"r");
							int temp=0;
							temp=atoi(q->index[i])/(20*p->attnum);
							temp=temp*20*p->attnum;
							char ch;
							for(j=0;j<temp;j++)
								ch=fgetc(fp);
							for(j=0;j<20*p->attnum;j++)
							{
								ch=fgetc(fp);
								cout<<ch;
							}
							cout<<endl;
							fclose(fp);
						}
					}
					q=q->next;
				}
			}
		}
		p=p->next;
	}
	cout<<endl<<endl;
	
	clock_t end=clock(); 
	unsigned long dis_time=end-start;
	cout<<"	"<<dis_time<<"毫秒!"<<endl<<endl;
}

void selectResult2()//*
{
	clock_t start=clock();

	LinkList p=L->next;
	while(p)
	{
		if(!strcmp(p->name,str1[3]))
		{
			cout<<"		"<<p->name<<endl;
			for(int i=0;i<p->attnum;i++)
			{
				cout<<"	"<<p->att[i]<<"	";
			}
			cout<<endl<<endl;
			for(int a=0;a<p->yuannum;a++)
			{
				for(int b=0;b<p->attnum;b++)
				{
					cout<<"	"<<p->yuan[a][b]<<"	";
				}
				cout<<endl;
			}
		}
		p=p->next;
	}
	cout<<endl<<endl;
	
	clock_t end=clock(); 
	unsigned long dis_time=end-start;
	cout<<"	"<<dis_time<<"毫秒!"<<endl<<endl;
}

void selectResult3()//nowhere
{
	clock_t start=clock();

	int i,j,w,t=0,k=1;
	LinkList p=L->next;
	char touying[100][20];
	while(strcmp(str1[k],"from"))
	{
		if(strcmp(str1[k],","))
		{
			strcpy(touying[t],str1[k]);
			cout<<"	"<<touying[t++];
		}
		k++;
	}
	k=k+1;
	cout<<endl<<endl;
	while(p)
	{
		if(!strcmp(str1[k],p->name))
		{
			for(j=0;j<p->yuannum;j++)
			{
				for(w=0;w<t;w++)
				{
					for(i=0;i<p->attnum;i++)
					{
						if(!strcmp(touying[w],p->att[i]))
						{
							cout<<"	"<<p->yuan[j][i];
						}
					}
				}
				cout<<endl;
			}
		}
		p=p->next;
	}
	cout<<endl;

	clock_t end=clock(); 
	unsigned long dis_time=end-start;
	cout<<"	"<<dis_time<<"毫秒!"<<endl<<endl;
}

void selectResult4()//nowhere索引
{
	clock_t start=clock(); 

	cout<<"	索引!"<<endl;
	int i,j,w,t=0,k=1;
	LinkList p=L->next;
	IndexList q;
	char touying[100][20];
	while(strcmp(str1[k],"from"))
	{
		if(strcmp(str1[k],","))
		{
			strcpy(touying[t],str1[k]);
			cout<<"	"<<touying[t++];
		}
		k++;
	}
	k=k+1;
	cout<<endl<<endl;
	while(p)
	{
		if(!strcmp(p->name,str1[k]))
		{
			if(strcmp(p->index,"0000"))
			{
				q=I->next;
				while(q)
				{
					if(!strcmp(p->index,q->name))
					{
						int a=0,b=0,c=0,tt=0;
						char yuan[100][100][20];
						for(i=0;i<q->length;i++)
						{
							FILE *fp;
							fp=fopen(p->name,"r");
							int temp=0;
							temp=atoi(q->index[i])/(20*p->attnum);
							temp=temp*20*p->attnum;
							char ch;
							char tyuan[20];
							for(j=0;j<temp;j++)
								ch=fgetc(fp);
							b=0;
							for(j=0;j<p->attnum;j++)
							{
								tt=0;
								ch=fgetc(fp);
								if(ch==' ')
								{
									while(ch==' ')
										ch=fgetc(fp);
								}
								while(ch!=' ')
								{
									tyuan[tt++]=ch;
									ch=fgetc(fp);
								}
								tyuan[tt]='\0';
								strcpy(yuan[a][b++],tyuan);

							}
							c=b;
							a++;
							fclose(fp);
						}
						for(j=0;j<p->yuannum;j++)
						{
							for(w=0;w<t;w++)
							{
								for(i=0;i<p->attnum;i++)
								{
									if(!strcmp(touying[w],p->att[i]))
									{
										cout<<"	"<<yuan[j][w];
									}
								}
							}
							cout<<endl;
						}
					}
					q=q->next;
				}
			}
		}
		p=p->next;
	}
	cout<<endl;
	
	clock_t end=clock(); 
	unsigned long dis_time=end-start;
	cout<<"	"<<dis_time<<"毫秒!"<<endl<<endl;
}

void selectResult5(int tag)//where
{
	clock_t start=clock(); 

	int i=1,j=0,t=0;
	LinkList p=L->next;
	char touying[100][20];
	char tatt[100][20],tyuan[100][20],tfuhao[100][20];
	char temp[100][100][20];
	while(strcmp(str1[i],"from"))
	{
		if(strcmp(str1[i],",")&&tag==0)
			strcpy(touying[t++],str1[i]);
		i++;
	}
	i=i+1;
	IndexList q;
	while(p)
	{
		if(!strcmp(str1[i],p->name))
		{
			if(tag==1)
			{
				for(int k=0;k<p->attnum;k++)
					strcpy(touying[t++],p->att[k]);
			}
			while(strcmp(str1[i],"\0"))
			{
				while(strcmp(str1[i+1],"")&&strcmp(str1[i+1],"=")&&strcmp(str1[i+1],">")&&strcmp(str1[i+1],"<")&&strcmp(str1[i+1],">=")&&strcmp(str1[i+1],"<=")&&strcmp(str1[i+1],"!="))
				{
					i++;
				}
				if(!strcmp(str1[i+1],""))
					break;
				strcpy(tatt[j],str1[i++]);
				strcpy(tfuhao[j],str1[i++]);				
				if(!strcmp(str1[i],"'"))
					i++;
				strcpy(tyuan[j++],str1[i]);
			}
			int a,b,c,d,e;
			if(strcmp(p->index,"0000"))
			{
				cout<<"	索引!"<<endl;
				q=I->next;
				while(q)
				{
					if(!strcmp(p->index,q->name))
					{
						a=0;
						b=0;
						c=0;
						int tt=0;
						for(i=0;i<q->length;i++)
						{
							FILE *fp;
							fp=fopen(p->name,"r");
							int temp1=0;
							temp1=atoi(q->index[i])/(20*p->attnum);
							temp1=temp1*20*p->attnum;
							char ch;
							char ttyuan[20];
							for(e=0;e<temp1;e++)
								ch=fgetc(fp);
							b=0;
							for(e=0;e<p->attnum;e++)
							{
								tt=0;
								ch=fgetc(fp);
								if(ch==' ')
								{
									while(ch==' ')
										ch=fgetc(fp);
								}
								while(ch!=' ')
								{
									ttyuan[tt++]=ch;
									ch=fgetc(fp);
								}
								ttyuan[tt]='\0';
								strcpy(temp[a][b++],ttyuan);
							}
							c=b;
							a++;
							fclose(fp);
						}
					}
					q=q->next;
				}
			}
			else
			{
				for(a=0;a<p->yuannum;a++)
				{
					for(b=0;b<p->attnum;b++)
					{
						strcpy(temp[a][b],p->yuan[a][b]);
					}
				}
			}
			int key;
			for(a=0;a<j;a++)
			{
				key=0;
				for(b=0;b<p->attnum;b++)
				{
					if(!strcmp(p->att[b],tatt[a]))
					{
						key=1;
					}
				}
				if(key==0)
				{
					cout<<"Error!"<<endl;
					return;
				}
			}
			for(a=0;a<j;a++)
			{
				for(c=0;c<p->attnum;c++)
				{
					if(!strcmp(p->att[c],tatt[a]))
					{
						for(b=0;b<p->yuannum;b++)
						{
							if(!strcmp(tfuhao[a],"="))
							{
								if(strcmp(temp[b][c],tyuan[a]))
								{
									for(d=0;d<p->attnum;d++)
										strcpy(temp[b][d],"");
								}
							}
							if(!strcmp(tfuhao[a],">"))
							{
								if(strcmp(temp[b][c],tyuan[a])>0)
								{
									for(d=0;d<p->attnum;d++)
										strcpy(temp[b][d],"");
								}
							}
							if(!strcmp(tfuhao[a],"<"))
							{
								if(strcmp(temp[b][c],tyuan[a])<0)
								{
									for(d=0;d<p->attnum;d++)
										strcpy(temp[b][d],"");
								}
							}
							if(!strcmp(tfuhao[a],">="))
							{
								if(strcmp(temp[b][c],tyuan[a])>0||!strcmp(temp[b][c],tyuan[a]))
								{
									for(d=0;d<p->attnum;d++)
										strcpy(temp[b][d],"");
								}
							}
							if(!strcmp(tfuhao[a],"<="))
							{
								if(strcmp(temp[b][c],tyuan[a])<0||!strcmp(temp[b][c],tyuan[a]))
								{
									for(d=0;d<p->attnum;d++)
										strcpy(temp[b][d],"");
								}
							}
							if(!strcmp(tfuhao[a],"!="))
							{
								if(!strcmp(temp[b][c],tyuan[a]))
								{
									for(d=0;d<p->attnum;d++)
										strcpy(temp[b][d],"");
								}
							}
						}
					}
				}
			}

			for(a=0;a<t;a++)
			{
				cout<<"	"<<touying[a];
			}
			cout<<endl<<endl;;
			int tkey=0;
			for(a=0;a<p->yuannum;a++)
			{
				tkey=0;
				for(b=0;b<t;b++)
				{
					for(c=0;c<p->attnum;c++)
					{
						if(!strcmp(p->att[c],touying[b]))
						{
							if(strcmp(temp[a][b],""))
							{
								cout<<"	"<<temp[a][b];
								tkey=1;
							}
						}
					}
				}
				if(tkey==1)
					cout<<endl;
			}
		}
		p=p->next;
	}
	cout<<endl;

	clock_t end=clock(); 
	unsigned long dis_time=end-start;
	cout<<"	"<<dis_time<<"毫秒!"<<endl<<endl;
}

///////////////////////////////////////////////////
/////多关系/////////////////////////////////////////
///////////////////////////////////////////////////

LinkList T;

void selectResult8(int tag)//多关系连接
{
	clock_t start=clock();

	cout<<"		多关系连接"<<endl;
	int i=1,j=0,t=0,k=0,l=0;
	LinkList p=L->next;
	char touying[100][20];
	char tbiao[100][20],tatt[100][20],tyuan[100][20],tfuhao[100][20];
	if(tag==0)
	{
		while(strcmp(str1[i],"from"))
		{
			if(strcmp(str1[i],","))
				strcpy(touying[t++],str1[i]);
			i++;
		}
		i++;
	}
	else
	{
		while(strcmp(str1[i],"from"))
		{
			i++;
		}
		i++;
	}
	while(strcmp(str1[i],"where")&&strcmp(str1[i],"\0"))
	{
		if(strcmp(str1[i],","))
			strcpy(tbiao[k++],str1[i]);
		i++;
	}
	InitList(T);
	LinkList s,q=T;
	int a,b,c,d,e,f;
	int key;
	for(l=0;l<k;l++)
	{
		p=L->next;
		while(p)
		{
			if(!strcmp(tbiao[l],p->name))
			{
				s=new LinkNode;
				strcpy(s->name,p->name);
				s->attnum=p->attnum;
				s->yuannum=p->yuannum;
				strcpy(s->index,p->index);
				for(a=0;a<p->attnum;a++)
				{
					strcpy(s->att[a],p->att[a]);
					strcpy(s->type[a],p->type[a]);
				}
				for(a=0;a<p->yuannum;a++)
				{
					for(b=0;b<p->attnum;b++)
					{
						strcpy(s->yuan[a][b],p->yuan[a][b]);
					}
				}
				s->next=NULL;
				q->next=s;
				q=s;
			}
			p=p->next;
		}
	}
	p=T->next;
	if(tag==1)
	{
		while(p)
		{
			for(a=0;a<p->attnum;a++)
				strcpy(touying[t++],p->att[a]);
			p=p->next;
		}
	}
	p=T->next;
	if(tag==2)
	{
		if(!strcmp(str[1],"*"))
		{
			while(p)
			{
				for(a=0;a<p->attnum;a++)
				{
					strcpy(touying[t],p->att[a]);
					cout<<"	"<<touying[t++];
				}
				p=p->next;
			}
			cout<<endl<<endl;
			char shuchu[100][100][20];
			p=T->next;
			c=0;
			d=0;
			int dd=0;
			while(p)
			{
				for(a=0;a<p->yuannum;a++)
				{
					d=0;
					for(b=0;b<p->attnum;b++)
					{
						strcpy(shuchu[c][d++],p->yuan[a][b]);
					}
					dd=d;
					c++;
				}
				p=p->next;
			}
			for(a=0;a<c;a++)
			{
				for(b=0;b<dd;b++)
				{
					cout<<"	"<<shuchu[a][b];
				}
				cout<<endl;
			}
		}
		return;
	}
	i=0;
	while(strcmp(str1[i],"\0"))
	{
		while(strcmp(str1[i],"")&&strcmp(str1[i],"=")&&strcmp(str1[i],">")&&strcmp(str1[i],"<")&&strcmp(str1[i],">=")&&strcmp(str1[i],"<=")&&strcmp(str1[i],"!="))
		{
			i++;
		}
		if(!strcmp(str1[i],""))
			break;
		if(!strcmp(str1[i+1],"'")||(str1[i+1][0]>'0'&&str1[i+1][0]<'9'))
		{
			strcpy(tfuhao[j],str1[i]);
			strcpy(tatt[j],str1[i-1]);				
			if(!strcmp(str1[i+1],"'"))
			{
				i++;
			}
			strcpy(tyuan[j++],str1[i+1]);
		}
		i++;
	}
	for(a=0;a<j;a++)
	{
		key=0;
		q=T->next;
		while(q)
		{			
			for(b=0;b<q->attnum;b++)
			{
				if(!strcmp(q->att[b],tatt[a]))
				{
					key=1;
				}
			}
			q=q->next;
		}
		if(key==0)
		{
			cout<<"Error!"<<endl;
			return;
		}
	}
	i=0;
	char condition[100][2][20];
	int connum=0;
	while(strcmp(str1[i],"\0"))
	{
		if(!strcmp(str1[i],"=")||!strcmp(str1[i],">")||!strcmp(str1[i],"<")||!strcmp(str1[i],">=")||!strcmp(str1[i],"<=")||!strcmp(str1[i],"!="))
		{
			char te[20];
			strcpy(te,str1[i+1]);
			if(strcmp("'",te)&&(te[0]<'0'||te[0]>'9'))
			{
				strcpy(condition[connum][0],str1[i-1]);
				strcpy(condition[connum++][1],str1[i+1]);
			}
		}
		i++;
	}

	char temp[100][100][20],alltemp[100][100][20];
	int ll=0,r1=0,rr=0,r2=0;
	for(a=0;a<100;a++)
	{
		for(b=0;b<100;b++)
		{
			strcpy(temp[a][b],"");
		}
	}

	p=T->next;
	IndexList qq;
	if(strcmp(p->index,"0000"))//
	{
		cout<<"	索引1!"<<endl;
		qq=I->next;
		while(qq)
		{
			if(!strcmp(p->index,qq->name))
			{
				a=0;
				b=0;
				c=0;
				int tt=0;
				for(i=0;i<qq->length;i++)
				{
					FILE *fp;
					fp=fopen(p->name,"r");
					int temp1=0;
					temp1=atoi(qq->index[i])/(20*p->attnum);
					temp1=temp1*20*p->attnum;
					char ch;
					char ttyuan[20];
					for(e=0;e<temp1;e++)
						ch=fgetc(fp);
					b=0;
					for(e=0;e<p->attnum;e++)
					{
						tt=0;
						ch=fgetc(fp);
						if(ch==' ')
						{
							while(ch==' ')
								ch=fgetc(fp);
						}
						while(ch!=' ')
						{
							ttyuan[tt++]=ch;
							ch=fgetc(fp);
						}
						ttyuan[tt]='\0';
						strcpy(temp[a][b++],ttyuan);
					}
					c=b;
					a++;
					fclose(fp);
				}
			}
			qq=qq->next;
		}
	}
	else
	{
		for(a=0;a<p->yuannum;a++)
		{
			for(b=0;b<p->attnum;b++)
			{
				strcpy(temp[a][b],p->yuan[a][b]);
			}
		}
	}//

	int yn=p->yuannum,an=p->attnum;
	char yuan[100][100][20];
	p=T->next;
	int synum=2;
	while(p)
	{
		if(p->next!=NULL)
		{
			ll=0;
			for(a=0;a<yn;a++)
			{
				for(b=0;b<p->next->yuannum;b++)
				{
					rr=0;
					for(c=0;c<an;c++)
					{
						strcpy(alltemp[ll][rr++],temp[a][c]);
					}
					r1=rr;
					ll++;
				}
			}
			
			if(strcmp(p->next->index,"0000"))//
			{
				cout<<"	索引"<<synum++<<"!"<<endl;
				qq=I->next;
				while(qq)
				{
					if(!strcmp(p->next->index,qq->name))
					{
						a=0;
						b=0;
						c=0;
						int tt=0;
						for(i=0;i<qq->length;i++)
						{
							FILE *fp;
							fp=fopen(p->next->name,"r");
							int temp1=0;
							temp1=atoi(qq->index[i])/(20*p->next->attnum);
							temp1=temp1*20*p->next->attnum;
							char ch;
							char ttyuan[20];
							for(e=0;e<temp1;e++)
								ch=fgetc(fp);
							b=0;
							for(e=0;e<p->next->attnum;e++)
							{
								tt=0;
								ch=fgetc(fp);
								if(ch==' ')
								{
									while(ch==' ')
										ch=fgetc(fp);
								}
								while(ch!=' ')
								{
									ttyuan[tt++]=ch;
									ch=fgetc(fp);
								}
								ttyuan[tt]='\0';
								strcpy(yuan[a][b++],ttyuan);
							}
							c=b;
							a++;
							fclose(fp);
						}
					}
					qq=qq->next;
				}
			}
			else
			{
				for(a=0;a<p->next->yuannum;a++)
				{
					for(b=0;b<p->next->attnum;b++)
					{
						strcpy(yuan[a][b],p->next->yuan[a][b]);
					}
				}
			}

			ll=0;
			for(a=0;a<yn;a++)
			{
				for(b=0;b<p->next->yuannum;b++)
				{
					rr=r1;
					for(c=0;c<p->next->attnum;c++)
					{
						strcpy(alltemp[ll][rr++],yuan[b][c]);
					}
					r2=rr;
					ll++;
				}
			}

			yn=yn*p->next->yuannum;
			an=an*p->next->attnum;
			for(a=0;a<yn;a++)
			{
				for(b=0;b<an;b++)
				{
					strcpy(temp[a][b],alltemp[a][b]);
				}
			}
		}
		p=p->next;
	}

	char atttemp[100][20];
	int atnum=0;
	p=T->next;
	while(p)
	{
		for(a=0;a<p->attnum;a++)
		{
			strcpy(atttemp[atnum++],p->att[a]);
		}
		p=p->next;
	}
	for(d=0;d<connum;d++)
	{
		for(c=0;c<atnum;c++)
		{
			if(!strcmp(atttemp[c],condition[d][0]))
				r1=c;
			if(!strcmp(atttemp[c],condition[d][1]))
				r2=c;
		}
		for(a=0;a<ll;a++)
		{
			if(strcmp(temp[a][r1],temp[a][r2]))
			{
				for(b=0;b<rr;b++)
					strcpy(temp[a][b],"");
			}
		}
	}
	//////////////////////////////////////////
	for(a=0;a<j;a++)
	{
		for(c=0;c<rr;c++)
		{
			if(!strcmp(atttemp[c],tatt[a]))
			{
				for(b=0;b<ll;b++)
				{
					if(!strcmp(tfuhao[a],"="))
					{
						if(strcmp(temp[b][c],tyuan[a]))
						{
							for(d=0;d<rr;d++)
								strcpy(temp[b][d],"");
						}
					}
					if(!strcmp(tfuhao[a],">"))
					{
						if(strcmp(temp[b][c],tyuan[a])>0)
						{
							for(d=0;d<rr;d++)
								strcpy(temp[b][d],"");
						}
					}
					if(!strcmp(tfuhao[a],"<"))
					{
						if(strcmp(temp[b][c],tyuan[a])<0)
						{
							for(d=0;d<rr;d++)
								strcpy(temp[b][d],"");
						}
					}
					if(!strcmp(tfuhao[a],">="))
					{
						if(strcmp(temp[b][c],tyuan[a])>0||!strcmp(temp[b][c],tyuan[a]))
						{
							for(d=0;d<rr;d++)
								strcpy(temp[b][d],"");
						}
					}
					if(!strcmp(tfuhao[a],"<="))
					{
						if(strcmp(temp[b][c],tyuan[a])<0||!strcmp(temp[b][c],tyuan[a]))
						{
							for(d=0;d<rr;d++)
								strcpy(temp[b][d],"");
						}
					}
					if(!strcmp(tfuhao[a],"!="))
					{
						if(!strcmp(temp[b][c],tyuan[a]))
						{
							for(d=0;d<rr;d++)
								strcpy(temp[b][d],"");
						}
					}
				}
			}
		}
	}
	////////////////////////////////////////////////////////////////
	for(f=0;f<rr;f++)
	{
		for(a=0;a<t;a++)
			if(!strcmp(touying[a],atttemp[f]))
				cout<<"	"<<atttemp[f];
	}
	cout<<endl<<endl;
	int tkey=0;
	for(a=0;a<ll;a++)
	{
		tkey=0;
		for(b=0;b<rr;b++)
		{
			if(strcmp(temp[a][b],""))
			{
				tkey=1;
				for(f=0;f<t;f++)
				{
					if(!strcmp(touying[f],atttemp[b]))
						cout<<"	"<<temp[a][b];
				}
			}	
		}
		if(tkey==1)
			cout<<endl;
	}
	cout<<endl;

	clock_t end=clock(); 
	unsigned long dis_time=end-start;
	cout<<"	"<<dis_time<<"毫秒!"<<endl<<endl;
}

void tree()
{
	int i=0,tounum=0,biaonum=0,tiaonum=0;
	char touying[100][20],biao[100][20],tiaojian[100][20];
	while(strcmp(str1[i],"from"))
	{
		if(strcmp(str1[i],","))
			strcpy(touying[tounum++],str1[i]);
		i++;
	}
	i++;
	while(strcmp(str1[i],"where"))
	{
		if(strcmp(str1[i],","))
			strcpy(biao[biaonum++],str1[i]);
		i++;
	}
	i++;
	while(strcmp(str1[i],"\0"))
	{		
		strcpy(tiaojian[tiaonum++],str1[i++]);
	}
	cout<<"	Π ";
	for(i=0;i<tounum;i++)
	{
		cout<<touying[i];
		if(i+1!=tounum)
			cout<<",";
	}
	cout<<endl<<"	(σ ";
	for(i=0;i<tiaonum;i++)
	{
		cout<<tiaojian[i];
	}
	cout<<endl<<"	(";
	for(i=0;i<tounum;i++)
	{
		cout<<touying[i];
		if(i+1!=tounum)
			cout<<"×";
	}
	cout<<"))"<<endl<<endl;
	/////////////////////////
	cout<<"			Π ";
	for(i=0;i<tounum;i++)
	{
		cout<<touying[i];
		if(i+1!=tounum)
			cout<<",";
	}
	cout<<endl<<"			|";
	cout<<endl<<"			|";
	cout<<endl<<"		σ ";
	for(i=0;i<tiaonum;i++)
	{
		cout<<tiaojian[i];
	}
	cout<<endl<<"			|";
	cout<<endl<<"			|";
	cout<<endl<<"			×"<<endl;;
	//////////////////////////////
	for(i=0;i<tounum;i++)
	{
		for(int j=2;j>0;j--)
			cout<<"	";
		cout<<"|";
		for(int k=2;k>0;k--)
			cout<<"	";
		if(i%2==0&&i!=0)
			cout<<endl;
		cout<<touying[i];
		if(i+1!=tounum)
			cout<<"×";
	}
}

void select()
{
	cout<<endl;
	int tag1=0,tag2=0;
	int t=0;
	while(strcmp(str1[t],"\0"))
	{
		if(!strcmp(str1[t],"*"))
		{
			tag1=1;
		}
		if(!strcmp(str1[t],"where"))
		{
			tag2=2;
		}
		t++;
	}
	t=0;
	while(strcmp(str1[t],"\0"))
	{
		if(!strcmp(str1[t],"from"))
		{
			while(strcmp(str1[t],"where")&&strcmp(str1[t],"\0"))
			{
				if(!strcmp(str1[t],","))
				{
					if(tag1!=1&&tag2==2||(tag1==0&&tag2==0))
						selectResult8(0);/////////////////////
					if(tag1==1&&tag2==2)
						selectResult8(1);///////////////
					if((tag1==1&&tag2==0))
						selectResult8(2);///////////////
					//tree();
					return;
				}
				t++;
			}
		}
		t++;
	}
	if(tag1==1&&tag2!=2)
	{
		selectResult1();//*索引
		//selectResult2();//*
		return;
	}
	if(tag1==1&&tag2==2)
	{
		selectResult5(1);//*where
		return;
	}
	if(tag1!=1&&tag2!=2)
	{
		//selectResult3();//nowhere
		selectResult4();//索引nowhere
		return;
	}
	if(tag1!=1&&tag2==2)
	{
		selectResult5(0);//where
		return;
	}
}

void disData()
{
	FILE *fpw;
	fpw=fopen("all.txt","w");
	cout<<endl;
	LinkList p=L->next;
	while(p)
	{
		FILE *fp;
		fp=fopen(p->name,"wb");
		cout<<"		"<<p->name<<endl;//
		fputs(p->name,fpw);
		fputs(" ",fpw);
		cout<<"		"<<p->index<<endl;
		fputs(p->index,fpw);
		fputs(" ",fpw);
		for(int i=0;i<p->attnum;i++)
		{
			cout<<"	"<<p->att[i]<<"	";//
			fputs(p->att[i],fpw);
			fputs(" ",fpw);
			fputs(p->type[i],fpw);
			fputs(" ",fpw);
		}
		cout<<endl;//
		for(int a=0;a<p->yuannum;a++)
		{
			for(int b=0;b<p->attnum;b++)
			{
				cout<<"	"<<p->yuan[a][b]<<"	";//
				int j=0,i=0;
				char temp[20]="";//记录定长为20
				while(p->yuan[a][b][j]!='\0')
				{
					temp[i++]=p->yuan[a][b][j++];
				}
				if(i!=20)
				{
					for(int d=i;d<20;d++)
					{
						temp[d]=' ';
					}
				}
				temp[20]='\0';
				fputs(temp,fp);
				/////////////////////////////////
				//fputs(p->yuan[a][b],fp);
				//fputs(" ",fp);
			}
			cout<<endl;//
			//fputs(",",fp);
		}
		fclose(fp);
		p=p->next;
		fputs("\n",fpw);
	}
	fclose(fpw);
	//cout<<endl;//
}

void writeIndex()
{
	FILE *fpw;
	fpw=fopen("allIndex.txt","w");
	LinkList q=L;
	IndexList p=I;
	int key;
	while(p->next)
	{
		key=0;
		q=L;
		while(q->next)
		{
			if(!strcmp(q->next->index,p->next->name))
			{
				key=1;
				for(int a=0;a<q->next->attnum;a++)
				{
					if(!strcmp(p->next->att,q->next->att[a]))
						key=2;
				}
				if(key==2)
				{
					FILE *fp;
					fp=fopen(p->next->name,"wb");
					cout<<"		"<<p->next->name;
					fputs(p->next->name,fpw);
					fputs(" ",fpw);
					cout<<"		"<<p->next->tablename;
					fputs(p->next->tablename,fpw);
					fputs(" ",fpw);
					cout<<"		"<<p->next->att;
					fputs(p->next->att,fpw);
					fputs(" ",fpw);
					cout<<"		"<<p->next->sort<<endl;
					fputs(p->next->sort,fpw);
					fputs(" ",fpw);
					for(int a=0;a<p->next->length;a++)
					{
						int j=0,i=0;
						char temp[20]="";//记录定长为20
						cout<<"	"<<p->next->context[a]<<"	";		
						while(p->next->context[a][j]!='\0')
						{
							temp[i++]=p->next->context[a][j++];
						}
						if(i!=20)
						{
							for(int d=i;d<20;d++)
							{
								temp[d]=' ';
							}
						}
						temp[20]='\0';
						fputs(temp,fp);
						//////////////////////////////////
						cout<<"	"<<p->next->index[a]<<"	";
						j=0,i=0;
						strcpy(temp,"");
						while(p->next->index[a][j]!='\0')
						{
							temp[i++]=p->next->index[a][j++];
						}
						if(i!=20)
						{
							for(int d=i;d<20;d++)
							{
								temp[d]=' ';
							}
						}
						temp[20]='\0';
						fputs(temp,fp);
						cout<<endl;
					}
					fclose(fp);
					fputs("\n",fpw);
					break;
				}
				else
				{
					FILE *fp;
					fp=fopen(p->next->name,"wb");
					fputs("",fp);
					fclose(fp);
					p->next=p->next->next;
					strcpy(q->next->index,"0000");
					cout<<"Error!"<<endl;
					break;
				}
			}
			q=q->next;
		}
		int del=0;
		if(key==0)
		{
			FILE *fp;
			if((fp=fopen(p->next->name,"wb"))!=NULL)
			{
				fputs("",fp);
				fclose(fp);
			}
			p->next=p->next->next;
			del=1;
			//cout<<"Error!"<<endl;
		}
		if(p->next==NULL)
			return;
		if(del==0)
			p=p->next;
	}
	fclose(fpw);
	cout<<endl;
}

void grant()
{
	UserList p,s=U;
	int i;
	if(!strcmp(str1[1],"createtab")||!strcmp("createind",str1[1]))
	{
		p=U;
		while(p)
		{
			if(!strcmp(p->name,str1[3]))
			{
				p->ct=1;
				return;
			}
			p=p->next;
		}
		if(p==NULL)
		{
			cout<<"Error!"<<endl;
		}
	}
	if(!strcmp(str1[1],"inserttab"))
	{
		p=U;
		while(p)
		{
			if(!strcmp(p->name,str1[5]))
			{
				for(i=0;i<p->inum;i++)
				{
					if(!strcmp(p->insert[i],str1[3]))
						return;
				}
				strcpy(p->insert[p->inum],str1[3]);
				p->inum++;
				return;
			}
			p=p->next;
		}
		if(p==NULL)
		{
			cout<<"Error!"<<endl;
		}
	}
	if(!strcmp(str1[1],"delettab"))
	{
		p=U;
		while(p)
		{
			if(!strcmp(p->name,str1[5]))
			{
				for(i=0;i<p->dnum;i++)
				{
					if(!strcmp(p->delet[i],str1[3]))
						return;
				}
				strcpy(p->delet[p->dnum],str1[3]);
				p->dnum++;
				return;
			}
			p=p->next;
		}
		if(p==NULL)
		{
			cout<<"Error!"<<endl;
		}
	}
	if(!strcmp(str1[1],"updatetab"))
	{
		p=U;
		while(p)
		{
			if(!strcmp(p->name,str1[5]))
			{
				for(i=0;i<p->unum;i++)
				{
					if(!strcmp(p->update[i],str1[3]))
						return;
				}
				strcpy(p->update[p->unum],str1[3]);
				p->unum++;
				return;
			}
			p=p->next;
		}
		if(p==NULL)
		{
			cout<<"Error!"<<endl;
		}
	}
	if(!strcmp(str1[1],"selecttab"))
	{
		p=U;
		while(p)
		{
			if(!strcmp(p->name,str1[5]))
			{
				for(i=0;i<p->snum;i++)
				{
					if(!strcmp(p->select[i],str1[3]))
						return;
				}
				strcpy(p->select[p->snum],str1[3]);
				p->snum++;
				return;
			}
			p=p->next;
		}
		if(p==NULL)
		{
			cout<<"Error!"<<endl;
		}
	}
	if(!strcmp(str1[1],"altertab"))
	{
		p=U;
		while(p)
		{
			if(!strcmp(p->name,str1[5]))
			{
				for(i=0;i<p->anum;i++)
				{
					if(!strcmp(p->alter[i],str1[3]))
						return;
				}
				strcpy(p->alter[p->anum],str1[3]);
				p->anum++;
				return;
			}
			p=p->next;
		}
		if(p==NULL)
		{
			cout<<"Error!"<<endl;
		}
	}
	if(!strcmp(str1[1],"droptab"))
	{
		p=U;
		while(p)
		{
			if(!strcmp(p->name,str1[5]))
			{
				for(i=0;i<p->drnum;i++)
				{
					if(!strcmp(p->drop[i],str1[3]))
						return;
				}
				strcpy(p->drop[p->drnum],str1[3]);
				p->drnum++;
				return;
			}
			p=p->next;
		}
		if(p==NULL)
		{
			cout<<"Error!"<<endl;
		}
	}
}

void revoke()
{
	UserList p=U;
	int i;
	while(p)
	{
		if(!strcmp(str1[5],p->name))
		{
			if(!strcmp(str1[1],"createtab"))//1
			{
				p->ct=0;
			}
			if(!strcmp(str1[1],"inserttab"))//2
			{
				for(i=0;i<p->inum;i++)
				{
					if(!strcmp(p->insert[i],str1[3]))
					{
						strcpy(p->insert[i],p->insert[p->inum-1]);
						p->inum--;
						return;
					}
				}
			}
			if(!strcmp(str1[1],"delettab"))//3
			{
				for(i=0;i<p->dnum;i++)
				{
					if(!strcmp(p->delet[i],str1[3]))
					{
						strcpy(p->delet[i],p->delet[p->dnum-1]);
						p->dnum--;
						return;
					}
				}
			}
			if(!strcmp(str1[1],"updatetab"))//4
			{
				for(i=0;i<p->unum;i++)
				{
					if(!strcmp(p->update[i],str1[3]))
					{
						strcpy(p->update[i],p->update[p->unum-1]);
						p->unum--;
						return;
					}
				}
			}
			if(!strcmp(str1[1],"selecttab"))//5
			{
				for(i=0;i<p->snum;i++)
				{
					if(!strcmp(p->select[i],str1[3]))
					{
						strcpy(p->select[i],p->select[p->snum-1]);
						p->snum--;
						return;
					}
				}
			}
			if(!strcmp(str1[1],"altertab"))//6
			{
				for(i=0;i<p->anum;i++)
				{
					if(!strcmp(p->alter[i],str1[3]))
					{
						strcpy(p->alter[i],p->alter[p->anum-1]);
						p->anum--;
						return;
					}
				}
			}
			if(!strcmp(str1[1],"droptab"))//7
			{
				for(i=0;i<p->drnum;i++)
				{
					if(!strcmp(p->drop[i],str1[3]))
					{
						strcpy(p->drop[i],p->drop[p->drnum-1]);
						p->drnum--;
						return;
					}
				}
			}
		}
		p=p->next;
	}
	if(p==NULL)
	{
		cout<<"Error!"<<endl;
	}
}

void control()
{
	if(name==1)
		create();
	if(name==2)
	{
		if(L->next!=NULL)
		{
			if(!strcmp(str[3],"add"))
				addAttribute();
			if(!strcmp(str[3],"drop"))
				delAttribute();
		}
		else
			cout<<"Error!"<<endl;
	}
	if(name==3)
	{
		if(L->next!=NULL)
		{
			if(!strcmp(str[1],"table"))
				delTable();
			if(!strcmp(str[1],"index"))
				delIndex();
		}
		else
			cout<<"Error!"<<endl;
	}
	if(name==4)
	{
		if(L->next!=NULL)
		{
			delItem();
		}
		else
			cout<<"Error!"<<endl;
	}	
	if(name==5)
	{
		if(L->next!=NULL)
		{
			addItem();
		}
		else
			cout<<"Error!"<<endl;
	}
	if(name==6)
	{
		if(L->next!=NULL)
		{
			chItem();
		}
		else
			cout<<"Error!"<<endl;
	}
	if(name==7)
	{
		if(L->next!=NULL)
		{
			select();
		}
		else
			cout<<"Error!"<<endl;
	}
	if(name==8)
	{
		if(U->next!=NULL)
		{
			grant();
		}
		else
			cout<<"Error!"<<endl;
	}
	if(name==9)
	{
		if(U->next!=NULL)
		{
			revoke();
		}
		else
			cout<<"Error!"<<endl;
	}
}

void read()
{
	FILE *fp;
	fp=fopen("all.txt","r");
	char tname[100],att[100],type[100];
	char ch;
	int i,j;
	LinkList p=L;
	LinkList q;
	ch=fgetc(fp);
	while(ch!=-1)
	{
		q=new LinkNode;
		q->attnum=0;
		q->yuannum=0;
		i=0;
		while(ch!=' ')
		{
			tname[i++]=ch;
			ch=fgetc(fp);
		}
		tname[i]='\0';
		strcpy(q->name,tname);
		ch=fgetc(fp);
		i=0;
		while(ch!=' ')
		{
			tname[i++]=ch;
			ch=fgetc(fp);
		}
		tname[i]='\0';
		strcpy(q->index,tname);
		ch=fgetc(fp);
		while(ch!='\n'&&ch!=-1)
		{
			j=0;
			while(ch!=' '&&ch!='\n')
			{
				att[j++]=ch;
				ch=fgetc(fp);
			}
			att[j]='\0';
			strcpy(q->att[q->attnum],att);
			j=0;
			ch=fgetc(fp);
			while(ch!=' '&&ch!='\n')
			{
				type[j++]=ch;
				ch=fgetc(fp);
			}
			type[j]='\0';
			strcpy(q->type[q->attnum],type);
			q->attnum++;
			ch=fgetc(fp);
		}
		p->next=q;
		q->next=NULL;
		p=q;
		ch=fgetc(fp);
	}
	fclose(fp);
	///////////////////////////////////////////////////
	p=L->next;
	char yuan[100];
	while(p)
	{
		fp=fopen(p->name,"r");
		ch=fgetc(fp);
		while(ch!=-1)
		{
			i=0;
			for(int a=0;a<p->attnum;a++)
			{
				j=0;
				while(ch!=' '&&ch!=',')
				{
					yuan[j++]=ch;
					ch=fgetc(fp);
				}
				yuan[j]='\0';
				while(j+1<20)
				{
					j++;
					ch=fgetc(fp);
				}
				strcpy(p->yuan[p->yuannum][i++],yuan);
				ch=fgetc(fp);
			}
			p->yuannum++;
			//ch=fgetc(fp);	
		}
		p=p->next;
	}
	///////////////////////////////////////////////////////
	IndexList s=I;
	IndexList w;
	fp=fopen("allIndex.txt","r");
	ch=fgetc(fp);
	while(ch!=-1)
	{
		w=new IndexNode;
		w->length=0;
		i=0;
		while(ch!=' ')
		{
			tname[i++]=ch;
			ch=fgetc(fp);
		}
		tname[i]='\0';
		strcpy(w->name,tname);
		ch=fgetc(fp);
		i=0;
		while(ch!=' ')
		{
			tname[i++]=ch;
			ch=fgetc(fp);
		}
		tname[i]='\0';
		strcpy(w->tablename,tname);
		ch=fgetc(fp);
		i=0;
		while(ch!=' ')
		{
			tname[i++]=ch;
			ch=fgetc(fp);
		}
		tname[i]='\0';
		strcpy(w->att,tname);
		ch=fgetc(fp);
		i=0;
		while(ch!=' ')
		{
			tname[i++]=ch;
			ch=fgetc(fp);
		}
		tname[i]='\0';
		strcpy(w->sort,tname);
		ch=fgetc(fp);
		
		w->next=NULL;
		s->next=w;
		s=w;
		ch=fgetc(fp);
	}
	fclose(fp);
	/////////////////////////////////////////
	s=I->next;
	char con[100];
	while(s)
	{
		fp=fopen(s->name,"r");
		ch=fgetc(fp);
		i=0;
		while(ch!=-1)
		{
			j=0;
			while(ch!=' '&&ch!=',')
			{
				con[j++]=ch;
				ch=fgetc(fp);
			}
			con[j]='\0';
			while(j+1<20)
			{
				j++;
				ch=fgetc(fp);
			}
			strcpy(s->context[i],con);
			ch=fgetc(fp);

			j=0;
			while(ch!=' '&&ch!=',')
			{
				con[j++]=ch;
				ch=fgetc(fp);
			}
			con[j]='\0';
			while(j+1<20)
			{
				j++;
				ch=fgetc(fp);
			}
			strcpy(s->index[i++],con);
			ch=fgetc(fp);

			s->length++;
			//ch=fgetc(fp);	
		}
		s=s->next;
	}
	////////////////////////////////////////////
	UserList u=U,r;
	FILE *fpw;
	fpw=fopen("user.txt","r");
	ch=fgetc(fpw);
	while(ch!=-1)
	{
		while(ch!='\n')
		{
			r=new UserNode;
			r->cnum=0;
			r->inum=0;
			r->dnum=0;
			r->unum=0;
			r->snum=0;
			r->anum=0;
			r->drnum=0;
			i=0;
			while(ch!='@')
			{
				r->name[i++]=ch;
				ch=fgetc(fpw);
			}
			r->name[i]='\0';
			ch=fgetc(fpw);
			if(ch=='1')
				r->ct=1;
			if(ch=='0')
				r->ct=0;
			ch=fgetc(fpw);
			ch=fgetc(fpw);
			while(ch!='$')//1
			{
				i=0;
				while(ch!='#')
				{
					r->create[r->cnum][i++]=ch;
					ch=fgetc(fpw);
				}
				r->create[r->cnum++][i]='\0';
				ch=fgetc(fpw);
			}
			ch=fgetc(fpw);
			while(ch!='$')//2
			{
				i=0;
				while(ch!='#')
				{
					r->insert[r->inum][i++]=ch;
					ch=fgetc(fpw);
				}
				r->insert[r->inum++][i]='\0';
				ch=fgetc(fpw);
			}
			ch=fgetc(fpw);
			while(ch!='$')//3
			{
				i=0;
				while(ch!='#')
				{
					r->delet[r->dnum][i++]=ch;
					ch=fgetc(fpw);
				}
				r->delet[r->dnum++][i]='\0';
				ch=fgetc(fpw);
			}
			ch=fgetc(fpw);
			while(ch!='$')//4
			{
				i=0;
				while(ch!='#')
				{
					r->update[r->unum][i++]=ch;
					ch=fgetc(fpw);
				}
				r->update[r->unum++][i]='\0';
				ch=fgetc(fpw);
			}
			ch=fgetc(fpw);
			while(ch!='$')//5
			{
				i=0;
				while(ch!='#')
				{
					r->select[r->snum][i++]=ch;
					ch=fgetc(fpw);
				}
				r->select[r->snum++][i]='\0';
				ch=fgetc(fpw);
			}
			ch=fgetc(fpw);
			while(ch!='$')//6
			{
				i=0;
				while(ch!='#')
				{
					r->alter[r->anum][i++]=ch;
					ch=fgetc(fpw);
				}
				r->alter[r->anum++][i]='\0';
				ch=fgetc(fpw);
			}
			ch=fgetc(fpw);
			while(ch!='$')//7
			{
				i=0;
				while(ch!='#')
				{
					r->drop[r->drnum][i++]=ch;
					ch=fgetc(fpw);
				}
				r->drop[r->drnum++][i]='\0';
				ch=fgetc(fpw);
			}
			ch=fgetc(fpw);
		}
		while(u->next)
		{
				u=u->next;
		}
		r->next=NULL;
		u->next=r;
		ch=fgetc(fpw);
	}
	fclose(fpw);

	u=U;
	UserList y;
	fpw=fopen("manage.txt","r");
	ch=fgetc(fpw);
	char temp[20];
	int flag;
	while(ch!=-1)
	{
		i=0;
		flag=0;
		while(ch!=' ')
		{
			temp[i++]=ch;
			ch=fgetc(fpw);
		}
		temp[i]='\0';
		y=U->next;
		while(y)
		{
			if(!strcmp(y->name,temp))
				flag=1;
			y=y->next;
		}
		if(flag==0)
		{
			r=new UserNode;
			r->ct=0;
			r->cnum=0;
			r->inum=0;
			r->dnum=0;
			r->unum=0;
			r->snum=0;
			r->anum=0;
			r->drnum=0;
			strcpy(r->name,temp);
			while(u->next)
			{
				u=u->next;
			}
			r->next=NULL;
			u->next=r;
			ch=fgetc(fpw);
		}
		while(ch!='\n')
		{
			ch=fgetc(fpw);
		}
		ch=fgetc(fpw);
	}
	fclose(fpw);
}

void puttime() 
{
	time_t rawtime; 
    struct tm * timeinfo;
    time(&rawtime); 
    timeinfo=localtime(&rawtime);
    printf ("%4d-%02d-%02d %02d:%02d:%02d\n",1900+timeinfo->tm_year, 1+timeinfo->tm_mon, 
	timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
}

char username[30];
char userpassword[30];

void login(int flag)
{
	int flag1=1;
	while(flag1)
	{
		printf("\n\t-------------------\n");
		printf("\t请输入用户名: ");
		
		cin>>username;
		printf("\t请输入密码: ");
		
		cin>>userpassword;
		printf("\t-------------------\n");
		FILE *fp;
		if(flag==1)
			fp=fopen("manage.txt","r");
		if(flag==2)
			return;
		char ch;
		char temp[30];
		int i;
	m3:	i=0;
		ch=fgetc(fp);
		while(ch!=' '&&ch!=-1)
		{
			temp[i++]=ch;
			ch=fgetc(fp);
		}
		temp[i]='\0';
		if(!strcmp(username,temp))
		{
			strcpy(temp,"");
			i=0;
			ch=fgetc(fp);
			while(ch!='\r'&&ch!='\n'&&ch!=-1)
			{
				temp[i++]=ch;
				ch=fgetc(fp);
			}
			temp[i]='\0';
			if(strcmp(userpassword,temp))
			{
				system("cls");
				printf("\n\t--用户名或密码错误,请重新输入!--\n");	
				continue;
			}
			else
				flag1=0;
		}
		else
		{
			ch=fgetc(fp);
			while(ch!='\n'&&ch!=-1)
			{
				ch=fgetc(fp);
			}
			if(ch==-1)
			{
				system("cls");
				printf("\n\t--不存在该用户,请重新输入!--\n");	
				continue;
			}
			strcpy(temp,"");
			goto m3;
		}
		fclose(fp);
	}
}

void registered()
{
	int flag1=1;
	while(flag1)
	{
		printf("\n\t-------------------\n");
		printf("\t请设置用户名: ");
		
		cin>>username;
		printf("\t请设置密码: ");
		
		cin>>userpassword;
		printf("\t-------------------\n");

		FILE* fpw=fopen("manage.txt","r");
		char ch=fgetc(fpw);
		char temp[20];
		int flag;
		int i;
		while(ch!=-1)
		{
			i=0;
			flag=0;
			while(ch!=' ')
			{
				temp[i++]=ch;
				ch=fgetc(fpw);
			}
			temp[i]='\0';
			if(!strcmp(username,temp))
			{
				cout<<endl<<"\t该用户已存在,请重新设置!"<<endl;
				flag=1;
				break;
			}
			while(ch!='\n')
			{
				ch=fgetc(fpw);
			}
			ch=fgetc(fpw);
		}
		fclose(fpw);
		if(flag==1)
			continue;

		FILE *fp;
		fp=fopen("manage.txt","a+");
		fputs(username,fp);
		fputs(" ",fp);
		fputs(userpassword,fp);
		fputc('\r',fp);
		fputc('\n',fp);
		fclose(fp);
		flag1=0;
	}
}

void view()
{
	int flag=1;
	char choice;
	while(flag)
	{
		printf("\n\t  数据库系统\n\t");
		puttime();
		printf("\t-------------------\n");
		printf("\t  1.用户登陆\n");
		printf("\t  2.管理员登陆\n");
		printf("\t  3.注册\n");
		printf("\t  0.退出\n");
        printf("\t-------------------\n");
m1:		printf("\n\t请选择菜单:");
        choice=getchar(); 
		getchar();
		if(choice!='1'&&choice!='0'&&choice!='2'&&choice!='3')
		{
			printf("\n\t输入错误，请重新输入!\n");
			goto m1;
		}
		else
		{
			switch(choice)
			{
			case '1':
				login(1);
				flag=0;
				break;
			case '2':
				login(2);
				flag=0;
				break;
			case '3':
				registered();
				flag=0;
				break;
			case '0':
				exit(0);
			}
		}
	}
}

void user()
{
	FILE *fp;
	int i;
	fp=fopen("user.txt","w");
	UserList p=U->next;
	while(p)
	{
		fputs(p->name,fp);
		fputs("@",fp);
		if(p->ct==1)
			fputc('1',fp);
		if(p->ct==0)
			fputc('0',fp);
		fputs("$",fp);
		for(i=0;i<p->cnum;i++)
		{
			fputs(p->create[i],fp);
			fputs("#",fp);
		}
		fputs("$",fp);
		for(i=0;i<p->inum;i++)
		{
			fputs(p->insert[i],fp);
			fputs("#",fp);
		}
		fputs("$",fp);
		for(i=0;i<p->dnum;i++)
		{
			fputs(p->delet[i],fp);
			fputs("#",fp);
		}
		fputs("$",fp);
		for(i=0;i<p->unum;i++)
		{
			fputs(p->update[i],fp);
			fputs("#",fp);
		}
		fputs("$",fp);
		for(i=0;i<p->snum;i++)
		{
			fputs(p->select[i],fp);
			fputs("#",fp);
		}
		fputs("$",fp);
		for(i=0;i<p->anum;i++)
		{
			fputs(p->alter[i],fp);
			fputs("#",fp);
		}
		fputs("$",fp);
		for(i=0;i<p->drnum;i++)
		{
			fputs(p->drop[i],fp);
			fputs("#",fp);
		}
		fputs("$",fp);
		fputs("\n",fp);
		p=p->next;
	}
	fclose(fp);
}

int permissions()
{
	if(!strcmp(username,"name"))
		return 1;
	UserList p=U->next;
	int i;
	while(p)
	{
		if(!strcmp(p->name,username))
		{
			if(name==1)
			{
				if(p->ct==1)
				{
					strcpy(p->create[p->cnum],str1[2]);
					p->cnum++;
					return 1;
				}
				else
					return 0;
			}
			if(name==2)
			{
				for(i=0;i<p->cnum;i++)
				{
					if(!strcmp(p->create[i],str1[2]))
					{
						return 1;
					}
				}
				for(i=0;i<p->anum;i++)
				{
					if(!strcmp(p->alter[i],str1[2]))
					{
						return 1;
					}
				}
				return 0;
			}
			if(name==3)//index
			{
				for(i=0;i<p->cnum;i++)
				{
					if(!strcmp(p->create[i],str1[2]))
					{
						return 1;
					}
				}
				for(i=0;i<p->drnum;i++)
				{
					if(!strcmp(p->drop[i],str1[2]))
					{
						return 1;
					}
				}
				return 0;
			}
			if(name==4)
			{
				for(i=0;i<p->cnum;i++)
				{
					if(!strcmp(p->create[i],str1[2]))
					{
						return 1;
					}
				}
				for(i=0;i<p->dnum;i++)
				{
					if(!strcmp(p->delet[i],str1[2]))
					{
						return 1;
					}
				}
				return 0;
			}	
			if(name==5)
			{
				for(i=0;i<p->cnum;i++)
				{
					if(!strcmp(p->create[i],str1[2]))
					{
						return 1;
					}
				}
				for(i=0;i<p->inum;i++)
				{
					if(!strcmp(p->insert[i],str1[2]))
					{
						return 1;
					}
				}
				return 0;
			}
			if(name==6)
			{
				for(i=0;i<p->cnum;i++)
				{
					if(!strcmp(p->create[i],str1[2]))
					{
						return 1;
					}
				}
				for(i=0;i<p->unum;i++)
				{
					if(!strcmp(p->update[i],str1[2]))
					{
						return 1;
					}
				}
				return 0;
			}
			if(name==7)
			{
				for(i=0;i<p->cnum;i++)
				{
					if(!strcmp(p->create[i],str1[2]))
					{
						return 1;
					}
				}
				for(i=0;i<p->snum;i++)
				{
					if(!strcmp(p->select[i],str1[2]))
					{
						return 1;
					}
				}
				return 0;
			}
			if(name==8)
			{
				if(!strcmp("createtab",str1[1])||!strcmp("createind",str1[1]))
					return 0;
				else
				{
					for(i=0;i<p->cnum;i++)
					{
						if(!strcmp(p->create[i],str1[3]))
							return 1;
					}
					if(i==p->cnum)
						return 0;
				}
			}
			if(name==9)
			{
				if(!strcmp("createtab",str1[1])||!strcmp("createind",str1[1]))
					return 0;
				else
				{
					if(p->ct==1)
						return 1;
					else
						return 0;
				}
			}
		}
		p=p->next;
	}
	if(p==NULL)
	{
		cout<<"Error!"<<endl;
		return 0;
	}
}

void main()
{
	view();
	getchar();
	system("cls");
	//////////////////
	InitList(L);
	InitIndexList(I);
	InitUserList(U);
	read();
	
	while(1)
	{
		FILE *fp;
		fp=fopen("0.txt","w");
m4:		cout<<"sql: ";
		char s[1000];
		int i=0;
		gets(s);
		fputs(s,fp);
		fclose(fp);
////////////////////////////////////////////////////////////
		turn();
		input();
		if(permissions()!=1)
		{
			cout<<"未得到授权!"<<endl<<endl;
			goto m4;
		}
		//dis();
		readtable();
		//distable();
		readwenfa();
		int success=intoStack();
		if(success==1)
		{
			control();
			disData();
			indexcon();
			writeIndex();
			user();
		}
		else
			cout<<"Error!"<<endl;
	}
}