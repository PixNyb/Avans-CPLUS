# CPLUS Week 6

## 1. Map, filter, reduce

1. Ga in de C++ Standard Library3 op zoek naar algorithms die zich ongeveer gedragen als `map`, `filter`, en `reduce`.
   Je zult merken dat ze anders heten (voor map wel logisch, anders botst het met `std::map`). Je zult ook merken dat ze niet exact de vorm hebben zoals ik hierboven beschreef, waardoor je ze niet kunt nesten.
   En dat is jammer. Zo jammer zelfs, dat wij dat nu zelf gaan oplossen. Maar dat komt zo.
   De vraag is hier dus: welke algorithms uit de C++ Standard Library komen overeen met `map`, `filter` en `reduce`?
   - `map`: `std::transform`
   - `filter`: `std::copy_if`
   - `reduce`: `std::accumulate`
2. Maak nu, in een eigen namespace, dit beroemde drietal. De versie die we gaan maken gedraagt zich precies zoals hierboven beschreven. We gaan steeds uit van `std::vector` om lijsten te representeren.
   - Zie [1/mrf.hpp](1/mrf.hpp) voor de implementatie.
3. We hebben nu dus functies gemaakt die we kunnen nesten, omdat ze allemaal een `std::vector` als argument èn returnwaarde hebben. Welk nadeel brengt dit met zich mee? Je ziet nu het compromis dat we sluiten: de versies uit de Standard Library zijn niet te nesten, maar hebben dit nadeel niet.
   - Het nadeel is dat we nu een `std::vector` moeten maken voor elke tussenstap. Dit kost extra geheugen en tijd.

## 2. Output- en inputiterators

