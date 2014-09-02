#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <valarray>
#include <iomanip>
#include <vector>
#include <map>
#include <fstream>
#include <bitset>
#include <set>


using namespace std;

int main(int argc, char **argv)
{
	map<string, bitset<10>> et;

	unsigned lineNumber;
	string line;
	char opcode[20];
	char argument[20];
	fstream i;
	fstream o;
	i.open("in.txt", ios::in);
	o.open("out.txt", ios::out | ios::trunc);

	lineNumber = 0;

	cout << "MyCPU Compiler v3" << endl;
	cout << "Faza 1: etykiety -> adresy skoku" << endl;
	while (std::getline(i, line))
	{
		strcpy(opcode, "\0");
		strcpy(argument, "\0");
		sscanf(line.c_str(), "%s %s", &opcode, &argument);

		if (strcmp("mva", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("mvb", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("load", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("store", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("xchg", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("jmp", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("jz", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("jc", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("jnz", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("jnc", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("nop", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("and", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("or", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("not", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("add", opcode) == 0)
		{
			++lineNumber;
		}
		if (strcmp("sub", opcode) == 0)
		{
			++lineNumber;
		}

		switch (opcode[0])
		{
		case '.':
			et[opcode] = lineNumber;
		}
	}


	i.clear();
	i.seekg(0, ios::beg);
	lineNumber = 0;

	cout << "Faza 2: Konwersja mnemonikow" << endl;
	while (std::getline(i, line))
	{
		strcpy(opcode, "\0");
		strcpy(argument, "\0");
		sscanf(line.c_str(), "%s %s", &opcode, &argument);

		std::bitset<8> binarg(atoi(argument));
		std::bitset<10> binaddr(atoi(argument));

		if (strcmp("nop", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b0000_0000000000";
			o << "; //nop" << endl;
			++lineNumber;
		}
		if (strcmp("mva", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b1010_00_";
			o << binarg;
			o << "; //mva " << argument << endl;
			++lineNumber;
		}
		if (strcmp("mvb", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b0001_00_";
			o << binarg;
			o << "; //mvb " << argument << endl;
			++lineNumber;
		}
		if (strcmp("load", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b0010_";
			o << binaddr;
			o << "; //load " << argument << endl;
			++lineNumber;
		}
		if (strcmp("store", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b0011_";
			o << binaddr;
			o << "; //store " << argument << endl;
			++lineNumber;
		}
		if (strcmp("xchg", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b0100_0000000000";
			o << "; //xchg" << endl;
			++lineNumber;
		}
		if (strcmp("jmp", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b0101_";
			o << et[argument];
			o << "; //jmp " << argument << endl;
			++lineNumber;
		}
		if (strcmp("jz", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b0110_";
			o << et[argument];
			o << "; //jz " << argument << endl;
			++lineNumber;
		}
		if (strcmp("jc", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b0111_";
			o << et[argument];
			o << "; //jc " << argument << endl;
			++lineNumber;
		}
		if (strcmp("jnz", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b1000_";
			o << et[argument];
			o << "; //jnz " << argument << endl;
			++lineNumber;
		}
		if (strcmp("jnc", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b1001_";
			o << et[argument];
			o << "; //jnc " << argument << endl;
			++lineNumber;
		}
		if (strcmp("and", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b1011_0000000000";
			o << "; //and" << endl;
			++lineNumber;
		}
		if (strcmp("or", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b1100_0000000000";
			o << "; //or" << endl;
			++lineNumber;
		}
		if (strcmp("not", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b1101_0000000000";
			o << "; //not" << endl;
			++lineNumber;
		}
		if (strcmp("add", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b1110_0000000000";
			o << "; //add" << endl;
			++lineNumber;
		}
		if (strcmp("sub", opcode) == 0)
		{
			o << "ROM[" << lineNumber << "] = 14'b1111_0000000000";
			o << "; //sub" << endl;
			++lineNumber;
		}
		switch (opcode[0])
		{
		case '.':
			o << "// " << opcode << endl;
		}

	}




	o << endl;

	cout << lineNumber << " lines parsed" << endl;

	i.close();
	o.close();

	return 0;
}

