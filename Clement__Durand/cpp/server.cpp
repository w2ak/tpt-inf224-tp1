//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "tcpserver.h"
#include "library.h"
using namespace std;
using namespace cppu;

const int PORT = 3331;

int main(int argc, char* argv[])
{
  // cree le TCPServer
  shared_ptr<TCPServer> server(new TCPServer());

  // cree l'objet qui gère les données
  shared_ptr<Library> base(new Library());

  const shared_ptr<Multimedia> pic = base->addPicture("picture","media/small.jpg",0,0);
  base->addVideo("video","media/small.mp4",0);
  base->addGroup("group")->push_back(pic);

  // le serveur appelera cette méthode chaque fois qu'il y a une requête
  server->setCallback(*base, &Library::processRequest);

  // lance la boucle infinie du serveur
  cout << "Starting Server on port " << PORT << endl;
  int status = server->run(PORT);

  // en cas d'erreur
  if (status < 0) {
    cerr << "Could not start Server on port " << PORT << endl;
    return 1;
  }

  return 0;
}
