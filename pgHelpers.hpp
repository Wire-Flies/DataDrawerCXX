#pragma once
#include <map>
#include <pqxx/pqxx>
#include <vector>
#include <string>

struct position{
    unsigned long long time;
    double longitude;
    double latitude;
};

struct flight {
    unsigned long long id;
    std::vector<position> positions; 
};

class pgconn{
    pqxx::connection * conn;
public:
    pgconn();
    ~pgconn();
    std::map<unsigned long long, flight> find_flights(std::string from, std::string to);
    std::map<unsigned long long, flight> find_all();
};

