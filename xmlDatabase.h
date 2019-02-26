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

/**
 * class XmlDatabase
 */
class XmlDatabase {
public:

    /**
     *
     * @param name
     * @return
     */
    int connect(const char *name);

    /**
     *
     * @param name
     * @return
     */
    int create(const char *name);

    /**
     *
     * @return
     */
    list<Record *> select();

    /**
     *
     * @param where
     * @return
     */
    list<Record *> select(Record *where);

    /**
     *
     * @param record
     * @return
     */
    int insert(Record *record);

    /**
     *
     * @param id
     */
    void remove(const char *id);

    /**
     *
     * @param record
     */
    void update(Record *record);

    /**
     *
     * @param name
     * @return
     */
    bool insertColumn(const char *name);

    /**
     *
     * @param name
     * @return
     */
    bool removeColumn(const char *name);

    /**
     *
     * @return
     */
    vector<const char *> getSchema();

    /**
     *
     * @return
     */
    int count();

private:

    /**
     *
     */
    const char *dbName;

    /**
     *
     */
    XMLDocument xmlDocument;

    /**
     *
     * @param name
     * @return
     */
    bool columnExist(const char *name);

    /**
     *
     * @param id
     * @return
     */
    Record *findRecordById(const char *id);

    /**
     *
     * @return
     */
    XMLNode *xmlGetRootNode();

    /**
     *
     * @param id
     * @return
     */
    XMLNode *xmlFindRecordById(const char *id);
};