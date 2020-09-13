#include "Scoreboard.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;
using namespace ed;

void Scoreboard::save(int points, int length)
{
	cout << "\033[32m" << "Enter your name: ";
	string name;
	cin >> name;

	ofstream file(FILE_NAME, std::ios::out | std::ios::app);
	if (!file.is_open())
	{
		cout << "Unable to open scoreboard.txt file, exiting" << "\033[0m" << endl;
		exit(1);
	}
	cout << "\033[0m";
	file << name << "|" << points << "|" << length << endl;
	file.close();
}

void Scoreboard::print()
{
	ifstream file(FILE_NAME, std::ios::in);
	
	vector<pair<int, string>> pointsToNames;
	string line;
	while (getline(file, line))
	{
		int tokenNumber = 0;
		string name;
		string pointsStr;
		for (unsigned int i = 0; i < line.size(); ++i)
		{
			if (line[i] == '|')
			{
				++tokenNumber;
				continue;
			}
			if (tokenNumber == 0)
			{
				name.push_back(line[i]);
			}
			else if (tokenNumber == 1)
			{
				pointsStr.push_back(line[i]);
			}
			else if (tokenNumber == 2)
			{
				int points = stoi(pointsStr);
				pointsToNames.push_back(make_pair(points, name));
				break;
			}
		}
	}

	// algoritmy
	sort(pointsToNames.begin(), pointsToNames.end(), [](const auto& el1, const auto& el2)
	{
		return el1.first > el2.first;
	});

	system("cls");
	for (unsigned int i = 0; i < pointsToNames.size(); ++i)
	{
		cout << "\033[32m" << i + 1 << ". " << pointsToNames[i].second << ": " << pointsToNames[i].first << endl;
	}
	system("pause");
	cout << "\033[0m";
}