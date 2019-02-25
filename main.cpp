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



    return 0;
}