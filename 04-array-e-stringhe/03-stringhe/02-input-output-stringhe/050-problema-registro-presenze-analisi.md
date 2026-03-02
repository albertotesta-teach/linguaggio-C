# Analisi – 050-problema-registro-presenze.c

## 1. Problema

All'ingresso di una scuola, uno studente digita il proprio nome e cognome
su un terminale. Il sistema deve leggere l'input, verificare che non sia
vuoto, e registrare la presenza stampando una riga di log formattata con
numero progressivo, data e ora preimpostate.

---

## 2. Analisi generale e struttura dati

| Variabile              | Tipo     | Dimensione | Motivazione                                        |
|------------------------|----------|------------|----------------------------------------------------|
| `data`                 | `char[]` | 11         | Data in formato ISO (10 caratteri + `'\0'`)        |
| `ora`                  | `char[]` | 6          | Ora in formato HH:MM (5 caratteri + `'\0'`)        |
| `nome_studente`        | `char[]` | 61         | Nome completo max 60 caratteri + `'\0'`            |
| `numero_registrazione` | `int`    | —          | Contatore progressivo (simulato)                   |
| `i`                    | `int`    | —          | Indice per scorrere la stringa e rimuovere `'\n'`  |
| `nome_valido`          | `int`    | —          | Flag: 1 = nome inserito, 0 = campo vuoto           |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Lettura del nome studente

**a) Input**
Stringa digitata dall'utente da tastiera, può contenere spazi
(es. "De Luca Giovanni").

**b) Output**
Nessun output diretto: il valore viene memorizzato in `nome_studente`
per i casi d'uso successivi.

**c) Variabili di supporto**
- `i` (`int`): indice usato nel ciclo di rimozione del `'\n'`.

**d) Vincoli**
- La lunghezza massima leggibile è 60 caratteri (il buffer è 61).
- `fgets` include `'\n'` nella stringa: deve essere rimosso prima dell'uso.

**e) Assunzioni**
- L'input proviene da `stdin` (tastiera).
- Il nome può contenere spazi, lettere accentate non sono gestite.

**f) Algoritmo in linguaggio naturale**
```
1. Mostrare il prompt "Inserisci nome e cognome: ".
2. Leggere la riga con fgets(nome_studente, 61, stdin).
3. Inizializzare i a 0.
4. Finché nome_studente[i] non è '\n' e non è '\0':
   a. Incrementare i.
5. Impostare nome_studente[i] a '\0' (rimuove '\n' se presente).
```

---

### Caso d'uso 2 – Verifica campo non vuoto

**a) Input**
La stringa `nome_studente` dopo la rimozione del `'\n'`.

**b) Output**
Nessun output diretto: imposta il flag `nome_valido`.

**c) Variabili di supporto**
- `nome_valido` (`int`): flag risultato della verifica.

**d) Vincoli**
- Una stringa vuota ha `nome_studente[0] == '\0'` dopo la rimozione del `'\n'`.

**e) Assunzioni**
- Una stringa composta solo da spazi è considerata valida
  (controllo semplificato, adatto al livello didattico).

**f) Algoritmo in linguaggio naturale**
```
1. Se nome_studente[0] è '\0':
   a. Impostare nome_valido a 0.
2. Altrimenti:
   a. Impostare nome_valido a 1.
```

---

### Caso d'uso 3 – Registrazione e stampa del log

**a) Input**
`nome_valido`, `nome_studente`, `data`, `ora`, `numero_registrazione`.

**b) Output**
Se il nome è valido, scheda formattata con tutti i dati della registrazione:
```
════════════════════════════════════════════════════
  PRESENZA REGISTRATA
════════════════════════════════════════════════════
  N. progressivo : 142
  Data           : 2024-11-15
  Ora            : 08:32
  Studente       : De Luca Giovanni
════════════════════════════════════════════════════

Presenza di De Luca Giovanni registrata correttamente.
```
Se il nome non è valido, messaggio di errore:
```
ERRORE: nessun nome inserito. Presenza non registrata.
```

**c) Variabili di supporto**
Nessuna variabile aggiuntiva: la stampa usa direttamente le variabili già dichiarate.

**d) Vincoli**
- La stampa avviene solo se `nome_valido` è 1.
- I campi della scheda sono allineati con larghezza fissa tramite `printf`.

**e) Assunzioni**
- Data e ora sono preimpostate nel codice (non lette da orologio di sistema).
- Il numero progressivo è simulato con un valore fisso.

**f) Algoritmo in linguaggio naturale**
```
1. Se nome_valido è 0:
   a. Stampare messaggio di errore.
2. Altrimenti:
   a. Stampare intestazione della scheda.
   b. Stampare numero progressivo, data, ora, nome studente.
   c. Stampare riga di conferma con il nome dello studente.
```
