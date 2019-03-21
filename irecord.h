//
// Created by Borys Pawluczuk on 21/03/2019.
//

#include <vector>

#ifndef XMLDATABASE_IRECORD_H
#define XMLDATABASE_IRECORD_H

/**
 * Record template interface
 */
template<typename TColumn>
class IRecord {

    /**
     * Add new column to record
     * @param column
     */
    void addColumn(TColumn *column);

    /**
    * Get all columns from record
    * @return
    */
    std::vector<TColumn *> getColumns();
};

#endif //XMLDATABASE_IRECORD_H
