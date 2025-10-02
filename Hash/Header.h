#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cstdint> // leidzia naudoti uint64_t
#include <limits>
#include <vector>
#include <chrono>


using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::mt19937;
using std::uniform_int_distribution;
using std::random_device;
using std::numeric_limits;
using std::streamsize;
using std::getline;
using std::vector;

extern string choice;
extern string input;

// Funkciju deklaravimas
void meniu();
string meniuFailai();
int meniuGeneravimas();
int meniuOutput();

string Generavimas(int ilgis, mt19937& gen);
void Sugeneruota(mt19937& gen, int g);

string Hex(uint64_t x);
string Hashinimas(const string& input);

void Isvedimas(const string& filename, int out);

void KolizijuPaieska(const string& failas); 
void MatuotiEfektyvuma(const string& failas, int kartojimai = 5);

