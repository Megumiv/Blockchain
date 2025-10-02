# Blockchain. Hash Generatorius



**Maišos funkcija (hash function)** – tai algoritmas, kuris bet kokį įvedimą (input) paverčia fiksuoto dydžio pseudoatsitiktiniu simbolių rinkiniu (maišos kodu), tarsi „piršto atspaudu“.



<br/> **Sukurta hash funkcija atitinka šiuos reikalavimus:**    

1\. Įvedimas – bet kokio ilgio eilutė (string).

2\. Rezultatas – visada vienodo dydžio (64 simboliai hex formatu).

3\. Deterministiškumas – tas pats įvedimas = tas pats rezultatas.

4\. Efektyvumas – turi veikti pakankamai greitai.

5\. Atsparumas kolizijoms.

6\. Lavinos efektas (angl. Avalanche effect).

7\. Negrįžtamumas – iš hash’o praktiškai neįmanoma atspėti pradinio teksto.



## Pseudokodas (hash)

Funkcija Hashinimas(tekstas):
    // 1. Nustatome pradinę hash reikšmę
    hash = 0xABCDEF1234567890   // 64 bitų pradinis skaičius

    // 2. Per kiekvieną simbolį tekste atliekamas maišymas
    kiekvienam simboliui c iš teksto:
        hash = hash * 131 + (ASCII(c) << 8)   // padidiname ir pridedame simbolį
        hash = hash XOR (hash >> 17)          // XOR su paslinkta versija

    // 3. Iš hash gauname galutinį rezultatą (64 simbolių eilutę)
    rezultatas = ""

    kartok 4 kartus:
        // pasukame hash bitus 15 pozicijų į kairę
        hash = (hash << 15) | (hash >> (64 - 15))

        // paverčiame hash į 16 simbolių hex eilutę
        hexEilute = ""
        laikinas = hash
        kartok 16 kartus:
            simbolis = hex[laikinas % 16]      // pasiimame paskutinius 4 bitus
            įrašome simbolį į eilutę iš galo
            laikinas = laikinas >> 4
        hexEilute = gauta 16 simbolių eilutė

        rezultatas = rezultatas + hexEilute

    grąžinti rezultatas   // tai bus 64 simbolių hash



<br/><br/>
## TYRIMO REZULTATAI IR IŠVADOS

<br/> **EFEKTYVUMO MATAVIMAS:** <br/>
<br/>![ ](<Screenshot 2025-10-02 132852.png>)
<br/>![ ](<Screenshot 2025-10-02 133425.png>)

<br/>**KOLIZIJU PAIESKA.** <br/> Rezultatas - 0 kolizijų.
<br/> ![alt text](<Screenshot 2025-10-02 133000-1.png>)


<br/> **NEGRĮŽTAMUMAS** <br/>
<img width="1033" height="156" alt="Screenshot 2025-10-02 141115" src="https://github.com/user-attachments/assets/60cbab20-b6ce-447c-bd89-c1bd95166973" />

<br/> **LAVINOS EFEKTAS** <br/>
UŽDUOTIS:
- sugeneruok 100 000 porų, kurios skiriasi tik vienu simboliu,
- pamatuok, kiek procentų skiriasi gautieji porų hash'ai:
- -bit'ų lygmeniu,
- -hex’ų lygmeniu.
- parodyk minimalias, maksimalias ir vidutines skirtingumo reikšmes.
<br/> REZULTATAS:
<img width="632" height="334" alt="Screenshot 2025-10-02 141549" src="https://github.com/user-attachments/assets/458a41b1-cd33-4d6f-bcc8-660f62061b95" />



<br/><br/>
**Hash stiprybės:**
- Net mažiausias įvesties pasikeitimas (vienas simbolis) labai pakeičia galutinį hash rezultatą (aukštas „avalanching“ efektas).
- Fiksuotas ilgis: nepriklausomai nuo įvesties ilgio, rezultatas visada 64 simbolių.
<br/>
**Hash silpnybės:**
- Naudoja paprastą daugybą ir XOR, todėl gali būti pažeidžiamas prieš deterministines atakas, jei įvestis ribota arba modeliuojama.
- Rotacijos ir XOR nėra pakankamai stiprūs kriptografiškai: palyginti su profesionaliomis hash funkcijomis (pvz., SHA-256), šios operacijos nesuteikia aukšto atsparumo atakoms.


**GAUTA** <br/>
(Generuojami) testiniai failai:
- failai su vienu simboliu (pvz. a , b ),
- failai su daug (>1000) atsitiktinių simbolių,
- failai su daug (>1000) atsitiktinių simbolių, kurie skiriasi tik vienu (pvz. viduriniu) simboliu,
- tuščias failas.

<br/>
Patikrinamas išvedimo dydis – nepriklausomai nuo įvedimo, rezultatas visada tokio pat ilgio.
<br/>
Deterministiška.
<br/>

Yra pasirinkimo meniu naudojimo palengvinimui. <br/>
<img width="493" height="223" alt="Screenshot 2025-10-02 141420" src="https://github.com/user-attachments/assets/c2cd4a85-248b-448a-99d1-ad78989816f0" />





