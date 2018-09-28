#ifndef ELEMENT_H
#define ELEMENT_H

enum status {frei, inBearbeitung};

class Element
{
public:
      Element(char *string);
      char *getName(void) { return name; }
      void addTag(char * string);
      void addAttribute(char * string);
      int getAnzahlTags() { return zahl; }
      char *getTagName(int slot) { return tags[slot]; }
      void druckeElement(int ebene,Element *wurzel);
      Element *getNext(void) { return naechstes; }
      void setNext(Element *neu) { naechstes = neu; }
      Element *sucheElement(char *suche,Element *element);
      int elementIstErlaubt(char *name);
      int attributeIstErlaubt(char *name);
      char tags[10][64];
   private:
      int zahl;
      char name[64];

      Element *naechstes;
      enum status status;
      int zahlAttribute;
      char attributes[10][64];
};

#endif // ELEMENT_H
