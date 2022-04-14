import requests
import json

#print('testing match-day connection...')

#response = requests.get(url='https://api.football-data.org/v2/competitions', headers={"X-Auth-Token": "f5c1f45ccb174b739541ad43203c7183"})

#response = requests.get(url='https://api.football-data.org/v2/competitions/ENG/matches', headers={"X-Auth-Token": "f5c1f45ccb174b739541ad43203c7183"})
response = requests.get(url='https://api.football-data.org/v2/competitions/PL/matches', headers={"X-Auth-Token": "f5c1f45ccb174b739541ad43203c7183"})

data = json.loads(response.text)

#print(data.keys())

#for competition in data['competitions']:
#    if competition["plan"] == "TIER_ONE":
#        print (competition)

matches = data['matches']

for match in matches:
    if match['status'] == 'FINISHED':
        print (match['homeTeam']['name'] + " " + str(match['score']['fullTime']['homeTeam']) + " - " + str(match['score']['fullTime']['awayTeam']) + " " + match['awayTeam']['name'])
    else:
        print (match['homeTeam']['name'] + " x - x " + match['awayTeam']['name'])
