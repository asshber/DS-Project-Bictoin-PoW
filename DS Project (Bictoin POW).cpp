#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include <chrono>
#include<thread>
#include<fstream>
#include"SHA256.h"
#include"json.hpp"
using namespace std;
fstream fout;
class B_Node //A node for blockchain data structutrre.
{
public:
	string data;
	string hash;
	B_Node()
	{}
	B_Node(string b):data(b)
	{
		hash = sha256(data);
	}
};
fstream& operator<<(fstream& fout, B_Node& obj)
{
	fout << obj.hash << endl;
	fout << obj.data << endl;
	return fout;
}
class MinerCommunity
{
private:
	string puzzle;
	string data;
	int count2;
public:
	MinerCommunity()
	{
		puzzle = "";
		data = "";
		count2 = 0;
	}
	MinerCommunity(string b)
	{
		puzzle = "";
		data = b;
		count2 = 0;
	}
	 void solve(string data,string MinerName)
	 {
		 stringstream s;
		 MinerName += ".txt";
		 string b_hash;
		 for (int i = 0; i < 10000; i++)
		 {
			 s << i;
			 s << data;
			 b_hash = sha256(s.str());
			 if (b_hash == puzzle)
			 {
				 if (count2 == 0)
				 {
					 fout.open(MinerName.c_str(), ios::app);
				     cout << "Done by: " << MinerName << endl;
					 count2++;
					 break;
				 }	
				 count2++;
			 }
			 s.str("");
		 }
	 }
	 void pool_mining(B_Node& obj1)
	 {
		 srand(100);
		 int x = rand();
		 x %= 3;
		 stringstream s;
		 if (x == 0)
		 {
			 s << 2000;
			 s << data;
			 puzzle = sha256(s.str());
		 }
		 else if (x == 1)
		 {
			 s << 4000;
			 s << data;
			 puzzle = sha256(s.str());
		 }
		 else if (x == 2)
		 {
			 s << 8000;
			 s << data;
			 puzzle = sha256(s.str());
		 }
		 mining(obj1);
	 }
	void mining(B_Node& obj1)
	{
		
		std::thread Miner1(&MinerCommunity::solve,this, data, "Miner 1");
		std::thread Miner2(&MinerCommunity::solve,this, data, "Miner 2");
		std::thread Miner3(&MinerCommunity::solve,this, data, "Miner 3");
		cout << endl << endl << endl << endl;
		Miner3.join();
		Miner1.join();
		Miner2.join();
		if (count2 >= 2)
			fout << obj1;
		else
			cout << "Majority didnt verify the puzzle" << endl;
	}
};
int main()
{
	string nam, dat;
	cout << endl << "Enter data:" << endl;
	getline(cin, dat);
	stringstream s;
	B_Node obj(dat);
	MinerCommunity object(dat);
	object.pool_mining(obj);
}