# Analisi – 040-problema-codice-fiscale.c

## 1. Problema

All'iscrizione la segreteria inserisce il codice fiscale degli studenti e
vuole intercettare subito gli errori di battitura. Il programma accetta il
codice anche in minuscolo, ne controlla la lunghezza e il tipo di ogni
carattere secondo lo schema del codice fiscale, verifica la lettera del
mese e, se il formato è corretto, ricava sesso e data di nascita.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `cf` | `char[]` | 30 | Codice letto (più lungo di 16 per accorgersi degli errori) |
| `schema` | `char[]` | 17 | `"LLLLLLCCLCCLCCCL"`: L = lettera, C = cifra |
| `lettere_mesi` | `char[]` | 13 | `"ABCDEHLMPRST"`: lettera di ogni mese |
| `nomi_mesi` | `char[][]` | 12 × 10 | Nomi dei mesi (parallelo a `lettere_mesi`) |
| `errore`, `mese` | `int` | — | Posizione del primo errore, indice del mese |
| `giorno`, `anno` | `int` | — | Valori ricavati dalle cifre |

| Funzione | Compito |
|----------|---------|
| `in_maiuscolo` | `toupper` su ogni carattere |
| `primo_errore` | Confronta il codice con lo schema usando `isalpha` e `isdigit` |
| `indice_mese` | Indice della lettera del mese, oppure -1 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Codice corretto scritto in minuscolo

**a) Input** – `rssmra85t10a944s`

**b) Output** – `RSSMRA85T10A944S: formato corretto`, sesso M, nato il 10 dicembre '85

**c) Variabili di supporto** – `giorno`, `anno`, `mese`

**d) Vincoli** – le cifre si convertono in numero con `c - '0'`

**e) Assunzioni** – codice senza omocodia

**f) Algoritmo in linguaggio naturale**
1. Convertire il codice in maiuscolo.
2. Verificare lunghezza, schema e lettera del mese.
3. Anno = cifre 7-8; giorno = cifre 10-11; mese dalla lettera 9.
4. Se il giorno supera 40 il sesso è F e il giorno vero è `giorno - 40`.

### Caso d'uso 2 – Codice femminile

**a) Input** – `BNCLRA92M52F205X`

**b) Output** – sesso F, nata il 12 agosto '92

**c) Variabili di supporto** – `giorno` = 52

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Errori di formato

**a) Input** – `RSSMRA85T10A94`; `RSSMR485T10A944S`; `RSSMRA85Z10A944S`

**b) Output** – "deve avere 16 caratteri, ne ha 14"; "in posizione 6 serve una lettera"; "la lettera del mese 'Z' non esiste"

**c) Variabili di supporto** – `errore`, `mese`

**d) Vincoli** – i controlli seguono l'ordine lunghezza → schema → mese; la
posizione si stampa contando da 1

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Se `strlen` è diverso da 16 segnalarlo.
2. Altrimenti scorrere lo schema: alla prima posizione in cui serve una
   lettera e c'è altro (o viceversa) fermarsi e restituire l'indice.
3. Se lo schema è rispettato ma la lettera del mese non è nell'elenco, segnalarlo.
