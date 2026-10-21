# Analisi – 040-problema-codice-fiscale.c

## 1. Problema

Una scuola necessita di un programma che visualizzi la scheda anagrafica di uno
studente e estragga automaticamente alcune informazioni codificate nel codice
fiscale italiano, verificandone inoltre la correttezza formale della lunghezza.

---

## 2. Analisi

### Input
Nessun input da tastiera: i dati dello studente sono stringhe inizializzate
nel codice.

| Variabile        | Tipo     | Dimensione | Descrizione                              |
|------------------|----------|------------|------------------------------------------|
| `nome`           | `char[]` | 31         | Max 30 caratteri + `'\0'`                |
| `cognome`        | `char[]` | 31         | Max 30 caratteri + `'\0'`                |
| `codice_fiscale` | `char[]` | 17         | Esattamente 16 caratteri + `'\0'`        |
| `classe`         | `char[]` | 5          | Es. "4B", max 4 caratteri + `'\0'`       |
| `indirizzo`      | `char[]` | 51         | Max 50 caratteri + `'\0'`                |

### Output
- La scheda dello studente con tutti i campi;
- le informazioni estratte dal codice fiscale: sigla del cognome, anno di
  nascita, giorno di nascita, codice del comune;
- la lunghezza del codice fiscale con l'esito "(corretta)" oppure
  "(ERRORE: dovrebbe essere 16)".

### Vincoli
- Ogni stringa è dimensionata per il dato più lungo previsto **più una
  cella** per il terminatore `'\0'`
- Le informazioni si estraggono accedendo ai caratteri per posizione,
  secondo la struttura del codice fiscale:

```
Posizioni  0- 2  → sigla cognome
Posizioni  3- 5  → sigla nome
Posizioni  6- 7  → anno di nascita (ultime 2 cifre)
Posizione  8     → mese di nascita (lettera)
Posizioni  9-10  → giorno di nascita (+ 40 per le donne)
Posizioni 11-14  → codice comune di nascita
Posizione  15    → carattere di controllo
```

- La lunghezza si conta scorrendo fino a `'\0'`, senza funzioni di libreria;
  il codice è corretto solo se ha esattamente 16 caratteri

### Assunzioni
- L'anno di nascita è nel 2000 o successivo: il programma antepone "20"
  alle due cifre
- Il giorno si stampa così com'è: per una studentessa comparirebbe il
  giorno + 40
- Si controlla solo la lunghezza, non il carattere di controllo

### Variabili di supporto

| Variabile   | Tipo  | Descrizione                               |
|-------------|-------|-------------------------------------------|
| `lunghezza` | `int` | Caratteri del codice fiscale fino a `'\0'`|

### Algoritmo in linguaggio naturale
1. Stampare la scheda con tutti i campi.
2. Stampare i caratteri 0–2 (sigla cognome), "20" seguito dai caratteri 6–7
   (anno), i caratteri 9–10 (giorno) e 11–14 (comune).
3. Contare i caratteri del codice fiscale fino al terminatore e stampare la
   lunghezza con l'esito del controllo.

---

## 3. Casi di test

I dati sono fissi nel codice: il Test 2 richiede di modificare il codice
fiscale e ricompilare.

### Test 1 – Codice fiscale corretto
- **Input:** `FRRGNN05A15L219X`
- **Output atteso:**
```
Informazioni estratte dal codice fiscale:
  Sigla cognome  : FRR
  Anno di nascita: 2005
  Giorno nascita : 15
  Codice comune  : L219

Lunghezza codice fiscale: 16 caratteri (corretta)
```

### Test 2 – Codice fiscale troppo corto
- **Cosa si verifica:** il conteggio fino a `'\0'`
- **Procedura:** togliere l'ultimo carattere (`FRRGNN05A15L219`)
- **Output atteso:**
  `Lunghezza codice fiscale: 15 caratteri (ERRORE: dovrebbe essere 16)`
