#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

struct guitar_brand {
	string name;
	int year_of_foundation;
};

bool operator==(const guitar_brand& a, const guitar_brand& b) {
	return a.name == b.name && a.year_of_foundation == b.year_of_foundation;
}

struct hash_table {
	size_t capacity;
	vector < vector < guitar_brand >> table;

	long hash_function(string key);
	void add(guitar_brand x);
	bool remove(guitar_brand x);
	bool find_item(guitar_brand x);
	void print();

	hash_table(size_t n) {
		this->capacity = n;
		table.resize(capacity);
	}

};

long hash_table::hash_function(string key){
	long sum = 0;
	for (int i = 0; i < key.length(); ++i) {
		sum += key[i] * (i + 1);
	}
	return sum%capacity;
}

void hash_table::add(guitar_brand x) {
	long hash_value = hash_function(x.name);
	if (!find_item(x)) table[hash_value].push_back(x);
	else cout << "ITEM ALREADY IN THE TABLE"<<endl;
}

bool hash_table::remove(guitar_brand x) {
	long hash_value = hash_function(x.name);
	if (find_item(x)) {
		auto i = find(table[hash_value].begin(), table[hash_value].end(), x);
		table[hash_value].erase(i);
		cout << "DELETED SUCCESFULLY"<<endl;
		return true;
	}
	else {
		cout << "FAILED TO DELETE" << endl;;
		return false;
	}
}

bool hash_table::find_item(guitar_brand x){
	long hash_value = hash_function(x.name);
	if (table[hash_value].size() == 0) return false;
	else {
		bool f = false;
		for (guitar_brand i : table[hash_value]) {
			if (i == x) {
				f = true;
				return f;
			}
		}
		return f;
	}
}

void hash_table::print() {
	for (int i = 0; i < capacity; i++) {
		cout << i;
		for (guitar_brand x : table[i]) {
			cout << " --> " << x.name << ": " << x.year_of_foundation;
		}
		cout << endl;
	}
}

int main(){
	guitar_brand ibanez, fender, gibson, jackson, schecter, esp, prs, x;
	ibanez.name = "Ibanez Guitars";
	ibanez.year_of_foundation = 1935;
	fender.name = "Fender Musical Instruments Corporation";
	fender.year_of_foundation = 1946;
	gibson.name = "Gibson Guitar Corporation";
	gibson.year_of_foundation = 1902;
	jackson.name = "Jackson Guitars";
	jackson.year_of_foundation = 1980;
	schecter.name = "Schecter Guitar Research";
	schecter.year_of_foundation = 1976;
	esp.name = "ESP Guitar Company";
	esp.year_of_foundation = 1975;
	prs.name = "PRS Guitars";
	prs.year_of_foundation = 1985;
	x.name = "x";
	x.year_of_foundation = 1;

	vector <guitar_brand> a = { ibanez, fender, gibson, jackson, schecter, esp, prs };
	hash_table h(5);
	for (guitar_brand i : a) {
		h.add(i);
	}
	h.print();
	h.remove(ibanez);
	h.find_item(ibanez);
	h.remove(x);
	h.add(fender);
	h.print();
}