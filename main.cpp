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

    XmlDatabase db;
    const char *dbName = "baza.xml";
    if (!db.connect(dbName)) {
        db.create(dbName);
        return 0;
    }

//    Record *r = db.findRecordById("1");
//    if (r) {
//        r->updateColumnValue(new Column("Type", "GITARA"));
//        db.update(r);
//    }

//    db.addColumn("Type");
//    db.addColumn("Name");
    db.addColumn("Desc");
//
//    Record *record = new Record();
//    record->addColumn(new Column("Type", "GITARA"));
//    record->addColumn(new Column("Name", "Kult"));
//    record->addColumn(new Column("Desc", "bla bla"));
//    db.insert(record);

//db.removeColumn("Desc");
//    Record *record = new Record();
//    record->addColumn(new Column("Type", "ARA"));
////    record->addColumn(new Column("Name", "Ku"));
//    list<Record *> lista = db.select(record);

    return 0;
}