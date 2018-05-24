#include <eosiolib/eosio.hpp>
#include "delphyforecast.hpp"

using namespace eosio;

void Delphyforecast::clearquery(uint64_t id){
    require_auth(admin);

    OralceQureyContainer oralceQureyContainer(_self, admin);
    auto ite = oralceQureyContainer.find(id);
    if(ite != oralceQureyContainer.end()){
        oralceQureyContainer.erase(ite);
    }
}

void Delphyforecast::addqurey( OracleQuery oq ) {
    require_auth(oq.from);

    OralceQureyContainer oralceQureyContainer(_self, admin);
    auto ite = oralceQureyContainer.find(oq.id);

    auto iteQueryId = oralceQureyContainer.rbegin();
    uint64_t id = 0;
    if(iteQueryId == oralceQureyContainer.rend()){
        id = 0;
    }else{
        id = iteQueryId->id + 1;
    }

    oralceQureyContainer.emplace(oq.from, [&](auto &s){
        s.id            = id;
        s.from          = oq.from;
        s.roles         = oq.roles;
        s.mode          = oq.mode;
        s.mode_detail   = oq.mode_detail;
        s.type          = oq.type;
        s.aspect        = oq.aspect;
        s.provider      = oq.provider;
        s.startdate     = oq.startdate;
        s.enddate       = oq.enddate;
        s.conditions    = oq.conditions;
        s.appealenddate  = oq.appealenddate;
        s.unit           = oq.unit;
        s.status         = QUERY_STATUS_NOT_DEAL;
        s.created        = now();
        s.updated        = now();
    });
}

void Delphyforecast::addappeal(const Appeal & a){

    require_auth(a.from);

    OralceQureyContainer oralceQureyContainer(_self, admin);
    auto iteQuery = oralceQureyContainer.find(a.idquery);
    eosio_assert(iteQuery != oralceQureyContainer.end(), QUERY_EXPIRED);

    AppealContainer appealContainer(_self, admin);
    auto ite = appealContainer.rbegin();
    uint64_t id = 0;
    if(ite == appealContainer.rend()){
        id = 0;
    }else{
        id = ite->id + 1;
    }

    appealContainer.emplace(admin, [&](auto &s){
          s.id      = id     ;
          s.idquery = a.idquery;
          s.from    = a.from   ;
          s.reason  = a.reason ;
          s.created = now();
          s.updated = now();
    });
}


void Delphyforecast::addanswer(const QueryResult & queryResult){

    require_auth(admin);

    OralceQureyContainer oralceQureyContainer(_self, admin);
    auto iteQuery = oralceQureyContainer.find(queryResult.idquery);
    eosio_assert(iteQuery!= oralceQureyContainer.end(), QUERY_NOT_EXISTS);
    eosio_assert(iteQuery->enddate<=now(), TIME_NOT_REACHED);

    QueryResultContainer queryResultContainer(_self, admin);
    auto ite = queryResultContainer.find(queryResult.idquery);

    if(ite == queryResultContainer.end()){
        queryResultContainer.emplace(admin, [&](auto&s){
            s.idquery  = queryResult.idquery;
            s.checked  = queryResult.checked;
            s.appealnum  = queryResult.appealnum;
            s.realvalue  = queryResult.realvalue;
            s.result  = queryResult.result;
            s.unitrate  = queryResult.unitrate;
            s.created  = queryResult.created;
            s.updated  = queryResult.updated;
        });
    }else{
          queryResultContainer.modify(queryResult, admin, [&](auto&s){
              s.idquery  = queryResult.idquery;
              s.checked  = queryResult.checked;
              s.appealnum  = queryResult.appealnum;
              s.realvalue  = queryResult.realvalue;
              s.result  = queryResult.result;
              s.unitrate  = queryResult.unitrate;
              s.created  = queryResult.created;
              s.updated  = queryResult.updated;
          });
    }

    oralceQureyContainer.modify(iteQuery, admin, [&](auto &s){
       s.status = QUERY_STATUS_DEALED;
    });
    eosio::print("version12");
}
