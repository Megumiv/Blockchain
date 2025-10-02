<<<<<<< HEAD
﻿#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cstdint>    // leidzia naudoti uint64_t

using namespace std;

string tekstas;
string choice;
string input;

// MENIU
void meniu()
{
	cout << "\n\nMeniu: \n";
	cout << "1 - Rankiniu budu ivesti teksta\n";
	cout << "2 - Pasirinkti nuskaitoma faila\n";
	cout << "3 - Sugeneruoti testini faila\n";
	cout << "4 - Baigti darba\n";
	cout << "Pasirinkite (1, 2, 3, 4): ";
	cin >> choice;
}

// Failu meniu
string meniuFailai() {
	int nus = 0;
	string filename;

	while (true) {
		cout << "\nPasirinkite koki faila nuskaitysite:\n"
			<< "1 - empty.txt\n"
			<< "2 - test1.txt\n"
			<< "3 - test2.txt\n"
			<< "4 - pats ivesiu pavadinima.\n";
		cin >> nus;

		if (nus == 1) return "empty.txt";
		if (nus == 2) return "test1.txt";
		if (nus == 3) return "test2.txt";
		if (nus == 4) {
			cin >> filename;
			return filename;
		}
		cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
	}
}

// Meniu pasirinkimui koki faila generuoti
int meniuGeneravimas() {
	int g;
	cout << "\nPasirinkite generavimo buda:\n";
	cout << "1 - visiškai atsitiktiniai simboliai (1000 po 1000)\n";
	cout << "2 - atsitiktiniai simboliai (1000 po 1000), kurie vienas nuo kito skiriasi tik 1 simboliu\n";
	cout << "Pasirinkimas: ";
	cin >> g;
	return g;
}


// DUOMENU GENERAVIMAS
const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{};:,.<>?/";
string Generavimas(int ilgis, mt19937& gen) {
	uniform_int_distribution<int> dist(0, charset.size() - 1);
	string eil;
	for (int i = 0; i < ilgis; ++i)
		eil += charset[dist(gen)];
	return eil;
}

// Sugeneruoja i failus pagal pasirinkima 
void Sugeneruota(mt19937& gen, int g) {
	string failas = (g == 1 ? "test1.txt" : "test2.txt");
	ofstream fd(failas);
	if (!fd.is_open()) {
		cerr << "Nepavyko atidaryti failo.\n";
		return;
	}

	if (g == 1) {// Pilnai atsitiktiniai simboliai 

		for (int i = 0; i < 5; i++) {
			string eilute = Generavimas(1000, gen);
			fd << eilute << '\n';
		}
	}
	else if (g == 2) { // Atsitiktiniai simboliai, kurie vienas nuo kito skiriasi tik 1 simboliu

		// Pirmoji eilute
		string eilute = Generavimas(1000, gen);
		fd << eilute << '\n';

		uniform_int_distribution<int> pozicija(0, 999);
		for (int i = 1; i < 5; i++) {
			string naujas = eilute;
			int idx = pozicija(gen); // atsitiktinis indeksas

			// Pakeiciamas vienas simbolis
			char simbolis;
			do {
				uniform_int_distribution<int> dist(0, charset.size() - 1);
				simbolis = charset[dist(gen)];
			} while (simbolis == naujas[idx]); // uztikrinama, kad simbolis butu kitoks

			naujas[idx] = simbolis;
			fd << naujas << '\n';

			eilute = naujas; // naujoji eilute tampa pagrindu tolimesniam generavimui
		}
	}

	fd.close();
	cout << "Sugeneruotas failas: " << failas << "\n";
}


// HASHINIMAS
// Funkcija pavercia viena uint64_t i tiksliai 16 hex simboliu eilute
string Hex(uint64_t x) {
	const char* hexs = "0123456789abcdef"; // hex simboliai
	string s(16, '0'); // uzpildoma nuliais

	// Einama nuo pabaigos link pradzios, konvertuojama po 4 bitus i hex simboli
	for (int i = 15; i >= 0; --i) {
		s[i] = hexs[x & 0xF]; // paskutiniai 4 bitai
		x >>= 4;             // paslinkama i desine
	}
	return s; // graziname 16 simboliu hex string
}

