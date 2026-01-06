// 2-oji uzduotis: Supaprastintos bloku grandines (Blockchain) kurimas

#include "Header.h"
vector<Block> blockchain; //grandine

string uzduotis;
string choose;

void meniu() {
    cout << "\nPasirinkite kuria uzduoti pateikti:\n";
    cout << "1 uzduotis - Hash funkcija\n";
    cout << "2 uzduotis - Blockchain kurimas\n";
    cout << "3 - Baigti darba\n";
    cout << "Iveskite pasirinkima (1, 2, 3): ";
    cin >> uzduotis;
}

void meniuBlock() {
    cout << "\n\nBlockchain meniu:\n";
    cout << "1 - Vartotoju generavimas\n";
    cout << "2 - Transakciju generavimas\n";
    cout << "3 - Bloko formavimas\n";
    cout << "4 - Bloko kasimas (eilinis)\n";
    cout << "5 - Bloko kasimas (lygiagretaus)\n";
    cout << "6 - Baigti darba\n";
    cout << "Pasirinkite (1, 2, 3, 4, 5, 6): ";
    cin >> choose;
}



// 1 PUNKTAS - VARTOTOJU GENERAVIMAS

// User klases apibrezimas
User::User(const string& name, const string& key, uint64_t balance)
    : name(name), publicKey(key), balance(balance) {
}

string User::getName() const { return name; }
string User::getPublicKey() const { return publicKey; }
uint64_t User::getBalance() const { return balance; }


// UserGenerator klases apibrezimas
UserGenerator::UserGenerator(int count, const string& outputFile)
    : count(count), outputFile(outputFile) {
}

void UserGenerator::generate() {
    users.clear();
    users.reserve(count);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> dist(10, 1'100'000);

    for (int i = 1; i <= count; ++i) {
        std::ostringstream oss;
        oss << "User" << setw(4) << setfill('0') << i;
        string name = oss.str();

        //string pubKey = Hashinimas(name + std::to_string(dist(gen)));

        string pubKey;
        uint64_t nonce = 0;
        do {
            pubKey = Hashinimas(name + std::to_string(dist(gen)) + std::to_string(nonce));
            ++nonce;
        } while (pubKey.substr(0, 3) != "000");

        uint64_t balance = dist(gen);
        users.emplace_back(name, pubKey, balance);
    }
}


void UserGenerator::saveToFile() const { // RAII: out uzsidaro automatiskai
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        throw std::runtime_error("Nepavyko sukurti failo: " + outputFile);
    }

    out << std::left
        << setw(12) << "Vardas"
        << setw(66) << "Viesasis raktas"
        << setw(15) << "Balansas" << "\n";
    out << std::string(93, '-') << "\n";

    for (const auto& u : users) {
        out << std::left
            << setw(12) << u.getName()
            << setw(66) << u.getPublicKey()
            << setw(15) << u.getBalance()
            << "\n";
    }
    cout << "\nSugeneruota " << users.size() << " vartotoju.\n";
    cout << "\nVisi duomenys irasyti i faila '" << outputFile << "'.\n";
}


void UserGenerator::printSample(int n) const {

    cout << "Pirmi " << n << " pavyzdziai (sutrumpinta):\n";
    for (int i = 0; i < n && i < (int)users.size(); ++i) {
        const auto& u = users[i];
        cout << setw(10) << std::left << u.getName()
            << " | Key: " << u.getPublicKey().substr(0, 20) << "..."
            << " | Balansas: " << u.getBalance() << "\n";
    }

}


// 2 PUNKTAS - TRANSAKCIJU GENERAVIMAS

//const vector<User>& UserGenerator::getUsers() const {
//    return users;}

TransactionGenerator::TransactionGenerator(const vector<User>& users, int txCount)
    : users(users), txCount(txCount) {
}


