# Analisi – 060-problema-username.c

## 1. Problema

La segreteria deve creare gli account della piattaforma scolastica per otto
nuovi iscritti. Lo username è formato dall'iniziale del nome seguita dalle
lettere del cognome, tutto in minuscolo e al massimo 8 caratteri. Se lo
stesso username è già stato assegnato si aggiunge una cifra (2, 3, …).

## 2. Analisi

### Input
Nessun input da tastiera: nomi e cognomi sono inizializzati nel codice.

| Variabile | Tipo       | Dimensione | Descrizione                                 |
|-----------|------------|------------|---------------------------------------------|
| `nomi`    | `char[][]` | 8 × 25     | Nome di ogni iscritto                       |
| `cognomi` | `char[][]` | 8 × 25     | Cognome, parallelo a `nomi`                 |

### Output
- Una tabella con nome, cognome e username di ogni iscritto;
- il numero di account creati e quanti hanno ricevuto una cifra.

### Vincoli
- Base dello username: iniziale del nome + solo le lettere del cognome
  (spazi e apostrofi eliminati), tutto in minuscolo, al massimo
  `MAX_BASE` (8) caratteri: i cognomi lunghi vengono troncati
- Se il candidato è già stato assegnato si prova la base con la cifra 2,
  poi 3, e così via, finché non è libero
- La cifra si aggiunge dopo la base, quindi uno username con cifra può
  avere 9 caratteri
- I duplicati si cercano solo tra gli username già assegnati (le prime k
  righe di `usernames`), che è un terzo array parallelo
- Tutte le funzioni sulle stringhe sono scritte a mano

### Assunzioni
- Non ci sono più di 9 iscritti con la stessa base: la cifra è una sola
  (`'0' + numero`)
- I nomi non contengono lettere accentate

### Variabili di supporto

| Variabile    | Tipo       | Dimensione | Descrizione                              |
|--------------|------------|------------|------------------------------------------|
| `usernames`  | `char[][]` | 8 × 25     | Username assegnati, parallelo a `nomi`   |
| `base`       | `char[]`   | 25         | Username senza cifra                     |
| `candidato`  | `char[]`   | 25         | Username da verificare                   |
| `numero`     | `int`      | —          | Cifra da aggiungere (1 = nessuna)        |
| `lung_base`  | `int`      | —          | Posizione in cui scrivere la cifra       |
| `con_numero` | `int`      | —          | Account con cifra aggiunta               |

| Funzione | Descrizione |
|---|---|
| `void crea_base(char dest[], const char nome[], const char cognome[])` | Iniziale + lettere del cognome, max 8 |
| `int gia_presente(const char candidato[], const char elenco[][LUNG], int n)` | 1 se il candidato è tra i primi n |
| `copia`, `lunghezza`, `confronta`, `minuscola`, `e_lettera` | Funzioni di base |

### Algoritmo in linguaggio naturale
Per ogni iscritto k:
1. Costruire la base e copiarla nel candidato; porre `numero = 1`.
2. Finché il candidato è tra gli username già assegnati: incrementare
   `numero`, ricopiare la base e aggiungere la cifra.
3. Se `numero > 1` contare l'account tra quelli con cifra.
4. Salvare il candidato in `usernames[k]` e stampare la riga.

Alla fine stampare il riepilogo.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Tabella degli username
- **Cosa si verifica:** omonimie (mrossi, mrossi2, mrossi3), cognomi con
  spazio e apostrofo, troncamento a 8 caratteri
- **Output atteso:**
```
  Nome         Cognome        Username
  Mario        Rossi          mrossi
  Marco        Rossi          mrossi2
  Anna Maria   De Luca        adeluca
  Giuseppe     D'Amico        gdamico
  Laura        Bianchi        lbianchi
  Francesca    Santangelo     fsantang
  Mattia       Santangelini   msantang
  Mirko        Rossi          mrossi3

Account creati: 8, di cui 2 con cifra aggiunta
```
- **Osservazione:** fsantang e msantang non sono duplicati perché hanno
  iniziali diverse; Mirko Rossi riceve il 3 perché mrossi e mrossi2 sono già
  assegnati
