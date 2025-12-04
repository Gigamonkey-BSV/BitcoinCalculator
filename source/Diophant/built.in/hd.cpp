#include <Diophant/built.in/hd.hpp>
#include <gigamonkey/schema/hd.hpp>

namespace Diophant {
    namespace HD = Gigamonkey::HD;

    data::N harden (const data::N &n) {
        uint32_t d;
        try {
            d = uint32_t (n);
        } catch (...) {
            throw data::exception {} << "invalid derivation";
        }
        return HD::BIP_32::harden (d);
    }

    data::N soften (const data::N &n) {
        uint32_t d;
        try {
            d = uint32_t (n);
        } catch (...) {
            throw data::exception {} << "invalid derivation";
        }
        return HD::BIP_32::soften (d);
    }

    HD::BIP_32::pubkey inline make_HD_pubkey (
        const data::bytes &p,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence) {
        if (depth > 255) throw data::exception {} << "depth cannot be larger than 255";
        if (chain_code.size () != 32) throw data::exception {} << "invalid chain code size " << chain_code.size ();
        HD::chain_code cc;
        std::copy (chain_code.begin (), chain_code.end (), cc.begin ());
        return HD::BIP_32::pubkey {
            Bitcoin::pubkey {p}, cc,
            network, data::byte (data::uint32 (depth)), data::uint32 (parent), data::uint32 (sequence)};
    }

    HD::BIP_32::secret inline make_HD_secret (
        const data::N &x,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence) {
        if (depth > 255) throw data::exception {} << "depth cannot be larger than 255";
        if (chain_code.size () != 32) throw data::exception {} << "invalid chain code size " << chain_code.size ();
        HD::chain_code cc;
        std::copy (chain_code.begin (), chain_code.end (), cc.begin ());
        return HD::BIP_32::secret {
            secp256k1::secret {data::uint256_little {x}}, cc,
            network, data::byte (data::uint32 (depth)), data::uint32 (parent), data::uint32 (sequence)};
    }

    data::string encode_HD_pubkey (
        const data::bytes &p,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence) {
        return make_HD_pubkey (p, chain_code, network, depth, parent, sequence).write ();
    }

    data::string encode_HD_secret (
        const data::N &x,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence) {
        return make_HD_secret (x, chain_code, network, depth, parent, sequence).write ();
    }

    data::tuple<data::bytes, data::bytes, Bitcoin::net, data::N, data::N, data::N>
    decode_HD_pubkey (const data::string &x) {
        auto k = HD::BIP_32::pubkey::read (x);
        if (!k.valid ()) throw data::exception {} << "invalid HD pubkey";
        data::bytes b (32);
        std::copy (k.ChainCode.begin (), k.ChainCode.end (), b.begin ());
        return {k.Pubkey, b, k.Network, k.Depth, k.Parent, k.Sequence};
    }

    data::tuple<data::N, data::bytes, Bitcoin::net, data::N, data::N, data::N>
    decode_HD_secret (const data::string &x) {
        auto k = HD::BIP_32::secret::read (x);
        if (!k.valid ()) throw data::exception {} << "invalid HD secret";
        data::bytes b (32);
        std::copy (k.ChainCode.begin (), k.ChainCode.end (), b.begin ());
        return {data::N (k.Secret.Value), b, k.Network, k.Depth, k.Parent, k.Sequence};
    }

    data::string HD_secret_to_public (const data::string &x) {
        auto k = HD::BIP_32::secret::read (x);
        if (!k.valid ()) throw data::exception {} << "invalid HD secret";
        return k.to_public ().write ();
    }

    data::tuple<data::bytes, data::bytes, Bitcoin::net, data::N, data::N, data::N>
    HD_secret_to_public (
        const data::N &x,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence) {
        auto pub = make_HD_secret (x, chain_code, network, depth, parent, sequence).to_public ();
        return {pub.Pubkey, pub.ChainCode, pub.Network, pub.Depth, pub.Parent, pub.Sequence};
    }

    data::string address_from_HD (const data::string &x) {
        HD::BIP_32::pubkey xpub;
        auto xprv = HD::BIP_32::secret::read (x);
        if (!xprv.valid ()) xpub = HD::BIP_32::pubkey::read (x);
        else xpub = xprv.to_public ();
        if (!xpub.valid ()) throw data::exception {} << "invalid hd key";
        return Bitcoin::address::decoded (xpub).encode ();
    }

