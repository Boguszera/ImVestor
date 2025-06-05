# ImVestor

## Opis projektu
ImVestor to interaktywna aplikacja desktopowa stworzona w C++ z wykorzystaniem biblioteki SFML 3.0,
która symuluje rynek akcji. Użytkownik może kupować i sprzedawać akcje różnych firm,
śledzić zmiany cen w czasie rzeczywistym za pomocą wizualnego wykresu,
a także generować szczegółowy raport ze swoich transakcji.

## Funkcjonalności:
- **Symulacja rynku akcji** - dynamicznie zmieniające się ceny akcji
- **System transakcji** - możliwość kupna i sprzedaży akcji
- **Portfel inwestycyjny** - śledzenie posiadanych aktywów
- **Interaktywne GUI** - przyjazny interfejs użytkownika
- **Wizualizacja danych** - wykresy cen akcji w czasie rzeczywistym
- **Generowanie raportu** - raport .csv zawierający historię transakcji oraz zysk/stratę
-----------------------------------------------------------
## Wymagania systemowe
- Kompilator C++ obsługujący standard C++20 (np. GCC 10+, Clang 12+, MSVC 2019+)
- CMake w wersji 3.20 lub nowszej
- SFML 3.0.0 (UWAGA: na systemach Linux może być konieczne doinstalowane zależności )
- System operacyjny: Windows / Linux / macOS

**UWAGA:** Na systemach Linux może być konieczne doinstalowanie dodatkowych zależności, aby poprawnie uruchomić lub skompilować projekt. Na przykład:
```bash
sudo apt-get update # SFML 3.0.0 jest stosunkowo nową technologią (może jej nie być w starych cache'ach)
sudo apt-get install libx11-dev libxrandr-dev libxi-dev libxext-dev libxcursor-dev libsfml-dev
```

-----------------------------------------------------------
## Struktura projektu
```
ImVestor/
├── src/                    # Katalog ze wszystkimi plikami źródłowymi (.h i .cpp)
│   ├── Company.h           # Klasa reprezentująca firmę na giełdzie, zarządzająca ceną akcji, trendami i historią cen
│   ├── Company.cpp
│   ├── Portfolio.h         # Zarządza portfelem użytkownika — przechowuje pozycje akcji, umożliwia dodawanie i usuwanie
│   ├── Portfolio.cpp
│   ├── ReportGenerator.h   # Generuje raport
│   ├── ReportGenerator.cpp 
│   ├── SystemMessage.h     # Zarządza komunikatami w aplikacji
│   ├── SystemMessage.cpp 
│   ├── StockHolding.h      # Reprezentuje pojedynczą pozycję w portfelu użytkownika (np. 100 akcji danej firmy)
│   ├── StockHolding.cpp
│   ├── TransactionManager.h # Obsługuje logikę kupna i sprzedaży akcji, aktualizując portfel i saldo użytkownika
│   ├── TransactionManager.cpp
│   ├── User.h              # Przechowuje dane użytkownika: nazwę, saldo oraz portfel inwestycyjny
│   ├── User.cpp
│   └── main.cpp            # Punkt startowy aplikacji
│
├── gui/                    # Interfejs użytkownika
│   ├── Button.h            # Deklaracja klasy przycisku GUI
│   └── Button.cpp          # Implementacja klasy przycisku GUI
│
├── assets/                 # Zasoby (czcionki, obrazy, ikony itp.)
│   └── LiberationSans-Regular.ttf  # Czcionka wykorzystywana w aplikacji
│
├── README.md               # Dokumentacja projektu i instrukcje użytkowania
├── .gitignore              # Pliki i foldery ignorowane przez Git
```

-----------------------------------------------------------
## Budowanie projektu
```bash
 1. Sklonuj repozytorium:
   git clone https://github.com/Boguszera/ImVestor.git

 2. Przejdź do folderu projektu:
   cd ImVestor
 
 3. Utwórz katalog build i przejdź do niego:
   mkdir build && cd build

 4. Skonfiguruj projekt za pomocą CMake:
   cmake ..

 5. Zbuduj projekt:
   cmake --build .

 6. Uruchom aplikację:
   ./ImVestor  (Linux/macOS)
   ImVestor.exe (Windows)

```

-----------------------------------------------------------
## Użycie
- Po uruchomieniu aplikacji wyświetlana jest lista dostępnych spółek z aktualnymi cenami akcji.

- Użyj przycisków "Buy" i "Sell" do dokonywania transakcji.

- Kliknij na nazwę spółki, aby wyświetlić wykres jej cen.

- Śledź swój portfel i saldo w prawym panelu.

- Wykorzystaj przycisk "Report", aby wygenerować raport.
-----------------------------------------------------------

## Mechanizm zmiany cen akcji
Ceny akcji w aplikacji są generowane na podstawie połączenia trendu (wzrostowy/spadkowy/liniowy) oraz losowych fluktuacji, co imituje realne zachowanie rynku.

- **Inicjalizacja trendu:** Każda spółka otrzymuje losowy bias trendu z zakresu od [-2.0, 2.0], który wpływa na ogólny kierunek zmian cen.
- **Aktualizacja ceny:** Cena zmienia się na podstawie trendu oraz losowego szumu (rozkład normalny - Gaussowski), co sprawia, że zmiany nie są całkowicie przewidywalne.
- **Minimalna cena:** Cena akcji nigdy nie spada poniżej 1.0 - uniknamy w ten sposób nieprawidłowych wartości.
- **Zmiana trendu:** Co losowy okres czasu (5–30 sekund) trend jest lekko modyfikowany przez dodanie niewielkiego dryfu, który jest ograniczony zakresem [-3.0, 3.0], co symuluje zmieniające się nastroje inwestorów i reakcje na wydarzenia.

-----------------------------------------------------------

## Licencja
Projekt korzysta z biblioteki SFML, która jest dostępna na licencji zlib/png (https://www.sfml-dev.org/license.php).

Font LiberationSans-Regular jest używany na licencji SIL Open Font License (https://scripts.sil.org/OFL).

Kod tego projektu jest udostępniany na licencji MIT — zobacz plik LICENSE.
-----------------------------------------------------------