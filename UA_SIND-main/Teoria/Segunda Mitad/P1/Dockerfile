FROM ubuntu:latest

# P1: Install Ubuntu with MySQL Server and Apache2 Server.
RUN apt -y update

RUN apt -y install mysql-server
RUN apt -y install apache2

CMD /usr/sbin/apache2ctl -D FOREGROUND