#include <iostream>
#include <fstream>
#include "HTTPRequest.hpp"

void post()
{

    http::Request request("http://localhost:8000/snubbyland_ensias_projet");
    std::map<std::string, std::string> parameters = {{"foo", "1"}, {"bar", "baz"}};
    const http::Response response = request.send("POST", parameters, {
        "Content-Type: application/x-www-form-urlencoded"
    });
    std::cout << std::string(response.body.begin(), response.body.end()) << '\n'; 

}




int main(int argc, char const *argv[])
{
	post();
	return 0;
}