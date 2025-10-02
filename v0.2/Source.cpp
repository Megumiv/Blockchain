#include "Header.h"

string choice;
string input;

// MENIU
void meniu() {
    cout << "\n\nMeniu: \n";
    cout << "1 - Rankiniu budu ivesti teksta\n";
    cout << "2 - Pasirinkti nuskaitoma faila\n";
    cout << "3 - Sugeneruoti testini faila\n";
    cout << "4 - Koliziju paieska\n";
    cout << "5 - Efektyvumo matavimas\n";
    cout << "6 - Demonstracija input + salt\n";
    cout << "7 - Lavinos efektas\n";
    cout << "8 - Baigti darba\n";
    cout << "Pasirinkite (1, 2, 3, 4, 5, 6, 7, 8): ";
    cin >> choice;
}

string meniuFailai() {
    int nus = 0;
    string filename;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        cout << "\nPasirinkite koki faila nuskaitysite:\n"
            << "1 - test_empty.txt\n"
            << "2 - test_random.txt\n"
            << "3 - test_random2.txt\n"
            << "4 - pats ivesiu pavadinima.\n";
        cout << "Pasirinkimas: ";

        string in;
        getline(cin, in);
        try {
            nus = stoi(in); // i int
        }
        catch (...) {
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
            continue;
        }
        if (nus == 1) return "test_empty.txt";
        if (nus == 2) return "test_random.txt";
        if (nus == 3) return "test_random2.txt";
        if (nus == 4) {
            cout << "Iveskite failo pavadinima: ";
            getline(cin, filename);
            if (!filename.empty())
                return filename;
            else
                cout << "Failo pavadinimas negali buti tuscias.\n";
        }
        else {
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
        }
    }
}

int meniuGeneravimas() {
    int g;
    cout << "\nPasirinkite generavimo buda:\n";
    cout << "1 - visiskai atsitiktiniai simboliai (keli po 1000)\n";
    cout << "2 - atsitiktiniai simboliai (keli po 1000), kurie vienas nuo kito skiriasi tik 1 simboliu\n";
    cout << "3 - 100 000 atsitiktiniu string poru, ilgiai: 10, 100, 500, 1000 simboliu\n";
    cout << "Pasirinkimas: ";
    cin >> g;

    if (g < 1 || g > 3) {
        cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
        return meniuGeneravimas();
    }

    return g;
}

