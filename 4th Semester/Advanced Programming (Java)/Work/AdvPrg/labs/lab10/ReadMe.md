- Lab Status

    - Compulsory - ![](https://us-central1-progress-markdown.cloudfunctions.net/progress/100)
      - https://github.com/BobuDragos/AdvPrg/tree/main/labs/lab10/compulsory
    - Homework - ![](https://us-central1-progress-markdown.cloudfunctions.net/progress/100)
      - https://github.com/BobuDragos/AdvPrg/tree/main/labs/lab10/homework
    - Bonus - ![](https://us-central1-progress-markdown.cloudfunctions.net/progress/0)
      - 

## Problem description

**Networking**

Create an application where clients connect to a server in order to form a social network. The application will contain two parts (create a project for each one):

* The server is responsible with the management of the clients and the implementation of the services.
* The client will communicate with the server, sending it commands containing the name of the service and the required parameters. The commands are:
  - register name: adds a new person to the social network;
  - login name: establishes a connection between the server and the client;
  - friend name1 name2 ... namek: adds friendship relations between the person that sends the command and other persons;
  - send message: sends a message to all friends.
  - read: reads the messages from the server.