1. Pas bovenstaande code aan zodat deze alleen de even getallen print.

   - Zie [2/start.cpp line 10](2/start.cpp#L10) voor de implementatie:

   ```cpp
   std::copy_if(std::istream_iterator<int>{f}, std::istream_iterator<int>{},
           std::ostream_iterator<int>{std::cout, "\n"},
           [](int i) { return i % 2 == 0; });
   ```

2. Laat de code nu het dubbele van elk getal uitvoeren.

   - Zie [2/start.cpp line 14](2/start.cpp#L17) voor de implementatie:

   ```cpp
   std::transform(std::istream_iterator<int>{f}, std::istream_iterator<int>{},
           std::ostream_iterator<int>{std::cout, "\n"},
           [](int i) { return i * 2; });
   ```

3. Wat voor een foutmelding krijg je als je de getallen in `input.txt` als volgt wilt sorteren: `std::sort(i_begin, i_end);`? Weet je waarom je deze foutmelding krijgt?

   - De foutmelding is:

   ```console
   /usr/include/c++/11/bits/stl_algo.h: In instantiation of ‘void std::__sort(_RandomAccessIterator, _RandomAccessIterator, _Compare) [with _RandomAccessIterator = std::istream_iterator<int>; _Compare = __gnu_cxx::__ops::_Iter_less_iter]’:
       /usr/include/c++/11/bits/stl_algo.h:4842:18:   required from ‘void std::sort(_RAIter, _RAIter) [with _RAIter = std::istream_iterator<int>]’
       start.cpp:28:12:   required from here
       /usr/include/c++/11/bits/stl_algo.h:1955:50: error: no match for ‘operator-’ (operand types are ‘std::istream_iterator<int>’ and ‘std::istream_iterator<int>’)
       1955 |                                 std::__lg(__last - __first) * 2,
            |                                           ~~~~~~~^~~~~~~~~
   ```

   - De foutmelding zegt dat er geen `operator-` is voor `std::istream_iterator<int>`. Dit komt omdat een `std::istream_iterator<int>` geen random access iterator is. Dit is nodig voor `std::sort`.

4. Gebruik een `back_insert_iterator` om de getallen uit `input.txt` te kopiëren naar een `vector<int>`.

   - Zie [2/start.cpp line 31](2/start.cpp#L31) voor de implementatie:

   ```cpp
   std::vector<int> v{};
   std::copy(std::istream_iterator<int>{f}, std::istream_iterator<int>{},
           std::back_inserter(v));
   ```

5. Sorteer de vector van opdracht 2.4 en schrijf de getallen in gesorteerde volgorde naar de console.

   - Zie [2/start.cpp line 37](2/start.cpp#L37) voor de implementatie:

   ```cpp
   std::sort(v.begin(), v.end());
   std::copy(v.begin(), v.end(), std::ostream_iterator<int>{std::cout, "\n"});
   ```

6. Bereken het product (vermenigvuldiging) van alle getallen in `input.txt`. Schrijf het resultaat met behulp van `o_begin` naar de console.

   - Zie [2/start.cpp line 48](2/start.cpp#L48) voor de implementatie:

   ```cpp
   *o_begin++ =
       std::accumulate(i_begin, i_end, 1, [](int a, int b) { return a * b; });
   ```

## 3. Lambda’s en functietemplates

1. Schrijf een functie `for_all` die twee iterators, `begin` en `end`, plus een lambda accepteert. Deze functie roept de lambda aan voor elk element tussen `begin` en `end`.

   - Zie [3/program.cpp line 25](3/program.cpp#L25) voor de implementatie:

   ```cpp
   template <typename Iterator, typename Lambda>
   void for_all(Iterator begin, Iterator end, Lambda lambda) {
       for (auto it = begin; it != end; ++it) {
           lambda(*it);
       }
   }
   ```

2. Implementeer onderstaande klasse. Vul de definitie waarnodig aan met extra variabelen:

   ```cpp
   class observable {
   public:
       observable(int value) : value_{value} {};
       void value(int value);
       template <typename Observer> void add_observer(Observer o);
   private:
       int value_;
   };
   ```

   - Zie [3/program.cpp line 7](3/program.cpp#L7) voor de implementatie:

   ```cpp
    class observable {
    public:
        observable(int value) : value_{value} {};
        void value(int value) {
            value_ = value;
            for (auto o : observers_) {
                o(value_);
            }
        }
        template <typename Observer> void add_observer(Observer o) {
            observers_.push_back(o);
        }

    private:
        int value_;
        std::vector<std::function<void(int)>> observers_;
    };
   ```

## 4. The Matrix

1. Implementeer in C++ je eigen templateklasse matrix die n × m matrices representeert. Test elke functie en operator die je implementeert met een unit tests. Je kunt hiervoor `catch.hpp` gebruiken. Je krijgt van ons een paar unit tests cadeau in `matrix.cpp`. (Let op: Dit bestand gaat ervanuit dat je je matrix in `matrix.hpp` definieert.) Zorg ervoor dat je template de volledige functionaliteit heeft:

   1. Een constructor die als argumenten het aantal rijen en kolommen accepteert.
   2. Een _default_ constructor
   3. Denk goed na of je de volgende zaken nodig hebt, of nog beter hoe je je klasse zo kan ontwerpen dat je geen van deze nodig hebt:
      1. een destructor
      2. copy operations (copy constructor en assignment)
      3. move operations (move constructor en assignment)
   4. Een member functie ix die een rij- en kolomindex accepteert en een refe- rentie naar de waarde op die plek terug geeft. Zorg ervoor dat je hem zo kan gebruiken:

      ```cpp
      linal::matrix<int> m { 3, 2 };
      m.ix(0,0) = 1;
      ```

   5. Een operator `+` die twee matrices bij elkaar optelt. En een operator `+=` die een matrix bij de huidige matrix optelt.
   6. Een operator `-` die twee matrices van elkaar aftrekt. En een operator `-=` die een matrix van de huidige matrix aftrekt.
   7. Een operator `*` die een matrix met een getal kan vermenigvuldigen en een definitie van `*` die een getal met een matrix kan vermenigvuldigen. Denk goed na waar je die laatste moet implementeren. Implementeer daarnaast ook de operator `*=`.
   8. Gebruik `std::mismatch` om de operatoren `==` en `!=` te definiëren. Deze operatoren controleren de gelijkheid van twee matrices.
   9. Overload de function call operator zodat deze een rij- en kolomindex accepteert en een referentie naar de waarde op die plek terug geeft.
