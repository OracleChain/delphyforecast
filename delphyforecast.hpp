/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosiolib/eosio.hpp>


#define SUCCESS_CODE 0
#define QUERY_ALREADY_EXISTS "6000001 QUERY_ALREADY_EXISTS" //参数错误
#define QUERY_NOT_EXISTS "6000002 QUERY_NOT_EXISTS"
#define QUERY_EXPIRED   "6000003 QUERY_EXPIRED"
#define TIME_NOT_REACHED "6000004 TIME_NOT_REACHED"

static long QUERY_STATUS_NOT_DEAL = 0l;
static long QUERY_STATUS_DEALED = 1l;

using namespace eosio;
/*
@abi table
*/
struct OracleQuery{
    uint64_t id;
    account_name from;
    std::string roles;//["BTC/USD"],

    std::string mode;//"normal", // 表示原值
    std::string mode_detail;//ration|value等取值

    std::string type;//"exchange"
    std::string aspect;//"price", // 价格
    std::string provider;//"okcoin", // 从哪个源获取的值

    uint64_t startdate;//15234345", //取结果的时间,utc 单位秒
    uint64_t enddate;//15234345", //取结果的时间,utc 单位秒

    std::string conditions;//:[">=10000","<10000"],//大于等于 1 万，小于 1 万
    uint64_t    appealenddate;//"43200" // 申诉时间,问题发起方，可能对此问题的答案有异议
    std::string unit;//usd或者cny等单位

    uint8_t     status;//当前状态 0表示未处理，1表示已经处理

    uint64_t created;
    uint64_t updated;

    uint64_t primary_key()const { return id; }

    EOSLIB_SERIALIZE(OracleQuery, (id)(from)(roles)(mode)(mode_detail)(type)(aspect)(provider)(startdate)(enddate)(conditions)(appealenddate)(unit)(status)(created)(updated))
};



/*
@abi table appeal i64
*/
struct Appeal{
    uint64_t id;
    uint64_t idquery;

    account_name from;
    std::string reason;

    uint64_t created;
    uint64_t updated;

    uint64_t primary_key()const { return id; }
    uint64_t get_secondary()const { return idquery; }

    EOSLIB_SERIALIZE(Appeal, (id)(idquery)(from)(reason)(created)(updated))
};



/*
@abi table
*/
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

    EOSLIB_SERIALIZE(QueryResult, (idquery)(checked)(appealnum)(readvalue)(result)(unitrate)(created)(updated))
};

typedef eosio::multi_index<N(oraclequery), OracleQuery> OralceQureyContainer;
typedef eosio::multi_index<N(queryresult), QueryResult> QueryResultContainer;
typedef eosio::multi_index<N(appeal), Appeal,
   eosio::indexed_by< N(bysecondary), eosio::const_mem_fun<Appeal,  uint64_t, &Appeal::get_secondary> >> AppealContainer;

class Delphyforecast : public contract {

    static const uint64_t admin = N(delforeadm);

    public:
    Delphyforecast( account_name self )
    :contract(self)
    {}

    /// @abi action
    void clearquery(uint64_t id);

    /// @abi action
    void addqurey( OracleQuery oq );

    /// @abi action
    void addappeal(const Appeal & a);

    /// @abi action
    void addanswer(const QueryResult & queryResult);
};

EOSIO_ABI( Delphyforecast, (addqurey)(addappeal)(addanswer)(clearquery))