int meniuOutput() {
    int out;
    cout << "\nKur norite isvesti rezultatus?\n";
    cout << "1 - I ekrana\n";
    cout << "2 - I faila (Rezultatai.txt)\n";
    cout << "Pasirinkimas: ";
    cin >> out;
    return out;
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

void Sugeneruota(mt19937& gen, int g) {

    if (g == 1 || g == 2) {

        string failas = (g == 1 ? "test_random.txt" : "test_random2.txt");
        ofstream fd(failas);
        if (!fd.is_open()) {
            cerr << "Nepavyko atidaryti failo.\n";
            return;
        }

        if (g == 1) {
            for (int i = 0; i < 5; i++) {
                string eilute = Generavimas(1000, gen);
                fd << eilute << '\n';
            }
        }
        else if (g == 2) {
            string eilute = Generavimas(1000, gen);
            fd << eilute << '\n';

            uniform_int_distribution<int> pozicija(0, 999);
            for (int i = 1; i < 5; i++) {
                string naujas = eilute;
                int idx = pozicija(gen);

                char simbolis;
                do {
                    uniform_int_distribution<int> dist(0, charset.size() - 1);
                    simbolis = charset[dist(gen)];
                } while (simbolis == naujas[idx]);

                naujas[idx] = simbolis;
                fd << naujas << '\n';
                eilute = naujas;
            }
        }

        fd.close();
        cout << "Sugeneruotas failas: " << failas << "\n";
    }

    else if (g == 3) { // Naujas pasirinkimas – 100 000 poru skirtingu ilgiu Koliziju paieskai
        const int kiekis = 100000;
        const std::vector<int> ilgiai = { 10, 100, 500, 1000 };

        for (int ilgis : ilgiai) {
            string failas = "test_" + std::to_string(ilgis) + ".txt";
            ofstream fd(failas);
            if (!fd.is_open()) {
                cerr << "Nepavyko sukurti failo: " << failas << "\n";
                continue;
            }

            // Sugeneruojame pirma eilute atsitiktinai
            string eilute = Generavimas(ilgis, gen);
            fd << eilute << '\n';

            uniform_int_distribution<int> pozicija(0, ilgis - 1);

            for (int i = 1; i < kiekis * 2; i++) { // *2, nes kiekviena pora = 2 eilutes
                string naujas = eilute;
                int idx = pozicija(gen);

                // Pakeiciame viena simboli
                char simbolis;
                do {
                    uniform_int_distribution<int> dist(0, charset.size() - 1);
                    simbolis = charset[dist(gen)];
                } while (simbolis == naujas[idx]);

                naujas[idx] = simbolis;

                fd << naujas << '\n';

                eilute = naujas; // naujoji eilute tampa pagrindu tolimesniam generavimui
            }

            fd.close();
            cout << "Sugeneruota " << kiekis << " poru (ilgis="
                << ilgis << ") i faila " << failas << "\n";
        }
    }
    else {
        cerr << "Neteisingas pasirinkimas generavimui.\n";
    }

}

// HASHINIMAS
string Hex(uint64_t x) {
    const char* hexs = "0123456789abcdef";
    string s(16, '0');
    for (int i = 15; i >= 0; --i) {
        s[i] = hexs[x & 0xF];
        x >>= 4;
    }
    return s;
}

inline uint64_t RotL(uint64_t x, int r) {
    return (x << r) | (x >> (64 - r));
}

string Hashinimas(const string& input) {
    uint64_t h1 = 0x123456789ABCDEF0ULL;  // pradin?s s?klos
    uint64_t h2 = 0x0FEDCBA987654321ULL;

    const uint64_t c1 = 0x87c37b91114253d5ULL;
    const uint64_t c2 = 0x4cf5ad432745937fULL;

    for (unsigned char c : input) {
        uint64_t k = c;
        k *= c1;
        k = RotL(k, 31);
        k *= c2;

        h1 ^= k;
        h1 = RotL(h1, 27) + h2;
        h1 = h1 * 5 + 0x52dce729;

        h2 ^= k;
        h2 = RotL(h2, 33) + h1;
        h2 = h2 * 5 + 0x38495ab5;
    }

    // Finalization mix (kaip MurmurHash3 stiliaus)
    h1 ^= input.size();
    h2 ^= input.size();

    h1 += h2;
    h2 += h1;

    // "Avalanche mix"
    auto fmix64 = [](uint64_t k) {
        k ^= k >> 33;
        k *= 0xff51afd7ed558ccdULL;
        k ^= k >> 33;
        k *= 0xc4ceb9fe1a85ec53ULL;
        k ^= k >> 33;
        return k;
        };

    h1 = fmix64(h1);
    h2 = fmix64(h2);

    h1 += h2;
    h2 += h1;

    // 256 bit? hash (4 x 64-bit ? 64 hex simboliai)
    string result;
    result.reserve(64);
    auto toHex = [](uint64_t x) {
        const char* hexs = "0123456789abcdef";
        string s(16, '0');
        for (int i = 15; i >= 0; --i) {
            s[i] = hexs[x & 0xF];
            x >>= 4;
        }
        return s;
        };

    result += toHex(h1);
    result += toHex(h2);
    result += toHex(~h1);
    result += toHex(~h2);

    return result;
}


void Isvedimas(const string& filename, int out) {
    ifstream fd(filename);
    if (!fd.is_open()) {
        cerr << "Nepavyko atidaryti failo: " << filename << endl;
        return;
    }

    ofstream outFile;
    if (out == 2) {
        outFile.open("Rezultatai.txt");
        if (!outFile.is_open()) {
            cerr << "Nepavyko sukurti failo: Rezultatai.txt\n";
            fd.close();
            return;
        }
    }

    string line;
    bool tuscias = true;

    while (getline(fd, line)) {
        string hashed = Hashinimas(line);

        // Patikrinimas – rezultato ilgis visada 64 simboliai
        if (hashed.size() != 64) {
            cerr << "KLAIDA: neteisingas hash ilgis ("
                << hashed.size() << " vietoj 64).\n";
        }

        if (out == 1) { // i ekrana
            cout << hashed << endl;
        }
        else if (out == 2) { // i faila
            outFile << hashed << endl;
        }
    }

    if (tuscias) {
        cout << "Failas tuscias: " << filename << endl;
    }

    fd.close();
    if (outFile.is_open()) {
        outFile.close();
        cout << "Rezultatai irasyti i faila Rezultatai.txt sekmingai.\n";
    }
}


// Patikrina kiek poru hash'ai sutampa
void KolizijuPaieska(const string& failas) {
    ifstream fd(failas);
    if (!fd.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failas << "\n";
        return;
    }

    string a, b;
    int poruSk = 0;
    int sutampanciuSk = 0;

    while (fd >> a >> b) {  // nuskaityti dvi eilutes poroje
        string hashA = Hashinimas(a);
        string hashB = Hashinimas(b);

        if (hashA == hashB) {
            sutampanciuSk++;
        }

        poruSk++;
    }

    fd.close();

    cout << "Failas: " << failas << "\n";
    cout << "Poru skaicius: " << poruSk << "\n";
    cout << "Sutampanciu hash skaicius: " << sutampanciuSk << "\n";
    double procentai = (poruSk > 0) ? (100.0 * sutampanciuSk / poruSk) : 0;
    cout << "Sutampanciu hash procentas: " << procentai << "%\n";
}

// Matuojamas efektyvumas, laikas su "konstitucija.txt"
void MatuotiEfektyvuma(const string& failas, int kartojimai) {
    ifstream fd(failas);
    if (!fd.is_open()) {
        cerr << "Nepavyko atidaryti failo: " << failas << "\n";
        return;
    }

    std::vector<string> eilutes;
    string line;
    while (getline(fd, line)) {
        eilutes.push_back(line);
    }
    fd.close();

    for (size_t n = 1; n <= eilutes.size(); n *= 2) {
        double suma = 0;

        for (int k = 0; k < kartojimai; ++k) {
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < n && i < eilutes.size(); ++i) {
                string h = Hashinimas(eilutes[i]);
                (void)h;
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> diff = end - start;
            suma += diff.count();
        }

        cout << "Hashavimas " << n << " eiluciu (5 kartu vidurkis): " << suma / kartojimai << " ms\n";
    }
}



// Generuoja atsitiktini salt
string GeneruotiSalt(int ilgis, mt19937& gen) {
    uniform_int_distribution<int> dist(0, charset.size() - 1);
    string salt;
    salt.reserve(ilgis);
    for (int i = 0; i < ilgis; ++i) {
        salt += charset[dist(gen)];
    }
    return salt;
}

// Demonstracija Hash(input + salt)
void DemonstruotiNegriztamaHash(const string& input) {
    random_device rd;
    mt19937 gen(rd());

    string salt = GeneruotiSalt(16, gen); // 16 simboliu salt
    string hashSuSalt = Hashinimas(input + salt);

    cout << "Originalus input: " << input << endl;
    cout << "Salt: " << salt << endl;
    cout << "Hash(input + salt): " << hashSuSalt << endl;

    cout << "\nNet jei zinome hash, atstatyti originalu input be salt praktiskai neimanoma." << endl;
}



void LavinosEfektasIsFailo(const string& failas) {
    ifstream fd(failas);
    if (!fd.is_open()) {
        cerr << "Nepavyko atidaryti failo: " << failas << endl;
        return;
    }

    string a, b;
    vector<int> bitDiffs;
    vector<int> hexDiffs;

    while (getline(fd, a)) {
        if (!getline(fd, b)) break; // kiekviena pora = 2 eilutes

        string hashA = Hashinimas(a);
        string hashB = Hashinimas(b);

        // Bitu skirtumas
        int bitDiff = 0;
        for (size_t i = 0; i < hashA.size(); ++i) {
            uint8_t v1 = std::stoi(hashA.substr(i, 1), nullptr, 16);
            uint8_t v2 = std::stoi(hashB.substr(i, 1), nullptr, 16);
            bitDiff += std::bitset<4>(v1 ^ v2).count();
        }

        // Hex simboliu skirtumas
        int hexDiff = 0;
        for (size_t i = 0; i < hashA.size(); ++i) {
            if (hashA[i] != hashB[i]) hexDiff++;
        }

        bitDiffs.push_back(bitDiff);
        hexDiffs.push_back(hexDiff);
    }

    fd.close();

    if (bitDiffs.empty()) {
        cout << "Failas neturi pakankamai poru.\n";
        return;
    }

    auto minBit = *min_element(bitDiffs.begin(), bitDiffs.end());
    auto maxBit = *max_element(bitDiffs.begin(), bitDiffs.end());
    double avgBit = accumulate(bitDiffs.begin(), bitDiffs.end(), 0.0) / bitDiffs.size();

    auto minHex = *min_element(hexDiffs.begin(), hexDiffs.end());
    auto maxHex = *max_element(hexDiffs.begin(), hexDiffs.end());
    double avgHex = accumulate(hexDiffs.begin(), hexDiffs.end(), 0.0) / hexDiffs.size();

    cout << "\n--- Lavinos efektas failui: " << failas << " ---\n";
    cout << "Bitu skirtumas: min=" << minBit << ", max=" << maxBit << ", vid=" << avgBit << endl;
    cout << "Hex simboliu skirtumas: min=" << minHex << ", max=" << maxHex << ", vid=" << avgHex << endl;
}