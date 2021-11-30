#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include <chrono>
#include<thread>
#include<fstream>
#include <direct.h>
#include"SHA256.h"
#include"json.hpp"
using json = nlohmann::json;
using namespace std;
fstream fout;
class B_Node //A node for blockchain data structutrre.
{
public:
	string Wallet_ID;
	string data;
	string hash;
	B_Node()
	{}
	B_Node(string a,string b):Wallet_ID(a),data(b)
	{
		hash = sha256(data);
	}
};
json& operator>>(json& fin, B_Node& obj)
{
	obj.data = fin["data"];
	obj.Wallet_ID = fin["ID"];
	obj.hash = sha256(obj.data);
	return fin;
}
fstream& operator>>(fstream& fin, B_Node& obj);
fstream& operator<<(fstream& fout, B_Node& obj)
{
	fout << obj.Wallet_ID << endl;
	fout << obj.hash << endl;
	fout << obj.data << endl << endl;
	return fout;
}
class MinerCommunity
{
private:
	string puzzle;
	string data;
	int count;
	int first_nonce;
public:
	MinerCommunity()
	{
		puzzle = "";
		data = "";
		count = 0;
	}
	MinerCommunity(string b)
	{
		puzzle = "";
		data = b;
		count = 0;
	}
	void solve(string data, string MinerName)
	{
		stringstream s;
		int r = mkdir(MinerName.c_str());
		string path = "./";
		path += MinerName;
		path += "/";
		path += MinerName;
		path += ".txt";
		string b_hash;
		for (int i = 0; i < 10000; i++)
		{
			s << i;
			s << data;
			b_hash = sha256(s.str());
			if (b_hash == puzzle)
			{
				const auto sleep_time = std::chrono::milliseconds(200);
				if (count == 0)
				{
					fout.open(path.c_str(), ios::app);
					cout << "Done by: " << MinerName << endl;
					count++;
					std::this_thread::sleep_for(sleep_time);
					break;
				}
					count++;
				std::this_thread::sleep_for(sleep_time);
			}
			s.str("");
		}
	}
	void pool_mining(B_Node& obj1)
	{
		stringstream s;
		srand(time(0));
		int nonce = rand() % 10000;
		s << nonce;
		s << data;
		puzzle = sha256(s.str());
		mining(obj1);
	}
	void mining(B_Node& obj1)
	{
		std::thread Miner1(&MinerCommunity::solve, this, data, "Miner 1");
		std::thread Miner2(&MinerCommunity::solve, this, data, "Miner 2");
		std::thread Miner3(&MinerCommunity::solve, this, data, "Miner 3");
		cout << endl << endl << endl << endl;
		Miner3.join();
		Miner1.join();
		Miner2.join();
		if (count >= 2)
			fout << obj1;
		else
			cout << "Majority didnt verify the puzzle" << endl;
	}
};
int main()
{
	//ifstream file("input.json");
	//json j;
	//file >> j;
	//int i = 2;
	//B_Node obj();
	//while (i)
	//{
	//	j >> obj;
	//	MinerCommunity object(obj.data);
	//	object.pool_mining(obj);
	//	i--;
	//}
	ifstream file("input.json");
	json j;
	file >> j;
	string dat = j["data"];
	string id = j["ID"];
	B_Node obj(id,dat);
	MinerCommunity object(dat);
	object.pool_mining(obj);
}