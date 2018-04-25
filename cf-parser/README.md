# Config file parser
Simple config file parser module. Parses valid* config files into the config structure defined in config.hpp file.

valid config example:
```
[section1]
key1=value11 | value12 | value13

; this is a comment

[section2]
key2=value21
key2=value22
key2=value23

[section3]
key2=value21 | value22
key2=value23
```
