#pragma once

#include <eosio/eosio.hpp>

#include <string>
#include <set>

namespace cognaize {

  // using namespace eosio;
  using eosio::contract;
  using eosio::name;
  using eosio::check;
  using eosio::print;

  using std::string;

  class [[eosio::contract("phonebook")]] phonebook : public contract
  {
  public:
    using contract::contract;
    phonebook(name receiver, name code, eosio::datastream<const char *> ds)
        : contract(receiver, code, ds), _phonebook(receiver, code.value)
    {
    } 

    // create the multi index tables to store the data
    struct [[eosio::table]] person
    {
      uint64_t key; // primary key
      string fullname;
      string phonenumber;

      uint64_t primary_key() const { return key; }
    };

    typedef eosio::multi_index<"person"_n, person> phonebook_t;  

    phonebook_t _phonebook; 

    // [[eosio::action]] will tell eosio-cpp that the function is to be exposed as an action for user of the smart contract.
    [[eosio::action]] void version();
    [[eosio::action]] void addperson(string fullname, string phonenumber);

  };

  EOSIO_DISPATCH( phonebook, (version)(addperson) )

} // namespace cognaize

