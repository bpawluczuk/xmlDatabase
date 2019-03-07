//
// Created by Borys Pawluczuk on 23/02/2019.
//
#include <iostream>
#include <map>
#include <sys/stat.h>
#include "xmlDatabase.h"
#include "tinyxml2-master/tinyxml2.h"
#include "tinyxml2-master/tinyxml2.cpp"

using namespace std;
using namespace tinyxml2;

XMLNode *XmlDatabase::xmlGetRootNode() {
    XMLNode *pRoot = XmlDatabase::xmlDocument.FirstChild();
    return pRoot;
}

const char *XmlDatabase::getDatabasePath(const char *name) {
    return (string("/Users/bpawluczuk/database/") + string(name)).c_str();
}

int XmlDatabase::connect(const char *name) {

    const char *path = XmlDatabase::getDatabasePath(name);

    XMLError result = XmlDatabase::xmlDocument.LoadFile(path);
    if (result != XML_SUCCESS) {
        cout << "Unable connect to database " << XmlDatabase::getDatabasePath(name) << endl;
        return false;
    }

    XmlDatabase::dbName = name;

    XMLNode *root = XmlDatabase::xmlGetRootNode();
    if (root == nullptr) {
        cout << "Wrong format database " << name << endl;
        return false;
    }

    cout << "Connect to database " << name << endl;
    return true;
}

int XmlDatabase::create(const char *name) {

    XMLNode *pRoot = XmlDatabase::xmlDocument.NewElement("Database");
    XmlDatabase::xmlDocument.InsertFirstChild(pRoot);

    XMLNode *pShema = XmlDatabase::xmlDocument.NewElement("Schema");
    pRoot->InsertFirstChild(pShema);

    XMLNode *pId = XmlDatabase::xmlDocument.NewElement("ID");
    pShema->InsertFirstChild(pId);

    XmlDatabase::createDatabaseDirectory();
    XmlDatabase::saveFile(name);

    return true;
}

bool XmlDatabase::createDatabaseDirectory() {

    if (mkdir("/Users/bpawluczuk/database", 0777) == -1) {
        cerr << "Error :  " << strerror(errno) << endl;
        return false;
    } else {
        cout << "Directory created";
        return true;
    }
}

void XmlDatabase::saveFile(const char *name) {

    XMLError error = XmlDatabase::xmlDocument.SaveFile(XmlDatabase::getDatabasePath(name));
    if (error) {
        cout << "Can't save file: " << XmlDatabase::getDatabasePath(name) << endl;
    }
}

int XmlDatabase::insert(Record *record) {

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();
    int count = XmlDatabase::columnCount() + 1;

    XMLElement *pNode = XmlDatabase::xmlDocument.NewElement("Record");
    pNode->SetAttribute("type", "record");
    pRoot->InsertEndChild(pNode);

    for (auto schema : XmlDatabase::getSchema()) {

        XMLElement *pElement = XmlDatabase::xmlDocument.NewElement(schema);

        if (strcmp(schema, "ID") == 0) {
            pElement->SetText(count); // Autoincrement
        }

        for (auto column : record->getColumns()) {
            if (strcmp(schema, column->getKey()) == 0 && column->getValue()) {
                pElement->SetText(column->getValue());
            }
        }

        pNode->InsertEndChild(pElement);
    }

    XmlDatabase::saveFile(XmlDatabase::dbName);

    return true;
}

int XmlDatabase::columnCount() {

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();

    int inc = 0;
    for (XMLElement *child = pRoot->FirstChildElement("Record"); child != 0; child = child->NextSiblingElement()) {
        inc += 1;
    }

    return inc;
}

bool XmlDatabase::columnExist(const char *name) {

    vector<const char *> schema = XmlDatabase::getSchema();

    for (auto column : schema) {
        if (strcmp(column, name) == 0) {
            return true;
        }
    }
    return false;
}

vector<const char *> XmlDatabase::getSchema() {

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();

    vector<const char *> result;

    for (XMLElement *node = pRoot->FirstChildElement("Schema"); node != 0; node = node->NextSiblingElement()) {
        for (XMLElement *child = node->FirstChildElement(); child != 0; child = child->NextSiblingElement()) {
            result.push_back(child->Name());
        }
        break;
    }

    return result;
}

