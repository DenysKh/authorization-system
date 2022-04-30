#ifndef OUTPUT_SERVICE_HPP
#define OUTPUT_SERVICE_HPP

#include <iostream>
#include <string>
#include <queue>

namespace logging
{
	class buffer_overflow : public std::runtime_error
	{
	public:
		using std::runtime_error::runtime_error;
	};

	class output_device
	{
	public:
		using log_buffer_type = std::queue< std::string >;

		explicit output_device(std::ostream&);
		~output_device();

		friend output_device& operator<<(output_device&, std::string);
	private:
		std::ostream* _curr_os;
		std::ostream* _emer_os;
		log_buffer_type _log_buffer;
		typename log_buffer_type::size_type _log_max_size;
	};
}

#endif
