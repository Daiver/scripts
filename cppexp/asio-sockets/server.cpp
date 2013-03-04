#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

int main(int argc, char** argv)
{
    try
    {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1300));
        for (;;)
        {
            tcp::socket socket(io_service);      
            //std::cout<<"Accept\n";
            acceptor.accept(socket);
            std::cout<<"Accept\n";
            for(;;)
            {
                boost::array<float, 7> buf;
                boost::system::error_code error;
                size_t len = socket.read_some(boost::asio::buffer(buf), error);
                if (error == boost::asio::error::eof)
                    break; // Connection closed cleanly by peer.
                else if (error)
                    throw boost::system::system_error(error); // Some other error.
                //std::cout.write(buf.data(), len);
                std::cout<<"FIRST ";
                for (int i = 0; i < 7; i++) std::cout<<buf[i]<<" ";
                std::cout<<std::endl;
                for (int j = 0; j < buf[0]; j++)
                {
                    boost::array<float, 3> buf2;
                    len = socket.read_some(boost::asio::buffer(buf2), error);
                    if (error == boost::asio::error::eof)
                        break; // Connection closed cleanly by peer.
                    else if (error)
                        throw boost::system::system_error(error); // Some other error.
                    std::cout<<"SECOND ";
                    for (int i = 0; i < 3; i++) std::cout<<buf2[i]<<" ";
                    std::cout<<std::endl;
                }

            }
            //std::string message = make_daytime_string();
            //boost::system::error_code ignored_error;
            //boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
