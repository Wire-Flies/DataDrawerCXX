#include "pgHelpers.hpp"
#include <iostream>

pgconn::pgconn(){
    conn = new pqxx::connection(
        "user=wireflies "
        "host=localhost "
        "password=wireflies "
        "dbname=wireflies");
}

pgconn::~pgconn(){
    delete conn;
}


std::map<unsigned long long, flight> pgconn::find_flights(std::string from, std::string to){
    pqxx::work work(*conn);
    std::string query = "SELECT flights.flight_id, snapshot_id, longitude, latitude FROM flights JOIN flight_data ON flights.flight_id = flight_data.flight_id WHERE schd_from LIKE '" + from + "' AND (real_to LIKE '" + to + "' OR (real_to IS NULL AND schd_to LIKE '" + to + "')) ORDER BY snapshot_id;";
    pqxx::result r = work.exec(query);
    
    std::map<unsigned long long, flight> flights;

    for(int i = 0; i < r.size(); i++){
        auto l = r[i];
        unsigned long long id = l[0].as<unsigned long long>(0);
        unsigned long long snapshot_id = l[1].as<unsigned long long>(0); 
        double longitude = l[2].as<double>(0);
        double latitude = l[3].as<double>(0);

        flights[id].positions.push_back({snapshot_id, longitude, latitude});
    }

    return flights;
}

