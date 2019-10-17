import xml.etree.ElementTree as ET
tree = ET.parse('NewOrder.xml')
root = tree.getroot()

print 'request = {}'

new_order_element = root.find('NewOrder')
for xml_element in new_order_element:
    if xml_element.text:
        print 'request["' + xml_element.tag + '"] = "' + xml_element.text + '"'

