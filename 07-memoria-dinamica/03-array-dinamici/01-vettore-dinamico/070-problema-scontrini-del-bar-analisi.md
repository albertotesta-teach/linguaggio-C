# Analisi – 070-problema-scontrini-del-bar.c

## 1. Problema

Il bar della scuola registra le vendite della giornata, una riga
`prodotto prezzo quantità` per scontrino, in un vettore dinamico di
`Voce`. A fine giornata il programma costruisce un secondo vettore con una
voce per prodotto (quantità sommate, incasso nel campo prezzo) usando le
stesse funzioni, poi stampa il riepilogo, l'incasso totale e il prodotto
più venduto.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| riga | testo | `prodotto prezzo quantita`; `FINE` termina |

### Output

- `vendita non valida` per ogni riga scartata.
- `Vendite registrate: V, prodotti diversi: P`.
- Per ogni prodotto: quantità e incasso.
- `Incasso: T euro` e `Piu' venduto: X` (se ci sono vendite).
- `Memoria insufficiente.`

### Vincoli

- Vettore `{Voce *dati; int n; int capacita;}` con capacità iniziale 4 e
  raddoppio; il `main` usa solo le funzioni del vettore.
- `elemento` restituisce un puntatore alla voce, valido solo fino alla
  prossima `aggiungi` (che può spostare il blocco).
- Prezzo positivo, quantità almeno 1.
- Nel riepilogo il campo `prezzo` contiene l'incasso del prodotto.
- A parità di quantità vale il primo prodotto.
- Una vendita per riga: il resto viene scartato. A fine input il
  programma termina come con `FINE`.

### Assunzioni

- Il nome del prodotto è una sola parola.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Voce` | `typedef struct { char prodotto[20]; double prezzo; int quantita; } Voce;` | Una vendita o un prodotto del riepilogo |
| `Elenco` | `typedef struct { Voce *dati; int n; int capacita; } Elenco;` | Vettore dinamico |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `vendite`, `riepilogo` | `Elenco *` | I due vettori |
| `voce` | `Voce *` | Voce del riepilogo da aggiornare |
| `migliore`, `incasso` | `int`, `double` | Risultati |

| Funzione | Compito |
|----------|---------|
| `crea_elenco`, `distruggi_elenco` | Allocazione e liberazione |
| `aggiungi`, `lunghezza`, `elemento` | Uso del vettore |
| `cerca(e, prodotto)` | Posizione del prodotto, −1 se assente |

### Algoritmo in linguaggio naturale

1. Creare i due vettori.
2. Leggere le vendite fino a `FINE` aggiungendo quelle valide.
3. Per ogni vendita: se il prodotto non è nel riepilogo aggiungerlo con
   l'incasso, altrimenti sommare quantità e incasso.
4. Stampare riepilogo, incasso e prodotto più venduto; distruggere i
   vettori.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Una mattina al bar

- **Input:** `panino 2.50 1`, `acqua 0.80 2`, `panino 2.50 2 extra`,
  `caffe 1 3`, `pizzetta 1.20 0`, `brioche x 1`, `acqua 0.80 1`, `FINE`
- **Output atteso:**
  ```
  Vendite (prodotto prezzo quantita', FINE per terminare):
    vendita non valida
    vendita non valida

  Vendite registrate: 5, prodotti diversi: 3
    panino         3 pz     7.50 euro
    acqua          3 pz     2.40 euro
    caffe          3 pz     3.00 euro
  Incasso: 12.90 euro
  Piu' venduto: panino
  ```
  (a parità di 3 pezzi vale il primo prodotto).

### Test 2 – Nessuna vendita

- **Input:** `FINE`
- **Output atteso:** `Vendite registrate: 0, prodotti diversi: 0` e
  `Incasso: 0.00 euro`.
