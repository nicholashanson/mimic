#include <cstdint>

#include <span>
#include <vector>

#include <openssl/evp.h>  
#include <openssl/rand.h>  
#include <openssl/err.h>

#include <crypto.hpp>

namespace mimic {

	encrypted_packet encrypt( const std::span<const uint8_t> plain_text, const std::span<const uint8_t> key ) {
		constexpr std::size_t tag_size = 16;
		constexpr std::size_t iv_size = 12;
		encrypted_packet packet;
		packet.cipher_text.resize( plain_text.size() );
		packet.tag.resize( tag_size );
		packet.iv.resize( iv_size );
		RAND_bytes( packet.iv.data(), iv_size );
		EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
		EVP_EncryptInit_ex( ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr );
		EVP_EncryptInit_ex( ctx, nullptr, nullptr, key.data(), packet.iv.data() );
		int len = 0;
		EVP_EncryptUpdate( ctx, packet.cipher_text.data(), &len, plain_text.data(), plain_text.size() );
		int cipher_text_len = len;
		EVP_EncryptFinal_ex( ctx, packet.cipher_text.data() + len, &len );
		cipher_text_len += len;
		packet.cipher_text.resize( cipher_text_len );
		EVP_CIPHER_CTX_ctrl( ctx, EVP_CTRL_GCM_GET_TAG, tag_size, packet.tag.data() );
		EVP_CIPHER_CTX_free( ctx );
		return packet;
	}

	std::vector<uint8_t> decrypt( const encrypted_packet& packet, const std::span<const uint8_t> key ) {
		constexpr std::size_t tag_size = 16;
		std::vector<uint8_t> plain_text( packet.cipher_text.size() );
		EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
		EVP_DecryptInit_ex( ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr );
		EVP_DecryptInit_ex( ctx, nullptr, nullptr, key.data(), packet.iv.data() );
		int len = 0;
		EVP_DecryptUpdate( ctx, plain_text.data(), &len, packet.cipher_text.data(), packet.cipher_text.size() );
		std::vector<uint8_t> tag_copy = packet.tag;
		EVP_CIPHER_CTX_ctrl( ctx, EVP_CTRL_GCM_SET_TAG, tag_size, tag_copy.data() );
		int plain_text_len = len;
		EVP_DecryptFinal_ex( ctx, plain_text.data() + len, &len );
		plain_text_len += len;
		plain_text.resize( plain_text_len );
		EVP_CIPHER_CTX_free( ctx );
		return plain_text;
	}

} // namespace mimic