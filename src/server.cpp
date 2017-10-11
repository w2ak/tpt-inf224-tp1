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

class MyBase {
private:
  int id;
  Library lib;
public:
  MyBase(int i) {
    id = i;
    const shared_ptr<Multimedia> pic = lib.addPicture("picture","media/small.jpg",0,0);
    lib.addVideo("video","media/small.mp4",0);
    lib.addGroup("group")->push_back(pic);
  };
  MyBase():MyBase(42) {};
  /* Cette méthode est appelée chaque fois qu'il y a une requête à traiter.
   * Ca doit etre une methode de la classe qui gere les données, afin qu'elle
   * puisse y accéder.
   *
   * Arguments:
   * - 'request' contient la requête
   * - 'response' sert à indiquer la réponse qui sera renvoyée au client
   * - si la fonction renvoie false la connexion est close.
   *
   * Cette fonction peut etre appelée en parallele par plusieurs threads (il y a
   * un thread par client).
   *
   * Pour eviter les problemes de concurrence on peut créer un verrou en creant
   * une variable Lock **dans la pile** qui doit etre en mode WRITE (2e argument = true)
   * si la fonction modifie les donnees.
   */
  bool processRequest(TCPConnection& cnx, const string& request, string& response)
  {
    int ok = 0;
    string help = "<fileInfo|groupInfo|play> <media-name>";
    stringstream resp;
    stringstream rqst;
    rqst.str(request);

    cerr << "\nRequest: '" << rqst.str() << "'" << endl;

    // 1) pour decouper la requête:
    // on peut par exemple utiliser stringstream et getline()
    char sep = ' ';
    string cmd;
    string name;

    // Get the two parameters
    if (!rqst.rdbuf()->in_avail()) { resp << help; ok = 2; goto done; }
    getline(rqst,cmd,sep);
    if (!rqst.rdbuf()->in_avail()) { resp << help; ok = 2; goto done; }
    getline(rqst,name,sep);
    if (rqst.rdbuf()->in_avail()) { resp << help; ok = 2; goto done; }

    // 2) faire le traitement:
    // - si le traitement modifie les donnees inclure: TCPLock lock(cnx, true);
    // - sinon juste: TCPLock lock(cnx);
    if (cmd == "fileInfo") {
      TCPLock lock(cnx);
      if (lib.hasFile(name)) {
        lib.fileInfo(name,resp);
      } else {
        ok = 1; resp << "Not Found";
      }
      goto done;
    }
    if (cmd == "groupInfo") {
      TCPLock lock(cnx);
      if (lib.hasGroup(name)) {
        lib.groupInfo(name,resp);
      } else {
        ok = 1; resp << "Not Found";
      }
      goto done;
    }
    if (cmd == "play") {
      TCPLock lock(cnx);
      if (lib.hasFile(name)) {
        resp << "Now playing: ";
        lib.fileInfo(name,resp);
        lib.open(name);
      } else {
        ok = 1; resp << "Not Found";
      }
      goto done;
    }
    resp << help; ok = 2; goto done;


    // 3) retourner la reponse au client:
done:
    switch (ok) {
      case 0:
        response = "OK: "; break;
      case 1:
        response = "KO: "; break;
      case 2:
        response = "??: "; break;
      default:
        response = "ShouldNotHappen "; break;
    }

    response+=resp.str();

    replace(response.begin(),response.end(),'\n',';');

    cerr << "response: " << response << endl;

    // renvoyer false si on veut clore la connexion avec le client
    return true;
  }
};


int main(int argc, char* argv[])
{
  // cree le TCPServer
  shared_ptr<TCPServer> server(new TCPServer());

  // cree l'objet qui gère les données
  shared_ptr<MyBase> base(new MyBase(PORT));

  // le serveur appelera cette méthode chaque fois qu'il y a une requête
  server->setCallback(*base, &MyBase::processRequest);

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
