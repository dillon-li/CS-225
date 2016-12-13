/**
 * @file huffman_tree.cpp
 * Implementation of a Huffman Tree class.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

#include "huffman_tree.h"

using namespace std;

HuffmanTree::HuffmanTree( vector<Frequency> frequencies ) {
	std::stable_sort( frequencies.begin(), frequencies.end() );
	buildTree( frequencies );
	vector<bool> path;
	buildMap( root, path );
}

HuffmanTree::HuffmanTree( const HuffmanTree & other ) {
	copy( other );
}

HuffmanTree::HuffmanTree( BinaryFileReader & bfile ) {
	root = readTree( bfile );
	vector<bool> path;
	buildMap( root, path );
}

HuffmanTree::~HuffmanTree() {
	clear( root );
}

const HuffmanTree & HuffmanTree::operator=( const HuffmanTree & rhs ) {
	if( this != &rhs ) {
		clear( root );
		copy( rhs );
	}
	return *this;
}

void HuffmanTree::clear( TreeNode * current ) {
	if( current == NULL )
		return;
	clear( current->left );
	clear( current->right );
	delete current;
}

void HuffmanTree::copy( const HuffmanTree & rhs ) {
	root = copy( rhs.root );
}

HuffmanTree::TreeNode * HuffmanTree::copy( const TreeNode * current ) {
	if( current == NULL )
		return NULL;
	TreeNode * node = new TreeNode( current->freq );
	node->left = copy( current->left );
	node->right = copy( current->right );
	return node;
}


HuffmanTree::TreeNode * HuffmanTree::removeSmallest( 
		queue<TreeNode *> & singleQueue, queue<TreeNode *> & mergeQueue ) {

	/**
	 * @todo Your code here!
	 *
	 * Remove the smallest TreeNode * from the two queues given as
	 * parameters. The entries on the queues are in sorted order, so the
	 * smaller of the two queues heads is the smallest item in either of
	 * the queues. Return this item after removing it from its queue.
	 */
	TreeNode * smallest = NULL;
	if(mergeQueue.empty() && singleQueue.empty()) // Both empty
		return smallest;
	else if(!mergeQueue.empty() && singleQueue.empty()) // One is empty
	{
		smallest=mergeQueue.front();
		mergeQueue.pop();
	}
	else if(mergeQueue.empty() && !singleQueue.empty()) // Other one is empty
	{
		smallest=singleQueue.front();
		singleQueue.pop();
	}
	else // Both have data
	{
		if(mergeQueue.front()->freq.getFrequency()<singleQueue.front()->freq.getFrequency()) 
		{
			smallest=mergeQueue.front();
			mergeQueue.pop();
		}
		else
		{
			smallest=singleQueue.front(); 
			singleQueue.pop();
		}
	}
	return smallest;
}

void HuffmanTree::buildTree( const vector<Frequency> & frequencies ) {
	queue<TreeNode *> singleQueue; // Queue containing the leaf nodes
	queue<TreeNode *> mergeQueue;  // Queue containing the inner nodes

	// Pushes the leaf nodes into singleQueue
	for(int i = 0; i < frequencies.size(); i++)
	{
		TreeNode * leaf = new TreeNode(frequencies[i]);
		singleQueue.push(leaf);
	}
	TreeNode * left_child;
	TreeNode * right_child;
	
	while(!((singleQueue.empty() && (mergeQueue.size() == 1)) || (mergeQueue.empty() && (singleQueue.size() == 1))))
	{
		left_child = removeSmallest(singleQueue, mergeQueue);
		right_child = removeSmallest(singleQueue, mergeQueue);
		TreeNode * parent = new TreeNode((left_child->freq).getFrequency() + (right_child->freq).getFrequency());
		parent->left = left_child;
		parent->right = right_child;
		mergeQueue.push(parent);
	}
	
	if(singleQueue.size() == 1)
		root = singleQueue.front();
	else if(mergeQueue.size() == 1)
		root = mergeQueue.front();
}

string HuffmanTree::decodeFile( BinaryFileReader & bfile ) {
	stringstream ss;
    decode( ss, bfile );
	return ss.str();
}

void HuffmanTree::decode( stringstream & ss, BinaryFileReader & bfile ) {
	TreeNode * current = root;
	while( bfile.hasBits() ) {
		if((current->left == NULL) && (current->right == NULL))
		{
			ss << (current->freq).getCharacter();
			current = root;
		}
		if(bfile.getNextBit())
			current = current->right; 
		else 
			current = current->left; 
	}
	ss << (current->freq).getCharacter();
}

void HuffmanTree::writeTree( BinaryFileWriter & bfile ) {
	writeTree( root, bfile );
}

