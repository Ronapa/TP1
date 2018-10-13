#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include "Array.h"

using namespace std;

typedef struct 
{
	double min;
	double max;
	double sum;
	int index;
	int l_bound;
	int r_bound;
	int valid_measures;
}leaf;

class Segment_Tree
{

	private:
		Array<leaf *> data;
		int number_of_values;
		int l_bound, r_bound;

		void build_Segment_Tree(int , int , int , Array<Data> & , Array<leaf> &)	


	public:
		Segment_Tree(& Array<Data>);
		~Segment_Tree();

		get_data_from_segment_tree(& Array<Data> , int , int);

}

Segment_Tree::Segment_Tree(& Array<Data> sensor)
{	
	number_of_values = sensor.get_size()-1;
	data = new Array<leaf>(number_of_values);
	l_bound = 0;
	r_bound = number_of_values+1;
	build_Segment_Tree(0,l_bound,r_bound,sensor,*(data));
}

void Segment_Tree::build_Segment_Tree(int index, int l_bound, int r_bound, Array<Data> &sensor , Array<leaf> &seg_tree)
{
	int i_left = (index*2+1)%number_of_values;
	int i_right = (index*2+2)%number_of_values;
	if (l_bound+2 == r_bound)
	{
		if (sensor[i_left].is_valid() == TRUE && sensor[i_right].is_valid() == TRUE)
		{
			double value1 = sensor[i_left].get_data();
			double value2 = sensor[i_right].get_data();

			seg_tree[i].min = value1 <= value2 ? value1 : value2;
			seg_tree[i].max = value1 >= value2 ? value1 : value2;
			seg_tree[i].sum = value1 + value2;
			seg_tree[i].valid_measures = 2;

		}else if(sensor[i_left].is_valid() == FALSE && sensor[i_right].is_valid() == TRUE)
		{
			double value1 = sensor[i_right].get_data();

			seg_tree[i].min = value1;
			seg_tree[i].max = value1;
			seg_tree[i].sum = value1;
			seg_tree[i].valid_measures = 1;
		}else if(sensor[i_left].is_valid() == TRUE && sensor[i_right].is_valid() == FALSE)
		{
			double value1 = sensor[i_left].get_data();

			seg_tree[i].min = value1;
			seg_tree[i].max = value1;
			seg_tree[i].sum = value1;
			seg_tree[i].valid_measures = 1;
		}else
		{
			seg_tree[i].min = INFINITE;
			seg_tree[i].max = MINUS_INFINITE;
			seg_tree[i]].sum = 0;
			seg_tree[i].valid_measures = 0;
		}
		seg_tree[i].l_bound = i_left;
		seg_tree[i].r_bound = i_right;
	}else
	{
		int mid = (l_bound + r_bound)/2;
		build_Segment_Tree(i_left,l_bound,mid,sensor,seg_tree);
		build_Segment_Tree(i_right,mid+1,r_bound,sensor,seg_tree);
		seg_tree[index] = seg_tree[i_left]|seg_tree[i_right];
	}
	return
}

	
