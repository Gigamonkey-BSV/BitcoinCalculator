#include <built.in/pubkey.hpp>

namespace Diophant {

    Bitcoin::integer pubkey_equal (const secp256k1::pubkey &x, const secp256k1::pubkey &y) {
        return x == y;
    }

    Bitcoin::integer pubkey_identical (const secp256k1::pubkey &x, const secp256k1::pubkey &y) {
        return x != y;
    }

    Bitcoin::integer pubkey_unequal (const secp256k1::pubkey &x, const secp256k1::pubkey &y) {
        return static_cast<const data::bytes &> (x) == static_cast<const data::bytes &> (y);
    }

    Bitcoin::integer pubkey_valid (const secp256k1::pubkey &x) {
        return Bitcoin::integer {x.valid ()};
    }

    secp256k1::pubkey secret_to_public (const uint256 &x, const Bitcoin::integer &y) {
        secp256k1::secret z {x};
        if (!z.valid ()) throw data::exception {} << "invalid secret key";

        return z.to_public (bool (y));
    }

    secp256k1::pubkey pubkey_negate (const secp256k1::pubkey &x) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        return -x;
    }

    Bitcoin::integer pubkey_compressed (const secp256k1::pubkey &x) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        return Bitcoin::integer {x.compressed ()};
    }

    Bitcoin::integer pubkey_uncompressed (const secp256k1::pubkey &x) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        return Bitcoin::integer {!x.compressed ()};
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

    secp256k1::pubkey pubkey_times (const secp256k1::pubkey &x, const uint256 &y) {
        if (!x.valid ()) throw data::exception {} << "invalid public key";
        secp256k1::secret z {y};
        if (!z.valid ()) throw data::exception {} << "invalid secret key";
        return x * z;
    }

    secp256k1::pubkey pubkey_times (const uint256 &x, const secp256k1::pubkey &y) {
        if (!y.valid ()) throw data::exception {} << "invalid public key";
        secp256k1::secret z {x};
        if (!z.valid ()) throw data::exception {} << "invalid secret key";
        return y * z;
    }
}
