class TrieNode {
public:
    TrieNode* children[26];
    int maxx;
    bool flag;

    TrieNode (){
        for (int i=0;i<26;i++)children[i]=nullptr;
        maxx=-1;
        flag=false;
    }
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (int i=0;i<word.size();i++){
            int index=word[i]-'a';
            if (!node->children[index]){
                node->children[index]=new TrieNode();
            }
            node = node->children[index];
        }
        node->flag=true;
    }
    
    bool search(string word) {
        TrieNode* node = root;
        for (int i=0;i<word.size();i++){
            int index = word[i]-'a';
            if (!node->children[index])return false;
            node = node->children[index];
        }
        if (node->flag)return true;
        return false;
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (int i=0;i<prefix.size();i++){
            int index = prefix[i]-'a';
            if (!node->children[index])return false;
            node = node->children[index];
        }
        return true;
    }
};
