# Analisi – 080-problema-validazione-iscrizione.c

## 1. Problema

La segreteria inserisce le iscrizioni al primo anno. leggi_iscrizione riempie la struct del chiamante e delega ogni parte a una funzione che riceve solo l'indirizzo di quella parte; restituisce 0 se tutto è corretto oppure il numero della parte sbagliata, usato dal main come indice di una tabella di messaggi. Si hanno 3 tentativi.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Data` | `giorno, mese, anno` | data del calendario |
| `Indirizzo` | `via, cap, comune` | residenza |
| `Iscrizione` | `nome, nascita, residenza` | scheda con due struct interne |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nuova` | `Iscrizione` | — | Scheda da riempire |
| `parti` | `const char *[]` | 4 | Nomi delle parti per i messaggi |
| `esito`, `tentativo` | `int` | — | Risultato e numero del tentativo |

| Funzione | Compito |
|----------|---------|
| `leggi_testo(domanda, dest, dimensione)` | Riga non vuota che stia nel campo |
| `leggi_data(d)` | Data esistente con anno dal 2011 al 2013 |
| `leggi_indirizzo(i)` | Legge via, CAP e comune, poi li controlla |
| `leggi_iscrizione(s)` | 0 oppure 1 nome, 2 data, 3 indirizzo |
| `stampa(s)` | Riceve const Iscrizione * |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Data sbagliata

**a) Input** – `Rossi Elena`, `31/04/2012`

**b) Output** – "Errore nella parte: data di nascita."

**c) Variabili di supporto** – `esito`

**d) Vincoli** – aprile ha 30 giorni

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – leggi_data(&s->nascita) restituisce 0 e la scheda si ricomincia.

### Caso d'uso 2 – Scheda corretta

**a) Input** – secondo tentativo con `12/04/2012` e l'indirizzo

**b) Output** – "Iscrizione registrata:" con nome, data e indirizzo

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – tutte le funzioni delle parti restituiscono 1.

### Caso d'uso 3 – Tre errori

**a) Input** – nome vuoto, anno 2009, CAP `1506`

**b) Output** – "Iscrizione non registrata."

**c) Variabili di supporto** – `tentativo`

**d) Vincoli** – CAP di 5 cifre, anni dal 2011 al 2013

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – dopo il terzo tentativo sbagliato il ciclo termina.
