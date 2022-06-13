# E-Goat
Jest to usługa peer-to-peer wymiany plików między użytkownikami oparta na protokole TCP. Składa się z dwóch aplikacji: serwera i klienta.
### Funkcjonalności 
---
- **Serwer**
	- Nasłuchuje, czy ktoś się podłączył
	- Przechowuje listę numerów IP podłączonych użytkowników 
	- Przechowuje nazwy plików oraz sumy kontrolne sha512 każdego użytkownika
- **Klient**
	- Po podłączeniu się do serwera pozwala na załadowanie folderu do przesłania na serwer
	- Wylicza sumy kontrolne sha512 każdego pliku w folderze
	- Wysyła na serwer paczkę z zawartymi sumami kontrolnymi i nazwami plików
### Spis klas i funkcji
---
Funkcje `int  main(int  argc,  char  *argv[])` tworzą obiekt klienta lub serwera.
- **Serwer**
	- `class EGoatTcpServer`
		-  `explicit  EGoatTcpServer(QObject  *parent  =  nullptr)`
		Konstruktor Serwera, zawiera informacje o porcie nasłuchu, definiuje strumienie danych oraz tekstowe (do przesyłu paczek oraz wyświetlania informacji na `stdout`.
		- `void coutWrite(QString  message)`oraz void`coutWrite(QByteArray  bytes)`
		Metody służące do wyświetlania wiadomości lub bajtów na ekranie (`stout`).
		- `void  socketWriteString(const  char*  s,  QTcpSocket  *socket1)`
		Wysłanie wiadomości do klienta.
	- `class User`
		- `User(QHostAddress  userIP)` oraz `User(QHostAddress  userIP,  QByteArray  checksums,  QTcpSocket  *socket)`
				Konstruują obiekt `User` na podstawie numeru IP lub numeru IP oraz dostarczonej paczki nazw plików i sum kontrolnych.
		- `QHostAddress  getUserIP()`
			Zwraca numer IP użytkownika.
		- `QMap<QString,  QByteArray>  getfileNamesAndChecksums()`
			Zwraca obiekt klasy `QMap` będący mapą nazw przesłanych plików oraz odpowiadających danym plikom sum kontrolnych.
		- `void  setChecksums(QByteArray  checksums,  QTcpSocket  *socket)`
			Wypakowuje z dostarczonej paczki typu `QByteArray`od klienta obiekt QMap.
- **Klient**
	- `explicit  EGoatTcpClient(QObject  *parent  =  nullptr)`
		Konstruktor, definiuje strumienie danych oraz tekstowe (do przesyłu paczek, wprowadzania oraz wyświetlania informacji na `stin` i `stdout`.
	- `void  doConnect()`
		Nawiązuje i obsługuje całe połączenie z serwerem.
	- `void  socketWriteString(QString  message,  QString  s,  QTcpSocket  *socket1)`oraz  ` void  socketWriteString(const  char  *s,  QTcpSocket  *socket1)`
		Wysyła wartość na serwer. Jeśli metoda zostanie wywołana z `QString message`, najpierw wyświetla informację o wartości, jaką chce wysłać, a następnie wysyła wprowadzoną wartość  przez użytkownika.
	-  `void coutWrite(QString  message)`oraz void`coutWrite(QByteArray  bytes)`
		Metody służące do wyświetlania wiadomości lub bajtów na ekranie (`stout`).
	- `QByteArray  fileChecksum(const  QString  &fileName)`
		Oblicza sumę kontrolną sha512 wprowadzonego pliku o nazwie `fileName`.
	- `QMap<QString,  QByteArray>  setFilesChecksums(QDir  dir)`
		Tworzy obiekt `QMap` z nazwami plików i ich sumami kontolnymi, które zaciąga z podanego katalogu `dir`.


