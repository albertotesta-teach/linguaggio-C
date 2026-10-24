# Analisi – 080-problema-risparmio-memoria.c

## 1. Problema

L'inventario del laboratorio contiene componenti, strumenti e manuali,
ognuno con dati diversi. Il programma confronta una struct con tutti i
campi e una struct con i dati specifici in una `union`, e calcola la
memoria occupata e risparmiata per il numero di articoli letto.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `articoli` | `long` | Numero di articoli, da 1 a 100000 |

### Output

- Le dimensioni (`sizeof`) delle tre parti e delle due struct.
- Un articolo di esempio letto dalla union.
- Memoria con la struct completa, con la union, risparmio in byte e in
  percentuale.
- `Numero non valido (da 1 a 100000).`

### Vincoli

- La union occupa quanto il suo campo più grande (`Strumento`, 32 byte),
  la struct completa la somma delle tre parti.
- Il campo `tipo` dice quale membro della union è valido; si legge solo
  quello.
- Le dimensioni dipendono dal compilatore (allineamento): i valori del
  test sono quelli di un sistema a 64 bit con gcc.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `TipoArticolo` | `typedef enum { COMPONENTE, STRUMENTO, MANUALE } TipoArticolo;` | Tipo dell'articolo |
| `Componente`, `Strumento`, `Manuale` | struct | Dati specifici |
| `ArticoloCompleto` | struct con le tre parti | Versione senza union |
| `ArticoloCompatto` | struct con `union { ... } dati` | Versione con union |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `esempio` | `ArticoloCompatto` | Resistenza R-0047, 4700 ohm, 5% |
| `articoli`, `completa`, `compatta` | `long` | Numero e memoria |

### Algoritmo in linguaggio naturale

1. Stampare le dimensioni e l'esempio.
2. Leggere il numero di articoli; se non valido segnalarlo.
3. Calcolare e stampare la memoria delle due versioni e il risparmio.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – 1000 articoli

- **Input:** `1000`
- **Output atteso:**
  ```
  sizeof(Componente) = 16, sizeof(Strumento) = 32, sizeof(Manuale) = 28
  sizeof(ArticoloCompleto) = 96 byte
  sizeof(ArticoloCompatto) = 48 byte
  Esempio: R-0047, 4700 ohm +/- 5%

  Articoli in inventario:   struct con tutti i campi:    96000 byte
    struct con union:            48000 byte
    risparmio:                   48000 byte (50%)
  ```

### Test 2 – Numero non valido

- **Input:** `0` (poi `abc`)
- **Output atteso:** `Numero non valido (da 1 a 100000).`
