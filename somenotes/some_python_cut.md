# cli short cut
python -mjson.tool  --make json format data human readable.
python -m SimpleHTTPServer port   -- share a folder with local ip:port

# clean enviroment, need install virtualenv
#  py27
virtualenv venv_name
# OR
virtualenv2 venv_name
source venv_name/bin/activate
#  py38
python -m venv python3_venv
#

# selenium  use webdriver, Keys
driver.Chrome(), Firefox()
d.get(url)
d.find_element_by id, xpath, class_name, link_text()
d.find..element..().send_keys(xxx) , could be string or KEYS.enter From KEYBORAD.
d.quit()