void HuffmanTree::writeTree( TreeNode * current, BinaryFileWriter & bfile ) {
	
	if((current->left == NULL) && (current->right == NULL))
	{
		bfile.writeBit(1);
		bfile.writeByte((current->freq).getCharacter());
	}
	else
	{
		bfile.writeBit(0);
		writeTree(current->left, bfile);
		writeTree(current->right, bfile);
	}

	/**
	 * @todo Your code here!
	 *
	 * This code is writing the current HuffmanTree in a compressed format
	 * to the given BinaryFileWriter. The strategy for doing so is as
	 * follows:
	 *		1. If we are a leaf node, write the bit "1" followed by the
	 *		   byte that is the character of this node.
	 *		2. If we are an internal node, writ the bit "0", and then
	 *		   encode the left and right subtree, recursively.
	 *
	 *	Note that we don't encode the frequencies in this compressed
	 *	version: this is fine, as the structure of the tree still reflects
	 *	what the relative frequencies were.
	 */
}

HuffmanTree::TreeNode * HuffmanTree::readTree( BinaryFileReader & bfile ) {
	
	if(bfile.hasBits())
	{
		if(bfile.getNextBit())
		{
			Frequency huff_freq(bfile.getNextByte(), 0);
			TreeNode * read_huffman = new TreeNode(huff_freq);	
			return read_huffman;
		}
		else
		{
			TreeNode * internal = new TreeNode(0);
			internal->left = readTree(bfile);
			internal->right = readTree(bfile);
			return internal;
		}
	}
	else
		return NULL;			

	/**
	 * @todo Your code here!
	 *
	 * This code is reading a HuffanTree in from a file in the format that
	 * we wrote it above. The strategy, then, is as follows:
	 *		1. If the file has no more bits, we're done.
	 *		2. If we read a 1 bit, we are a leaf node: create a new
	 *		   TreeNode with the character that is the next byte in the
	 *		   file (its frequency should be 0, since we are ignoring
	 *		   frequency data now).
	 *		3. If we read a 0 bit, create a new internal node (with
	 *		   frequency 0, since we are ignoring them now, and set its left
	 *		   child and right children to be the subtrees built recursively.
	 *		4. Your function should return the TreeNode it creates, or NULL
	 *		   if it did not create one.
	 */
}

void HuffmanTree::buildMap( TreeNode * current, vector<bool> & path ) {
	// Base case: leaf node.
	if( current->left == NULL && current->right == NULL ) {
		bitsMap[current->freq.getCharacter()] = path;
		return;
	}

	// Move left
	path.push_back( false );
	buildMap( current->left, path );
	path.pop_back();

	// Move right
	path.push_back( true );
	buildMap( current->right, path );
	path.pop_back();
}

void HuffmanTree::printInOrder() const {
	printInOrder( root );
	cout << endl;
}

void HuffmanTree::printInOrder( const TreeNode * current ) const {
	if( current == NULL )
		return;
	printInOrder( current->left );
	cout << current->freq.getCharacter() << ":" <<
		current->freq.getFrequency() << " ";
	printInOrder( current->right );
}

void HuffmanTree::writeToFile( const string & data, BinaryFileWriter & bfile ) {
	for( auto it = data.begin(); it != data.end(); ++it )
		writeToFile( *it, bfile );
}

void HuffmanTree::writeToFile( char c, BinaryFileWriter & bfile ) {
	vector<bool> bits = getBitsForChar( c );
	for( auto it = bits.begin(); it != bits.end(); ++it )
		bfile.writeBit( *it );
}

vector<bool> HuffmanTree::getBitsForChar( char c ) {
	return bitsMap[c];
}

// class for generic printing

template <typename TreeNode>
class HuffmanTreeNodeDescriptor:
    public GenericNodeDescriptor< HuffmanTreeNodeDescriptor<TreeNode> >
{
	public:

	HuffmanTreeNodeDescriptor(const TreeNode* root): subRoot(root) { /* nothing */ }

	string key() const
	{
		std::stringstream ss;
        char ch = subRoot->freq.getCharacter();
		int freq = subRoot->freq.getFrequency();

        // print the sum of the two child frequencies
        if(ch == '\0')
		    ss << freq;
        // print the leaf containing a character and its count
        else
        {
            if(ch == '\n')
                ss << "\\n";
            else
                ss << ch;
            ss << ":" << freq;
        }
		return ss.str();
	}

	bool isNull() const { return subRoot == NULL; }
	HuffmanTreeNodeDescriptor left() const { return HuffmanTreeNodeDescriptor(subRoot->left); }
	HuffmanTreeNodeDescriptor right() const { return HuffmanTreeNodeDescriptor(subRoot->right); }

	private:

    const TreeNode* subRoot;
};

int HuffmanTree::height(const TreeNode* subRoot) const
{
    if(subRoot == NULL)
        return -1;
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

void HuffmanTree::print(std::ostream & out) const
{
    int h = height(root);
    if(h > _max_print_height)
    {
        out << "Tree is too big to print. Try with a small file (e.g. data/small.txt)" << endl;
        return;
    }

    printTree(HuffmanTreeNodeDescriptor<TreeNode>(root), out);
}
