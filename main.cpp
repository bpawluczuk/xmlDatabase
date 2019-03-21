#include <iostream>
#include <map>
#include <iterator>
#include <list>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>

#include "xmlDatabase.h"

using namespace std;

int main() {

    // Utworzenie i połączenie z bazą danych
    XmlDatabase db;
    const char *dbName = "baza.xml";
    if (!db.connect(dbName)) {
        db.create(dbName);
        return 0;
    }

    //Dodawanie kolumn do tabeli
    db.insertColumn("Type");
    db.insertColumn("Desc");
    db.insertColumn("Status");

    // Dodawanie nowego rekordu do bazy
    Record *record = new Record();
    record->addColumn(new Column("Type", "CD"));
    record->addColumn(new Column("Desc", "opis przedmiotu"));
    db.insert(record);

    // Pobieranie listy rekordów z bazy
    list<Record *> result = db.select();

    // Wyszukiwanie po zawartości kolumny
    Record *whereRecord = new Record();
    // Dodawanie kolumny po zawartości której chcemy szukać
    whereRecord->addColumn(new Column("Desc", "szukany opis przedmiotu"));

    /**
     * Odpowiednik w SQL
     *
     * SELECT col1, col2 FROM tabela
     * WHERE col1 LIKE '%szukana fraza%' and col1 LIKE '%szukana fraza%';
     */
    list<Record *> resultSearch = db.select(whereRecord);

    // Update zawartości rekordu
    Record *recordUpdate = new Record();
    recordUpdate->addColumn(new Column("ID", "1")); //ID rekordu który edytujemy
    recordUpdate->addColumn(new Column("Desc", "nowy opis przedmiotu"));
    db.update(recordUpdate);

    // Usuwanie rekordu
    db.remove("1");

    // Usuwanie kolumny
    db.removeColumn("Status");

    return 0;
}