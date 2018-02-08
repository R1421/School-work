
public class TreeLock {
//	public class Tree{
		public class Node{
			private Node parent;
			private Node left;
			private Node right;
			private int resource;
			
			private volatile boolean[] flags;
			private volatile int victim;
			
			public Node(){
				flags = new boolean[2];
				flags[0] = false;
				flags[1] = false;
			}
			public Node(Node p){
				parent = p;
				flags = new boolean[2];
				flags[0] = false;
				flags[1] = false;
			}
			public void setLeft(Node n){
				left = n;
			}
			public void setRight(Node n){
				right = n;
			}
			public void setResource(int r){
				resource = r;
			}
			public int getResource(){
				return resource;
			}
			
			public void lock(int i){
				//Use i to find out which is the left child and which is the right
				flags[i] = true;
				victim = i;
				while(flags[1-i] && victim == i){}
				if(parent != null) parent.lock((this == parent.right)? 1:0);	
			}
			public void unlock(int i){
				if(parent != null) parent.unlock((this == parent.right)? 1:0);
				flags[i] = false;
			}
		}
		
		private Node head;
		private Node[] leaves;
		private int index;
		private int numLeaves;
		
		public TreeLock(int n, int r) throws Exception{
			double e = Math.log(n)/Math.log(2) % 1;
			if(e != 0.0){
				throw new IllegalArgumentException("Selected value of n must be a power of 2");
			}
			numLeaves = n/2;
			leaves = new Node[numLeaves];
			index = 0;
			head = new Node();
			head.setResource(r);
			head.setLeft(buildSubTree(numLeaves/2, head));
			head.setRight(buildSubTree(numLeaves/2, head));
		}
		private Node buildSubTree(int n, Node p){
			Node newNode = new Node(p);
			if(n == 1) {
				leaves[index] = newNode;
				index++;
				return newNode;
			}
			newNode.setLeft(buildSubTree(n/2, newNode));
			newNode.setRight(buildSubTree(n/2, newNode));
			return newNode;
		}
		public void printLeaves(){
			for(int i = 0; i < numLeaves; i++){
				System.out.println(leaves[i]);
			}
		}
		public void lock(){
			//Move up the tree locking parent node after parent node
			int i = (int) (Thread.currentThread().getId());
			leaves[i % numLeaves].lock(i % 2);
		}
		public void unlock(){
			//Move to the top of the tree, then unlock each node while heading to the leaf
			int i = (int) (Thread.currentThread().getId());
			leaves[i % numLeaves].unlock(i % 2);
		}
		public void incrementResource(){
			head.setResource(head.getResource()+1);
		}
		public int getResource(){
			return head.getResource();
		}
//	}
}
