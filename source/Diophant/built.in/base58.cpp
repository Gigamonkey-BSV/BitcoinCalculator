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

    data::string address_encode (const data::bytes &dig, Bitcoin::net net) {
        if (dig.size () != 20) throw data::exception {} << "invalid size for address.";
        digest160 digest;
        std::copy (dig.begin (), dig.end (), digest.begin ());
        return Bitcoin::address::encode (net, digest);
    }

    data::tuple<data::bytes, Bitcoin::net> address_decode (const data::string &addr) {
        auto decoded = Bitcoin::address::decode (addr);
        data::bytes b {};
        b.resize (20);
        std::copy (decoded.Digest.begin (), decoded.Digest.end (), b.begin ());
        return {b, decoded.Network};
    }

    static_assert (std::same_as<data::uint256, data::math::uint<data::endian::little, 4, data::uint64>>);

    data::string WIF_encode (const data::N &secret, Bitcoin::net mainnet, bool compressed) {
        return Bitcoin::WIF::encode (mainnet,
            secp256k1::secret {data::uint256_little (secret)}, compressed);
    }

    data::tuple<data::N, Bitcoin::net, bool> WIF_decode (const data::string &wif) {
        auto decoded = Bitcoin::WIF::decode (wif);
        return {data::N (decoded.Secret.Value), decoded.Network, decoded.Compressed};
    }

}
