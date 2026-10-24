# Analisi – 080-problema-filtri-catalogo.c

## 1. Problema

Gli studenti cercano nel catalogo della biblioteca scegliendo un filtro da
un menu: autore, genere, anno di pubblicazione o disponibilità. Ogni
filtro è una funzione con lo stesso prototipo, raccolta in una tabella di
tipo `Filtro` (puntatore a funzione); `mostra` applica il filtro scelto a
tutto l'array di struct `Libro`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `scelta` | `int` | Filtro da 1 a 4; 0 termina |
| `valore` | `char[20]` | Il resto della riga: parte del nome dell'autore, genere, anno minimo; ignorato per "disponibili" |
| catalogo | nel sorgente | 7 libri (titolo, autore, genere, anno, copie libere) |

### Output

- Il menu dei filtri.
- Per ogni ricerca: i libri che superano il filtro e `Trovati: N`.
- `Filtro inesistente.` per una scelta fuori menu o non numerica.

### Vincoli

- `typedef int (*Filtro)(const Libro *l, const char *valore);`: tutti i
  filtri hanno lo stesso prototipo, anche `disponibile` che non usa il
  valore.
- Autore: il valore è contenuto nel nome (`strstr`); genere: uguaglianza
  (`strcmp`); anno: pubblicati da quell'anno in poi (`atoi`);
  disponibili: copie libere > 0.
- Il valore è il resto della riga senza gli spazi iniziali (può
  contenere spazi, es. `Primo Levi`); oltre 19 caratteri si scarta.
- Maiuscole e minuscole contano.
- A fine input il programma termina come con 0.

### Assunzioni

- Un valore vuoto non filtra nulla per l'autore (ogni nome contiene la
  stringa vuota) e vale come anno 0.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Libro` | `typedef struct { char titolo[32]; char autore[24]; char genere[16]; int anno; int copie_libere; } Libro;` | Un libro del catalogo |
| `Filtro` | `typedef int (*Filtro)(const Libro *l, const char *valore);` | Funzione che decide se un libro va mostrato |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `catalogo` | `Libro[7]` | Array di struct |
| `filtri` | `Filtro[4]` | Tabella dei filtri |
| `descrizioni` | `const char *[4]` | Voci del menu |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `per_autore`, `per_genere`, `dopo_anno`, `disponibile` | I quattro filtri |
| `mostra(catalogo, n, f, valore)` | Stampa i libri che superano `f` e li conta |
| `leggi_valore(valore, dimensione)` | Legge il resto della riga |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Stampare il menu.
2. Finché la scelta non è 0:
   1. leggere la scelta (fine input → 0; testo → filtro inesistente);
   2. se è tra 1 e 4 leggere il valore e chiamare
      `mostra(catalogo, LIBRI, filtri[scelta - 1], valore)`, stampando il
      numero di libri trovati;
   3. altrimenti scartare la riga e, se non è 0, segnalare il filtro
      inesistente.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – I quattro filtri

- **Cosa si verifica:** ogni filtro, un valore con spazi, un genere con la
  maiuscola, filtri inesistenti, valore troppo lungo.
- **Input:** `1 Calvino`, `1 Primo Levi`, `2 fantascienza`, `2 Romanzo`,
  `3 1970`, `4`, `7 x`, `abc`, `1` seguito da 50 zeri, `0`
- **Output atteso** (dopo il menu):
  ```
    Il barone rampante     Italo Calvino   romanzo      1957  libere 1
    Le citta' invisibili   Italo Calvino   romanzo      1972  libere 0
    Trovati: 2
    Se questo e' un uomo   Primo Levi      memorie      1947  libere 3
    Il sistema periodico   Primo Levi      racconti     1975  libere 0
    Trovati: 2
    Fahrenheit 451         Ray Bradbury    fantascienza 1953  libere 2
    Io, robot              Isaac Asimov    fantascienza 1950  libere 1
    Trovati: 2
    Trovati: 0
    Le citta' invisibili   Italo Calvino   romanzo      1972  libere 0
    Il sistema periodico   Primo Levi      racconti     1975  libere 0
    Trovati: 2
    Il barone rampante     Italo Calvino   romanzo      1957  libere 1
    Fahrenheit 451         Ray Bradbury    fantascienza 1953  libere 2
    Io, robot              Isaac Asimov    fantascienza 1950  libere 1
    Se questo e' un uomo   Primo Levi      memorie      1947  libere 3
    La luna e i falo'      Cesare Pavese   romanzo      1950  libere 2
    Trovati: 5
    Filtro inesistente.
    Filtro inesistente.
    Trovati: 0
  ```
