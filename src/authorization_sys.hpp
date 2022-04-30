#ifndef AUTHORIZATION_SYS_HPP
#define AUTHORIZATION_SYS_HPP

#include "encr_decr_service.hpp"
#include "output_service.hpp"

namespace sys
{
	using namespace logging;
	using namespace encr_decr;

	class user_sys
	{
		bool check_user_existence(std::string, std::string);

		// bool check_user_existence(...); - overload
	public:
		user_sys(std::iostream&, std::ostream&, std::istream&);

		void register_user(std::string, std::string, std::string, std::string);
		bool sign_in(std::string, std::string);

		// void delete_user(...);
		// void resume_user(...);
		// void change_user(...);

	private:
		std::iostream& _user_ios;
		output_device    _log_os;
		encr_decr_service   _eds;
	};
}

#endif
