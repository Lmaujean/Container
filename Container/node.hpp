#pragma once

namespace ft
{
	template <class T>	
	struct Node
	{
		T	    * data;
		Node 	* parent;
		Node	* left;
		Node	* right;
		int	color;
	};
};