bool XmlDatabase::removeColumn(const char *name) {

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();

    if (strcmp(name, "ID") == 0) {
        return false;
    }

    for (XMLElement *pSchema = pRoot->FirstChildElement("Schema");
         pSchema != 0; pSchema = pSchema->NextSiblingElement()) {
        XMLElement *child = pSchema->FirstChildElement(name);
        if (child) {
            pSchema->DeleteChild(child);
        }
    }

    XmlDatabase::saveFile(XmlDatabase::dbName);

    return true;
}

bool XmlDatabase::insertColumn(const char *name) {

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();

    if (XmlDatabase::columnExist(name)) {
        return false;
    }

    for (XMLElement *node = pRoot->FirstChildElement("Schema"); node != 0; node = node->NextSiblingElement()) {
        XMLElement *pElement = XmlDatabase::xmlDocument.NewElement(name);
        node->InsertEndChild(pElement);
    }

    XmlDatabase::saveFile(XmlDatabase::dbName);

    return true;
}

void XmlDatabase::remove(const char *id) {

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();
    XMLNode *node = XmlDatabase::xmlFindRecordById(id);

    if (node) {
        pRoot->DeleteChild(node);
        XmlDatabase::saveFile(XmlDatabase::dbName);
    }
}

XMLNode *XmlDatabase::xmlFindRecordById(const char *id) {

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();

    for (XMLElement *node = pRoot->FirstChildElement("Record"); node != 0; node = node->NextSiblingElement()) {
        XMLElement *child = node->FirstChildElement("ID");
        if (strcmp(child->GetText(), id) == 0) {
            return child->Parent();
        }
    }

    return nullptr;
}

Record *XmlDatabase::findRecordById(const char *id) {

    XMLNode *node = XmlDatabase::xmlFindRecordById(id);

    if (!node) {
        return nullptr;
    }

    Record *record = new Record();

    for (XMLElement *child = node->FirstChildElement(); child != 0; child = child->NextSiblingElement()) {
        Column *column = new Column(child->Name(), child->GetText());
        record->addColumn(column);
    }

    return record;
}

void XmlDatabase::update(Record *record) {

    const char *id = record->getId();
    XMLNode *node = XmlDatabase::xmlFindRecordById(id);

    if (node) {
        vector<Column *> columns = record->getColumns();
        for (auto column : columns) {
            for (XMLElement *child = node->FirstChildElement(); child != 0; child = child->NextSiblingElement()) {
                if (strcmp(child->Name(), column->getKey()) == 0 && column->getValue()) {
                    child->SetText(column->getValue());
                }
            }
        }

        XmlDatabase::saveFile(XmlDatabase::dbName);
    }
}

list<Record *> XmlDatabase::select() {

    int indexColumn = 0;
    int indexRow = 0;

    XMLNode *pRoot = XmlDatabase::xmlGetRootNode();
    list<Record *> result;

    for (XMLElement *node = pRoot->FirstChildElement("Record"); node != 0; node = node->NextSiblingElement()) {
        Record *record = new Record(indexRow++);
        indexColumn = 0;
        for (XMLElement *child = node->FirstChildElement(); child != 0; child = child->NextSiblingElement()) {

            Column *column = new Column(child->Name(), child->GetText(), indexColumn++);
            record->addColumn(column);
        }
        result.push_back(record);
    }

    XmlDatabase::dataSet.setRecordList(result);

    return result;
}

list<Record *> XmlDatabase::select(Record *where) {

    list<Record *> result;
    bool addRecord = false;
    const char *word;

    for (auto record: XmlDatabase::select()) {
        for (auto column: record->getColumns()) {
            word = where->getColumnValue(column->getKey());
            if (word != nullptr && column->getValue() != nullptr && strstr(column->getValue(), word) != nullptr) {
                addRecord = true;
            } else if (word != nullptr) {
                addRecord = false;
            }
        }

        if (addRecord) {
            result.push_back(record);
        }
    }

    return result;
}

DataSet XmlDatabase::getDataSet() {
    return XmlDatabase::dataSet;
}