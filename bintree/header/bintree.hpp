#include <iostream>
#include <deque>

template <class Key, class Val, class Comp=std::less<Key>>
class BinTree {
	private:
		struct Node {
			Val val;
			Key key;
			Node *left = nullptr;
			Node *right = nullptr;
			Node *parent = nullptr;

			bool is_left_child() {
				return (parent && (parent->left == this));
			}

			bool is_right_child() {
				return (parent && (parent->right == this));
			}
		};

		static Comp comp;
		Node *root = nullptr;

	public:
		class iterator {
			using Node=BinTree::Node;
			Node *current = nullptr;

			private:
				iterator() {}

				explicit iterator(Node *node): current(node) {}

				friend BinTree;

			public:
				iterator& operator++() {
					if (current->right) {
						current = current->right;
						while (current->left) current = current->left;
					} else if (current->is_left_child()) {
						current = current->parent;
					} else if (current->is_right_child()) {
						current = current->parent;
						while (current && !current->is_left_child()) current = current->parent;
						if (current) current = current->parent;
					} else {
						current = nullptr;
					}
					return *this;
				}

				Val& operator*() {
					return current->val;
				}

				bool operator==(const iterator &it) const {
					return (current == it.current);
				}

				bool operator!=(const iterator &it) const {
					return (current != it.current);
				}
		};

		iterator begin() {
			Node *current = root;
			if (!current) return end();
			while (current->left) current = current->left;
			return iterator(current);
		}

		iterator end() {
			return iterator();
		}

	public:
		BinTree() {}

		~BinTree() {
			std::deque<Node*> deq;
			if (root) deq.push_back(root);
			while (!deq.empty()) {
				if (deq.front()->left) deq.push_back(deq.front()->left);
				if (deq.front()->right) deq.push_back(deq.front()->right);
				delete deq.front();
				deq.pop_front();
			}
		}

		Val& operator[](const Key &key) {
			return this->get_at(key)->val;
		}

		bool erase(Key key) {
			Node* todel = this->get_at(key);
			if (!todel) return false;

			if (todel->is_left_child()) {
				todel->parent->left = nullptr;
			} else if (todel->is_right_child()) {
				todel->parent->right = nullptr;
			} else {
				root = root->left ? root->left : root->right;
			}

			if (todel->left) {
				auto tmp = todel->left;
				tmp->parent = nullptr;
				this->insert(tmp);
			}

			if (todel->right) {
				auto tmp = todel->right;
				tmp->parent = nullptr;
				this->insert(tmp);
			}

			delete todel;
			return true;
		}


	private:
		Node* get_at(const Key &key) {
			Node *current = root;
			if (!current) {
				Node *newboi = new Node;
				newboi->key = key;
				root = newboi;
				return root;
			}

			while (current->left || current->right) {
				if (comp(key, current->key)) {
					if(!current->left) break;
					current = current->left;
				} else if (comp(current->key, key)) {
					if(!current->right) break;
					current = current->right;
				} else {
					return current;
				}
			}

			const bool lt = comp(current->key, key);
			const bool gt = comp(key, current->key);

			if(!(lt || gt)) return current;

			Node *newboi = new Node;
			newboi->parent = current;
			newboi->key = key;

			if (lt) {
				current->right = newboi;
			} else {
				current->left = newboi;
			}
			return newboi;
		}

		Node* insert(Node *newnode) {
			Node *current = root;
			if (!newnode) return newnode;
			if (!current) {
				root = newnode;
				return newnode;
			}

			std::deque<Node*> deq;
			deq.push_front(newnode);
			while (!deq.empty()) {
				current = root;
				Node *newboi = deq.front();
				deq.pop_front();
				while (current->left || current->right) {
					if (comp(newboi->key, current->key)) {
						if(!current->left) break;
						current = current->left;
					} else if (comp(current->key, newboi->key)) {
						if(!current->right) break;
						current = current->right;
					} else {
						current->val = newboi->val;
						auto tmp1 = newboi->right;
						auto tmp2 = newboi->left;

						if (tmp1) {
							tmp1->parent = nullptr;
							deq.push_back(tmp1);
						}

						if (tmp2) {
							tmp2->parent = nullptr;
							deq.push_back(tmp2);
						}

						delete newboi;
					}
				}

				const bool lt = comp(current->key, newboi->key);
				const bool gt = comp(newboi->key, current->key);

				newboi->parent = current;
				if (lt) {
					auto tmp = newboi->left;
					current->right = newboi;

					if (tmp) {
						newboi->left = nullptr;
						tmp->parent = nullptr;
						deq.push_back(tmp);
					}
				} else if (gt) {
					auto tmp = newboi->right;
					current->left = newboi;

					if (tmp) {
						newboi->right = nullptr;
						tmp->parent = nullptr;
						deq.push_back(tmp);
					}
				} else {
					current->val = newboi->val;
					auto tmp1 = newboi->right;
					auto tmp2 = newboi->left;

					if (tmp1) {
						tmp1->parent = nullptr;
						deq.push_back(tmp1);
					}

					if (tmp2) {
						tmp2->parent = nullptr;
						deq.push_back(tmp2);
					}

					delete newboi;
				}
			}
			return newnode;
		}
};

template <class Key, class Val, class Comp>
Comp BinTree<Key, Val, Comp>::comp;
