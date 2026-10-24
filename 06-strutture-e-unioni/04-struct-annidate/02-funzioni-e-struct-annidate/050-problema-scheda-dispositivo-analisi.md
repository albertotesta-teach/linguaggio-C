# Analisi – 050-problema-scheda-dispositivo.c

## 1. Problema

Prima della verifica di sistemi e reti il tecnico controlla le schede dei
PC del laboratorio. Ogni scheda (`Dispositivo`) ha due parti annidate,
`Hardware` e `Rete`, e ogni parte ha la sua funzione di controllo che
riceve solo quella parte. Una funzione sul laboratorio controlla anche gli
indirizzi IP duplicati e conta le schede da correggere.

## 2. Analisi

### Input

Nessun input da tastiera: le schede sono nel sorgente.

| PC | CPU | RAM | Disco | IP/prefisso | Gateway |
|----|-----|-----|-------|-------------|---------|
| PC-01 | i5 | 16 | 512 | 192.168.10.11/24 | 192.168.10.1 |
| PC-02 | i3 | 8 | 256 | 192.168.10.12/24 | 192.168.1.1 |
| PC-03 | i5 | 4 | 512 | 192.168.10.13/24 | 192.168.10.1 |
| PC-04 | i7 | 16 | 1024 | 192.168.10.11/24 | 192.168.10.1 |
| PC-05 | i5 | 16 | 512 | 192.168.10.300/24 | 192.168.10.1 |

### Output

- Per ogni PC la riga della scheda e, sotto, gli errori trovati oppure
  `ok`.
- `Schede da correggere: N su 5`.

### Vincoli

- Hardware: almeno 8 GB di RAM e 256 GB di disco.
- Rete: ogni numero dell'IP e del gateway tra 0 e 255; prefisso da 8 a
  30; gateway nella stessa sottorete (IP AND maschera uguali); IP diverso
  dal gateway.
- Un IP è duplicato se uguale a quello di un PC precedente.
- `hardware_valido` riceve `&lab[i].hw`, `rete_valida` riceve
  `&lab[i].rete`: ogni funzione vede solo la sua parte.
- L'IP si confronta come numero a 32 bit; la maschera è
  `0xFFFFFFFF << (32 − prefisso)`.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Hardware` | `typedef struct { char cpu[12]; int ram_gb; int disco_gb; } Hardware;` | Parte hardware |
| `Rete` | `typedef struct { int ip[4]; int prefisso; int gateway[4]; } Rete;` | Parte di rete |
| `Dispositivo` | `typedef struct { char nome[8]; Hardware hw; Rete rete; } Dispositivo;` | Scheda completa |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `laboratorio` | `Dispositivo[5]` | Le schede |
| `errori` | `int` | Schede con almeno un errore |
| `maschera` | `unsigned long` | Maschera di sottorete |

| Funzione | Compito |
|----------|---------|
| `ip_valido(ip)` | Numeri tra 0 e 255 |
| `valore_ip(ip)` | I quattro numeri come un valore a 32 bit |
| `stesso_ip(a, b)` | Uguaglianza di due IP |
| `stampa_ip(ip)` | Stampa in notazione puntata |
| `hardware_valido(h)` | Controlla RAM e disco, stampa gli errori |
| `rete_valida(r)` | Controlla IP, prefisso, sottorete, gateway |
| `stampa_dispositivo(d)` | Riga della scheda |
| `controlla_laboratorio(lab, n)` | Controlla tutte le schede e i duplicati |

### Algoritmo in linguaggio naturale

1. Per ogni PC: stampare la scheda, controllare l'hardware, controllare la
   rete, confrontare l'IP con quelli dei PC precedenti; se tutto va bene
   stampare `ok`, altrimenti contare la scheda.
2. Stampare il numero di schede da correggere.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Cosa si verifica:** un errore diverso per ogni PC dal secondo al
  quinto.
- **Input:** nessuno.
- **Output atteso:**
  ```
  PC-01  i5   16 GB RAM   512 GB  192.168.10.11/24 gw 192.168.10.1
      ok
  PC-02  i3    8 GB RAM   256 GB  192.168.10.12/24 gw 192.168.1.1
      gateway fuori dalla sottorete
  PC-03  i5    4 GB RAM   512 GB  192.168.10.13/24 gw 192.168.10.1
      RAM insufficiente: 4 GB
  PC-04  i7   16 GB RAM  1024 GB  192.168.10.11/24 gw 192.168.10.1
      indirizzo gia' usato da PC-01
  PC-05  i5   16 GB RAM   512 GB  192.168.10.300/24 gw 192.168.10.1
      indirizzo o gateway con numeri oltre 255

  Schede da correggere: 4 su 5
  ```

### Test 2 – Prefisso più corto

- **Cosa si verifica:** con /16 il gateway 192.168.1.1 è nella stessa
  sottorete di 192.168.10.12.
- **Procedura:** cambiare il prefisso di PC-02 in 16.
- **Output atteso:** `ok` sotto PC-02 e `Schede da correggere: 3 su 5`.
