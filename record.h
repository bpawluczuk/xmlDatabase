//
// Created by Borys Pawluczuk on 24/02/2019.
//

#ifndef XMLDATABASE_RECORD_H
#define XMLDATABASE_RECORD_H

#endif //XMLDATABASE_RECORD_H

#include <map>
#include <vector>
#include "column.h"

class Record {
public:

    /**
     *
     * @param column
     */
    void addColumn(Column *column);

    /**
     *
     * @return
     */
    vector<Column *> getColumns();

    /**
     *
     * @return
     */
    const char *getId();

    /**
     *
     * @param name
     * @return
     */
    const char *getColumnValue(const char *name);

    /**
     *
     * @param key
     * @param value
     */
    void updateColumnValue(const char *key, const char *value);

    /**
     *
     * @param updateColumn
     */
    void updateColumnValue(Column *updateColumn);

    /**
     *
     * @param updateColumns
     */
    void updateColumnValue(vector<Column *> updateColumns);

private:

    /**
     *
     */
    vector<Column *> ownColumns;
};