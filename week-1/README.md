# CPLUS Week 1

## 1.1 Tools installeren

Binnen dit vak maak ik gebruik van `gcc` op Ubuntu

## 1.2 Bouwen

### 1.2.1 Preprocessen

Zie [hello.i](hello.i).

_Wat is er gebeurd met het bestand? Verklaar wat de preprocessor heeft gedaan._

De preprocessor heeft de `#include` directives vervangen door de inhoud van de gerefereerde bestanden.

### 1.2.2 Compileren

Zie [hello.o](hello.o).

### 1.2.3 Linken

Zie [hello](hello).

## 2.1 Linke(r) boel

1. Gebruik de woorden “compiler” en “linker” om uit te leggen hoe je een werkend programmam maakt van file1.cpp en file2.cpp.
   - Doordat in [file1.cpp](file1.cpp) de implementatie van `hi()` belooft wordt kan de compiler deze files zonder problemen omzetten in object files. Nadat dit gebeurt is voegt de linker deze twee bestanden samen waarbij de linker ervoor zorgt dat de call naar `hi()` in [file1.cpp](file1.cpp) naar [file2.cpp](file2.cpp) verwijst.
2. Verwacht je een fout tijdens het compileren of linken wanneer we de declaratie op regel 4 van file1.cpp verwijderen? Leg uit.
   - Wanneer de declaratie van `hi()` uit [file1.cpp](file1.cpp) verwijderd wordt geeft de compiler een error. [file1.cpp](file1.ccp) roept namelijk een functie aan die helemaal niet bestaat omdat de inhoud van [file2.cpp](file2.cpp) nog helemaal niet bekend is.
3. Wat gebeurt er als we de definitie van hi uit file2.cpp verwijderen? Krijgen we dan een compilatie- of een linkfout?
   - Wanneer de definitie van `hi()` uit [file2.cpp](file2.cpp) verwijderd wordt heeft de compiler hier geen last van, de compiler kijkt namelijk alleen naar de _beloftes_ van het bestand. De linker zal hier echter wel over klagen, er zijn namelijk beloftes niet waar gemaakt waardoor de linker het programma niet kan linken tot een uitvoerbaar bestand.
4. Plaats de declaratie van hi in een header file. Voeg een regel toe aan file1.cpp om deze header te gebruiken.
   - Zie [file1-2.1.4.cpp](file1-2.1.4.cpp) en [header.h](header.h)

## 2.2 Volgorde

[2.2.cpp](2.2.cpp)

1. Compileer [2.2.cpp](2.2.cpp).
2. Krijg je foutmeldingen? Zo ja, welke?

   - Ja, ik krijg de volgende foutmelding:

   ```console
   2.2.cpp: In function ‘int main()’:
   2.2.cpp:5:5: error: ‘hi’ was not declared in this scope
   5 |     hi();
     |     ^~
   ```

3. Wat betekenen deze foutmeldingen?
   - Deze foutmeldingen betekenen dat op het moment dat de compiler bij regel 5 aankomt er nog geen definitie of promise voor de functie `hi()` heeft gekregen, en deze functie in feite dus niet bestaat.
4. Pas het bestand aan zodat het wel te compileren is.
   - Zie [2.2-fix.cpp](2.2-fix.cpp) en [2.2-fix.o](2.2-fix.o)

## 2.3 Declarations to the rescue

[2.3.cpp](2.3.cpp)

1. Welke foutmelding(en) krijg je als je deze code wilt compileren?

   - Ik krijg de volgende foutmelding:

   ```console
   2.3.cpp: In function ‘void say_odd(int)’:
   2.3.cpp:9:9: error: ‘say_even’ was not declared in this scope
   9 |         say_even(n - 1);
     |         ^~~~~~~~
   ```

2. Wat betekent/betekenen deze?

   - Deze foutmelding houdt in dat op het moment dat `say_odd()` de `say_even()` functie probeert aan te roepen de compiler nog geen definitie of promise voor de `say_even()` functie heeft gehad en deze functie dus niet bestaat.

3. Leg uit waarom in tegenstelling tot het vorige voorbeeld we dit probleem niet kunnen oplossen door de functies `say_odd` en `say_even` om te draaien.

   - Omdat de functies elkaar aanroepen is er altijd een functie die later gedefinieerd wordt door de ander, en deze dus nog niet bestaat op het moment dat de compiler deze tegenkomt.

