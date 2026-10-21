# Analisi – 060-problema-rubrica-telefonica.c

## 1. Problema

Un'applicazione gestisce una rubrica telefonica con 6 contatti. Il programma
deve visualizzare la rubrica completa, cercare un contatto per prefisso del
nome (senza usare `strcmp`) e filtrare i contatti con numero di cellulare
(prefisso telefonico '3').

---

## 2. Analisi

### Input
Nessun input da tastiera: i contatti e la stringa da cercare sono
inizializzati nel codice.

| Variabile  | Tipo       | Dimensione | Descrizione                                |
|------------|------------|------------|--------------------------------------------|
| `nomi`     | `char[][]` | 6 × 25     | Cognome e nome di ogni contatto            |
| `telefoni` | `char[][]` | 6 × 13     | Numero di telefono, parallelo a `nomi`     |
| `ricerca`  | `char[]`   | 25         | Testo da cercare all'inizio dei nomi       |

### Output
- La rubrica: nome e numero di ogni contatto;
- il risultato della ricerca: il primo contatto il cui nome inizia con il
  testo cercato, oppure "Nessun contatto trovato con questo nome.";
- l'elenco dei contatti con un cellulare (numero che inizia con '3') e il
  loro numero.

### Vincoli
- `nomi[i]` e `telefoni[i]` appartengono sempre allo stesso contatto
- La ricerca confronta solo i primi caratteri del nome (ricerca per
  prefisso), carattere per carattere, distinguendo maiuscole e minuscole
- La ricerca si ferma al primo contatto trovato tramite il flag `trovato`
  nella condizione del ciclo esterno, e il confronto si ferma al primo
  carattere diverso tramite il flag `uguale`: niente `break`
- Il controllo del cellulare confronta il carattere `'3'`, non il numero 3

### Assunzioni
- I nomi non superano 24 caratteri e i numeri 12
- La stringa di ricerca non è vuota

### Variabili di supporto

| Variabile        | Tipo  | Descrizione                                       |
|------------------|-------|---------------------------------------------------|
| `len_ricerca`    | `int` | Lunghezza di `ricerca`, contata fino a `'\0'`     |
| `trovato`        | `int` | 1 quando un contatto corrisponde                  |
| `indice_trovato` | `int` | Posizione del contatto trovato (-1 se nessuno)    |
| `uguale`         | `int` | 1 finché i caratteri confrontati coincidono       |
| `num_cellulari`  | `int` | Numero di contatti con prefisso '3'               |

### Algoritmo in linguaggio naturale
1. Stampare nome e numero di ogni contatto.
2. Contare i caratteri di `ricerca` fino a `'\0'`.
3. Per ogni contatto, finché non se ne è trovato uno:
   a. porre `uguale = 1`;
   b. confrontare i primi `len_ricerca` caratteri del nome con quelli di
      `ricerca`, fermandosi al primo diverso (`uguale = 0`);
   c. se tutti coincidono porre `trovato = 1` e memorizzare l'indice.
4. Stampare il contatto trovato o il messaggio di assenza.
5. Per ogni contatto il cui numero inizia con '3' stamparlo e contarlo;
   stampare il totale.

---

## 3. Casi di test

Il testo da cercare è fisso nel codice: per i test 2–4 si modifica
l'inizializzazione di `ricerca` e si ricompila.

### Test 1 – Ricerca di un cognome e filtro cellulari
- **Input:** `ricerca = "Rossi"`
- **Output atteso:**
```
Ricerca 'Rossi':
  Trovato: Rossi Marco - Tel: 3471234567

Contatti con numero di cellulare (prefisso '3'):
  Rossi Marco: 3471234567
  Verdi Luca: 3389876543
  Russo Pietro: 3201112233
Totale cellulari in rubrica: 3 su 6
```

### Test 2 – Ricerca per prefisso parziale
- **Cosa si verifica:** basta l'inizio del nome
- **Input:** `ricerca = "Ver"`
- **Output atteso:** `Trovato: Verdi Luca - Tel: 3389876543`

### Test 3 – Maiuscole e minuscole
- **Cosa si verifica:** il confronto distingue le maiuscole
- **Input:** `ricerca = "rossi"`
- **Output atteso:** `Nessun contatto trovato con questo nome.`

### Test 4 – Nome assente
- **Input:** `ricerca = "Neri"`
- **Output atteso:** `Nessun contatto trovato con questo nome.`
