from selenium import webdriver
import chromedriver_binary

import time

driver = webdriver.Chrome()
driver.get("http://www.filelist.io/login.php")

inputElement = driver.find_element_by_id("username")
inputElement.send_keys('shantzu2005')

inputElement = driver.find_element_by_id("password")
inputElement.send_keys('netu12')

inputElement.submit() 

#time.sleep(2)
file_result = open('results.csv', 'w')

for i in range(10):
    #driver.get("https://filelist.io/browse.php?page=1")
    time.sleep(2)
    driver.get("https://filelist.io/browse.php?cat=19&page={0}".format(i))

    page_results = driver.find_elements_by_class_name('torrentrow')

    for result in page_results:
        info = result.text.split('\n')
        name = info[0].replace(',', ' ')
        downloads = info[7].replace(',', '')

        file_result.write(name + ',' + str(downloads) + '\n')

file_result.close()

driver.close()
