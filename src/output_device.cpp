#include "output_service.hpp"

namespace logging
{
	output_device::output_device(std::ostream& _os)
		: _curr_os(&_os)
		, _emer_os(&std::cerr)
		, _log_max_size(log_buffer_type::container_type().max_size())
	{
	}

	output_device::~output_device()
	{
		if (_curr_os == &std::cerr)
		{
			if (!_emer_os->fail())
			{
				while (!_log_buffer.empty())
				{
					*_emer_os << _log_buffer.front() << std::endl;
					_log_buffer.pop();
				}
			}
		}
	}

	output_device& operator<<(output_device& _inst, std::string _log)
	{
		if (_inst._curr_os->fail())
		{
			std::swap(_inst._curr_os, _inst._emer_os);
			*_inst._curr_os
				<< "\nThe main logging stream has failed."
				<< "\nBackup started."
				<< "\nThe main stream will be resumed after the problem is fixed.\n\n";
		}

		if (_inst._curr_os == &std::cerr)
		{
			if (_inst._emer_os->fail())
			{
				if (_inst._log_buffer.size() == _inst._log_max_size)
				{
					throw buffer_overflow("buffer overflowed");
				}
				_inst._log_buffer.push(_log + '\n');
			}
			else
			{
				std::swap(_inst._emer_os, _inst._curr_os);

				while (!_inst._log_buffer.empty())
				{
					*_inst._curr_os << _inst._log_buffer.front() << std::endl;
					_inst._log_buffer.pop();
				}
			}
		}

		*_inst._curr_os << _log << std::endl;
		return _inst;
	}
}
