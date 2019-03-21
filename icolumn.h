//
// Created by Borys Pawluczuk on 21/03/2019.
//

#ifndef XMLDATABASE_ICOLUMN_H
#define XMLDATABASE_ICOLUMN_H

/**
 * Column template interface
 */
template<typename TKey, typename TValue>
class IColumn{
    void setKey(TKey key);
    void setValue(TValue value);
    TKey getKey() const;
    TValue getValue() const;
};

#endif //XMLDATABASE_ICOLUMN_H
