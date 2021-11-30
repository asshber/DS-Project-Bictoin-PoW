#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include <chrono>
#include<thread>
#include<fstream>
#include"SHA256.h"
using namespace std;
fstream fout;
class user
{
public:
	string name;
	string data;
	string hash;
	user()
	{}
	user(string a,string b,string c):name(a),data(b)
	{
		hash = sha256(data);
	}
};
fstream& operator<<(fstream& fout, user& obj)
{
	fout << obj.name << endl;
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
	MinerCommunity(string a, string b)
	{
		puzzle = a;
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
	void mining(user& obj1)
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
	cout << "Enter name:" << endl;
	getline(cin, nam);
	int nonce = 5550;
	cout << endl << "Enter data:" << endl;
	getline(cin, dat);
	stringstream s;
	s << nonce;
	s << dat;
	string puzzle = sha256(s.str());
	user obj(nam, dat, puzzle);
	MinerCommunity object(puzzle, dat);
	object.mining(obj);
}