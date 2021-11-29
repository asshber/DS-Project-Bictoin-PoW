#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include <chrono>
#include<thread>
#include<fstream>
#include"SHA256.h"
using namespace std;
//class Blockchain_Node;
//vector<Blockchain_Node> Blockchain;
//struct Details
//{
//	//string name;
//	//string time;
//	int nonce;
//	Details(int x):nonce(x){}
//};
//stringstream& operator<<(stringstream& dout,Details& obj)
//{
//	//dout << obj.name << obj.time;
//	dout<< obj.nonce;
//	return dout;
//}
int flag = 0;
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
	user(string a,string b,string c)
	{
		name = a;
		data = b;
		hash = c;
	}
};
class Miners
{
private:
	string hash;
	string data;
public:
	Miners(){}
	Miners(string a, string b)
	{
		hash = a;
		data = b;
	}
	 int solve(string puzzle, string data,string MinerName, user& obj)
	 {
		 stringstream s;
		 MinerName += ".txt";
		 string hash;
		 for (int i = INT_MIN; i < INT_MAX; i++)
		 {
			 s << i;
			 s << data;
			 hash = sha256(s.str());
			 if (hash == puzzle)
			 {
				 count2++;
				 if (flag == 0)
				 {
					 flag = i;
					 fout.open(MinerName.c_str(), ios::app);
					 cout << "Done by: " << MinerName << endl;
					 break;
				 }
				 else if (flag != 0 && count2 == 2)
				 {		 
					 return 0;
				 }		 
			 }
			 s.str("");
		 }
	 }
	void mining(user& obj1)
	{
		Miners* obj = new Miners(hash,data);
		std::thread Miner1(&Miners::solve,obj, hash, data, "Miner 1", std::ref(obj1));
		std::thread Miner2(&Miners::solve,obj, hash, data, "Miner 2", std::ref(obj1));
		std::thread Miner3(&Miners::solve,obj, hash, data, "Miner 3", std::ref(obj1));
		cout << endl << endl << endl << endl;
		Miner3.join();
		Miner1.join();
		Miner2.join();
		Miner1.detach();
		Miner2.detach();
		Miner3.detach();
		fout << obj1;
		delete obj;
	}
	
	
};

fstream& operator<<(fstream& fout, user& obj)
{
	fout << obj.data << endl;
	fout << obj.hash << endl;
	fout << obj.name << endl;

	return fout;
}


int main()
{
	string nam, dat;
	cout << "Enter name:" << endl;
	cin >> nam;
	int nonce = -2147483648;
	cout << endl << "Enter data:" << endl;
	cin >> dat;
	stringstream s;
	s << nonce;
	s << dat;
	string hash = sha256(s.str());
	user obj(nam, dat, hash);
	Miners obj2(hash, dat);
	obj2.mining(obj);
}