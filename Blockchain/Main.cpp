#include "Header.h"

std::unique_ptr<TransactionGenerator> tgPtr; // nullptr is pradziu
UserGenerator ug(1000);          // vartotojai, globalus objektas

Block currentBlock;        // Saugo paskutini sugeneruota bloka
bool blockGenerated = false; // Ar blokas jau sugeneruotas




int main() {

	while (true) {
		cout << "---  PRADINIS MENIU  ---\n";
		meniu();
		//if (uzduotis == "1" || uzduotis == "2") {
		//	break;
		//}

		// 1 UZDUOTIS
		if (uzduotis == "1") {


			cout << "\n\n---  HASH GENERATORIUS  ---";

			random_device rd;
			mt19937 gen(rd());

			while (true) {
				meniuHash();

				if (choice == "1") { // ivedama ranka

					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					while (true) {
						cout << "\nIveskite teksta (norint baigti - enter): \n";
						getline(cin, input);  // nuskaitoma eilute

						if (input.empty()) {
							break;
						}
						// Iskvieciama hash funkcija ir atspausdinamas rezultatas
						cout << "\nSugeneruotas rezultatas:\n" << Hashinimas(input) << endl;
					}
				}

				else if (choice == "2") { // nuskaitomas failas
					string filename = meniuFailai();
					int out = meniuOutput();
					Isvedimas(filename, out);

				}

				else if (choice == "3") { // testiniu failu paruosimas
					int g = meniuGeneravimas();
					Sugeneruota(gen, g);
				}

				else if (choice == "4") { // koliziju paieska
					// Patikriname hash sutapimus kiekviename poru faile
					KolizijuPaieska("test_10.txt");
					KolizijuPaieska("test_100.txt");
					KolizijuPaieska("test_500.txt");
					KolizijuPaieska("test_1000.txt");
				}

				else if (choice == "5") { // efektyvumo matavimas
					MatuotiEfektyvuma("konstitucija.txt");
				}

				else if (choice == "6") { // Demonstracija input + salt
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nIveskite teksta demonstracijai: ";
					getline(cin, input);
					DemonstruotiNegriztamaHash(input);
				}

				else if (choice == "7") {  // Lavinos efektas
					LavinosEfektasIsFailo("test_10.txt");
					LavinosEfektasIsFailo("test_100.txt");
					LavinosEfektasIsFailo("test_500.txt");
					LavinosEfektasIsFailo("test_1000.txt");

				}

				else if (choice == "8") { // baigiamas darbas
					break;
				}

				else { // meniu neteisingo ivedimo isvestis
					cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
					continue;
				}
			}

		}



		// 2 UZDUOTIS 


		else if (uzduotis == "2") {
			cout << "\n\n---  BLOCKCHAIN KURIMAS  ---";

			while (true) {
				meniuBlock();

				if (choose == "1") { // Vartotoju generavimas
					try {
						UserGenerator generator(1000);
						generator.generate();
						generator.saveToFile();
						generator.printSample();
					}
					catch (const std::exception& e) {
						std::cerr << "Klaida: " << e.what() << "\n";
					}
				}

				else if (choose == "2") { // Transakciju generavimas
					cout << "\nTransakciju generavimas pradetas.\n";
					try {
						//UserGenerator ug(1000);
						ug.generate();

						tgPtr = std::make_unique<TransactionGenerator>(ug.getUsers(), 10000);
						tgPtr->generateTransactions();
						tgPtr->saveToFile();

						//TransactionGenerator tg(ug.getUsers(), 10000);
						//tg.generateTransactions();
						//tg.saveToFile();
					}
					catch (const std::exception& e) {
						cerr << "Klaida: " << e.what() << endl;
					}
				}

				else if (choose == "3") { // Bloko formavimas

					// sitaassssss
					/*
					if (!tgPtr) {
						cout << "Ikeliami vartotojai ir transakcijos is failu...\n";
						ug.loadFromFile("vartotojai.txt");
						tgPtr = std::make_unique<TransactionGenerator>(ug.getUsers(), 0);
						tgPtr->loadFromFile("transakcijos.txt");
					}


					BlockGenerator bg(tgPtr->getTransactions());
					currentBlock = bg.generateBlock("000000GENESISBLOCK"); // Sugeneruojamas blokas
					blockGenerated = true;

					bg.saveBlockToFile(currentBlock);
					*/


					// Bloku formavimas - visu bloku generavimas
					cout << "Bloku formavimas pradetas.\n";


					if (!tgPtr) {
						cout << "Ikeliami vartotojai ir transakcijos is failu...\n";
						ug.loadFromFile("vartotojai.txt");
						tgPtr = std::make_unique<TransactionGenerator>(ug.getUsers(), 0);
						tgPtr->loadFromFile("transakcijos.txt");
					}

					if (tgPtr->getTransactions().size() < 100) {
						cout << "Nepakanka transakciju bloku formavimui (reikia bent 100). Turite: "
							<< tgPtr->getTransactions().size() << "\n";
						continue;
					}

					// Formuojame visus galimus blokus
					int blockCount = 0;
					string prevHash = "000000GENESISBLOCK";

					// Issaugojame pirma bloka i 'blokas.txt' paprastai (ne append)
					std::ofstream clearFile("blokas.txt");
					clearFile.close();

					while (tgPtr->getTransactions().size() >= 100) {
						try {
							BlockGenerator bg(tgPtr->getTransactions());
							Block block = bg.generateBlock(prevHash);

							blockCount++;
							bg.saveBlockToFile(block, "blokas.txt", blockCount);

							// Pasaliname panaudotas transakcijas
							auto& txVec = tgPtr->getTransactions();
							txVec.erase(txVec.begin(), txVec.begin() + 100);

							// Kito bloko prevHash bus sio bloko merkleRoot
							prevHash = block.header.merkleRoot;

						}
						catch (const std::exception& e) {
							cerr << "Klaida formuojant bloka: " << e.what() << "\n";
							break;
						}
					}

					cout << "\nIs viso suformuota " << blockCount << " bloku.\n";
					cout << "Liko nepanaudotu transakciju: " << tgPtr->getTransactions().size() << "\n";

					blockGenerated = false; // Blokai issaugoti, bet neiskasti

				}

				else if (choose == "4") { // Bloku kasimas (eilinis)

					// Patikriname, ar blokas jau sugeneruotas arba galima ikelti is failo
					if (!blockGenerated) {
						if (fileExists("blokas.txt")) {
							if (LoadBlockFromFile(currentBlock, "blokas.txt")) {
								// Jei dar neturime tgPtr, ikeliame transakcijas
								if (!tgPtr) {
									ug.loadFromFile("vartotojai.txt");
									tgPtr = std::make_unique<TransactionGenerator>(ug.getUsers(), 0);
									tgPtr->loadFromFile("transakcijos.txt");
								}
								currentBlock.transactions = tgPtr->getTransactions();
								blockGenerated = true;
								cout << "\nBlokas ikeltas is failo 'blokas.txt' su transakcijomis.\n";
							}
							else {
								cout << "Nepavyko ikelti bloko is failo.\n";
								continue;
							}
						}
						else {
							cout << "Pirmiausia sugeneruokite bloka (meniu pasirinkimas 3).\n";
							continue;
						}
					}

					// Tikriname, ar blokas turi transakciju
					if (currentBlock.transactions.empty()) {
						cout << "Blokas neturi transakciju, negalimas kasimas.\n";
						continue;
					}

					cout << "Pradedamas EILINIS bloko kasimas (Proof-of-Work)...\n";
					string minedHash = MineBlock(currentBlock, 3); // Naudojamas tas pats blokas

					if (minedHash.substr(0, 3) == string(3, '0')) { // jei sekmingai iskasta

						cout << "Blokas sekmingai iskastas! Hash: " << minedHash << "\n";
						currentBlock.hash = minedHash; // Issaugome hash i bloko struktura 

						// Issaugome iskasta bloka i nauja faila 'iskastas.txt'
						if (tgPtr) {
							BlockGenerator bg(tgPtr->getTransactions());
							bg.saveBlockToFile(currentBlock, "iskastas.txt"); // naujas failas
						}


						// 5 PUNKTAS - Bloko patvirtinimas ir itraukimas i grandine
						processBlock(currentBlock, ug, tgPtr);

						// Isvalome currentBlock, kad kitas blokas butu naujas
						currentBlock.transactions.clear();
						blockGenerated = false;
					}

				}


				else if (choose == "5") { // Bloku kasimas (lygiagretaus)

					// Patikriname, ar blokas jau sugeneruotas arba galima ikelti is failo
					if (!blockGenerated) {
						if (fileExists("blokas.txt")) {
							if (LoadBlockFromFile(currentBlock, "blokas.txt")) {
								// Jei dar neturime tgPtr, ikeliame transakcijas
								if (!tgPtr) {
									ug.loadFromFile("vartotojai.txt");
									tgPtr = std::make_unique<TransactionGenerator>(ug.getUsers(), 0);
									tgPtr->loadFromFile("transakcijos.txt");
								}
								currentBlock.transactions = tgPtr->getTransactions();
								blockGenerated = true;
								cout << "\nBlokas ikeltas is failo 'blokas.txt' su transakcijomis.\n";
							}
							else {
								cout << "Nepavyko ikelti bloko is failo.\n";
								continue;
							}
						}
						else {
							cout << "Pirmiausia sugeneruokite bloka (meniu pasirinkimas 3).\n";
							continue;
						}
					}

					// Tikriname, ar blokas turi transakciju
					if (currentBlock.transactions.empty()) {
						cout << "Blokas neturi transakciju, negalimas kasimas.\n";
						continue;
					}

					// Pasirinkti threadu skaiciu
					int numThreads;
					cout << "\nIveskite threadu skaiciu (0 = automatinis): ";
					cin >> numThreads;

					cout << "\nPradedamas LYGIAGRETAUS bloko kasimas (Proof-of-Work)...\n";
					string minedHash = MineBlockParallel(currentBlock, 3, 5000000, numThreads);

					if (minedHash.substr(0, 3) == string(3, '0')) { // jei sekmingai iskasta

						cout << "\nBlokas sekmingai iskastas! Hash: " << minedHash << "\n";
						currentBlock.hash = minedHash; // Issaugome hash i bloko struktura 

						// Issaugome iskasta bloka i nauja faila 'iskastas.txt'
						if (tgPtr) {
							BlockGenerator bg(tgPtr->getTransactions());
							bg.saveBlockToFile(currentBlock, "iskastas.txt"); // naujas failas
						}

						// Bloko patvirtinimas ir itraukimas i grandine
						processBlock(currentBlock, ug, tgPtr);

						// Isvalome currentBlock, kad kitas blokas butu naujas
						currentBlock.transactions.clear();
						blockGenerated = false;
					}

				}


				//else if (choose == "5") {
					//processBlock(currentBlock, ug, tgPtr);
				//}

				else if (choose == "6") { // baigiamas darbas
					break;
				}

				else {
					cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
					continue;
				}
			}


		}

		else if (uzduotis == "3") { // Baigti darba
			break;
		}

		else {
			cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
			continue;
		}
	}

	return 0;
}

