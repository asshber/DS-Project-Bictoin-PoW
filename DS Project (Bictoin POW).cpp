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
static int count2 = 0;
class user
{
public:
	string name;
	string data;
	string hash;
	user()
	{}
	user(string a,string b,string c):name(a),data(b),hash(c)
	{}
};
fstream& operator<<(fstream& fout, user& obj)
{
	fout << obj.data << endl;
	fout << obj.hash << endl;
	fout << obj.name << endl;
	return fout;
}
class MinerCommunity
{
private:
	string hash;
	string data;
public:
	MinerCommunity(){}
	MinerCommunity(string a, string b)
	{
		hash = a;
		data = b;
	}
	 void solve(string puzzle, string data,string MinerName)
	 {
		 stringstream s;
		 MinerName += ".txt";
		 string hash;
		 for (int i = 0; i < 10000; i++)
		 {
			 s << i;
			 s << data;
			 hash = sha256(s.str());
			 if (hash == puzzle)
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
		MinerCommunity* obj = new MinerCommunity(hash,data);
		std::thread Miner1(&MinerCommunity::solve,obj, hash, data, "Miner 1");
		std::thread Miner2(&MinerCommunity::solve,obj, hash, data, "Miner 2");
		std::thread Miner3(&MinerCommunity::solve,obj, hash, data, "Miner 3");
		cout << endl << endl << endl << endl;
		Miner3.join();
		Miner1.join();
		Miner2.join();
		if(count2>=2)
			fout << obj1;
		delete obj;
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
	string hash = sha256(s.str());
	user obj(nam, dat, hash);
	MinerCommunity obj2(hash, dat);
	obj2.mining(obj);
}