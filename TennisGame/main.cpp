#include <string>
#include <utility>
#include <vector>
#include <iostream>
using namespace std;

class Game {
	friend ostream& operator<<(ostream& os, const Game& rhs);
	class Player {
	public:
		Player(const string& name, vector<pair<string, float>>& bet) : name(name), bet(bet) {}
		const string& getName() const { return name; }
		float getRate(const string& athletheName) const {
			for (const pair<string, float>& eachBet : bet) {
				if (eachBet.first == athletheName) {
					return eachBet.second;
				}
			}return 0; //If the player didn't bet for the qualified athlete, they will not get any points
		}
	private:
		string name;
		vector<pair<string, float>> bet;
	};
public:
	bool addPlayer(const string& name, vector<pair<string, float>> bet) { //I did get an error, I can not pass it by reference
		if (!playerSearch(name)) {
			players.push_back({ Player(name,bet), 0 }); return true;
		}return false;
	}
	void updateRound(int magnitutude, vector<string> qualifiedAthletes) {
		for (const string& athleteName : qualifiedAthletes) {
			for (pair<Player, float>& player : players) {
				player.second += magnitutude * player.first.getRate(athleteName); 
			}
		}mySort();
	}
private:
	vector<pair<Player, float>> players;

	bool playerSearch(const string& name) { // I don't want any two players to have the same name
		for (const pair<Player, float>& p : players) {
			if (p.first.getName() == name) return true;
		}return false;
	}
	void swap(size_t i) { //I can change it to while loop //Which is a more optimized way for this situation // I just did it recursively to practice my recursion skills
		if (i >= 1 && players[i].second > players[i - 1].second) {
			pair<Player, float> temp = players[i-1];
			players[i - 1] = players[i];
			players[i] = temp;
			swap(--i);
		}
	}
	void mySort() {
		for (size_t i = 1; i < players.size(); ++i) {
			if (players[i].second > players[i - 1].second) swap(i); //Descending order
		}
	}
};

ostream& operator<<(ostream& os, const Game& rhs) {
	int counter = 1;
	for (const pair<Game::Player, float>& player : rhs.players) {
		os << counter << "- "; ++counter;
		os << "Player's name: " << player.first.getName() << " || ";
		os << "Current Score: " << player.second << endl;
	}return os;
}

void merge(vector<int>& v, size_t leftLow, size_t leftHigh, size_t rightLow, size_t rightHigh) {
	cout << leftLow << " " << leftHigh << " " << rightLow << " " << rightHigh << endl;
	while (leftLow < rightLow && rightLow < rightHigh) {
		if (v[leftLow] <= v[rightLow]) ++leftLow;
		else {
			int temp = v[rightLow];
			size_t cursor = rightLow;
			while (cursor > leftLow) { v[cursor] = v[cursor - 1]; --cursor; }
			v[leftLow] = temp;
			++leftLow, ++rightLow;
		}
	}
}

pair<int, int> mergeSort(vector<int>& v, size_t low, size_t high) {
	if (low < high) {
		pair<size_t, size_t> left = mergeSort(v, 0, (high+low) / 2);
		pair<size_t, size_t> right = mergeSort(v, ((high + low) / 2) + 1, high);
		merge(v, left.first, left.second, right.first, right.second);
		cout << "Hello" << endl;
	}
	pair<size_t, size_t> pos = { low, high };
	return pos;
}


void printVector(const vector<int>& v) {
	for (int val : v) cout << val << ' ';
	cout << endl;
}

int main() {
	Game tennisGame;
	tennisGame.addPlayer("Senol", { {"Djokovic", .3}, {"Alcaraz", .2}, {"Ruud", .25}, {"Medvedev", .25} });
	tennisGame.addPlayer("Selim", { { "Nadal", .35 }, { "Alcaraz", .15 }, { "Medvedev", .3 }, { "Tsitsipas", .2 } });
	tennisGame.addPlayer("Murat", { {"Alcaraz", .359375}, {"Nadal", .359375}, {"Tsitsipas", .171875}, {"Medvedev", .046875},
		{"Sinner", .015625}, {"Ruud", .015625}, {"Djokovic", .015625}, {"Zverev", .015625} });
	tennisGame.updateRound(2, { "Djokovic", "Nadal", "Zverev", "Alcaraz", "Ruud", "Rune", "Rublev", "Cilic" });
	tennisGame.updateRound(4, {  "Nadal", "Zverev", "Ruud", "Cilic" });
	tennisGame.updateRound(8, { "Nadal",  "Ruud" });
	tennisGame.updateRound(16, { "Nadal" });
	cout << tennisGame;
	vector<int> v { 1, 3, 4, 2 };
	mergeSort(v, 0, v.size()-1);
	printVector(v);
}