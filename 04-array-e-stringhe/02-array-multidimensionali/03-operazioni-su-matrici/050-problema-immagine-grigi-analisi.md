# Analisi – 050-problema-immagine-grigi.c

## 1. Problema

Un'immagine in scala di grigi di 6 × 10 pixel (una freccia verso destra)
è rappresentata da una matrice di luminosità da 0 a 255. Il programma deve
mostrarla a schermo con caratteri di diversa "pienezza", calcolarne la
luminosità media e applicare tre operazioni: negativo, soglia (bianco/nero)
e specchio orizzontale.

## 2. Analisi

### Input
Nessun input da tastiera: l'immagine è inizializzata nel codice.

| Variabile   | Tipo      | Dimensione | Descrizione                                    |
|-------------|-----------|------------|------------------------------------------------|
| `originale` | `int[][]` | 6 × 10     | Luminosità dei pixel (0 nero, 255 bianco)      |

### Output
- L'immagine originale disegnata a caratteri e la luminosità media;
- il negativo;
- la versione a soglia, solo bianco o nero;
- lo specchio orizzontale (la freccia punta a sinistra).

Ogni pixel si disegna con due caratteri secondo il suo livello:

| Livello (`valore / 52`) | 0 | 1 | 2 | 3 | 4 |
|---|---|---|---|---|---|
| Carattere | spazi | `..` | `oo` | `OO` | `@@` |

### Vincoli
- L'immagine originale non viene modificata: ogni operazione scrive in
  `risultato`
- Negativo: ogni pixel diventa `255 − valore`
- Soglia: bianco se il valore è **strettamente** maggiore di 128, nero
  altrimenti
- Specchio: in ogni riga la colonna c si scambia con `LARGHEZZA − 1 − c`,
  solo per la prima metà delle colonne (altrimenti ogni coppia verrebbe
  scambiata due volte e l'immagine tornerebbe com'era)
- La media si accumula in un `long` e si calcola con una divisione reale

### Assunzioni
- Tutti i valori sono tra 0 e 255, quindi il livello è tra 0 e 4

### Variabili di supporto

| Variabile   | Tipo      | Dimensione | Descrizione                            |
|-------------|-----------|------------|----------------------------------------|
| `risultato` | `int[][]` | 6 × 10     | Matrice di lavoro di ogni operazione   |
| `livello`   | `int`     | —          | Luminosità ridotta a 0–4               |
| `somma`     | `long`    | —          | Accumulatore per la media              |
| `appoggio`  | `int`     | —          | Variabile per lo scambio               |
| `ALTEZZA`, `LARGHEZZA`, `BIANCO`, `NERO`, `SOGLIA` | `#define` | — | 6, 10, 255, 0, 128 |

### Algoritmo in linguaggio naturale
1. Disegnare l'originale convertendo ogni pixel in livello e carattere, e
   sommare i valori; stampare la media.
2. Negativo: riempire `risultato` con `255 − originale` e disegnarlo.
3. Soglia: riempire `risultato` con 255 o 0 e disegnarlo (`@@` o spazi).
4. Specchio: copiare l'originale in `risultato`, poi in ogni riga scambiare
   le colonne simmetriche della prima metà; disegnarlo.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Originale e media
- **Output atteso:**
```
  |          OO        |
  |          @@OO      |
  |..........@@@@@@    |
  |..........@@@@@@    |
  |          @@OO      |
  |          OO        |
Luminosita' media: 74.0
```

### Test 2 – Negativo
- **Cosa si verifica:** lo sfondo scuro diventa chiaro e viceversa
- **Output atteso:**
```
  |@@@@@@@@@@..@@@@@@@@|
  |@@@@@@@@@@  ..@@@@@@|
  |oooooooooo      @@@@|
  |oooooooooo      @@@@|
  |@@@@@@@@@@  ..@@@@@@|
  |@@@@@@@@@@..@@@@@@@@|
```

### Test 3 – Soglia
- **Cosa si verifica:** l'asta (valore 100, sotto la soglia) scompare, resta
  solo la punta
- **Output atteso:**
```
  |          @@        |
  |          @@@@      |
  |          @@@@@@    |
  |          @@@@@@    |
  |          @@@@      |
  |          @@        |
```

### Test 4 – Specchio orizzontale
- **Output atteso:**
```
  |        OO          |
  |      OO@@          |
  |    @@@@@@..........|
  |    @@@@@@..........|
  |      OO@@          |
  |        OO          |
```
