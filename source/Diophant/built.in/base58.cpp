#include <Diophant/built.in/base58.hpp>
#include <gigamonkey/p2p/checksum.hpp>
#include <gigamonkey/wif.hpp>

namespace Diophant {
    using namespace Gigamonkey;

    data::N decode_base_58 (const data::string &x) {
        data::maybe<data::N> result = data::encoding::base58::decode<data::N> (x);
        if (!bool (result)) throw data::exception {} << "invalid base 58 string";
        return *result;
    }

    data::string encode_base_58 (const data::N &x) {
        return data::encoding::base58::encode<data::N> (x);
    }

    data::string encode_base_58_check (const data::byte &b, const data::bytes &z) {
        return base58::check (b, z).encode ();
    }

    data::tuple<data::byte, data::bytes> decode_base_58_check (const data::string &x) {
        auto ch = base58::check::decode (x);
        return {ch.version (), ch.payload ()};
    }

    data::string address_encode (const data::uint160_little &dig, bool mainnet) {
        return Bitcoin::address::encode (mainnet ? Bitcoin::net::Main: Bitcoin::net::Test, digest160 {dig});
    }

    static_assert (std::same_as<data::uint256, data::math::uint<data::endian::little, 4, data::uint64>>);

    data::string WIF_encode (const data::N &secret, bool mainnet, bool compressed) {
        return Bitcoin::WIF::encode (mainnet ? Bitcoin::net::Main: Bitcoin::net::Test,
            secp256k1::secret {data::uint256_little (secret)}, compressed);
    }

    data::tuple<data::uint160_little, bool> address_decode (const data::string &addr) {
        auto decoded = Bitcoin::address::decode (addr);
        return {decoded.Digest, decoded.Network == Bitcoin::net::Main};
    }

    data::tuple<data::N, bool, bool> WIF_decode (const data::string &wif) {
        auto decoded = Bitcoin::WIF::decode (wif);
        auto xl = decoded.Secret.Value.begin ();
        return {data::N (decoded.Secret.Value), decoded.Network == Bitcoin::net::Main, decoded.Compressed};
    }

}
