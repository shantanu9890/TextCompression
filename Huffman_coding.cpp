#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

string takeInput()
{
    cout << "# ENTER TEXT : " << endl;
    string s;
    getline(cin, s);
    return s;
}

int *freqArray(string s)
{
    int *a = new int[256];
    for (int i = 0; i < 256; i++)
    {
        a[i] = 0;
    }

    for (int i = 0; i < s.size(); i++)
    {
        a[s[i]]++;
    }

    return a;
}
 
class binaryTreeNode
{
public:
    int data;
    char ch;
    bool isLeaf;
    binaryTreeNode *right, *left;

    binaryTreeNode(int data, char c = '\0')
    {
        this->isLeaf = false;
        this->data = data;
        this->ch = c;
        this->left = nullptr;
        this->right = nullptr;
    }
    ~binaryTreeNode()
    {
        delete left;
        delete right;
    }
};

class Comp
{
public:
    friend class binaryTreeNode;
    bool operator()(binaryTreeNode *a, binaryTreeNode *b)
    {
        return a->data > b->data;
    }
};

class HuffmanCode
{
    friend class binaryTreeNode;
    friend class Comp;

    int *fArray;
    priority_queue<binaryTreeNode *, vector<binaryTreeNode *>, Comp> heap;
    unordered_map<char, string> chst;
    unordered_map<string, char> stch;

public:
    HuffmanCode();
    void encode(string, unordered_map<char, string>);
    void decode(string, unordered_map<string, char>);
};

void fillMap(binaryTreeNode *root, unordered_map<char, string> &map, unordered_map<string, char> &map1, string s)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->isLeaf)
    {
        map[root->ch] = s;
        map1[s] = root->ch;
        return;
    }

    fillMap(root->left, map, map1, s + "0");
    fillMap(root->right, map, map1, s + "1");
}

void getcode(string st)
{
    for (int i = 0; i < st.size(); i++)
    {
        cout << (int)st[i] - 48;
    }
}

void HuffmanCode::encode(string text, unordered_map<char, string> chst)
{
    cout << "encoded code: ";
    vector<char> v;
    for (int i = 0; i < text.size(); i++)
    {
        if (chst.count(text[i]) == 0)
        {
            v.push_back(text[i]);
            continue;
        }
        string out = chst[text[i]];
        getcode(out);
    }
    cout<<endl;
    if (!v.empty())
    {
        cout << "Letters: ";
        for (int j = 0; j < v.size(); j++)
        {
            cout << v[j] << " , ";
        }
        cout << "are not available.";
    }

    cout << "\n\n";
}

void HuffmanCode::decode(string text, unordered_map<string, char> stch)
{
    cout << "decoded text: ";
    int j = 0;
    for (int i = 0; i < text.size(); i++)
    {
        string s = text.substr(j, i - j + 1);
        if (stch.count(s) > 0)
        {
            cout << stch[s];
            j = i + 1;
        }
    }
    cout << endl;
}

HuffmanCode::HuffmanCode()
{
    while (true)
    {

        string text = takeInput();
        fArray = freqArray(text);

        for (int i = 0; i < 256; i++)
        {
            if (fArray[i] == 0)
            {
                continue;
            }

            binaryTreeNode *root = new binaryTreeNode(fArray[i], (char)i);
            root->isLeaf = true;
            heap.push(root);
        }

        while (heap.size() > 1)
        {
            binaryTreeNode *node1 = heap.top();
            heap.pop();
            binaryTreeNode *node2 = heap.top();
            heap.pop();
            binaryTreeNode *root = new binaryTreeNode(node1->data + node2->data);
            root->left = node1;
            root->right = node2;
            heap.push(root);
        }
        cout << heap.size() << endl;
        binaryTreeNode *fRoot = heap.top();

        string s = "";
        fillMap(fRoot, chst, stch, s);
        encode(text, chst);

        cout << "code for each character: " << endl;
        unordered_map<char, string>::iterator i = chst.begin();
        while (i != chst.end())
        {
            cout << i->first << " : " << i->second << endl;
            i++;
        }
        cout << endl;

        bool loop = true;
        while (loop)
        {
            cout << "Enter 1 to encode, 2 to decode & -1 to stop : ";
            int k;
            cin >> k;
            if (cin.fail()||k==-1)
            {
                cin.clear();
                cin.ignore(512, '\n');
                if (k==-1)
                {
                    loop=false;cout<<"\n\n";
                    continue;
                }
                
            }
            if (k != 1 && k != 2 && k != -1)
            {
                cout << "Enter appropriate value " << endl;
                continue;
            }
            else
            {
                cout << "Enter text: " << endl;
                string input;
                cin >> input;

                switch (k)
                {
                case 1:
                    encode(input, chst);
                    break;

                case 2:
                    decode(input, stch);
                    break;
                }
            }
        }
    }
}

int main()
{
    HuffmanCode hf;
    return 0;
}
