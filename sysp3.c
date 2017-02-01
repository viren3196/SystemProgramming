#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

FILE *fp1 = fopen("input3.txt","r");
FILE *fp2 = fopen("output3.txt","r");

string lastEV = "";
int flag=0;

class MNTTAB
{
	public:
		string name;
		int pp,kp,ev,mdtp,kpdp,sstp;
}m[5];

vector<string> PNTAB[5];
vector<string> APTAB[5];
map<string,int> EVTAB[5];
map<string,int> ::iterator it;

class MDT
{
	public:
		int lc;
		string name, op1, op2;
}mobj[5][10];

int findindex(string word)
{
	for(int i=0 ;i<5 ; i++)
		for(int j=0 ;j<PNTAB[i].size() ; j++)
		{
			if(PNTAB[i][j] == word)
				return j+1;
		}
	return -1;
}

int macroIndex(string macro)
{
	for(int i=0;i<5 ; i++)
	{
		if(m[i].name == macro)
			return i;
	}
}

void Environment(string word, int index)
{
	if(EVTAB[index].find(word) == EVTAB[index].end())
	{
		EVTAB[index][word] = 0;
		m[index].ev++;
	}
}

string checkEnvironment(string word, int index)
{
	if(EVTAB[index].find(word) != EVTAB[index].end())
	{
		return "YES";
	}
	return "NO";
}

void EVgetIndex(string word, string num, int xx)
{
	for(it=EVTAB[xx].begin() ; it!=EVTAB[xx].end() ; it++)
	{
		if(it->first == word)
		{
			it->second = stoi(num);
			return;
		}
	}
}

string process(string word, string macro, int xx, int* ev1)
{
	if(flag==0)
	{
		for(int i=0;i<5;i++)
		{
			if(m[i].name == word)
			{
				cout<<"DUPLICATE MACROS DEFINED\n";
				cout<<"I am terminating your program!\n";
				exit(0);
			}
			else if(m[i].name == "")
			{
				m[i].name = word;
				m[i].pp = 0;
				m[i].kp = 0;
				m[i].ev = 0;
				m[i].mdtp = 25;
				m[i].kpdp = 0;
				m[i].sstp = 0;
				break;
			}
		}
		flag=1;
	}
	else if(word == "LCL")
	{
		*ev1 = 1;
	}
	else
	{
		int signal=0;
		if((word[0]>='0' && word[0]<='9') || word[0]=='-')
		{
			EVgetIndex(lastEV,word,xx);
		}		
	
		else if(word[0]=='&')
		{
			if(*ev1==1)
			{
				Environment(word,xx);
			}
			
			else if(checkEnvironment(word,xx) == "YES")
			{
				lastEV = word;
			}
			
			else
			{
				int i;
				for(i=0;i<PNTAB[xx].size();i++)
				{
					if(PNTAB[xx][i] == word)
					{
						signal = 1;
						break;
					}
				}
				if(i==PNTAB[xx].size())
				{
					m[xx].pp += 1;

					if(word[word.size()-1] == '=')
					{
						m[xx].kp += 1;
						word.pop_back();
					}
					PNTAB[xx].push_back(word);
				}
			}
		}
		else if(word != "SET")
		{
			int i;
			for(i=0;i<10;i++)
			{
				if(mobj[xx][i].name=="")
				{
					mobj[xx][i].name = word;
					break;
				}
			}
			if(i==0)
				mobj[xx][i].lc = m[0].mdtp;
			else
				mobj[xx][i].lc = mobj[xx][i-1].lc+1;
		}
		
		if(signal == 1)
		{
			int j;
			for(int i=0;i<10;i++)
			{
				if(mobj[xx][i].op1 == "")
				{
					j = findindex(word);
					mobj[xx][i].op1 += "(P,";
					mobj[xx][i].op1 += to_string(j);
					mobj[xx][i].op1 +=")";
					break;
				}
				if(mobj[xx][i].op2 == "")
				{
					j = findindex(word);
					mobj[xx][i].op2 += "(P,";
					mobj[xx][i].op2 += to_string(j);
					mobj[xx][i].op2 +=")";
					break;
				}
			}
		}
	}
	
	if(word == "MEND")
	{
		flag=0;
		return "OFF";
	}
	return "ON";
}

void init()
{
	for(int j=0;j<5;j++)
		for(int i=0;i<10;i++)
		{
			mobj[j][i].lc = 0;
			mobj[j][i].name = "";
			mobj[j][i].op1 = "";
			mobj[j][i].op2 = "";
		}
	
	for(int i=0;i<5;i++)
	{
		m[i].name = "";
	}
}

string checkMacro(string word)
{
	for(int i=0;i<5;i++)	
	{
		if(m[i].name == word)
		{
			return "ON";
		}
	}
	return "OFF";
}

