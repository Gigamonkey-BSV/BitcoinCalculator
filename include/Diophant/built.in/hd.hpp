#ifndef BITCOIN_CALCULATOR_BUILTIN_HD
#define BITCOIN_CALCULATOR_BUILTIN_HD

#include <Diophant/built.in/pubkey.hpp>

namespace Diophant {

    data::N hd_get_secret (const data::string &);
    secp256k1::pubkey hd_get_pubkey (const data::string &);

    data::bytes sign (const std::string &key, const data::uint256_little &digest);
    bool verify (const std::string &x, const data::uint256_little &digest, const data::bytes &sig);

    data::string hd_secret_to_public (const data::string &);
    data::string hd_pubkey_derive (const data::string &, const data::N &);
    data::string hd_derive (const data::string &, const data::N &);
    data::string hd_derive_hardened (const data::string &, const data::N &);

}

#endif

