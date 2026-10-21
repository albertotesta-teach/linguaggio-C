# Analisi – 080-problema-elezione-rappresentanti.c

## 1. Problema

Una classe elegge i due rappresentanti. Le 20 schede sono state trascritte
come stringhe: una scheda vuota è bianca, una scheda con il testo esatto di
un candidato è valida, ogni altro testo è nullo. Il programma fa lo spoglio,
stampa i voti con le percentuali sui voti validi e indica gli eletti; se c'è
un pareggio per il secondo posto segnala che serve un ballottaggio.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `candidati` | `char[4][24]` | Nomi dei candidati: Bianchi Luca, Neri Giulia, Russo Marco, Gallo Sara |
| `schede` | `char[20][24]` | Testo trascritto da ogni scheda |

I dati sono inizializzati nel sorgente: il programma non legge nulla da tastiera.

### Output

- Elenco delle schede nulle con il loro numero e il testo.
- Riepilogo: schede totali, valide, bianche, nulle.
- Voti e percentuale (sui voti validi) di ogni candidato.
- Il primo eletto; i candidati al secondo posto e il secondo eletto,
  oppure la segnalazione di ballottaggio in caso di pareggio.

### Vincoli

- Una scheda è valida solo se il testo coincide esattamente con un candidato
  (`strcmp`): maiuscole diverse o refusi la rendono nulla.
- Le percentuali si calcolano sui voti validi; se `valide` è 0 si stampa 0.
- Il secondo classificato si cerca escludendo il primo.

### Assunzioni

- Le schede sono già trascritte senza spazi in eccesso.
- Il primo posto non è in pareggio (in caso di parità per il primo posto il
  programma elegge il candidato con indice minore e mette l'altro al secondo posto).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `voti` | `int[4]` | Voti di ciascun candidato (parallelo a `candidati`) |
| `bianche`, `nulle`, `valide` | `int` | Conteggi dello spoglio |
| `c` | `int` | Indice del candidato trovato sulla scheda (-1 se nulla) |
| `primo`, `secondo` | `int` | Indici dei primi due classificati |
| `pari_merito` | `int` | Candidati (escluso il primo) con i voti del secondo |

| Funzione | Compito |
|----------|---------|
| `cerca_candidato` | Restituisce l'indice del candidato uguale alla scheda (`strcmp`), oppure -1 |

### Algoritmo in linguaggio naturale

1. Per ogni scheda:
   1. se `strlen(scheda) == 0` incrementare `bianche`;
   2. altrimenti cercare il candidato: se -1 incrementare `nulle` e stampare
      la scheda, se no incrementare `voti[c]` e `valide`.
2. Stampare il riepilogo dello spoglio.
3. Per ogni candidato stampare voti e `100.0 * voti[c] / valide`.
4. Trovare l'indice del massimo (`primo`) e stamparlo come eletto.
5. Trovare il massimo tra gli altri candidati (`secondo`).
6. Stampare tutti i candidati diversi da `primo` con i voti di `secondo`,
   contandoli in `pari_merito`.
7. Se `pari_merito > 1` segnalare il ballottaggio, altrimenti stampare
   `secondo` come eletto.

## 3. Casi di test

### Test 1 – Classificazione delle schede

- **Cosa si verifica**: distinzione tra schede valide, bianche e nulle
  (maiuscole sbagliate, refuso, persona non candidata).
- **Input**: le 20 schede del sorgente, tra cui `""` (2 volte),
  `"neri giulia"`, `"Verdi Paolo"`, `"Neri Giula"`.
- **Valori intermedi attesi**: `bianche` = 2, `nulle` = 3, `valide` = 15.
- **Output atteso**:
  ```
  === SPOGLIO ===
    scheda  8 nulla: "neri giulia"
    scheda 16 nulla: "Verdi Paolo"
    scheda 20 nulla: "Neri Giula"
  Schede: 20  valide: 15  bianche: 2  nulle: 3
  ```

### Test 2 – Percentuali sui voti validi

- **Cosa si verifica**: le percentuali sono calcolate sulle 15 schede valide, non sulle 20 totali.
- **Input**: dati del sorgente.
- **Valori intermedi attesi**: `voti` = {2, 5, 4, 4}; ad esempio 100 × 5 / 15 = 33.3.
- **Output atteso**:
  ```
  === RISULTATI ===
    Bianchi Luca    2 voti   13.3%
    Neri Giulia     5 voti   33.3%
    Russo Marco     4 voti   26.7%
    Gallo Sara      4 voti   26.7%
  ```

### Test 3 – Pareggio per il secondo posto

- **Cosa si verifica**: due candidati a pari merito per il secondo posto portano al ballottaggio.
- **Input**: dati del sorgente.
- **Valori intermedi attesi**: `primo` = 1 (Neri Giulia), `secondo` = 2
  (Russo Marco, il primo con 4 voti), `pari_merito` = 2.
- **Output atteso**:
  ```
  Eletto: Neri Giulia
  Secondo posto con 4 voti: Russo Marco, Gallo Sara
  Pareggio: serve un ballottaggio per il secondo rappresentante.
  ```

### Test 4 – Secondo eletto senza pareggio

- **Cosa si verifica**: con un secondo classificato unico il programma lo
  elegge direttamente.
- **Procedura**: nel sorgente sostituire la ventesima scheda `"Neri Giula"`
  con `"Russo Marco"`, ricompilare ed eseguire.
- **Input**: schede modificate (Russo Marco sale a 5 voti).
- **Valori intermedi attesi**: `nulle` = 2, `valide` = 16, `voti` = {2, 5, 5, 4};
  `primo` = 1 (Neri Giulia, indice minore a parità), `secondo` = 2, `pari_merito` = 1.
- **Output atteso** (righe finali):
  ```
  Schede: 20  valide: 16  bianche: 2  nulle: 2
  ...
  Eletto: Neri Giulia
  Secondo posto con 5 voti: Russo Marco
  Eletto: Russo Marco
  ```
