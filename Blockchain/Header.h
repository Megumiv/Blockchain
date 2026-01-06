#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cstdint> // leidzia naudoti uint64_t
#include <limits>
#include <vector>
#include <chrono>
#include <bitset>
#include <numeric>
#include <algorithm>
//nuo 2 uzd
#include <iomanip>
#include <sstream>
//#include <filesystem> // C++17
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>



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
void meniuHash();
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


void PatikrintiHashPoras(const string& failoVardas);
void DemonstruotiNegriztamaHash(const string& input);

void LavinosEfektasIsFailo(const string& failas);



// 2 uzduoties papildymai:

using std::setw;
using std::setfill;

extern string uzduotis;
void meniu();

extern string choose;
void meniuBlock();


class User { // Vartotojo struktura (duomenu konteineris)
private:
    string name;
    string publicKey;
    uint64_t balance;

public:
    User(const string& name, const string& key, uint64_t balance);

    // Getteriai – kapsuliacija (duomenys privatus)
    string getName() const;
    string getPublicKey() const;
    uint64_t getBalance() const;

    // Setter to allow balance updates from UserGenerator
    void setBalance(uint64_t newBalance); // ?????????????????????????
};

// Atsakinga uz vartotoju generavima ir issaugojima
class UserGenerator {
private:
    vector<User> users;
    int count;
    string outputFile;

public:
    explicit UserGenerator(int count = 1000, const string& outputFile = "vartotojai.txt");
    void generate();
    void saveToFile() const;
    void printSample(int n = 5) const;

    const vector<User>& getUsers() const;
    vector<User>& getUsers();

    void loadFromFile(const string& filename = "vartotojai.txt");
};


// TRANSAKCIJOS IR UTXO 

struct UTXO {
    string ownerKey;
    uint64_t amount;
    string utxo_id;
};

struct Transaction {
    string transaction_id;
    string sender;
    string receiver;
    uint64_t amount;
};

class TransactionGenerator {
private:
    vector<UTXO> utxos;
    vector<Transaction> transactions;
    vector<User> users;
    int txCount;

public:
    TransactionGenerator(const vector<User>& users, int txCount = 10000);

    void initUTXO();
    void generateTransactions();
    void saveToFile(const string& filename = "transakcijos.txt") const;

    const vector<Transaction>& getTransactions() const;
    vector<Transaction>& getTransactions();

    void loadFromFile(const string& filename = "transakcijos.txt");
};



//  BLOKO STRUKTURA

struct BlockHeader {
    string prevBlockHash;
    uint64_t timestamp;
    int version;
    string merkleRoot;
    uint64_t nonce;
    int difficulty;
};

struct Block {
    BlockHeader header;
    vector<Transaction> transactions;
    string hash; // Hash bloko po kasimo (Proof-of-Work)
};

class BlockGenerator {
private:
    vector<Transaction> allTransactions;

public:
    explicit BlockGenerator(const vector<Transaction>& txs);

    Block generateBlock(const string& prevHash = "GENESIS");
    //void saveBlockToFile(const Block& block, const string& filename = "blokas.txt") const;
    void saveBlockToFile(const Block& block, const std::string& filename = "blokas.txt", int blockNumber = 0) const;

};


void loadFromFile(const string& filename = "transakcijos.txt");


// BLOKO KASIMAS

// Proof-of-Work funkcija
string MineBlock(Block& block, int difficulty = 3, uint64_t maxAttempts = 5000000);

// Lygiagretaus kasimo funkcija
string MineBlockParallel(Block& block, int difficulty = 3, uint64_t maxAttempts = 5000000, int numThreads = 0);



inline bool fileExists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
};

bool LoadBlockFromFile(Block& block, const std::string& filename);


// BLOKO GRANDINE IR TIKRINIMAS

extern vector<Block> blockchain; // visa blockchain grandine

void processBlock(Block& currentBlock, UserGenerator& ug, std::unique_ptr<TransactionGenerator>& tgPtr);
