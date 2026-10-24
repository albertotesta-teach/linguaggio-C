# Analisi – 040-problema-indirizzo-ip.c

## 1. Problema

Nel laboratorio di reti si calcolano maschera, indirizzo di rete e di
broadcast di un indirizzo IPv4 con prefisso, e si controlla se un secondo
indirizzo è nella stessa rete. L'indirizzo è una `union`: come numero a 32
bit per i calcoli con la maschera, come quattro byte per la stampa. Su una
macchina little-endian il primo numero dell'indirizzo sta in `byte[3]`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[64]` | `a.b.c.d/prefisso e.f.g.h`; `FINE` termina |

### Output

- `maschera`, `rete`, `broadcast` in notazione puntata.
- `in memoria: XX XX XX XX (byte[0] ... byte[3])`: i byte del primo
  indirizzo nell'ordine in cui stanno in memoria.
- `<altro> e' nella stessa rete` / `NON e' nella stessa rete`.
- `Dati non validi.`

### Vincoli

- I due campi della union occupano la stessa memoria: si scrive
  `numero` e si leggono i `byte`.
- Maschera = `0xFFFFFFFF << (32 − prefisso)`; rete = IP AND maschera;
  broadcast = rete OR NOT maschera.
- Prefisso da 1 a 30; numeri dell'indirizzo da 0 a 255.
- Stessa rete: (altro AND maschera) = rete.
- Una riga più lunga del buffer viene troncata e il resto scartato. A fine
  input il programma termina come con `FINE`.

### Assunzioni

- Macchina little-endian (x86, ARM): `stampa_ip` legge i byte da 3 a 0.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Indirizzo` | `typedef union { uint32_t numero; uint8_t byte[4]; } Indirizzo;` | Indirizzo IPv4 visto in due modi |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `primo`, `secondo` | `char[64]` | I due indirizzi come testo |
| `ip`, `altro`, `maschera`, `rete`, `broadcast` | `Indirizzo` | Valori calcolati |
| `prefisso` | `int` | Bit della parte di rete |
| `resto` | `int` | Caratteri scartati di una riga lunga |

| Funzione | Compito |
|----------|---------|
| `leggi_ip(testo, ip)` | Converte `a.b.c.d`; 0 se non valido |
| `stampa_ip(ip)` | Stampa i quattro byte in notazione puntata |

### Algoritmo in linguaggio naturale

1. Finché non si termina:
   1. leggere una riga (fine input → fine), scartare il resto se troppo
      lunga;
   2. con `FINE` terminare;
   3. separare primo indirizzo, prefisso e secondo indirizzo e
      convertirli; se qualcosa non è valido segnalarlo;
   4. calcolare maschera, rete e broadcast, stamparli con i byte in
      memoria e il confronto del secondo indirizzo.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Reti diverse

- **Cosa si verifica:** calcoli con prefissi /24, /8, /26, ordine dei byte
  in memoria, dati non validi.
- **Input:** `192.168.10.37/24 192.168.10.200`, `10.1.2.3/8 11.0.0.1`,
  `172.16.5.130/26 172.16.5.190`, `192.168.1.300/24 1.1.1.1`,
  `192.168.1.1/31 192.168.1.2`, `ciao`, una riga di 70 cifre, `FINE`
- **Valori intermedi attesi:** /26 → maschera ...192; 130 AND 192 = 128;
  broadcast 128 + 63 = 191. 192.168.10.37 = 0xC0A80A25: in memoria
  25 0A A8 C0.
- **Output atteso:**
  ```
    maschera  255.255.255.0
    rete      192.168.10.0
    broadcast 192.168.10.255
    in memoria: 25 0A A8 C0 (byte[0] ... byte[3])
    192.168.10.200 e' nella stessa rete
    maschera  255.0.0.0
    rete      10.0.0.0
    broadcast 10.255.255.255
    in memoria: 03 02 01 0A (byte[0] ... byte[3])
    11.0.0.1 NON e' nella stessa rete
    maschera  255.255.255.192
    rete      172.16.5.128
    broadcast 172.16.5.191
    in memoria: 82 05 10 AC (byte[0] ... byte[3])
    172.16.5.190 e' nella stessa rete
    Dati non validi.
    Dati non validi.
    Dati non validi.
    Dati non validi.
  ```
