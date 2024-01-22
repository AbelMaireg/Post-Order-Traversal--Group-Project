#include "./b-tree.h"

int main()
{
    BTree<char> btree('a');

    BTree<char>::Iterator it(btree.root());

    it.setLeft('b'); it.setRight('c');

    it.left();
    it.setLeft('d'); it.setRight('e');

    it.parent().right();
    it.setLeft('f'); it.setRight('g');

    it.right();
    it.setLeft('h'); it.setRight('i');

    it.mostParent();
    
// Pre-Order Traversal
    it.print_preOT();
    write(1, "\n", 1);

// In-Order Traversal    
    it.print_inOT();
    write(1, "\n", 1);

// Post-Order Traversal
    it.print_postOT();
    write(1, "\n", 1);

}