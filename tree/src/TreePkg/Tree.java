package TreePkg;

public class Tree {
	Node root = null;
	
	private void remove(Comparable key, Node n, Node old) {
		if (n == null)
			return;
		int res = n.key.compareTo(key);
		if (res > 0)
			this.remove(key, n.R, n);
		if (res < 0)
			this.remove(key, n.L, n);
		if ((n.L == null) && (n.R == null)) {
			if (old.L == n)
				old.L = null;
			if (old.R == n)
				old.R = null;
			return;
		}
		if ((n.L == null) || (n.R == null)) {
			Node tmp = null;
			if (n.L == null)
				tmp = n.L;
			if (n.R == null)
				tmp = n.R;
			n.key = tmp.key;
			n.value = tmp.value;
			n.L = tmp.L;
			n.R = tmp.R;
			return;
		}
		Node tmp = n.R;
		while (tmp.L != null) {
			tmp = tmp.L;
		}
		n.value = tmp.value;
		n.key = tmp.key;
		this.remove(tmp.key, n.R, n);
	}
	
	public void delete(Comparable key) {
		if (this.root.key.compareTo(key) == 0) {
			if  ((this.root.L == null) && (this.root.R == null)) {
				this.root = null;
				return;
			}
			
		}
		this.remove(key, this.root, null);
	}
	
	public boolean add(Comparable key, Object value) {
		Node res = new Node(key, value);
		if (this.root == null) {
			this.root = res;
			return true;
		}
		Node tmp = this.root;
		Node old = null;
		
		while ((tmp != null) && (tmp.key.compareTo(key) != 0)) {
			old = tmp;
			if (tmp.key.compareTo(key) > 0) {
				tmp = tmp.R;
			}
			else {
				tmp = tmp.L;
			}				
		}
		
		if (tmp != null)
			return false;
		if (old.key.compareTo(key) > 0) {
			old.R = res;
		}
		else {
			old.L = res;
		}
		return true;
	}
	
	public Object find(Comparable key) {
		Node tmp = this.root;
		while ((tmp != null) && (tmp.key.compareTo(key) != 0)) {
			if (tmp.key.compareTo(key) > 0) {
				tmp = tmp.R;
			}
			else {
				tmp = tmp.L;
			}
				
		}
		if (tmp == null)
			return null;
		return tmp.value;
	}
	
	public Tree() {
		
	}

}
