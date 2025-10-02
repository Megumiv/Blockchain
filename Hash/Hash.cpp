#include "Header.h"


int main() {
	cout << "--- HASH GENERATORIUS ---";

	random_device rd;
	mt19937 gen(rd());

	while (true) {
		meniu();

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
			cout << "Iveskite teksta demonstracijai: ";
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
	return 0;
}

