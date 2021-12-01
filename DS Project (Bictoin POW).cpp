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
	string Block_ID;
	string data;
	string hash;
	B_Node()
	{}
	B_Node(string a,string b):Block_ID(a),data(b)
	{
		hash = sha256(data);
	}
	void set(string a, string b) {
		data = b;
		Block_ID = a;
		hash = sha256(data);
	}
	
};

fstream& operator>>(fstream& fin, B_Node& obj)//for reading from file
{
	getline(fin, obj.Block_ID);
	getline(fin, obj.hash);
	getline(fin, obj.data);
	return fin;
}
fstream& operator<<(fstream& fout, B_Node& obj)//for writing in file
{
	fout << obj.Block_ID << endl;
	fout << obj.hash << endl;
	fout << obj.data << endl;
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
	int reward_count(string MinerName)
	{
		stringstream path;
		int rewardcount = 0;
		path << "./" << MinerName << "/" << MinerName << ".txt";
		fstream file(path.str(), ios::in);
		B_Node obj;
		while (file >> obj)
		{
			rewardcount++;
		}
		return rewardcount;

	}
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
			if (count >= 3)
				break;
			s << i;
			s << data;
			b_hash = sha256(s.str());
			if (b_hash == puzzle)
			{
				if (count == 0)
				{
					count++;
					fout.open(path.str(), ios::app);
					cout << "Done by: " << MinerName << endl;
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
		std::thread Miner4(&MinerCommunity::solve, this, data, "Miner 4");
		std::thread Miner5(&MinerCommunity::solve, this, data, "Miner 5");
		cout << endl << endl << endl << endl;
		Miner3.join();
		Miner1.join();
		Miner2.join();
		Miner4.join();
		Miner5.join();
		if (count >= 3)
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
	cout << "Rewrad count for Miner 1 is : " << object.reward_count("Miner 1")<<endl;
	cout << "Rewrad count for Miner 2 is : " << object.reward_count("Miner 2") << endl;
	cout << "Rewrad count for Miner 3 is : " << object.reward_count("Miner 3") << endl;
}
//blockchain POW