#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include <chrono>
#include"SHA256.h"
using namespace std;
//class Blockchain_Node;
//vector<Blockchain_Node> Blockchain;
struct Details
{
	//string name;
	//string time;
	int nonce;
	Details(int x):nonce(x){}
};
stringstream& operator<<(stringstream& dout,Details& obj)
{
	//dout << obj.name << obj.time;
	dout<< obj.nonce;
	return dout;
}
class Miner
{
	string name;
	int count;
public:
	void solve(string puzzle,string data)
	{
		stringstream s;
		string hash;
		for (int i = 0; i < 10000; i++)
		{
			s << i;
			s << data;
			hash = sha256(s.str());
			if (hash == puzzle)
			{
				cout << "pp";
				break;
			}
			s.str("");
		}
	}
};
//class Blockchain_Node
//{
//	string p_hash;
//	Details data;
//	string hash;
//public:
//	Blockchain_Node()
//	{
//		stringstream s;
//		p_hash = getlasthash();
//		s << data<<p_hash;
//		hash = sha256(s.str());
//		p_hash = getlasthash();
//		Blockchain.push_back(*this);
//	}
//	string getlasthash()
//	{
//		Blockchain_Node p = Blockchain.back();
//		return (p.hash);
//	}
//};

int main()
{
	stringstream s;
	s << 2;
	s << "hello";
	string hash = sha256(s.str());
	Miner obj;
	obj.solve(hash, "hello");
}