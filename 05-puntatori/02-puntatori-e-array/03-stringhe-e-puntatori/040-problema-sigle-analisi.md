# Analisi – 040-problema-sigle.c

## 1. Problema

La segreteria di una scuola deve scrivere la sigla di molti enti. Il
programma legge il nome completo di un ente e costruisce la sigla con le
iniziali maiuscole delle parole, saltando le parole di 3 lettere o meno
(articoli e preposizioni). Una riga vuota termina il programma.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[100]` | Nome dell'ente letto con `fgets`; riga vuota per finire |

### Output

- Per ogni nome: `Sigla: <SIGLA>`.

### Vincoli

- Una parola è una sequenza di lettere (`isalpha`): spazi, apostrofi e
  punteggiatura separano le parole.
- Le parole di 3 lettere o meno si saltano; delle altre si prende l'iniziale
  in maiuscolo (`toupper`).
- `crea_sigla` scorre il nome con il puntatore `p`, ricorda l'inizio di ogni
  parola in `inizio` e ne calcola la lunghezza come `p − inizio`; scrive la
  sigla tramite il puntatore `s`.
- La sigla non supera 19 caratteri più il `'\0'`: le iniziali in più si
  ignorano.
- Il `'\n'` lasciato da `fgets` si cerca con `strchr` e si toglie prima del
  controllo della riga vuota; se manca, la riga era più lunga del buffer e
  il resto si scarta.
- La fine dell'input termina il programma.

### Assunzioni

- Il nome non contiene lettere accentate.
- Le preposizioni articolate lunghe ("delle", "della") non vengono saltate.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `sigla` | `char[20]` | Sigla costruita |
| `a_capo` | `char *` | Posizione del `'\n'` trovato da `strchr`, `NULL` se manca |
| `c` | `int` | Carattere scartato da una riga troppo lunga |
| `continua` | `int` | Flag del ciclo principale |
| `p`, `inizio`, `s` | `const char *`, `const char *`, `char *` | In `crea_sigla` |
| `MAX_SIGLA`, `MAX_BREVE` | `#define` | 20, 3 |

| Funzione | Compito |
|----------|---------|
| `crea_sigla(nome, sigla)` | Scrive in `sigla` le iniziali delle parole lunghe |

### Algoritmo in linguaggio naturale

1. Finché `continua`:
   1. leggere una riga; a fine input terminare;
   2. togliere il `'\n'`, oppure scartare il resto di una riga troppo lunga;
   3. se la riga è vuota terminare, altrimenti costruire e stampare la sigla.
2. In `crea_sigla`, scorrendo il nome: a ogni lettera ricordare l'inizio
   della parola e avanzare fino alla fine della parola; se la parola è
   lunga più di 3 lettere e c'è spazio, aggiungere l'iniziale maiuscola;
   gli altri caratteri si saltano. Alla fine chiudere la sigla con `'\0'`.

## 3. Casi di test

Nell'output i nomi inseriti non compaiono (input da pipe).

### Test 1 – Parole tutte lunghe

- **Input:** `Istituto Tecnico Industriale Statale`
- **Output atteso:** `  Sigla: ITIS`

### Test 2 – Parole brevi e apostrofo

- **Cosa si verifica:** "per" (3 lettere) e "l" (1 lettera, separata
  dall'apostrofo) si saltano.
- **Input:** `Ente Nazionale per l'Aviazione Civile`
- **Output atteso:** `  Sigla: ENAC`

### Test 3 – Minuscole e preposizioni lunghe

- **Input:** `unione europea`; `Organizzazione delle Nazioni Unite per
  l'Educazione, la Scienza e la Cultura`
- **Output atteso:** `  Sigla: UE`; `  Sigla: ODNUESC` ("delle" ha 5
  lettere e non viene saltata).

### Test 4 – Sigla al limite

- **Cosa si verifica:** la sigla si ferma a 19 caratteri.
- **Input:** 20 volte la parola `Abcd` separata da spazi
- **Output atteso:** `  Sigla: AAAAAAAAAAAAAAAAAAA` (19 lettere).

### Test 5 – Riga più lunga del buffer

- **Cosa si verifica:** il resto della riga non diventa un altro nome.
- **Input:** 6 volte `Alfa Beta Gamma Delta ` (132 caratteri), poi riga vuota
- **Output atteso:** una sola riga `  Sigla: ABGDABGDABGDABGDAB` (le iniziali
  delle parole contenute nei primi 99 caratteri).

### Test 6 – Fine

- **Input:** riga vuota
- **Output atteso:** il programma termina senza stampare sigle.
