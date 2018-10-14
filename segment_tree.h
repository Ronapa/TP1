#ifndef SEG_TREE_H
#define SEG_TREE_H

#include <iostream>
#include "Array.h"
#include "data.h"
#include "leaf.h"

class Segment_Tree
{

	private:
		leaf * seg_tree;
		int number_of_values;
		int l_bound, r_bound;

		void build_Segment_Tree(int , int , int , Array<data> & , Array<leaf> &);	


	public:
		Segment_Tree(Array<data> & );
		~Segment_Tree();

		leaf get_value_from_segment_tree(int , int  , int , Array<data> &);

};



#endif