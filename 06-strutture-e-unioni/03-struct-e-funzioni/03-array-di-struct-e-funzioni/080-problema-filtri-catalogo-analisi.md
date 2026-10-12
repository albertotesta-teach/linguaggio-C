# Analisi – 080-problema-filtri-catalogo.c

## 1. Problema

Gli studenti cercano nel catalogo della biblioteca scegliendo un filtro da un menu: autore, genere, anno di pubblicazione o disponibilità. Ogni filtro è una funzione con lo stesso prototipo, raccolta in una tabella di Filtro; mostra applica il filtro scelto a tutto l'array.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Libro` | `titolo, autore, genere, anno, copie_libere` | scheda del catalogo |
| `Filtro` | `int (*)(const Libro *, const char *)` | funzione di selezione |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `catalogo` | `Libro[]` | 7 | Libri |
| `filtri` | `Filtro[]` | 4 | Funzioni di filtro |
| `descrizioni` | `const char *[]` | 4 | Voci del menu |
| `valore` | `char[]` | 20 | Valore di riferimento |

| Funzione | Compito |
|----------|---------|
| `per_autore, per_genere, dopo_anno, disponibile` | 1 se il libro passa il filtro |
| `mostra(catalogo, n, f, valore)` | Stampa i libri che passano e restituisce quanti sono |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Filtro per autore

**a) Input** – `1 Calvino`

**b) Output** – due libri di Italo Calvino

**c) Variabili di supporto** – `filtri[0]`

**d) Vincoli** – l'autore contiene il testo (strstr)

**e) Assunzioni** – maiuscole come nel catalogo

**f) Algoritmo in linguaggio naturale** – mostra chiama f(&catalogo[i], valore).

### Caso d'uso 2 – Filtro per anno

**a) Input** – `3 1960`

**b) Output** – due libri del 1972 e del 1975

**c) Variabili di supporto** – —

**d) Vincoli** – anno >= valore

**e) Assunzioni** – il valore è un numero

**f) Algoritmo in linguaggio naturale** – dopo_anno converte il testo con atoi.

### Caso d'uso 3 – Disponibili e menu

**a) Input** – `4 x`; `9 a`

**b) Output** – cinque libri; "Filtro inesistente."

**c) Variabili di supporto** – —

**d) Vincoli** – scelta 1-4

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – disponibile ignora il valore con (void).
