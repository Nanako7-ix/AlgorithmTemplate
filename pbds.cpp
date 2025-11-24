#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template<typename T>
struct NodeUpdate {
	template<typename Node_CItr,typename Node_Itr,typename Cmp_Fn,typename _Alloc>
	struct X {
		using metadata_type = T;
		void operator()(Node_Itr u, Node_CItr end) {
			Node_Itr l = u.get_l_child();
			Node_Itr r = u.get_r_child();
			const_cast<T&> (u.get_metadata()) = (
				(l == end ? T() : l.get_metadata()) +
				**u +
				(r == end ? T() : r.get_metadata())
			);
		}
		virtual Node_CItr node_begin() const = 0;
		virtual Node_CItr node_end() const = 0;
	};
};

template<typename T, template<typename Node_CItr,typename Node_Itr,typename Cmp_Fn,typename _Alloc> typename NodeUpdate>
struct Tree : __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, NodeUpdate> {
	using super = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, NodeUpdate>;
	// ......
};

template<typename T>
template<typename Node_CItr, typename Node_Itr, typename Cmp_Fn, typename _Alloc>
using X = typename NodeUpdate<T>::template X<Node_CItr, Node_Itr, Cmp_Fn, _Alloc>;

struct count {
	int cnt;
	count() { cnt = 0; }
	count(int) { cnt = 1; }
	friend count operator+(const count& x, const count& y) {
		count res;
		res.cnt = x.cnt + y.cnt;
		return res;
	}
};

Tree<int, NodeUpdate<count>::X> s;

