# Analisi – 070-problema-pacchetto-sensore.c

## 1. Problema

La centralina meteo invia pacchetti di 8 byte. Una `union` sovrappone
l'array dei byte ricevuti e una struct con i campi (temperatura e umidità
in decimi, batteria in mV, numero del sensore, byte di controllo). Il
programma verifica che la struct sia di 8 byte, controlla il byte di
controllo (somma dei primi 7 modulo 256) e stampa i valori.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[64]` | Otto byte esadecimali separati da spazi; `FINE` termina |

### Output

- `sensore S: T gradi, umidita' U%, batteria B mV` con
  `CAMBIARE LE PILE` sotto i 3000 mV.
- `Pacchetto corrotto: controllo errato.`, `Servono 8 byte.`
- Se la struct non occupa 8 byte, un messaggio e il programma non legge
  pacchetti.

### Vincoli

- Si scrivono i byte in `grezzi` e si leggono i campi della struct: i
  valori a 16 bit sono little-endian (byte basso per primo).
- Temperatura con segno (`int16_t`), in decimi di grado; umidità e
  batteria senza segno.
- Ogni byte deve valere al massimo 0xFF.
- Controllo: (somma dei primi 7 byte) mod 256 = ottavo byte.
- Una riga più lunga del buffer viene troncata e il resto scartato. A fine
  input il programma termina come con `FINE`.

### Assunzioni

- Macchina little-endian, come la centralina.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Pacchetto` | `typedef union { uint8_t grezzi[8]; struct { int16_t temperatura; uint16_t umidita; uint16_t batteria; uint8_t sensore; uint8_t controllo; } campi; } Pacchetto;` | Il pacchetto visto come byte e come campi |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `p` | `Pacchetto` | Pacchetto letto |
| `riga` | `char[64]` | Testo letto |
| `resto` | `int` | Caratteri scartati di una riga lunga |
| `BATTERIA_MINIMA` | `#define` | 3000 mV |

| Funzione | Compito |
|----------|---------|
| `leggi_pacchetto(riga, p)` | Legge 8 byte esadecimali; 0 se non sono 8 byte validi |
| `controllo_corretto(p)` | Verifica il byte di controllo |

### Algoritmo in linguaggio naturale

1. Se `sizeof(p.campi)` non è 8 segnalarlo e non continuare.
2. Finché non si termina: leggere una riga (fine input → fine), scartare il
   resto se troppo lunga; con `FINE` terminare; leggere i byte,
   controllarli e stampare i campi.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Pacchetti

- **Input:** `D7 00 E0 01 E4 0C 03 AB`, `D3 FF 84 03 54 0B 07 BF`,
  `D7 00 E0 01 E4 0C 03 AC`, `D7 00 E0`, `D7 00 E0 01 E4 0C 03 1AB`, una
  riga di 70 cifre, `FINE`
- **Valori intermedi attesi:** 0x00D7 = 215 → 21.5 gradi; 0xFFD3 = −45 →
  −4.5 gradi; 0x0CE4 = 3300 mV; controllo del primo pacchetto
  683 mod 256 = 171 = 0xAB.
- **Output atteso:**
  ```
    sensore 3: 21.5 gradi, umidita' 48.0%, batteria 3300 mV
    sensore 7: -4.5 gradi, umidita' 90.0%, batteria 2900 mV  CAMBIARE LE PILE
    Pacchetto corrotto: controllo errato.
    Servono 8 byte.
    Servono 8 byte.
    Servono 8 byte.
  ```
