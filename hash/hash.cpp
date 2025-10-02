<<<<<<< HEAD
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
                cout << "\nIveskite teksta: \n";
                getline(cin, input);  // nuskaitoma eilute

                if (input.empty()) {
                    break;
                }
                // Iskvieciama hash funkcija ir atspausdinamas rezultatas
                cout << "\nSugeneruotas rezultatas:\n" << Hashinimas(input) << endl;
            }
        }

        else if (choice == "2") { // nuskaitomas failas
            string filename = meniuFailai(); // pasirenkamas nuskaitymo failas
            //HASH
            //cout << rezultatas;
        }

        else if (choice == "3") { // testiniu failu paruosimas
            int g = meniuGeneravimas();
            Sugeneruota(gen, g);
        }

        else if (choice == "4") { // baigiamas darbas
            break;
        }

        else { // meniu neteisingo ivedimo isvestis
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
            continue;
        }
    }
    return 0;
}

=======
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
                cout << "\nIveskite teksta: \n";
                getline(cin, input);  // nuskaitoma eilute

                if (input.empty()) {
                    break;
                }
                // Iskvieciama hash funkcija ir atspausdinamas rezultatas
                cout << "\nSugeneruotas rezultatas:\n" << Hashinimas(input) << endl;
            }
        }

        else if (choice == "2") { // nuskaitomas failas
            string filename = meniuFailai(); // pasirenkamas nuskaitymo failas
            //HASH
            //cout << rezultatas;
        }

        else if (choice == "3") { // testiniu failu paruosimas
            int g = meniuGeneravimas();
            Sugeneruota(gen, g);
        }

        else if (choice == "4") { // baigiamas darbas
            break;
        }

        else { // meniu neteisingo ivedimo isvestis
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
            continue;
        }
    }
    return 0;
}

>>>>>>> a4504517df2868f8186b5e8cfedc53a1c4934494
