# Analisi – 070-problema-cronometro.c

## 1. Problema

Alla gara dei 100 metri stile libero il cronometrista inserisce per ogni
atleta minuti, secondi e decimi. Il programma trasforma ogni tempo in
decimi di secondo (tipo `Decimi`), trova il vincitore e stampa il distacco
di ogni atleta dal migliore nel formato m'ss"d.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `minuti`, `secondi`, `decimi` | `int` | Tempo di un atleta, tre numeri sulla stessa riga |
| `nomi` | `const char *[5]` | Atleti (nel sorgente): Bianchi, Esposito, Ferrari, Russo, Colombo |

### Output

- Per ogni tempo non valido: `Tempo non valido, ripetere.`
- Il vincitore con il suo tempo.
- Una tabella con atleta, tempo e distacco dal vincitore (`+0'00"0` per il
  vincitore).
- Se l'input termina prima dei cinque tempi: `Inserimento interrotto.` e
  nessuna classifica.

### Vincoli

- I tempi sono memorizzati come `Decimi` (`typedef int Decimi;`):
  `(minuti * 60 + secondi) * 10 + decimi`.
- Minuti non negativi, secondi da 0 a 59, decimi da 0 a 9; un tempo non
  valido (anche non numerico) viene richiesto di nuovo allo stesso atleta.
- Formato di stampa m'ss"d: secondi sempre su due cifre.

### Assunzioni

- A parità di tempo vince l'atleta inserito prima.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Decimi` | `typedef int Decimi;` | Tempo in decimi di secondo |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `tempi` | `Decimi[5]` | Tempi convertiti |
| `letti` | `int` | Valore restituito da `scanf` |
| `a` | `int` | Atleta corrente; `ATLETI + 1` segnala l'interruzione |
| `migliore` | `int` | Indice del tempo più basso |

| Funzione | Compito |
|----------|---------|
| `in_decimi(minuti, secondi, decimi)` | Converte in decimi di secondo |
| `stampa_tempo(t)` | Stampa nel formato 1'05"3 |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché non sono stati letti cinque tempi:
   1. leggere minuti, secondi e decimi;
   2. a fine input interrompere;
   3. se non sono tre numeri, scartare la riga e chiedere di ripetere;
   4. se fuori intervallo, chiedere di ripetere;
   5. altrimenti convertire in decimi, aggiornare il migliore e passare
      all'atleta successivo.
2. Se i tempi sono completi, stampare il vincitore e per ogni atleta il
   tempo e la differenza con il tempo migliore.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Gara con tempi non validi

- **Cosa si verifica:** richiesta ripetuta per tempi fuori intervallo e non
  numerici, vincitore e distacchi.
- **Input:** `1 5 3`, `1 70 2`, `abc`, `1 2 8`, `1 8 0`, `1 2 8`, `0 59 9`
- **Valori intermedi attesi:** tempi 653, 628, 680, 628, 599 decimi;
  migliore Colombo (599).
- **Output atteso:**
  ```
    Tempo non valido, ripetere.
    Tempo non valido, ripetere.

  Vincitore: Colombo con 0'59"9

    Atleta     Tempo     Distacco
    Bianchi   1'05"3    +0'05"4
    Esposito  1'02"8    +0'02"9
    Ferrari   1'08"0    +0'08"1
    Russo     1'02"8    +0'02"9
    Colombo   0'59"9    +0'00"0
  ```

### Test 2 – Pari merito al primo posto

- **Cosa si verifica:** a parità vince il primo inserito.
- **Input:** `1 0 0`, `1 0 0`, `1 0 5`, `1 1 0`, `1 0 0`
- **Output atteso:** `Vincitore: Bianchi con 1'00"0`; distacco `+0'00"0`
  per Bianchi, Esposito e Colombo.

### Test 3 – Input interrotto

- **Cosa si verifica:** la fine dell'input non produce una classifica con
  tempi mancanti.
- **Input:** `1 5 3`, poi fine input.
- **Output atteso:**
  ```
    Inserimento interrotto.
  ```
