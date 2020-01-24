#include <iostream>
#include <vector>
#include <algorithm>

struct letter{
    char l;
    int s = 0, e = 0, color = 0;
    std::vector<letter*> next;
    letter(char l) : l(l) {}

    void add(letter* n) {
        next.push_back(n);
    }
};

bool alpha_dfs_visit(const std::vector<letter*>& lts, int& time, letter* l) {
    l->s = ++time;
    l->color = 1;
    bool res = true;
    
    for(int j = 0; j<l->next.size() && res; ++j) {
        if(l->next[j]->e == 0 && l->next[j]->s != 0) res = false;
        else if(l->next[j]->color == 0) {
            res = res && alpha_dfs_visit(lts, time, l->next[j]);
        }
    }
    l->e = ++time;
    l->color = 2;
    return res;
}

bool alpha_dfs(const std::vector<letter*>& lts) {
    bool res = true;
    int time = 0;
    for(int i = lts.size()-1; i>=0; --i) {
        if(lts[i]->color == 0) {
            res = res && alpha_dfs_visit(lts, time, lts[i]);
        }
    }

    return res;
}

std::string alphabet(const std::vector<std::string>& sts) {
    std::vector<letter*> lts;
    for(int i = 0; i<26; ++i) lts.push_back(new letter((char)('a' + i)));

    bool valid = true; 
    for(int i=0; i<sts.size() - 1 && valid; ++i) {
        bool et = true;
        for(int j = 0; j<sts[i].length() && j < sts[i+1].length() && et; ++j) {
            if(sts[i][j] != sts[i+1][j]) {
                lts[(int)(sts[i][j] - 'a')]->add(lts[(int)(sts[i+1][j] - 'a')]);
                et = false;
            } 
        }
        if(et && sts[i].length() > sts[i+1].length()) valid = false;
    }

    if(alpha_dfs(lts) && valid) {
        std::sort(lts.begin(), lts.end(), [](letter* l1, letter* l2) {
            return l1->e > l2->e;
        });
        std::string res;
        for(int i = 0; i<lts.size(); ++i) res.push_back(lts[i]->l);
        return res;
    }
    else return "Impossible";

}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<std::string> sts;
    for(int i = 0; i<n; ++i) {
        std::string s;
        std::cin >> s;
        sts.push_back(s);
    }

    std::string res = alphabet(sts);
    std::cout << res << std::endl;
}
