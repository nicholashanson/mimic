#include <protocol.hpp>

namespace mimic {

	std::optional<message_type> get_message_type( const std::span<const uint8_t> message ) {
		auto type = static_cast<message_type>( message.front() );
		if ( type == message_type::init ) return message_type::init;
		return std::nullopt;
	}

} // namespace mimic

