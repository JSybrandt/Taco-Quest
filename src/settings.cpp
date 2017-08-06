#include"settings.h"

Settings::Settings(string path){
  if(!fileExists(path)){
    writeDefaultSettings(path);
  }
  fstream fin(path, ios::in);
  map<string, string> values;
  string key, val;
  while(fin >> key >> val){
    values[key] = val;
  }
  fin.close();

  this->up = str2key(values[SK::UP]);
  this->down = str2key(values[SK::DOWN]);
  this->left = str2key(values[SK::LEFT]);
  this->right = str2key(values[SK::RIGHT]);
  this->shoot = str2key(values[SK::SHOOT]);
}

bool Settings::fileExists(string path){
  fstream in(path, ios::in);
  return in.good();
}

void Settings::writeDefaultSettings(string path){
  fstream fout(path, ios::out);
  fout << SK::UP    <<"\t"<< "W" << endl;
  fout << SK::LEFT  <<"\t"<< "A" << endl;
  fout << SK::DOWN  <<"\t"<< "S" << endl;
  fout << SK::RIGHT <<"\t"<< "D" << endl;
  fout << SK::SHOOT <<"\t"<< "SPACE" << endl;
}

Keyboard::Key Settings::str2key(string str){
  if(str.length() == 1){
    char c = str[0];
    c = toupper(c);
    if(c >= 'A' && c <= 'Z'){
      return (Keyboard::Key) (c-'A');
    }
  } else if(str == "SPACE"){
    return Keyboard::Key::Space;
  }
  cerr << "INVALID SETTINGS FILE" << endl;
  return Keyboard::Key::Unknown;
}
