#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<fstream>
using namespace std;

FILE *fp1 = fopen("newinput.txt","r");
FILE *fp2 = fopen("output.txt","w");
int lc=0,flag=0,j=0,lit=0;
char ch;
bool decConstant=false;
bool Origin=false;


struct mot{
	char mneumonic[20];
	char classname[8];
	int opcode;
	int length;
}m[20];

struct RED
{
	char name[10];
	int op;
}r[4];	

struct COND
{
	char name[10];
	int op;
}c[6];	

class littab
{
	public:
	string name;
	int addr;
}l[10];

class Symtab
{
	public:
		string name;
		int addr;
}s1[10];	

void find(string s,bool first)
{
	
	if(s.compare("ORIGIN")==0)
	{
		Origin=true;
		fprintf(fp2,"\t(AD,05)");
		return;
	}
	
	for(int i=0;i<20;i++)
	{
		if(s==m[i].mneumonic)
		{
			if(strcmp(m[i].mneumonic,"DC") == 0)
				decConstant = true;
			if((strcmp(m[i].classname,"AD") == 0) || first!=true) //strcmp(m[i].mneumonic,"DS") == 0) || (strcmp(m[i].mneumonic,"DC") == 0))
				fprintf(fp2,"\t");
			else
				fprintf(fp2,"%d\t",lc);
					
			fprintf(fp2,"(%s,0%d)",m[i].classname,m[i].opcode);			
			return;
		}
	}
	for(int i=0;i<4;i++)
	{
		if(s==r[i].name)
		{
			//fprintf(fp2,"%d\t",lc);
			fprintf(fp2," %d, ",r[i].op);			
			return;
		}
	}
	for(int i=0;i<4;i++)
	{
		if(s==c[i].name)
		{
			//fprintf(fp2,"%d\t",lc);
			fprintf(fp2," (0%d) ",c[i].op);			
			return;
		}
	}

	if(ch!='\n')
		fprintf(fp2,"%d\t",lc);
	
	int k;
	for(k=0;k<j;k++)
	{
		if(s1[k].name[0] == s[0] && s1[k].name[1] == s[1])
		{
			if(s1[k].addr == -1 && first==true)
			{
				s1[k].addr = lc;		
			}
			if(first == false)
				fprintf(fp2," (S,%d) ",k);
			break;
		}
	}
	if(k==j)
	{
		if(ch=='\n')
		{
			s1[j].name = s;
			s1[j].addr = -1;
			j++;
			fprintf(fp2," (S,%d) ",j-1);
		}
		else
		{
			s1[j].name = s;
			s1[j].addr = lc;
			j++;
		}
	}
}

int isnum(char c)
{
	if(c>='0' && c<='9')
		return 1;
	return 0;
}

void searchEQU(string str1, string str2)
{
	int addr;
	for(int i=0;i<j;i++)	
	{
		if(s1[i].name[0] == str2[0] && s1[i].name[1] == str2[1])
		{
			addr = s1[i].addr;
			break;
		}
	}
	
	for(int i=0;i<j;i++)	
	{
		if(s1[i].name[0] == str1[0] && s1[i].name[1] == str1[1])
		{
			s1[i].addr = addr;
			break;
		}
	}
}

