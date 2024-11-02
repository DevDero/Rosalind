#include <iostream>
#include <string>
#include <bits.h>
#include <vector>

using namespace std;

const string fastaMessage = "Enter your sequence in FASTA format,place 'end' at the end:";


class Sequence {
public:
	string ID;
	string DNAsequence;
	int lenght = 0;
	int AT = 0, GC = 0;
	double GCContent = 0;

	double GetGCContent() {
		GCContent= (static_cast<double>(GC) / lenght)*100;
		return GCContent;
	}
};
class FastaUtil {
public:
	void Receive() {
		cout << fastaMessage;
		string line;
		string input;
		while (getline(cin, line))
		{
			input += line;
			if (line == "end") {
				break;
			}
		}
		TraverseSequences(input);
	}
private:
	vector<Sequence> SequenceVector;

	bool isDNA(char& ch) {
		switch (ch)
		{
		case 'A':case 'T':case 'G':case 'C':
			return true;
		default:
			return false;
			break;
		}
	}
	void TraverseSequences(string &input){
		string::iterator it;
		Sequence* currentSequence;
		Sequence* highestCG = new Sequence();

		for (it = input.begin(); it !=input.end();)
		{
			if (*it == 'e')
				break;
			if (*it == '>') {
				currentSequence = new Sequence();
				while (!isDNA(*it)){
					currentSequence->ID += *it;
					it++;
				}
				while (isDNA(*it)) {
					currentSequence->DNAsequence += *it;
					currentSequence->lenght++;
					GCCounter(*it, currentSequence->AT, currentSequence->GC);
					it++;
				}
				currentSequence->GetGCContent();
				if (currentSequence->GCContent > highestCG->GCContent)
					highestCG = currentSequence;
			}
		}
		cout<<std::cout.precision(8)<<highestCG->ID<<' ' << highestCG->GetGCContent();
	}
	void GCCounter(char& base,int &_AT,int &_GC) {
		if (base == 'G' || base == 'C')
			_GC++;
		else
			_AT++;
	}
	
};
