#include <iostream>
#include "node.hpp"


namespace ft
{
  template<class T>
  void inorder(ft::node<T> *root) {
    if (root != NULL) {
      inorder(root->left);
      std::cout << root->key << " -> ";
      if (root->parent == NULL)
        std::cout << " [ NULL ] "  << std::endl;
      else
        std::cout << " [ " << root->parent->key << " ] "  << std::endl;
      inorder(root->right);

    }
  }
  template<class T>
  ft::node<T> *predecessor(ft::node<T> *node)
  {
    ft::node<T> *temp = node;
      if (node != NULL)
      {
        std::cout << node->parent->key;
      }
    return temp;
  }
  template<class T>
  ft::node<T> *minValueNode(ft::node<T> *node) 
  {
    ft::node<T> *current = node;
  
    while (current && current->left != NULL)
      current = current->left;

    return current;
  }
  template<class T>
  ft::node<T> *maxValueNode(ft::node<T> *node) 
  {
    ft::node<T> *current = node;

    while (current && current->right != NULL)
      current = current->right;

    return current;
  }
  template<class T>
  bool findValue(ft::node<T> *node, T key) 
  {
    ft::node<T> *temp = node;
    while (temp != NULL && &key != temp->key)
    {
      if (&key == temp->key)
        return true;
      if (&key > temp->key)
        temp = temp->right;
      else if (&key < temp->key)
        temp = temp->left;
    }
    return false;
  }

  template<class T>
  ft::node<T> *deleteNode(ft::node<T> *root, T key)
  {
    if (root == NULL) return root;
    if (key < root->key)
    {
      root->left = deleteNode(root->left, key);
    }
    else if (key > root->key)
    {
      root->right = deleteNode(root->right, key);
    }
    else {
      if (root->left == NULL && root->right == NULL)
      {
        delete root;
        return NULL;
      }
      if (root->left == NULL) 
      {
        ft::node<T> *temp = root->right;
        temp->parent = root->parent;
        delete root;
        return temp;
      } 
      else if (root->right == NULL) 
      {
        ft::node<T> *temp = root->left;
        temp->parent = root->parent;
        delete root;
        return temp;
      }
      if (root->key == key)
      {
        ft::node<T> *temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
      }
      else
      {  
        ft::node<T> *temp = minValueNode(root);  
        root->key = temp->key;
        root->left = deleteNode(root->left, temp->key);
      }
    }
    return root;
  }

  template<class T>
  void clearNode(ft::node<T> *root)
  {
	while (root->left != NULL && root->right != NULL)
	{
		if (root->left)
			root = root->left;
		else if (root->right)
			root = root->right;
		clearNode(root);
	}
	delete root;
  }
  
}