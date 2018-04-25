#include "config.hpp"
#include <fstream>
#include <map>

inline void ignoreSpaces(std::string &line) {
	line.erase(0, line.find_first_not_of(" \f\n\r\t\v"));
	line.resize(line.find_last_not_of(" \f\n\r\t\v") + 1);
}

inline bool isSection(const std::string &line) {
	return line[0] == '[' and line.find(']') != line.npos and line.find_last_of('[') == line.find_first_of('[');
}

inline bool isComment(const std::string &line) {
	return line[0] == ';';
}

inline bool isKey(const std::string &line) {
	return line.find_first_of('=') == line.find_last_of('=') and line.find('=') != line.npos;
}

inline bool isValid(const std::string &str) {
	return !str.empty();
}

bool Config::addSection(const std::string &secName) {
	std::string name = secName;
	ignoreSpaces(name);
	if (!isValid(name))
		return false;
	if (hasSection(name)) {
		ignoringSection = true;
		std::cerr << "Attempt to add already existing section " << secName << " ignored" << std::endl;
		return true;
	}
	std::map<std::string, std::set<std::string>> keys;
	_data.emplace(name, keys);

	ignoringSection = false;
	last_section = name;
	return true;
}

inline std::pair<bool, std::set<std::string>> parseValue(const std::string &value) {
	std::set<std::string> parsed;
	std::string new_feed = value;
	bool corr = true;

	do {
		std::string val = new_feed.substr(0, new_feed.find_first_of('|'));
		ignoreSpaces(val);
		if (!isValid(val))
			corr = false;
		parsed.insert(val);
		new_feed.erase(0, new_feed.find_first_of('|') + 1);
	} while (new_feed.find_first_of('|') != new_feed.npos);
	ignoreSpaces(new_feed);
	if (!isValid(new_feed))
		corr = false;
	parsed.insert(new_feed);
	return { corr, parsed };
}

bool Config::addKey(const std::string &key, const std::string &value) {
	if (ignoringSection)
		return true;
	std::pair<bool, std::set<std::string>> new_value = parseValue(value);
	if (!new_value.first)
		return false;

	std::string new_key = key;
	ignoreSpaces(new_key);
	if (!isValid(new_key))
		return false;

	if (!hasKey(last_section, new_key)) {
		_data[last_section].insert({ new_key, new_value.second });
	} else {
		for (auto &x : new_value.second)
			_data[last_section][new_key].insert(x);
	}
	return true;
}


Status Config::read(const std::string &name) {
	std::ifstream file;
	std::string line;
	file.open(name);
	last_section = "";
	ignoringSection = false;

	if (!file.is_open()) {
		std::cerr << "Unable to open provided file " << name << std::endl;
		return Status::FileNotFound;
	}
	while (std::getline(file, line)) {
		ignoreSpaces(line);
		if (line.empty() || isComment(line))
			continue;
		if (isSection(line)) {
			if (!addSection(line.substr(1, line.find_first_of(']') - 1)))
				return Status::WrongFormat;
		} else {
			if (!isValid(last_section) or !isKey(line) or _data.empty())
				return Status::WrongFormat;
			if (!addKey(line.substr(0, line.find_first_of('=')),
					line.substr(line.find_first_of('=') + 1, line.size() - 1)))
				return Status::WrongFormat;
		}
	}

	return Status::Success;
}

std::pair<Status, std::set<std::string>> Config::value(const std::string &secName, const std::string &keyName) const {
	if (!hasSection(secName))
		return { Status::MissingSection, {} };
	if (!hasKey(secName, keyName))
		return { Status::MissingKey, {} };
	return { Status::Success, _data.find(secName)->second.find(keyName)->second };
}

bool Config::hasSection(const std::string &secName) const {
	return _data.find(secName) != _data.end();
}

bool Config::hasKey(const std::string &secName, const std::string &keyName) const {
	if (hasSection(secName))
		return _data.find(secName)->second.find(keyName) != _data.find(secName)->second.end();
	return false;
}


bool Config::hasValue(const std::string &secName, const std::string &keyName, const std::string &value) const {
	if (hasKey(secName, keyName))
		return _data.find(secName)->second.find(keyName)->second.find(value) != _data.find(secName)->second.find(keyName)->second.end();
	return false;
}

bool Config::isValue(const std::string &secName, const std::string &keyName, const std::string &value) const {
	return hasValue(secName, keyName, value) && _data.find(secName)->second.find(keyName)->second.size() == 1;
}

Status Config::serialize(const std::string &fileName) const {
	std::ofstream output;
	output.open(fileName);

	for (auto &section : _data) {
		output << "[" << section.first << "]" << std::endl;
		for (auto &key : section.second) {
			for (auto &value : key.second) {
				output << key.first << " = " << value << std::endl;
			}
		}
		output << std::endl;
	}
	return Status::Success;
}
