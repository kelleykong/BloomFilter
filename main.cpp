#include "bloom filter.h"
#include <fstream>
using namespace std;

int main()
{
	ifstream in("DIC.TXT");
	if (!in)
		cout << "Can't Find DIC" << endl;
	int n;
	in>>n;
	char *str;
	str = new char[256];

	BloomFilter BF(2*n);

	for(int i = 0; i < n;i++)
	{
		in>>str;
//		cout<<str<<endl;
		BF.add((void *)str);
	}

	while(strcmp(str, ";") != 0)
	{	
		cout<<"please give the word you want to check"<<endl;	
		cin>>str;
		BF.query((void *)str);
	}

	return 0;
}