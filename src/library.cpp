#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "tcpserver.h"
#include "library.h"
using namespace std;
using namespace cppu;

bool Library::processRequest(TCPConnection& cnx, const string& request, string& response)
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
    if (hasFile(name)) {
      fileInfo(name,resp);
    } else {
      ok = 1; resp << "Not Found";
    }
    goto done;
  }
  if (cmd == "groupInfo") {
    TCPLock lock(cnx);
    if (hasGroup(name)) {
      groupInfo(name,resp);
    } else {
      ok = 1; resp << "Not Found";
    }
    goto done;
  }
  if (cmd == "play") {
    TCPLock lock(cnx);
    if (hasFile(name)) {
      resp << "Now playing: ";
      fileInfo(name,resp);
      open(name);
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
