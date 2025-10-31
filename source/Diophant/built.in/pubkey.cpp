#include <Diophant/built.in/pubkey.hpp>
#include <gigamonkey/wif.hpp>

namespace Diophant {

    static_assert (std::same_as<data::uint256, data::math::uint<data::endian::little, 4, data::uint64>>);

    bool pubkey_valid (const secp256k1::pubkey &x) {
        return x.valid ();
    }

    secp256k1::pubkey secret_to_public (bool y, const data::N &x) {
        secp256k1::secret z {data::uint256_little (x)};
        if (!z.valid ()) throw data::exception {} << "invalid secret key";

        return z.to_public (y);
    }

    secp256k1::pubkey pubkey_negate (const secp256k1::pubkey &x) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        return -x;
    }

    bool pubkey_compressed (const secp256k1::pubkey &x) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        return x.compressed ();
    }

    bool pubkey_uncompressed (const secp256k1::pubkey &x) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        return !x.compressed ();
    }

    secp256k1::pubkey pubkey_compress (const secp256k1::pubkey &x) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        return x.compress ();
    }

    secp256k1::pubkey pubkey_decompress (const secp256k1::pubkey &x) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        return x.decompress ();
    }

    secp256k1::pubkey pubkey_plus (const secp256k1::pubkey &x, const secp256k1::pubkey &y) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        if (!y.valid ()) throw data::exception {} << "invalid public key";
        return x + y;
    }

    secp256k1::pubkey pubkey_times (const secp256k1::pubkey &x, const data::N &y) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        secp256k1::secret z {data::uint256_little (y)};
        if (!z.valid ()) throw data::exception {} << "invalid secret key";
        return x * z;
    }

    secp256k1::pubkey pubkey_times (const data::N x, const secp256k1::pubkey &y) {
        if (!y.valid ()) throw data::exception {} << "invalid public key";
        secp256k1::secret z {data::uint256_little (x)};
        if (!z.valid ()) throw data::exception {} << "invalid secret key";
        return y * z;
    }

    data::bytes sign (const data::N &key, const data::uint256_little &digest) {
        return secp256k1::secret {data::uint256_little {key}}.sign (digest);
    }

    bool verify (const secp256k1::pubkey &x, const data::bytes &digest, const data::bytes &sig) {
        if (digest.size () != 32) throw data::exception {} << "invalid signature size";
        data::uint256_little dig;
        std::copy (digest.begin (), digest.end (), dig.begin ());
        return x.verify (dig, secp256k1::signature {sig});
    }

    data::uint160_little address_hash (const secp256k1::pubkey &p) {
        return Bitcoin::Hash160 (p);
    }

    data::string address_from_pubkey (const secp256k1::pubkey &p, Bitcoin::net mainnet) {
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
