# Analisi – 080-problema-distanze-citta.c

## 1. Problema

Una tabella a doppia entrata riporta le distanze stradali tra 6 città.
Il programma deve verificare che la tabella sia coerente (diagonale nulla e
simmetria), trovare per ogni città la più vicina, la coppia più lontana e la
lunghezza di un itinerario indicato come sequenza di città.

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile    | Tipo       | Dimensione | Descrizione                                    |
|--------------|------------|------------|------------------------------------------------|
| `distanze`   | `int[][]`  | 6 × 6      | Km tra la città riga e la città colonna        |
| `citta`      | `char[][]` | 6 × 14     | Nomi: valgono sia per le righe sia per le colonne |
| `itinerario` | `int[]`    | 5          | Indici delle città nell'ordine di visita       |

Itinerario: Alessandria → Pavia → Milano → Asti → Torino.

### Output
- Gli eventuali errori della tabella e l'esito della verifica
  ("verificate" oppure "ERRORI");
- per ogni città la più vicina, con la distanza;
- la coppia di città più lontane;
- i tratti dell'itinerario con i km e il totale.

### Vincoli
- La tabella è coerente se la diagonale è tutta a zero e se
  `distanze[i][j] == distanze[j][i]`; per la simmetria basta controllare le
  celle sopra la diagonale (j > i)
- La città più vicina è il minimo della riga **escludendo la diagonale**:
  l'ipotesi iniziale è la prima colonna diversa da i
- La coppia più lontana si cerca solo sopra la diagonale, perché ogni coppia
  compare due volte nella matrice
- Un tratto dell'itinerario va dalla tappa t alla tappa t + 1: la distanza
  è nella riga `itinerario[t]` e nella colonna `itinerario[t + 1]`; i tratti
  sono `TAPPE − 1`
- A parità vince la prima città o coppia trovata

### Assunzioni
- Le distanze sono positive e approssimate al chilometro
- Gli indici dell'itinerario sono validi

### Variabili di supporto

| Variabile     | Tipo        | Descrizione                                |
|---------------|-------------|--------------------------------------------|
| `coerente`    | `int` (0/1) | Esito della verifica                       |
| `piu_vicina`  | `int`       | Colonna del minimo nella riga corrente     |
| `i_max`, `j_max` | `int`    | Coppia più lontana                         |
| `km_totali`   | `int`       | Lunghezza dell'itinerario                  |
| `CITTA`, `TAPPE` | `#define`| 6, 5                                       |

### Algoritmo in linguaggio naturale
1. Per ogni città: se la distanza da sé non è 0 segnalarlo; per ogni città
   successiva, se le due distanze simmetriche sono diverse segnalarlo.
   Stampare l'esito.
2. Per ogni riga i partire dalla prima colonna diversa da i e cercare il
   minimo tra le colonne j ≠ i; stampare la città più vicina.
3. Scorrere le celle con j > i e cercare il massimo; stampare la coppia.
4. Per ogni tratto dell'itinerario leggere la distanza, stamparla e
   sommarla; stampare il totale.

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; il Test 3
richiede di modificare la tabella e ricompilare.

### Test 1 – Verifica e città più vicine
- **Cosa si verifica:** la diagonale (0) non viene scelta come minimo
- **Output atteso:**
```
Diagonale nulla e simmetria: verificate

--- Citta' piu' vicina ---
  Alessandria  -> Asti           37 km
  Asti         -> Alessandria    37 km
  Genova       -> Alessandria    80 km
  Milano       -> Pavia          38 km
  Torino       -> Asti           60 km
  Pavia        -> Milano         38 km
```

### Test 2 – Coppia più lontana e itinerario
- **Output atteso:**
```
Coppia piu' lontana: Genova - Torino (170 km)

--- Itinerario ---
  Alessandria  -> Pavia          63 km
  Pavia        -> Milano         38 km
  Milano       -> Asti          125 km
  Asti         -> Torino         60 km
  Totale: 286 km
```

### Test 3 – Tabella non simmetrica
- **Cosa si verifica:** la verifica individua l'errore di trascrizione
- **Procedura:** nella riga di Asti cambiare la distanza da Torino da 60 a 65
- **Output atteso:** `Errore: Asti-Torino = 65 ma Torino-Asti = 60` e
  `Diagonale nulla e simmetria: ERRORI`
- **Osservazione:** il messaggio di errore compare prima del titolo della
  tabella, perché la verifica precede la stampa dell'intestazione