void TransactionGenerator::initUTXO() {
    utxos.clear();

    for (const auto& u : users) {
        UTXO utxo;
        utxo.ownerKey = u.getPublicKey();
        utxo.amount = u.getBalance();
        utxo.utxo_id = Hashinimas(u.getPublicKey() + std::to_string(u.getBalance()));
        utxos.push_back(utxo);
    }
}


void TransactionGenerator::generateTransactions() {
    transactions.clear();
    initUTXO();

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < txCount && !utxos.empty(); ++i) {

        // Atsitiktinis UTXO (siuntejas)
        std::uniform_int_distribution<size_t> utxoDist(0, utxos.size() - 1);
        size_t utxoIndex = utxoDist(gen);
        UTXO input = utxos[utxoIndex];

        // Atsitiktinis gavejas
        const User& receiverUser = users[gen() % users.size()];
        if (receiverUser.getPublicKey() == input.ownerKey)
            continue;

        // Suma
        std::uniform_int_distribution<uint64_t> amountDist(1, input.amount);
        uint64_t amount = amountDist(gen);

        // Transakcija
        Transaction tx;
        tx.sender = input.ownerKey;
        tx.receiver = receiverUser.getPublicKey();
        tx.amount = amount;

        tx.transaction_id = Hashinimas(
            tx.sender + tx.receiver + std::to_string(tx.amount)
        );

        transactions.push_back(tx);

        // Pasaliname panaudota UTXO
        utxos.erase(utxos.begin() + utxoIndex);

        // Gavejo naujas UTXO
        UTXO receiverUTXO;
        receiverUTXO.ownerKey = tx.receiver;
        receiverUTXO.amount = amount;
        receiverUTXO.utxo_id = Hashinimas(tx.transaction_id + "out1");
        utxos.push_back(receiverUTXO);

        // Graza siuntejui (jei liko)
        if (input.amount > amount) {
            UTXO change;
            change.ownerKey = tx.sender;
            change.amount = input.amount - amount;
            change.utxo_id = Hashinimas(tx.transaction_id + "change");
            utxos.push_back(change);
        }
    }

    cout << "\nSugeneruota " << transactions.size()
        << " transakciju naudojant UTXO modeli.\n";
}



void TransactionGenerator::saveToFile(const string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Nepavyko sukurti failo: " + filename);
    }

    out << "==================== TRANSAKCIJU SARASAS ====================\n\n";

    int index = 1;
    for (const auto& tx : transactions) {

        out << "================================================================================\n";
        out << string(30, ' ') << "TRANSAKCIJA #" << index++ << "\n";
        out << "--------------------------------------------------------------------------------\n";

        out << "Transaction ID : " << tx.transaction_id << "\n";
        out << "Sender         : " << tx.sender << "\n";
        out << "Receiver       : " << tx.receiver << "\n";
        out << "Amount         : " << tx.amount << "\n";

        out << "================================================================================\n\n";
    }

    cout << "\nTransakcijos issaugotos faile '" << filename << "\n";
}



// 3 PUNKTAS - BLOKU FORMAVIMAS


BlockGenerator::BlockGenerator(const vector<Transaction>& txs)
    : allTransactions(txs) {
}

const vector<Transaction>& TransactionGenerator::getTransactions() const {
    return transactions;
}


static string calculateMerkleRoot(const vector<Transaction>& txs) {
    string combined;
    for (const auto& tx : txs) {
        combined += tx.transaction_id;
    }
    return Hashinimas(combined);
}



