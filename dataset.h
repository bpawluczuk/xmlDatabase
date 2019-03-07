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
 * This class represents data set of database,
 * This class defines data source who is needed for cooperation with table view model
 */
class DataSet {
public:

    /**
     * Set record list
     * @param records
     */
    void setRecordList(list<Record *> records);

    /**
     * Get row count
     * @return
     */
    int getRowCount();

    /**
     * Get column count
     * @return
     */
    int getColumnCount();

    /**
     * Get column name by index of
     * @param indexColumn
     * @return
     */
    const char *getColumnName(int indexColumn);

    /**
     * Get cell value by index row and index column
     * @param indexRow
     * @param indexColumn
     * @return
     */
    const char *getCellValue(int indexRow, int indexColumn);

private:

    list<Record *> records;
    vector<const char *> columnNames;
    vector<vector<const char *>> rows;
    int columnCount;
    int rowsCount;
};