4. Zorg dat de code wel compileert door op de juiste plaats de functie `say_even` te _declareren_.
   - Zie [2.3-fix.cpp](2.3-fix.cpp) en [2.3-fix.o](2.3-fix.o)

## 3 Procesgeheugen: stack vs heap

1. Door het type van het array lijst steeds te veranderen en het programma opnieuw te starten, kun je achterhalen hoeveel ruimte verschillende gegevenstypen nodig hebben. Doe dit voor de types `char`, `wchar_t`, `int`, `long`, `long long`, `float`, `double` en `Aap`. Zet je meetresultaten in een tabel en verbind daar conclusies aan.

   - Na het runnen van het bestand met GDB en het uitvoeren van `info proc mappings` krijg ik de volgende resultaten:

   | Type        | Heapgrootte (bytes hex) | Heapgrootte (bytes dec) |
   | ----------- | ----------------------- | ----------------------- |
   | `char`      | 0x9867241000            | 654565445632            |
   | `wchar_t`   | 0x2619b970000           | 2618245447680           |
   | `int`       | 0x2619b970000           | 2618245447680           |
   | `long`      | 0x4c336dae000           | 5236485447680           |
   | `long long` | 0x4c336dae000           | 5236485447680           |
   | `float`     | 0x2619b970000           | 2618245447680           |
   | `double`    | 0x4c336dae000           | 5236485447680           |
   | `Aap`       | 0xe49a3ea6000           | 15709445447680          |

   - Hieruit kan ik concluderen dat het `char` type de minste ruimte in beslag neemt, en het `Aap` type de meeste ruimte in beslag neemt.

2. Leid uit je meetgegevens ook af hoe groot de heap ongeveer is.

   - Door het gebruik van `info proc mappings` weet ik precies hoe groot de heap is, of deze resources beschikbaar zijn op mijn systeem is een ander verhaal. De gemiddelde heap is 4991025447424 bytes groot. Oftewel ~5TB.

3. Verwijder nu de initialisatie van lijst en draai het programma weer. Verklaar de verschilen.

   - Na het runnen van het bestand waarbij de initialisatie van `lijst` verwijderd is met GDB en het uitvoeren van `info proc mappings` krijg ik de volgende resultaten:

   | Type        | Heapgrootte (bytes hex) | Heapgrootte (bytes dec) |
   | ----------- | ----------------------- | ----------------------- |
   | `char`      | 0x420000                | 4325376                 |
   | `wchar_t`   | 0x420000                | 4325376                 |
   | `int`       | 0x420000                | 4325376                 |
   | `long`      | 0x420000                | 4325376                 |
   | `long long` | 0x420000                | 4325376                 |
   | `float`     | 0x420000                | 4325376                 |
   | `double`    | 0x420000                | 4325376                 |
   | `Aap`       | 0x420000                | 4325376                 |

   - Doordat de initialisatie wegvalt hoeft er geen geheugen voor de lijst variable gereserveerd te worden. Hierdoor wordt de heap kleiner. Wel kan onder runtime hierdoor de heap groter worden.

4. Haal de commentaartekens vóór `int a,b,c,d,e,f,g,h,i,j;` weg (en laat de lijst static). Verklaar de verschillen.

   - Na het initialiseren van de array gaat de gemiddelde heapgrootte naar `0x630000`, dit houdt in dat er extra geheugen geregistreerd is om de array `int a,b,c,d,e,f,g,h,i,j;` op te slaan in geheugen.

5. Verplaats de regel `int a,b,c,d,e,f,g,h,i,j;` tot in de constructor. Verklaar weer de verschillen.

   - Na het verplaatsen van de regel `int a,b,c,d,e,f,g,h,i,j;` tot in de constructor gaat de heap size terug naar `0x420000`. Wat betekend dat er nu geen geheugen is gereserveerd voor de variabelen.

6. Kun je de grootte van de stack nu bepalen? Leg uit.

   - Ja, zoals hiervoor heb ik de grootte van de stack bepaald met de hulp van `info proc mappings`. Hierdoor heb ik een accurate heap size.
