//
// Created by Borys Pawluczuk on 24/02/2019.
//

#ifndef XMLDATABASE_COLUMN_H
#define XMLDATABASE_COLUMN_H

#endif //XMLDATABASE_COLUMN_H

#include <iostream>
#include "icolumn.h"

using namespace std;

/**
 * class Column
 * This class represents cell in record of database,
 * This class defines object who contain following properies:
 * name column,
 * value column,
 * number column
 */
class Column : IColumn<const char *, const char *>{
public:

    /**
     * Constructor
     * @param key
     * @param value
     */
    Column(const char *key, const char *value, int index = 0);

    /**
     * Set column name
     * @param key
     */
    void setKey(const char *key);

    /**
     * Set cell value
     * @param value
     */
    void setValue(const char *value);

    /**
     * Get column name
     * @return
     */
    const char *getKey() const;

    /**
     * Get cell value
     * @return
     */
    const char *getValue() const;

    /**
     * Set index of column
     * @param index
     */
    void setIndex(int index);

    /**
     * Get index of column
     * @return
     */
    int getIndex() const;

private:

    const char *key;
    const char *value;
    int index;
};