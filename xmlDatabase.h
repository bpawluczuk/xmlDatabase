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
 * This class represents database,
 * This class defines methods who are needed for manage of database, creates and fill simple ORM objects
 */
class XmlDatabase {
public:

    /**
     * Connect to database file *.xml
     * @param name
     * @return
     */
    int connect(const char *name);

    /**
     * Create database file *.xml
     * @param name
     * @return
     */
    int create(const char *name);

    /**
     * Return all records from database who is currently set
     * @return
     */
    list<Record *> select();

    /**
     * Return all records who meet the condition where
     * @param where
     * @return
     */
    list<Record *> select(Record *where);

    /**
     * Insert record to database
     * @param record
     * @return
     */
    int insert(Record *record);

    /**
     * Remove record from database
     * @param id
     */
    void remove(const char *id);

    /**
     * Update record to database
     * @param record
     */
    void update(Record *record);

    /**
     * Alter database schema and add new column
     * @param name
     * @return
     */
    bool insertColumn(const char *name);

    /**
     * Alter database and remove column
     * @param name
     * @return
     */
    bool removeColumn(const char *name);

    /**
     * Get database schema
     * @return
     */
    vector<const char *> getSchema();

    /**
     * Get column count
     * @return
     */
    int columnCount();

    /**
     * Get specify database path
     * @param name
     * @return
     */
    const char *getDatabasePath(const char *name);

    /**
     * Get data set
     * @return
     */
    DataSet getDataSet();

private:

    const char *dbName;
    const char *dbPath;
    XMLDocument xmlDocument;
    DataSet dataSet;
    void saveFile(const char *name);
    bool createDatabaseDirectory();
    bool columnExist(const char *name);
    Record *findRecordById(const char *id);
    XMLNode *xmlGetRootNode();
    XMLNode *xmlFindRecordById(const char *id);
};