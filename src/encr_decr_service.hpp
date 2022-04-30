#ifndef ENCRYPTING_DECRYPTING_SERVICE_HPP
#define ENCRYPTING_DECRYPTING_SERVICE_HPP

#include <fstream>

namespace encr_decr
{
	class encr_decr_service
	{
		std::uint8_t _key;
	public:
		explicit encr_decr_service(std::istream&);

		std::string encrypt(std::string);
		std::string decrypt(std::string);
	};
}

#endif
