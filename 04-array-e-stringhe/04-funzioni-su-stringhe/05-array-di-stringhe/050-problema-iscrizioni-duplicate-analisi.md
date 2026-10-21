# Analisi – 050-problema-iscrizioni-duplicate.c

## 1. Problema

Per la gita d'istituto gli studenti si sono iscritti con un modulo online,
ma alcuni lo hanno inviato più volte scrivendo il nome in modo diverso
(maiuscole, spazi). Bisogna riconoscere i duplicati, indicare per ciascuno
il modulo originale e produrre l'elenco degli iscritti senza ripetizioni.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `moduli` | `char[10][28]` | Nomi come sono stati scritti nei moduli, in ordine di arrivo |

I dati sono inizializzati nel sorgente: il programma non legge nulla da tastiera.

### Output

- Per ogni duplicato: numero e testo del modulo e numero e testo del
  modulo originale.
- Moduli ricevuti, duplicati, iscritti.
- Elenco numerato degli iscritti senza ripetizioni.

### Vincoli

- Due nomi sono uguali se lo sono dopo la normalizzazione: minuscolo,
  spazi iniziali e finali eliminati, un solo spazio tra le parole.
- Il confronto avviene sulle copie normalizzate (`strcmp`), la stampa sugli originali.
- Si conserva il primo modulo inviato, nell'ordine di arrivo.
- Un modulo si confronta solo con quelli precedenti e ci si ferma al primo
  uguale trovato.

### Assunzioni

- Il nome è scritto sempre nell'ordine cognome nome.
- Non si riconoscono errori di battitura: nomi che differiscono anche per
  una sola lettera sono persone diverse.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `normalizzati` | `char[10][28]` | Nomi normalizzati (parallelo a `moduli`) |
| `pulito` | `char[10][28]` | Elenco senza duplicati (array riempito parzialmente) |
| `n_pulito` | `int` | Righe usate di `pulito` |
| `i`, `j` | `int` | Modulo corrente e modulo precedente con cui si confronta |
| `duplicato` | `int` | Flag del modulo corrente |
| `duplicati` | `int` | Totale dei duplicati |

| Funzione | Compito |
|----------|---------|
| `normalizza` | Copia in minuscolo, senza spazi iniziali/finali, con un solo spazio tra le parole |

### Algoritmo in linguaggio naturale

1. Normalizzare tutti i moduli.
2. Per ogni modulo `i`:
   1. confrontarne la copia normalizzata con quelle dei moduli `j < i`,
      fermandosi al primo uguale;
   2. se è un duplicato stamparlo con il modulo originale e incrementare `duplicati`;
   3. altrimenti copiarlo in `pulito`.
3. Stampare i totali e l'elenco pulito.
4. In `normalizza`: copiare in minuscolo ogni carattere diverso dallo spazio;
   copiare uno spazio solo se il carattere precedentemente copiato non è
   uno spazio e non si è all'inizio; alla fine togliere l'eventuale spazio finale.

## 3. Casi di test

### Test 1 – Maiuscole diverse

- **Cosa si verifica**: due nomi che differiscono solo per le maiuscole.
- **Input**: modulo 1 `Rossi Mario`, modulo 3 `ROSSI MARIO` (dati del sorgente).
- **Valori intermedi attesi**: entrambi normalizzati in `rossi mario`.
- **Output atteso**:
  ```
    modulo  3 [ROSSI MARIO] e' un duplicato del modulo 1 [Rossi Mario]
  ```

### Test 2 – Spazi iniziali, finali e doppi

- **Cosa si verifica**: la normalizzazione degli spazi.
- **Input**: modulo 5 `  bianchi  sara`, modulo 9 `Verdi  Luca `.
- **Valori intermedi attesi**: normalizzati in `bianchi sara` e `verdi luca`.
- **Output atteso**:
  ```
    modulo  5 [  bianchi  sara] e' un duplicato del modulo 2 [Bianchi Sara]
    modulo  9 [Verdi  Luca ] e' un duplicato del modulo 4 [Verdi Luca]
  ```

### Test 3 – Nome identico

- **Cosa si verifica**: un modulo inviato due volte con lo stesso testo.
- **Input**: moduli 6 e 10 `Neri Anna`.
- **Output atteso**:
  ```
    modulo 10 [Neri Anna] e' un duplicato del modulo 6 [Neri Anna]
  ```

### Test 4 – Nomi simili ma diversi

- **Cosa si verifica**: basta una lettera diversa perché siano due iscritti.
- **Input**: `Rossi Mario` e `Rossi Maria`.
- **Output atteso**: nessuna riga di duplicato per il modulo 8; entrambi
  compaiono nell'elenco degli iscritti.

### Test 5 – Elenco pulito

- **Cosa si verifica**: totali e ordine di arrivo dell'elenco finale, con il
  testo del primo modulo inviato.
- **Input**: dati del sorgente.
- **Output atteso**:
  ```
  Moduli ricevuti: 10, duplicati: 4, iscritti: 6
  Elenco degli iscritti:
    1. Rossi Mario
    2. Bianchi Sara
    3. Verdi Luca
    4. Neri Anna
    5. Gallo Paolo
    6. Rossi Maria
  ```
