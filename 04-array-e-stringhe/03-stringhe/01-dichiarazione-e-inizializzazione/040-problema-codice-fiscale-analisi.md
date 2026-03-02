# Analisi – 040-problema-codice-fiscale.c

## 1. Problema

Una scuola necessita di un programma che visualizzi la scheda anagrafica di uno
studente e estragga automaticamente alcune informazioni codificate nel codice
fiscale italiano, verificandone inoltre la correttezza formale della lunghezza.

---

## 2. Analisi generale e struttura dati

Il programma gestisce dati testuali di natura anagrafica. Poiché in C le stringhe
sono array di `char` terminati da `'\0'`, ogni campo viene dichiarato con una
dimensione massima stabilita in base ai limiti reali del dato che rappresenta.

| Variabile         | Tipo        | Dimensione | Motivazione                              |
|-------------------|-------------|------------|------------------------------------------|
| `nome`            | `char[]`    | 31         | Max 30 caratteri + `'\0'`                |
| `cognome`         | `char[]`    | 31         | Max 30 caratteri + `'\0'`                |
| `codice_fiscale`  | `char[]`    | 17         | Esattamente 16 caratteri + `'\0'`        |
| `classe`          | `char[]`    | 5          | Formato "4B", max 4 caratteri + `'\0'`   |
| `indirizzo`       | `char[]`    | 51         | Max 50 caratteri + `'\0'`                |
| `lunghezza`       | `int`       | —          | Contatore per la verifica della lunghezza|

La struttura del codice fiscale italiano utilizzata per l'estrazione:

```
Posizioni  0- 2  → sigla cognome (3 consonanti)
Posizioni  3- 5  → sigla nome (3 consonanti)
Posizioni  6- 7  → anno di nascita (ultime 2 cifre)
Posizione  8     → mese di nascita (lettera)
Posizioni  9-10  → giorno di nascita (+ 40 per le donne)
Posizioni 11-14  → codice comune di nascita
Posizione  15    → carattere di controllo
```

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Visualizzazione scheda studente

**a) Input**
Dati statici inizializzati nel codice (simulazione di dati provenienti da un
archivio): nome, cognome, codice fiscale, classe, indirizzo.

**b) Output**
Scheda formattata a video con etichette allineate e bordi testuali:
```
========================================
        SCHEDA STUDENTE
========================================
Nome             : Giovanni
Cognome          : Ferrero
...
```

**c) Variabili di supporto**
Nessuna variabile aggiuntiva. La formattazione è gestita direttamente da `printf`
con specificatori di larghezza.

**d) Vincoli**
- Ogni stringa deve essere correttamente terminata da `'\0'`.
- Le dimensioni degli array devono essere sufficienti a contenere il dato più
  il terminatore.

**e) Assunzioni**
- I dati sono precaricati e validi (nessun controllo di input richiesto).
- La codifica dei caratteri è ASCII standard (nessun carattere accentato).

**f) Algoritmo in linguaggio naturale**
```
1. Dichiarare e inizializzare le stringhe con i dati dello studente.
2. Stampare la riga di intestazione con bordi.
3. Stampare ciascun campo preceduto dalla sua etichetta.
4. Stampare la riga di chiusura.
```

---

### Caso d'uso 2 – Estrazione informazioni dal codice fiscale

**a) Input**
La stringa `codice_fiscale` già dichiarata e inizializzata (16 caratteri).

**b) Output**
Righe a video con le informazioni estratte:
```
Sigla cognome  : FRR
Anno di nascita: 2005
Giorno nascita : 15
Codice comune  : L219
```

**c) Variabili di supporto**
Nessuna: l'accesso avviene direttamente tramite indice sull'array `codice_fiscale`.

**d) Vincoli**
- Il codice fiscale deve avere esattamente 16 caratteri.
- Le posizioni di ciascun campo sono fisse e definite dalla normativa italiana.

**e) Assunzioni**
- Il codice fiscale è formalmente corretto e non contiene caratteri non validi.
- Il programma non verifica il carattere di controllo (posizione 15).

**f) Algoritmo in linguaggio naturale**
```
1. Accedere alle posizioni 0-2 e stampare la sigla del cognome.
2. Accedere alle posizioni 6-7 e stamparle precedute dal prefisso "20"
   per ricostruire l'anno completo.
3. Accedere alle posizioni 9-10 e stampare il giorno di nascita.
4. Accedere alle posizioni 11-14 e stampare il codice comune.
```

---

### Caso d'uso 3 – Verifica della lunghezza del codice fiscale

**a) Input**
La stringa `codice_fiscale`.

**b) Output**
Messaggio a video che conferma o segnala un errore sulla lunghezza:
```
Lunghezza codice fiscale: 16 caratteri (corretta)
```

**c) Variabili di supporto**
- `lunghezza` (`int`): contatore incrementato a ogni iterazione del ciclo.

**d) Vincoli**
- Il ciclo deve fermarsi al carattere `'\0'` senza includerlo nel conteggio.
- La lunghezza corretta attesa è esattamente 16.

**e) Assunzioni**
- La stringa è sempre terminata da `'\0'` (garanzia dell'inizializzazione statica).
- Non si usa `strlen` per mostrare allo studente come implementare il conteggio
  manualmente.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare il contatore lunghezza a 0.
2. Finché il carattere in posizione lunghezza non è '\0':
   a. Incrementare lunghezza di 1.
3. Confrontare lunghezza con 16.
4. Se uguale a 16: stampare "corretta".
   Altrimenti: stampare messaggio di errore.
```
