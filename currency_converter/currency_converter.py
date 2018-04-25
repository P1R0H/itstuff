"""
Currency Converter CLI
python3.5

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


created by Andrej Dravecky
7. 4. 2018

"""

import argparse
import json
from forex_python.converter import CurrencyRates, CurrencyCodes, RatesNotAvailableError
from forex_python.bitcoin import BtcConverter


class CurrencyConverter:
    """
    CurrencyConverter class

    :raises ValueError in case when input currency is None or not recognized
    :raises RatesNotAvailableError from forex-python module

    """

    def __init__(self):
        # Dictionary of symbols and matching currencies, conflicting values use alternative symbols
        self.__dict = {
            "$"  : "USD",
            "kr" : "NOK",
            "¥"  : "CNY",
            "₪"  : "ILS",
            "₹"  : "INR",
            "R$" : "BRL",
            "Kr.": "DKK",
            "₺"  : "TRY",
            "L"  : "RON",
            "zł" : "PLN",
            "฿"  : "THB",
            "Kč" : "CZK",
            "RM" : "MYR",
            "Fr.": "CHF",
            "€"  : "EUR",
            "S$" : "SGD",
            "R"  : "ZAR",
            "£"  : "GBP",
            "₽"  : "RUB",
            "Rp" : "IDR",
            "₩"  : "KRW",
            "kn" : "HRK",
            "Ft" : "HUF",
            "₱"  : "PHP",
            "Ƀ"  : "BTC",

            # alternative symbols

            "A$" : "AUD",
            "M$" : "MXN",
            "C$" : "CAD",
            "NZ$": "NZD",
            "HK$": "HKD",
            "JP¥": "JPY",
            "Ikr": "ISK",
            "Skr": "SEK"

        }

    def print_known_currencies(self):
        """
        currency information print

        """

        rev_dict = {v: k for k, v in self.__dict.items()}

        print("List of known currencies:", end="\n\n")
        print("CODE   SYMBOL   CURRENCY", end="\n\n")

        c = CurrencyCodes()
        for code in sorted(self.__dict.values()):
            of = " " * (4 - len(rev_dict[code]))
            print("'{}'  [{}]".format(code, rev_dict[code]), end=of)
            if code == "BTC":
                print("- BitCoin", end="\n")
                continue
            print("- {}".format(c.get_currency_name(code)), end="\n")

    def __get_currency(self, arg):
        if arg is None:
            return None
        if arg in self.__dict.values():
            return arg
        if arg in self.__dict.keys():
            return self.__dict[arg]
        raise ValueError("Currency '{}' not recognized".format(arg))

    def __build_output(self, amount, inc, outc):
        if inc == "BTC":
            # BTC input handling
            if outc is not None:
                return {outc: BtcConverter().convert_btc_to_cur(amount, outc)}

            # BitCoin conversion uses USD rates, amount is changed accordingly
            amount = BtcConverter().convert_btc_to_cur(amount, "USD")
            out_data = CurrencyRates().get_rates("USD")
            out_data["USD"] = 1.0
        else:
            # classic input handling + add BTC
            out_data = CurrencyRates().get_rates(inc)
            out_data["BTC"] = BtcConverter().convert_to_btc(1, inc)

            if outc is not None:
                out_data = {outc: out_data[outc]}

        # recalculate money amount against all rates (round to 5 places after floating point)
        for key in out_data.keys():
            out_data[key] = round(out_data[key] * amount, 5)

        return out_data

    def convert(self, amount, incurr, outcurr = None):
        """
        handles currency conversion and JSON structure construction

        :param amount:  amount of money to be converted
        :param incurr:  input currency symbol or 3 letter code
        :param outcurr:  output currency symbol or 3 letter code, defaults to None -> pick all currencies

        :return: JSON structured data as JSON dump string

        """

        # check codes and get codes from symbols
        input_currency = self.__get_currency(incurr)
        if input_currency is None:
            raise ValueError("incurr cannot be None")
        output_currency = self.__get_currency(outcurr)

        # creating structured data for JSON structure
        in_data = {"amount": amount, "currency": input_currency}
        out_data = self.__build_output(amount, input_currency, output_currency)

        return json.dumps({"input": in_data, "output": out_data}, sort_keys=True, indent=4)


def prepare_parser():
    """
    prepares argument parser for main function

    :return: parser as ArgumentParser object

    """

    parser = argparse.ArgumentParser()

    parser.add_argument("-i", "--info", dest="info", const=True, default=False,
                        nargs='?', help="prints out known currencies")
    parser.add_argument("--amount", type=float, default=1.0, dest="amount",
                        help="amount of input currency to be converted, 1.0 if not present")
    parser.add_argument("--output_currency", dest="out_curr",
                        help="output currency symbol or code, all known currencies if not present")
    parser.add_argument("--input_currency", type=str, dest="in_curr",
                        help="output currency symbol or code")
    parser.add_argument("--file", type=str, dest="path", help="output file path")

    return parser


def main():
    """
    main function calls parser, calls CurrencyConverter class methods and handles output

    """

    try:
        args = prepare_parser().parse_args()

        if args.info:
            CurrencyConverter().print_known_currencies()
        else:
            json_dump = CurrencyConverter().convert(args.amount, args.in_curr, args.out_curr)
            open(args.path, 'w').write(json_dump) if args.path is not None else print(json_dump)

    # catching unrecognized currency exception
    except ValueError as v:
        print(v)

    # catching RateNotAvailable if Forex cannot get rates for whatever reason
    except RatesNotAvailableError as r:
        print(r)


if __name__ == "__main__":
    main()