    data::tuple<data::bytes, Bitcoin::net> address_from_HD (
        const data::N &x,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence) {
        auto xpub = make_HD_secret (x, chain_code, network, depth, parent, sequence).to_public ();
        if (!xpub.valid ()) throw data::exception {} << "invalid hd key";
        auto addr = Bitcoin::address::decoded (xpub);
        return {addr.Digest, addr.Network};
    }

    data::tuple<data::bytes, Bitcoin::net> address_from_HD (
        const data::bytes &pubkey,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence) {
        auto xpub = make_HD_pubkey (pubkey, chain_code, network, depth, parent, sequence);
        if (!xpub.valid ()) throw data::exception {} << "invalid hd key";
        auto addr = Bitcoin::address::decoded (xpub);
        return {addr.Digest, addr.Network};
    }

    data::string HD_derive (const data::string &x, const data::N &n) {

        uint32_t d;
        try {
            d = uint32_t (n);
        } catch (...) {
            throw data::exception {} << "invalid derivation";
        }

        HD::BIP_32::secret sk = HD::BIP_32::secret::read (x);
        if (sk.valid ()) return sk.derive ({d}).write ();

        bool hardened = static_cast<int32_t> (d) < 0;

        HD::BIP_32::pubkey pk = HD::BIP_32::pubkey::read (x);
        if (!pk.valid ()) throw data::exception {} << "invalid HD pubkey";
        if (hardened) throw data::exception {} << "cannot harden derive an HD pubkey";

        return pk.derive ({d}).write ();

    }

    data::tuple<data::bytes, data::bytes, Bitcoin::net, data::N, data::N, data::N>
    HD_derive (
        const data::bytes &p,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence, const data::N &n) {

        uint32_t d;
        try {
            d = uint32_t (n);
        } catch (...) {
            throw data::exception {} << "invalid derivation";
        }

        bool hardened = static_cast<int32_t> (d) < 0;
        if (hardened) throw data::exception {} << "cannot harden derive an HD pubkey";

        auto pub = make_HD_pubkey (p, chain_code, network, depth, parent, sequence).derive ({d});
        return {pub.Pubkey, pub.ChainCode, pub.Network, pub.Depth, pub.Parent, pub.Sequence};
    }

    data::tuple<data::N, data::bytes, Bitcoin::net, data::N, data::N, data::N>
    HD_derive (
        const data::N &x,
        const data::bytes &chain_code,
        Bitcoin::net network,
        const data::N &depth,
        const data::N &parent,
        const data::N &sequence, const data::N &n) {

        uint32_t d;
        try {
            d = uint32_t (n);
        } catch (...) {
            throw data::exception {} << "invalid derivation";
        }

        auto sec = make_HD_secret (x, chain_code, network, depth, parent, sequence).derive ({d});
        return {data::N (sec.Secret.Value), sec.ChainCode, sec.Network, sec.Depth, sec.Parent, sec.Sequence};
    }

    data::bytes sign_with_HD (const data::string &xprv, const data::bytes &digest) {
        if (digest.size () != 32) throw data::exception {} << "invalid digest size";
        auto k = HD::BIP_32::secret::read (xprv);
        if (!k.valid ()) throw data::exception {} << "invalid HD secret";
        data::uint256_little dig {};
        std::copy (digest.begin (), digest.end (), dig.begin ());
        return Bitcoin::secret (k).sign (dig);
    }

    bool verify_with_HD (const data::string &xpub, const data::bytes &digest, const data::bytes &sig) {
        if (digest.size () != 32) throw data::exception {} << "invalid digest size";
        auto k = HD::BIP_32::pubkey::read (xpub);
        if (!k.valid ()) throw data::exception {} << "invalid HD pubkey";
        data::uint256_little dig {};
        std::copy (digest.begin (), digest.end (), dig.begin ());
        return k.Pubkey.verify (dig, secp256k1::signature {sig});
    }

    data::N HD_get_secret (const data::string &xprv) {
        auto k = HD::BIP_32::secret::read (xprv);
        if (!k.valid ()) throw data::exception {} << "invalid HD secret";
        return data::N (k.Secret.Value);
    }

    data::bytes HD_get_pubkey (const data::string &xpub) {
        auto k = HD::BIP_32::pubkey::read (xpub);
        if (!k.valid ()) throw data::exception {} << "invalid HD pubkey";
        return k.Pubkey;
    }

}
