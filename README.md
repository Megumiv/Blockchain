# 4-asis darbas: išmaniosios sutarties ir decentralizuotos aplikacijos kūrimas

## TIKSLAS IR REIKALAVIMAI

Pagrindinis šios užduoties tikslas yra sukurti išmaniąją sutartį (angl. smart contract), kuri įgyvendintų tam tikrą verslo logiką ir galėtų užtikrinti jos "saugų" ir "patikimą" funkcionavimą decentralizuotame viešąjame tinkle. 

Išmaniosios sutarties valdymui ir verslo proceso dalyvių tarpusavio sąveikai palengvinti bus kuriama decentralizuota aplikacija su Front-End .

Šioje užduotyje išmanioji sutartis įgyvendinama **Solidyti** programavimo kalba ir turi būti adaptuota Ethereum blockchain tinklui. Šiai užduočiai atlikti Jums reikės:
- Išmaniosios sutarties kūrimui rekomenduojama naudoti "on-line" įrankį **Remix IDE**,
- o testavimui ir diegimui Truffle IDE, kurį reikia įdiegti į savo kompiuterį.
- Decentralizuotos aplikacijos testavimui galite naudoti Ganache įrankį, kuris sukuria lokalų
Ethereum tinklą.
- Jums taip pat prireiks kliento MetaMask, kuris įgalins sąsają su Ethereum tinklu.
- Išmaniosios sutarties testavimui naudokite lokalų ir viešąjį Ethereum testinius tinklus (angl.
testnet), pvz., Sepolia.




## DARBO EIGA

1. Realizuokite **verslo logiką išmanioje sutartyje Solidyti kalboje.**
2. Ištestuokite išmaniosios sutarties veikimą **Ethereum lokaliame tinkle.**
3. Ištestuokite išmaniosios sutarties veikimą **Ethereum testiniame tinkle** (pvz., Sepolia).
4. Naudojant Ethereum testinio tinklo Etherscan peržiūrėkite išmaniosios sutarties vykdymo
**"logus".**
5. Sukurkite decentralizuotos aplikacijos **Front-End** (tinklapį arba mobiliąją aplikaciją), kuri
įgalintų bendravimą su išmaniąja sutartimi.



## ATLIKTA UžDUOTIS 

Pasirinktas **kitas sukurtas verslo modelis** nei pavyzdyje (**papildomiems balams**) ir jo pagrindu įgyvendinta išmanioji sutartis.
**Papildomai** - aprašomas išsamiau su scenarijais, sekų diagrama (angl. Sequence diagram) čia, ReadME faile.
**Sukurtas decentralizuotos aplikacijos Front-End.**

Išmanioji sutartis užtikrina:
- skaidrų mokėjimų valdymą,
- pasitikėjimo nereikalaujantį atsiskaitymą,
- aiškiai apibrėžtą paslaugos vykdymo procesą.



  
## VERSLO MODELIO APRAŠYMAS

Ši sukurta išmanioji sutartis leidžia bet kokiam **užsakovui** (kode - **client**) saugiai užsisakyti paslaugas, o **samdomam specialistui / pardavėjui / tiekėjui** ( kode - **freelancer**) jas atlikti. Mokėjimas laikomas išmaniojoje sutartyje pavadinimu **eSutartis**, kuri užtikrina, kad pinigai bus pervesti **tik atlikus užduotį ir tai patvirtinus**, su galimybe užduotį atšaukti.

ŠALYS:
- Užsakovas (client) - Sukuria užduotį - užsako paslaugą, sumoka ETH, patvirtina atliktą darbą
- Specialistas (freelancer) - Priima užduotį, atlieka ją, pažymi kaip atliktą
- Išmanioji sutartis (eSutartis) - Laiko pinigus escrow, valdo užduočių statusus, saugo verslo logiką ir perveda lėšas




## GALIMI VERSLO MODELIO SCENARIJAI


A SCENARIJUS. **SĖKMINGAS DIZAINO KŪRIMO UŽSAKYMAS**
   1. Klientas (gali būti įmonė) turi svetainės dizaino sukūrimo poreikį - jis sukuria dizaino užduotį. Perveda ETH į eSutartis.
   2. Specialistas, išmanantis šią sritį priima užduotį ir ją atlieka - sukuria reikiamo dizaino failus.
   3. Specialistas tuomet pažymi sistemoje užduotį kaip atliktą.
   4. Klientui (įmonės atstovui) patvirtinus atliktą darbą, pervedami ETH specialistui.


