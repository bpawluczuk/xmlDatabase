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

#ifndef XMLDATABASE_RECORD_H
#include "record.h"
#endif

#include "dataset.h"

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
    int columnCount();

    /**
     *
     * @param name
     * @return
     */
    const char *getDatabasePath(const char *name);

    /**
     *
     * @return
     */
    DataSet getDataSet();

private:

    /**
     *
     */
    const char *dbName;

    /**
     *
     */
    const char *dbPath;

    /**
     *
     */
    XMLDocument xmlDocument;

    /**
     *
    */
    DataSet dataSet;

    /**
     *
     * @param name
     */
    void saveFile(const char *name);

    /**
     *
     * @param name
    */
    bool createDatabaseDirectory();

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