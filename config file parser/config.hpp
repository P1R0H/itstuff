#ifndef HW02_CONFIG_HPP
#define HW02_CONFIG_HPP

#include <iostream>
#include <map>
#include <set>
#include <string>

enum class Status {
	Success,
	MissingSection,
	MissingKey,
	FileNotFound,
	WrongFormat
};

class Config {

public:
	/** Read the config file.
	 *
	 *  @param name The path to the config file.
	 *  @return Success in case of success
	 *          FileNotFound in case the file cannot be opened (does not matter why)
	 *          WrongFormat in case the format of the config file is wrong
	 */
	Status read(const std::string &name);

	/** Get the config value.
	 *
	 *  @param secName The section of the config file.
	 *  @param keyName The key of the section of the config file.
	 *  @return {Success, value} in case of success
	 *          {MissingSection, empty string} in case the section name is not found
	 *          {MissingKey, empty string} in case the key is not found
	 *
	 * (Note: this function's prototype is going to change in the desired
	 *  extension. You may want to change the docstring accordingly.)
	 */
	std::pair<Status, std::set<std::string>> value(const std::string &secName, const std::string &keyName) const;

	/** Find out whether the config file contains a section with the given name.
	 *
	 *  @param secName The section of the config file.
	 *  @return true if contains, false otherwise
	 */
	bool hasSection(const std::string &secName) const;

	/** Find out whether the config file contains a key with the given name
         *  in the particular section.
	 *
	 *  @param secName The section of the config file.
	 *  @param keyName The key of the section of the config file.
	 *  @return true if contains, false otherwise
	 */
	bool hasKey(const std::string &secName, const std::string &keyName) const;

	/** Find out whether the given key of the given section has the provided value.
	 *
	 *  @param secName The section of the config file.
	 *  @param keyName The key of the section of the config file.
	 *  @param value The tested value.
	 *  @return true if the key can have only this value, false otherwise
	 */
	bool isValue(const std::string &secName, const std::string &keyName, const std::string &value) const;

	/** Find out whether the given key of given section can have provided value.
	 *
	 *  @param secName The section of the config file.
	 *  @param keyName The key of the section of the config file.
	 *  @param value The tested value.
	 *  @return true if the key can have the value, false otherwise
	 */
	bool hasValue(const std::string &secName, const std::string &keyName, const std::string &value) const;

	/** Prints out the current structure of the config file.
	 *
	 *  @param name The path to the output file.
	 *  @return Success in case of success
	 *          FileNotFound in case the file cannot be opened
	 */
	Status serialize(const std::string &fileName) const;

private:
	std::map<std::string, std::map<std::string, std::set<std::string>>> _data;
	std::string last_section;
	bool ignoringSection;
	bool addKey(const std::string &key, const std::string &value);
	bool addSection(const std::string &secName);

};

#endif // HW02_CONFIG_HPP
