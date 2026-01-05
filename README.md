# Blockchain
## 2-oji užduotis: Supaprastintos blokų grandinės (Blockchain) kūrimas
---------------------------------------------------------------------

**UŽDUOTIES TIKSLAS:**
<br/>Sukurti supaprastintą blokų grandinę, imituojančią jos veikimą realiomis sąlygomis.<br/>
Blokų grandinė yra nuoseklus blokų sąrašas, kuriame kiekvienas blokas susietas su ankstesnio bloko maišos reikšme (hash).<br/>
Kiekvienas blokas turi dvi dalis: antraštę (Header) ir turinį (Body).

## UŽDUOTIES ATLIKTI REIKALAVIMAI

Sukurta blokų grandinė atitinka šiuos eigos punktus:
 1. Generuoja vartotojus (~1000)
    - vardas
    - public_key (viešasis raktas)
    - balansas (atsitiktinis nuo 100 iki 1 000 000)
 2. Transakcijų generavimas (~10 000 įrašų) - NAUDOJAMAS UTXO MODELIS (papildomiems balams)
    - transaction_id (kitų laukų hash)
    - sender (siuntėjo raktas)
    - receiver (gavėjo raktas)
    - amount (siunčiama suma)
 3. Naujo bloko formavimas:
 4. Bloko kasimas (Proof-of-Work)
 5. Bloko patvirtinimas ir įtraukimas

<br/><br/> Bloko struktūra pateikiama žemiau paveiksliuke:<br/>
<img width="1227" height="758" alt="blockstruct" src="https://github.com/user-attachments/assets/a744a083-4f4d-4bfe-ad0b-9d1ebdd615d9" /> 
<br/>

## ATLIKTAS DARBAS

<br/>Atlikta pagrindinė užduotis.
<br/>+ papildomai: UTXO modelio realizavimas<br/>

<br/>Sukurta **centralizuota** blokų grandinė.
<br/>Transakcijų ir bloko kūrimo bei kiti procesai **matomi konsolėje ir failuose.**
<br/>Įgyvendinta **Merkle Tree.**
<br/>Imituojamas **decentralizuotas** kasimas. Bandoma kasti **ribotą bandymų skaičių.**<br/>



<br/> <br/>Atliktas darbas iš pradžių leidžia pasirinkti meniu, ar norima 2-osios užduoties funkcionalumo, ar 1-osios (praeitos, skirtos hash kūrimui): <br/>
<img width="458" height="220" alt="prmeniu" src="https://github.com/user-attachments/assets/dc1b44c7-a7c0-485b-b3ce-fcd488f576ba" />


<br/> <br/> Pasirinkus 2-ąją užduotį, rodomas šis meniu: <br/>
<img width="795" height="237" alt="blmeniu" src="https://github.com/user-attachments/assets/f20be7fd-c340-4b8e-8d5f-406d40eb0e6d" />


<br/><br/>
## AI NAUDOJIMAS

AI pagalba buvo pasitelkiama šiems žingsniams: klasės sėkmingo kūrimo - naudotos gerosios OOP praktikos, kaip enkapsuliacija, konstruktoriai, RAII idiomos taikymas - užtikrinimui, UTXO modelio kūrimo analizei, bloko kasimo realizacijai (iš dalies), bendram kodo optimizavimui, klaidų paieškai.
