# CPLUS Week 2

## 1. Pointers begrijpen

1. Zet in commentaar achter elke toekenning wat je denkt dat de waarden zijn van de 4 variabelen na uitvoering van die toekenning.
    - Zie [1.cpp](1.cpp)

2. Controleer je antwoorden door te single-steppen met de debugger, en daarbij de waarden te inspecteren. Verklaar eventuele verschillen.
    - Er zijn geen verschillen.

## 2. We value your call

1. Typ of kopieer onderstaand programma naar een nieuw project in je ontwikkelomgeving. Welke waarde van a wordt door het programma afgedrukt? Verklaar dit resultaat.
    - Het programma drukt voor a de waarde `5` uit. Dit komt doordat de functie `cbv` niet de waarde van de pointer naar `a` wijzigt, maar een kopie van de waarde krijgt en die wijzigt. `a` verandert dus niet.

## 3. A good reference

1. Welke waarde van `a` wordt door dit programma afgedrukt?
    - Het programma print voor `a` de waarde `15` uit.

## 4. These are a few of my favourite things

1. Implementeer onderstaande varianten van de functie `show_favourites` die een object van het type `Favourites` accepteert en volgende uitvoer weergeeft:

    ```console
    Favourite letter: J
    Favourite prime: 11
    Favourite digit: 9
    ```

    De eerste variant accepteert een `Favourite` by value, de tweede by reference en de derde als pointer.

    ```cpp
    // pass by value
    void show_favourites_by_value(Favourites f)
    {
    }
    // pass by reference
    void show_favourites_by_reference(Favourites& f)
    {
    }
    // pass by pointer
    void show_favourites_by_pointer(Favourites* p)
    {
    }
    ```

2. Schrijf nu een functie `set_prime` die de prime-member van de struct verandert. Beargumenteer op welke wijze je de struct doorgeeft aan de functie.
    - Voor de `set_prime` functie is het het beste om de struct door te geven als referentie. Dit omdat de functie de waarde van de prime-member verandert en niet de waarde van de struct zelf. Zie [4.cpp](4.cpp) voor de implementatie.

## 5. It's a brand new day

1. Maak in onderstaand programma de main-functie af door een object van het type Day op de heap aan te maken en geheugen na gebruik weer vrij te geven.
    - Zie [5.cpp](5.cpp) voor de implementatie.

## 6. Don’t leak

1. Leg uit wat de programmeur van bovenstaande code is vergeten.
    - De programmeur is vergeten om de `delete` operator te gebruiken om het geheugen dat gebruikt is voor de `multiply` functie weer vrij te geven.

2. Voeg dit toe aan de code.
    - Zie [6.cpp](6.cpp) voor de implementatie.

3. Denk na over het gebruik van de functie multiply. Kunnen andere programmeurs zonder uitleg met dee functie aan de slag?
    - Nee, de functie `multiply` is niet duidelijk. Het is niet duidelijk of de functie een pointer of een referentie verwacht. Ook is het niet duidelijk of de functie de waarde van de variabelen verandert of niet. Daarnaast allocate de functie geheugen voor een nieuwe variabele, maar geeft het niet weer vrij. Hier moet de gebruiker van de functie rekening mee houden.

## 7. I forgot my name

1. Beschrijf wat je verwacht wanneer je deze code uitvoert.
    - Ik verwacht dat de code letter voor letter de naam `Jeroen` uitprint.

2. Compileer de code maar voer hem nog niet uit. Controleer of je compiler waarschuwingen geeft. Zo ja, noteer deze en probeer ze te verklaren.
    - Bij het compilen van de code krijg ik de volgende warning:

    ```console
    7.cpp: In function ‘char* my_name()’:
    7.cpp:5:10: warning: address of local variable ‘myname’ returned [-Wreturn-local-addr]
        5 |   return myname;
        |          ^~~~~~
    7.cpp:4:8: note: declared here
        4 |   char myname[6] = {'J', 'e', 'r', 'o', 'e', 'n'};
        |        ^~~~~~
    ```

    Deze warning geeft aan dat de functie `my_name` een pointer teruggeeft naar een lokale variabele. Dit is niet goed omdat de lokale variabele niet meer bestaat nadat de functie is uitgevoerd.

3. Voer de code nu daadwerkelijk uit. Gebeurt er wat je verwacht?
    - De code hangt op een `Segmentation fault` error. Dit komt doordat de functie `my_name` een pointer teruggeeft naar een lokale variabele. Deze lokale variabele bestaat niet meer nadat de functie is uitgevoerd. De pointer wijst dus naar een stuk geheugen dat niet meer bestaat.

4. Hoe zou jij een array van characters vanuit een functie naar een andere kunnen overbrengen? Dit betekent dat de letters van de naam Jeroen bruikbaar moeten zijn in main.
    - Om een array van characters vanuit een functie naar een andere te brengen kan je een pointer gebruiken. Zie [7.cpp](7.cpp) voor de implementatie.

