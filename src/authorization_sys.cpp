#include "authorization_sys.hpp"

namespace sys
{
	bool user_sys::check_user_existence(std::string _login, std::string _password)
	{
		std::string _line;

		_user_ios.seekg(0);
		while (std::getline(_user_ios, _line))
		{
			auto _log = _line.find(_login);
			auto _pass = _line.find(_password);
			if (_log != std::string::npos && _pass != std::string::npos
				&& _log < _pass)
				return true;
		}
		_user_ios.clear();
		return false;
	}

	user_sys::user_sys(std::iostream& _ios, std::ostream& _os, std::istream& _key_is)
		: _user_ios(_ios)
		, _log_os(_os)
		, _eds(_key_is)
	{
	}

	void user_sys::register_user(std::string _login, std::string _password,
		std::string _question, std::string _answer)
	{
		_login = _eds.encrypt(_login);
		_password = _eds.encrypt(_password);

		if (!check_user_existence(_login, _password))
		{
			_question = _eds.encrypt(_question);
			_answer = _eds.encrypt(_answer);

			_user_ios
				<< "Login:" << _login << ' '
				<< "Password:" << _password << ' '
				<< "Secret question:" << _question << ' '
				<< "Answer:" << _answer << '\n';
			_log_os << ("User \'" + _login + "\' registered in the user system.");
		}
	}

	bool user_sys::sign_in(std::string _login, std::string _password)
	{
		return check_user_existence(_eds.encrypt(_login), _eds.encrypt(_password));
	}
}
