# Analisi – 060-problema-codice-prodotto.c

## 1. Problema

Un sistema di magazzino utilizza codici prodotto nel formato `CAT-NNN-XX`.
Il programma deve estrarre le componenti di un codice (categoria, progressivo,
variante) accedendo ai caratteri per indice, e verificare se due prodotti
appartengono alla stessa categoria confrontando i caratteri uno a uno.

---

## 2. Analisi

### Input
Nessun input da tastiera: i tre codici sono stringhe inizializzate nel
codice.

| Variabile   | Tipo     | Dimensione | Descrizione                          |
|-------------|----------|------------|--------------------------------------|
| `prodotto1` | `char[]` | 11         | `ELE-042-BL` (10 caratteri + `'\0'`) |
| `prodotto2` | `char[]` | 11         | `ELE-107-RO`                         |
| `prodotto3` | `char[]` | 11         | `ALI-003-VE`                         |

### Output
- L'elenco dei tre codici;
- categoria, progressivo e variante del primo prodotto;
- l'esito del confronto di categoria tra il primo e il secondo prodotto e
  tra il primo e il terzo;
- l'esito della verifica dei separatori del primo prodotto.

Struttura del codice:
```
Indice:  0    1    2    3    4    5    6    7    8    9    10
         'E'  'L'  'E'  '-'  '0'  '4'  '2'  '-'  'B'  'L'  '\0'
         categoria      sep  progressivo    sep  variante
```

### Vincoli
- Le componenti si copiano carattere per carattere saltando i separatori
  (indici 3 e 7) e si chiudono con `'\0'`
- Due prodotti hanno la stessa categoria se i primi 3 caratteri coincidono;
  il confronto avviene carattere per carattere, senza `strcmp`, e si ferma
  alla prima differenza tramite il flag nella condizione del `while`
- Il formato è integro se i caratteri agli indici 3 e 7 sono `'-'`
- Il confronto distingue maiuscole e minuscole

### Assunzioni
- I codici hanno sempre la lunghezza del formato

### Variabili di supporto

| Variabile          | Tipo     | Dimensione | Descrizione                         |
|--------------------|----------|------------|-------------------------------------|
| `categoria`        | `char[]` | 4          | 3 lettere + `'\0'`                  |
| `progressivo`      | `char[]` | 4          | 3 cifre + `'\0'`                    |
| `variante`         | `char[]` | 3          | 2 lettere + `'\0'`                  |
| `i`                | `int`    | —          | Indice del confronto                |
| `stessa_categoria` | `int`    | —          | Flag, inizialmente 1                |

### Algoritmo in linguaggio naturale
1. Stampare i tre codici.
2. Copiare i caratteri 0–2, 4–6 e 8–9 del primo codice nelle tre
   componenti, aggiungere i terminatori e stamparle.
3. Per ciascuna coppia (1–2 e 1–3): porre `stessa_categoria = 1`; per i da
   0 a 2, finché è vero, azzerarlo se i caratteri sono diversi; stampare
   l'esito.
4. Verificare i separatori agli indici 3 e 7 e stampare l'esito.

---

## 3. Casi di test

I codici sono fissi nel codice: il Test 2 richiede di modificare il primo e
ricompilare.

### Test 1 – Estrazione e confronti
- **Output atteso:**
```
Analisi Prodotto 1 (ELE-042-BL):
  Categoria   : ELE
  Progressivo : 042
  Variante    : BL

Confronto categorie:
  ELE-042-BL e ELE-107-RO: STESSA categoria (ELE)
  ELE-042-BL e ALI-003-VE: categorie DIVERSE

Verifica integrità formato ELE-042-BL:
  Separatori '-' in posizione corretta: formato VALIDO
```

### Test 2 – Separatore errato
- **Procedura:** sostituire il primo codice con `ELE_042-BL`
- **Output atteso:**
  `ERRORE: separatori mancanti o in posizione errata`
