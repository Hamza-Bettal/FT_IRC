/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:59:40 by hbettal           #+#    #+#             */
/*   Updated: 2025/03/17 12:41:51 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bot.hpp"

void sendMessage(int sock, const std::string message)
{
    std::string msg = message + "\r\n";
    send(sock, msg.c_str(), msg.length(), 0);
}

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter))
        result.push_back(token);
    return result;
}

void rmoveNew_line(std::string &str)
{
    std::string s = str;
    int i = str.size() - 1;
    while(str[i] == '\n' || str[i] == '\r')
    {
        str.erase(i);
        i--;
    }
}

std::string getRandJoke()
{
    std::string Jokes[] =
    {
        "A teacher asks a student: 'If your mom has 4 kids and your dad has 5, how many is that?' The student replies: 'Too many problems, sir!' 😂",
        "A Moroccan guy says to his friend: 'I want to marry a quiet woman.' His friend replies: 'Good luck, that only exists on traffic signs!' 🤣",
        "A Fassi, a Rbati, and a Casaoui find a magic lamp. The genie grants each of them a wish. The Fassi says: 'I want to be super rich!' The Rbati says: 'I want a royal palace!' The Casaoui says: 'Listen, I just want the two of them back here in five minutes!' 😂",
        "A kid tells his dad: 'Dad, I want a bicycle!' His dad replies: 'Inshallah, my son!' A week later, the kid comes back: 'Dad, where’s my bike?' The dad says: 'I’m still waiting for the store’s Inshallah!' 🤣",
        "A guy walks into a pharmacy and asks: 'Do you have medicine for stress?' The pharmacist replies: 'Yes, of course!' The guy says: 'Give me 10! My nervous system is completely wrecked!' 😂",
        "A Moroccan orders a pizza. The waiter asks: 'Do you want it cut into 6 or 8 slices?' He replies: 'No, no, 6 is better! 8 is too many, I won’t finish them all!' 🤣",
        "A father tells his son: 'If you do well in school, I’ll buy you a PlayStation.' The kid studies hard and says: 'Dad, where’s my PlayStation?' The dad replies: 'Good job! Now work to buy your own games!' 😂",
        "A man visits a mystic and says: 'Sidi, I want my wife to listen to me more!' The mystic gives him a magical talisman. He opens it and finds written inside: 'Close the bathroom door after use.' 🤣",
        "A Moroccan taxi driver is driving slowly. The passenger asks: 'Why are you driving so slow?' The driver replies: 'Because I have time.' The passenger asks: 'Then why are you honking at everyone?' The driver replies: 'Because they don’t!' 😂",
        "A man brags to his friend: 'My son is so smart, at six months he could say papa and mama!' His friend replies: 'Oh yeah? My son at three months was already saying: L9reeeebaaaaa (Taaaaxi)!' 🤣"
    };
    return Jokes[std::rand() % 10];
}

std::string getRandQuote()
{
    std::string quots[] =
    {
        "The only way to do great work is to love what you do. - Steve Jobs",
        "Success is not final, failure is not fatal: it is the courage to continue that counts. - Winston Churchill",
        "Believe you can and you're halfway there. - Theodore Roosevelt",
        "It does not matter how slowly you go as long as you do not stop. - Confucius",
        "Opportunities don't happen. You create them. - Chris Grosser",
        "The secret of getting ahead is getting started. - Mark Twain",
        "Difficulties in life are intended to make us better, not bitter. - Dan Reeves",
        "Do what you can, with what you have, where you are. - Theodore Roosevelt",
        "Hardships often prepare ordinary people for an extraordinary destiny. - C.S. Lewis",
        "Don't watch the clock; do what it does. Keep going. - Sam Levenson"
    };
    return quots[std::rand() % 10];
}

void handleResponse(int sock, std::string response)
{
    if (response.find("PRIVMSG " + std::string(NICK)) == std::string::npos)
        return;
    std::vector<std::string> msg = split(response, ':');
    if (msg.empty() || msg.size() < 2)
        return;
    std::vector<std::string> tmp = split(msg[1], '!');
    if (tmp.empty())
        return;
    std::string clientName = tmp[0];
    std::vector<std::string> names = split(msg[msg.size() - 1], ' ');
    std::string command = names[0];
    names.erase(names.begin());
    std::srand(time(0));
    rmoveNew_line(command);
    if (command == "JOCK")
    {
        sendMessage(sock, "PRIVMSG " + clientName + " : " + getRandJoke());
        return;
    }
    else if (command == "QUOTE")
    {
        sendMessage(sock, "PRIVMSG " + clientName + " : " + getRandQuote());
        return;
    }
    else if (command == "RAND")
    {
        if (names.size() < 2)
        {
            sendMessage(sock, "PRIVMSG " + clientName + " : Invalid number of arguments");
        }
        std::string winner = names[std::rand() % names.size()];
        sendMessage(sock, "PRIVMSG " + clientName + " : ===> " + winner + " <=== is the chosen one");
    }
    else if (command == "PING")
    {
        sendMessage(sock, "PRIVMSG " + clientName + " : PONG");
        return;
    }
    else if (command == "HELP")
    {
        sendMessage(sock, "PRIVMSG " + clientName + " : BOT commands: JOCK : get a joke, RAND : choose a random winner, PING : check if the bot is alive, QUOTE : get a motivation quote");
        return;
    }
    else
    {
        sendMessage(sock, "PRIVMSG " + clientName + " : Invalid BOT command (JOCK, RAND, PING, QUOTE, HELP)");
        return;
    }
}