Block BlockGenerator::generateBlock(const string& prevHash) {
    if (allTransactions.size() < 100) {
        throw std::runtime_error("Nepakanka transakciju blokui formuoti.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    // Atsitiktinai sumaisome transakcijas
    vector<Transaction> selected = allTransactions;
    std::shuffle(selected.begin(), selected.end(), gen);
    //selected.resize(100);
    if (selected.size() > 100) selected.resize(100);

    // Pašalinti panaudotas transakcijas iš allTransactions
    vector<Transaction> remaining;
    for (const auto& tx : allTransactions) {
        bool used = std::any_of(selected.begin(), selected.end(),
            [&](const Transaction& t) { return t.transaction_id == tx.transaction_id; });
        if (!used) remaining.push_back(tx);
    }
    allTransactions = remaining;




    Block block;
    block.transactions = selected;

    // Header pildymas
    block.header.prevBlockHash = prevHash;
    block.header.timestamp =
        std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now()
        );
    block.header.version = 1;
    block.header.merkleRoot = calculateMerkleRoot(block.transactions);
    block.header.nonce = gen();
    block.header.difficulty = 2; // sumazinau del greitesnio demonstravimo

    return block;
}


void BlockGenerator::saveBlockToFile(const Block& block, const string& filename, int blockNumber) const {
    std::ofstream out(filename, std::ios::app); // append prie failo
    if (!out.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + filename);
    }

    out << "========================= " << blockNumber << " BLOKAS =========================\n\n";

    out << "[ HEADER ]\n";
    out << "Previous Block Hash : " << block.header.prevBlockHash << "\n";
    out << "Timestamp           : " << block.header.timestamp << "\n";
    out << "Version             : " << block.header.version << "\n";
    out << "Merkle Root Hash    : " << block.header.merkleRoot << "\n";
    out << "Nonce               : " << block.header.nonce << "\n";
    out << "Difficulty Target   : " << block.header.difficulty << "\n";

    //out << "\n[ BODY – TRANSAKCIJOS (" << block.transactions.size() << ") ]\n";
    out << "\n[ BODY – TRANSAKCIJOS ]\n";
    out << std::string(70, '-') << "\n";

    int i = 1;
    for (const auto& tx : block.transactions) {
        out << "TX #" << i++ << "\n";
        out << "  ID       : " << tx.transaction_id << "\n";
        out << "  Sender   : " << tx.sender << "\n";
        out << "  Receiver : " << tx.receiver << "\n";
        out << "  Amount   : " << tx.amount << "\n";
        out << std::string(70, '-') << "\n";
    }

    cout << "\nBlokas #" << blockNumber << " sekmingai issaugotas faile '" << filename << "'.\n";

    out.close();
}



// UserGenerator
void UserGenerator::loadFromFile(const string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti vartotoju failo: " + filename);
    }

    users.clear();
    string line;
    std::getline(in, line); // antraste
    std::getline(in, line); // bruksnys

    while (std::getline(in, line)) {
        if (line.empty()) continue;
        string name = line.substr(0, 12);
        string pubKey = line.substr(12, 66);
        uint64_t balance = std::stoull(line.substr(78));
        users.emplace_back(name, pubKey, balance);
    }

    cout << "\nVartotojai ikelti is failo '" << filename
        << "'. Isviso " << users.size() << " vartotoju.\n";
}

// TransactionGenerator
void TransactionGenerator::loadFromFile(const string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti transakciju failo: " + filename);
    }

    transactions.clear();
    utxos.clear(); // jei reikia

    string line;
    std::getline(in, line); // praleidziame header
    while (std::getline(in, line)) {
        if (line.empty() || line.find("TRANSAKCIJA") != string::npos)
            continue;

        Transaction tx;
        while (std::getline(in, line) && !line.empty()) {
            if (line.find("Transaction ID") != string::npos)
                tx.transaction_id = line.substr(line.find(":") + 2);
            else if (line.find("Sender") != string::npos)
                tx.sender = line.substr(line.find(":") + 2);
            else if (line.find("Receiver") != string::npos)
                tx.receiver = line.substr(line.find(":") + 2);
            else if (line.find("Amount") != string::npos)
                tx.amount = std::stoull(line.substr(line.find(":") + 2));
        }
        transactions.push_back(tx);
    }

    cout << "\nTransakcijos ikeltos is failo '" << filename
        << "'. Is viso " << transactions.size() << " transakciju.\n";
}





