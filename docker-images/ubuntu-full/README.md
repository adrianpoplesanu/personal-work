Docker build image command:

docker build --tag=ubuntu-full-image:20.04 .

Once it's running try this:

docker ps
# nginx-test e numele containerului care ruleaza deja
docker exec –it nginx-test /bin/bash
