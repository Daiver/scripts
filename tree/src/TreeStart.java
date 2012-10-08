
///import TreePkg;

public class TreeStart {

	public static void main(String[] args) {
	    TreePkg.Tree tree = new TreePkg.Tree();
	
		tree.add(12, "12!");
		tree.add(14, "14!");
		tree.add(1, "1!");
		tree.add(14, "14!");
		tree.add(16, "16!");
		tree.add(15, "15!");
		
		System.out.println(tree.find(12));
		System.out.println(tree.find(14));
		System.out.println(tree.find(1));
		System.out.println(tree.find(16));
		System.out.println(tree.find(105));
		tree.delete(12);
		System.out.println(tree.find(12));
		System.out.println(tree.find(14));
		System.out.println(tree.find(1));
		System.out.println(tree.find(16));
		System.out.println(tree.find(15));
	}
	
}
