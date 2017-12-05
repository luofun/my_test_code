#include <iostream>
#include <string>
#include <istream>
#include <map>

using namespace std;

char table[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',\
				'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',\
				'0','1','2','3','4','5','6','7','8','9',\
				'+' , '// '\
};

map<char, int> mmm;

int main(){
	string input, base64encode, base64decode;
	for (int i = 0; i < 64; i++)
		mmm[table[i]] = i;
	cout << "put your input: ";
	getline(cin, input);
	string isubstr = input;
	int flagnow = 0;
	//encode
	while (isubstr.length() >= 3)
	{
		base64encode.push_back(table[(isubstr[0] >> 2)]);
		base64encode.push_back(table[((isubstr[0] & 0x3) << 4) + (isubstr[1] >> 4)]);
		base64encode.push_back(table[((isubstr[1] & 0xf) << 2) + (isubstr[2] >> 6)]);
		base64encode.push_back(table[isubstr[2] & 0x3f]);
		flagnow += 3;
		isubstr = input.substr(flagnow);
	}
	if (isubstr.length() != 0)
	{
		int tail = 0;
		for (int i = isubstr.length(); i < 3; ++i)
		{
			isubstr += '\0';
			++tail;
		}
		base64encode.push_back(table[(isubstr[0] >> 2)]);
		base64encode.push_back(table[((isubstr[0] & 0x3) << 4) + (isubstr[1] >> 4)]);
		base64encode.push_back(table[((isubstr[1] & 0xf) << 2) + (isubstr[2] >> 6)]);
		base64encode.push_back(table[isubstr[2] & 0x3f]);
		for (int i = 0; i < tail; i++)
			base64encode.pop_back();
		for (int i = 0; i < tail; i++)
			base64encode.push_back('=');
	}
	//decode
	if (input.length() % 4 != 0)
		cout << "no the right length for decode\n";
	flagnow = 0;
	isubstr = input;
	while (isubstr.length() >= 4)
	{
		base64decode.push_back(((mmm[isubstr[0]] & 0x3f) << 2) + ((mmm[isubstr[1]] & 0x30) >> 4));
		base64decode.push_back(((mmm[isubstr[1]] & 0xf) << 4) + ((mmm[isubstr[2]] & 0x3c) >> 2)); 
		base64decode.push_back(((mmm[isubstr[2]] & 0x3) << 6) + (mmm[isubstr[3]] & 0x3f));
		if (isubstr[2] == '=')
		{
			base64decode.pop_back();
			base64decode.pop_back();
			break;
		}
		if (isubstr[3] == '=')
		{
			base64decode.pop_back();
			break;
		}
		flagnow += 4;
		isubstr = input.substr(flagnow);
	}

	cout << "base64encode: " << base64encode << endl;
	cout << "base64decode: " << base64decode << endl;
	return 0;
}