void init()
{
	
	strcpy(m[0].mneumonic,"START");
	strcpy(m[0].classname,"AD");
	m[0].opcode=01;
	m[0].length=1;

	strcpy(m[1].mneumonic,"END");
	strcpy(m[1].classname,"AD");
	m[1].opcode=02;
        m[1].length=1;

	strcpy(m[2].mneumonic,"EQU");
	strcpy(m[2].classname,"AD");
	m[2].opcode=03;
        m[2].length=1;

	strcpy(m[3].mneumonic,"LTORG");
	strcpy(m[3].classname,"AD");
	m[3].opcode=04;
        m[3].length=1;
        
	strcpy(m[4].mneumonic,"ORIGIN");
	strcpy(m[4].classname,"AD");
	m[4].opcode=05;
	m[4].length=1;

	strcpy(m[5].mneumonic,"STOP");
	strcpy(m[5].classname,"IS");
	m[5].opcode=01;
	m[5].length=1;

	strcpy(m[6].mneumonic,"ADD");
	strcpy(m[6].classname,"IS");
	m[6].opcode=02;
	m[6].length=1;

	strcpy(m[7].mneumonic,"SUB");
	strcpy(m[7].classname,"IS");
	m[7].opcode=03;
	m[7].length=1;

	strcpy(m[8].mneumonic,"MULT");
	strcpy(m[8].classname,"IS");
	m[8].opcode=04;
	m[8].length=1;

	strcpy(m[9].mneumonic,"MOVER");
	strcpy(m[9].classname,"IS");
	m[9].opcode=05;

	strcpy(m[10].mneumonic,"MOVEM");
	strcpy(m[10].classname,"IS");
	m[10].opcode=06;

	strcpy(m[11].mneumonic,"COMP");
	strcpy(m[11].classname,"IS");
	m[11].opcode=07;

	strcpy(m[12].mneumonic,"BC");
	strcpy(m[12].classname,"IS");
	m[12].opcode=8;

	strcpy(m[13].mneumonic,"READ");
	strcpy(m[13].classname,"IS");
	m[13].opcode=9;

	strcpy(m[14].mneumonic,"PRINT");
	strcpy(m[14].classname,"IS");
	m[14].opcode=10;

	strcpy(m[15].mneumonic,"DS");
	strcpy(m[15].classname,"DL");
	m[15].opcode=01;

	strcpy(m[16].mneumonic,"DC");
	strcpy(m[16].classname,"DL");
	m[16].opcode=02;
	
	strcpy(m[18].mneumonic,"LTORG");
	strcpy(m[18].classname,"AD");
	m[18].opcode=04;
	
	strcpy(m[19].mneumonic,"ORIGIN");
	strcpy(m[19].classname,"AD");
	m[19].opcode=05;
/*---------------------------------*/
	strcpy(r[0].name,"AREG");
	r[0].op=1;
	
	strcpy(r[1].name,"BREG");
	r[1].op=2;
	
	strcpy(r[2].name,"CREG");
	r[2].op=3;
	
	strcpy(r[3].name,"DREG");
	r[3].op=4;

/*-------------------------------*/

struct COND c[6];
	strcpy(c[0].name,"LE");
	c[0].op=1;
	
	strcpy(c[1].name,"LT");
	c[1].op=2;
	
	strcpy(c[2].name,"GT");
	c[2].op=3;
	
	strcpy(c[3].name,"GE");
	c[3].op=4;
	
	strcpy(c[4].name,"EQ");
	c[4].op=5;
	
	strcpy(c[5].name,"ANY");
	c[5].op=6;

	for(int i=0;i<17;i++)
	{
		m[i].length=1;
	}
}

string Constant(string);
string Mneumonic(string, ofstream& file);
void Symbol(string, ofstream& file);
void Literal(string, ofstream& file);
void pass2();

