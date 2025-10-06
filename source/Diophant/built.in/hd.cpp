#include <Diophant/built.in/hd.hpp>
#include <gigamonkey/schema/hd.hpp>

namespace Diophant {
    namespace HD = Gigamonkey::HD;

    data::string encode_HD_pubkey (
        const secp256k1::pubkey &p,
        const data::bytes &chain_code,
        Bitcoin::net network,
        data::byte depth,
        data::uint32 parent,
        data::uint32 sequence) {
        if (chain_code.size () != 32) throw data::exception {} << "invalid chain code size " << chain_code.size ();
        HD::chain_code cc;
        std::copy (chain_code.begin (), chain_code.end (), cc.begin ());
        return HD::BIP_32::pubkey {p, cc,
            network, depth, parent, sequence}.write ();
    }

    data::string encode_HD_secret (
        const data::N &x,
        const data::bytes &chain_code,
        Bitcoin::net network,
        data::byte depth,
        data::uint32 parent,
        data::uint32 sequence) {
        if (chain_code.size () != 32) throw data::exception {} << "invalid chain code size " << chain_code.size ();
        HD::chain_code cc;
        std::copy (chain_code.begin (), chain_code.end (), cc.begin ());
        return HD::BIP_32::secret {secp256k1::secret {data::uint256_little {x}}, cc,
            network, depth, parent, sequence}.write ();
    }

    data::tuple<secp256k1::pubkey, data::bytes, Bitcoin::net, data::byte, data::uint32, data::uint32>
    decode_HD_pubkey (const std::string &x) {
        auto k = HD::BIP_32::pubkey::read (x);
        if (!k.valid ()) throw data::exception {} << "invalid HD pubkey";
        data::bytes b (32);
        std::copy (k.ChainCode.begin (), k.ChainCode.end (), b.begin ());
        return {k.Pubkey, b, k.Network, k.Depth, k.Parent, k.Sequence};
    }

    data::tuple<data::N, data::bytes, Bitcoin::net, data::byte, data::uint32, data::uint32>
    decode_HD_secret (const std::string &x) {
        auto k = HD::BIP_32::secret::read (x);
        if (!k.valid ()) throw data::exception {} << "invalid HD secret";
        data::bytes b (32);
        std::copy (k.ChainCode.begin (), k.ChainCode.end (), b.begin ());
        return {data::N (k.Secret.Value), b, k.Network, k.Depth, k.Parent, k.Sequence};
    }

    data::bytes sign (const std::string &key, const data::uint256_little &digest) {
        auto k = HD::BIP_32::secret::read (key);
        if (!k.valid ()) throw data::exception {} << "invalid HD secret";
        return k.sign (digest);
    }

    bool verify (const std::string &x, const data::uint256_little &digest, const data::bytes &sig) {
        auto k = HD::BIP_32::pubkey::read (x);
        if (!k.valid ()) throw data::exception {} << "invalid HD pubkey";
        return k.Pubkey.verify (digest, secp256k1::signature {sig});
    }

    data::string hd_secret_to_public (const data::string &x) {
        auto k = HD::BIP_32::secret::read (x);
        if (!k.valid ()) throw data::exception {} << "invalid HD secret";
        return k.to_public ().write ();
    }

    data::string hd_pubkey_derive (const data::string &x, data::list<data::uint32> d) {
        auto k = HD::BIP_32::pubkey::read (x);
        if (!k.valid ()) throw data::exception {} << "invalid HD pubkey";
        return k.derive (d).write ();
    }

    data::string hd_secret_derive (const data::string &x, data::list<data::uint32> d) {
        auto k = HD::BIP_32::secret::read (x);
        if (!k.valid ()) throw data::exception {} << "invalid HD secret";
        return k.derive (d).write ();
    }

}
