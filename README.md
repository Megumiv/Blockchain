# Blockchain
## 2-oji užduotis: Supaprastintos blokų grandinės (Blockchain) kūrimas
---------------------------------------------------------------------

## **UŽDUOTIES TIKSLAS:**
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

<br/><br/> Bloko struktūra pateikiama žemiau paveiksliuke:<br/><br/>
<img width="1227" height="758" alt="blockstruct" src="https://github.com/user-attachments/assets/a744a083-4f4d-4bfe-ad0b-9d1ebdd615d9" /> 
<br/>

## ATLIKTAS DARBAS

<br/>**Atlikta pagrindinė užduotis.**
<br/>**+ papildomai: UTXO modelio realizavimas**
<br/>**+ papildomai: Lygiagretus kasimo procesas**<br/>

<br/>Sukurta **centralizuota** blokų grandinė.
<br/>Transakcijų ir bloko kūrimo bei kiti procesai **matomi konsolėje ir failuose.**
<br/>Įgyvendinta **Merkle Tree.**
<br/>Imituojamas **decentralizuotas** kasimas. Bandoma kasti **ribotą bandymų skaičių.**<br/>
<br/>Naudojamos **gerosios OOP praktikos**: aiški klasės struktūra, enkapsuliacija, konstruktoriai, RAII idiomos taikymas.

<br/> <br/>Atliktas darbas iš pradžių leidžia pasirinkti meniu, ar norima 2-osios užduoties funkcionalumo, ar 1-osios (praeitos, skirtos hash kūrimui): <br/> 
<br/>
<img width="458" height="220" alt="prmeniu" src="https://github.com/user-attachments/assets/dc1b44c7-a7c0-485b-b3ce-fcd488f576ba" />


<br/> <br/> Pasirinkus 2-ąją užduotį, rodomas šis meniu: <br/> 
<br/> <img width="391" height="215" alt="image" src="https://github.com/user-attachments/assets/415f9599-16f0-4523-a6f1-110ac79bdf8d" />



## GAUNAMI REZULTATAI

<br/>Žemiau pateikiami išvestų failų rezultatai, kai kur pridėtas ir konsolės vaizdas (rezultatus galime dalinai matyti ir konsolėje paleidus užduotį, tik įrašyti didesni kiekį į failą - greičiau ir patogiau).<br/>

<br/>
IŠVEDAMI SUGENERUOTI VARTOTOJAI (konsolėje, paveiksliuke tik pirmieji matomi faile vartotojai.txt):<br/><br/>
<img width="793" height="444" alt="m1" src="https://github.com/user-attachments/assets/27f975bc-cb6e-4e19-8fe1-675b39bd5248" />
<br/> 
<img width="1085" height="676" alt="t1" src="https://github.com/user-attachments/assets/5f9eaf10-c4c1-4064-a56b-52e9858ad3e0" />

IŠVEDAMOS SUGENERUOTOS TRANSAKCIJOS (konsolėje, paveiksliuke tik pirmieji matomi faile transakcijos.txt):<br/><br/>
<br/><img width="788" height="298" alt="m2" src="https://github.com/user-attachments/assets/48fb11f2-0696-4299-864e-17eec7c766e2" />
<br/><img width="1072" height="675" alt="t2" src="https://github.com/user-attachments/assets/8e535233-81a5-4c61-b0c4-d18766245ff6" />

<br/>IŠVEDAMI SUGENERUOTI BLOKAI (paveiksliuke tik paskutinios iŠvestys konsolėje ir tik pirmieji matomi faile blokas.txt):<br/><br/>
<img width="647" height="409" alt="m3" src="https://github.com/user-attachments/assets/7b3975b1-e45d-40f9-b765-1356bfe0cf0d" />
<br/> <img width="1086" height="674" alt="t3" src="https://github.com/user-attachments/assets/2c7fc439-c01c-459c-8fde-455a4e88faee" />

<br/>IŠVEDAMA SUGENERUOTA GRANDINE (konsolėje, faile grandine.txt):<br/><br/>
<img width="1178" height="409" alt="m4" src="https://github.com/user-attachments/assets/e34807b5-2a33-4aff-8a7b-21b1fef9c11e" />
<br/> <img width="1081" height="277" alt="t4" src="https://github.com/user-attachments/assets/fb31bef6-11b9-4f66-887b-faa571995a68" />



<br/><br/>
## AI NAUDOJIMAS

AI pagalba buvo pasitelkiama šiems žingsniams: klasės sėkmingo kūrimo - naudotos gerosios OOP praktikos, kaip enkapsuliacija, konstruktoriai, RAII idiomos taikymas - užtikrinimui, UTXO modelio kūrimo analizei, grandines realizacijai, bendram kodo optimizavimui, klaidų paieškai.
