# Analisi – 060-problema-consumo-acqua.c

## 1. Problema

Una famiglia di 3 persone annota a fine mese la lettura del contatore
dell'acqua in metri cubi. Il consumo del mese è la differenza tra due
letture consecutive. Per i sei mesi del semestre il programma calcola il
consumo in metri cubi e in litri, il consumo giornaliero per persona, il
mese con il consumo più alto e quanti mesi superano la soglia di 150 litri
per persona al giorno. I due tipi `MetriCubi` e `Litri` distinguono le
unità di misura.

## 2. Analisi

### Input

Nessun input da tastiera: i dati sono nel sorgente.

| Dato | Tipo | Valore |
|------|------|--------|
| `letture` | `MetriCubi[7]` | 1284.6 (31 dicembre), 1295.3, 1304.9, 1315.8, 1326.1, 1338.4, 1353.0 |
| `giorni` | `int[6]` | 31, 28, 31, 30, 31, 30 |
| `mesi` | `const char *[6]` | da gennaio a giugno |
| `PERSONE` | `#define` | 3 |
| `SOGLIA_GIORNALIERA` | `#define` | 150.0 litri per persona al giorno |

### Output

- Una tabella con mese, consumo in m³, litri, litri per persona al giorno
  e l'indicazione `oltre soglia` quando serve.
- Il consumo totale del semestre in m³ e in litri.
- Il mese con il consumo più alto.
- Il numero di mesi oltre la soglia.

### Vincoli

- Le letture crescono sempre: ogni consumo è positivo.
- 1 m³ = 1000 litri.
- Consumo per persona al giorno = litri del mese / giorni del mese / persone.
- Un mese è "oltre soglia" se il valore è strettamente maggiore di 150.

### Assunzioni

- `letture[0]` è la lettura del 31 dicembre, `letture[m + 1]` quella di
  fine mese `m`.
- A parità di consumo massimo vale il primo mese.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `MetriCubi` | `typedef double MetriCubi;` | Volumi letti dal contatore |
| `Litri` | `typedef double Litri;` | Volumi convertiti in litri |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `del_mese` | `MetriCubi` | Consumo del mese corrente |
| `al_giorno` | `Litri` | Litri per persona al giorno |
| `massimo` | `int` | Indice del mese con il consumo più alto |
| `oltre` | `int` | Contatore dei mesi oltre soglia |

| Funzione | Compito |
|----------|---------|
| `consumo(prima, dopo)` | Differenza tra due letture |
| `in_litri(volume)` | Conversione da m³ a litri |

### Algoritmo in linguaggio naturale

1. Stampare l'intestazione della tabella.
2. Per ogni mese `m`:
   1. calcolare il consumo `letture[m + 1] - letture[m]`;
   2. calcolare i litri per persona al giorno;
   3. stampare la riga, con `oltre soglia` se il valore supera 150, e
      contare il mese;
   4. se il consumo supera quello del mese `massimo`, aggiornare `massimo`.
3. Stampare il consumo totale (ultima lettura meno la prima), il mese con
   il consumo più alto e il numero di mesi oltre soglia.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Cosa si verifica:** calcolo dei consumi, della soglia e del massimo.
- **Input:** nessuno.
- **Valori intermedi attesi:** giugno 1353.0 - 1338.4 = 14.6 m³ = 14600
  litri; 14600 / 30 / 3 ≈ 162 litri per persona al giorno (oltre soglia).
- **Output atteso:**
  ```
    Mese       Consumo m3   Litri   Litri/persona/giorno
    gennaio         10.7    10700           115
    febbraio         9.6     9600           114
    marzo           10.9    10900           117
    aprile          10.3    10300           114
    maggio          12.3    12300           132
    giugno          14.6    14600           162   oltre soglia

  Consumo totale del semestre: 68.4 m3 (68400 litri)
  Mese con il consumo piu' alto: giugno (14.6 m3)
  Mesi oltre 150 litri per persona al giorno: 1
  ```

### Test 2 – Nessun mese oltre soglia

- **Cosa si verifica:** il conteggio vale 0 e nessuna riga è marcata.
- **Procedura:** cambiare l'ultima lettura in `1350.0`.
- **Valori intermedi attesi:** giugno 11.6 m³, 11600 / 30 / 3 ≈ 129 litri.
- **Output atteso:** giugno senza `oltre soglia`; `Mese con il consumo piu'
  alto: maggio (12.3 m3)`; `Mesi oltre 150 litri per persona al giorno: 0`.

### Test 3 – Massimo nel primo mese

- **Cosa si verifica:** il massimo resta all'indice iniziale 0.
- **Procedura:** cambiare la prima lettura in `1270.0`.
- **Valori intermedi attesi:** gennaio 25.3 m³, 25300 / 31 / 3 ≈ 272 litri.
- **Output atteso:** `Mese con il consumo piu' alto: gennaio (25.3 m3)`;
  `Mesi oltre 150 litri per persona al giorno: 2`.
