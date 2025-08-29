#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <cstdint>

#include <optional>
#include <span>

namespace mimic {
	
	enum class message_type : uint8_t {
		init = 0x01
	};

	std::optional<message_type> get_message_type( const std::span<const uint8_t> message );

} // namespace mimic

#endif // PROTOCOL_HPP