B SCENARIJUS. **NESĖKMINGAS DESERTŲ KEPINIŲ UŽSAKYMAS**
   1. Klientas nori užsakyti itin didelį pyragaičių kiekį svarbiems asmenims, turi specialių ir griežtų reikalavimų, ilgą alergenų sąrašą. Sukuria užduotį sistemoje ir perveda ETH į eSutartis.
   2. Kepėjas priima užduotį, bet po detalaus planavimo supranta, kad negalės įvykdyti dėl ribotų resursų / griežtų reikalavimų / didelės rizikos.
   3. Kepėjas pažymi sistemoje, kad užduotis negali būti atlikta.
   4. eSutartis grąžina pinigus klientui.




## SEKŲ EIGA

Verslo modelio šalių tarpusavio sąveikos seka aprašyta žemiau su detalesniais komentarais bei po juo pavaizduota **sekų diagrama (angl.
Sequence diagram).** 


1. Užduoties kūrimas - **createTask()**
   - Client sukuria užduotį ir siunčia ETH į sutartį.
   - Sutartis įrašo užduotį ir užrakina pinigus.
   - Užduoties statusas = open.

2. Užduoties priėmimas - **acceptTask()**
   - Freelancer priima užduotį.
   - Sutartis pakeičia užduoties būseną į InProgress.

3. Užduoties atlikimas - **markCompleted()**
   - Freelancer pažymi užduotį kaip Completed.
   - Sutartis atnaujina būseną.

4. Mokėjimo patvirtinimas - **confirmAndPay()**
   - Client patvirtina atliktą darbą.
   - Sutartis perveda ETH freelancer’ui ir pažymi užduotį kaip Paid.
  
5. Atšaukimas - **cancelTask()**
   - Client arba Freelancer gali atšaukti užduotį, jei ji dar nėra pilnai atlikta (Open arba   InProgress).
   - eSutartis atnaujina statusą į Cancelled.
   - ETH grąžinamas Klientui.



### Sekų diagrama (angl.Sequence diagram)
<br/>
<br/> **Sekų diagramos (angl. Sequence diagram)** vaizdavimui pasirinkta išbandyti internetinius tekstinių diagramų įrankius: https://sequencediagram.org/ ir 
https://www.planttext.com/. Gautas rezultatas vaizduojamas žemiau pasitelkus antrąją PlantUML priemonę (naršyklės versija - https://www.planttext.com/).<br/>

<img width="425" height="542" alt="image" src="https://github.com/user-attachments/assets/095053bf-aa8a-4739-ba06-53a1d402b7fe" /> <br/>


<br/> 
Naudotas tekstas diagramai gauti: <br/>
<img width="473" height="419" alt="image" src="https://github.com/user-attachments/assets/f2ffada0-b0e7-4365-91e0-af0564d2410e" /> <br/>


## TESTAVIMAS EUTHEREUM LOKALIAME TINKLE 

Testavimas buvo sėkminags.
Išmaniosios sutarties veikimas ištestuotas Euthereum lokaliame tinkle - REMIX VM (Prague).
Žemiau pateiktos testavimo ekrano nuotraukos:
<br/>


<img width="1919" height="992" alt="Screenshot 2026-01-06 024906" src="https://github.com/user-attachments/assets/0ae4b0e1-f8f1-462f-a20c-a59b74ea8142" /> <br/>

<img width="1917" height="991" alt="Screenshot 2026-01-06 024958" src="https://github.com/user-attachments/assets/e4ef1a6c-306a-4e3f-8581-7b28ab71969d" /> <br/>

<img width="996" height="707" alt="Screenshot 2026-01-06 025302" src="https://github.com/user-attachments/assets/806c5b89-6a9f-4165-a167-b3431b83867d" /> <br/>

<img width="1001" height="710" alt="Screenshot 2026-01-06 025314" src="https://github.com/user-attachments/assets/0613b255-4ce0-46d6-9989-3750c383ca5d" /> <br/>

<img width="306" height="201" alt="Screenshot 2026-01-06 030544" src="https://github.com/user-attachments/assets/4f49d668-a89a-4f1e-a860-3e25fdcaea74" /> <br/>

