#include <iostream>
#include <string.h>
#include <fstream>


char w[2000002];
char s[2000002];

int letter_used[257];
int d [257], sl, wl;

using namespace std;

int main (int argc, char * argv[])
{
    cout<<"Booyer-moore solver for DSA lab by avlad171\n";
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

	for(int i = 0; i < sl; ++i)
		letter_used[s[i]] = 1;
	for(int i = 0; i <= 255; ++i)
		d[i] = wl; 				//initialize d table

	for(int j = 0; j < wl - 1; ++j)
	{
		d[w[j]] = wl - j - 1;	//pattern precompiling
		//cout<<"j = "<<j<<", w[j] = "<<w[j]<<", d[w[j]] = "<<d[w[j]]<<"\n";
	}

	cout<<"D table:\n";
	for(int j = 0; j < 256; ++j)
		if(letter_used[j])
			cout<<"T["<<(unsigned char)j<<"] = "<<d[j]<<"\n";
	cout<<"Any other table entry is "<<wl<<"\n\n";

	int i = wl, j = wl; //pattern search
	while ((j > 0) && (i <= sl))
	{
		j = wl;
        int k = i;
        while ((j > 0) && (s[k - 1] == w[j - 1]))
		{
			k = k-1;
			j = j-1;
		}

		//cout<<"i = "<<i<<", j = "<<j<<", s[i - 1] = "<<s[i - i]<<", d[s[i - 1] = "<<d[s[i-1]]<<"\n";
		if (j > 0)
		{
			cout<<"Shifting by "<<d[s[i - 1]]<<"\n";
			i = i + d[s[i - 1]];
		}
	}

	if(j == 0)
		cout<<"Match at "<<i - wl<<"\n";

	return 0;
}
