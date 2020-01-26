#ifndef __DISJSET_HPP
#define __DISJSET_HPP

template <typename T>
struct disjset {
    T v;    
    disjset* p;
    int rank = 0;

    disjset(T v) : v(v) {
        this->p = this;
    }

    disjset* findSet() {
        if(this != this->p) {
            this->p = this->p->findSet();
        }
        return this->p;
    }

    static void unionSet(disjset* s1, disjset* s2){
        disjset *r1 = s1->findSet(), *r2 = s2->findSet();
        if(r1->rank > r2->rank) {
            r2->p = r1;
        } else if( r2->rank > r1->rank) {
            r1->p = r2;
        } else {
            r2->p = r1;
            r1->rank++;
        }
    }
};

#endif