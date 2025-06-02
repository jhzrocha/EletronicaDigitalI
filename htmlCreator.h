#ifndef HTMLCREATOR_H
#define HTMLCREATOR_H

#include <pgmspace.h>

class HTMLCreator {
  public:
    const char* getHTMLPage();
  
  private:
    static const char index_html[];  // apenas a declaração
};

#endif
