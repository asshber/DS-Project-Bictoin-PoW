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
	void set(string a, string b) {
		data = b;
		Wallet_ID = a;
		hash = sha256(data);
	}
	
};

fstream& operator>>(fstream& fin, B_Node& obj);//for reading from file
fstream& operator<<(fstream& fout, B_Node& obj)//for writing in file
{
	fout << obj.Wallet_ID << endl;
	fout << obj.hash << endl;
	fout << obj.data << endl << endl;
	return fout;
}
class MinerCommunity//Miners are in this community
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
	void set(string d)
	{
		data = d;
		puzzle = "";
		count = 0;
	}
	void solve(string data, string MinerName)//Miner will solve through this algorithm
	{
		stringstream s;
		int r = mkdir(MinerName.c_str());
		stringstream path;
		path << "./" << MinerName << "/" << MinerName << ".txt";
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
					fout.open(path.str(), ios::app);
					cout << "Done by: " << MinerName << endl;
					count++;
					
					break;
				}
					count++;
					
			}
			s.str("");
		}
	}
	void pool_mining(B_Node& obj1)//it will pass random puzzle to miners
	{
		stringstream s;
		srand(time(0));
		int nonce = rand() % 10000;
		s << nonce;
		s << data;
		puzzle = sha256(s.str());
		mining(obj1);
	}
	void mining(B_Node& obj1)//Miners are in this function
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
		fout.close();
	}
};
int main()//main
{
	string id, data;
	ifstream file("input.txt");
	json j;
	B_Node obj;
	MinerCommunity object;
	while (!file.eof())
	{
		file >> j;
		data = j["data"];
		id = j["ID"];
		obj.set(id, data);
		object.set(data);
		object.pool_mining(obj);
		if (file.peek() == EOF)
			break;
	}
	
}
//blockchain POW