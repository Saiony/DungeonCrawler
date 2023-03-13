#include<iostream>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE
#include<asio.hpp>
#include<asio/ts/buffer.hpp>
#include<asio/ts/internet.hpp>

std::vector<char> vBuffer(20 * 1024);

void GrabSomeData(asio::ip::tcp::socket& socket)
{
	socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
		[&](std::error_code errorCode, std::size_t length)
		{
			if (errorCode)
				return;

			std::cout << "\n\nRead " << length << " bytes\n\n";

			for (int i = 0; i < length; i++)
				std::cout << vBuffer[i];

			GrabSomeData(socket);
		}
	);
}

int main()
{
	asio::error_code errorcode;

	asio::io_context context; //platform specific interface

	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", errorcode), 80);

	asio::ip::tcp::socket socket(context);
	socket.connect(endpoint, errorcode);

	if (errorcode)
		std::cout << "Failed to connect to address. \n " << errorcode.message() << std::endl;
	else
		std::cout << "Connected!" << std::endl;

	//get info from example.com
	if (socket.is_open())
	{
		GrabSomeData(socket);


		std::string sRequest = 
			"GET /index.html HTTP/1.1\r\n"
			"Host: example.com\r\n"
			"Connection: close\r\n\r\n";

		socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), errorcode);

		using namespace std::chrono_literals; 
		std::this_thread::sleep_for(2000ms);
	}

	return 0;
}