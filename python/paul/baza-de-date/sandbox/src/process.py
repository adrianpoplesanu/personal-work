import json

filename = open('files/AutomatBun-Copy.js', 'r')
data = filename.read()

data = data.replace('var informatii = {', '{')
data = data.replace('contor:', "'contor':")
data = data.replace('cod:', "'cod':")
data = data.replace('numepr:', "'numepr':")
data = data.replace('prenume:', "'prenume':")
data = data.replace('numeFata:', "'numeFata':")
data = data.replace('nume:', "'nume':")
data = data.replace('cale:', "'cale':")
data = data.replace('zzn:', "'zzn':")
data = data.replace('lln:', "'lln':")
data = data.replace('ann:', "'ann':")
data = data.replace('datan:', "'datan':")
data = data.replace('datan2:', "'datan2':")
data = data.replace('datad:', "'datad':")
data = data.replace('varsta:', "'varsta':")
data = data.replace('zodie:', "'zodie':")
data = data.replace('codsot:', "'codsot':")
data = data.replace('codtata:', "'codtata':")
data = data.replace(', tata:', ", 'tata':")
data = data.replace('codmama:', "'codmama':")
data = data.replace(', mama:', ", 'mama':")
data = data.replace('codcopil1:', "'codcopil1':")
data = data.replace('copil1:', "'copil1':")
data = data.replace('codcopil2:', "'codcopil2':")
data = data.replace('copil2:', "'copil2':")
data = data.replace('codcopil3:', "'codcopil3':")
data = data.replace('copil3:', "'copil3':")
data = data.replace('codcopil4:', "'codcopil4':")
data = data.replace('copil4:', "'copil4':")
data = data.replace('codcopil5:', "'codcopil5':")
data = data.replace('copil5:', "'copil5':")
data = data.replace('codcopil6:', "'codcopil6':")
data = data.replace('copil6:', "'copil6':")
data = data.replace('codcopil7:', "'codcopil7':")
data = data.replace('copil7:', "'copil7':")
data = data.replace('codcopil8:', "'codcopil8':")
data = data.replace('copil8:', "'copil8':")
data = data.replace('codcopil9:', "'codcopil9':")
data = data.replace('copil9:', "'copil9':")
data = data.replace('tatanum:', "'tatanum':")
data = data.replace('mamanum:', "'mamanum':")
data = data.replace('sotnum:', "'sotnum':")
data = data.replace('sot:', "'sot':")
data = data.replace('copilnum1:', "'copilnum1':")
data = data.replace('copilnum2:', "'copilnum2':")
data = data.replace('copilnum3:', "'copilnum3':")
data = data.replace('copilnum4:', "'copilnum4':")
data = data.replace('copilnum5:', "'copilnum5':")
data = data.replace('copilnum6:', "'copilnum6':")
data = data.replace('copilnum7:', "'copilnum7':")
data = data.replace('copilnum8:', "'copilnum8':")
data = data.replace('copilnum9:', "'copilnum9':")
data = data.replace('obs:', "'obs':")
data = data.replace('numepoza:', "'numepoza':")
data = data.replace('poza:', "'poza':")

data = data.replace("'", '"')
data = data.replace("""},

}""", """}

}""")

#print (data)

data = json.loads(data)
print(data)


'''
'006': {'contor': '006', cod: '6',
numepr: 'Stefan Ioan', nume: 'Stefan', prenume: 'Ioan',
numeFata: 'Stefan',
cale: '../../HTML_Fam/images/',
zzn: '2', lln: '23', ann: '1929', datan: '23/2/1929', datan2: '23.feb.1929', datad: '22.iun.1997',
varsta: '68ani,3luni,30zile', zodie: 'Pesti',
codsot: '005', sot: 'Stefan_Ecaterina',
codtata: '021', tata: 'Stefan_Marin',
codmama: '022', mama: 'Stefan_Maria',
codcopil1: '032', copil1: 'Stefan_Paul',
codcopil2: '008', copil2: 'Stefan_Razvan',
codcopil3: '009', copil3: 'Stefan_Catalin',
codcopil4: '0', copil4: '.',
codcopil5: '0', copil5: '.',
codcopil6: '0', copil6: '.', codcopil7: '0', copil7: '.', codcopil8: '0', copil8: '.', codcopil9: '0', copil9: '.',
tatanum: 'tata:Sefan Marin n:29.sep.1907, Cobia-d:15.ian.1982, Sighisoara',
mamanum: 'mama:Stefan (Irimie) Maria n:2.apr.1911, Sighisoara-d:29.dec.1989, Sighisoara',
sotnum: 'sot/ie:Stefan (Wandelic) Ecaterina - Paula n:13.oct.1935, Bucuresti-d:3.apr.2017, Bucuresti',
copilnum1: 'copil:Stefan Paul n:2.mai.1955, Bucuresti ',
copilnum2: 'copil:Stefan Razvan n:2.oct.1962, Bucuresti',
copilnum3: 'copil:Stefan Catalin n:13.iun.1968, Bucuresti',
copilnum4: 'copil:',
copilnum5: 'copil:',
copilnum6: 'copil:', copilnum7: 'copil:', copilnum8: 'copil:', copilnum9: 'copil:',
obs: 'Stefan_Ioan_Obs()',
poza: '006_Stefan_Ioan.jpg',
numepoza: '006_Stefan_Ioan'},
'''
