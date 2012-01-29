std::string Ping::generate_answer(const std::string& sender,
                                  const std::string& text)
    {
        return std::string("pong you, ").append(sender);
    }
