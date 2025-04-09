#include <built.in/base58.hpp>
#include <gigamonkey/p2p/checksum.hpp>

namespace Diophant {

    uint256 decode_base_58 (const data::string &x) {
        data::maybe<uint256> result = data::encoding::base58::decode<uint256> (x);
        if (!bool (result)) throw data::exception {} << "invalid base 58 string";
        return *result;
    }

    data::string encode_base_58 (const uint256 &x) {
        return data::encoding::base58::encode<uint256> (x);
    }

    data::string encode_base_58_check (const data::byte &b, const Bitcoin::integer &z) {
        return Gigamonkey::base58::check (b, z).encode ();
    }

    std::tuple<data::byte, Bitcoin::integer> decode_base_58_check (const data::string &x) {
        auto ch = Gigamonkey::base58::check::decode (x);
        return {ch.version (), Bitcoin::integer::read (ch.payload ())};
    }

}
