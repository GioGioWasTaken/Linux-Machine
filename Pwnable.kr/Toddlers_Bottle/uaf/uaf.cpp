#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
using namespace std;

class Human {
private:
  virtual void give_shell() { system("/bin/sh"); }

protected:
  int age;
  string name;

public:
  virtual void introduce() {
    cout << "My name is " << name << endl;
    cout << "I am " << age << " years old" << endl;
  }
};

class Man : public Human {
public:
  Man(string name, int age) {
    this->name = name;
    this->age = age;
  }
  virtual void introduce() {
    Human::introduce();
    cout << "I am a nice guy!" << endl;
  }
};

class Woman : public Human {
public:
  Woman(string name, int age) {
    this->name = name;
    this->age = age;
  }
  virtual void introduce() {
    Human::introduce();
    cout << "I am a cute girl!" << endl;
  }
};

int main(int argc, char *argv[]) {
  Human *m = new Man("Jack", 25);
  Human *w = new Woman("Jill", 21);

  size_t len;
  char *data;
  unsigned int op;
  while (1) {
    cout << "1. use\n2. after\n3. free\n";
    cin >> op;

    switch (op) {
    case 1:
      m->introduce(); // essentially just a calculation of a memory address.
                      // Equivalent to: [m(m is a pointer) + offset of
                      // introduce]
      w->introduce();
      // I need a memory address, s.t. the offset of introduce from that memory
      // address, is the give_shell function.
      break;
    case 2:
      len = atoi(argv[1]);
      data = new char[len];
      read(open(argv[2], O_RDONLY), data, len);
      cout << "your data is allocated" << endl;
      break;
    case 3:
      delete m;
      delete w;
      break;
    default:
      break;
    }
  }

  return 0;
}
