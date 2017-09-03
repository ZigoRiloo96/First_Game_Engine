#include "Engine.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

using namespace std;

sqlite3* db;

using Record = std::vector<std::string>;
using Records = std::vector<Record>;

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
    Records* records = static_cast<Records*>(p_data);
    try {
        records->emplace_back(p_fields, p_fields + num_fields);
    }
    catch (...) {
        // abort select on failure, don't let exception propogate thru sqlite3 call-stack
        return 1;
    }
    return 0;
}

Records select_stmt(const char* stmt)
{
    Records records;
    char *errmsg;
    int ret = sqlite3_exec(db, stmt, select_callback, &records, &errmsg);
    if (ret != SQLITE_OK) {
        std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
    }
    else {
        std::cerr << records.size() << " records returned.\n";
    }

    return records;
}

void sql_stmt(const char* stmt)
{
    char *errmsg;
    int ret = sqlite3_exec(db, stmt, 0, 0, &errmsg);
    if (ret != SQLITE_OK) {
        std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
    }
}

void loadStandartObjects()
{

}

void Engine::testDataLoad(const char *file)
{
    if (sqlite3_open(file, &db) != SQLITE_OK) {
        std::cerr << "Could not open database.\n";
        return;
    }

    Records records = select_stmt("SELECT * FROM COLLIDERS");
    Records StandartObjects_records = select_stmt("SELECT * FROM StandartObjects");
    sqlite3_close(db);

    for (auto& record : records) {
        // do something with your records
        int col[5];
        int i = 0;
        for (string s : record)
        {
            col[i] = std::stoi(s);
            std::cout << col[i] << "\n";
            i++;
        }
        m_Colliders.push_back(new Collider("first", sf::IntRect(col[1], col[2], col[3], col[4])));
    }

    for (auto& record : StandartObjects_records) {
        // do something with your records
        int col[5];
        int i = 0;
        for (string s : record)
        {
            col[i] = std::stoi(s);
            std::cout << col[i] << "\n";
            i++;
        }
        m_StandartObjects.push_back(new StandartObject(col[1], col[2], m_pEntityTextures.at(col[3]), col[3]));
    }
}

void Engine::testDataSave(const char *file)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *sql;

    rc = sqlite3_open(file, &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    //sql = "CREATE TABLE COLLIDERS("  \
    //    "ID INT PRIMARY KEY NOT NULL," \
    //    "posX           INT ," \
    //    "posY           INT ," \
    //    "sizeX          INT ," \
    //    "sizeY          INT );";

    string coli = " ";

    coli = "DELETE FROM COLLIDERS;";

    std::cout << coli << "\n";
    sql = coli.c_str();

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    coli = "DELETE FROM StandartObjects;";

    std::cout << coli << "\n";
    sql = coli.c_str();

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    coli = "";
    int i = 1;

    for (Collider* c : m_Colliders)
    {
        coli += "INSERT INTO COLLIDERS (ID,posX,posY,sizeX,sizeY) VALUES (";
        coli += std::to_string(i);
        coli += ", ";
        coli += std::to_string(c->getPosition().x);
        coli += ", ";
        coli += std::to_string(c->getPosition().y);
        coli += ", ";
        coli += std::to_string(c->getSize().x);
        coli += ", ";
        coli += std::to_string(c->getSize().y);
        coli += "); ";
        ++i;
    }

    std::cout << coli << "\n";
    sql = coli.c_str();

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Records created successfully\n");
    }

    //StandartObjectsSave
    coli = "";
    i = 0;

    for (StandartObject* c : m_StandartObjects)
    {
        coli += "INSERT INTO StandartObjects (ID,posX,posY,numTexture) VALUES (";
        coli += std::to_string(i);
        coli += ", ";
        coli += std::to_string(c->mf_getSprite().getPosition().x);
        coli += ", ";
        coli += std::to_string(c->mf_getSprite().getPosition().y);
        coli += ", ";
        coli += std::to_string(c->getID());
        coli += "); ";
        ++i;
    }

    std::cout << coli << "\n";
    sql = coli.c_str();

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Records created successfully\n");
    }

    //delete[] sql;
    sqlite3_close(db);
}