#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include "mbc_radio.h"

class Channel {
public :
	virtual void play() = 0;
	virtual void stop() = 0;
	virtual std::string getName() const {
		// TODO : implement Channel::getName()
		return std::string("Not Assigned");
	}
	friend std::ostream& operator << (std::ostream& o, const Channel& ch) {
		o << ch.getName();
		return o;
	}
};
class Channel_MBC_Fun : public Channel {
public :
	void play() {
		obj.start_stream(1);
	}
	void stop() {
		obj.stop_stream();
	}
	std::string getName() const {
		return std::string("MBC Fun Radio");
	}
private :
	MBC_Radio obj;
};
class Channel_MBC_Classic : public Channel {
public :
	void play() {
		obj.start_stream(2);
	}
	void stop() {
		obj.stop_stream();
	}
	std::string getName() const {
		return std::string("MBC Classic Radio");
	}
private :
	MBC_Radio obj;
};
struct MBC_Creator : public Channel {
	MBC_Creator(int ch = 0, const std::string& chName = "") : channel_number(ch), channel_name(chName) {}
	void play() {
		obj.start_stream(channel_number);
	}
	void stop() {
		obj.stop_stream();
	}
	std::string getName() const {
		return channel_name;
	}
private :
	MBC_Radio obj;
	int channel_number;
	std::string channel_name;
};
class Radio {
	typedef Channel Element;
	typedef Element& Reference;
	typedef Element* Pointer;
	typedef std::list<Pointer> ChannelListType;
	typedef ChannelListType::iterator ChannelIterator;
public :
	int select_channel() {
		unsigned int choice;

		// show channel list, then get user choice.
		do {
			int index = 0;
			std::cout << index++ << " : exit" << std::endl;
			for (Pointer& e : channellist) {
				std::cout << index++ << " : " << *e << std::endl;
			}
			std::cout << "Choose Channel Number :> ";
			std::cin >> choice;
		} while (choice < 0 || choice >= channellist.size());

		if (choice == 0) {
			quit();
			return 0;
		}

		current_channel = choice - 1;

		return choice;
	}
	void play() {
		ChannelIterator it = channellist.begin();
		std::advance(it, current_channel);

		(*it)->play();
	}
	void stop() {
		ChannelIterator it = channellist.begin();
		std::advance(it, current_channel);

		(*it)->stop();
	}
	void record() {

	}
	void quit() {
		stop();

		// TODO : implement Radio::quit()
	}
	void addChannel(const Pointer& ch) {
		channellist.push_back(ch);
	}
private :
	ChannelListType channellist;
	int current_channel;
};

std::list<std::pair<int,std::string>> channel_info_parser(std::fstream& file) {
	std::list<std::pair<int, std::string>> ret;

	int number = 0;
	std::string name;
	char c;
	int state = 0;
	while (file.get(c).good()) {
		if (c == '\n' || c == '\r') {
			state = 0;
		}
		// set number.
		else if (state == 0) {
			if (c == ' ') {
				ret.push_back(std::make_pair(number,std::string()));

				state = 1;
				number = 0;
			}
			else if (c > '0' && c < '9') {
				number *= 10;
				number += c - '0';
			}
		}
		// set name.
		else if (state == 1) {
			ret.back().second.append(1, c);
		}
	}

	return ret;
}

int main(void) {
	Radio mymy;

	mymy.addChannel(new Channel_MBC_Fun());
	mymy.addChannel(new Channel_MBC_Classic());

	std::fstream file("mbc_channel_info.txt", std::ios_base::in);
	if (!file.good()) {
		std::cerr << "channel file not found." << std::endl;
		return 1;
	}
	// number string(contains space)
	std::list<std::pair<int, std::string>> channel_infos;
	channel_infos = channel_info_parser(file);

	//char* mbc_names[] = {"MBC Fun Radio", "MBC Classic Radio", "MBC Fun Fun"};
	//for (int i = 0; i < 10; i++) {
	//	mymy.addChannel(new MBC_Creator(i, mbc_names[i]));
	//}
	for (std::pair<int, std::string>& e : channel_infos) {
		mymy.addChannel(new MBC_Creator(e.first, e.second));
	}

	return 0;
}