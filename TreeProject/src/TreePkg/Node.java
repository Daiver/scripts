package TreePkg;

public class Node {

	Object value = null;
	Comparable key = null;
	Node L = null;
	Node R = null;
	public Node(Comparable key, Object value){
		this.key = key;
		this.value = value;
	}
	
}
