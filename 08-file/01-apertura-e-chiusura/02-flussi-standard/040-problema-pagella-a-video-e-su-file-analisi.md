# Analisi – 040-problema-pagella-a-video-e-su-file.c

## 1. Problema

A fine trimestre il coordinatore inserisce i voti di uno studente nelle
sei materie. La pagella, con la media e le insufficienze, compare a video
e, dopo una conferma, si salva in `pagella-COGNOME.txt`. Una sola funzione
scrive la pagella sul flusso che riceve (`stdout` o il file), così le due
copie sono identiche.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `cognome` | testo | Cognome dello studente, senza spazi, fino a 29 caratteri |
| `voti[i]` | `int` | Voto intero da 1 a 10 per ciascuna delle 6 materie |
| `risposta` | `char` | `s` o `n` (anche maiuscole): salvare la pagella? |

### Output

- `  voto da 1 a 10` su `stderr` per ogni voto da ripetere.
- La pagella: intestazione con il cognome, una riga per materia (nome in
  18 colonne, voto in 2, `  *` se insufficiente), `Media: M` con due
  decimali, `Nessuna insufficienza.` oppure `Insufficienze (*): K`.
- `Pagella salvata in pagella-COGNOME.txt` (il file contiene la stessa
  pagella) oppure `Pagella non salvata.`.
- `Dati incompleti.` se l'input finisce prima; `Impossibile creare NOME`
  su `stderr`.

### Vincoli

- `stampa_pagella` riceve un `FILE *` e scrive solo con `fprintf(f, ...)`:
  chiamata con `stdout` scrive a video, con il file aperto in `"w"` scrive
  nel file.
- Il nome del file si costruisce con `sprintf` in 50 caratteri
  (`pagella-` + 29 + `.txt` ci stanno).
- Il voto si legge come parola e si accetta solo se è un intero senza
  altri caratteri (`7.5`, `otto`, `8a` si rifiutano).
- Insufficiente: voto minore di 6. La media è la somma divisa per 6.
- Il file si salva solo con la risposta `s`/`S`; si controlla `fopen` e si
  chiude con `fclose`.

### Assunzioni

- Le sei materie sono fisse.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `materie` | `const char *[6]` | Nomi delle materie |
| `voti` | `int[6]` | Voti inseriti |
| `nome_file` | `char[50]` | Nome costruito con `sprintf` |
| `f` | `FILE *` | Pagella su file |
| `ok` | `int` | 0 se l'input finisce prima |
| `MATERIE` | `#define` | 6 |

| Funzione | Compito |
|----------|---------|
| `leggi_voto(materia)` | Chiede il voto finché è valido; 0 a fine input |
| `stampa_pagella(f, cognome, materie, voti, n)` | Scrive la pagella sul flusso `f` |

### Algoritmo in linguaggio naturale

1. Leggere il cognome e i sei voti; se l'input finisce, stampare
   `Dati incompleti.`.
2. Stampare la pagella su `stdout` e chiedere se salvarla.
3. Con la conferma costruire il nome del file, aprirlo in `"w"`, chiamare
   la stessa funzione con il file e chiuderlo.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe); i messaggi di
`stderr` compaiono a video prima della pagella perché `stdout` verso una
pipe è bufferizzato.

### Test 1 – Pagella salvata

- **Cosa si verifica:** i voti non validi si ripetono; il file contiene la
  stessa pagella del video.
- **Input:** `Bianchi`, `7`, `5`, `otto`, `8`, `9`, `11`, `6`, `6`, `s`
- **Valori intermedi attesi:** somma 41, media 41/6 = 6.83; una
  insufficienza (Matematica).
- **Output atteso:**
  ```
    voto da 1 a 10
    voto da 1 a 10
  Cognome dello studente:   Italiano:   Matematica:   Inglese:   Inglese:   Informatica:   Sistemi e reti:   Sistemi e reti:   Scienze motorie: 
  PAGELLA DEL PRIMO TRIMESTRE - Bianchi
  ----------------------------------
  Italiano            7
  Matematica          5  *
  Inglese             8
  Informatica         9
  Sistemi e reti      6
  Scienze motorie     6
  ----------------------------------
  Media: 6.83
  Insufficienze (*): 1

  Salvare la pagella? (s/n) Pagella salvata in pagella-Bianchi.txt
  ```
- **Procedura:** confrontare con `cat pagella-Bianchi.txt`: dalla riga
  `PAGELLA` a `Insufficienze` il contenuto è identico.

### Test 2 – Voto decimale e pagella non salvata

- **Input:** `Verdi 7.5 7 8 6 6 6 6 N`
- **Valori intermedi attesi:** `7.5` rifiutato; voti 7, 8, 6, 6, 6, 6,
  media 6.50.
- **Output atteso:** un `  voto da 1 a 10`, la pagella con
  `Media: 6.50` e `Nessuna insufficienza.`, poi `Pagella non salvata.`.

### Test 3 – Dati incompleti

- **Input:** `Neri 7 8`, poi fine input
- **Output atteso:** `... Inglese: Dati incompleti.`
