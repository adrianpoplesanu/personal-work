import requests
import json

#print('testing match-day connection...')

response = requests.get(url='https://api.football-data.org/v2/competitions', headers={"X-Auth-Token": "f5c1f45ccb174b739541ad43203c7183"})

#response = requests.get(url='https://api.football-data.org/v2/competitions/EC/matches', headers={"X-Auth-Token": "f5c1f45ccb174b739541ad43203c7183"})

data = json.loads(response.text)

for competition in data['competitions']:
    if competition["plan"] == "TIER_ONE":
        print (competition)
