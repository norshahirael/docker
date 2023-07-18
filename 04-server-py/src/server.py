import socket
import mysql.connector
import time

def Main():
  host = "172.18.0.6"
  port = 8779

  mydb = mysql.connector.connect(host = "172.17.0.1", port =30000, user = "ira", password = "ira", database = "sir_db")
  mycursor = mydb.cursor()
  mycursor.execute("SELECT * FROM mytable")
  myresult = mycursor.fetchall()

  for x in myresult:
    print(x)
    time.sleep(1)

  mySocket = socket.socket()
  mySocket.connect(("172.18.0.5",300001))

  message = input(" - ")

  while message != 'q':
    mySocket.send(message.encode())
    data = mySocket.recv(1024).decode()

    print ('Received from server' + data)

    message = input (" - ")
 
  mySocket.close()


if __name__ == '__main__':
  Main()
