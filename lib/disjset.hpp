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

template <typename T>
struct ldisjset
{
    T x;
    int n = 1;
    ldisjset *next = nullptr, *prev = this, *r;

    ldisjset(T x) : x(x) {
        r = this;
    }

    void merge(ldisjset* m) {
        ldisjset *last = this->r->prev, *firstm = m->r;

        last->next = firstm;
        firstm->prev = last;
        this->r->n += firstm->n;

        while(firstm != NULL) {
            firstm->r = this->r;
            if(firstm->next == NULL) this->r->prev = firstm;
            firstm = firstm->next;
        }
    } 

    static void union_set(ldisjset* s1, ldisjset* s2) {
        if(s1->r->n > s2->r->n) s1->merge(s2);
        else s2->merge(s1);
    }
};

#endif