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
//        db.create(dbName);
        return 0;
    }

    Record *record = new Record();
//    list<Record *> lista = db.select(record);
    list<Record *> lista = db.select();

    DataSet dataSet = db.getDataSet();
    cout << dataSet.getRowCount() << endl;
    cout << dataSet.getColumnCount() << endl;
    cout << dataSet.getColumnName(3) << endl;
    cout << dataSet.getCellValue(3,2) << endl;




    return 0;
}