void online_game()
{

    y = 0;
    l = get_level();
    cout << "level : " << l << endl;
    SDL_RenderCopy(render, texture_wait, NULL, NULL);
    SDL_RenderPresent(render);
    is_online_game = 1;
    while(id2 == "0")
    {
        SDL_Delay(50);   //finding a player
    }
    play();
}

int thread_playing_online(void *_)
{
    while(1)if(is_online_game)break;
    i_win=0;
    cout << "STREAMING .." << endl;
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
        ws.handshake(host, "/game/stream");
        beast::flat_buffer buffer;

        cout << "connecting ..." << endl;

        //demmand id of player 2

        do
        {
            text = "@ " + to_string(l);
            ws.write(net::buffer(text));
            ws.read(buffer);
            text = beast::buffers_to_string(buffer.data()) ;
            buffer.clear();
        }
        while(text == ".");
        id2 = text;
        //the game begain
        cout << text << endl;
        while(1)
        {
            buffer.clear();
            text = to_string(level.player.x) + " " + to_string(level.player.y);
            if(i_win){
                i_win=0;
                text="WIN";
                cout<<"you win";
                break;
            }
            // Send the message
            ws.write(net::buffer(text));
            // This buffer will hold the incoming message
            // Read a message into our buffer
            ws.read(buffer);
            text = beast::buffers_to_string(buffer.data()) ;

            if(text == "LOSE")
            {

                cout << "you lose" << endl;
                break;
            }

            streams = stringstream(text);
            streams >> player2.first >> player2.second;
        }
        // Close the WebSocket connection
        ws.close(websocket::close_code::normal);
        // If we get here then the connection is closed gracefully

    }
    catch(exception const &e)
    {

        cout << "Error: " << e.what() << endl;
    }
    index();
    return 1;
}
