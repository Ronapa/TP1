#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include "Array.h"
#include "utilities.h"
#include "data.h"
#include "leaf.h"
#include "segment_tree.h"

using namespace std;

Segment_Tree::Segment_Tree(Array<data> & sensor)
{	
	number_of_values = sensor.size()-1;
	seg_tree = new Array<leaf>(number_of_values);
	l_bound = 0;
	r_bound = number_of_values+1;
	build_Segment_Tree(0,l_bound,r_bound,sensor);
	for (int i =0 ; i<number_of_values ; i++)
	{
		//cout << (*seg_tree)[i].min << " " << (*seg_tree)[i].max << " " << (*seg_tree)[i].sum << " " << (*seg_tree)[i].valid_measures << endl;
	}
}

Segment_Tree::~Segment_Tree()
{	
	delete seg_tree;
}

void Segment_Tree::build_Segment_Tree(int index, int l_bound, int r_bound, Array<data> &sensor)
{
	int i_left = (index*2+1);
	int i_right = (index*2+2);
	//cout << index << " i_left: " << i_left << "  i_right: " << i_right << " l_bound: " << l_bound << " r_bound: " << r_bound << endl;
	if (l_bound+2 == r_bound)
	{
		i_left = (index*2+1) - number_of_values;
		i_right = (index*2+2) - number_of_values;
		if (sensor[i_left].is_valid() == true && sensor[i_right].is_valid() == true)
		{
			double value1 = sensor[i_left].get_data();
			double value2 = sensor[i_right].get_data();

			(*seg_tree)[index].min = value1 <= value2 ? value1 : value2;
			(*seg_tree)[index].max = value1 >= value2 ? value1 : value2;
			(*seg_tree)[index].sum = value1 + value2;
			(*seg_tree)[index].valid_measures = 2;

		}else if(sensor[i_left].is_valid() == false && sensor[i_right].is_valid() == true)
		{
			double value1 = sensor[i_right].get_data();

			(*seg_tree)[index].min = value1;
			(*seg_tree)[index].max = value1;
			(*seg_tree)[index].sum = value1;
			(*seg_tree)[index].valid_measures = 1;
		}else if(sensor[i_left].is_valid() == true && sensor[i_right].is_valid() == false)
		{
			double value1 = sensor[i_left].get_data();

			(*seg_tree)[index].min = value1;
			(*seg_tree)[index].max = value1;
			(*seg_tree)[index].sum = value1;
			(*seg_tree)[index].valid_measures = 1;
		}else
		{
			(*seg_tree)[index].min = INFINITE;
			(*seg_tree)[index].max = MINUS_INFINITE;
			(*seg_tree)[index].sum = 0;
			(*seg_tree)[index].valid_measures = 0;
		}
		(*seg_tree)[index].l_bound = l_bound;
		(*seg_tree)[index].r_bound = r_bound;
		return;
	}else
	{
		int mid = (l_bound + r_bound)/2;
		build_Segment_Tree(i_left,l_bound,mid,sensor);
		build_Segment_Tree(i_right,mid,r_bound,sensor);
		(*seg_tree)[index] = (*seg_tree)[i_left]||(*seg_tree)[i_right];
	}
	return ;
}

leaf Segment_Tree::get_value_from_segment_tree(int index , int q_left , int q_right , Array<data> &sensor)	
{
	//cout << index << " q_left: " << q_left << "  q_right: " << q_right << " l_bound: " << (*seg_tree)[index].l_bound << " r_bound: " << (*seg_tree)[index].r_bound << endl;
	if (index > (number_of_values -1))
	{
		leaf aux;
		int index_bis = index - number_of_values;
		if(sensor[index_bis].is_valid() == true && index_bis >= q_left && index_bis <q_right)
		{
			float value1 = sensor[index_bis].get_data();

			aux.min = value1;
			aux.max = value1;
			aux.sum = value1;
			aux.valid_measures = 1;
		}else
		{
			aux.min = INFINITE;
			aux.max = MINUS_INFINITE;
			aux.sum = 0;
			aux.valid_measures = 0;
		}
		aux.l_bound = (*seg_tree)[index].l_bound;
		aux.r_bound = (*seg_tree)[index].r_bound;

		return aux;
	}
	if ((*seg_tree)[index].l_bound >= q_left && (*seg_tree)[index].r_bound <= q_right)
	{
		return (*seg_tree)[index];
	}
	if ((*seg_tree)[index].l_bound >= q_right || (*seg_tree)[index].r_bound <= q_left)
	{
		leaf aux;
		aux.min = INFINITE;
		aux.max = MINUS_INFINITE;
		aux.sum = 0;
		aux.valid_measures = 0;
		aux.l_bound = (*seg_tree)[index].l_bound;
		aux.r_bound = (*seg_tree)[index].r_bound;
		return aux;
	}
	leaf aux_l, aux_r;

	aux_l = get_value_from_segment_tree(index*2+1,q_left,q_right,sensor);
	aux_r = get_value_from_segment_tree(index*2+2,q_left,q_right,sensor);
	
	return aux_l||aux_r;
}