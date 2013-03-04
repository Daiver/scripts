#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char **argv)
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], "1300");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);
        for (;;)
        {
            boost::array<float, 7> b;
            b[0] = 3; b[1] = 10; b[2] = 11; b[3]; b[4] = 1; b[5] = 99; b[6] = 9;
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(b), ignored_error);
            for(int i = 0; i < 3; i++)
            {
                boost::array<float, 3> b2;
                b2[0] = 117.0; b2[1] = 9878.0; b2[2] = 98.0;
                boost::asio::write(socket, boost::asio::buffer(b2), ignored_error);
            }
                                            
            /*
            boost::array<char, 128> buf;
            boost::system::error_code error;
            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
                else if (error)
                    throw boost::system::system_error(error); // Some other error.
                std::cout.write(buf.data(), len);
            */
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
