namespace mimic {

	struct encrypted_packet {
		std::vector<uint8_t> cipher_text;
		std::vector<uint8_t> tag;
		std::vector<uint8_t> iv;
	};

	encrypted_packet encrypt( const std::span<const uint8_t> plain_text, const std::span<const uint8_t> key );

	std::vector<uint8_t> decrypt( const encrypted_packet& packet, const std::span<const uint8_t> key );

}