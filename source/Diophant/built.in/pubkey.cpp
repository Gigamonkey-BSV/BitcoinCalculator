#include <Diophant/built.in/pubkey.hpp>
#include <gigamonkey/wif.hpp>

namespace Diophant {

    static_assert (std::same_as<data::uint256, data::math::uint<data::endian::little, 4, data::uint64>>);

    bool pubkey_valid (const data::bytes &x) {
        return secp256k1::pubkey::valid (x);
    }

    bool pubkey_equal (const data::bytes &x, const data::bytes &y) {
        return secp256k1::pubkey {x} == secp256k1::pubkey {y};
    }

    data::bytes secret_to_public (bool y, const data::N &x) {
        secp256k1::secret z {data::uint256_little (x)};
        if (!z.valid ()) throw data::exception {} << "invalid secret key";

        return z.to_public (y);
    }

    data::bytes pubkey_negate (const data::bytes &x) {
        if (!secp256k1::pubkey::valid (x)) throw data::exception {} << "invalid public key";
        return secp256k1::pubkey::negate (x);
    }

    bool pubkey_compressed (const data::bytes &x) {
        if (!secp256k1::pubkey::valid (x)) throw data::exception {} << "invalid public key";
        return secp256k1::pubkey::compressed (x);
    }

    bool pubkey_uncompressed (const data::bytes &x) {
        if (!secp256k1::pubkey::valid (x)) throw data::exception {} << "invalid public key";
        return !secp256k1::pubkey::compressed (x);
    }

    data::bytes pubkey_compress (const data::bytes &x) {
        if (!secp256k1::pubkey::valid (x)) throw data::exception {} << "invalid public key";
        return secp256k1::pubkey::compress (x);
    }

    data::bytes pubkey_decompress (const data::bytes &x) {
        if (!secp256k1::pubkey::valid (x)) throw data::exception {} << "invalid public key";
        return secp256k1::pubkey::decompress (x);
    }

    data::bytes pubkey_plus (const data::bytes &x, const data::bytes &y) {
        if (!secp256k1::pubkey::valid (x)) throw data::exception {} << "invalid public key";
        if (!secp256k1::pubkey::valid (y)) throw data::exception {} << "invalid public key";
        return secp256k1::pubkey::plus_pubkey (x, y);
    }

    data::bytes pubkey_times (const data::bytes &x, const data::N &y) {
        if (!secp256k1::pubkey::valid (x)) throw data::exception {} << "invalid public key";
        secp256k1::secret z {data::uint256_little (y)};
        if (!z.valid ()) throw data::exception {} << "invalid secret key";
        return secp256k1::pubkey::times (x, z.Value);
    }

    data::bytes pubkey_times (const data::N x, const data::bytes &y) {
        if (!secp256k1::pubkey::valid (y)) throw data::exception {} << "invalid public key";
        secp256k1::secret z {data::uint256_little (x)};
        if (!z.valid ()) throw data::exception {} << "invalid secret key";
        return secp256k1::pubkey::times (y, z.Value);
    }

    data::bytes sign (const data::N &key, const data::uint256_little &digest) {
        return secp256k1::secret {data::uint256_little {key}}.sign (digest);
    }

    bool verify (const data::bytes &x, const data::bytes &digest, const data::bytes &sig) {
        if (digest.size () != 32) throw data::exception {} << "invalid signature size";
        data::uint256_little dig;
        std::copy (digest.begin (), digest.end (), dig.begin ());
        return secp256k1::pubkey::verify (x, dig, secp256k1::signature {sig});
    }

    data::uint160_little address_hash (const data::bytes &p) {
        return Bitcoin::Hash160 (p);
    }

    data::string address_from_pubkey (const data::bytes &p, Bitcoin::net mainnet) {
        return Gigamonkey::Bitcoin::address::encode (mainnet, Bitcoin::Hash160 (p));
    }

    data::string address_from_secret (const data::N &n, Bitcoin::net mainnet, bool compressed) {
        return address_from_pubkey (secret_to_public (compressed, n), mainnet);
    }

    data::bytes sign_with_WIF (const data::string &wif, const data::uint256_little &digest) {
        return Bitcoin::WIF::decode (wif).sign (digest);
    }

    data::string address_from_WIF (const data::string &wif) {
        return Bitcoin::WIF::decode (wif).address ().encode ();
    }
}
