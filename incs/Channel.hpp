//
// Created by Delphine Bouron on 02/02/2023.
//

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <map>
# include <vector>
# include "User.hpp"

class Channel
{
	public:
		Channel(const std::string &name, User &opUser);
		Channel(const Channel &src);
		Channel &operator=(const Channel &rhs);
		virtual ~Channel();

		const std::string &getName() const;
		const std::string &getSubject() const;
		bool getMode(char mode);
		const std::vector<User> &getUsers() const;
		bool isBanned(User &user);

		void setName(const std::string &name);
		void setSubject(const std::string &subject);
		void setMode(char &modeName, bool &isMode);
		void addUser(User &user);
		void addOpUser(User &opUser);
		void banUser(User &user);

	private:
		std::string				_name; //200 char max
		std::string 			_subject;
		std::map<char, bool>	_mode;
		std::vector<User>		_users;
		std::vector<User>		_opUsers;
		std::vector<User>		_bannedUsers;
		unsigned short			_usrNbMax;
		std::string 			_mdp;

		Channel();
};

#endif //CHANNEL_HPP
