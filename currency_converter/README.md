# Currency Converter
two small apps - currency converter CLI and API

## Command Line Applicaion

```
current exchange rates are obtained by forex-python module:
https://github.com/MicroPyramid/forex-python

get forex:
% pip3 install forex-python

usage: currency_converter.py [-h] [-i [INFO]] [--amount AMOUNT]
                             [--output_currency OUT_CURR]
                             [--input_currency IN_CURR] [--file PATH]

optional arguments:
  -h, --help            show this help message and exit
  -i [INFO], --info [INFO]
                        prints out known currencies
  --amount AMOUNT       amount of input currency to be converted, 1.0 if not
                        present
  --output_currency OUT_CURR
                        output currency symbol or code, all known currencies
                        if not present
  --input_currency IN_CURR
                        output currency symbol or code
  --file PATH           output file path

```

### CurrencyConverter class
CurrencyConverter class can be imported from currency_converter module.

**Example:**
```python
from currency_converter import CurrencyConverter
from time import strftime, gmtime
import time
import json


def print_btc(timer, inv):
    converter = CurrencyConverter()
    print("BTC to USD rates", end="\n")
    while True:
        wtf = json.loads(converter.convert(1, "BTC", "USD"))
        print("{}: {}".format(strftime("%Y-%m-%d %H:%M:%S", gmtime()), wtf["output"]["USD"]), end="\n")
        time.sleep(inv)
        if timer < 0:
            return
        timer = timer - inv


print_btc(600, 30)

```
**Output:**
```
BTC to USD rates
2018-03-10 22:42:00: 8866.7125
2018-03-10 22:42:31: 8852.5413
2018-03-10 22:43:01: 8852.5413
2018-03-10 22:43:31: 8852.5413
2018-03-10 22:44:01: 8849.7563
2018-03-10 22:44:32: 8848.0263
2018-03-10 22:45:02: 8848.0263
2018-03-10 22:45:32: 8848.0263
2018-03-10 22:46:02: 8853.9138
2018-03-10 22:46:33: 8840.2663
2018-03-10 22:47:03: 8840.2663
2018-03-10 22:47:33: 8826.7575
2018-03-10 22:48:03: 8826.7575
2018-03-10 22:48:33: 8819.42
2018-03-10 22:49:03: 8819.42
2018-03-10 22:49:34: 8819.42
2018-03-10 22:50:04: 8820.415
2018-03-10 22:50:34: 8826.2525
2018-03-10 22:51:04: 8826.2525
2018-03-10 22:51:34: 8826.2525
2018-03-10 22:52:04: 8825.4288
2018-03-10 22:52:35: 8826.9013

```

## Web API
```
using Flask webdevelopment framework:
https://github.com/pallets/flask

get flask:
% pip3 install flask

usage:
% python3 cc_api.py
% GET "http://[HOST]:5000/currency_converter?amount=[AMOUNT]&input_currency=[CURRENCY]"
% GET "http://[HOST]:5000/currency_converter?amount=[AMOUNT]&input_currency=[CURRENCY]&output_currency=[CURRENCY]"

[AMOUNT] - defaults to 1, if not present
[CURRENCY] - currency symbol or 3 letter code
```

## Symbols and Currencies
```
List of known currencies:

CODE   SYMBOL   CURRENCY

'AUD'  [A$]  - Australian dollar
'BRL'  [R$]  - Brazilian real
'BTC'  [Ƀ]   - BitCoin
'CAD'  [C$]  - Canadian dollar
'CHF'  [Fr.] - Swiss franc
'CNY'  [¥]   - Chinese/Yuan renminbi
'CZK'  [Kč]  - Czech koruna
'DKK'  [Kr.] - Danish krone
'EUR'  [€]   - European Euro
'GBP'  [£]   - British pound
'HKD'  [HK$] - Hong Kong dollar
'HRK'  [kn]  - Croatian kuna
'HUF'  [Ft]  - Hungarian forint
'IDR'  [Rp]  - Indonesian rupiah
'ILS'  [₪]   - Israeli new sheqel
'INR'  [₹]   - Indian rupee
'ISK'  [Ikr] - Icelandic króna
'JPY'  [JP¥] - Japanese yen
'KRW'  [₩]   - South Korean won
'MXN'  [M$]  - Mexican peso
'MYR'  [RM]  - Malaysian ringgit
'NOK'  [kr]  - Norwegian krone
'NZD'  [NZ$] - New Zealand dollar
'PHP'  [₱]   - Philippine peso
'PLN'  [zł]  - Polish zloty
'RON'  [L]   - Romanian leu
'RUB'  [₽]   - Russian ruble
'SEK'  [Skr] - Swedish krona
'SGD'  [S$]  - Singapore dollar
'THB'  [฿]   - Thai baht
'TRY'  [₺]   - Turkish new lira
'USD'  [$]   - United States dollar
'ZAR'  [R]   - South African rand


```
