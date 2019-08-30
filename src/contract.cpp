#include <contract.hpp>

#include <eosio/asset.hpp>

namespace cognaize {

void phonebook::version()
{
  print("Phonebook version 0.1");
};

void phonebook::addperson(string fullname, string phonenumber)
{
  require_auth(_self);

  check(fullname.size() <= 256, "fullname name has more than 256 bytes");
  check(phonenumber.size() <= 256, "phonenumber name has more than 256 bytes");

  // update the table to include a new poll
  _phonebook.emplace(get_self(), [&](auto &item) {
    item.key = _phonebook.available_primary_key();
    item.fullname = fullname;
    item.phonenumber = phonenumber;
  });
}

} // namespace cognaize
