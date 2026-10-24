# Analisi – 070-problema-conto-della-gita.c

## 1. Problema

Il docente organizzatore prepara il conto della gita: alcune voci sono a
persona (albergo, ingressi, assicurazione), altre sono totali (pullman,
guida). Gli accompagnatori partecipano ma non pagano; il totale si divide
tra gli studenti con arrotondamento al centesimo superiore. Gli importi
sono struct piccole (`Importo`) passate per valore; la funzione sulla voce
riceve `const Voce *` e passa `v->costo` alle funzioni sugli importi.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `studenti` | `int` | Da 10 a 50 |
| `docenti` | `int` | Accompagnatori, almeno uno ogni 15 studenti |
| voci | nel sorgente | Pullman 1450.00 (totale), Albergo 58.50 a persona, Museo Egizio 6.00 a persona, Guida 180.00 (totale), Assicurazione 3.50 a persona |

### Output

- Una riga per voce (con `costo x partecipanti =` per le voci a persona)
  e il totale.
- `Quota per studente: Q euro (S studenti, D accompagnatori gratuiti)`.
- `Raccolto R, avanzo A` (differenza dovuta all'arrotondamento).
- `Dati non validi: ...` oppure `Servono almeno N accompagnatori per S
  studenti.`

### Vincoli

- I conti si fanno in centesimi interi, senza errori di arrotondamento dei
  `double`.
- Voci a persona: costo × (studenti + accompagnatori).
- Quota = ⌈totale / studenti⌉ al centesimo; l'avanzo è
  quota × studenti − totale.
- Accompagnatori necessari: ⌈studenti / 15⌉.

### Assunzioni

- Gli accompagnatori pagano la loro parte attraverso la quota degli
  studenti.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Importo` | `typedef struct { int euro; int centesimi; } Importo;` | Una somma di denaro |
| `Voce` | `typedef struct { char descrizione[24]; Importo costo; int a_persona; } Voce;` | Una voce del conto con l'importo annidato |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `voci` | `Voce[5]` | Le voci del conto |
| `partecipanti` | `int` | Studenti + accompagnatori |
| `totale`, `parziale`, `quota`, `raccolto` | `Importo` | Importi calcolati |
| `STUDENTI_PER_DOCENTE` | `#define` | 15 |

| Funzione | Compito |
|----------|---------|
| `in_centesimi(a)`, `da_centesimi(c)` | Conversioni |
| `somma(a, b)`, `per(a, volte)` | Operazioni sugli importi |
| `diviso_per_eccesso(a, parti)` | Divisione arrotondata per eccesso |
| `costo_voce(v, partecipanti)` | Costo complessivo di una voce |
| `stampa_importo(a)` | Stampa `E.CC euro` |

### Algoritmo in linguaggio naturale

1. Leggere studenti e accompagnatori; se non validi o insufficienti,
   segnalarlo.
2. Per ogni voce calcolare il costo complessivo, stamparlo e sommarlo al
   totale.
3. Calcolare la quota per eccesso, il raccolto e l'avanzo e stamparli.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – 30 studenti e 2 accompagnatori

- **Valori intermedi attesi:** 32 partecipanti; totale 3806.00;
  380600 / 30 = 12686.67 → 12687 centesimi; raccolto 3806.10.
- **Input:** `30 2`
- **Output atteso:**
  ```
  Studenti e accompagnatori:   Pullman (2 giorni)                         1450.00 euro
    Albergo, 1 notte        58.50 euro x 32 =  1872.00 euro
    Museo Egizio             6.00 euro x 32 =   192.00 euro
    Guida                                       180.00 euro
    Assicurazione            3.50 euro x 32 =   112.00 euro
    Totale                                     3806.00 euro
  Quota per studente:   126.87 euro (30 studenti, 2 accompagnatori gratuiti)
  Raccolto  3806.10 euro, avanzo     0.10 euro
  ```

### Test 2 – Accompagnatori insufficienti

- **Input:** `30 1`; poi `31 2`
- **Output atteso:** `Servono almeno 2 accompagnatori per 30 studenti.`;
  `Servono almeno 3 accompagnatori per 31 studenti.`

### Test 3 – Gruppo grande

- **Input:** `45 3`
- **Output atteso:** totale 4894.00, `Quota per studente:   108.76 euro`,
  avanzo 0.20.

### Test 4 – Dati non validi

- **Input:** `8 1` (poi `abc`)
- **Output atteso:** `Dati non validi: da 10 a 50 studenti e almeno un
  accompagnatore.`
