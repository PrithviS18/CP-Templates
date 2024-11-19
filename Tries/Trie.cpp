class Node {
    Node *links[2];
 
public:
    int freq[2];
    Node() {
        links[0] = links[1] = nullptr;
        freq[0] = freq[1] = 0;
    }
    void createLink(int b) {
        links[b] = new Node();
    }
    Node* goToLink(int b) {
        return links[b];
    }
    bool containsLink(int b) {
        return links[b] != nullptr;
    }
};
 
class Trie {
    Node *root;
 
public:
    Trie() {
        root = new Node();
    }
    void insert(int x) {
        Node *t = root;
        for (int i = 31; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (!t->containsLink(b)) {
                t->createLink(b);
            }
            t->freq[b]++;
            t = t->goToLink(b);
        }
    }
    void remove(int x) {
        Node *t = root;
        for (int i = 31; i >= 0; i--) {
            int b = (x >> i) & 1;
            t->freq[b]--;
            t = t->goToLink(b);
        }
    }
    int get(int y) {
        Node *t = root;
        int res = 0;
        for (int i = 31; i >= 0; i--) {
            int by = (y >> i) & 1;
            if (t->containsLink(by) && t->freq[by] > 0) {
                t = t->goToLink(by);
            } else {
                res |= (1 << i);
                t = t->goToLink(1 - by);
            }
        }
        return res;
    }
};