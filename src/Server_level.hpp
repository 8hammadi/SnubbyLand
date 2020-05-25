string POST(string data)
{
    try
    {
        // The io_context is required for all I/O
        net::io_context ioc;
        // These objects perform our I/O
        tcp::resolver resolver{ioc};
        websocket::stream<tcp::socket> ws{ioc};
        // Look up the domain name
        boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> results = resolver.resolve(host, port);
        // Make the connection on the IP address we get from a lookup
        net::connect(ws.next_layer(), results.begin(), results.end());
        // Set a decorator to change the User-Agent of the handshake
        ws.set_option(websocket::stream_base::decorator(
                          [](websocket::request_type & req)
        {
            req.set(boost::beast::http::field::user_agent,
                    string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-client-coro");
        }));
        // Perform the websocket handshake
        ws.handshake(host, "/game/level");
        beast::flat_buffer buffer;
        ws.write(net::buffer(data));
        ws.read(buffer);
        // Close the WebSocket connection
        ws.close(websocket::close_code::normal);
        // If we get here then the connection is closed gracefully

        return beast::buffers_to_string(buffer.data());

    }
    catch(exception const &e)
    {

        cout << "Error: " << e.what() << endl;
    }
    return ".";
}


string send_level_to_server(int k)
{

    cout << "SEND LEVEL " << k << " Level" << endl;
    std::ifstream t("../levels/" + to_string(k));
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    // cout<<"ID OF LEVEL :"<<POST(str)<<endl;
    return POST(str);
}


bool get_level_from_server(string levelid) // ex:k="L201"
{
    cout << "GET LEVEL ONLINE .." << endl;
    string input = POST(levelid);
    if(input == ".")return 0;
    ofstream out(levelid);
    out << input;
    out.close();

    cout << input << endl;
    ifstream ifs(levelid);
    boost::archive::text_iarchive ar(ifs);
    ar &ll;
    level = *ll;
    return 1;
}