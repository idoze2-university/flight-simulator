import xml.etree.ElementTree as ET
output = ET.parse(
    'Project_Data/generic_small.xml').getroot().find('generic/output')
nodes = list(n.text for n in output.findall('chunk/node'))

i = 0
for n in nodes:
    print 'names[%d] = \"%s\";' % (i, n)
    i = i+1