// 4 PUNKTAS - BLOKO KASIMAS

string MineBlock(Block& block, int difficulty, uint64_t maxAttempts) {
    string prefix(difficulty, '0');
    uint64_t nonce = 0;
    string hash;
    //const int64_t maxAttempts = 1'000'000; // ribojame bandymus


    while (nonce < maxAttempts) {
        string headerData = block.header.prevBlockHash
            + std::to_string(block.header.timestamp)
            + std::to_string(block.header.version)
            + block.header.merkleRoot
            + std::to_string(nonce)
            + std::to_string(block.header.difficulty);

        hash = Hashinimas(headerData);

        if (hash.substr(0, difficulty) == prefix) {
            block.header.nonce = nonce;
            break;
        }
        ++nonce;
    }

    if (nonce >= maxAttempts) {
        cout << "Nepavyko iskasti bloko per " << maxAttempts << " bandymu. Procesas sustabdytas.\n";
        block.header.nonce = nonce;
    }



    return hash;
}


// LYGIAGRETAUS KASIMO FUNKCIJA

void MineWorker(
    const BlockHeader& header,
    int difficulty,
    uint64_t startNonce,
    uint64_t endNonce,
    std::atomic<bool>& found,
    std::atomic<uint64_t>& resultNonce,
    string& resultHash,
    std::mutex& resultMutex,
    int threadId
) {
    string prefix(difficulty, '0');

    for (uint64_t nonce = startNonce; nonce < endNonce && !found.load(); ++nonce) {
        string headerData = header.prevBlockHash
            + std::to_string(header.timestamp)
            + std::to_string(header.version)
            + header.merkleRoot
            + std::to_string(nonce)
            + std::to_string(header.difficulty);

        string hash = Hashinimas(headerData);

        if (hash.substr(0, difficulty) == prefix) {
            bool expected = false;
            if (found.compare_exchange_strong(expected, true)) {
                // Pirmas thread'as, kuris rado sprendima
                resultNonce.store(nonce);
                {
                    std::lock_guard<std::mutex> lock(resultMutex);
                    resultHash = hash;
                }
                cout << "\n[Thread " << threadId << "] Rado sprendima! Nonce: " << nonce << "\n";
            }
            return;
        }

        // Periodiskai pranesti apie progresa (kas 100000 bandymu)
        if (nonce % 100000 == 0 && nonce > startNonce) {
            cout << "[Thread " << threadId << "] Patikrinta: " << (nonce - startNonce) << " nonce reiksmiu...\r" << std::flush;
        }
    }
}


