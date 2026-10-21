# Analisi – 050-problema-registro-presenze.c

## 1. Problema

All'ingresso di una scuola, uno studente digita il proprio nome e cognome
su un terminale. Il sistema deve leggere l'input, verificare che non sia
vuoto, e registrare la presenza stampando una riga di log formattata con
numero progressivo, data e ora preimpostate.

---

## 2. Analisi

### Input

| Variabile       | Tipo     | Dimensione | Descrizione                                  |
|-----------------|----------|------------|----------------------------------------------|
| `nome_studente` | `char[]` | 61         | Nome e cognome, max 60 caratteri + `'\0'`    |

Data, ora e numero progressivo sono preimpostati nel codice.

### Output
- L'intestazione del registro con data e ora;
- se il nome non è vuoto, il riquadro "PRESENZA REGISTRATA" con numero
  progressivo, data, ora e studente, e la conferma; altrimenti
  "ERRORE: nessun nome inserito. Presenza non registrata.".

### Vincoli
- Il nome si legge con `fgets`, perché può contenere spazi (`scanf` con
  `%s` si fermerebbe al primo spazio)
- `fgets` conserva il `'\n'` finale: si scorre la stringa fino a `'\n'` o a
  `'\0'` e lo si sostituisce con `'\0'`
- Un nome è vuoto se, tolto il `'\n'`, il primo carattere è `'\0'`
- `fgets` legge al massimo 60 caratteri, quindi il buffer non viene mai
  superato

### Assunzioni
- Data, ora e numero progressivo sono costanti didattiche: in un sistema
  reale verrebbero dall'orologio e da un archivio
- Un nome fatto di soli spazi è considerato valido

### Variabili di supporto

| Variabile              | Tipo     | Dimensione | Descrizione                             |
|------------------------|----------|------------|-----------------------------------------|
| `data`                 | `char[]` | 11         | Data in formato ISO                     |
| `ora`                  | `char[]` | 6          | Ora in formato HH:MM                    |
| `numero_registrazione` | `int`    | —          | Numero progressivo simulato (142)       |
| `i`                    | `int`    | —          | Indice per trovare il `'\n'`            |
| `nome_valido`          | `int`    | —          | 1 se il nome non è vuoto                |

### Algoritmo in linguaggio naturale
1. Stampare l'intestazione con data e ora.
2. Leggere il nome con `fgets`.
3. Scorrere fino a `'\n'` o `'\0'` e scrivervi `'\0'`.
4. Se il primo carattere è `'\0'` il nome non è valido.
5. Se è valido stampare la registrazione, altrimenti l'errore.

---

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato.

### Test 1 – Nome con spazi
- **Cosa si verifica:** `fgets` legge anche gli spazi e il `'\n'` viene
  rimosso (la conferma finisce subito dopo il nome)
- **Input:** `De Luca Giovanni`
- **Output atteso:**
```
  N. progressivo : 142
  Data           : 2024-11-15
  Ora            : 08:32
  Studente       : De Luca Giovanni
════════════════════════════════════════════════════

Presenza di De Luca Giovanni registrata correttamente.
```

### Test 2 – Nome vuoto
- **Input:** solo Invio
- **Output atteso:** `ERRORE: nessun nome inserito. Presenza non registrata.`
