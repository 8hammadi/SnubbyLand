string POST(map<string, string> parameters)
{
    try
    {
        http::Request request("http://horusnews.herokuapp.com/snubbyland_ensias_projet");
        // http::Request request("http://ensias.pythonanywhere.com/snubbyland");
        // http::Request request("http://localhost:8000/snubbyland_ensias_projet");

        const http::Response response = request.send("POST", parameters,
        {
            "Content-Type: application/x-www-form-urlencoded"
        });
        return string(response.body.begin(), response.body.end()) ;
    }
    catch(const std::exception &e)
    {
        cout  << e.what() << endl;
        return "e";
    }

}

string login(string id)
{
    return POST( {{"what", "login"}, {"id", id}}) ;
}

string logout(string id, string token)
{
    return POST( {{"what", "logout"}, {"id", id}, {"token", token}}) ;
}
//find_player return id of player online

string find_player(string id, int level)
{

    return POST( {{"what", "i want to play online ."}, {"id", id}, {"level", to_string(level)}});
}

//when the players playing

string send_and_get_status(string token, string id, int x, int y)
{
    return POST({{"what", "status_of_playing"}, {"id", id}, {"x", to_string(x)}, {"y", to_string(y)}, {"token", token}, {"i win", "0"}});
}


