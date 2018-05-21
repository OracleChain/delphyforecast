/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosiolib/eosio.hpp>


#define SUCCESS_CODE 0
#define QUERY_ALREADY_EXISTS "6000001 QUERY_ALREADY_EXISTS" //参数错误
#define QUERY_NOT_EXISTS "6000002 QUERY_NOT_EXISTS"
#define QUERY_EXPIRED   "6000003 QUERY_EXPIRED"

/*
@abi action
@abi table
*/
struct OralceQurey{
    uint64_t id;
    account_name from;
    std::vector<std::string> roles;//["BTC/USD"],

    std::string mode;//"normal", // 表示原值
    std::string mode_detail;//ration|value等取值

    std::string type;//"exchange"
    std::string aspect;//"price", // 价格
    std::string provider;//"okcoin", // 从哪个源获取的值

    uint64_t startdate;//15234345", //取结果的时间,utc 单位秒
    uint64_t enddate;//15234345", //取结果的时间,utc 单位秒

    std::vector<std::string> conditions;//:[">=10000","<10000"],//大于等于 1 万，小于 1 万
    uint64_t    appealenddate;//"43200" // 申诉时间,问题发起方，可能对此问题的答案有异议
    std::string unit;//usd或者cny等单位

    uint8_t     status;//当前状态 0表示未处理，1表示已经处理

    uint64_t created;
    uint64_t updated;

    uint64_t primary_key()const { return id; }

    EOSLIB_SERIALIZE(OralceQurey, (id)(from)(roles)(mode)(mode_detail)(type)(aspect)(provider)(startdate)(enddate)(conditions)(appealenddate)(unit)(status)(created)(updated));
};

typedef eosio::multi_index<N(OralceQurey), OralceQurey> OralceQureyContainer;

/*
@abi action
@abi table
*/
struct Appeal{
    uint64_t id;
    uint64_t idquery;

    account_name from;
    uint64_t reason;

    uint64_t created;
    uint64_t updated;

    uint64_t primary_key()const { return id; }
    uint64_t get_secondary()const { return idquery; }

    EOSLIB_SERIALIZE(Appeal, (id)(from)(idquery)(reason)(created)(updated));
};

typedef eosio::multi_index<N(Appeal), Appeal,
   eosio::indexed_by< N(bysecondary), eosio::const_mem_fun<Appeal,  uint64_t, &Appeal::get_secondary> >> AppealContainer;


struct QueryResult{
    uint64_t idquery;

    uint8_t checked;
    uint64_t appealnum;
    std::string readvalue;
    std::string result;
    std::string unitrate;

    uint64_t created;
    uint64_t updated;

    uint64_t primary_key()const { return idquery; }

    EOSLIB_SERIALIZE(QueryResult, (idquery)(checked)(appealnum)(readvalue)(result)(unitrate)(created)(updated));
};

typedef eosio::multi_index<N(QueryResult), QueryResult> QueryResultContainer;

class Delphyforecast : public eosio::contract {
    static const uint64_t contractCode = N(delphyfore);
    static const uint64_t admin = N(delforeadm);


    public:
      using contract::contract;

      /// @abi action
      void addOralceQurey( OralceQurey oq ) {
            OralceQureyContainer oralceQureyContainer(contractCode， admin);
            const_iterator ite = oralceQureyContainer.find(oq.id);
            eosio_assert(ite != oralceQureyContainer.end(), QUERY_ALREADY_EXISTS);

            oralceQureyContainer.emplace(admin, [&](auto &s){
                s..id            = oq.id;
                s..from          = oq.from;
                s..roles         = oq.roles;
                s..mode          = oq.mode;
                s..mode_detail   = oq.mode_detail;
                s..type          = oq.type;
                s..aspect        = oq.aspect;
                s..provider      = oq.provider;
                s..startdate     = oq.startdate;
                s..enddate;       = oq.enddate;
                s..conditions;    = oq.conditions;
                s..appealenddate  = oq.appealenddate;
                s..unit;          = oq.unit;
                s..status;        = oq.status;
                s..created;       = oq.created;
                s..updated;       = oq.updated;
            });
      }

      void addAppeal(const Appeal & a){
          OralceQureyContainer oralceQureyContainer(contractCode， admin);
          const_iterator ite = oralceQureyContainer.find(a.idquery);
          eosio_assert(ite != oralceQureyContainer.end(), QUERY_EXPIRED);

          AppealContainer appealContainer(contractCode, admin);
          const_reverse_iterator ite = appealContainer.rbegin();
          if(ite == appealContainer.rend()){
              a.id = 0;
          }else{
              a.id = ite->id + 1;
          }

          appealContainer.emplace(admin, [&](auto &s){
                s.id      = a.id     ;
                s.idquery = a.idquery;
                s.from    = a.from   ;
                s.reason  = a.reason ;
                s.created = a.created;
                s.updated = a.updated;
          });

          auto secondary_index = appealContainer.template get_index<N(bysecondary)>();
          secondary_index.
      }
};

EOSIO_ABI( Delphyforecast, (addOralceQurey) )




