#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
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

void Library::unparse(ostream& s) const {
  char sep = ';';
  for (auto it: files) {
    s << it.first << sep;
    it.second->unparse(s);
    s << endl;
  }
  for (auto it: groups) {
    s << it.first << sep;
    it.second->unparse(s);
    s << endl;
  }
}

void Library::save(const string& filename) const {
  ofstream file;
  file.open(filename);
  if (file) unparse(file);
  file.close();
}

void Library::parse(istream& s) {
  string lin,key,cls;
  stringstream buf;
  char sep = ';';
  getline(s,lin);
  while (!lin.empty()) {
    buf.str(lin);
    getline(buf,key,sep);
    getline(buf,cls,sep);
    if (cls == "Group") {
      if (!hasGroup(key)) {
        shared_ptr<Group<Multimedia>> obj(new Group<Multimedia>(key));
        obj->parse(buf,[this](const string& k) { return this->getFile(k); });
        groups[key] = obj;
      }
    } else if (!hasFile(key)) {
      shared_ptr<Multimedia> obj;
      if (cls == "Picture") obj = shared_ptr<Multimedia>(new Picture(key));
      if (cls == "Video") obj = shared_ptr<Multimedia>(new Video(key));
      if (cls == "Movie") obj = shared_ptr<Multimedia>(new Movie(key));
      if (obj) {
        obj->parse(buf);
        files[key] = obj;
      }
    }
    getline(s,lin);
  }
}

void Library::load(const string& filename) {
  ifstream file;
  file.open(filename);
  if (file) parse(file);
  file.close();
}
