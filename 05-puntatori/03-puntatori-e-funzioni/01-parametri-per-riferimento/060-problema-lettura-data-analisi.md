# Analisi – 060-problema-lettura-data.c

## 1. Problema

Per prenotare la palestra comunale si inserisce una data `gg/mm/aaaa`. Il
programma controlla che la data esista, compresi i mesi da 30 giorni e
febbraio negli anni bisestili, e per una data valida indica il giorno
successivo, quando la prenotazione scade. Una riga vuota termina.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `giorno`, `mese`, `anno` | `int` | — | Data letta, poi spostata al giorno dopo |
| `esito` | `int` | — | 1 valida, 0 non valida, -1 fine |
| `riga` | `char[]` | 40 | Riga letta con `fgets` dentro `leggi_data` |
| `gg`, `mm`, `aa` | `int` | — | Valori provvisori prima del controllo |

| Funzione | Compito |
|----------|---------|
| `leggi_data(&g, &m, &a)` | Legge e controlla una data, tre esiti possibili |
| `giorni_del_mese(m, a)` | 28, 29, 30 o 31 |
| `giorno_dopo(&g, &m, &a)` | Porta la data al giorno successivo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Cambio di anno

**a) Input** – `31/12/2026`

**b) Output** – "Prenotazione per il 31/12/2026, scade il 01/01/2027"

**c) Variabili di supporto** – `*g`, `*m`, `*a`

**d) Vincoli** – i tre valori cambiano insieme dentro la stessa funzione

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Incrementare il giorno.
2. Se supera i giorni del mese, tornare a 1 e incrementare il mese.
3. Se il mese supera 12, tornare a 1 e incrementare l'anno.

### Caso d'uso 2 – Anni bisestili

**a) Input** – `29/02/2026`; `28/02/2028`

**b) Output** – "Data non valida."; scadenza il 29/02/2028

**c) Variabili di supporto** – nessuna

**d) Vincoli** – bisestile se divisibile per 4 e non per 100, oppure per 400

**e) Assunzioni** – anni dal 1900

**f) Algoritmo in linguaggio naturale** – `giorni_del_mese` restituisce 29 per
febbraio solo negli anni bisestili.

### Caso d'uso 3 – Esito a tre valori

**a) Input** – `31/04/2026`, `ciao`, riga vuota

**b) Output** – due volte "Data non valida.", poi il programma termina

**c) Variabili di supporto** – `esito`, `gg`, `mm`, `aa`

**d) Vincoli** – le variabili del chiamante si scrivono solo se la data è
valida

**e) Assunzioni** – una riga che inizia con `'\n'` è vuota

**f) Algoritmo in linguaggio naturale** – leggere la riga; se è vuota o manca,
restituire -1; altrimenti convertire con `sscanf` in variabili locali,
controllare e solo allora copiare nei parametri di uscita.