string MineBlockParallel(Block& block, int difficulty, uint64_t maxAttempts, int numThreads) {
    // Jei numThreads = 0, naudojame visus galimus CPU branduolius
    if (numThreads <= 0) {
        numThreads = std::thread::hardware_concurrency();
        if (numThreads == 0) numThreads = 4; // default, jei nepavyko nustatyti
    }

    cout << "\nPradedamas lygiagretaus kasimas su " << numThreads << " thread'ais...\n";
    cout << "Sunkumas: " << difficulty << " (ieskoma hash su " << difficulty << " nuliais priekyje)\n";
    cout << "Maksimalus bandymu skaicius: " << maxAttempts << "\n\n";

    auto startTime = std::chrono::high_resolution_clock::now();

    std::atomic<bool> found(false);
    std::atomic<uint64_t> resultNonce(0);
    string resultHash;
    std::mutex resultMutex;

    vector<std::thread> threads;
    uint64_t range = maxAttempts / numThreads;

    // Sukuriame thread'us
    for (int i = 0; i < numThreads; ++i) {
        uint64_t start = i * range;
        uint64_t end = (i == numThreads - 1) ? maxAttempts : (i + 1) * range;

        threads.emplace_back(
            MineWorker,
            std::ref(block.header),
            difficulty,
            start,
            end,
            std::ref(found),
            std::ref(resultNonce),
            std::ref(resultHash),
            std::ref(resultMutex),
            i + 1
        );
    }

    // Laukiame kol visi thread'ai baigs darba
    for (auto& t : threads) {
        t.join();
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;

    if (found.load()) {
        block.header.nonce = resultNonce.load();
        cout << "\n\n=== BLOKAS SEKMINGAI ISKASTAS ===\n";
        cout << "Laikas: " << elapsed.count() << " sekundes\n";
        cout << "Nonce: " << block.header.nonce << "\n";
        cout << "Hash: " << resultHash << "\n";
        cout << "Greitis: " << (block.header.nonce / elapsed.count()) << " hash/s\n";
        return resultHash;
    }
    else {
        block.header.nonce = maxAttempts;
        cout << "\n\nNepavyko iskasti bloko per " << maxAttempts << " bandymu.\n";
        cout << "Laikas: " << elapsed.count() << " sekundes\n";

        // Graziname paskutini hash
        string headerData = block.header.prevBlockHash
            + std::to_string(block.header.timestamp)
            + std::to_string(block.header.version)
            + block.header.merkleRoot
            + std::to_string(block.header.nonce)
            + std::to_string(block.header.difficulty);
        return Hashinimas(headerData);
    }
}


bool LoadBlockFromFile(Block& block, const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;

    std::string line;
    while (std::getline(in, line)) {
        if (line.find("Previous Block Hash") != std::string::npos)
            block.header.prevBlockHash = line.substr(line.find(":") + 2);
        else if (line.find("Timestamp") != std::string::npos)
            block.header.timestamp = std::stoull(line.substr(line.find(":") + 2));
        else if (line.find("Version") != std::string::npos)
            block.header.version = std::stoi(line.substr(line.find(":") + 2));
        else if (line.find("Merkle Root Hash") != std::string::npos)
            block.header.merkleRoot = line.substr(line.find(":") + 2);
        else if (line.find("Nonce") != std::string::npos)
            block.header.nonce = std::stoull(line.substr(line.find(":") + 2));
        else if (line.find("Difficulty Target") != std::string::npos)
            block.header.difficulty = std::stoi(line.substr(line.find(":") + 2));

        // Transakcijos
        else if (line.find("Transaction ID") != std::string::npos) {
            Transaction tx;
            tx.transaction_id = line.substr(line.find(":") + 2);
            std::getline(in, line);
            tx.sender = line.substr(line.find(":") + 2);
            std::getline(in, line);
            tx.receiver = line.substr(line.find(":") + 2);
            std::getline(in, line);
            tx.amount = std::stoull(line.substr(line.find(":") + 2));
            block.transactions.push_back(tx);
        }
    }

    in.close();
    return true;
}



// 5 PUNKTAS - BLOKO PATVIRTINIMAS IR GRANDINES PAPILDYMAS



vector<User>& UserGenerator::getUsers() {
    return users;
}


vector<Transaction>& TransactionGenerator::getTransactions() {
    return transactions;
}



// Funkcija, kuri realizuoja bloko patvirtinima ir itraukima
// 
// Funkcija, kuri issaugo blockchain i faila "grandine.txt" ir papildomai raso info
void SaveBlockchainToFile(const vector<Block>& chain, const string& filename) {
    ofstream out(filename, std::ios::app); // ios::app -> papildymas prie esamo failo
    if (!out.is_open()) {
        cerr << "Nepavyko atidaryti failo " << filename << " irasyti blockchain.\n";
        return;
    }

    const Block& lastBlock = chain.back();

    out << chain.size();
    //out << " Bloko hash: " << lastBlock.header.merkleRoot << "\n";
    out << " Bloko hash: " << lastBlock.hash << "\n";
    out << "------------------------------\n";

    out.close();
}



// SITASSS
/*
void processBlock(Block& block, UserGenerator& ug, std::unique_ptr<TransactionGenerator>& tgPtr) {
    cout << "\nPradedamas Bloko patvirtinimas, transakciju ir balansu atnaujinimas, bloko pridejimas prie grandines...\n"

    // Patikriname ar blokas turi transakciju
    if (block.transactions.empty()) {
        cout << "Transakcijos neegzistuoja, negalima patvirtinti bloko.\n";
        return;
    }

    // Iteruojame per visas bloko transakcijas
    for (const auto& tx : block.transactions) {

        // Surandame siunteja
        for (auto& user : ug.getUsers()) {
            if (user.getPublicKey() == tx.sender) {
                user.setBalance(user.getBalance() - tx.amount);
                break;
            }
        }

        // Surandame gaveja
        for (auto& user : ug.getUsers()) {
            if (user.getPublicKey() == tx.receiver) {
                user.setBalance(user.getBalance() + tx.amount);
                break;
            }
        }
    }

    // Pasaliname i blokas itrauktas transakcijas is globalaus transakciju saraso
    if (tgPtr) {
        auto& txVec = const_cast<vector<Transaction>&>(tgPtr->getTransactions());
        for (const auto& tx : block.transactions) {
            txVec.erase(std::remove_if(txVec.begin(), txVec.end(),
                [&](const Transaction& t) { return t.transaction_id == tx.transaction_id; }),
                txVec.end());
        }
    }

    // Pridedame blokas i blockchain
    blockchain.push_back(block);

    // Konsoles pranesimas
    cout << "\nBlokas patvirtintas ir itrauktas i blockchain.\n";
    cout << "Blockchain ilgis: " << blockchain.size() << "\n";
    cout << "Izkasto bloko hash: " << block.header.merkleRoot << "\n";

    // Issaugome i faila "grandine.txt"
    SaveBlockchainToFile(blockchain, "grandine.txt");

    //cout << "\nBlokas patvirtintas ir itrauktas i blockchain. Blockchain ilgis: "
    //    << blockchain.size() << "\n";
}
*/

void processBlock(Block& block, UserGenerator& ug, std::unique_ptr<TransactionGenerator>& tgPtr) {
    if (block.transactions.empty()) {
        cout << "Transakcijos neegzistuoja, negalima patvirtinti bloko.\n";
        return;
    }

    // Iteruojame per bloko transakcijas ir atnaujiname vartotoju balansus
    for (const auto& tx : block.transactions) {
        for (auto& user : ug.getUsers()) {
            if (user.getPublicKey() == tx.sender) {
                user.setBalance(user.getBalance() - tx.amount);
                break;
            }
        }
        for (auto& user : ug.getUsers()) {
            if (user.getPublicKey() == tx.receiver) {
                user.setBalance(user.getBalance() + tx.amount);
                break;
            }
        }
    }

    // Pasaliname i bloka itrauktas transakcijas is globalaus saraso
    if (tgPtr) {
        //auto& txVec = const_cast<vector<Transaction>&>(tgPtr->getTransactions());
        auto& txVec = tgPtr->getTransactions();
        for (const auto& tx : block.transactions) {
            txVec.erase(std::remove_if(txVec.begin(), txVec.end(),
                [&](const Transaction& t) { return t.transaction_id == tx.transaction_id; }),
                txVec.end());
        }
    }

    // Pridedame blokas i blockchain
    blockchain.push_back(block);

    // Konsoles pranesimas
    cout << "\nBlokas automatiskai patvirtintas ir itrauktas i blockchain.\n";
    cout << "Blockchain ilgis: " << blockchain.size() << "\n";
    //cout << "Iskasto bloko hash: " << block.header.merkleRoot << "\n";

    // Issaugome i faila "grandine.txt"
    SaveBlockchainToFile(blockchain, "grandine.txt");
}


void User::setBalance(uint64_t newBalance) {
    balance = newBalance;
}