<img width="319" height="256" alt="image" src="https://github.com/user-attachments/assets/55163134-03a5-459d-967b-73c1f3de34c5" /> <br/>

<img width="1919" height="992" alt="Screenshot 2026-01-06 031052" src="https://github.com/user-attachments/assets/9d17a3ad-66a4-419a-bc5b-ea7b747de58e" /> <br/>





## TESTAVIMAS ETHEREUM TESTINIAME TINKLE - SEPOLIA

Buvo atliktas kitas testavimas - Ethereum testiniame tinkle - **Sepolia.**

Naudotasi **MetaMask.** Testiniame Sepolia tinkle, turimoje piniginėje gauti testavimo ETH (0,05 SepoliaETH):
<img width="1911" height="959" alt="Screenshot 2026-01-06 055552" src="https://github.com/user-attachments/assets/fb3a004d-4922-45ad-80e5-6ac38f3b6a7c" /> <br/>

REMIX programa buvo sujungta su MetaMask pinigine bei pasirinkta Sepolia aplinka per REMIX testavimo tikslais (tai ne localhost, o realus testinis tinklas Sepolia):
<img width="444" height="380" alt="Screenshot 2026-01-06 062514" src="https://github.com/user-attachments/assets/2da9e1e8-ddb7-4ea5-9851-63f11b3ba22f" /> <br/>





TESTAVIMAS:

Paspausta "deploy". Vaizdas REMIX programoje ir MetaMask patvirtinimo reikėjimas vaizduojamas nuotraukose žemiau bei rezultatas:

<img width="1919" height="1013" alt="Screenshot 2026-01-06 062926" src="https://github.com/user-attachments/assets/4454bba0-79e4-4f84-9645-34a08b76e929" /> <br/>

<img width="464" height="894" alt="Screenshot 2026-01-06 063001" src="https://github.com/user-attachments/assets/7395cccc-d972-43d4-af1f-7f0c51f9733e" /> <br/>

<img width="467" height="881" alt="Screenshot 2026-01-06 063041" src="https://github.com/user-attachments/assets/407d05ee-9764-47a1-b99d-f9dd37f1f94f" /> <br/>

<img width="1437" height="395" alt="Screenshot 2026-01-06 063110" src="https://github.com/user-attachments/assets/827ca3c7-24b2-4380-b341-0ce84ea51615" /> <br/>



Deploy'into kontrakto funkcijos REMIX programoje:

<img width="357" height="657" alt="image" src="https://github.com/user-attachments/assets/bbbf9a86-b2c9-4a25-8b4f-af658c2f3be6" /> <br/>



Nukopijuotas kontrakto adresas (angl. contract address) tolimesniam testavimui:

<img width="1480" height="676" alt="Screenshot 2026-01-06 063156" src="https://github.com/user-attachments/assets/6c7d3171-0334-4253-8176-24048c2832ef" /> <br/>



AcceptTask, markCompleted, getTask, createTask suveikė sėkmingai. Tačiau paskutinis žingsnis - confirmAndPay - nepavyko. Rezultatai žemiau ekrano nuotraukose:

<img width="1474" height="866" alt="Screenshot 2026-01-06 064809" src="https://github.com/user-attachments/assets/760779fc-e529-48d1-97ac-cf85e54a24e7" /> <br/>

<img width="446" height="428" alt="Screenshot 2026-01-06 065004" src="https://github.com/user-attachments/assets/48763a40-2f18-4a9e-b646-a10d62c253db" /> <br/>




## ETHERSCAN IR SUTARTIES VYKDYMO "LOGS"

Taip pat peržiūrėti vykdymo rezultatai per ETHEREUM ETHERSCAN. Siekant matyti šią informaciją, iš seniau REMIX buvo nukopijuotas kontrakto adresas (0x28c07321731487072a7e0c52437f93882fdbb6be), pagal kurį tai randama. Rezultatai pateikiami žemiau.

<img width="1402" height="936" alt="Screenshot 2026-01-06 065043" src="https://github.com/user-attachments/assets/7e6192a9-7bab-4249-a14c-584cfd01c2eb" /> <br/>

<img width="1393" height="562" alt="Screenshot 2026-01-06 065102" src="https://github.com/user-attachments/assets/494c7141-24d0-492b-a4ae-aecd045c60b6" /> <br/>





