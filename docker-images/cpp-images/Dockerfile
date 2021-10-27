FROM python:3.8.0-slim
RUN apt-get -o Acquire::Max-FutureTime=86400 update \
&& apt-get install g++ -y \
&& apt-get clean