#define CATCH_CONFIG_MAIN  
#include <catch2/catch_all.hpp>

#include <vector>

#include <crypto.hpp>

TEST_CASE( "Encrypt Decrypt" ) {
    std::vector<uint8_t> plain_text = { 'H', 'e', 'l', 'l', 'o' };
    std::vector<uint8_t> key = { 0x00, 0x01, 0x02, 0x03,
                                 0x04, 0x05, 0x06, 0x07,
                                 0x08, 0x09, 0x0a, 0x0b,
                                 0x0c, 0x0d, 0x0e, 0x0f };
    auto encrypted_packet = mimic::encrypt( plain_text, key );
    auto unencrypted_packet = mimic::decrypt( encrypted_packet, key );
    REQUIRE( unencrypted_packet == plain_text );
}