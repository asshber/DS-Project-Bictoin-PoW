#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include"SHA256.h"
using namespace std;
class Blockchain_Node;
vector<Blockchain_Node> Blockchain;
class Blockchain_Node
{
	string p_hash;
	string data;
	string hash;
public:
	Blockchain_Node(string x):data(x)
	{
		stringstream s;
		p_hash = getlasthash();
		s << data << p_hash;
		hash = sha256(s.str());
		p_hash = getlasthash();
	}
	string getlasthash()
	{
		Blockchain_Node p = Blockchain.back();
		return (p.hash);
	}
};

int main()
{
	
}