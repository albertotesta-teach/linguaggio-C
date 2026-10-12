# Analisi – 050-problema-scheda-dispositivo.c

## 1. Problema

Prima della verifica di sistemi e reti il tecnico controlla le schede dei PC del laboratorio. Ogni scheda ha due parti, Hardware e Rete, e ogni parte ha la sua funzione di controllo che riceve solo quella parte. Una funzione sul laboratorio controlla anche gli indirizzi IP duplicati.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Hardware` | `cpu, ram_gb, disco_gb` | componenti |
| `Rete` | `ip[4], prefisso, gateway[4]` | configurazione di rete |
| `Dispositivo` | `nome, hw, rete` | scheda del PC |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `laboratorio` | `Dispositivo[]` | 5 | Schede dei PC |
| `errori` | `int` | — | Schede da correggere |
| `maschera` | `unsigned long` | — | Maschera di sottorete a 32 bit |

| Funzione | Compito |
|----------|---------|
| `hardware_valido(h)` | RAM almeno 8 GB, disco almeno 256 GB |
| `rete_valida(r)` | Numeri da 0 a 255, prefisso da 8 a 30, gateway nella sottorete e diverso dal PC |
| `valore_ip(ip)` | Quattro numeri in un unico valore a 32 bit |
| `stampa_dispositivo(d)` | Usa d->hw e d->rete |
| `controlla_laboratorio(lab, n)` | Controlla le parti e i duplicati, conta gli errori |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Scheda corretta

**a) Input** – PC-01

**b) Output** – "ok"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – entrambe le funzioni di controllo restituiscono 1 e nessun PC precedente ha lo stesso IP.

### Caso d'uso 2 – Gateway fuori rete

**a) Input** – PC-02 con gateway 192.168.1.1

**b) Output** – "gateway fuori dalla sottorete"

**c) Variabili di supporto** – `maschera`

**d) Vincoli** – /24 = 255.255.255.0

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – (ip AND maschera) diverso da (gateway AND maschera).

### Caso d'uso 3 – Hardware e duplicati

**a) Input** – PC-03 e PC-04

**b) Output** – "RAM insufficiente: 4 GB"; "indirizzo gia' usato da PC-01"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni PC confrontare l'IP con quelli dei PC precedenti.

### Caso d'uso 4 – Numeri non validi

**a) Input** – PC-05 con 192.168.10.300

**b) Output** – "indirizzo o gateway con numeri oltre 255"; "Schede da correggere: 4 su 5"

**c) Variabili di supporto** – `errori`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ip_valido controlla i quattro numeri prima di ogni altro calcolo.
