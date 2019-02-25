//
// Created by Borys Pawluczuk on 23/02/2019.
//

#ifndef XMLDATABASE_XMLDATABASE_H
#define XMLDATABASE_XMLDATABASE_H

#endif //XMLDATABASE_XMLDATABASE_H

#include <iostream>
#include <map>
#include <list>
#include "tinyxml2-master/tinyxml2.h"
#include "record.h"

using namespace std;
using namespace tinyxml2;

class XmlDatabase {
public:

    int connect(const char *name);

    int create(const char *name);

    list<Record *> select();

    list<Record *> select(Record *where);

    int insert(Record *record);

    void remove(const char *id);

    bool addColumn(const char *name);

    int count();

    vector<const char *> getSchema();

    Record *findRecordById(const char *id);

    void update(Record *record);

    bool columnExist(const char *name);

private:
    const char *dbName;
    XMLDocument xmlDocument;

    XMLNode *xmlGetRootNode();

    XMLNode *xmlFindRecordById(const char *id);
};