void macroExpansion(ofstream& file1, int xx)
{	
	for(int i=0;i<10;i++)
	{
		if(mobj[xx][i].name != "")
		{
			
			file1<<" + ";
			file1<<mobj[xx][i].name;
			
			if(mobj[xx][i].name!="MEND")
				file1<<" ";
			else
				file1<<"\n";
				
			if(mobj[xx][i].name!="MEND")
			{
				int index1 = ((int)(mobj[xx][i].op1[3]-48))-1;
				file1<<APTAB[xx][index1];
				file1<<",";
			
				int index2 = ((int)(mobj[xx][i].op2[3]-48))-1;
				file1<<APTAB[xx][index2];
				file1<<"\n";
			}
			//cout<<index1<<index2;	
			//cout<<mobj[i].name<<APTAB[index1]<<APTAB[index2];

		}
		else
		{
			break;
		}
	}

}

void printAll()
{
	cout<<"\n*** MNTTAB TABLE ***\n";
	
	for(int i=0;i<5;i++)
	{
		if(m[i].name!="")
		{
			cout<<i+1<<" ";
			cout<<m[i].name<<" ";
			cout<<m[i].pp<<" ";
			cout<<m[i].kp<<" ";
			cout<<m[i].ev<<" ";
			cout<<m[i].mdtp<<" ";
			cout<<m[i].kpdp<<" ";
			cout<<m[i].sstp<<"\n";
		}
		else
			break;
	}
	
	cout<<endl;
	
	cout<<"\n*** EVTAB TABLE ***\n";
	for(int j=0;j<5;j++)
	{
		if(EVTAB[j].size()>0)
			cout<<m[j].name<<endl;
		int i=1;	
		for(it = EVTAB[j].begin() ; it!=EVTAB[j].end() ;)
		{
			cout<<i<<" "<<it->first<<" "<<it->second<<endl;
			i++;
			it++;	
		}
		if(EVTAB[j].size()>0)
			cout<<endl;
	}
	
	cout<<"\n*** PNTAB TABLE ***\n";
	for(int j=0;j<5;j++)
	{
		if(PNTAB[j].size()>0)
			cout<<m[j].name<<endl;
			
		for(int i=0; i<PNTAB[j].size();i++)
		{
			cout<<i+1<<" "<<PNTAB[j][i]<<endl;
			if(i==PNTAB[j].size()-1)
				cout<<endl;		
		}
	}
		
	cout<<"\n*** APTAB TABLE ***\n";
	for(int j=0;j<5;j++)
	{
		if(APTAB[j].size()>0)
			cout<<m[j].name<<endl;
			
		for(int i=0; i<APTAB[j].size();i++)
		{
			cout<<i+1<<" "<<APTAB[j][i]<<endl;
			if(i==APTAB[j].size()-1)
				cout<<endl;		
		}
	}
		
	cout<<endl;
	
	cout<<"*** MDT TABLE ***\n";
	for(int j=0;j<5;j++)
	{
		if(mobj[j][0].name != "")
			cout<<m[j].name<<endl;
			
		for(int i=0;i<10;i++)
		{
			if(mobj[j][i].name != "")
			{
				cout<<mobj[j][i].lc<<" ";
				cout<<mobj[j][i].name<<" ";
				cout<<mobj[j][i].op1<<" ";
				cout<<mobj[j][i].op2<<" ";
				cout<<endl;
			}
			else
				break;
		}
		if(mobj[j][0].name=="")
			break;		
		cout<<endl;
	}

}

main()
{
	ofstream file1;    
	file1.open("output3.txt",ios::trunc );
	
	init();
	
	int f = 0, pflag=0, flag2=1, index, *ev1;
	int g=0;
	ev1 = &g;
	string word="", macro, macromode = "OFF", Expansionmode = "OFF", currentMacro="";
	char ch=fgetc(fp1), pch;
	while(ch!=EOF)
	{
		if(ch=='\n' && pch=='\n')
				;
		else if(ch==' ' || ch=='\n' || ch==',')
		{	
			if(word=="MACRO")
			{
				macromode = "ON";
				pflag=0;
			}
			
			else if(Expansionmode == "ON")
			{
				int i;
				for(i=0;i<APTAB[index].size() ; i++)
				{
					if(word == APTAB[index][i])
						break;
				}
				if(i==APTAB[index].size())
					APTAB[index].push_back(word);
					
				if(ch=='\n')
				{
					macroExpansion(file1, index);
					Expansionmode = "OFF";
				}
			}
				
			else if(macromode == "ON")
			{
				if(pflag==0)
				{
					currentMacro = word;
					pflag=1;
				}

				index = macroIndex(currentMacro);
				macromode = process(word, currentMacro, index, ev1);
			}
		
			else 
			{
				Expansionmode = checkMacro(word);	
				if(Expansionmode == "ON")
				{
					currentMacro = word;
					index = macroIndex(currentMacro);
					APTAB[index].clear();
				}
			}
			
			if(macromode == "OFF" && word!="MEND")
			{
				if(word == currentMacro)
					flag2 = 0;
				
				if(flag2==1)
				{
					file1<<word;
					file1<<ch;
				}
				
				if(ch=='\n')
					flag2 = 1;
			}
			word="";
		}
		else
		{
			word+=ch;
		}
		if(ch=='\n')
					*ev1 = 0;
		pch = ch;
		ch=fgetc(fp1);
	}
	
	printAll();	
	
	file1.close();
	return 0;
}
