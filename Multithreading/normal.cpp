#include <bits/stdc++.h>
using namespace std;

struct Tree {
    int childLockedCount;
    vector<Tree*> lockedDescendants;
    map<int, int> mpp;
    string name;
    int id;
    Tree* parent;
    vector<Tree*> child;
    bool isLocked;

    Tree(string s) {
        this->name = s;
        this->childLockedCount = 0;
        this->parent = nullptr;
        this->isLocked = false;
    }
};

unordered_map<string, Tree*> storee;

bool parentlock(Tree* node) {
    Tree* curr = node->parent;
    while (curr) {
        if (curr->isLocked) return true;
        curr = curr->parent;
    }
    return false;
}

void addChildLock(Tree* node, int val, int id) {
    Tree* curr = node->parent;
    while (curr) {
        curr->childLockedCount += val;
        if (val == 1)
            curr->mpp[id]++;
        else {
            curr->mpp[id]--;
            if (curr->mpp[id] == 0) curr->mpp.erase(id);
        }
        if (val == 1)
            curr->lockedDescendants.push_back(node);
        else {
            // Remove from lockedDescendants
            auto& vec = curr->lockedDescendants;
            vec.erase(remove(vec.begin(), vec.end(), node), vec.end());
        }
        curr = curr->parent;
    }
}

bool lock(Tree* node, int id) {
    if (node->isLocked || parentlock(node) || node->childLockedCount > 0) return false;
    node->id = id;
    node->isLocked = true;
    addChildLock(node, 1, id);
    return true;
}

bool unlock(Tree* node, int id) {
    if (!node->isLocked) return false;
    if (node->id != id) return false;
    node->isLocked = false;
    addChildLock(node, -1, id);
    return true;
}

void unlockDescendants(Tree* node, int id) {
    vector<Tree*> toUnlock = node->lockedDescendants;
    for (auto it : toUnlock) {
        if (it->isLocked && it->id == id) {
            it->isLocked = false;
            addChildLock(it, -1, id);
        }
    }
}

bool upgrade(Tree* node, int id) {
    if (node->isLocked || parentlock(node)) return false;
    if (node->mpp.size() != 1) return false;
    if (node->mpp.begin()->first != id) return false;
    unlockDescendants(node, id);
    node->id = id;
    node->isLocked = true;
    addChildLock(node, 1, id);
    return true;
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<string> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        Tree* node = new Tree(arr[i]);
        storee[arr[i]] = node;
    }

    for (int i = 0; i < n; i++) {
        if (i * m + 1 < n) {
            for (int j = 1; j <= m; j++) {
                if (i * m + j >= n) break;
                Tree* parent = storee[arr[i]];
                Tree* child = storee[arr[i * m + j]];
                child->parent = parent;
                parent->child.push_back(child);
            }
        }
    }

    while (q--) {
        int a, id;
        string s;
        cin >> a >> s >> id;
        Tree* node = storee[s];
        if (a == 1)
            cout << (lock(node, id) ? "true" : "false") << endl;
        else if (a == 2)
            cout << (unlock(node, id) ? "true" : "false") << endl;
        else
            cout << (upgrade(node, id) ? "true" : "false") << endl;
    }

    return 0;
}
