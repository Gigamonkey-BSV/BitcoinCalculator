#include <Diophant/built.in/hd.hpp>
#include <gigamonkey/schema/hd.hpp>

namespace Diophant {
    namespace HD = Gigamonkey::HD;

    data::N hd_get_secret (const data::string &x) {
        return data::N (HD::BIP_32::secret::read (x).Secret.Value);
    }

    secp256k1::pubkey hd_get_pubkey (const data::string &x) {
        return HD::BIP_32::pubkey::read (x).Pubkey;
    }

    data::bytes sign (const std::string &key, const data::uint256_little &digest) {
        return HD::BIP_32::secret::read (key).sign (digest);
    }

    bool verify (const std::string &x, const data::uint256_little &digest, const data::bytes &sig) {
        return HD::BIP_32::pubkey::read (x).Pubkey.verify (digest, secp256k1::signature {sig});
    }

    data::string hd_secret_to_public (const data::string &x) {
        return HD::BIP_32::secret::read (x).to_public ().write ();
    }

    data::string hd_pubkey_derive (const data::string &x, const data::N &d) {
        data::uint32 dd = static_cast<data::uint32> (data::int32 (d));
        return HD::BIP_32::pubkey::read (x).derive ({dd}).write ();
    }

    data::string hd_derive (const data::string &x, const data::N &d) {
        data::uint32 dd = static_cast<data::uint32> (data::int32 (d));
        return HD::BIP_32::secret::read (x).derive ({dd}).write ();
    }

    data::string hd_derive_hardened (const data::string &x, const data::N &d) {
        data::uint32 dd = static_cast<data::uint32> (data::int32 (d));
        return HD::BIP_32::pubkey::read (x).derive ({HD::BIP_32::harden (dd)}).write ();
    }

}
