delphyforecast

doushadeMBP:~ cl$ cleos create key
Private key: 5HpfrRettiCo1WDmBV2TMGc2JE32vkGPp1F9EKA3kqKNxNf9L7z
Public key: EOS72u3vGxanQMUNuZnteNTDYuRYgyCGPLnyZwecinbSuCLr9X6zs
doushadeMBP:~ cl$ cleos create key
Private key: 5Jo8BqwKuv8tmw6nRYBDeFW5XFuw6u7N6dhBraoDixNBHsV3bK6
Public key: EOS68pJgFj6BXw2j5D3DoYZQo6Px87KfgKy5D7xw8uYPefTzYPtwz


cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/ create account eosio delphyfore EOS72u3vGxanQMUNuZnteNTDYuRYgyCGPLnyZwecinbSuCLr9X6zs  EOS68pJgFj6BXw2j5D3DoYZQo6Px87KfgKy5D7xw8uYPefTzYPtwz

cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/ create account eosio delforeadm EOS72u3vGxanQMUNuZnteNTDYuRYgyCGPLnyZwecinbSuCLr9X6zs  EOS68pJgFj6BXw2j5D3DoYZQo6Px87KfgKy5D7xw8uYPefTzYPtwz

cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/ create account eosio delphy EOS72u3vGxanQMUNuZnteNTDYuRYgyCGPLnyZwecinbSuCLr9X6zs  EOS68pJgFj6BXw2j5D3DoYZQo6Px87KfgKy5D7xw8uYPefTzYPtwz



cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/   push action delphyfore addqurey '{"par":{"id":"1","from":"delphy", "roles":"LTC/BTC","mode":"normal","mode_detail":"","type":"exchange","aspect":"price","provider":"okex","startdate":"0","enddate":"1527144959","conditions":"100,1000，>=100000，<100000","appealenddate":"1527144959","unit":"cny","status":"0","created":"0","updated":"0"}}' -p delphy

cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/   push action delphyfore clearquery '{"id":"107820858998785"}' -p delforeadm

cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/ get table -l 100 delphyfore delforeadm oraclequery




cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/   push action delphyfore addappeal  '{"par":{"id":"0", "from":"delforeadm", "idquery":"0","reason":"not satisfy","created":"0","updated":"0"}}' -p  delforeadm

cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/ get table -l 100 delphyfore delforeadm appeal


cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/   push action delphyfore addanswer '{"par":{"idquery":"2","checked":"1","appealnum":"1","realvalue":"1","result":"1","unitrate":"1","created":"0","updated":"0"}}' -p delforeadm

cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/ get table -l 100 delphyfore delforeadm queryresult