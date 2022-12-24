#pragma once

#include <mc/Player.hpp>

#include <sqlite3/sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>

#define DEFAULT_POINTS 0

enum PointType {
  Mining,
  Placing,
  Killing
};

inline std::string type_tostring(PointType type) {
  switch (type) {
    case PointType::Mining: return "mining";
    case PointType::Placing: return "placing";
    case PointType::Killing: return "killing";
  }
  return "";
}

void initDB();

float getPoint(Player* player, PointType type);
void setPoint(Player* player, PointType type, float point);
float addPoint(Player* player, PointType type, float point);
float reducePoint(Player* player, PointType type, float point);

float getPointa(PointType type);
void setPointa(PointType type, float point);