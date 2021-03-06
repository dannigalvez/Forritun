#include "RadadurListi.h"

RadadurListi::RadadurListi() {
    this->head = nullptr;
}

void RadadurListi::setjaILista(Gogn gogn) {
    this->setjaILista(gogn.getID(), gogn.getNumer());
}

void RadadurListi::setjaILista(int id, int numer) {
    if(this->erILista(id)) return;
    if(this->head == nullptr) {
        this->head = new GognNode(id, numer);
    } else {
        GognNode* nyttStak = new GognNode(id, numer);
        if(nyttStak->data < this->head->data) {
            nyttStak->next = this->head;
            this->head = nyttStak;
        } else {
            GognNode* current = this->head;
            GognNode* prev = this->head;
            while(current && current->data < nyttStak->data) {
                prev = current;
                current = current->next;
            }
            prev->next = nyttStak;
            nyttStak->next = current;
        }
    }
}

// fallið eyðir staki með id úr listanum
void RadadurListi::eydaUrLista(int id) {
    if(!this->erILista(id)) return;
    if(this->head->data.getID() == id) {
        GognNode* newHead = this->head->next;
        delete this->head;
        this->head = newHead;
    } else {
        GognNode* current = this->head;
        GognNode* prev = current;
        while(current && current->data.getID() != id) {
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        delete current;
    }
}

// fallið skilar true ef stak með id er í listanum annars false
bool RadadurListi::erILista(int id) {
    GognNode* current = this->head;
    while(current) {
        if(current->data.getID() == id)
            return true;
        current = current->next;
    }
    return false;
}

// fallið skrifa listann út á skjá
void RadadurListi::prentaLista() {
    GognNode* current = this->head;
    while(current) {
        current->data.prentaGogn();
        current = current->next;
    }
}

// destructorinn eyðir öllum Node-unum úr listanum
RadadurListi::~RadadurListi() {
    GognNode* newHead;
    while(this->head) {
        newHead = this->head->next;
        delete this->head;
        this->head = newHead;
    }
}

// Afritar öll gögnin úr stökunum úr gamliListinn yfir í þennan klasa
RadadurListi::RadadurListi(RadadurListi& gamliListinn) {
    GognNode* old_data = gamliListinn.head;
    
    GognNode* nyttStak = new GognNode(old_data->data.getID(), old_data->data.getNumer());
    this->head = nyttStak;

    GognNode* prev = nyttStak;
    while(old_data->next != nullptr){
        GognNode* nyttStak = new GognNode(old_data->data.getID(), old_data->data.getNumer());
        prev->next = nyttStak;
        prev = nyttStak;

        old_data = old_data->next;
    }
}

int RadadurListi::summa(){
    GognNode* current = this->head;
    int summan = 0;
    while(current != nullptr){
        summan += current->data.getNumer();
        current = current->next;
    }
    return summan;
}

/* Skilar true ef summan af öllum Gogn.numer í þessum 
klasa er minni en summan af öllum Gogn.numer í other */
bool RadadurListi::operator<(RadadurListi& other) {
    return summa() < other.summa();
}

/* Skilar true ef summan af öllum Gogn.numer í þessum 
klasa er stærri en summan af öllum Gogn.numer í other */
bool RadadurListi::operator>(RadadurListi& other) {
    return !(summa() < other.summa());
}

/* Skilar true ef summan af öllum Gogn.numer í þessum 
klasa er minni eða sama sem summan af öllum Gogn.numer í other */
bool RadadurListi::operator<=(RadadurListi& other) {
    return summa() < other.summa() || summa() == other.summa();
}

/* Skilar true ef summan af öllum Gogn.numer í þessum 
klasa er stærri eða sama sem summan af öllum Gogn.numer í other */
bool RadadurListi::operator>=(RadadurListi& other) {
    return summa() > other.summa() || summa() == other.summa();
}

// Skilar true ef fjöldi staka í þessum klasa er sá sami og fjoldi staka í other
bool RadadurListi::operator==(RadadurListi& other) {
    GognNode* currentA = this->head;
    int teljariA = 0, teljariB;
    while(currentA != nullptr){
        teljariA++;
        currentA = currentA->next;
    }

    GognNode* currentB = other.head;
    while(currentB != nullptr){
        teljariB++;
        currentB = currentB->next;
    }

    return teljariA == teljariB; 

}

// Skilar true ef fjöldi staka í þessum klasa er ekki sá sami og fjoldi staka í other
bool RadadurListi::operator!=(RadadurListi& other) {
    return !(this->head == other.head);
}