main()
{	
	init();
	int LC=0;
	string word="",prev,label1="",label2="";
	bool first = true;
	ch=fgetc(fp1);
	while(ch!=EOF)
	{
		if((ch==' ' || ch=='\n' || ch==',') )
		{
			if(isnum(word[0]))
			{
				LC = stoi(word);
				if(lc==0)
					lc=LC-1;
					
				if(decConstant == true)
				{
					decConstant = false;
					lc += LC-1;
				}
				else if(Origin == true)
				{
					Origin = false;
					lc = LC-1;
					fprintf(fp2,"\t");
				}
					
				fprintf(fp2," (c,%d)",LC);				
				
			}
			else if(word[1] == '\'' && word[0] == '=')
			{
				int flag = 1;
				for(int i=0;i<lit;i++)
				{
					if(word == l[i].name && l[i].addr == -1)
					{
						flag = 0;
						fprintf(fp2,"(L,%d)",i);	
						break;
					}
				}
				if(flag)
				{
					l[lit].name = word;
					l[lit].addr = -1;
					lit++;
					fprintf(fp2,"(L,%d)",lit-1);
				}
			}
			else
			{
				if(word == "EQU" )
					label1 = prev;
				else if(prev == "EQU")
					label2 = word;
				if(label1.size()>0 && label2.size()>0)
					searchEQU(label1,label2);
					
				if(word[0]=='L' && word[1]=='T' && word[2]=='O' && word[3]=='R' && word[4]=='G')
				{
					int temp = lc;
					for(int i=0;i<lit;i++)
					{
						if(l[i].addr == -1)
						{
							l[i].addr = temp;
							temp++;
						}
					}
					fprintf(fp2,"\t(AD,04)");
				}
				
				else if(word[0]=='E' && word[1]=='N' && word[2]=='D')
				{
					int temp = lc;
					for(int i=0;i<lit;i++)
					{
						if(l[i].addr == -1)
						{
							l[i].addr = temp;
							temp++;
						}
					}
					fprintf(fp2,"\t(AD,02)");
					word="";
				}
				else
				{
					find(word,first);
					prev = word;
				}
				first = false;
			}
			word="";
		}
		else
		{
			word+=ch;
		}
		if(ch=='\n')
		{
			lc++;
			fprintf(fp2,"\n");
			first = true;
		}
		ch=fgetc(fp1);
	}
	
	int cnt=0;
	cout<<"\nSYMBOL TABLE:\n";
	for(int i=0;i<j;i++)
	{
		cout<<s1[i].name<<"\t";
		cout<<s1[i].addr<<endl;
		if(s1[i].addr == -1)
			cnt++;
	}
		
	cout<<"\nLITERAL TABLE:\n";
	for(int i=0;i<lit;i++)
	{
		cout<<l[i].name<<"\t";
		cout<<l[i].addr<<endl;
	}
	
	fclose(fp1);
	fclose(fp2);
	if(cnt>0)
		cout<<"\nPASS II cannot process....undefined labels found!\n";
	else
		pass2();
	return 0;
}

string Constant(string word)
{
	if(word[0]=='(' && word[1]=='c')
		return "YES";
	return "NO";
}

string Mneumonic(string word1, ofstream& file2)
{
	if(word1[0]!='(')
		return "NO";
		
	int found = word1.find(',');
	string word2 = word1.substr(1,found-1);
	if(word2=="AD" || word2=="IS" || word2=="DL")
	{
		//cout<<word2;
		if(word2=="IS")
		{
			//cout<<word1.substr(found+1,word1.size()-2);
			file2<<word1.substr(found+1,2);
			file2<<" ";
		}
		else
		{
			file2<<"-- ";
		}
		return "YES";
	}
	return "NO";
}

void Symbol(string word, ofstream& file2)
{
	int index = word[3]-48;
	file2<<s1[index].addr;
	file2<<" ";
}

void Literal(string word, ofstream& file2)
{
	int index = word[3]-48;
	file2<<l[index].addr;
	file2<<" ";
}

string isnum(string word, ofstream& file2)
{
	if(word[0]>='0' && word[0]<='9')
	{
		file2<<word<<" ";
		return "YES";
	}
	return "NO";
}


bool valid(char ch)
{
	if(ch>=0 && ch<=255)
		return true;
	return false;
}


void pass2()
{
	FILE *fp3 = fopen("output.txt","r");
	ofstream file2;
	file2.open("pass2out.txt",ios::trunc);
	char ch,pv;
	string word = "";

	do
	{
		ch = fgetc(fp3);
		if(ch=='(')
			break;
	}while(true);
	
	while(ch!=EOF)
	{	
		if(valid(ch)==false)
			;
		else if(pv == ' ' && ch == ' ')
			word = "";
		else if((ch=='\n' || ch==' ' || ch=='\t') || (ch==',' && pv>='0' && pv<='9'))
		{
			if(word != " ")
			{
				//cout<<word<<endl;
				if(Constant(word) == "YES")
					file2<<"-- ";
				else if(Mneumonic(word,file2) == "YES")		
					;
				else if(word[0]=='(' && word[1]=='S')
					Symbol(word,file2);
				
				else if(word[0]=='(' && word[1]=='L')
					Literal(word,file2);
				
				else if(isnum(word,file2) == "YES")
					;
				else
					;
			
				if(ch=='\n')
					file2<<endl;
			}
			word = "";
		}
		else
			word+=ch;
		pv = ch;
		ch = fgetc(fp3);
	}
	
	file2.close();
}
