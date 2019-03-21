//
// Created by Borys Pawluczuk on 24/02/2019.
//

#ifndef XMLDATABASE_RECORD_H
#define XMLDATABASE_RECORD_H

#endif //XMLDATABASE_RECORD_H

#include <map>
#include <vector>
#include "irecord.h"
#include "column.h"

/**
 * class Record
 * This class represents record of database,
 * This class defines object who contain table cells in one row
 */
class Record : IRecord<Column>{
public:

    /**
     * Constructor
     * @param index
     */
    Record(int index = 0);

    /**
     * Add new column to record
     * @param column
     */
    void addColumn(Column *column);

    /**
     * Get all columns from record
     * @return
     */
    vector<Column *> getColumns();

    /**
     * Get identyfier of database record
     * @return
     */
    const char *getId();

    /**
     * Get column value by column name
     * @param name
     * @return
     */
    const char *getColumnValue(const char *name);

    /**
     * Set index of record
     * @param index
     */
    void setIndex(int index);

    /**
     * Get index of record
     * @return
     */
    int getIndex() const;

private:

    vector<Column *> columns;
    int index;
};