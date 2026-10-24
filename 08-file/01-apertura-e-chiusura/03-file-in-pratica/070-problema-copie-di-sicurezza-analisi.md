# Analisi – 070-problema-copie-di-sicurezza.c

## 1. Problema

Il verbale del consiglio di classe viene aggiornato più volte. Prima di
ogni modifica il programma fa ruotare le copie di sicurezza (`.bak3` si
rimuove, `.bak2` diventa `.bak3`, `.bak1` diventa `.bak2`) e copia
l'originale in `.bak1`. Poi aggiunge in fondo la riga scritta
dall'utente e mostra quante righe ha ogni versione presente.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `nome` | testo | File da modificare, fino a 39 caratteri |
| `riga` | testo | Riga da aggiungere, spazi compresi, fino a 99 caratteri |

### Output

- Il file con la nuova riga in fondo e fino a tre copie `NOME.bak1`
  (la più recente), `NOME.bak2`, `NOME.bak3`.
- `Aggiunta a NOME.`, poi `Versioni presenti:` con una riga per versione:
  nome in 18 colonne e `righe: R`.
- Su `stderr`: `Copia di sicurezza non riuscita: modifica annullata.` o
  `Impossibile aprire NOME`.

### Vincoli

- La rotazione parte dalla copia più vecchia: prima `remove` di `.bak3`,
  poi `rename` di `.bak2` e `.bak1`; in ordine inverso una copia
  cancellerebbe la successiva. Un `rename` di una copia che non esiste
  fallisce senza conseguenze.
- La copia in `.bak1` si fa solo se l'originale esiste; se la copia non
  riesce il file non si modifica.
- La riga si aggiunge aprendo in `"a"`; se il file non esiste viene
  creato.
- I nomi delle copie si costruiscono con `sprintf` in 50 caratteri (39 +
  `.bak3`).
- La riga si legge con `scanf(" %99[^\n]")`: i caratteri oltre il 99° si
  perdono.

### Assunzioni

- Il file da modificare è un file di testo con le righe terminate da a
  capo.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `nome`, `riga` | `char[40]`, `char[100]` | Dati inseriti |
| `copia_nome` | `char[50]` | Nome di una copia |
| `ok` | `int` | 0 se l'input finisce o la copia di sicurezza fallisce |
| `COPIE` | `#define` | 3 |

| Funzione | Compito |
|----------|---------|
| `ruota_copie(nome)` | Fa scorrere le copie e copia l'originale in `.bak1`; 0 se la copia fallisce |
| `copia(da, a)` | Copia un file carattere per carattere; 0 se non riesce |
| `esiste(nome)` | 1 se il file si può aprire in lettura |
| `stampa_righe(nome)` | Stampa il numero di righe del file |

### Algoritmo in linguaggio naturale

1. Leggere il nome del file e la riga da aggiungere.
2. Se il file esiste, far ruotare le copie e copiarlo in `.bak1`; se la
   copia non riesce, annullare.
3. Aprire il file in `"a"`, scrivere la riga e chiuderlo.
4. Stampare le righe del file e di ogni copia presente.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe). Si parte senza
`verbale.txt`; i test vanno eseguiti in ordine.

### Test 1 – Prima modifica: nessuna copia

- **Input:** `verbale.txt`, `Seduta del 3 ottobre: presenti tutti i docenti`
- **Output atteso:**
  ```
  File da modificare: Riga da aggiungere: Aggiunta a verbale.txt.
  Versioni presenti:
    verbale.txt        righe: 1
  ```

### Test 2 – Seconda, terza e quarta modifica

- **Input:** `verbale.txt` con `Punto 1: andamento didattico`; poi con
  `Punto 2: uscite didattiche`; poi con `Punto 3: varie`
- **Output atteso:** dopo la quarta modifica
  ```
  Versioni presenti:
    verbale.txt        righe: 4
    verbale.txt.bak1   righe: 3
    verbale.txt.bak2   righe: 2
    verbale.txt.bak3   righe: 1
  ```
  (dopo la seconda ci sono `verbale.txt` e `.bak1`, dopo la terza anche
  `.bak2`).

### Test 3 – Quinta modifica: la copia più vecchia si perde

- **Input:** `verbale.txt`, `La seduta e' tolta alle 16:30`
- **Output atteso:**
  ```
  Versioni presenti:
    verbale.txt        righe: 5
    verbale.txt.bak1   righe: 4
    verbale.txt.bak2   righe: 3
    verbale.txt.bak3   righe: 2
  ```
- **Procedura:** `verbale.txt.bak3` contiene le prime due righe del
  verbale.

### Test 4 – Input incompleto

- **Input:** `verbale.txt`, poi fine input
- **Output atteso:** `File da modificare: Riga da aggiungere: ` e nessuna
  modifica né rotazione.
