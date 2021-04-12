#include <iostream>
#include <string.h>
#include <fstream>

char w[2000002];
char s[2000002];
int match [2000002], sl, wl;

using namespace std;
void kmp_match()	//original, DFA, de pe infoarena
{
    match [0] = 0;
    int j = 0;
    for (int i = 1; i < wl; i++)
    {
        while (j > 0 && (w[j] != w[i]))
            j = match[j-1];
        if (w[j] == w[i])
            j++;
        match[i] = j;
    }
}

void kmp_match2()	//pseudocodu din curs, OFC NU MERGE
{
	int j = 0;
	int k = -1;
	match[0]= -1;
	while(j < wl - 1)
	{
		while((k >= 0) && (w[j] != w[k]))
		{
			k = match[k];
			j = j + 1;
			k = k + 1;

		if(w[j] = w[k])
			match[j] == match[k];
		else
			match[j] = k;
		}
	}
}

void kmp_match3()	//wikipedia
{
	int i;
	int j = 0;

	match[0]= -1;

	for(i = 1; i < wl; ++i)
	{
		if(w[i] == w[j])
			match[i] = match[j];
		else
		{
			match[i] = j;
			j = match[j];
			while(j >= 0 && w[i] != w[j])
				j = match[j];
		}
		j = j + 1;
	}

	match[i] = j;
}

int main (int argc, char * argv[])
{
    cout<<"KMP solver for DSA lab by avlad171\n";
	if(argc < 2)
	{
		cout<<"Enter some text:";
		cin>>s;
	}
	else
	{
		ifstream in(argv[1]);
		if(!in.is_open())
		{
			cout<<"Unable to open file!\n";
			return -1;
		}
		in>>s;
	}

	cout<<"Enter pattern (to be searched):";
	cin>>w;

    wl = strlen (w);
    sl = strlen (s);

	if(sl > 200000 || wl > 200000)
	{
		cout<<"Error - string too long!\n";
		exit(-1);
	}

	//calculam tabela
    kmp_match3();

	//afisam tabela
	cout<<"\nKMP shift table:\n";
	for(int i = 0; i < wl; ++i)
		cout<<i - match[i]<<" ";
	cout<<"\n";

	//cod din curs, asta mere
	int i = 0;
	int j = 0;
	while((j < wl) && (i < sl))
	{
		cout<<i<<"\n";
		while((j >= 0) && (s[i] != w[j]))
		{
			cout<<"Shifting with "<<j - match[j]<<"\n";
			j = match[j];
		}
		j = j + 1;
		i = i + 1;
	}
    if(j == wl)
		cout<<"Match at "<<i - wl<<"\n";

	return 0;
}
