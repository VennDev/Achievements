#include "PlayerData.h"

#define DATABASE_FILE "plugins\\Achievements\\points.db"

static std::unique_ptr<SQLite::Database> db;

void initDB() {
    db = std::make_unique<SQLite::Database>(DATABASE_FILE, SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
    std::string smt = "CREATE TABLE IF NOT EXISTS points(uuid VARCHAR(36) PRIMARY KEY, ";
    for (PointType type = (PointType)0; type <= PointType::Killing; type = static_cast<PointType>((size_t)type+1)) {
        smt += type_tostring(type) + " REAL NOT NULL, ";
    }
    smt = smt.substr(0, smt.size() - 2);
    db->exec(smt + ")");
}

void initPoint(Player* player) {
    SQLite::Statement query(*db, "INSERT INTO points VALUES (?, ?)");
    query.bindNoCopy(1, player->getUuid());
    query.bind(2, DEFAULT_POINTS);
    query.exec();
}

float getPoint(Player* player, PointType type) {
    SQLite::Statement query(*db, "SELECT ? FROM points WHERE uuid=?");
    query.bind(1, type_tostring(type));
    query.bindNoCopy(2, player->getUuid());
    while (query.executeStep()) {
        return query.getColumn(0).getDouble();
    }
    initPoint(player);
    return DEFAULT_POINTS;
}

void setPoint(Player* player, PointType type, float point) {
    SQLite::Statement query(*db, "UPDATE points SET ?=? WHERE uuid=?");
    query.bind(1, type_tostring(type));
    query.bind(2, point);
    query.bindNoCopy(3, player->getUuid());
    query.exec();
}

float addPoint(Player* player, PointType type, float point) {
    float total = getPoint(player, type) + point;
    if (total >= 0) {
        setPoint(player, type, total);    
    }
    return total;
}

float reducePoint(Player* player, PointType type, float point) {
    float total = getPoint(player, type) - point;
    if (total >= 0) {
        setPoint(player, type, total);    
    }
    return total;
}


float getPointa(PointType type) {
    SQLite::Statement query1(*db, "SELECT ? FROM points WHERE uuid=?");
    query1.bind(1, type_tostring(type));
    query1.bindNoCopy(2, "abc");
    while (query1.executeStep()) {
        return query1.getColumn(0).getDouble();
    }
    SQLite::Statement query2(*db, "INSERT INTO points VALUES (?, ?)");
    query2.bindNoCopy(1, "abc");
    query2.bind(2, DEFAULT_POINTS);
    query2.exec();
    return DEFAULT_POINTS;
}
void setPointa(PointType type, float point) {
    SQLite::Statement query(*db, "UPDATE points SET ?=? WHERE uuid=?");
    query.bind(1, type_tostring(type));
    query.bind(2, point);
    query.bindNoCopy(3, "abc");
    query.exec();
}