"""
Hosting Controller Translation Bot (HCTB) v0.1
    @author Andrej Dravecky
    
following python3 modules requied:
    Splinter
    BeautifulSoup
    Googletrans*

usage:
    set username, password and translation
    language** in proper variables inside this file

    % python3 hctb.py

*translation powered by Google translate API
**for supported languages and their codes visit https://cloud.google.com/translate/docs/languages

"""

#====== CONFIGURATION ======#

username = ''
password = ''
translation_language = ''

#===========================#

from splinter import Browser
from bs4 import BeautifulSoup
from googletrans import Translator

with Browser('firefox') as b:
    b.visit('http://hc10translation.hostingcontroller.com')
    
    b.fill('textboxUserName', username)
    b.fill('textboxPassword', password)
    b.find_by_name('Button_Login').first.click()
    
    b.find_by_id('ctl00_ContentPlaceHolder2_GridViewMylanguages_ctl08_LinkButtontranslate').first.click()

    t = Translator()
    while True:
        table = b.find_by_id('ctl00_ContentPlaceHolder2_GridViewTranslations')[0].find_by_tag('td')
        boxes = b.find_by_css('.TextBox')
        
        for count in range(len(boxes)):
            box_name = BeautifulSoup(boxes[count].outer_html, 'lxml').input.attrs['name']
            trans_input = t.translate(table[count*2].text, dest=translation_language).text
            b.fill(box_name, trans_input)

        input('Is page valid? [press ENTER to continue]')
        b.find_by_value('Save & Continue').first.click()