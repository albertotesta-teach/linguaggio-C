# Analisi – 060-problema-storico-dei-prezzi.c

## 1. Problema

Il comitato dei genitori registra ogni mese il prezzo del pasto in mensa. Le rilevazioni vanno in un vettore dinamico di `Rilevazione`. Il programma stampa la variazione percentuale mese per mese, costruisce un secondo vettore con i mesi di aumento (lunghezza non nota in anticipo), indica l'aumento più forte e la variazione complessiva.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Rilevazione` | `mese[8], prezzo` | prezzo di un mese |
| `Storico` | `dati (Rilevazione *), n, capacita` | vettore dinamico di rilevazioni |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `storico` | `Storico *` | struct + blocco di n Rilevazione (heap) | Prezzi nel tempo |
| `mesi_aumento` | `Storico *` | creato da aumenti | Copie dei mesi di aumento, da distruggere |
| `r`, `prima`, `ultima` | `Rilevazione` | — | Rilevazione letta, primo e ultimo mese |
| `massimo`, `letti` | `int` | — | Mese con l'aumento più forte; valori letti |

| Funzione | Compito |
|----------|---------|
| `variazione(prima, dopo)` | (dopo - prima) / prima × 100 |
| `variazione_mese(s, i)` | Variazione del mese i rispetto al precedente |
| `aumenti(s)` | Vettore nuovo con i mesi di aumento; NULL se manca memoria |
| `crea_storico, aggiungi, lunghezza, elemento, distruggi_storico` | Funzioni del vettore |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Anno scolastico

**a) Input** – da `set24 4.20` a `mag25 4.90`, poi `FINE`

**b) Output** – tabella con le variazioni; 3 aumenti su 8 (nov24, gen25, mar25); più forte mar25 +10.0%; complessivo +16.7%

**c) Variabili di supporto** – `massimo`

**d) Vincoli** – prezzo > 0

**e) Assunzioni** – mesi in ordine cronologico

**f) Algoritmo in linguaggio naturale** – aumenti scorre da 1 e copia i mesi con prezzo maggiore del precedente.

### Caso d'uso 2 – Prezzo errato

**a) Input** – `feb25 abc`

**b) Output** – "prezzo non valido per feb25"

**c) Variabili di supporto** – `letti`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – si salta la parola non numerica.

### Caso d'uso 3 – Nessun aumento

**a) Input** – `set24 4`, `ott24 3.5`

**b) Output** – "Nessun aumento.", complessivo -12.5%

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il vettore risultato ha lunghezza 0 ma va distrutto.

### Caso d'uso 4 – Un solo mese

**a) Input** – `set24 4.20 FINE`

**b) Output** – "Servono almeno due mesi."

**c) Variabili di supporto** – —

**d) Vincoli** – almeno 2 rilevazioni

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna variazione calcolabile.
