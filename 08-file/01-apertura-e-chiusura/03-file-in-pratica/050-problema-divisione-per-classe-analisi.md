# Analisi – 050-problema-divisione-per-classe.c

## 1. Problema

Gli iscritti al corso di primo soccorso arrivano in un unico elenco
`classe cognome`, in ordine sparso. Il programma tiene aperti insieme i
file di tutte le classi incontrate (`classe-3A.txt`, ...): per ogni
iscritto cerca la classe, apre il suo file se la classe è nuova e vi
scrive il cognome. Alla fine chiude tutti i file e ne stampa il contenuto.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `classe` | testo | Classe dell'iscritto, fino a 7 caratteri; `FINE` termina |
| `cognome` | testo | Cognome, senza spazi, fino a 29 caratteri |

### Output

- Un file `classe-XX.txt` per classe, con un cognome per riga.
- `File creati: N, iscritti scartati: S`, poi per ogni classe
  `--- classe-XX.txt (iscritti: K) ---` e il contenuto del file.
- Su `stderr`: `  scartato COGNOME (CLASSE)` quando non si può aprire un
  altro file, `  impossibile creare NOME`.

### Vincoli

- I file aperti sono al massimo 8 (`MAX_CLASSI`): un array di `FILE *`
  tiene un file aperto per classe fino alla fine; un iscritto di una nona
  classe si scarta.
- Il nome della classe si converte in maiuscolo: `3a` e `3A` finiscono
  nello stesso file.
- Il nome del file si costruisce con `sprintf` in 30 caratteri.
- Tutti i file si chiudono con `fclose` prima di rileggerli.
- I file si aprono in `"w"`: ogni esecuzione rifà gli elenchi.

### Assunzioni

- L'input contiene coppie complete classe-cognome; una classe senza
  cognome alla fine dell'input si ignora.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `classi` | `char[8][8]` | Classi incontrate |
| `file` | `FILE *[8]` | File aperto di ogni classe |
| `conta` | `int[8]` | Iscritti scritti in ogni file |
| `n` | `int` | Classi (file aperti) |
| `k` | `int` | Indice della classe cercata, -1 se nuova |
| `nome_file` | `char[30]` | Nome costruito con `sprintf` |
| `scartati` | `int` | Iscritti non scritti |

| Funzione | Compito |
|----------|---------|
| `cerca(classi, n, classe)` | Indice della classe, -1 se non c'è |
| `ricopia(nome)` | Stampa il contenuto di un file |

### Algoritmo in linguaggio naturale

1. Leggere coppie classe-cognome fino a `FINE` o alla fine dell'input.
2. Convertire la classe in maiuscolo e cercarla; se è nuova e c'è posto,
   aprire il suo file in `"w"` e aggiungerla.
3. Se la classe ha un file, scrivere il cognome e contarlo; altrimenti
   scartare l'iscritto.
4. Chiudere tutti i file, stampare il riepilogo e il contenuto di ogni
   file.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Iscritti al corso

- **Input:** `3A Rossi 4B Bianchi 3A Verdi 5C Neri`,
  `4B Russo 3A Gallo 5C Costa FINE`
- **Output atteso:**
  ```
  Iscritti (classe cognome, FINE per terminare):

  File creati: 3, iscritti scartati: 0
  --- classe-3A.txt (iscritti: 3) ---
  Rossi
  Verdi
  Gallo
  --- classe-4B.txt (iscritti: 2) ---
  Bianchi
  Russo
  --- classe-5C.txt (iscritti: 2) ---
  Neri
  Costa
  ```

### Test 2 – Minuscole e troppe classi

- **Input:** `3a Rossi 3A Verdi 1A x 2A x 3B x 4B x 5B x 1C x 2C x 9Z Neri`,
  poi fine input
- **Valori intermedi attesi:** `3a` diventa `3A`; le classi 3A, 1A, 2A,
  3B, 4B, 5B, 1C, 2C occupano gli 8 file; 9Z non ha posto.
- **Output atteso:** `  scartato Neri (9Z)` su `stderr`;
  `File creati: 8, iscritti scartati: 1`; `classe-3A.txt` contiene
  `Rossi` e `Verdi`.
