#include <Diophant/built.in/base58.hpp>
#include <gigamonkey/p2p/checksum.hpp>

namespace Diophant {

    data::N decode_base_58 (const data::string &x) {
        data::maybe<data::N> result = data::encoding::base58::decode<data::N> (x);
        if (!bool (result)) throw data::exception {} << "invalid base 58 string";
        return *result;
    }

    data::string encode_base_58 (const data::N &x) {
        return data::encoding::base58::encode<data::N> (x);
    }

    data::string encode_base_58_check (const data::byte &b, const data::bytes &z) {
        return Gigamonkey::base58::check (b, z).encode ();
    }

    std::tuple<data::byte, data::bytes> decode_base_58_check (const data::string &x) {
        auto ch = Gigamonkey::base58::check::decode (x);
        return {ch.version (), ch.payload ()};
    }

}
