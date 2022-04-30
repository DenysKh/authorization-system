#include "encr_decr_service.hpp"

namespace encr_decr
{
	encr_decr_service::encr_decr_service(std::istream& _is)
	{
		_is.seekg(-1, std::ios::end);
		_is >> _key;
	}

	std::string encr_decr_service::encrypt(std::string _line)
	{
		for (char& _ : _line)
		{
			_ ^= _key;
		}
		return _line;
	}

	std::string encr_decr_service::decrypt(std::string _line)
	{
		for (char& _ : _line)
		{
			_ ^= _key;
		}
		return _line;
	}
}