## 8. C-strings

1. Maak de while-loop in onderstaande functie `int string_length(char* str)` af. Deze functie retourneert de lengte van een string (exclusief het NUL-character). **Je mag de conditie in de while-loop niet aan- passen.**
    - Zie [8.cpp](8.cpp) voor de implementatie.

2. Gebruik jouw implementatie van string_length in volgend voorbeeld en verklaar de uitvoer. Is deze zoals je verwacht? Waarom wel, waarom niet?
    - De uitvoer is zoals ik verwacht. Aangezien het NULL-character niet wordt meegeteld telt de functie `string_length` de lengte in beide gevallen als `5`.

3. Pas de functie `not_safe` aan zodat de uitvoer juist is, dus:

    ```console
    16
    16
    ```

    - Zie [8.cpp](8.cpp) voor de implementatie.

## 9. Buffer overflow

1. Schrijf een functie `void copy_string(char*from, char* to)` die de string from kopieert naar to en gebruik die in volgend voorbeeld.
    - Zie [9.cpp](9.cpp) voor de implementatie.

2. Wat gebeurt er wanneer het array to te klein is voor alle karakters van from?
    - Op de manier waarop de functie `copy_string` nu is geïmplementeerd zal de functie de karakters van `from` blijven kopiëren naar `to` totdat het NULL-character is bereikt. Dit kan dus leiden tot een buffer overflow.

3. **Optionele uitdaging** De header `<cstring>` bevat de functie `strcpy(char*dest, const char* src)` om C-strings te kopiëren. De ontwikkelaars van het besturingssysteem OpenBSD vonden deze functie niet veilig genoeg en ontwikkelden daarom volgend alternatief: `strlcpy(char* dst, const char* src, size_t dstsize);`. Hier bevat dstsize de grootte van het array dst. Waarom is deze functie veiliger?
    - Deze functie is veiliger omdat de functie een parameter heeft die de grootte van het array `dst` bevat. Hierdoor kan de functie controleren of er genoeg ruimte is in het array `dst` om de string te kopiëren. Als er niet genoeg ruimte is zal de functie de string niet kopiëren en een error teruggeven.

4. **Optionele uitdaging** Waarom is dstsize van het type `size_t` en niet `int`?
    - `size_t` is een unsigned integer type. Dit betekent dat het type alleen positieve waarden kan bevatten. Dit is handig omdat de grootte van een array niet negatief kan zijn.

## 10. Bring on the big uns

1. Maak een nieuw project aan in je favoriete IDE.
    - Zie [10](10) voor het project.

2. Download de file `big_uns.zip` uit de course
    - Zie [10](10) voor het project.

3. Importeer of kopieer de code uit de bestanden `read_int.h`, `read_int.cpp` en `big_uns.cpp` in je project.
    - Zie [10](10) voor het project.

4. Vervang de implementatie van de functie `write_big` in `big_uns.cpp`. Deze functie ontvangt een getal `a` en moet vervolgens dat getal in grote cijfers naar het scherm schrijven. De grote vcijfers staan in het globale array `bigdigits`.
    - Zie [10/big_uns.cpp](10/big_uns.cpp) voor de implementatie.

## 11. Constantly thinking about `const`

Bekijk onderstaande code en bepaal welke functies je als `const` kunt kwalificeren. Pas hun declaraties aan en schrijf bijpassende definities. Zorg ervoor dat de definitie compileert en test deze in een klein programma.

```cpp
class Student { 
    int _number;
    int _age; 
  public:
    Student(int number) : _number { number } {}; int getNumber();
    void setNumber(int newNumber);
    int getAge();
    void setAge();
    int ageDifference(const Student& other); int futureAge() { return getAge() + 1; }
};
```

Het is mogelijk om de functies `getNumber`, `getAge`, `ageDifference` en `futureAge` als `const` te kwalificeren. Zie [11.cpp](11.cpp) voor de implementatie.

## 12. Constantinople

1. Bepaal welke **parameters** als `const` gekwalificeerd kunnen worden.
    - De volgende parameters kunnen als `const` gekwalificeerd worden:
        - `name` in de functie `City` (constructor)
        - `city` in de functie `populationDifference`
        - `other` in de functie `populationDifference`
        - `newName` in de functie `setName`
2. Bepaal welke **member functions** als `const` gekwalificeerd kunnen worden.
    - De volgende member functions kunnen als `const` gekwalificeerd worden:
        - `getName`
        - `getPopulation`
3. Bepaal welke **resultaattypes** als `const` gemarkeerd kunnen worden.
    - De volgende resultaattypes kunnen als `const` gemarkeerd worden:
        - `getPopulation`

Zie [12.cpp](12.cpp) voor de implementatie.