// Pagrindinė hash funkcija
string Hashinimas(const string& input) {
	uint64_t hash = 0xABCDEF1234567890ULL; // pradine reiksme

	// Maisome kiekviena ivesties simboli
	for (char c : input) {
		hash = hash * 131 + (static_cast<unsigned char>(c) << 8); // dauginame ir sudedame simbolio ASCII
		hash ^= hash >> 17; // XOR su paslinktu hash
	}

	string result; // galutinis hash
	for (int i = 0; i < 4; ++i) {
		// Sukame bitus, kad kiekviena dalis butu skirtinga
		hash = (hash << 15) | (hash >> 49);
		result += Hex(hash); // konvertuojame i 16 hex simboliu ir pridedame prie rezultato
	}

	return result; // galutinis 64 simboliu hash
=======
﻿#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cstdint>    // leidzia naudoti uint64_t

using namespace std;

string tekstas;
string choice;
string input;

// MENIU
void meniu()
{
	cout << "\n\nMeniu: \n";
	cout << "1 - Rankiniu budu ivesti teksta\n";
	cout << "2 - Pasirinkti nuskaitoma faila\n";
	cout << "3 - Sugeneruoti testini faila\n";
	cout << "4 - Baigti darba\n";
	cout << "Pasirinkite (1, 2, 3, 4): ";
	cin >> choice;
}

// Failu meniu
string meniuFailai() {
	int nus = 0;
	string filename;

	while (true) {
		cout << "\nPasirinkite koki faila nuskaitysite:\n"
			<< "1 - empty.txt\n"
			<< "2 - test1.txt\n"
			<< "3 - test2.txt\n"
			<< "4 - pats ivesiu pavadinima.\n";
		cin >> nus;

		if (nus == 1) return "empty.txt";
		if (nus == 2) return "test1.txt";
		if (nus == 3) return "test2.txt";
		if (nus == 4) {
			cin >> filename;
			return filename;
		}
		cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
	}
}

// Meniu pasirinkimui koki faila generuoti
int meniuGeneravimas() {
	int g;
	cout << "\nPasirinkite generavimo buda:\n";
	cout << "1 - visiškai atsitiktiniai simboliai (1000 po 1000)\n";
	cout << "2 - atsitiktiniai simboliai (1000 po 1000), kurie vienas nuo kito skiriasi tik 1 simboliu\n";
	cout << "Pasirinkimas: ";
	cin >> g;
	return g;
}


// DUOMENU GENERAVIMAS
const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{};:,.<>?/";
string Generavimas(int ilgis, mt19937& gen) {
	uniform_int_distribution<int> dist(0, charset.size() - 1);
	string eil;
	for (int i = 0; i < ilgis; ++i)
		eil += charset[dist(gen)];
	return eil;
}

// Sugeneruoja i failus pagal pasirinkima 
void Sugeneruota(mt19937& gen, int g) {
	string failas = (g == 1 ? "test1.txt" : "test2.txt");
	ofstream fd(failas);
	if (!fd.is_open()) {
		cerr << "Nepavyko atidaryti failo.\n";
		return;
	}

	if (g == 1) {// Pilnai atsitiktiniai simboliai 

		for (int i = 0; i < 5; i++) {
			string eilute = Generavimas(1000, gen);
			fd << eilute << '\n';
		}
	}
	else if (g == 2) { // Atsitiktiniai simboliai, kurie vienas nuo kito skiriasi tik 1 simboliu

		// Pirmoji eilute
		string eilute = Generavimas(1000, gen);
		fd << eilute << '\n';

		uniform_int_distribution<int> pozicija(0, 999);
		for (int i = 1; i < 5; i++) {
			string naujas = eilute;
			int idx = pozicija(gen); // atsitiktinis indeksas

			// Pakeiciamas vienas simbolis
			char simbolis;
			do {
				uniform_int_distribution<int> dist(0, charset.size() - 1);
				simbolis = charset[dist(gen)];
			} while (simbolis == naujas[idx]); // uztikrinama, kad simbolis butu kitoks

			naujas[idx] = simbolis;
			fd << naujas << '\n';

			eilute = naujas; // naujoji eilute tampa pagrindu tolimesniam generavimui
		}
	}

	fd.close();
	cout << "Sugeneruotas failas: " << failas << "\n";
}


// HASHINIMAS
// Funkcija pavercia viena uint64_t i tiksliai 16 hex simboliu eilute
string Hex(uint64_t x) {
	const char* hexs = "0123456789abcdef"; // hex simboliai
	string s(16, '0'); // uzpildoma nuliais

	// Einama nuo pabaigos link pradzios, konvertuojama po 4 bitus i hex simboli
	for (int i = 15; i >= 0; --i) {
		s[i] = hexs[x & 0xF]; // paskutiniai 4 bitai
		x >>= 4;             // paslinkama i desine
	}
	return s; // graziname 16 simboliu hex string
}

// Pagrindinė hash funkcija
string Hashinimas(const string& input) {
	uint64_t hash = 0xABCDEF1234567890ULL; // pradine reiksme

	// Maisome kiekviena ivesties simboli
	for (char c : input) {
		hash = hash * 131 + (static_cast<unsigned char>(c) << 8); // dauginame ir sudedame simbolio ASCII
		hash ^= hash >> 17; // XOR su paslinktu hash
	}

	string result; // galutinis hash
	for (int i = 0; i < 4; ++i) {
		// Sukame bitus, kad kiekviena dalis butu skirtinga
		hash = (hash << 15) | (hash >> 49);
		result += Hex(hash); // konvertuojame i 16 hex simboliu ir pridedame prie rezultato
	}

	return result; // galutinis 64 simboliu hash
>>>>>>> a4504517df2868f8186b5e8cfedc53a1c4934494
}