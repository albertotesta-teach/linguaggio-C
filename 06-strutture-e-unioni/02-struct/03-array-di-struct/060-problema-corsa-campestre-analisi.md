# Analisi – 060-problema-corsa-campestre.c

## 1. Problema

Alla corsa campestre corrono allievi e juniores. Il programma trova il
podio di ogni categoria senza ordinare l'array: cerca tre volte il tempo
minimo tra gli atleti della categoria non ancora premiati. Gli atleti
ritirati (tempo 0) non entrano in classifica. Per il secondo e il terzo
stampa anche il distacco dal primo. Gli atleti sono un array di struct
`Atleta`.

## 2. Analisi

### Input

Nessun input da tastiera: i risultati sono nel sorgente.

| Atleta | Classe | Categoria | Tempo (s) |
|--------|--------|-----------|-----------|
| Rinaldi | 1A | A | 742 |
| Gentile | 4B | J | 701 |
| Pellegrini | 2C | A | 728 |
| Mancini | 5A | J | 689 |
| Serra | 1B | A | 0 (ritirato) |
| Vitale | 3A | J | 715 |
| Testa | 2A | A | 735 |
| Fabbri | 4C | J | 698 |
| Marchi | 2B | A | 751 |
| Riva | 5B | J | 0 (ritirato) |

### Output

- Per ogni categoria: `=== NOME (N arrivati) ===` e fino a tre righe con
  posizione, nome, classe, tempo in `m'ss"` e, dal secondo, `+D s`.

### Vincoli

- Categoria `'A'` = allievi, `'J'` = juniores.
- L'array non viene ordinato: un vettore `premiato` ricorda chi è già sul
  podio.
- Il podio ha al massimo tre posti e non più degli arrivati.
- A parità di tempo viene prima l'atleta che compare prima nell'array.

### Assunzioni

- I tempi sono in secondi interi.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Atleta` | `typedef struct { char nome[20]; char classe[4]; char categoria; int tempo; } Atleta;` | Un concorrente |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `atleti` | `Atleta[10]` | Array di struct |
| `premiato` | `int[10]` | 1 se l'atleta è già sul podio |
| `categorie`, `nomi_categorie` | `const char[2]`, `const char *[2]` | Codici e nomi delle categorie |
| `arrivati` | `int` | Atleti della categoria con tempo positivo |
| `migliore` | `int` | Indice del più veloce non premiato (−1 = nessuno) |
| `tempo_primo` | `int` | Tempo del vincitore, per i distacchi |

### Algoritmo in linguaggio naturale

1. Per ogni categoria:
   1. contare gli arrivati e stampare l'intestazione;
   2. per ogni posto da 1 a 3 (non oltre gli arrivati): cercare tra gli
      atleti della categoria, arrivati e non premiati, quello con il tempo
      minimo; segnarlo come premiato; stamparlo con il distacco dal primo.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Cosa si verifica:** podio per categoria, esclusione dei ritirati,
  distacchi.
- **Input:** nessuno.
- **Output atteso:**
  ```
  === ALLIEVI (4 arrivati) ===
    1. Pellegrini  2C  12'08"
    2. Testa       2A  12'15"  +7 s
    3. Rinaldi     1A  12'22"  +14 s
  === JUNIORES (4 arrivati) ===
    1. Mancini     5A  11'29"
    2. Fabbri      4C  11'38"  +9 s
    3. Gentile     4B  11'41"  +12 s
  ```

### Test 2 – Meno di tre arrivati

- **Cosa si verifica:** il podio si ferma al numero di arrivati.
- **Procedura:** mettere tempo 0 a Rinaldi e Pellegrini.
- **Output atteso:**
  ```
  === ALLIEVI (2 arrivati) ===
    1. Testa       2A  12'15"
    2. Marchi      2B  12'31"  +16 s
  ```

### Test 3 – Pari merito

- **Cosa si verifica:** a parità vale l'ordine dell'array.
- **Procedura:** dare a Testa il tempo 728, come Pellegrini.
- **Output atteso:** `1. Pellegrini 2C 12'08"`, `2. Testa 2A 12'08"  +0 s`.
