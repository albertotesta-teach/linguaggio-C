# Analisi – 080-problema-tariffe-parcheggio.c

## 1. Problema

Il parcheggio multipiano offre tre tariffe: oraria (1.50 euro per ora
iniziata), prima ora gratis (poi 2.00 euro per ora iniziata) e giornaliera
(9.00 euro fissi). Per ogni durata letta in minuti il programma stampa il
costo con ogni tariffa e quella più conveniente; 0 termina. Le tariffe
hanno il tipo `Tariffa` e la funzione che sceglie la migliore restituisce
un puntatore a funzione.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `minuti` | `int` | Durata della sosta, positiva; 0 termina |

### Output

- Per ogni durata: il costo con le tre tariffe e
  `Conviene: <tariffa> (C euro)`.
- `Durata non valida.` per una durata negativa o non numerica.

### Vincoli

- `typedef double (*Tariffa)(int minuti);`: anche `giornaliera` riceve i
  minuti, pur non usandoli.
- Ore iniziate = `(minuti + 59) / 60` (arrotondamento per eccesso).
- Prima ora gratis: fino a 60 minuti costa 0, poi 2.00 euro per ogni ora
  iniziata oltre la prima.
- A parità di costo vale la prima tariffa della tabella.
- Il nome della tariffa migliore si trova confrontando il puntatore
  restituito con quelli della tabella.
- Fine input equivale a 0.

### Assunzioni

- Una sosta dura al massimo un giorno (la tariffa giornaliera è fissa).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Tariffa` | `typedef double (*Tariffa)(int minuti);` | Funzione che calcola il costo di una sosta |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `nomi` | `const char *[3]` | Nomi delle tariffe |
| `tariffe` | `const Tariffa[3]` | Funzioni di calcolo |
| `migliore` | `Tariffa` | Tariffa restituita da `piu_conveniente` |
| `letti` | `int` | Valore restituito da `scanf` |
| `t` | `int` | Indice della tariffa |

| Funzione | Compito |
|----------|---------|
| `oraria`, `prima_ora_gratis`, `giornaliera` | Costo di una sosta |
| `ore_iniziate(minuti)` | Ore arrotondate per eccesso |
| `piu_conveniente(minuti, tariffe, n)` | Restituisce la tariffa con il costo più basso |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché la durata non è 0:
   1. leggere la durata (fine input → 0; testo → non valida);
   2. se positiva, stampare il costo con ogni tariffa, ottenere la tariffa
      migliore, cercarne il nome nella tabella e stamparla con il costo;
   3. se negativa, segnalarla e continuare.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Sosta breve

- **Cosa si verifica:** la prima ora gratis.
- **Input:** `45`, `0`
- **Output atteso:**
  ```
    oraria             1.50 euro
    prima ora gratis   0.00 euro
    giornaliera        9.00 euro
    Conviene: prima ora gratis (0.00 euro)
  ```

### Test 2 – Ore iniziate

- **Cosa si verifica:** l'arrotondamento per eccesso al confine dell'ora.
- **Input:** `60`, `61`, `0`
- **Valori intermedi attesi:** 60 minuti = 1 ora (gratis); 61 minuti =
  2 ore per l'oraria (3.00) e 1 ora oltre la prima (2.00).
- **Output atteso:** `Conviene: prima ora gratis (0.00 euro)`, poi
  `oraria 3.00`, `prima ora gratis 2.00`,
  `Conviene: prima ora gratis (2.00 euro)`.

### Test 3 – Cambio di tariffa conveniente

- **Cosa si verifica:** al crescere della durata conviene l'oraria e poi la
  giornaliera.
- **Input:** `300`, `500`, `0`
- **Output atteso:**
  ```
    oraria             7.50 euro
    prima ora gratis   8.00 euro
    giornaliera        9.00 euro
    Conviene: oraria (7.50 euro)
    oraria            13.50 euro
    prima ora gratis  16.00 euro
    giornaliera        9.00 euro
    Conviene: giornaliera (9.00 euro)
  ```

### Test 4 – Durata non valida

- **Input:** `-3`, `abc`, `0`
- **Output atteso:**
  ```
    Durata non valida.
    Durata non valida.
  ```
