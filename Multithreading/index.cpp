#include <bits/stdc++.h>
#include <thread>
#include <mutex>
using namespace std;

/*
    Class representing each Tree Node.
    It contains lock status, parent-child links, and tracking info for upgrades.
*/
class Tree {
public:
    string name;                       // Name of the node
    int id;                            // ID of user who locked the node
    Tree* parent;                      // Pointer to parent node
    vector<Tree*> children;           // List of children

    int childLockedCount;             // Count of locked descendants
    map<int, int> mpp;                // Map to track user ID counts in descendants
    vector<Tree*> lockedDescendants;  // List of locked descendant nodes
    bool isLocked;                    // Flag to indicate if node is locked

    mutex mtx;                        // Mutex for thread-safe access

    /*
        Constructor: Initializes values
    */
    Tree(string name) {
        this->name = name;
        this->id = -1;
        this->parent = nullptr;
        this->childLockedCount = 0;
        this->isLocked = false;
    }
};

/*
    Class to manage the locking system across all nodes.
    Provides lock, unlock, and upgrade operations with thread-safety.
*/
class TreeLockingSystem {
private:
    unordered_map<string, Tree*> store;  // Stores node name -> Tree* mapping
    mutex store_mutex;                   // Mutex to protect `store` access

    /*
        Checks if any parent of the given node is locked.
        Traverses up and locks each parent temporarily to check.
    */
    bool parentLocked(Tree* node) {
        Tree* curr = node->parent;
        while (curr) {
            lock_guard<mutex> lock(curr->mtx);
            if (curr->isLocked) return true;
            curr = curr->parent;
        }
        return false;
    }

    /*
        Updates ancestor nodes when a node is locked or unlocked.
        Adds/removes lock info and updates lock count maps and vectors.
    */
    void addChildLock(Tree* node, int delta, int id) {
        Tree* curr = node->parent;
        while (curr) {
            lock_guard<mutex> lock(curr->mtx);
            curr->childLockedCount += delta;
            if (delta == 1) {
                curr->mpp[id]++;
                curr->lockedDescendants.push_back(node);
            } else {
                curr->mpp[id]--;
                if (curr->mpp[id] == 0)
                    curr->mpp.erase(id);
                auto& vec = curr->lockedDescendants;
                vec.erase(remove(vec.begin(), vec.end(), node), vec.end());
            }
            curr = curr->parent;
        }
    }

    /*
        Unlocks all descendant nodes that were locked by the same user ID.
        Safely reads and unlocks each locked descendant.
    */
    void unlockDescendants(Tree* node, int id) {
        vector<Tree*> toUnlock;
        {
            lock_guard<mutex> lock(node->mtx);
            toUnlock = node->lockedDescendants;
        }
        for (Tree* desc : toUnlock) {
            lock_guard<mutex> lock(desc->mtx);
            if (desc->isLocked && desc->id == id) {
                desc->isLocked = false;
                addChildLock(desc, -1, id);
            }
        }
    }

public:
    /*
        Adds a new node to the system.
        Protected by mutex to avoid race on map insert.
    */
    void addNode(const string& name) {
        lock_guard<mutex> lock(store_mutex);
        store[name] = new Tree(name);
    }

    /*
        Builds a general m-ary tree based on level order.
        Assigns parent-child relationships.
    */
    void buildTree(const vector<string>& names, int m) {
        int n = names.size();
        for (int i = 0; i < n; ++i) {
            Tree* parent = store[names[i]];
            for (int j = 1; j <= m; ++j) {
                int childIndex = i * m + j;
                if (childIndex >= n) break;
                Tree* child = store[names[childIndex]];
                parent->children.push_back(child);
                child->parent = parent;
            }
        }
    }

    /*
        Locks the node if:
        - It is not already locked
        - No ancestor is locked
        - No descendant is locked
    */
    bool lockNode(const string& name, int id) {
        Tree* node;
        {
            lock_guard<mutex> lock(store_mutex);
            node = store[name];
        }

        lock_guard<mutex> lock(node->mtx);
        if (node->isLocked || parentLocked(node) || node->childLockedCount > 0)
            return false;

        node->isLocked = true;
        node->id = id;
        addChildLock(node, 1, id);
        return true;
    }

    /*
        Unlocks the node only if:
        - It is locked
        - Same user (id) is trying to unlock
    */
    bool unlockNode(const string& name, int id) {
        Tree* node;
        {
            lock_guard<mutex> lock(store_mutex);
            node = store[name];
        }

        lock_guard<mutex> lock(node->mtx);
        if (!node->isLocked || node->id != id)
            return false;

        node->isLocked = false;
        addChildLock(node, -1, id);
        return true;
    }

    /*
        Upgrades the node to locked if:
        - It is not locked
        - No ancestor is locked
        - All locked descendants belong to same user ID
    */
    bool upgradeNode(const string& name, int id) {
        Tree* node;
        {
            lock_guard<mutex> lock(store_mutex);
            node = store[name];
        }

        lock_guard<mutex> lock(node->mtx);
        if (node->isLocked || parentLocked(node))
            return false;
        if (node->mpp.size() != 1 || node->mpp.begin()->first != id)
            return false;

        unlockDescendants(node, id);
        node->isLocked = true;
        node->id = id;
        addChildLock(node, 1, id);
        return true;
    }

    /*
        Thread handler function: determines which operation to perform.
        Called from main() in separate threads.
    */
    void handleQuery(int a, const string& name, int id) {
        bool result = false;
        if (a == 1)
            result = lockNode(name, id);
        else if (a == 2)
            result = unlockNode(name, id);
        else
            result = upgradeNode(name, id);
        cout << (result ? "true" : "false") << endl;
    }
};

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    TreeLockingSystem system;
    vector<string> names(n);

    /*
        Read node names and add them to the system
    */
    for (int i = 0; i < n; ++i) {
        cin >> names[i];
        system.addNode(names[i]);
    }

    /*
        Build the tree in level-order using m-ary relationship
    */
    system.buildTree(names, m);

    vector<thread> threads;

    /*
        Launch threads for each query concurrently
        Each query performs lock, unlock, or upgrade
    */
    for (int i = 0; i < q; ++i) {
        int a, id;
        string name;
        cin >> a >> name >> id;

        // Create a new thread and bind the class method to it
        threads.emplace_back(&TreeLockingSystem::handleQuery, &system, a, name, id);
    }

    /*
        Wait for all threads to finish
    */
    for (auto& t : threads) t.join();

    return 0;
}
