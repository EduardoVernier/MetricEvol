#ifndef TRIE_H
#define TRIE_H

#include <vector>
using namespace std;

class Node
{
public:
    Node() { mContent = ' '; mMarker = false; }
    ~Node() {};
    void setContent(char c) { mContent = c; }
    bool wordMarker() { return mMarker; }
    void setWordMarker() { mMarker = true; }
    Node* findChild(char c);
    void appendChild(Node* child) {mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }

private:
    char mContent;
    bool mMarker;
    vector <Node*> mChildren;
};


class Trie
{
public:
    Trie();
    ~Trie();
    bool addSHA1(char* s);
    bool searchSHA1(char* s);

private:
    Node* root;

};

#endif // TRIE_H
