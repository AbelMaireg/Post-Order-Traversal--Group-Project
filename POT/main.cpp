#include "./b-tree.h"

int main()
{
    BTree<char> btree('a');

    BTree<char>::Iterator it(btree.root());

    it.setL('b'); it.setR('c');

    it.left();
    it.setL('d'); it.setR('e');

    it.parent().right();
    it.setL('f'); it.setR('g');

    it.right();
    it.setL('h'); it.setR('i');

    it.mostParent();
    it.print_postOT();
}