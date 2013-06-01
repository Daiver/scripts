#include <vector>
#include <string>
using namespace std;
class button;
class dialog;
class button {
      string text;
            float timer;
                  int x,y;
                        public:
                                     int state;
                                                  void Create(string in_text);
                                                               void Render(int in_x,int in_y);
                                                               };
