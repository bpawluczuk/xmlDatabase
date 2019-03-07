//
// Created by Borys Pawluczuk on 06/03/2019.
//

#ifndef XMLDATABASE_RECORD_H

#include "record.h"

#endif

#include <list>

#ifndef XMLDATABASE_DATASET_H
#define XMLDATABASE_DATASET_H

#endif //XMLDATABASE_DATASET_H

/**
 * class DataSet
 */
class DataSet {
public:

    /**
     *
     * @param records
     */
    void setRecordList(list<Record *> records);

    /**
     *
     * @return
     */
    int getRowCount();

    /**
     *
     * @return
     */
    int getColumnCount();

    /**
     *
     * @param indexColumn
     * @return
     */
    const char *getColumnName(int indexColumn);

    /**
     *
     * @param indexRow
     * @param indexColumn
     * @return
     */
    const char *getCellValue(int indexRow, int indexColumn);

private:

    /**
     *
     */
    list<Record *> records;

    /**
     *
     */
    vector<const char *> columnNames;

    /**
     *
     */
    vector<vector<const char *>> rows;

    /**
     *
     */
    int columnCount;

    /**
     *
     */
    int rowsCount;
};