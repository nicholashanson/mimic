#include <catch2/catch_all.hpp>

#include <vector>

#include <protocol.hpp>

TEST_CASE( "Get Message Type" ) {
    std::vector<uint8_t> client_payload = { 0x01 };
    auto message_type = mimic::get_message_type( client_payload );
    REQUIRE( message_type.has_value() == true );
    REQUIRE( message_type.value() == mimic::message_type::init );
}